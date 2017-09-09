/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SwitchConnectionCommand.java
 *
 */
package com.gensym.shell.commands;

import java.util.Vector;
import java.util.Hashtable;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2AccessInitiationException;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwGateway;
import com.gensym.message.Resource;
import com.gensym.shell.util.*;
import com.gensym.ui.AbstractStructuredCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.ui.SubCommandInformation;
import com.gensym.ui.StructuredCommandInformation;
import com.gensym.message.Trace;

/** 
 * Command to switch
 * between open G2 connections.  This command may only be used in multiple 
 * connection applications and requires the use of the ConnectionManager 
 * for maintaining the open connections to G2.
 */
public final class SwitchConnectionCommand extends AbstractStructuredCommand {
  public static final String TW_SWITCH_CONNECTION = "TwSwitchConnection";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";
  
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");
  private Resource shortBundle = Resource.getBundle("com/gensym/shell/commands/CommandShortResource");

  private Hashtable connectionTable;//maps cxn key (hashcode) to TwAccess object
  private Vector orderedConnectionList;

  private ConnectionManager connectionMgr;
  private TwAccess currentConnection;

  private ContextChangedListener contextChangedListener;
  private G2ConnectionAdapter closingListener;

  public SwitchConnectionCommand(ConnectionManager connectionMgr){
    super (new CommandInformation[]{});

    //initialize properties
    this.connectionMgr = connectionMgr;
    currentConnection = connectionMgr.getCurrentConnection();
    connectionTable = new Hashtable();
    contextChangedListener = new ContextChangedAdapter();
    closingListener = new G2CloseAdapter();
    orderedConnectionList = new Vector();

    //hook-up listeners
    connectionMgr.addContextChangedListener(contextChangedListener);

    TwAccess[] openConnections = connectionMgr.getOpenConnections();
    for (int i=0; i<openConnections.length; i++){
      TwAccess connection = openConnections[i];
      Integer code = new Integer(connection.hashCode());
      orderedConnectionList.addElement(code.toString());
      connectionTable.put(code.toString(), connection);
      connection.addG2ConnectionListener(closingListener);
    }

    //define command structure
    setStructuredKeys(new CommandInformation[]{createSwitchSubCommand()});

    //set availability
    if (connectionMgr.getCurrentConnection() == null){
      setAvailable(TW_SWITCH_CONNECTION, false);
    }
  }

  private SubCommandInformation createSwitchSubCommand(){
    Vector list;
    synchronized(this) {list = (Vector)orderedConnectionList.clone();}
    CommandInformation[] connections = new CommandInformation[list.size()];
    for (int i=0; i<list.size(); i++){
      String code = (String)list.elementAt(i);
      TwAccess connection = (TwAccess)connectionTable.get(code);
      if (connection != null){
	String connectionName = connection.toShortString();
	Boolean state = Boolean.FALSE;
	if (connection.equals(currentConnection)) state = Boolean.TRUE;
	connections[i] = 
	  new CommandInformation(code, true, null, null, null, null, 
				 state, true, (i+1)+" "+connectionName, connectionName, null, null,
				 null, new Character((char)('0' + i + 1)), null);
      }
    }
    boolean available = list.size() > 0;
    return new SubCommandInformation(TW_SWITCH_CONNECTION, available, shortResource, 
				longResource, null, null, null, mnemonicResource, connections);
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey))
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", cmdKey));

    TwAccess connection = (TwAccess)connectionTable.get(cmdKey);
      if (connection != null){
	connectionMgr.setCurrentConnection(connection);
	Integer code = new Integer(connection.hashCode());
	String key = code.toString();
	setState(key, Boolean.FALSE);
	setState(key, Boolean.TRUE);
      }
  }

  /** 
   *  Sets the availability of command and notifies listeners if availability
   *  has changed.
   */
  @Override
  protected void setAvailable(String key, boolean available){
    super.setAvailable(key, available);
  }

  @Override
  protected void setState(String key, Boolean state){
    if (orderedConnectionList.contains(key))
      super.setState(key, state);
  }

  @Override
  protected void setStructuredKeys(StructuredCommandInformation[] structure){
    super.setStructuredKeys(structure);
  }

  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      TwAccess newCurrentConnection = e.getConnection();
      TwAccess previousConnection = currentConnection;
      currentConnection = newCurrentConnection;
      if (previousConnection != null)
	setState(new Integer(previousConnection.hashCode()).toString(), Boolean.FALSE);
      if (currentConnection == null){
	setAvailable(TW_SWITCH_CONNECTION, false);
      }
      else{
	Integer code = new Integer(currentConnection.hashCode());
	String key = code.toString();
	if (connectionTable.get(key) == null){//new connection
	  setAvailable(TW_SWITCH_CONNECTION, true);
	  orderedConnectionList.addElement(key);
	  connectionTable.put(key, currentConnection);
	  currentConnection.addG2ConnectionListener(closingListener);
	  setStructuredKeys(new CommandInformation[]{createSwitchSubCommand()});
	}
	setState(key, Boolean.TRUE);
      }
    } 
  }
  
  class G2CloseAdapter extends G2ConnectionAdapter{
    @Override
    public void g2ConnectionClosed(G2ConnectionEvent e){
      TwAccess connection = (TwAccess)e.getSource();
      connection.removeG2ConnectionListener(this);
      Integer code = new Integer(connection.hashCode());
      String key = code.toString();
      orderedConnectionList.removeElement(key);
      connectionTable.remove(key);
      setStructuredKeys(new CommandInformation[]{createSwitchSubCommand()});
      if (orderedConnectionList.size() == 0){
	setAvailable(TW_SWITCH_CONNECTION, false);
      }
    }
  }
}




