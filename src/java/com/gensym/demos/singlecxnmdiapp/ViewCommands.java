/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ViewCommands.java
 *
 */
package com.gensym.demos.singlecxnmdiapp;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.WindowEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowListener;
import javax.swing.JDialog;
import com.gensym.shell.util.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.dlg.WarningDialog;
import com.gensym.ntw.TwAccess;
import com.gensym.core.UiApplication;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ntw.util.KbMessageTableView;
import com.gensym.ntw.util.MessageBoard;
import com.gensym.ntw.util.Logbook;
import com.gensym.ntw.util.WindowUtil;
import com.gensym.message.Resource;
import com.gensym.message.Trace;

public final class ViewCommands extends AbstractCommand {

  public static final String VIEW_LOGBOOK = "ViewLogbook";
  public static final String VIEW_MESSAGE_BOARD = "ViewMessageBoard";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";

  private Resource shortBundle = Resource.getBundle("com/gensym/demos/singlecxnmdiapp/CommandShortResource");
  private Resource i18n = Resource.getBundle("com/gensym/demos/singlecxnmdiapp/Errors");

  private UiApplication app;
  
  private ConnectionManager connectionManager;
  private TwAccess currentConnection;

  private ViewDialog messageBoardDialog;
  private ViewDialog logbookDialog;

  public ViewCommands(UiApplication app){
    super (new CommandInformation[]{
      new CommandInformation(VIEW_LOGBOOK, true, shortResource, 
			     longResource, "logbook.gif", null, Boolean.FALSE, true),
      new CommandInformation(VIEW_MESSAGE_BOARD, true, shortResource, 
			     longResource, "messageboard.gif", null, Boolean.FALSE, true)});

    this.app = app;

    if (app instanceof TW2Application){
      connectionManager = ((TW2Application)app).getConnectionManager();
      currentConnection = ((TW2Application)app).getConnection();
    }
    else if (app instanceof TW2MDIApplication){
      connectionManager = ((TW2MDIApplication)app).getConnectionManager();
      currentConnection = ((TW2MDIApplication)app).getConnection();
    }

    if (connectionManager != null)
      connectionManager.addContextChangedListener(new ConnectionChangedListener());

    updateAvailability();
  }

  private void updateAvailability(){
    setAvailable(VIEW_LOGBOOK, (currentConnection != null));
    setAvailable(VIEW_MESSAGE_BOARD, (currentConnection != null));
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (!isAvailable(cmdKey))
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", 
						  cmdKey));
    if (getState(cmdKey).booleanValue())
      hideView(cmdKey);
    else
      showView(cmdKey);
  }

  private void hideView(String key){
    try{
      ViewDialog dlg;
      if (key.equals(VIEW_LOGBOOK)){
	dlg = logbookDialog;
	logbookDialog = null;
      }
      else{
	dlg = messageBoardDialog;
	messageBoardDialog = null;
      }
      if (dlg != null){
	dlg.setVisible(false);
	dlg.disposeView();
      }
      setState(key, Boolean.FALSE);
    }
    catch(G2AccessException ex){
      new WarningDialog(app.getCurrentFrame(),
			i18n.getString("Error"), true, 
			i18n.format("CommunicationError", ex.toString()), 
			null).setVisible(true);
      Trace.exception(ex);
    }
  }

  private void showView(String key){
    try{
      if (key.equals(VIEW_LOGBOOK))
	logbookDialog = new ViewDialog(app, currentConnection, key);
      else
	messageBoardDialog = new ViewDialog(app, currentConnection, key);
      setState(key, Boolean.TRUE);
    }
    catch(G2AccessException ex){
      new WarningDialog(app.getCurrentFrame(),
			i18n.getString("Error"), true, 
			i18n.format("CommunicationError", ex.toString()), 
			null).setVisible(true);
      Trace.exception(ex);
    }
  }

  public void setConnection(TwAccess connection){
    if (connectionManager == null){
      if (((currentConnection != null) && ((!currentConnection.equals(connection)))) ||
	  ((currentConnection == null) && (connection != null)))
	setCurrentConnection(connection);
    }
    else
      throw new IllegalStateException(i18n.getString("CantCallSetCxnInMultiCxnApp"));
  }

  private void setCurrentConnection(TwAccess connection){
    currentConnection = connection;
    if (currentConnection == null || connectionManager != null){
      hideView(VIEW_LOGBOOK);
      hideView(VIEW_MESSAGE_BOARD);
    }
    updateAvailability();
  }

  class ConnectionChangedListener implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      setCurrentConnection(e.getConnection());
    }
  }

  class DialogClient extends WindowAdapter{
    
    private String key;

    DialogClient(String key){
      this.key = key;
    }
    
    @Override
    public void windowClosing(WindowEvent event){
      hideView(key);
    }
  }

  class ViewDialog extends JDialog{
    
    private KbMessageTableView logbookOrMessageBoard;
    
    ViewDialog(UiApplication app, TwAccess connection, String key) 
	 throws G2AccessException{
	   super(app.getCurrentFrame());
	   if (key.equals(ViewCommands.VIEW_LOGBOOK)){
	     logbookOrMessageBoard = new Logbook(connection);
	     setTitle(shortBundle.format("LogbookFor", connection.toShortString()));
	   }
	   else{
	     logbookOrMessageBoard = new MessageBoard(connection);
	     setTitle(shortBundle.format("MessageBoardFor", connection.toShortString()));
	   }
	   getContentPane().add(logbookOrMessageBoard, BorderLayout.CENTER);
	   addWindowListener(new DialogClient(key));
	   setSize(400, 300);
	   WindowUtil.centerFrame(app.getCurrentFrame(), this);
	   setVisible(true);
    }
    
    void disposeView() throws G2AccessException{
      logbookOrMessageBoard.dispose();
    }
  }

}
