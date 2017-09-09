/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MessageBoard.java
 *
 */

package com.gensym.ntw.util;

import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;
import java.util.Enumeration;
import java.util.Vector;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.classes.Message;
import com.gensym.classes.MessageBoardParameters;
import com.gensym.message.Trace;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.Denotation;
import com.gensym.uitools.utils.StatusBar;

/**
 * MessageBoard is a client view of G2's Message Board.  The Message Board is represented
 * by a tabular view with a toolbar to perform standard operations. 
 */
public class MessageBoard extends KbMessageTableView{

  /**
   * Creates a MessageBoard for the specified connection.  The MessageBoard is initialized
   * with the current contents of the Message Board.
   */

  private GoToMessageOriginCommand goToOriginCommand;

  public MessageBoard(TwAccess connection) throws G2AccessException{
    super(connection, new MessageBoardKbMessageAdapter());
    initialize(connection);
  }

  public MessageBoard(TwAccess connection, 
		      MessageBoardParameters mbParam) throws G2AccessException
  {
    super(connection, new MessageBoardKbMessageAdapter(mbParam));
    initialize(connection);
  }

  private void initialize(TwAccess connection) throws G2AccessException {
    goToOriginCommand = new GoToMessageOriginCommand(this);
    toolBar.add(goToOriginCommand);
    ((MessageBoardKbMessageAdapter)kbMessageListener).setTableView(tableView);
    ((MessageBoardKbMessageAdapter)kbMessageListener).setMBoard(this, this.statusBar);
    connection.getKb().addKbMessageListener(kbMessageListener);
    popup.add(goToOriginCommand,menuConstraints);
  }

  /**
   *  Unhooks this MessageBoard from receiving KbEvents from G2.
   */
  @Override
  public void dispose() throws G2AccessException{
    super.dispose ();
    tableView.clear();
    ((MessageBoardKbMessageAdapter)kbMessageListener).dispose();
  }
}

class MessageBoardKbMessageAdapter extends Thread implements KbMessageListener, ItemListener, MouseListener {

  private MessageBoard mBoard;
  private StatusBar statusBar;
  private MessageBoardParameters mbParam;
  private static final Symbol MESSAGE_BOARD_ = Symbol.intern("MESSAGE-BOARD");
  private static final Symbol HIGHLIGHT_NEW_MESSAGES_ = Symbol.intern("HIGHLIGHT-NEW-MESSAGES");
  private TableView tableView;
  private KbMessage previousMessage;
  private boolean highlight;
  private Vector events = new Vector();

  public MessageBoardKbMessageAdapter() {
    highlight = true;
    start();
  }

  public void dispose() throws G2AccessException {
    if (mbParam != null)
      mbParam.removeItemListener(this);
  }
  
