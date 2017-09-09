package com.gensym.controls;

import java.util.EventListener;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.jgi.G2Access;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Gateway;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.LoginRequest;
import com.gensym.jgi.ConnectionTimedOutException;
import com.gensym.classes.Item;
import com.gensym.message.Resource;
import com.gensym.message.MessageEvent;
import com.gensym.message.MessageKey;
import com.gensym.message.Message;
import com.gensym.message.Trace;
import com.gensym.util.Symbol;

/** A utility bean for fetching an Item from G2. Only <code>retrieveItem</code>
 * will cause an actual call to G2 to retrieve an item. The
 * constructors and property methods are designed to set up the internal data
 * in preparation for the next actual call to G2. If an ItemRetriever reference
 * is shared among several objects it is possible for one of those objects to
 * change the name (for example) of the item to be retrieved before the item
 * is retrieved, so users of this class need to control access to any instances
 * they are using.
 * <p>
 * If a reference is being shared, one way to ensure that the item being
 * retrieved has the expected parameters is to use retrieveItem:
 * <blockquote>
 * <pre>
 *  synchronized(retriever) { 
 *          retriever.setItemName(name); 
 *          retriever.setItemClassName(className); 
 *          retriever.setConnectionInfo(info);
 *          // synchronous
 *          Item item = retriever.retrieveItem(); 
 *        }
 * </pre>
 * </blockquote>
 * Uses g2-get-unique-named-item to retrieve the item on the G2 side.
 * <p>
 * This class automatically calls .trim() on every string before it
 * sends the string to G2, but leaves the actual property unchanged.
 * Strings that are empty after trimming are converted to <code>null</code>
 * before being sent to G2. This is done to work around bugs in
 * VisualBasic.
 *
 * @author rpenny
 * @version 1.11
 * @see com.gensym.jgi.G2ConnectionInfo
 */
public class ItemRetriever implements java.io.Serializable {

  static final long serialVersionUID = -1222483474008308785L;
  private static Resource i18n =
    Resource.getBundle("com.gensym.controls.Messages");
  private static final MessageKey messageKey =
  Message.registerMessageKey("com.gensym.util", ItemRetriever.class);
  private static final String DEFAULT_ITEM_CLASS_NAME = "ITEM";
  private G2ConnectionInfo connectionInfo;
  private String itemName;
  private String itemClassName;
  private String hostName = "localhost", port = "1111";
  private String brokerURL;
  private String connectionClassName = "com.gensym.ntw.TwGateway";
  private String gsiInterfaceClassName = "UI-CLIENT-INTERFACE";
  private transient G2Access connection;
  private transient Item item;

  // the following three slots valid for TwAccesss only
  private Symbol userMode;
  private Symbol userName;
  private transient Symbol userPassword;

  private ItemRetrievalListener listener;

  /**
   * Creates an empty <code>ItemRetriever</code> that will need to
   * have at least <code>setItemName</code> called on it before
   * it can retrieve an <code>Item</code>.
   */
  public ItemRetriever() {
  }

  /** Enough information to connect to a G2 and retrieve a Unique Named Item.
   * If the <code>itemClassName/itemName</code> combination is not unique
   * in the specified G2, the retrieval will fail.
   * @param connectionInfo how to connect to G2
   * @param itemClassName the <code>Item</code> retrieved will be an instance
   * of this class. Defaults to "ITEM" if <code>null</code>.
   * @param itemName the name of the <code>Item</code> to be retrieved.
   */
  public ItemRetriever (G2ConnectionInfo connectionInfo,
			String itemClassName,
			String itemName) {
    this.connectionInfo = connectionInfo;
    this.itemName = itemName;
    this.itemClassName = itemClassName;
  }

  private void resetConnection()
  {
    item = null;
    connectionInfo = null;
    connection = null;
  }
  
