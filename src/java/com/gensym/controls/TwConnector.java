/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TwConnector.java
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.controls;

import java.util.Vector;
import java.util.Enumeration;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Connector;
import com.gensym.jgi.G2Connection;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2CommunicationErrorEvent;
import com.gensym.ntw.TwConnectionListener;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.jgi.ConnectionNotAvailableException;
import com.gensym.ntw.TwGateway;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.ntw.LoginRequest;
import com.gensym.ntw.TwConnectionAdapter;
import com.gensym.util.*;
import com.gensym.irm.IconRenderingManager;
import com.gensym.classes.Item;
import com.gensym.classes.UserMenuChoice;
import com.gensym.classes.Kb;
import com.gensym.ntw.WorkspaceShowingListener;
import com.gensym.ntw.TwConnection;

import com.gensym.dlgruntime.DialogManager;

/**
 * A Telewindows Connector Bean is to be used in environments where the
 * static method <code>TwGateway.openConnection()</code>
 * in TwGateway cannot be called.
 * In order to use this class, the values for all the
 * relevant properties specifying how to make the connection
 * should be filled in and then createConnection should
 * be called.
 * <p>
 * NOTE: the userPassword is transient for security reasons, so
 * <code>setUserPassword</code> must be called at runtime before
 * connecting to a secure G2.
 *
 * @version 1.0 20  Apr 1998
 *
 * @author M.Gribble
 */

public class TwConnector extends G2Connector {

  static final long serialVersionUID = -6258659757520916780L;

  private Symbol userMode;
  private Symbol userName;
  private transient Symbol userPassword;
  /**
   * @undocumented
   */
  protected G2ConnectionListener internalConnectionListener;

  public TwConnector () {
    super();
    gsiInterfaceName = "TW-CONNECTOR-BEAN-INTERFACE";
    xnClass    = "com.gensym.ntw.TwGateway";
    intfClass  = "UI-CLIENT-INTERFACE";
    setSharable(false);
    setForceNew(true);
  }

  private void createConnection (TwConnectionInfo xnInfo,
				 LoginRequest loginRequest) throws G2AccessException {
    G2ConnectionEvent initEvent = null;
    G2CommunicationErrorEvent errorEvent = null;
    closePrivateConnection();
    //try {
      TwGateway twxn = (TwGateway) TwGateway.openConnection (xnInfo);
      //System.out.print ("" + twxn +  " connected. Logging in with default values...");
      setXn (twxn);
      if (twxn instanceof TwGateway)
	startConnectionListening(twxn, getConnection());
      if (!twxn.isLoggedIn())
	twxn.login (loginRequest);
      //System.out.println (" Done!");

      initEvent = new G2ConnectionEvent(xn, 0, getRemoteProcessInitString (), false);
	
      /*} catch (G2AccessException g2aie) {
      Trace.exception (g2aie);
      Object source = (xn == null ? (Object)this : xn);
      errorEvent = new G2CommunicationErrorEvent(source, 0, 0, g2aie.getMessage());
    }*/

    // This is a hack until we can work out a way of listening for connection events
    // created from getOrMakeConnection
    synchronized (connectionListenersMonitor) {
      if (xn != null && connectionListeners != null) {
		for (Enumeration e = connectionListeners.elements(); e.hasMoreElements();) {
		  G2ConnectionListener listener = (G2ConnectionListener)e.nextElement(); 
		  if (errorEvent != null) 
		    listener.communicationError(errorEvent);
		  else
		    listener.g2ConnectionInitialized(initEvent);
		}
      }
    }
  }    


