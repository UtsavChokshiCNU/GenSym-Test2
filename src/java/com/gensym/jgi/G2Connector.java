
package com.gensym.jgi;

import com.gensym.message.Trace;
import com.gensym.util.Symbol;
import com.gensym.util.Sequence;
import com.gensym.classes.Item;
import com.gensym.classes.G2Definition;
import java.util.Vector;
import java.util.Enumeration;
import java.lang.reflect.Method;
import java.awt.Component;
import java.awt.Toolkit;
import java.awt.Image;
import java.awt.Graphics;
import java.awt.Dimension;
import java.awt.Color;

/**
 * A G2Connector is a visual component Bean that provides the event and method interfaces of 
 * a G2Connection. This bean is to be used in builder environmennts where the
 * static getOrMakeConnection in G2Gateway cannot be called.
 * In order to use this class, the values for all the
 * relevant properties specifying how to make the connection
 * should be filled in and then <B>createConnection</B> should
 * be called. The "relevant properties" all having corresponding properties
 * in <code>G2ConnectionInfo</code>
 * @see com.gensym.jgi.G2Gateway
 * @see com.gensym.jgi.G2ConnectionInfo
 * @see #createConnection
 *
 */
public class G2Connector extends Component {

  /**
   * Allow evolution for serialized instances
   */
  static final long serialVersionUID = -6258659757520916607L;

  /**
   * Private fields
   */
  private String url        = null;
  private String logicalName     = null;
  private String host       = G2ConnectionInfo.DEFAULT_HOST;
  private String port       = G2ConnectionInfo.DEFAULT_PORT;
  private boolean isPerm    = true;
  private boolean shareable = true;
  private boolean forceNew  = false;
  private String remoteProcessInitString = "";
  /**
   * @undocumented
   */
  protected String gsiInterfaceName = "G2-CONNECTOR-BEAN-INTERFACE";
  /**
   * @undocumented
   */
  protected String xnClass    = G2Gateway.DEFAULT_TWO_TIER_CLASS_NAME;
  /**
   * @undocumented
   */
  protected String intfClass  = G2Gateway.DEFAULT_GSI_CLASS_NAME;

  protected final Object connectionListenersMonitor = new Object();
  /**
   * @undocumented
   */
  protected transient G2Connection xn;

  public G2Connector () {
    closingListener = new G2ConnectionClosingAdapter(this);
  }

  /**
   * Returns the URL for the broker to contact to make a connection
   * @see com.gensym.jgi.G2ConnectionInfo#getBrokerURL
   * @return the broker URL for the connection
   */
  public String getBrokerURL () {
    return url;
  }

  /** Sets the URL that will be used the next time an attempt is made to
   * make a connection. If the URL is non-null, then a third-tier connection
   * will be made.
   */
  public void setBrokerURL (String newURL) {
    url = newURL;
    reset ();
  }

  /**
   * Returns the logical-name of the connection to connect to
   * @return the name of the logical connection for the connection.
   * @see com.gensym.jgi.G2ConnectionInfo#getLogicalName
   */
  public String getLogicalName () {
    return logicalName;
  }

  /**
   * @see com.gensym.jgi.G2ConnectionInfo#getLogicalName
   */
  public void setLogicalName (String newLogicalName) {
    logicalName = newLogicalName;
    reset ();
  }

  /**
   * Returns the host to which to connect
   * @see com.gensym.jgi.G2ConnectionInfo#getHost
   * @return the host for the connection
   */
  public String getHost () {
    return host;
  }

  /** Sets the host name that will be used for the next connection.
   */
  public void setHost (String newHost) {
    host = newHost;
  }

  /**
   * Returns the port to which to connect
   * @see com.gensym.jgi.G2ConnectionInfo#getPort
   * @return the port for the connection
   */
  public String getPort () {
    return port;
  }

  /** Sets the port that will be used for the next connection.
   */
  public void setPort (String newPort) {
    port = newPort;
  }

  /**
   * Returns the G2Gateway class that will be created
   * @see com.gensym.jgi.G2ConnectionInfo#getConnectionClassName
   * @return the name of the Java <code>class</code> that will be created
   * for the connection. Should be com.gensym.jgi.G2Gateway or some subclass.
   * Must implement com.gensym.jgi.G2Connection.
   */
  public String getConnectionClassName() {
    return xnClass;
  }