  private void initiateConnection()
  throws G2AccessException
  {
    if (connectionInfo == null)
      connectionInfo =
	new G2ConnectionInfo (normalizeForVB(brokerURL),
			      normalizeForVB(hostName),
			      normalizeForVB(port),
			      normalizeForVB(connectionClassName),
			      normalizeForVB(gsiInterfaceClassName));

   try {
     if (connection == null) {
       connection = G2Gateway.getOrMakeConnection(connectionInfo);
       if (connection instanceof TwAccess &&
	   !((TwAccess)connection).isLoggedIn()) {
	 LoginRequest request = new LoginRequest(userMode, userName,
						 userPassword);
	 ((TwAccess)connection).login (request);
       }
     }
    } catch (ConnectionTimedOutException e) {
      throw new G2AccessException(e);
    }
  }

  private void dispatchRetrievalFailure(G2AccessException e, String detail) {
    if (listener != null) {
      MessageEvent messageEvent =
	new MessageEvent(1, messageKey, i18n,
			 "ItemRetriever_retrievalFailed",
			 new Object[]
			 {connectionInfo, itemName, getItemClassName(), detail});

      listener.itemRetrievalFailed(new ItemRetrievalEvent
				   (this, e, messageEvent));
    }
  }

  private void resolveItem() throws G2AccessException {
    if (itemName == null) {
      dispatchRetrievalFailure(null,
			       i18n.getString("ItemRetriever_noNameSpecified"));
      return;
    }
      
    try {
      initiateConnection();
      item = (Item)connection.getUniqueNamedItem
	(Symbol.intern(normalizeForVB(getItemClassName())),
	 Symbol.intern(normalizeForVB(itemName)));
    } catch (G2AccessException e) {
      Trace.exception(e);
      dispatchRetrievalFailure(e, e.getMessage());
      throw e;
    }

    if (listener != null) {
      listener.itemRetrieved(new ItemRetrievalEvent(this, item));
    }
  }

  /** Synchronously calls G2 to retrieve the unique named item described
   * by the retriever's current connectionInfo, itemName, and itemClassName.
   * If the item has already been retrieved, it returns the item immediately.
   * Also notifies any listeners if the item had not been retrieved
   * previously.
   *
   * @returns the Item from G2 as specified by this ItemRetriever.
   * @exception G2AccessException If any G2AccessExceptions are thrown
   * by <code>G2Gateway</code> while
   * either connecting to the specified G2 or while retrieving the
   * <code>Item</code>, they will be thrown here.
   */
  public synchronized Item retrieveItem() throws G2AccessException {
    if (item != null)
      return item;

    resolveItem();

    return item;
  }

  /**
   * Method to do the retrieval but not return it.
   * Special hack for VB, needs review -vkp, 3/17/98
   * @exception G2AccessException for the same reasons as in
   * <code>retrieveItem</code>
   * @see #retrieveItem
   * @undocumented
   */
  public void retrieveItemForVB () throws G2AccessException {
    retrieveItem ();
  }

  /** Adds <code>l</code> to the list of listeners to this
   * <code>ItemRetriever</code>. If the <code>ItemRetriever</code>
   * already contains
   * an <code>Item</code>, the <code>itemRetrieved</code> method on
   * <code>l</code> will be called back from within this method.
   *
   * @param l the listener to add
   */
  public synchronized void addItemRetrievalListener(ItemRetrievalListener l) {

    listener = ControlsEventMulticaster.add(listener, l);

    if (item != null)
      l.itemRetrieved(new ItemRetrievalEvent(this, item));
  }

  /** Remove the listener <code>l</code> from the list of listeners.
   * @param l the listener to remove
   */
  public synchronized void removeItemRetrievalListener(ItemRetrievalListener l) {
    listener = ControlsEventMulticaster.remove(listener, l);
  }

