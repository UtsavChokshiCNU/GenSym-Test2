/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TopLevelSystemTablesCommands.java
 *
 */
package com.gensym.shell.commands;

import java.awt.Component;
import java.awt.event.ActionEvent;
import java.net.MalformedURLException;

import com.gensym.classes.Kb;
import com.gensym.classes.Module;
import com.gensym.classes.Item;
import com.gensym.classes.ImplAccess;
import com.gensym.dlgruntime.DialogManager;
import com.gensym.dlgruntime.ResourceInstantiationException;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.shell.util.ConnectionManager;

import com.gensym.shell.util.ContextChangedListener;
import com.gensym.shell.util.ContextChangedEvent;

/** 
 * Command to access the System Tables for a top level module. The
 * application adding this command is responsible for managing the 
 * connection, if using TwAccess to construct the command. Use the 
 * method {@link setConnection} for this purpose. The connection
 * is managed automatically by this command, if a {@link com.gensym.shell.util.ConnectionManager}
 * is used to construct it. 
 * 
 */

public class TopLevelSystemTablesCommands extends SystemTablesCommands
implements ContextChangedListener{

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";

  private static Resource i18n = Resource.getBundle("com/gensym/shell/commands/Messages");
  private Component requestingComponent;
  private ConnectionManager connectionManager;
  private TwAccess currentConnection;
  
  /**
   * Creates a TopLevelSystemTablesCommand for the top level module
   * of the given connection. The application using this constructor
   * is responsible for updating the command with new connection information,
   * using the {@link #setConnection} method.
   * @param {@link java.awt.Component} a parent component  which requests and controls where the System
   * Table dialog will be displayed
   * @param {@link com.gensym.ntw.TwAccess}  a connection which 
   * determines the top level module, for which to create the System Tables
   */
  public TopLevelSystemTablesCommands(Component requestingComponent, TwAccess connection) {
    super(requestingComponent);
    setConnection(connection);
     
  }  

  /**
   * Creates a TopLevelSystemTablesCommand for the top level module
   * of the current connection, which is determined automatically by the 
   * Connection Manager of the application. 
   * @param {@link java.awt.Component} a component which requests and controls where the System
   * Table dialog will be displayed
   * @param {@link com.gensym.shell.util.ConnectionManager}  a Connection Manager which 
   * determines the current connection, which in turn determines the top level module
   * for which to create the System Tables
   */
  public TopLevelSystemTablesCommands (Component requestingComponent, ConnectionManager cxnManager) {
    super(requestingComponent);
    connectionManager = cxnManager;
    connectionManager.addContextChangedListener(this);
    setConnection(connectionManager.getCurrentConnection());
  }


  /**
   * @undocumented
   * For internal use only, gets the current top level module
   * for the connection
   */
  @Override
  public Module getModule(){
    if (currentConnection != null){
      try {
	Module mod = currentConnection.getKb().getTopLevelModule();
	return mod;
      } catch (G2AccessException gae) {
	Trace.exception (gae);
      }
      
    }
    // if no connection - no module
    return null;
  }

   /**
   * Sets the current connection.  This command's actions act upon the current
   * connection.  Single connection application should use this method to
   * inform this command about changes in the current connection.
   * @param {@link com.gensym.ntw.TwAccess} a TwAccess current connection
   */
  //This method must set the current top level module, using the super-class's
  // setModule method.
  public void setConnection(TwAccess connection) {
    currentConnection = connection;
    setModule(getModule());
  }

  /**
   * @undocumented
   * method used by the super class to get the current connection
   */
      
  protected TwAccess getConnection(){
    return currentConnection;
  }

   /** 
   * This method updates the connection, and the resulting
   * top level module for the connection. This method is 

   * called automatically for application using a
   * {@link com.gensym.shell.util.ConnectionManager}. 
   * Applications using a single connection, have no need to call
   * this method. Use the {@link #setConnection} method instead.
   */

  @Override
  public void currentConnectionChanged(ContextChangedEvent e){
    setConnection(e.getConnection());
  }


}