  /**
   * Sets the name of the G2Gateway class that will be created
   * for createConnection. Should be com.gensym.jgi.G2Gateway or some subclass.
   * Must implement com.gensym.jgi.G2Connection.
   */
  public void setConnectionClassName (String newXnClass) {
    xnClass = newXnClass;
    reset ();
  }    

  /**
   * Returns the name of the class of interface created in G2
   * @return the class-name of the interface object created in G2 for
   *         the connection. Must be a subclass of GSI-INTERFACE.
   * @see com.gensym.jgi.G2ConnectionInfo#getGsiInterfaceClassName
   */
  public String getGsiInterfaceClassName() {
    return intfClass;
  }

  /**
   * Sets the name of the class of interface that will be created in G2
   * when createConnection is called. Must be a subclass of GSI-INTERFACE.
   * @see com.gensym.jgi.G2ConnectionInfo#getGsiInterfaceClassName
   */
  public void setGsiInterfaceClassName(String newIntfClass) {
    intfClass = newIntfClass;
    reset ();
  }
    
  /**
   * Indicates whether the connection creation is permanent
   * @return true if the GSI-INTERFACE is "permanent" in G2 (e.g. will
   * survive a clear-kb).
   * @see com.gensym.jgi.G2ConnectionInfo#isPermanent
   */
  public boolean isPermanent () {
    return isPerm;
  }

  /**
   * Indicates whether the GSI-INTERFACE created in G2 will be "permanent"
   */
  public void setPermanent (boolean newIsPerm) {
    isPerm = newIsPerm;
    reset ();
  }

  /**
   * Indicates whether the connection may be shared
   * @return true if the connnection is not single-user, false otherwise.
   * @see com.gensym.jgi.G2ConnectionInfo#isSharable
   */
  public boolean isSharable () {
    return shareable;
  }

  /**
   * Indicates whether the connection may be shared
   * @return true if the connnection is not single-user, false otherwise.
   */
  public void setSharable (boolean newShared) {
    shareable = newShared;
    reset ();
  }

  /**
   * Indicates whether or not a new connection will be created forcibly
   * @return true if the Connector will create a new connection every time,
   *           false otherwise.
   * @see com.gensym.jgi.G2ConnectionInfo#isForceNew
   */
  public boolean isForceNew () {
    return forceNew;
  }

  /**
   * Indicates whether or not a new connection will be created forcibly
   */
  public void setForceNew (boolean newForceNew) {
    forceNew = newForceNew;
    reset ();
  }

  /**
   * Get the NAME of the instance GSI-INTERAFCE in G2 which is handling
   * the G2 Connection.
   * @return the Name of the GSI-INTERFACE
   * @see com.gensym.jgi.G2ConnectionInfo#getGsiInterfaceName
   */
  public String getGsiInterfaceName () {
    return gsiInterfaceName;
  }

  /**
   * Get the NAME of the instance GSI-INTERAFCE in G2 which will handle
   * the G2 Connection.
   */
  public void setGsiInterfaceName(String name) {
    gsiInterfaceName = name;
    reset();
  }

  /**
   * Get the value of the remote-process-initialization-string is handling
   * the G2 Connection.
   * @see com.gensym.jgi.G2ConnectionInfo#getRemoteProcessInitString
   */
  public String getRemoteProcessInitString() {
    return remoteProcessInitString;
  }

  /**
   * Set the value of the remote-process-initialization-string is handling
   * the G2 Connection.
   */
  public void setRemoteProcessInitString(String str) {
    remoteProcessInitString = str;
    reset();
  }

  synchronized void reset () {
    if (xn != null) {
      removeAllListeners();
      xn.removeG2ConnectionListener(closingListener);
      closePrivateConnection();
      xn = null;
    }
  }

  public G2Connection getConnection () {
    return xn;
  }

  /**
   * @undocumented
   */
  protected G2Connection _getConnection() {
    if (xn == null) {
      throw new ConnectionNotAvailableException("No Connection Open, call createConnection()");
    } else 
      return xn;
  }

  private G2ConnectionListener closingListener;

  /**
   * @undocumented
   */
  protected synchronized void setXn(G2Connection con) {
    reset();
    xn = con;
    addAllListeners(); 
    xn.addG2ConnectionListener(closingListener);
  }

  /**
   * Closes the connection that is exclusively owned by this
   * G2Connector. "Exclusively owned" means that the connection
   * was made with <code>forceNew true</code> and <code>sharable
   * false</code>. Does nothing if the
   * internal connection is <code>null</code>.
   */
  protected void closePrivateConnection() {
    if (xn == null)
      return;

    G2ConnectionInfo info = ((G2Gateway)xn).getG2ConnectionInfo();
    if (!info.isSharable() && info.isForceNew())
      closeConnection();
  }

