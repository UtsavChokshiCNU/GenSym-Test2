/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ConnectionManager.java
 *
 */
package com.gensym.shell.util;

import java.util.Vector;
import java.util.Enumeration;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2AccessInitiationException;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.jgi.G2ConnectionAdapter;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.ntw.TwConnectionInfo;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwGateway;

/**
 * A class that manages open connections to G2. It is used
 * by applications that open multiple connections to G2s.
 * It maintains a notion of a "current" connection, and notifies
 * listeners when the current context changes. <p>
 *
 * UI clients that allow the application to connect to more
 * than one G2 should need to create one and only one instance of
 * a ConnectionManager. If a ConnectionManager is present, applications
 * should always use <code>openConnection</code> on this
 * class rather than getting a connection by calling
 * <code>TwGateway.openConnection</code> directly.
 *
 * @author ch
 * @version 1.0 
 *
 */
public class ConnectionManager {
  private Vector openConnections;
  private TwAccess currentConnection;
  private Vector contextListeners;
  private G2ConnectionListener cxnAdapter;

  /**
   * Creates a new ConnectionManager. Callers need create
   * only one instance of this class per application.
   */
  public ConnectionManager() {
    openConnections = new Vector();
    contextListeners = new Vector();
    cxnAdapter = new ConnectionAdapter ();
  }

  /**
   * Opens a new connection and sets it as the current connection
   * @param url the URL of the broker from which to request a connection
   * @param host the hostname or address of the machine on which G2 is running
   * @param port the port number at which G2 is listening for connection requests
   * @return a TwConnection connected to the specified G2
   * @exception ConnectionTimedOutException if the connection times out
   * @exception G2AccessInitiationException if a problem occurs making intial
   *  connection to G2
   * @exception G2AccessException if any other communication error occurs while
   *    establishing a connection.
   */
  public TwAccess openConnection (String url, String host, String port)
  throws ConnectionTimedOutException, G2AccessInitiationException, G2AccessException{
    return openConnection (new TwConnectionInfo (url, host, port));
  }


  /**
   * Opens a new connection and sets it as the current connection
   * @parm connection a TwConnectionInfo object that encapsulates the
   *    request to open a connection
   * @return a TwConnection connected to the specified G2
   * @exception ConnectionTimedOutException if the connection times out
   * @exception G2AccessException if any other communication error occurs while
   *    establishing a connection.
   */
  public TwAccess openConnection(TwConnectionInfo connectionInfo)
  throws ConnectionTimedOutException, G2AccessInitiationException, G2AccessException{
    TwAccess newConnection = TwGateway.openConnection (connectionInfo);
    if (!(openConnections.contains(newConnection))){
      openConnections.addElement(newConnection);
      //ContextChangedEvent e = new ContextChangedEvent(this, newConnection);
      newConnection.addG2ConnectionListener(cxnAdapter);
      setNewCurrentConnection(newConnection);
    } else
      setCurrentConnection(newConnection);
    return newConnection;
  }
    
  /**
   * Returns the current connection
   * @return the current TwConnection
   */
  public TwAccess getCurrentConnection() {
    return currentConnection;
  }

  /**
   * Return true if there is any open connection, otherwise
   * false
   * @return boolean
   * @author FY - 01/18/00
   */
   public boolean hasConnections() {
     return openConnections.size() != 0;
   }

  private void setCurrentConnection0(TwAccess connection) {
    if ((connection != null) && (!connection.isAlive())){
      openConnections.removeElement(connection);
      connection = null;
      while (openConnections.size() > 0){
	connection = (TwAccess)openConnections.firstElement();
	if (!connection.isAlive()){
	  openConnections.removeElement(connection);
	  connection = null;
	}
	else break;
      }
    }
    setCurrentConnection(connection);
  }

  /**
   * Ensures that the specified connection is made current. If this
   * was not previously the current connection, all listeners are
   * notified of this event.
   * @see ContextChangedListener
   * @connection the TwConnection to be made current
   */
  public void setCurrentConnection(TwAccess connection) {
    //System.out.println("old cxn:"+currentConnection+" new cxn:"+connection);
    if ((connection != null) && (!connection.isAlive())){
      throw new IllegalArgumentException("Connection is not alive");
    }
    if ((currentConnection == null)&&(connection == null)) return;
    if ((currentConnection != null)&&(currentConnection.equals(connection))) return;
    else {	  
      ContextChangedEvent e = new ContextChangedEvent(this, connection, false);
      currentConnection = connection;
      notifyCurrentConnectionChanged(e);
    }
  }

  private void setNewCurrentConnection(TwAccess connection) {
    if ((currentConnection == null)&&(connection == null)) return;
    if ((currentConnection != null)&&(currentConnection.equals(connection))) return;
    else {	  
      ContextChangedEvent e = new ContextChangedEvent(this, connection, true);
      currentConnection = connection;
      notifyCurrentConnectionChanged(e);
    }
  }

  /**
   * Returns an array of currently managed connections 
   * @return an array of the current open TwConnections
   */
  public TwAccess[] getOpenConnections(){
    TwAccess[] cxns = new TwAccess[openConnections.size()];
    openConnections.copyInto(cxns);
    return cxns;
  }

  /**
   * Adds the specified context changed listener to receive context
   * changed events from this ConnectionManager
   * @param l the context changed listener
   */
  public synchronized void addContextChangedListener(ContextChangedListener l){
    if (!(contextListeners.contains(l)))
      contextListeners.addElement(l);
  }

  /**
   * Removes the specified context changed listener so that it no
   * longer receives context changed events from this ConnectionManager.
   * @param l the context changed listener
   */
  public synchronized void removeContextChangedListener(ContextChangedListener l){
    if (contextListeners.contains(l))
      contextListeners.removeElement(l);
  }
  
  /**
   * Notifies all listeners of the change in the current context.
   * Subclasses should override this to get specialized behaviour
   * when this event occurs.
   * @param e the context changed event containing the information
   *   about the change
   */
  protected void notifyCurrentConnectionChanged(ContextChangedEvent e) {
    if (contextListeners.size() < 1) return;
    Vector l;
    synchronized(this) {l = (Vector)contextListeners.clone();}
    Enumeration ccl = l.elements();
    while (ccl.hasMoreElements())
      ((ContextChangedListener)ccl.nextElement()).currentConnectionChanged(e);
  }

  /**
   * Private adapter class to listen for connection
   * closing events so that we can maintain state
   * correctly
   */
  class ConnectionAdapter extends G2ConnectionAdapter {
    /**
     * The only event we are interested in
     */
    @Override
    public void g2ConnectionClosed (G2ConnectionEvent event) {
      TwAccess connection = (TwAccess)event.getSource();
      //System.out.println ("ConnectionManager Adapter notified of Cxn Closing = " + connection);
      if (openConnections.contains(connection)) 
	openConnections.removeElement(connection);
      
      if (openConnections.size() == 0)
	setCurrentConnection(null);
      else if (openConnections.size() == 1) 
	setCurrentConnection0((TwAccess)openConnections.firstElement());
      else {
	// what about displaying a SelectionDialog with the available
	// connections for the user to choose which should become the
	// currentConnection?
	setCurrentConnection0((TwAccess)openConnections.firstElement());
      }
    }
  }
}