  /**
   * Creates a connection to G2 with the current set of attributes, then
   * logs into G2.
   * Calls <code>closePrivateConnection(false)</code> before opening the
   * new connection.
   * <p>
   * NOTE: The user password is not persistent, so it will have to be
   * set at runtime before connecting to a secure G2.
   * @see #setUserPassword(String)
   * @see com.gensym.jgi.G2Connector#closePrivateConnection
   */
  @Override
  public void createConnection () throws G2AccessException {
    TwConnectionInfo xnInfo =
      new TwConnectionInfo (normalizeForVB (getBrokerURL ()),
			    normalizeForVB (getLogicalName ()),
			    normalizeForVB (getHost ()),
			    normalizeForVB (getPort ()),
			    normalizeForVB (getConnectionClassName ()),
			    normalizeForVB (getGsiInterfaceClassName ()),
			    normalizeForVB (getGsiInterfaceName()),
			    null,
			    new Boolean (isPermanent ()),
			    normalizeForVB (getRemoteProcessInitString()),
			    isForceNew (), isSharable ());
    LoginRequest loginRequest =
      new LoginRequest(userMode, userName, userPassword);
    createConnection(xnInfo, loginRequest);
  }

  private Vector workspaceShowingListeners = new Vector();

  /**
   * @undocumented
   */
  @Override
  protected synchronized void addAllListeners() {
    //super.addAllListeners();
    if (xn == null || connectionListeners == null) return;
    //System.out.println ("Adding " + connectionListeners.size () + " TwCxn/G2Cxn listeners");
    for (Enumeration e = connectionListeners.elements(); e.hasMoreElements();) {
      G2ConnectionListener listener = (G2ConnectionListener)e.nextElement(); 
      if (listener instanceof TwConnectionListener)
	((TwConnection)xn).addTwConnectionListener ((TwConnectionListener)listener);
      else
	xn.addG2ConnectionListener(listener);
    }
    TwConnection txn = (TwConnection)_getConnection(); 
    if (txn == null || workspaceShowingListeners == null) return;
    //System.out.println ("Adding " + workspaceShowingListeners.size () + " WkspShowing listeners");
    for (Enumeration e = workspaceShowingListeners.elements(); e.hasMoreElements();) {
      WorkspaceShowingListener listener = (WorkspaceShowingListener)e.nextElement();
      try {
	txn.addWorkspaceShowingListener(listener);
      } catch (G2AccessException E) { throw new RuntimeException("G2AccessException:" + E.getMessage()); }
    }
  }

  /**
   * @undocumented
   */
  @Override
  protected synchronized void removeAllListeners() {
    //super.removeAllListeners();
    if (xn == null || connectionListeners == null) return;
    for (Enumeration e = connectionListeners.elements(); e.hasMoreElements();) {
      G2ConnectionListener listener = (G2ConnectionListener)e.nextElement(); 
      if (listener instanceof TwConnectionListener)
	((TwConnection)xn).removeTwConnectionListener ((TwConnectionListener)listener);
      else
	xn.removeG2ConnectionListener(listener);
    }
    TwConnection txn = (TwConnection)_getConnection();
    if (txn == null || workspaceShowingListeners == null) return;
    for (Enumeration e = workspaceShowingListeners.elements(); e.hasMoreElements();) {
      WorkspaceShowingListener listener = (WorkspaceShowingListener)e.nextElement(); 
      try {
	txn.removeWorkspaceShowingListener(listener);
      } catch (G2AccessException E) { throw new RuntimeException("G2AccessException:" + E.getMessage()); }
    }
  }

  private void startConnectionListening(G2Connection newConnection,
					  G2Connection oldConnection) {
    if (newConnection != null && newConnection.equals(oldConnection))
      return;

    if (oldConnection != null && internalConnectionListener != null)
      oldConnection.removeG2ConnectionListener(internalConnectionListener);

    if (internalConnectionListener == null) {
      internalConnectionListener = makeG2ConnectionListener();
    }

    newConnection.addG2ConnectionListener(internalConnectionListener);
  }

  private G2ConnectionListener makeG2ConnectionListener() {
    return new TwConnectionAdapter() {
      @Override
      public void userModeChanged(TwConnectionEvent e) {
	TwConnector.this.userMode = e.getUserMode();
      }
    };
  }    

  /**
   * Add a WorkspaceShowingListener, who will be informed of any WorkspaceShowing events for
   * a G2 connection.
   * @see com.gensym.ntw.TwGateway#addWorkspaceShowingListener
   */
  public void addWorkspaceShowingListener(WorkspaceShowingListener listener) throws G2AccessException { 
    synchronized(connectionListenersMonitor) {
      if (workspaceShowingListeners == null) workspaceShowingListeners = new Vector();
    }
    workspaceShowingListeners.addElement(listener);
    try {
      TwConnection txn = (TwConnection)_getConnection(); 
      txn.addWorkspaceShowingListener(listener);
    } catch (ConnectionNotAvailableException e) {}
  }