  /**
   * Sets the information about how to connect to G2 to retrieve the
   * next <code>Item</code>.
   * If the new info doesn't <code>match</code> the connection info
   * of the current connection, replace the current connection info
   * and nullify the item and connection for this retriever.
   * <p>
   * Resets the values of brokerURL, hostName, and port to match
   * the brokerURL, hostName, and portName of the new <code>info</code>.
   * <p>
   * NOTE: the new item is not retrieved until <code>retrieveItem</code>
   * is called on this retriever.
   *
   * @param info the new specifics of how to connect to a G2 to
   * retrieve the next item.
   */
  public synchronized void setConnectionInfo(G2ConnectionInfo info) {
    if (info == null ||
	(connection != null &&
	 !info.matches(((G2Gateway)connection).getG2ConnectionInfo()))) {
      connection = null;
      item = null;
    }
    if (info != null) {
      setBrokerURL(info.getBrokerURL());
      setHost(info.getHost());
      setPort(info.getPort());
      setConnectionClassName(info.getConnectionClassName());
    }
    connectionInfo = info;
    
  }

  /** The information that will be used to connect to G2 the next time
   * the retriever performs a retrieval */
  public synchronized G2ConnectionInfo getConnectionInfo() {
    return connectionInfo;
  }

  /** Prepares the retriever to resolve to a new name */
  public synchronized void setItemName(String itemName) {
    if (this.itemName == null || !this.itemName.equals(itemName)) {
      item = null;
    }

    this.itemName = itemName;
  }

  /**
   * Returns the string for the URL to be used to connect to a
   * <code>G2RMIAccessBrokerImpl</code>.
   *
   * @returns a URL string if connecting in three-tier mode,
   * <code>null</code> otherwise
   * @see com.gensym.jgi.G2ConnectionInfo
   */
  public synchronized String getBrokerURL () {
    return brokerURL;
  }

  /**
   * Also resets the connectionInfo.
   * @param brokerURL the URL string if connecting in three-tier mode,
   * or <code>null</code> if a two-tier connection is desired.
   *
   * @see com.gensym.jgi.G2ConnectionInfo
   * @see com.gensym.jgi.rmi.G2RMIAccessBrokerImpl
   */
  public synchronized void setBrokerURL (String brokerURL) {
    this.brokerURL = brokerURL;
    connectionInfo = null;
  }

  /**
   * The hostname for G2.
   * @see com.gensym.jgi.G2ConnectionInfo
   */
  public synchronized String getHost () {
    return hostName;
  }

  /**
   * Also resets the connectionInfo.
   * @see com.gensym.jgi.G2ConnectionInfo#getHost
   */
  public synchronized void setHost (String newHost) {
    hostName = newHost;
    resetConnection();
  }

  /**
   * The string representing the port number for connecting to G2
   * @see com.gensym.jgi.G2ConnectionInfo#getPort
   */
  public synchronized String getPort () {
    return port;
  }

  /**
   * The string representing the port number for connecting to G2.
   * Also resets the connectionInfo.
   * @see com.gensym.jgi.G2ConnectionInfo#getPort
   */
  public synchronized void setPort (String newPort) {
    port = newPort;
    resetConnection();
  }

  /**
   * Defaults to com.gensym.ntw.TwGateway.
   * @see com.gensym.jgi.G2ConnectionInfo#getConnectionClassName
   */
  public synchronized String getConnectionClassName () {
    if (connectionInfo != null) {
      return connectionInfo.getConnectionClassName();
    }
    return connectionClassName;
  }

  /**
   * The class of the connection in G2
   * Also resets the connectionInfo.
   * @see com.gensym.jgi.G2ConnectionInfo#getConnectionClassName
   */
  public synchronized void setConnectionClassName (String newName) {
    connectionClassName = newName;
    resetConnection();
  }

  /**
   * Defaults to UI-CIENT-INTERFACE
   * @see com.gensym.jgi.G2ConnectionInfo#getGsiInterfaceClassName
   */
  public synchronized String getGsiInterfaceClassName () {
    if (connectionInfo != null) {
      return connectionInfo.getGsiInterfaceClassName();
    }
    return gsiInterfaceClassName;
  }

