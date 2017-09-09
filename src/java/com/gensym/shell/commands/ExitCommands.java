/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ExitCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.Frame;
import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;
import java.awt.event.ActionEvent;
import com.gensym.core.ExitThread;
import com.gensym.ntw.TwAccess;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;

public final class ExitCommands extends AbstractCommand implements WindowListener {
  /** Command to exit application */
  public static final String EXIT = "ExitTelewindows2";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");

  private ConnectionManager connectionMgr = null;
  private TwAccess          singleConnection = null;

  public ExitCommands(Frame frame, TwAccess connection) {
    this(frame, (ConnectionManager)null);
    singleConnection = connection;
  }

  public ExitCommands(Frame frame, ConnectionManager connectionManager) {
    super(new CommandInformation[]{
      new CommandInformation(EXIT, true, shortResource, longResource, "exit_tw.gif", 
			     null, null, true, mnemonicResource, null)});

    connectionMgr = connectionManager;
    frame.addWindowListener((WindowListener)this);
  }

  public void setConnection(TwAccess connection){
    singleConnection = connection;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)){
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", 
						  cmdKey));
    }
    
    if (singleConnection != null)
      exitApp(singleConnection);
    else if (connectionMgr != null)
      exitApp(connectionMgr);
    else exitApp();
  }

  @Override
  public void windowClosing(WindowEvent e) {
    if (singleConnection != null)
      exitApp(singleConnection);
    else if (connectionMgr != null)
      exitApp(connectionMgr);
    else
      exitApp();
  }

  @Override
  public void windowActivated(WindowEvent e) {}
  @Override
  public void windowDeactivated(WindowEvent e) {}
  @Override
  public void windowOpened(WindowEvent e) {}
  @Override
  public void windowClosed(WindowEvent e) {}
  @Override
  public void windowIconified(WindowEvent e) {}
  @Override
  public void windowDeiconified(WindowEvent e) {}

  private void exitApp(ConnectionManager connectionManager) {
    TwAccess[] cxns = connectionManager.getOpenConnections();
    for (int i=0; i<cxns.length; i++)
      cxns[i].closeConnection();
    exitApp();
  }

  private void exitApp(TwAccess connection) {
    connection.closeConnection();
    exitApp();
  }

  private void exitApp() {
    ExitThread.exit();
  }

}