  /**
   * Remove a WorkspaceShowingListener, who was previously listening for WorkspaceShowing
   * events.
   * @see com.gensym.ntw.TwGateway#removeWorkspaceShowingListener
   */
  public void removeWorkspaceShowingListener(WorkspaceShowingListener listener) throws G2AccessException {
    synchronized(connectionListenersMonitor) {
      if (workspaceShowingListeners == null) workspaceShowingListeners = new Vector();
    }
    workspaceShowingListeners.removeElement(listener);
    try {
      TwConnection txn = (TwConnection)_getConnection();
      txn.removeWorkspaceShowingListener(listener);
    } catch (ConnectionNotAvailableException e) {}
  }

  // These deemed dangerous to change for a TwConnection.
  /**
   * Specifies what class will be created by the underlying
   * call to <code>G2Gateway.getOrMakeConnection</code>. Care should be
   * taken in setting this to anything other than "com.gensym.jgi.G2Gateway"
   * or "com.gensym.ntw.TwGateway", particularly if there is a chance that
   * the application could be run in three-tier mode.
   */
  @Override
  public void setConnectionClassName (String newXnClass) {
    super.setConnectionClassName (newXnClass);
  }

  @Override
  public void setGsiInterfaceClassName (String newIntfClass) {
    super.setGsiInterfaceClassName (newIntfClass);
  }

  /**
   * @deprecated
   * @undocumented
   */
  public Structure getDialog (Item itm, Symbol userMode, Structure locale) throws G2AccessException {
    return ((TwConnection)_getConnection()).getDialog(itm, userMode, locale);
  }

  /**
   * @see com.gensym.ntw.TwGateway#createItem
   */
  public Item createItem (Symbol className) throws G2AccessException {
    return ((TwConnection)_getConnection()).createItem(className);
  }

  /** Sets the user mode of the session in G2. Affects the userMode
   * of the current connection to G2, if there is one,
   * and this mode will be used in the next connection to G2.
   * This String will be interned as a <code>Symbol</code>, but it will
   * <b>not</b> be automatically uppercased.
   * @throws com.gensym.ntw.InvalidUserModeException if the user mode
   * is rejected by G2.
   */
  public void setUserMode (String newUserMode) throws G2AccessException {
    TwConnection cnxn = (TwConnection)getConnection();
    if (newUserMode == null) {
      userMode = null;
      return;			// Dont set mode on active Xn to null
    }
    Symbol newUserModeSymbol = Symbol.intern(newUserMode);
    if (cnxn != null)
      cnxn.setUserMode(newUserModeSymbol);
    userMode = newUserModeSymbol;
  }

  /**
   * Returns the userMode of the actual connection to G2. If there is
   * no current connection, it will return the last known value of the
   * last connection to G2, or if there has never been a connection to G2
   * it will return the last value set by <code>setUserMode</code>.
   * @see com.gensym.ntw.LoginRequest#getUserMode
   */
  public String getUserMode () throws G2AccessException {
    TwConnection cnxn = (TwConnection)getConnection();
    Symbol userModeSymbol = cnxn == null ? userMode : cnxn.getUserMode();
    return (userModeSymbol == null ? null :
	    userModeSymbol.getPrintValue());
  }

  /** Sets what userName will be used for the next connection
   * to G2. This will be translated into a <code>Symbol</code>,
   * before it is sent to G2 but will not be automatically uppercased.
   * <p>
   * NOTE: This does <b>not</b> affect the userName of the current connection.
   * to G2.
   */
  public void setUserName(String newUserName) {
    userName = (newUserName != null ?
		Symbol.intern(newUserName) : null);
		
  }

  /**
   * The user name.
   * @returns the user name that will be used for the next call to
   * createConnection
   * @see com.gensym.ntw.LoginRequest#getUserName
   */
  public String getUserName() {
    return userName == null ? null : userName.getPrintValue();
  }