  /**
   * Creates a connection to G2 with the current set of attribute settings.
   * Calls <code>closePrivateConnection(false)</code> before opening the
   * new connection.
   * @see com.gensym.jgi.G2Connector#closePrivateConnection
   */
  /*
   * This has been copied to TwConnector to enable it to specialize the way in
   * which connections are made. Please keep in sync until we figure our way
   * out of this mess! -vkp, 5/7/98
   */
  /* Maybe we could do something with introspection: have a method
   * "protected Method getInfoConstructor()", or we could just provide
   * overrides for the default xnClass and intfClass (that's really all
   * TwConnectionInfo provides).
   */
  public void createConnection () throws G2AccessException {
    G2ConnectionEvent initEvent = null;
    G2CommunicationErrorEvent errorEvent = null;
    closePrivateConnection();
    try {
      G2ConnectionInfo xnInfo = new G2ConnectionInfo (normalizeForVB (url),
						      normalizeForVB (logicalName),
						      normalizeForVB (host),
						      normalizeForVB (port),
						      normalizeForVB (xnClass),
						      normalizeForVB (intfClass),
						      normalizeForVB (gsiInterfaceName),
						      null,
						      new Boolean (isPerm),
						      normalizeForVB (remoteProcessInitString),
						      forceNew, shareable);
      setXn((G2Connection) G2Gateway.getOrMakeConnection (xnInfo));
      initEvent = new G2ConnectionEvent(xn, 0, remoteProcessInitString, false);
	
    } catch (G2AccessInitiationException g2aie) {
      Trace.exception (g2aie);
      errorEvent = new G2CommunicationErrorEvent(this, 0, 0, g2aie.getMessage());
    }

    // This is a hack until we can work out a way of listening for connection events
    // created from getOrMakeConenction
    synchronized (connectionListeners) {
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
   * @undocumented
   */
  protected Vector connectionListeners = new Vector();

  /**
   * @undocumented
   */
  protected void addAllListeners() {
	synchronized(connectionListenersMonitor) {
	    if (xn == null || connectionListeners == null) 
	    	return;
	    for (Enumeration e = connectionListeners.elements(); e.hasMoreElements();) {
	      G2ConnectionListener listener = (G2ConnectionListener)e.nextElement(); 
	      xn.addG2ConnectionListener(listener);
	    }
	}
  }

  /**
   * @undocumented
   */
  protected void removeAllListeners() {
	synchronized(connectionListenersMonitor) {  
	    if (xn == null || connectionListeners == null) 
	    	return;
	    for (Enumeration e = connectionListeners.elements(); e.hasMoreElements();) {
	      G2ConnectionListener listener = (G2ConnectionListener)e.nextElement(); 
	      xn.removeG2ConnectionListener(listener);
	    }
	}
  }

  /**
   * Add a G2ConnectionListener, who will be informed of any G2Connection events for
   * a G2 connection.
   */
  public void addG2ConnectionListener(G2ConnectionListener listener) {
    synchronized(connectionListenersMonitor) {
      if (connectionListeners == null) 
    	  connectionListeners = new Vector();
      connectionListeners.addElement(listener);
    }
    
    if (xn != null)
      xn.addG2ConnectionListener(listener);
  }


  /**
   * Remove a G2ConnectionListener, who was previously listening for G2Connection
   * events.
   */
  public void removeG2ConnectionListener(G2ConnectionListener listener) {
    synchronized(connectionListenersMonitor) {
      if (connectionListeners == null) 
    	  connectionListeners = new Vector();
      connectionListeners.removeElement(listener);
    }
    if (xn != null)
      xn.removeG2ConnectionListener(listener);
  }


  /**
   * Report an Error Message to the Log book of the connected G2.
   *
   */
  public void returnMessage(String message) {
    _getConnection().returnMessage(message);
  }


  /**
   * Report an Error Message to the Log book of the connected G2.
   * @param errorSymbol A Symbol to identify the error
   * @param errorMessage A String detailing the error
   */
  public  void reportLogBookErrorMessage(Symbol error_symbol, String error_message) {
    _getConnection().reportLogBookErrorMessage(error_symbol, error_message);
  }

  /** 
   * Close the connection an active connection with a G2.
   * Does nothing if the connection is not open
   */
  public void closeConnection() {
    G2Connection cnxn = xn;
    if (cnxn != null)
      cnxn.closeConnection();
  }

  /**
   * Register a method of a Java object, so that it can be called by a connected G2.
   *
   * This method declares that when G2 CALLS or STARTS a specified REMOTE-PROCEDURE-DECLARATION (RPD)
   * across a GSI connection to Javalink then JavaLink will attempt to call 
   * [target].[method_name](params_from_G2_call...).
   * JavaLink will call method_name with the number and type of parameters sent from
   * G2 during the G2 RPC call. If target does not have the corresponding method_name with 
   * the correct parameter signature then JavaLink will raise a java.lang.NoSuchMethodException.
   *
   * Note: For the most optimal performance, it is recommended that Methods are registered
   * with the second variant of this method, where a java.lang.reflect.Method is registered 
   * instead of a method String this saves significant time, as JavaLink does not need to 
   * lookup the registered method each time. However, by registering a method with a string
   * allows JavaLink to dynamically dispatch a method call based on the method name and 
   * the parameters sent from G2.
   *
   * @param target      The object on which the method is to be called.
   * @param method_name The method to made visible.
   * @param g2_RPD_name The G2 REMOTE-PROCEDURE-DECLARATION name to be associated with method_name for target.
   * @exception DuplicateLocalRPCException When g2_RPD_name has already been declared as a G2 RPC.
   */
  public void registerJavaMethod(Object target, 
				 String method_name, 
				 Symbol g2_RPD_name ) {
    _getConnection().registerJavaMethod(target, method_name, g2_RPD_name);
  }

   /**
   * Register a prelooked up Method of a Java object, so that it can be called by a connected G2.
   *
   * This method declares that when G2 CALLS or STARTS a specified REMOTE-PROCEDURE-DECLARATION (RPD)
   * across a GSI-INTERFACE(connected to JAVALINK) then JavaLink will attempt to call
   * [target].[java_method](params...) registered for the RPD name using <B>registerJavaMethod</B>
   * Note, JavaLink will call java_method with the number and type of parameters sent from
   * G2 during the G2 RPC call. If java_method does not have 
   * the correct parameter signature then JavaLink will raise a java.lang.NoSuchMethodException.
   *
   *
   * @param target      The object on which the method is to be called.
   * @param java_method The method to made visible.
   * @param g2_RPD_name The G2 REMOTE-PROCEDURE-DECLARATION name to be associated with method_name for target.
   * @param call_in_new_thread Set true to create a new thread for the execution of the method
   *                           otherwise a G2 RPC call to Java will be queued with all other
   *                           method calls for this G2Connection.
   * @exception DuplicateLocalRPCException When g2_RPD_name has already been declared as a G2 RPC.
   */
  public void registerJavaMethod(Object target, 
				 Method java_method,
				 Symbol g2_RPD_name, 
				 boolean call_in_new_thread ) {
    _getConnection().registerJavaMethod(target, java_method, g2_RPD_name, call_in_new_thread);
  }

  /**
   * Call a predeclared G2 procedure/method synchronously (wait until the call returned or a timeout)
   * The current thread will wait until the remote G2 has executed.
   * <P>To call a G2 method the first argument in args must be a G2 Item of the 
   * appropriate class.</P>
   * 
   * @param g2_procedure_name  The predeclared G2 procedure/method to call.
   * @param args   The Object array to pass to the G2 procedure/method as its arguments.
   * @param timeout Time in milliseconds to wait for the return, 0 for indefinite.
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   * @exception TimeoutException if the the RPC takes longer than the timeout period.
   * @return The result of the G2 procedure/method.
   */
  public Object callRPC (Symbol g2_procedure_name, 
			 Object args[], 
			 int timeout)
       throws G2AccessException {
   return _getConnection().callRPC(g2_procedure_name, args, timeout);
  }

  /**
   * @undocumented For COM use only
   */
  public Object callRPC (Symbol g2_procedure_name, 
			 Sequence argsSeq, 
			 int timeout)
       throws G2AccessException {
   Object[] args = new Object[argsSeq.size ()];
   argsSeq.copyInto (args);
   return callRPC (g2_procedure_name, args, timeout);
  }

  /**
   * Start a predeclared remote G2 procedure, ignore any return values.
   * The method returns Immediately. The G2 procedure must have been
   * previously declared using method <B>declareRemoteRPC</B>
   *
   * @param g2_procedure_name  The G2 procedure to call
   * @param items  The array of objects to pass as arguments
   */
  public void startRPC(Symbol g2_procedure_name, 
		       Object items[]) {
    _getConnection().startRPC(g2_procedure_name, items);
  }

  /**
   * @undocumented For COM use only
   */
  public void startRPC (Symbol g2_procedure_name, 
			Sequence argsSeq) {
    Object[] args = new Object[argsSeq.size ()];
    argsSeq.copyInto (args);
    startRPC (g2_procedure_name, args);
  }

  /**
   * Indicates whether the current thread can call an
   * RPC synchronously
   */
  public boolean canCallRPC () {
    return _getConnection().canCallRPC();
  }

  /**
   * Set the value type of the return type of a object parameter from a remote RPC call
   * @param return_value_type either PASS_BY_COPY or PASS_BY_HANDLE
   */
  public void setRemoteRPCReturnKind (Symbol g2_procedure_name,
				      int return_value_type) {
    _getConnection().setRemoteRPCReturnKind(g2_procedure_name, return_value_type);
  }

  // Introspection Access
       
  /**
   * Retrieves a specific named Item from a G2. Use this
   * method to get a "root" item after making a connection to G2.
   * @param itmClass a Symbol naming the class of the Item
   * @param itmName the name of the Item
   * @return the requested Item
   * @exception G2AccessException if any error occurs during communication or if
   *   no such Item exists
   */
  public Item getUniqueNamedItem (Symbol itmClass,
				    Symbol itmName) 
       throws G2AccessException {
   return _getConnection().getUniqueNamedItem(itmClass, itmName);
  }

  /**
   * @undocumented
   */
  public String getAttributeAsText (Item itm,
				    Symbol slotName,
				    Symbol specificClassIfAny) 
       throws G2AccessException {
   return _getConnection().getAttributeAsText(itm, slotName, specificClassIfAny);
  }

  /**
   * Returns a Sequence of structures describing each attribute of the class
   * (See Attribute Export for details of the format of this information)
   * @param className a Symbol naming the G2 class
   * @param attributeNames a Sequence of symbols naming attributes of <code>
   *          className</code> for which to retreive attribute descriptions.
   *          A zero length Sequence may be passed in to retreive the
   *          descriptions of <bold>all</all> attributes.
   * @return A Sequence containing structures, each of which is a description
   *           of an attribute of the class.
   */
  public Sequence getAttributeDescriptions (Symbol className, Sequence attributeNames) 
       throws G2AccessException {
   return _getConnection().getAttributeDescriptions(className, attributeNames);
  }
       
  /**
   * Returns the current system time in the connected G2
   * @return The current unix system time (elapsed since Jan 1, 1970) at the connected G2.
   * @exception G2AccessException When there is a problem communicating with G2
   */
  public double g2UnixTime() throws G2AccessException {
    return _getConnection().g2UnixTime();
  }

  /**
   * Returns the time when G2 was started most recently.
   * @return The double value of the time when G2 was most recently started.
   * @exception G2AccessException When there is a problem communicating with G2
   */
  public double g2UnixTimeAtStart() throws G2AccessException {
    return _getConnection().g2UnixTimeAtStart();
  }

  /**
   * Gets the host name of the machince on which the connected G2 is running on.
   * @return The machine's host name of the connected G2.
   * @exception G2AccessException When there is a problem communicating with G2
   */
  public String g2GetHostName() throws G2AccessException {
    return _getConnection().g2GetHostName();
  }

  /**
   * Gets the TCP/IP port number or name on which the connected G2 is listening for network connections.
   * @return The connected G2's listener TCP/IP port number or port name as a String.
   * @exception G2AccessException When there is a problem communicating with G2
   */
  public String g2GetPortNumberOrName() throws G2AccessException {
    return _getConnection().g2GetPortNumberOrName();
  }

  /**
   * Returns the current port number or name based on a network type index.
   * @param index An integer of 1 or 2.
   * @return A Text string of the current port number or name.
   * @exception G2AccessException When there is a problem communicating with G2
   */
  public String g2GetPortNumberOrNameGivenIndex(int index) throws G2AccessException {
    return _getConnection().g2GetPortNumberOrNameGivenIndex(index);
  }

  /**
   * Gets the current version of the G2 Software.
   * @return A String value of the system and software version of the connected G2 process.
   * @exception G2AccessException When there is a problem communicating with G2.
   */
  public String g2GetSoftwareVersion() throws G2AccessException {
    return _getConnection().g2GetSoftwareVersion();
  }

  /** 
   * Returns the current run state of G2.
   * @return a symbol that is one of RUNNING, PAUSED, or RESET
   * @exception G2AccessException if any error occurs during communication
   *   with G2
   */
  public Symbol getG2State() throws G2AccessException {
    return _getConnection().getG2State();
  }

  /**
   * Sets the run state of G2. In order to restart G2, first change to
   * RESET then change to RUNNING.
   * @param the desired new state of G2. This should be one of the following
   *   Symbols - RUNNING, PAUSED, or RESET
   * @exception G2AccessException if any error occurs during communication
   *   with G2
   */
  public Symbol setG2State(Symbol newState) throws G2AccessException {
    return getConnection().setG2State(newState);
  }

  /**
   * Retreives all strict instances of a given class. In other words,
   * given a class A and its subclass B, assuming instances of both A
   * A and B exist in the KB, <code>getStrictInstancesOfClass (A)</code>
   * will not include instances of B. In order to gather all instances of
   * a class including subclasses, use <code>getDirectSubClasses</code>
   * and call <code>getStrictInstances</code> recursively.
   * @param g2ClassName_ a Symbol naming a class
   * @return a Sequence of 0 or more Items of the class g2ClassName_
   * @see #getDirectSubClasses
   * @exception G2AccessException if there any errors during communication or within the call
   */
  public Sequence getStrictInstancesOfClass (Symbol g2ClassName_) throws G2AccessException {
    return _getConnection().getStrictInstancesOfClass(g2ClassName_);
  }

 /**
   * Retreives the names of all direct subclasses of a given class.
   * Use this method recursively to gather all subclasses of a given class.
   * @param g2ClassName_ a Symbol naming a class
   * @return a Sequence of Symbols naming the direct subclasses
   * @exception G2AccessException if there any errors during communication or within the call
   */
  public Sequence getDirectSubclasses (Symbol g2ClassName_) throws G2AccessException {
    return _getConnection().getDirectSubclasses(g2ClassName_);
  }


  /** Sets the debugging state of the underlying g2 interface class. Should
   * avoid using this in three-tier situations, as others may be using
   * the middle tier that is slowed down by turning on debug. */
  public void setInterfaceDebugOptions(boolean on) {
    _getConnection().setInterfaceDebugOptions(on);
  }

  public void setInterfaceDebugOptions(int level) {
    _getConnection().setInterfaceDebugOptions(level);
  }

  /**
   * Returns the definition Item for any G2 class
   * @exception G2AccessException when a problem occurs as a result
   *   of communicating with G2.
   */
  public G2Definition getDefinition(Symbol g2ClassName)
       throws G2AccessException {
   return _getConnection().getDefinition(g2ClassName);
  }

  protected static volatile Image iconImage = null;

  protected Image getIconImage() {
    if (iconImage == null) {
      synchronized(G2Connector.class) {
        if (iconImage == null) {
          iconImage = 
              Toolkit.getDefaultToolkit().getImage(this.getClass().getResource ("connector.gif"));
        }
      }
    }
    return iconImage;
  }

  @Override
  public void paint (Graphics g) {
    Dimension size = getSize ();
    g.setColor (Color.blue);

    Image iconImg = getIconImage();
    g.drawImage(iconImg, 1, 1, this);

    g.drawLine (0, 0, size.width - 1, 0);
    g.drawLine (size.width - 1, 0, size.width - 1, size.height - 1);
    g.drawLine (size.width - 1, size.height - 1, 0, size.height - 1);  
    g.drawLine (0, size.height - 1, 0, 0);

  }

  @Override
  public Dimension getPreferredSize() {
    Image iconImg = getIconImage();
    int iconWidth = iconImg.getWidth(this);
    int iconHeight = iconImg.getHeight(this);
    return new Dimension(iconWidth + 2, iconHeight + 2);
  }

  @Override
  public Dimension getMinimumSize() {
    return getPreferredSize();
  }

  private static String normalizeForVB(final String in) {
    if (in == null)
      return null;

    String trimmed = in.trim();
    if (trimmed.length() == 0) 
      return null;
    else
      return trimmed;
    }
}

class G2ConnectionClosingAdapter extends G2ConnectionAdapter implements java.io.Serializable{
  static final long serialVersionUID = 2L;

  private G2Connector connector;

  public G2ConnectionClosingAdapter(G2Connector connector) {
    this.connector = connector;
  }
  @Override
  public void g2ConnectionClosed(G2ConnectionEvent event) {
    if (event.getSource().equals(connector.getConnection()))
      connector.reset();
  }
}
  
