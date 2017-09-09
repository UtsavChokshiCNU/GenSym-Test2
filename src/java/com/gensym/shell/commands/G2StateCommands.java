/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2StateCommands.java
 *
 */
package com.gensym.shell.commands;

import java.util.Vector;
import java.awt.event.ActionEvent;
import com.gensym.ntw.TwAccess;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.WarningDialog;
import com.gensym.dlg.QuestionDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlg.CommandConstants;
import com.gensym.ntw.TwGateway;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2CommunicationErrorEvent;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2AccessInitiationException;
import com.gensym.jgi.G2AccessException;
import com.gensym.core.UiApplication;
import com.gensym.util.Symbol;
import com.gensym.message.Resource;
import com.gensym.shell.util.*;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.CommandEvent;

/** 
 * Command to start, pause, resume, reset, and restart G2.  All G2 state
 * changes are performed on the current connection.  This command may be
 * used in both single and multiple connection applications.  In single connection
 * applications, the application is responible for updating this command with
 * the current connection via setConnection.  In multiple connection applications,
 * the ConnectionManager is used to obtain the currentConnection.  This command's
 * availability will always reflect the current state of the G2 that corresponds
 * to the current connection.
 *
 */
public final class G2StateCommands extends AbstractCommand{
  /** Command key to start G2. */
  public static final String START = "Start";
  /** Command key to restart G2. */
  public static final String RESTART = "Restart";
  /** Command key to pause G2. */
  public static final String PAUSE = "Pause";
  /** Command key to resume G2. */
  public static final String RESUME = "Resume";
  /** Command key to reset G2. */
  public static final String RESET = "Reset";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");
  private Resource shortBundle = Resource.getBundle("com/gensym/shell/commands/CommandShortResource");

  private TwAccess currentConnection;

  private ContextChangedListener contextChangedListener;
  private G2ConnectionListener g2ConnectionAdapter;
  private StandardDialogClient dlgClient;
  private String currentCommand = null;
  private boolean promptBeforeRestartEnabled = true;;
  private boolean promptBeforeResetEnabled = true;
  /**
   *  Creates a G2StateCommands for a single connection application.
   */
  public G2StateCommands(TwAccess connection){
    this();
    setConnection(connection);
  }

  /**
   *  Creates a G2StateCommands for a multiple connection application.
   */
  public G2StateCommands(ConnectionManager connectionMgr){
    this();
    setConnection(connectionMgr.getCurrentConnection());
    contextChangedListener = new ContextChangedAdapter();
    connectionMgr.addContextChangedListener(contextChangedListener);
  }