  /**
   *
   * Also resets the connectionInfo.
   * @see com.gensym.jgi.G2ConnectionInfo#getGsiInterfaceClassName
   */
  public synchronized void setGsiInterfaceClassName (String newName) {
    gsiInterfaceClassName = newName;
    resetConnection();
  }

  /** Returns the name of the item that will be used the next time
   * the retriever performs a retrieval */
  public synchronized String getItemName() {
    return itemName;
  }

  /** Prepares the retriever to resolve to a new class name */
  public synchronized void setItemClassName(String itemClassName) {
    if (this.itemClassName == null ||
	!this.itemClassName.equals(itemClassName)) {
      item = null;
    }

    this.itemClassName = itemClassName;
  }

  /** Returns the class name of the item that will be used the next time
   * the retriever performs a retrieval.
   * @returns the class name that has been specified for this
   * <code>ItemRetriever</code>, or "ITEM" if none has been specified.
   */
  public synchronized String getItemClassName() {
    return itemClassName == null ? DEFAULT_ITEM_CLASS_NAME : itemClassName;
  }

  @Override
  public String toString() {
    return super.toString() + ": " + connectionInfo + "; name: " + itemName +
      "; class: " + itemClassName;
  }

  private static String normalizeForVB(String in) {
    //System.out.println("received \"" + in + "\"");
    if (in == null) {
      //System.out.println("actually null");
      return null;
    }

    in = in.trim();
    if (in.length() == 0) { // empty string
      //System.out.println("EmptyString");
      return null;
    } else {
      //System.out.println("AOK");
      return in;
    }
  }    
  /** Sets the user mode for the next item retrieval.
   * This String will be interned as a <code>Symbol</code>, but it will
   * <b>not</b> be automatically uppercased.
   * <p>
   * NOTE: This will not work unless the connection is a TwAccess.
   */
  public void setUserMode (String newUserMode) throws G2AccessException {
    Symbol newUserModeSymbol = Symbol.intern(newUserMode);
    if (connection instanceof TwAccess) {
      TwAccess cnxn = (TwAccess)connection;
      if (cnxn != null)
	cnxn.setUserMode(newUserModeSymbol);
    }
    userMode = newUserModeSymbol;
  }

  /**
   * Returns the user mode by which the next item will be retrieved.
   * <p>
   * NOTE: This will not work unless the connection is a TwAccess.
   */
  public String getUserMode () throws G2AccessException {
    if (connection != null && !(connection instanceof TwAccess))
      return null;
    
    TwAccess cnxn = (TwAccess)connection;
    Symbol userModeSymbol = cnxn == null ? userMode : cnxn.getUserMode();
    return (userModeSymbol == null ? null :
	    userModeSymbol.getPrintValue());
  }

  /** Sets what userName will be used for the next connection
   * to G2. This will be translated into a <code>Symbol</code>,
   * but will not be automatically uppercased.
   * <p>
   * NOTE: This does <b>not</b> affect the userName of the current connection.
   * to G2.
   * <p>
   * NOTE: This will not work unless the connection is a TwAccess.
   */
  public void setUserName(String newUserName) {
    userName = Symbol.intern(newUserName);
  }

  public String getUserName() {
    return userName == null ? null : userName.getPrintValue();
  }

  /** Sets what userPassword will be used for the next connection
   * to G2.
   * <p>
   * NOTE: This is not a password administration tool.
   * <p>
   * SECURITY NOTE: For security reasons, this field is transient. In other
   * words, the password will not be saved out to file when this bean is
   * stored. Therefore it will have to be set at runtime.
   * <p>
   * NOTE: This will not work unless the connection is a TwAccess.
   */
  public void setUserPassword(String newPassword) {
    userPassword = Symbol.intern(newPassword);
  }

}
    
