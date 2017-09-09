/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ModeCommands.java
 *
 */
package com.gensym.demos.sequoia.course;

import java.awt.event.ActionEvent;
import com.gensym.dlg.WarningDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwGateway;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.util.Symbol;

public class ModeCommands extends AbstractCommand implements ContextChangedListener {

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");
  private Resource shortBundle = Resource.getBundle("com/gensym/demos/sequoia/course/CommandShortResource");

  private static final String USER = "User";
  private static final String DEVELOPER = "Developer";

  //define on and off states
  private  Boolean off = new Boolean(false);
  private Boolean on = new Boolean(true);

  //get user and developer mode command keys
  private String[] modes = getKeys();
  private String user = modes[0];
  private String developer = modes[1];

  private TwAccess currentConnection = null;

  public ModeCommands(ConnectionManager connectionManager) {
    super(new CommandInformation[]{
      new CommandInformation(USER, true, 
			     shortResource, longResource, 
			     null, null, Boolean.TRUE, true),
      new CommandInformation(DEVELOPER, true, 
			     shortResource, longResource,
			     null, null, Boolean.FALSE, true)});

    setConnection(connectionManager.getCurrentConnection());
    connectionManager.addContextChangedListener(this);
  }

  @Override
  public void currentConnectionChanged(ContextChangedEvent e){
    setConnection(e.getConnection());
  }

  public void setConnection(TwAccess connection){
    currentConnection = connection;
    boolean available = true;
    available = (currentConnection != null);
  
    // GET_KBWORKSPACE should check for named workspaces
    setAvailable(USER, available);
    setAvailable(DEVELOPER, available);
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)){
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", 
						  cmdKey));
    } 

    if (cmdKey.equals(USER))
      handleUserCommand();
    else if (cmdKey.equals(DEVELOPER))
      handleDeveloperCommand();
  }

  @Override
  public String[] getKeys(){
    return new String[] {USER, DEVELOPER};
  }

  private void handleUserCommand() {
    //get current state of User command
    Boolean state = this.getState(USER);

    //set state of user and developer commands based on user mode state
    if (state.booleanValue()) {
      this.setState(USER, off);
      this.setState(DEVELOPER, on);
    } else {
      this.setState(USER, on);
      this.setState(DEVELOPER, off);
    }

    //initialize user mode as a symbol
    Symbol user = Symbol.intern ("USER");

    //call setUserMode on the connection
    try {
      ((TwGateway)currentConnection).setUserMode(user);
      //System.out.println(((TwGateway)currentConnection).getUserMode());
    }
    catch (G2AccessException ex){
      Trace.exception(ex);
    }
  }

  private void handleDeveloperCommand() {
    //get current state of Developer command
    Boolean state = this.getState(DEVELOPER);

    //set state of user and developer commands based on developer mode state
    if (state.booleanValue()) {
      this.setState(developer, off);
      this.setState(user, on);
    } else {
      this.setState(developer, on);
      this.setState(user, off);
    }

    //initialize user mode as a symbol
    Symbol developer = Symbol.intern ("DEVELOPER");

    //call setUserMode on the connection
    try {
      ((TwGateway)currentConnection).setUserMode(developer);
      //System.out.println(((TwGateway)currentConnection).getUserMode());
    }
    catch (G2AccessException ex){
      Trace.exception(ex);
    }
  }

  //create and show an error dialog
  private void displayError(String title, String msg) {
     WarningDialog dlg = new WarningDialog (null, title, true, msg, 
				       (StandardDialogClient) null);
     dlg.show();
  }
}