  private G2StateCommands(){
    super(new CommandInformation[]{
      new CommandInformation(START, true, shortResource, longResource, 
			     "start.gif", null, null, true),
      new CommandInformation(RESTART, true, shortResource, longResource,
			     "restart.gif", null, null, true),
      new CommandInformation(PAUSE, true, shortResource, longResource, 
			     "pause.gif", null, null, true),
      new CommandInformation(RESUME, true, shortResource, longResource, 
			     "resume.gif", null, null, true),
      new CommandInformation(RESET, true, shortResource, longResource, 
			     "reset.gif", null, null, true)});
    g2ConnectionAdapter = new G2StateConnectionAdapter();
    dlgClient = new DialogClient();
  }  
	
  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)) {
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", cmdKey));
    }

    try{
      if ((cmdKey.equals(START))||(cmdKey.equals(RESUME)))
	currentConnection.setG2State(TwGateway.RUNNING_);
      else if (cmdKey.equals(RESTART)){
	if (!promptBeforeRestartEnabled)
	  executeRestartCommand();
	else{
	  currentCommand = RESTART;
	  QuestionDialog qd = new QuestionDialog(UiApplication.getCurrentFrame(), shortBundle.getString("StandardDialogTitle"), true, shortBundle.getString("PromptToRestart"), dlgClient);
	  qd.setVisible(true);
	}
      }
      else if (cmdKey.equals(PAUSE))
        currentConnection.setG2State(TwGateway.PAUSED_);
      else if (cmdKey.equals(RESET)){
	if (!promptBeforeResetEnabled)
	  executeResetCommand();
	else{
	  currentCommand = RESET;
	  QuestionDialog qd = new QuestionDialog(UiApplication.getCurrentFrame(), shortBundle.getString("StandardDialogTitle"), true, shortBundle.getString("PromptToReset"), dlgClient);
	  qd.setVisible(true);
	}
      }
    }
    catch(G2AccessException ex){
      displayAccessError(ex);
    }
  }

  private void executeRestartCommand(){
    try{
      currentConnection.setG2State(TwGateway.RESET_);
      currentConnection.setG2State(TwGateway.RUNNING_);
    }
    catch(G2AccessException ex){
      displayAccessError(ex);
    }
  }

  private void executeResetCommand(){
    try{
      currentConnection.setG2State(TwGateway.RESET_);
    }
    catch(G2AccessException ex){
      displayAccessError(ex);
    }
  }

  private void displayAccessError(G2AccessException ex){
    String cxnString = currentConnection.toShortString();
    String msg = ex.getMessage();
    if (msg == null)
      new WarningDialog(null, i18n.getString("Error"), true, i18n.format("AccessError", cxnString), null).setVisible(true);
    else
      new WarningDialog(null, i18n.getString("Error"), true, i18n.format("AccessErrorWithReason", cxnString, msg), null).setVisible(true);
  }
  

  /**
   * Sets the current connection.  This command's actions act upon the current
   * connection.  Single connection application should use this method to
   * inform this command about changes in the current connection.
   */
  public void setConnection(TwAccess connection){
    //stop listening to old current connection
    if (currentConnection != null)
      currentConnection.removeG2ConnectionListener(g2ConnectionAdapter);
    //set new current connection
    currentConnection = connection;
    //start listening to new current connection
    if (currentConnection != null)
      currentConnection.addG2ConnectionListener(g2ConnectionAdapter);
    updateAvailability();
  }

  /**
   *  Returns true if the user is prompted before the KB is restarted.
   */
  public boolean isPromptBeforeRestartEnabled(){
    return promptBeforeRestartEnabled;
  }

  /**
   *  Set whether to prompt the user before restarting the KB.  The default
   *  value if true.
   */
  public void setPromptBeforeRestartEnabled(boolean promptBeforeRestart){
    promptBeforeRestartEnabled = promptBeforeRestart;
  }

  /**
   *  Returns true if the user is prompted before the KB is reset.
   */
  public boolean isPromptBeforeResetEnabled(){
    return promptBeforeResetEnabled;
  }

  /**
   *  Set whether to prompt the user before resetting the KB.  The default value
   *  is true.
   */
  public void setPromptBeforeResetEnabled(boolean promptBeforeReset){
    promptBeforeResetEnabled = promptBeforeReset;
  }


  private void updateAvailability(){
    if (currentConnection == null) 
      noConnection();
    else{
      try{
	Symbol state_ = currentConnection.getG2State();
	if (state_.equals(G2Gateway.RUNNING_)) g2Running();
	else if (state_.equals(G2Gateway.PAUSED_)) g2Paused();
	else if (state_.equals(G2Gateway.RESET_)) g2Reset();
      }
      catch(G2AccessException ex){
	com.gensym.message.Trace.exception(ex);
	noConnection();
      }
    }
  }

  private void g2Running(){
    setConnectionStateAvailability(false, true, true, false, true);
  }

  private void g2Reset(){
    setConnectionStateAvailability(true, false, false, false, false);
  }

  private void g2Paused(){
    setConnectionStateAvailability(false, true, false, true, true);
  }

  private void noConnection(){
    setConnectionStateAvailability(false, false, false, false, false);
  }

  private void setConnectionStateAvailability(
				       boolean startState, boolean restartState, 
				       boolean pauseState, boolean resumeState,
				       boolean resetState){
    setAvailable(START, startState);
    setAvailable(RESTART, restartState);
    setAvailable(PAUSE, pauseState);
    setAvailable(RESUME, resumeState);
    setAvailable(RESET, resetState);
  }    

  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      setConnection(e.getConnection());
    }
  }

  class G2StateConnectionAdapter extends G2ConnectionAdapter{
    @Override
    public void g2IsPaused (G2ConnectionEvent event) {
      g2Paused();
    }
    
    @Override
    public void g2IsResumed (G2ConnectionEvent event) {
      g2Running();
    }
    
    @Override
    public void g2IsReset (G2ConnectionEvent event) {
      g2Reset();
    }
    
    @Override
    public void g2IsStarted (G2ConnectionEvent event) {
      g2Running();
    }
  }

  class DialogClient implements StandardDialogClient{

    @Override
    public void dialogDismissed (StandardDialog d, int cmdCode){
      d.setVisible(false);
      if (cmdCode == CommandConstants.YES) {
	if (currentCommand.equals(RESTART))
	  executeRestartCommand();
	else
	  executeResetCommand();
      }
    }
  }
}