  public MessageBoardKbMessageAdapter(MessageBoardParameters mp) {
    mbParam = mp;
    try {
      highlight = mbParam.getHighlightNewMessages();
      mbParam.addItemListener(this);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
    start();
  }

  @Override
  public void run() {
    while (true) {
      KbEvent[] evts = null;
      int count;
      synchronized (events) {
	count = events.size();
	evts = new KbEvent[count];
	events.copyInto(evts);
	events.clear();
      }
      for(int i=0;i<count;i++) 
	processKbEvent(evts[i]);
      try {
	synchronized (this) {
	  wait();
	}
      } catch (InterruptedException ie) {
	Trace.exception(ie);
      }
    }
  }

  @Override
  public void receivedInitialContents (KbEvent event){
    events.addElement(event);
    synchronized(this) {    
      notify();
    }
  }
  
  @Override
  public void kbMessageAdded(KbEvent event){
    events.addElement(event);
    synchronized(this) {    
      notify();
    }
  }
  
  @Override
  public void kbMessageDeleted(KbEvent event){
    events.addElement(event);
    synchronized(this) {
      notify();
    }
  }
  
  private void processKbEvent(KbEvent event) {
    switch(event.getID()) {
    case KbEvent.KB_MESSAGES_INITIAL_DOWNLOAD:
      handleReceivedInitialContents(event);
      break;      
    case KbEvent.KB_MESSAGE_BOARD_MESSAGE_ADDED:
      handleKbMessageAdded(event);      
      break;      
    case KbEvent.KB_MESSAGE_BOARD_MESSAGE_DELETED:
      handleKbMessageDeleted(event);            
      break;
    }
  }
  
  @Override
  public void mousePressed(MouseEvent event){
    MessageBoard.popupMenuIfNecessary(event, tableView.getTable());
  }
  @Override
  public void mouseReleased(MouseEvent event){
    MessageBoard.popupMenuIfNecessary(event, tableView.getTable());
  }

  @Override
  public void mouseClicked(MouseEvent e){
    if (e.getClickCount() == 2)
      mBoard.viewMessageCommand.actionPerformed(new ActionEvent(mBoard, 0, ""));
  }
  @Override
  public void mouseEntered(MouseEvent e){}
  @Override
  public void mouseExited(MouseEvent e){}

  @Override
  public void receivedInitialValues(ItemEvent e) {}
  @Override
  public void itemDeleted(ItemEvent e){}
  @Override
  public void itemModified(ItemEvent e) {
    try {
      Sequence denotation = e.getDenotation();
      Structure struct = (Structure)denotation.elementAt(0);
      if ((Symbol)struct.getAttributeValue(Denotation.NAME_, null) == HIGHLIGHT_NEW_MESSAGES_)
      highlight = ((MessageBoardParameters)e.getSource()).getHighlightNewMessages();
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  public void handleReceivedInitialContents (KbEvent event){
    Structure initialData = (Structure)event.getData();
    Sequence msgBoardMsgs = (Sequence)initialData.getAttributeValue(MESSAGE_BOARD_, null);
    Enumeration msgs = msgBoardMsgs.elements();
    while (msgs.hasMoreElements()) {
      previousMessage = new KbMessage((Message)msgs.nextElement(), true);
      if (previousMessage.isValid)
	tableView.addTableViewMessage(previousMessage);
    }
    if (highlight && previousMessage != null)
      previousMessage.setBackgroundColor(Color.green);
  }
  
  public void handleKbMessageAdded(KbEvent event){
    KbMessage newMessage;

    if (event.getID() == KbEvent.KB_MESSAGE_BOARD_MESSAGE_ADDED){
      if (previousMessage != null)
	previousMessage.setBackgroundColor(Color.white);
      newMessage = new KbMessage((Message)event.getData(), true);
      if (highlight)
	newMessage.setBackgroundColor(Color.green);
      if (newMessage.isValid)
	tableView.addTableViewMessage(newMessage);
      previousMessage = newMessage;
      try{
	String message = ((com.gensym.classes.MessageImpl)newMessage.
			  getMessage()).getText();
	statusBar.setStatus(MessageBoard.getMessageNumber(message),
			    MessageBoard.NUMBER);
	statusBar.setStatus(MessageBoard.getMessageTime(message),
			    MessageBoard.TIME);
      } catch (G2AccessException gae){
	Trace.exception(gae);
      }
      statusBar.flashColor();
    }
  }
  
  private void handleKbMessageDeleted(KbEvent event){
    if (event.getID() == KbEvent.KB_MESSAGE_BOARD_MESSAGE_DELETED){
      tableView.removeTableViewMessage(new KbMessage((Message)event.getData(), false));
      tableView.getTable().clearSelection();
    }
  }

  void setMBoard(MessageBoard mBoard, StatusBar statusBar) {
    this.mBoard = mBoard;
    this.statusBar = statusBar;
  }
  
  void setTableView(TableView tableView){
    this.tableView = tableView;
    tableView.getTable().addMouseListener(this);
  }
}




