/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TW2Application.java
 *
 */
package com.gensym.shell.util;

import java.awt.Frame;
import java.util.Properties;
import java.awt.Component;
import java.util.Vector;
import com.gensym.dlg.ErrorDialog;
import com.gensym.mdi.MDIFrame;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.ntw.LoginRequest;
import com.gensym.ntw.TwAccess;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.util.Symbol;
import com.gensym.message.Resource;
import com.gensym.message.Trace;

/**
 * A Class that can be used as the parent of all Telewindows2 User Interface applications.
 * It provides support for getting the ConnectionManager (or the current connection
 * of a single connection application) and handling of command-line options.
 */
public abstract class TW2Application extends com.gensym.core.UiApplication {

  private static TwConnectionInfo connectionInfo = null;
  private static LoginRequest loginRequest = null;

  /**
   * Creates a TW2Application
   * @param isMultipleFrames Indicates whether this application should support
   * multiple frames
   */
  protected TW2Application(String[] commandLine, boolean isMultipleFrames) {
    super(commandLine, isMultipleFrames);
    initialize(commandLine);
  }

  /** 
   * Calls static initializers based on the commandLine arguments.
   */
  public static void initialize (String[] commandLine) {
    TW2DefaultCommandLineHandler argHandler =
      new TW2DefaultCommandLineHandler(commandLine);

    connectionInfo = argHandler.getG2ConnectionInformation();
    loginRequest = argHandler.getLoginRequest();
  }

  /**
   * Creates a TW2Application single frame application
   */
  protected TW2Application (String[] commandLine) {
    this (commandLine, false);
  }

  /**
   * @return the TwConnectionInfo created from parsing the command 
   * line arguments (url, host, port)
   */
  public static TwConnectionInfo getG2ConnectionInformation() {
    return connectionInfo;
  }

  /**
   * @return the LoginRequest created from parsing the command
   * line arguments (mode, user-name, password) 
   */
  public static LoginRequest getLoginRequest(){
    return loginRequest;
  }

  /**
   * Returns the current connection for single connection applications.
   * For multiple connection applications this method can return null.
   * Clients should call getConnectionManager().getCurrentConnection()
   * instead.
   * @return the current connection of the TW2Application
   */
  public abstract TwAccess getConnection();

  /**
   * This sets the current connection (which will be returned by getConnection).
   * Single connection application subclasses should accept this
   * as being the open connection. For multiple connection subclasses,
   * this method call may do nothing or throw an exception. Clients
   * should call getConnectionManager().setCurrrentConnection(TwAccess)
   * instead.
   * @param connection the current connection
   */
  public abstract void setConnection(TwAccess connection);

  /**
   * Returns the com.gensym.shell.util.ConnectionManager for multiple connection
   * applications using the ConnectionManager.
   * Subclasses that support multiple connection applications using the
   * ConnectionManager may use this.
   * @return the ConnectionManager of the TW2Application
   */
  public abstract ConnectionManager getConnectionManager();
}
