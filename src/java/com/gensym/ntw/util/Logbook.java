/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Logbook.java
 *
 */

package com.gensym.ntw.util;

import java.awt.event.ActionEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseEvent;
import java.util.Enumeration;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.classes.Message;
import com.gensym.classes.LogbookParameters;
import com.gensym.message.Trace;
import com.gensym.util.ItemListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.Denotation;
import com.gensym.uitools.utils.StatusBar;
import java.util.Vector;

/**
 * Logbook is a client view of G2's Logbook.  The Logbook is represented
 * by a tabular view with a toolbar to perform standard operations. 
 */

public class Logbook extends KbMessageTableView {

  private GoToReferencedItemCommand goToCommand;
  private ClearCommand clearCommand;
  private FindCommand findCommand;


  /**
   * Creates a Logbook for the specified connection.  It is initialized
   * with the current contents of the Logbook in G2.
   */
  public Logbook(TwAccess connection) throws G2AccessException{
    super(connection, new LogbookKbMessageAdapter());
    initialize(connection);
  }

  public Logbook(TwAccess connection, LogbookParameters logParam) throws G2AccessException{
    super(connection, new LogbookKbMessageAdapter(logParam));
    initialize(connection);
 }

  private void initialize(TwAccess connection) throws G2AccessException {
    goToCommand = new GoToReferencedItemCommand(this);
    clearCommand = new ClearCommand(this);
    findCommand = new FindCommand(this);
    toolBar.add(goToCommand);
    toolBar.add(clearCommand);
    toolBar.add(findCommand);
    
    ((LogbookKbMessageAdapter)kbMessageListener).setTableView(tableView);
    ((LogbookKbMessageAdapter)kbMessageListener).setLogbook(this,
							    this.statusBar);
    connection.getKb().addKbMessageListener(kbMessageListener); 

    popup.add(goToCommand,menuConstraints);
    popup.add(clearCommand, menuConstraints);
    popup.add(findCommand, menuConstraints);
  }

  /**
   *  Unhooks this Logbook from receiving KbEvents from G2.
   */
  @Override
  public void dispose() throws G2AccessException{
    super.dispose ();
    tableView.clear();
    ((LogbookKbMessageAdapter)kbMessageListener).dispose();
  }
}


class LogbookKbMessageAdapter extends Thread implements KbMessageListener, ItemListener, MouseListener {

  private static final Symbol LOGBOOK_ = Symbol.intern("LOGBOOK");
  private Vector events = new Vector();
  private TableView tableView;
  private LogbookParameters logParam;
  private Logbook logbook;
  private StatusBar statusBar;
  private static final Symbol MAXIMUM_NUMBER_OF_PAGES_TO_KEEP_IN_MEMORY_ = Symbol.intern("MAXIMUM-NUMBER-OF-PAGES-TO-KEEP-IN-MEMORY");

  public LogbookKbMessageAdapter() {
    start();
  }

  public LogbookKbMessageAdapter(LogbookParameters lp) {
    logParam = lp;
    try {
      logParam.addItemListener(this);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
    start();    
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

  private void processKbEvent(KbEvent event) {
    switch(event.getID()) {
    case KbEvent.KB_MESSAGES_INITIAL_DOWNLOAD:
      handleReceivedInitialContents(event);
      break;      
    case KbEvent.KB_LOGBOOK_MESSAGE_ADDED:
      handleKbMessageAdded(event);      
      break;      
    case KbEvent.KB_LOGBOOK_MESSAGE_DELETED:
      handleKbMessageDeleted(event);            
      break;
    }
  }
  
  public void dispose() throws G2AccessException {
    if (logParam != null)
      logParam.removeItemListener(this);
  }
  @Override
  public void mousePressed(MouseEvent event){
    Logbook.popupMenuIfNecessary(event, tableView.getTable());
  }
  @Override
  public void mouseReleased(MouseEvent event){
    Logbook.popupMenuIfNecessary(event, tableView.getTable());
  }

  @Override
  public void mouseClicked(MouseEvent e){
    if (e.getClickCount() == 2) {
      logbook.viewMessageCommand.actionPerformed(new ActionEvent(logbook, 0, ""));
    }
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
      if ((Symbol)struct.getAttributeValue(Denotation.NAME_, null) == MAXIMUM_NUMBER_OF_PAGES_TO_KEEP_IN_MEMORY_)
	tableView.setMessageLimit(logParam.getMaximumNumberOfPagesToKeepInMemory());
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  public void handleReceivedInitialContents (KbEvent event){    
    
    Structure initialData = (Structure)event.getData();
    Sequence logbookMsgs = (Sequence)initialData.getAttributeValue(LOGBOOK_, null);
    Enumeration msgs = logbookMsgs.elements();
    while (msgs.hasMoreElements()) {
      KbMessage viewMsg = new KbMessage((Message)msgs.nextElement(), true);
      if (viewMsg.isValid)
	tableView.addTableViewMessage(viewMsg);
    }
  }

  private void handleKbMessageAdded(KbEvent event) {
    if (event.getID() == KbEvent.KB_LOGBOOK_MESSAGE_ADDED) {
      KbMessage viewMsg = new KbMessage((Message)event.getData(), true);
      if (viewMsg.isValid)
	tableView.addTableViewMessage(viewMsg);
      try{
	String message = ((com.gensym.classes.MessageImpl)viewMsg.
			  getMessage()).getText();
	statusBar.setStatus(Logbook.getMessageNumber(message),
			    Logbook.NUMBER);
	statusBar.setStatus(Logbook.getMessageTime(message),
			    Logbook.TIME);
      } catch (G2AccessException gae){
	Trace.exception(gae);
      }
      statusBar.flashColor();
    }
  }
  
  public void handleKbMessageDeleted(KbEvent event){    
    if (event.getID() == KbEvent.KB_LOGBOOK_MESSAGE_DELETED) 
      tableView.removeTableViewMessage(new KbMessage((Message)event.getData(), false));
  }

  void setTableView(TableView tableView) throws G2AccessException {
    this.tableView = tableView;
    tableView.setMessageLimit(logParam.getMaximumNumberOfPagesToKeepInMemory());
    tableView.getTable().addMouseListener(this);
  }

  void setLogbook(Logbook logbook, StatusBar statusBar) {
    this.logbook = logbook;
    this.statusBar = statusBar;
  }
}