  /** Sets what user password will be used for the next connection
   * to G2.
   * <p>
   * NOTE: This is not a password administration tool.
   * <p>
   * SECURITY NOTE: For security reasons, this field is transient. In other
   * words, the password will not be saved out to file when this bean is
   * stored. Therefore it will have to be set at runtime when connecting to
   * a secure g2.
   * @see com.gensym.ntw.LoginRequest
   */
  public void setUserPassword(String newPassword) {
    userPassword = (newPassword != null ?
		    Symbol.intern(newPassword) : null);
  }

  /**
   * @see com.gensym.ntw.TwGateway#getNamedWorkspaces
   */
  public Sequence getNamedWorkspaces () throws G2AccessException {
    return ((TwConnection)_getConnection()).getNamedWorkspaces();
  }

  /**
   * @see com.gensym.ntw.TwGateway#getFormatInfo
   * @undocumented
   */
  public Structure getFormatInfo(Symbol formatName) throws G2AccessException {
    return ((TwConnection)_getConnection()).getFormatInfo(formatName);
  }

  /**
   * @undocumented
   */
  public IconRenderingManager getIconManager () {
    return ((TwConnection)_getConnection()).getIconManager();
  }

  /**
   * @undocumented
   */
  public Structure subscribeToModules() throws G2AccessException {
    return ((TwConnection)_getConnection()).subscribeToModules();
  }

  /**
   * @undocumented
   */
  public void unsubscribeToModules() throws G2AccessException {
    ((TwConnection)_getConnection()).unsubscribeToModules();
  }

  /**
   * @see com.gensym.ntw.TwGateway#getDialogManager
   */
  public DialogManager getDialogManager () {
    return ((TwConnection)_getConnection()).getDialogManager();
  }

  /**
   * @see com.gensym.ntw.TwGateway#getKb
   */
  public Kb getKb () {
    return ((TwConnection)_getConnection()).getKb();
  }
       
  /**
   * @see com.gensym.ntw.TwGateway#getUserMenuChoice
   */
  public UserMenuChoice getUserMenuChoice(Symbol label,
					  Symbol applicableClass)
       throws G2AccessException {
    return ((TwConnection)_getConnection()).getUserMenuChoice(label, applicableClass);
  }

  private static String normalizeForVB(String in) {
    if (in == null)
      return null;

    in = in.trim();
    if (in.length() == 0) 
      return null;
    else
      return in;
  }



  /**
   * Add a TwConnectionListener, who will be informed of any TwConnection events for
   * a Tw connection.
   * @see com.gensym.ntw.TwGateway#addTwConnectionListener
   */
  public void addTwConnectionListener(TwConnectionListener listener) {
    synchronized(connectionListenersMonitor) {
      if (connectionListeners == null) 
    	  connectionListeners = new Vector();
      connectionListeners.addElement(listener);
    }
    
    if (xn != null)
      ((TwConnection)xn).addTwConnectionListener(listener);
  }

  
  /**
   * Remove a TwConnectionListener, who was previously listening for TwConnection
   * events.
   * @see com.gensym.ntw.TwGateway#removeTwConnectionListener
   */
  public void removeTwConnectionListener(TwConnectionListener listener) {
    synchronized(connectionListenersMonitor) {
      if (connectionListeners == null) 
    	  connectionListeners = new Vector();
      connectionListeners.removeElement(listener);
    }
   
    if (xn != null)
      ((TwConnection)xn).removeTwConnectionListener(listener);
  }

  /**
   * @undocumented For COM use only
   */
  public Object callRPCForVB (Symbol g2_procedure_name, 
			       Sequence argsSeq, 
			       int timeout)
       throws G2AccessException {
	 return callRPC (g2_procedure_name, argsSeq, timeout);
  }

  /**
   * @undocumented For COM use only
   */
  public void startRPCForVB (Symbol g2_procedure_name, 
			     Sequence argsSeq) {
    startRPC (g2_procedure_name, argsSeq);
  }

  /**
   * @undocumented Needed for method dispatch in VB to work around
   * Plug-in bug of not delivering exceptions
   */
  public Object getThis () {
    return this;
  }

}
