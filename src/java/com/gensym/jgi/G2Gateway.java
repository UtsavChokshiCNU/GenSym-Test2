/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2Gateway.java
 *
 *
 *   Modifications:
 *
 */
package com.gensym.jgi;

/* Imports */
import java.util.Hashtable;
import java.util.Enumeration;
import java.util.Vector;
import java.lang.reflect.Method;
import java.nio.charset.Charset;

import com.gensym.util.Symbol;
import com.gensym.util.ClassManager;
import com.gensym.util.Denotation;
import com.gensym.core.DebugUtil;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.CorruptionException;
import com.gensym.jgi.download.StubCreationException;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;
import com.gensym.util.AlreadyInitializedException;
import com.gensym.util.ItemEvent;
import com.gensym.jgi.download.StubClassLoader;
import com.gensym.jgi.download.DefaultStubFactory;
import com.gensym.jgi.download.G2StubFactory;
import com.gensym.classes.Item;
import com.gensym.classes.G2Definition;
import com.gensym.util.UnexpectedException;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.IOException;
import java.io.PrintWriter;
import com.gensym.jgi.dataservice.DataServiceHandler;

/* Main G2Gateway defintion */


/**
 * This class provides a network interface to a GSI-INTERFACE object created
 * within a connected G2.
 *
 * <P>A G2Gateway can communicate with a G2 once a connection has been
 * established. The G2Gateway
 * can create the connection using the methods <B>getOrMakeConnection</B>,
 * <B>initiateConnection</B> or wait for a G2 server to make the connection.
 *
 * <P>There are three distinct ways of communicating with G2;
 *
 * <P>1.Simple Messages : send messages to G2's message board (<B>returnMessage</B>) and
 * Receive a message from G2 (<B>g2MessageReceived</B> in G2ConnectionListener)
 *
 * <P>2.Remote Procedure Calls : Registered Java Methods (<B>registerJavaMethod</B>)
 * can be called by G2 and G2 procedures/methods that can be called by a G2Gateway.
 * G2 procedures and methods can be called Synchronously (<B>callRPC</B>)
 * and started (<B>startRPC</B>).
 *
 * <P>3. Data Services: You can create java Data Services that supply data on demand to
 * Gsi Data Serviced Variables defined in G2.
 *
 * <P><P>Data types in RPC calls between G2 and Java are converted automatically;
 *
 * <P>When G2 calls a method in a G2Gateway the parameters are
 * converted as follows;
 * <LI>G2 INTEGER to Java int
 * <LI>G2 TEXT to Java String
 * <LI>G2 TRUTH-VALUE to boolean
 * <LI>G2 FLOAT to Java double
 * <LI>G2 SYMBOL to Java com.gensym.util.Symbol
 * <LI>G2 SEQUENCE to Java com.gensym.util.Sequence
 * <LI>G2 STRUCTURE to Java com.gensym.util.Structure
 * <LI>G2 ITEM to Java com.gensym.classes.Item **
 * (** All G2 System classes are defined as Java Stub
 *     classes in package com.gensym.classes. Additionally any KB user classes are also
 * converted to Java stubs)
 *
 * <P><P>When G2 embeds data within an array, sequence or structure, all primitive
 * types will be object wrapped;
 * <LI> G2 INTEGER to Java Integer
 * <LI> G2 TRUTH-VALUE to Java Boolean
 * <LI> G2 FLOAT to Java Double
 *
 * <P>The following Java datatypes are automatically converted to G2 ITEMs or VALUEs
 * when sent back to G2 via a RPC call (see <B>CallRPC...</B>) even when embedded in
 * Sequences, Structures, Attributes of Items, Arrays or Lists;
 *
 * <LI>Java Integer to G2 INTEGER
 * <LI>Java String to G2 TEXT
 * <LI>Java Boolean to G2 TRUTH-VALUE
 * <LI>Java Double to G2 FLOAT
 * <LI>Java Byte to G2 INTEGER
 * <LI>Java Character to G2 TEXT(of one char)
 * <LI>Java Float to G2 FLOAT
 * <LI>Java Short to G2 INTEGER
 * <LI>Java Long to G2 INTEGER(first 31 bits)
 * <LI>Java com.gensym.util.Symbol to G2 SYMBOL
 * <LI>Java com.gensym.util.Sequence to G2 SEQUENCE
 * <LI>Java com.gensym.util.Structure to G2 STRUCTURE
 * <LI>Java com.gensym.util.Item to G2 ITEM (and any subclasses of etc...)
 * <LI>Java Object[] to G2 G2-ARRAY
 * <LI>Java boolean[] to G2 TRUTH-VALUE-ARRAY
 * <LI>Java Symbol[] to G2 SYMBOL-ARRAY
 * <LI>Java String[] to G2 TEXT-ARRAY
 * <LI>Java Number[] to G2 QUANTITY-ARRAY
 * <LI>Java double[] to G2 FLOAT-ARRAY
 * <LI>Java int[] to G2 INTEGER-ARRAY
 *
 * <P>Note: The conversion to and from primitive Java arrays is very efficient.</P>
 *
 * <P> Callbacks generated from communication with G2 cause events to be sent to any
 * G2ConnectionListeners. These events are generated under predefined conditions;
 * <LI>The connected G2 has resumed.
 * <LI>The connected G2 has paused.
 * <LI>The connected G2 has send a message (VIA INFORM THE...)
 * <LI>The connection to G2 has been closed.
 * <LI>A connection to G2 has just been established.
 * <LI>A communicationError has occured while the connection to a G2 is active.
 * <LI>A communication error has occured, but no connection is active.
 * <LI>The network cannot deliver data that Java is attempting to write to G2.
 * <LI>The network cannot deliver data that G2 is attempting to write to Java.
 *
 * <P>A G2ConnectionListener can register interest in these events by calling
 * <B>addG2ConnectionListener</B> and can remove interest by calling
 * <B>removeG2ConnectionListener</B>.
 *
 * <P>A G2Gateway can only be connected to one G2 at any one time. If multiple
 * connections are required within a Java application, then multiple G2Gateway's
 * must be created. However, a G2Gateway can reconnect to another G2 on the network.
 * Note, when a G2Gateway reconnects to another G2, Remote Procedures must be
 * redeclared for the new connection.
 *
 * <P>Any G2 can attempt to make an unsolicited connection to Java, but the
 * connection must be accepted by an installed G2ConnectionHandlerFactory.
 * The static method <B>setG2ConnectionHandlerFactory</B> allows a
 * G2ConnectionHandlerFactory instance to select/create a G2Connection
 * for any unsolicited G2 connections.
 *
 * <P>G2Gateway has been designed to allow multiple Java threads to access a Java connection.
 *
 *
 * @version 	1.0.v0, 25 Sep 1997
 *
 * @author      mdg, vkp, rp
 * @see         com.gensym.jgi.G2Connection
 * @see         com.gensym.classes.Item
 * @see         com.gensym.jgi.G2ConnectionHandlerFactory
 * @see         com.gensym.jgi.G2ConnectionListener
 */
public class G2Gateway implements G2Connection {

  // Private attributes

  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi", G2Gateway.class);

  /**
   * Turned on by RPCTrace for RPC tracing
   */
   static boolean rpcTraceOn;

  /**
   * JGIConnection gateway to G2
   */
  static JGInterface _nativeInterface;
  /**
   * Unique Identification String for connection purposes
   */
  private String uniqueIdent = "-G2connectionID " + this.hashCode();

  /**
   * Lookup table for declared functions handles as these are per connection
   */
  private Hashtable remoteRPCTable = new Hashtable();

  /**
   * Lookup table for declared local RPCs (G2 to Java), keyed on G2 RPD name
   * contains LocalRPCDeclaration objects
   */
  private Hashtable localRPCTable;

  /**
   * Lookup table for open connections
   */
  private static Vector pendingConnections = new Vector();
  private static Hashtable openConnections = new Hashtable();

  /**
   * My Current Context
   */
  private int context = -1;

  /**
   * The ClassManager for this context
   */
  private ClassManager classManager;

  /**
   * Java level debugging switch
   */
  private boolean fulldebug = false;
  private static boolean traceOn = false;

  private static Hashtable _indentifiedInterfaces = new Hashtable();

  private static final Resource i18n =
  Trace.getBundle("com.gensym.jgi.Messages");

  private static final Resource i18nTrace =
  Trace.getBundle("com.gensym.jgi.TraceMessages");

  private boolean _connectionAlive = false;

  /**
   * Constant, notify G2 to pass an item by HANDLE
   * @see setRemoteRPCReturnKind
   */
  public static final int PASS_BY_HANDLE = JGInterface.PASS_BY_HANDLE;

  /**
   * Constant, notify G2 to pass an item by COPY
   * @see setRemoteRPCReturnKind
   */
  public static final int PASS_BY_COPY = JGInterface.PASS_BY_COPY;

  /**
   * Constant, notify G2 to pass a parameter return by REFERENCE
   * @see setRemoteRPCReturnKind
   */
  //public static final int PASS_BY_REFERENCE = JGInterface.PASS_BY_REFERENCE;

  /**
   *  Constant, notify G2 to pass a parameter return by COPY WITH HANDLE
   * @see setRemoteRPCReturnKind
   */
  //public static final int PASS_BY_COPY_WITH_HANDLE = JGInterface.PASS_BY_COPY_WITH_HANDLE;

  /**
   * Constant, to declare a Java method to be executed in a new thread when called by G2 
   *@see declareLocalRPC
   */
  public static final boolean CALL_METHOD_IN_NEW_THREAD = true;


  /**
   * Constant, to declare a Java method so that a call request from G2 is queued with other
   * method requests for this G2 connection.
   *
   *@see declareLocalRPC
   */
  public static final boolean DONT_CALL_METHOD_IN_NEW_THREAD = false;


  /**
   * Class Root name of Java Proxy classes in G2 for Java class provided by this Gateway
   */
  public static final Symbol G2_JAVA_PROXY_ROOT_CLASS_NAME = Symbol.intern("JGI-JAVA-PROXY");

  /**
   * The paused state constant
   */
  public static final Symbol PAUSED_  = Symbol.intern ("PAUSED");

  /**
   * The reset state constant
   */
  public static final Symbol RESET_   = Symbol.intern ("RESET");

  /**
   * The running state constant
   */
  public static final Symbol RUNNING_ = Symbol.intern ("RUNNING");

  private Symbol currentG2State = null;

  private static long DEFAULT_CONNECTION_TIMEOUT = 20000;  // 20 seconds

  private long timeOut = DEFAULT_CONNECTION_TIMEOUT;

  /**
   * What host and port this connection used while connecting to G2
   */
  private String host, port;

  /**
   * Non thread aware connection flag
   */
  private volatile boolean G2ConnectionNotificationFlag;

  /**
   * Non thread aware conneciton flag event
   */
  private volatile G2ConnectionEvent G2ConnectionAbortedEvent;

  /**
   * The version of the G2 we are connecting to.
   */
  private G2Version version;

  /**
   * G2ConnectionListener List
   */
  private Vector g2ConnectionListeners = new Vector(5);

  /**
   * You must use getCurrentStubLoader() to access this, to ensure that it
   * is set up correctly...should not be null in two tier case.
   */
  private StubClassLoader loader; 

  // Static code

  /**
   * Once this class has been loaded, we can potentially interpret
   * G2 URLs. In order to facilitate this, we need to load known
   * interpreters at this time
   */
  static {
    com.gensym.net.g2.G2ProtocolRegistry.loadInterpreters ();
  }

  // Public command line arguments
  /**
   * Command line option for specifing a TCPIP Listener port from which
   * JavaLink will listener for incoming G2 connections.
   * Follow this command with a valid TCPIP port number (e.g. 22045).
   * The default listener port for JavaLink is 22041.
   */
  public static final String LISTENER_PORT_OPTION = JGInterface.LISTENER_PORT_OPTION;

  /**
   * Command line option for specifing that there is no Listener port from 
   * which JavaLink will listen for incoming G2 connections.
   * JavaLink can connect to G2, but G2 will not be able to initiate a connection with JavaLink
   */
  public static final String NO_LISTENER_OPTION   = JGInterface.NO_LISTENER_OPTION;

  /**
   * Must be called to initialize the G2 Communication class before any other
   * public G2Access method called.
   *@exception AlreadyInitializedException When this class has already been initialized.
   */
  public static void initialize () throws AlreadyInitializedException {
    String args[] = new String[0];
    initialize(args);
  }

  /**
   * Must be called to initialize the G2 Communications class before any other
   * public G2Access method called.
   *
   * @param listener_port The TCPIP port at which G2Gateway will listen for
   *                      incoming unsolicited connections from G2 servers.
   *@exception AlreadyInitializedException When this class has already been initialized.
   */
  public static void initialize(int listener_port)
       throws AlreadyInitializedException
  {
    String args[] = new String[2];
    args[0] = JGInterface.LISTENER_PORT_OPTION;
    args[1] = "" + listener_port;
    initialize(args);
  }

  /**
   * Must be called to initialize the G2 Communications class before any other
   * public G2Access method called.
   *
   * @param command_line_options
   * <code>-nolistener</code> <code>-listenerport</code> port <code>-tcpipexact</code>
   * <code>-tcpport</code> <code>-debuggateway</code>
   * <code>-secure</code> <code>-cert</code> certificate_identifier
   *@exception AlreadyInitializedException When this class has already been initialized.
   *@see LISTENER_PORT_OPTION
   *@see NO_LISTENER_OPTION
   */
  public static synchronized void initialize(String []args){
    if (_nativeInterface != null){
    	return;
    }

    _nativeInterface = JGInterface.getJGInterface(args);
    //Now set this limit, in case it was called before we had a native interface available
    _nativeInterface.setGSIContextLimit(maximumContexts);
      
  }

  /**
   * Startup the G2 Communications Gateway allowing G2Gateway to connect and communicate with
   * G2 and listen for unsolicited connections from G2 servers (unsolicited connections are only accepted
   * if a G2ConnectionFactory has been installed). G2 Connections made via
   * <B>getOrMakeConnection</B> will automatically startup the G2 Communications if not already started.
   * @see #getOrMakeConnection
   * @see #setConnectionHandlerFactory
   */
  public static void startup()
  {
    if (_nativeInterface == null)
      throwNotInitializedException();

    _nativeInterface.startup();
  }
	

  /**
   * Generic throw not initialized method.
   */
  private static void throwNotInitializedException()
  {
    throw new G2GatewayNotInitializedError
      ("G2 Gateway not Initialized, call G2Gateway.initialize()");
  }

  /**
   * Generic throw not alive method
   */
  private static void throwConnectionNotAliveException()
  {
    throw new G2CommunicationException("This connection is not currently connected to a G2");
  }

  // Public constructors

  /**
   * Creates an inactive G2 Gateway and initializes it with a ClassManager.
   * Makes the classManager with makeClassManager.
   * @see com.gensym.jgi.G2Gateway#makeClassManager
   */
  public G2Gateway() {
  }

  /**
   * @undocumented
   * This method is called just before the connection initialized
   * event is dispatched. It is guaranteed to be followed by
   * that event. The connection is not yet alive for RPC calls.
   * @see #isAlive
   */
  protected void initializeInstance () {
    classManager = makeClassManager ();
  }

  /**
   * This allows subclasses of G2Gateway to install their own subclass
   * of ClassManager
   */
  /* Maybe implement sharing of ClassManagers? */
  protected ClassManager makeClassManager() {
    ClassManager manager = null;
    manager = new ClassManager(this);
    return manager;
  }

  //Public methods

  // Property Modifiers

  /**
   * Set the timeout that is used in <B>initiateConnection()</B> and <B>callRPC</B>
   * (The default is 20 seconds)
   *@param timeOut The time in milliseconds.
   *
   */
  public synchronized void setDefaultCommunicationTimeOut(long timeOut) {
    this.timeOut = timeOut;
  }

  /**
   * Set the default timeout that is used in <B>initiateConnection()</B> and <B>callRPC</B>
   * for future instances of G2Gateway.  (The default default is 20 seconds)
   *@param timeOut The time in milliseconds.
   *
   */
  public static void setDefaultDefaultCommunicationTimeOut(long timeOut) {
    G2Gateway.DEFAULT_CONNECTION_TIMEOUT = timeOut;
  }


  /**
   * @see #setDefaultCommunicationTimeOut(long timeOut)
   */
  public synchronized long getDefaultCommunicationTimeOut() {
    return timeOut;
  }

  // G2ConnectionListener interface

  /**
   * Add a G2ConnectionListener, who will be informed of any G2Connection events for
   * a G2 connection.
   *@param listener The G2ConnectionListener to inform.
   */
  @Override
  public synchronized void addG2ConnectionListener(G2ConnectionListener listener) {
    if (!g2ConnectionListeners.contains(listener))
      g2ConnectionListeners.addElement(listener);
  }


  /**
   * Remove a G2ConnectionListener, who was previously listening for G2Connection
   * events.
   *@param listener The G2ConnectionListener to inform.
   */
  @Override
  public synchronized void removeG2ConnectionListener(G2ConnectionListener listener) {
    g2ConnectionListeners.removeElement(listener);
  }

  // G2 Callback Methods

  /**
   * Returns the list of current G2ConnectionListeners registered to
   * receive events from this Gateway.
   *@returns A Vector of G2ConnectionListeners.
   */
  protected synchronized Vector getG2ConnectionListeners () {
    return (Vector) g2ConnectionListeners.clone ();
  }

  /**
   * Notify any listeners of a connection event...note these events are
   * delivered by JGInterface outside the GSI library thread.
   * @param  event The G2ConnectionEvent to dispatch.
   */
  protected void dispatchG2ConnectionEvent(G2ConnectionEvent event) {

    //Must ensure that Subscriptions are set
    int eventid = event.getId();

    Trace.send (10, traceKey, i18nTrace, "dispatchCxnEvent", event);
    //System.out.println (this+ ": G2Gateway.dispatchConnectionEvent (" + event + ") in " + Thread.currentThread ());
    //System.out.flush ();
    // Must do, regardless of G2ConnectionListeners....
    switch (eventid) {
    case G2ConnectionEvent.G2_IS_PAUSED:
      currentG2State = PAUSED_;
      break;
    case G2ConnectionEvent.G2_IS_RESET:
      currentG2State = RESET_;
      break;
    case G2ConnectionEvent.G2_IS_RESUMED:
    case G2ConnectionEvent.G2_IS_STARTED:
      currentG2State = RUNNING_;
      break;
    case G2ConnectionEvent.G2_CONNECTION_INITIALIZED:
      try {
	String str = checkForHandleOK(0);
	if (str != null){
		return; 
	}
	checkAndStoreVersion ();
	setV5Mode(true); // Must set this for subscriptions to be devlivered
	initializeReceiveRegistrations();
	G2ConnectionNotificationFlag = true;
      } catch (G2AccessException gae) {
	Trace.exception (gae);
	Trace.send(10, traceKey, i18nTrace, "Can not set V5 mode...error was " + gae.toString());
      }
      break;
    case G2ConnectionEvent.G2_CONNECTION_CLOSED:
      //System.out.println ("Connection no longer valid! Cannot make RPC calls");
      _connectionAlive = false;

      // Put the following into a dispose method
      removeOpenConnection(g2ConnectionInfo);
      ConnectionResolver.clearWrapper(this);
      classManager = null;
      if (_nativeInterface != null)
	_nativeInterface.clearMethodCallQueue(this);
      loader = null;
      // The following caused too many problems downstream.  It was
      // even worse when we nulled the subscpntable
      // subscpnTable.clear();
      remoteRPCTable = null;
      
      localRPCTable = null;
      break;
    case G2ConnectionEvent.G2_CONNECTION_ABORTED:
      G2ConnectionNotificationFlag = true;
      G2ConnectionAbortedEvent = event;
      break;
    default:
    } //switch

    Vector dispatchList = null;
    if (!g2ConnectionListeners.isEmpty()) {
      synchronized(this) {
	dispatchList = (Vector)g2ConnectionListeners.clone();
      }

      for (Enumeration e = dispatchList.elements(); e.hasMoreElements();) {
	G2ConnectionListener listener = (G2ConnectionListener)e.nextElement();
	switch (eventid) {
	case G2ConnectionEvent.G2_IS_PAUSED:
	  listener.g2IsPaused(event);
	  break;
	case G2ConnectionEvent.G2_IS_RESUMED:
	  listener.g2IsResumed(event);
	  break;
	case G2ConnectionEvent.G2_IS_RESET:
	  listener.g2IsReset(event);
	  break;
	case G2ConnectionEvent.G2_IS_STARTED:
	  listener.g2IsStarted(event);
	  break;
	case G2ConnectionEvent.G2_CONNECTION_CLOSED:
	  listener.g2ConnectionClosed(event);
	  break;
	case G2ConnectionEvent.G2_CONNECTION_INITIALIZED:
	  listener.g2ConnectionInitialized(event);
	  break;
	case G2ConnectionEvent.G2_MESSAGE_RECEIVED:
	  listener.g2MessageReceived(event);
	  break;
	case G2ConnectionEvent.G2_COMMUNICATION_ERROR:
	  listener.communicationError((G2CommunicationErrorEvent)event);
	  break;
	case G2ConnectionEvent.G2_READ_BLOCKAGE:
	  listener.readBlockage(event);
	  break;
	case G2ConnectionEvent.G2_WRITE_BLOCKAGE:
	  listener.writeBlockage(event);
	  break;
	default:
	}
      }
    }
  }

  /**
   * @undocumented
   */
  protected void initializeReceiveRegistrations() {
    if (_nativeInterface != null) {
      if (dataServiceHandler != null ) // we want to receive registrations
	_nativeInterface.setReceiveRegistrations(context, true);
      else
	_nativeInterface.setReceiveRegistrations(context, false);
    }
  }

  private DataServiceHandler dataServiceHandler = null;
  
  void setDataServiceHandler(DataServiceHandler dataServiceHandler) {
    if (dataServiceHandler != null) {
      this.dataServiceHandler = dataServiceHandler;
      //System.out.println("registered " + this.dataServiceHandler);
    }
  }

  void dispatchDataServiceHandlerEvent(Object data, int eventId, Object[] identifyingAttributes) {
    if (dataServiceHandler != null) {
      //System.out.println("calling  " + this.dataServiceHandler + " " + eventId);
      dataServiceHandler.dispatchDataServiceEvent(data, eventId, identifyingAttributes);
    }
  }


  /**
   * Called to provide the Connection ID when a G2 connection
   * has been established. Do not override this method.
   *
   * @param context_number The context number.
   */
  void setConnectionID(int ID)
  {
    context = ID;

    _connectionAlive = true;

    // Declare per connection local functions just in case they have never been declared
    privateInitializeLocalRPCs();
    initializeLocalRPCs();

    // initialize Remote RPCs to G2 for this connection
    privateInitializeConnectionRPCs();
    initializeConnectionRPCs();
       
    // We have commpleted connection, release the connection block
    //System.out.println ("Connection Created : " + ID);
    //Thread.dumpStack ();
    //G2ConnectionNotificationFlag = true;
  }


  // Public methods
  // ***********************************


  /**
   * Sets the G2ConnectionHandlerFactory of an application.
   *
   * <P>It can be called at most once
   * by an application. A G2ConnectionHandlerFactory is responsible for selecting an
   * appropriate G2Connection for an incomming unsolicited (g2 initiated) G2 connection.<P>
   * Throws an Error if the factory has already been defined.
   *
   * @param fac the desired factory.
   */
  public static void setConnectionHandlerFactory(G2ConnectionHandlerFactory fac)
  {

    if (_nativeInterface == null)
      throwNotInitializedException();
    _nativeInterface.setConnectionHandlerFactory(fac);
  }



  /**
   * Return a message to the connected G2.
   *
   * <P> The message text is sent to the MESSAGE-BOARD item in the current KB
   * of the connected G2.
   *
   * @param message the message to send to G2's message board.
   */
  @Override
  public void returnMessage(String message)
  {
    if (_nativeInterface == null)
      throwNotInitializedException();
    
    if (_connectionAlive)
      _nativeInterface.returnMessage(message, context);
    else
      throw new G2CommunicationException("Connection not actively connected to a G2");
  }

  /**
   * Set the maximum number of G2 Gateway (GSI) Contexts we will allow in this client.
   *
   * @param limit An integer limit.  Default (inherited from G2 Gateway) is 50.
   *
   */

  private static int maximumContexts = 50;

  public static void setGSIContextLimit(int limit)
  {
    if (_nativeInterface != null)
      _nativeInterface.setGSIContextLimit(limit);
    maximumContexts = limit;
  }    

  /**
   * Return the socket on which G2Gateway is listening for unsolictated G2.
   * connections.
   *@return the socket on which G2Gateway is listening.
   *
   */
  public static int getListenerSocket()
  {
    if (_nativeInterface == null)
      throwNotInitializedException();

    return _nativeInterface.getListenerSocket();
  }

  /**
   * Return whether the context is secure (SSL)
   *@Return whether the context is secure (SSL)
   *
   */
  @Override
  public boolean getSecureContext()
  {
    if (_nativeInterface == null)
      throwNotInitializedException();

    if (_nativeInterface.getSecureContext(this.context) == 0)
      return false;
    else
      return true;
  }

  /**
   * Report an Error Message to the Log book of the connected G2.
   * @param errorSymbol A Symbol to identify the error
   * @param errorMessage A String detailing the error
   *
   */
  @Override
  public void reportLogBookErrorMessage(Symbol errorSymbol, String errorMessage)
  {
    if (_nativeInterface == null)
      throwNotInitializedException();

    if (!_connectionAlive)
      throwConnectionNotAliveException();

    _nativeInterface.reportLogBookErrorMessage(errorSymbol, errorMessage, context);
  }


  /**
   * Close an active connection with a G2.
   * The connection is not alive after this point.
   * Any attempts to call RPCs through this Gateway will
   * fail.
   * @see #isAlive
   */
  @Override
  public void closeConnection() {
    if (g2ConnectionInfo != null)
      removeOpenConnection(g2ConnectionInfo);
    if (_nativeInterface == null)
      throwNotInitializedException();

    // Event though the conenction is technically still open, we mark it closed
    // straight away, as thge closeConnection event, is asynchronus and could
    // come at any time.
    _connectionAlive = false;

    _nativeInterface.closeConnection(this.context);
  }


  /**
   * Determines if this Gateway can be used for RPC calls
   * to G2 or not. It will return true once it has initialized
   * properly and until it is closed (either by a method call
   * or from the server).
   * @return boolean true if it is OK to call RPCs through
   *   this Gateway, false otherwise
   * @see #closeConnection
   */
  @Override
  public boolean isAlive () {
    return _connectionAlive;
  }


  /**
   * Get the declaration for a localRPC for a given connection and java_method_name.
   */
  final LocalRPCDeclaration getLocalRPCDeclaration(Symbol G2_RPD_name)
  {
    //System.out.println("In getLocalRPCDeclaration Name is " + G2_RPD_name + " " + this);

    if (localRPCTable == null) {
      localRPCTable = new Hashtable(11);
    }

    return (LocalRPCDeclaration)localRPCTable.get(G2_RPD_name);
  }

  /**
   * Set the declaration for a localRPC for a given connection and G2_RPD_name.
   * Note : method called from JGInterface to store declarations
   */
  final void setLocalRPCDeclaration(Symbol G2_RPD_name,
				    LocalRPCDeclaration target) {

    if (localRPCTable == null) {
      localRPCTable = new Hashtable(11);
    }

    localRPCTable.put(G2_RPD_name, target);
  }


  /**
   * Register a method of a Java object, so that it can be called by a connected G2.
   *
   * This method declares that when G2 CALLS or STARTS a specified REMOTE-PROCEDURE-DECLARATION (RPD)
   * across a GSI connection to Javalink then G2Gateway will attempt to call
   * [target].[method_name](params_from_G2_call...).
   * G2Gateway will call method_name with the number and type of parameters sent from
   * G2 during the G2 RPC call. If target does not have the corresponding method_name with
   * the correct parameter signature then G2Gateway will raise a java.lang.NoSuchMethodException.
   *
   * Note: For the most optimal performance, it is recommended that Methods are registered
   * with the second variant of this method, where a java.lang.reflect.Method is registered
   * instead of a method String. This saves significant time, as G2Gateway does not need to
   * lookup the registered method each time. However, by registering a method with a string
   * allows G2Gateway to dynamically dispatch a method call based on the method name and
   * the parameters sent from G2.
   *
   * @param target      The object on which the method is to be called.
   * @param method_name The method to made visible.
   * @param g2_RPD_name The G2 REMOTE-PROCEDURE-DECLARATION name to be associated with method_name for target.
   * @exception DuplicateLocalRPCException When g2_RPD_name has already been declared as a G2 RPC.
   */
  @Override
  public void registerJavaMethod(Object target,
				 String method_name,
				 Symbol g2_RPD_name )
  {
    /* The native interface needs to know the return signature of the method
     * This method will return a Object
     */
    if (_nativeInterface == null)
      throwNotInitializedException();
    _nativeInterface.declareLocalRPC(this,
				     target,
				     method_name,
				     g2_RPD_name,
				     JGInterface.CALL_METHOD_IN_QUEUED_THREAD);
  }

  /**
   * Register a pre-looked-up Method of a Java object, so that it can be called by a connected G2.
   *
   * This method declares that when G2 CALLS or STARTS a specified REMOTE-PROCEDURE-DECLARATION (RPD)
   * across a GSI-INTERFACE(connected to JAVALINK) then G2Gateway will attempt to call
   * [target].[java_method](params...) registered for the RPD name using <B>registerJavaMethod</B>.
   * Note, G2Gateway will call java_method with the number and type of parameters sent from
   * G2 during the G2 RPC call. If java_method does not have
   * the correct parameter signature then G2Gateway will raise a java.lang.NoSuchMethodException.
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
  @Override
  public void registerJavaMethod(Object target,
				 Method java_method,
				 Symbol g2_RPD_name,
				 boolean call_in_new_thread )
  {
    /* The native interface needs to know the return signature of the method
     * This method will return a Object
     */
    if (_nativeInterface == null)
      throwNotInitializedException();
    _nativeInterface.declareLocalRPC(this,
				     target,
				     java_method,
				     g2_RPD_name,
				     (call_in_new_thread ?
				      JGInterface.DONT_CALL_METHOD_IN_QUEUED_THREAD :
				      JGInterface.CALL_METHOD_IN_QUEUED_THREAD));

  }

  /**
   * For registering frequently called methods whose absence is fatal.
   * @throws NoSuchMethodError
   * @undocumented
   */
  protected void registerJavaMethod (Object target, Class clazz, String methodName,
				     Class[] methodArgs,
				     Symbol callback, boolean inNewThread){
    try {
      Method method = clazz.getDeclaredMethod(methodName, methodArgs);
      registerJavaMethod(target, method, callback, inNewThread);
    } catch (NoSuchMethodException nsme) {
      Trace.exception(nsme);
      throw new NoSuchMethodError(i18n.format("g2gMissingCrucialMethod",
					      clazz, methodName));
    }
  }


  /**
   * Declares a G2 procedure/method in a G2 process to be invocable, as a remote
   * RPC, by a connected G2Gateway.
   *
   *<P>Calls to <B>declareRemoteRPC</B> should be made in callback method
   * <B>G2InitializeConnection</B>, because remote procedure declarations
   * are specific to a G2 connection.
   *
   *@param g2_function_name  The G2 procedure name to call.
   *@param java_receiver_method_name For reception of asynchronous RPC calls.
   *@param timeout milliseconds to wait before the call is timeout and aborted.
   */
  private void declareRemoteRPC(Symbol g2_procedure_name,
				String java_receiver_method_name,
				int timeout)
  {

    declareRemoteRPC(g2_procedure_name,
                       -1, /* Varargs */
                       -1, /* Varargs */
		       java_receiver_method_name,
		       timeout);
  }



  /**
   * Declares a G2 procedure/method in a G2 process to be invocable, as a remote
   * RPC, by a connected G2Gateway.
   *
   *<P>Calls to <B>declareRemoteRPC</B> should be made in callback method
   * <B>G2InitiaizeConnection</B>, because remote procedure declarations
   * are specific to a G2 connection.
   *
   *@param g2_function_name  The G2 procedure name to call.
   *@param remote_arg_count  The number of args in the G2 procedure.
   *@param return_arg_count  The number of args expected to be returned.
   *@param java_receiver_method_name For reception of asynchronous RPC calls.
   *@param timeout milliseconds to wait before the call is timeout and aborted.
   */
  private void declareRemoteRPC(Symbol g2_procedure_name,
				int remote_arg_count,
				int return_arg_count,
				String java_receiver_method_name,
				int timeout)
  {
    
    if (_nativeInterface == null)
      throwNotInitializedException();

    if (!_connectionAlive)
      throwConnectionNotAliveException();

    // Java wrapper of rpdeclare_remote
    // we must record the java method name, so we can lookup
    // the rpc handle when doing a call or start on a G2 proc
    if (remoteRPCTable == null)
      
      // We need an instance of an hashtable to create a dictionary
      // of g2 functions called
      remoteRPCTable = new Hashtable();

    Long handle = (Long)_nativeInterface.declareRemoteRPC(g2_procedure_name,
								remote_arg_count,
								return_arg_count,
								java_receiver_method_name,
								context);

    //System.out.println("Got handle from remote declare " + handle);
    
    // Store the g2_function handle for lookuplater
    //if (handle.intValue() >0 )
    // New RPC definition
    RPCDefinition rpcdef = new RPCDefinition();
    rpcdef.handle = handle;
    rpcdef.timeout = timeout;
    remoteRPCTable.put(g2_procedure_name, rpcdef);

    setRemoteRPCReturnKind (g2_procedure_name, PASS_BY_HANDLE);

    if (fulldebug){
    	System.out.println(remoteRPCTable);
    }
    
  }


		
  /**
   * Asynchronous calls, to be redesigned...private for now (mdg)
   *
   * Call A predeclared G2 procedure and return immediately
   *
   * <P>The G2 procedure is called asynchronusly, any return values
   * are returned by G2 calling a specified G2Gateway method.
   * The G2 procedure must have been predeclared by <B>declareRemoteRPC</B>.
   *
   * @param g2_procedure_name  The name of the predeclared G2 procedure to call.
   * @param items  The array of objects to send as arguments.
   */
  private void callRPCAsynchronous (Symbol g2_procedure_name,
				    Object items[])
  {
    if (_nativeInterface == null)
      throwNotInitializedException();

    if (!_connectionAlive)
      throwConnectionNotAliveException();

    //System.out.println("in callRPC" + items.toString() + g2_procedure_name.toString());
    RPCDefinition rpcdef = (RPCDefinition)remoteRPCTable.get(g2_procedure_name);
    
    if (rpcdef == null)
      throw(new
	    G2RemoteRPCNotPredeclaredException(
					       "G2 RPC " + g2_procedure_name + " Not predeclared"));

    else _nativeInterface.callRPCAsynchronous(rpcdef.handle, items, context);
  }


  /**
   * Call a predeclared G2 procedure/method synchronously (wait until then call returned or
   * a timeout).
   * The current thread will wait until the remote G2 has executed.
   * <P>To call a G2 method the first argument in args must be a G2 Item of the
   * appropriate class.</P>
   *
   * @param g2_procedure_name  The predeclared G2 procedure to call.
   * @param args   The Object array to pass to the G2 procedure/method as its arguments.
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   * @exception TimeoutException if the RPC takes longer than the default timeout period.
   * @Exception ConnecionNotAliveException when the Gateway is not currently connected to a G2.
   * @return The result of the G2 procedure/method.
   */
  @Override
  public Object callRPC (Symbol g2_procedure_name,
			 Object args[]) throws G2AccessException {


    long t0 = 0L;
    if (rpcTraceOn)
      t0 = System.currentTimeMillis();

    if (_nativeInterface == null)
      throwNotInitializedException();

    if (!_connectionAlive)
      throw new ConnectionNotAliveException();

    RPCDefinition rpcdef = (RPCDefinition)remoteRPCTable.get(g2_procedure_name);

    if (rpcdef == null) {
      // Automatically declare this RPC, so GSI does not moan
      declareRemoteRPC(g2_procedure_name, "asynchronousCatchAll", (int)timeOut);
      rpcdef = (RPCDefinition)remoteRPCTable.get(g2_procedure_name);
    }

    if (traceOn) {
      Trace.send(30, traceKey, i18nTrace, "g2gcallRPC",
		 g2_procedure_name, DebugUtil.printArray(args));
    }
    Object ret =  _nativeInterface.callRPC(rpcdef.handle, args, rpcdef.timeout, context);

    if (rpcTraceOn) {
        long t1 = System.currentTimeMillis();
        RPCTrace.addRPCTraceData(g2_procedure_name, args, (t1 - t0));

    }


    return ret;
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
   * @Exception ConnectionNotAliveException when the Gateway is not currently connected to a G2.
   * @return The result of the G2 procedure/method.
   */
  @Override
  public Object callRPC (Symbol g2_procedure_name,
			 Object args[],
			 int timeout) throws G2AccessException
  {

    long t0 = 0L;
    if (rpcTraceOn)
      t0 = System.currentTimeMillis();

    if (_nativeInterface == null)
      throwNotInitializedException();

    if (!_connectionAlive)
      throw new ConnectionNotAliveException();

    RPCDefinition rpcdef = (RPCDefinition)remoteRPCTable.get(g2_procedure_name);

    if (rpcdef == null) {
      // Automatically declare this RPC, so GSI does not moan
      declareRemoteRPC(g2_procedure_name, "asynchronousCatchAll", (int)timeOut);
      rpcdef = (RPCDefinition)remoteRPCTable.get(g2_procedure_name);
    }

    Object ret =  _nativeInterface.callRPC(rpcdef.handle, args, timeout, context);



    if (rpcTraceOn) {
        long t1 = System.currentTimeMillis();
        RPCTrace.addRPCTraceData(g2_procedure_name, args, (t1 -t0));
    }
    return ret;
  }



  /**
   * Start a predeclared remote G2 procedure, ignore any return values.
   * The method returns immediately.
   *
   * @param g2_procedure_name  The G2 procedure to call.
   * @param args  The array of objects to pass as arguments.
   */
  @Override
  public void startRPC(Symbol g2_procedure_name,
		       Object args[])
  {
    
    if (_nativeInterface == null)
      throwNotInitializedException();

    if (!_connectionAlive)
      throwConnectionNotAliveException();
	
    RPCDefinition rpcdef = (RPCDefinition)remoteRPCTable.get(g2_procedure_name);

    if (rpcdef == null) {
      // Automatically declare this RPC, so GSI does not moan
      declareRemoteRPC(g2_procedure_name, "asynchronousCatchAll", (int)timeOut);
      rpcdef = (RPCDefinition)remoteRPCTable.get(g2_procedure_name);
    }

    _nativeInterface.startRPC(rpcdef.handle, args, context);
  }


  /**
   * Indicates whether this thread can successfully call an RPC synchronously
   * If this call returns false, then a call to <code>callRPC</code> will throw
   * an Exception.
   * @return true if synchronous RPC calls are allowed in the current Thread,
   *   false otherwise.
   */
  @Override
  public boolean canCallRPC () {
    return (!JGInterface.inCallbackThread ());
  }


  /**
   * Set the value type of the return type of an Item from a remote RPC call.
   * G2 Items are returned BY_HANDLE by default in JavaLink.
   * @param g2_procedure_name The name of the procedure
   * @param return_value_type either PASS_BY_COPY or PASS_BY_HANDLE
   */
  @Override
  public void setRemoteRPCReturnKind (Symbol g2_procedure_name,
				      int return_value_type)
  {
    if (_nativeInterface == null)
      throwNotInitializedException();

    if (!_connectionAlive)
      throwConnectionNotAliveException();

    RPCDefinition rpcdef = (RPCDefinition)remoteRPCTable.get(g2_procedure_name);

    if (rpcdef == null) {
      // Automatically declare this RPC, so GSI does not moan
      declareRemoteRPC(g2_procedure_name, "asynchronousCatchAll", (int)timeOut);
      rpcdef = (RPCDefinition)remoteRPCTable.get(g2_procedure_name);
    }
  
    _nativeInterface.setRemoteRPCReturnKind(rpcdef.handle,
                                            -1,
					    return_value_type,
                                            context);
  }

  /**
   * This method allows groups of "by-handle" items to have their attributes updated "in-place".
   * JavaLink will update the items as a group using one remote call to G2. 
   * Note, all Items updated by this call must have been downloaded from this
   * connection.
   * @param items The "by-handle" items referring to items in the G2 across this connection
   * @param attributesArray Structure containing values of named attributes to be overwritten. 
            Set null for no attributes changes.
   * @param values If the items are Gsi-Variables, this array contains the new values for the 
   *               each variable. Set to null if the items are not Gsi-Variables.
   * @param statusValues If the items are Gsi-Variables, this arrat contains the new status for
   *               each variable, Set to null if the items are not Gsi-Variables.
   * @undocumented
   */
  @Override
  public void returnValues(Item[] items, 
			  Structure[] attributesArray, 
			  Object[] values, 
			  int[] statusValues) {
    if (_nativeInterface == null)
      throwNotInitializedException();

    if (!_connectionAlive)
      throwConnectionNotAliveException();

    _nativeInterface.returnValues(items,
				  attributesArray,
				  values,
				  statusValues,
				  context);
  }

  /**
   * This method allows groups of "by-handle" GsiVariables to be updated.
   * JavaLink will update the GsiVariables as a group using one remote call to G2. 
   * Note, all Items updated by this call must have been downloaded from this
   * connection.
   * @param items The "by-handle" GsiVariables referring to items in the G2 across this connection
   * @param values This array contains the new values for the each variable.
   * @param statusValues This array contains the new status for each variable.
   * @undocumented
   */
  public void returnValues(Item[] items, 
			  Object[] values, 
			  int[] statusValues) {
    if (_nativeInterface == null)
      throwNotInitializedException();

    if (!_connectionAlive)
      throwConnectionNotAliveException();

    _nativeInterface.returnValues(items,
				  null,
				  values,
				  statusValues,
				  context);
  }


  /**
   * Switch on/off low level function call debugging to stdout.
   */
  static void setInterfaceFundebug(boolean state)
  {
    if (_nativeInterface == null)
      throwNotInitializedException();

    _nativeInterface.setFundebug(state);
  }

  /**
   * Switch on/off low level data conversion function call debugging to stdout.
   */
  static void setInterfaceConvdebug(boolean state)
  {
    if (_nativeInterface == null)
      throwNotInitializedException();

    _nativeInterface.setConvdebug(state);
  }

  /**
   * Switch on/off low level Interface detailed debugging to stdout.
   */
  static void setInterfaceFulldebug(boolean state)
  {
    if (_nativeInterface == null)
      throwNotInitializedException();

    _nativeInterface.setFulldebug(state);
  }

  /**
   * Switch on/off low level interface status, warning and error messages to stdout.
   *
   */
  static void setInterfaceOutput(boolean state)
  {
    if (_nativeInterface == null)
      throwNotInitializedException();

    _nativeInterface.setInterfaceOutput(state);
  }

  /**
   * Switch on/off low level function call debugging to stdout.
   */
  @Override
  public void setInterfaceDebugOptions (boolean debugState) {
    setInterfaceFulldebug(debugState);
    setInterfaceConvdebug(debugState);
    setInterfaceFundebug(debugState);
    setInterfaceOutput(debugState);
  }


  @Override
  public void setInterfaceDebugOptions (int level) {
    setInterfaceFundebug(level >= 1 ? true : false);
    setInterfaceConvdebug(level >= 2 ? true : false);
    setInterfaceFulldebug(level >= 3 ? true : false);
    setInterfaceOutput(level >= 1 ? true : false);
  }


  private G2ConnectionInfo g2ConnectionInfo;

  /** Returns a G2ConnectionInfo object that contains the information
   * that specifies the details of the Gateway's connection profile
   * with G2.
   */
  public G2ConnectionInfo getG2ConnectionInfo() {
    return g2ConnectionInfo;
  }



  /**
   * A non thread-safe enumeration of the open connections.
   * @return an Enumeration of all open connections
   * @undocumented For Gensym use only. Does not need to be public
   */
  public static Enumeration getConnections() {
    return openConnections.elements();
  }

  /**
   * Set the default connection info for this connection.
   * @param The new default G2ConnectionInfo
   */
  protected void setConnectionInfo(G2ConnectionInfo info) {
    g2ConnectionInfo = info;
  }

  /**
   * Try to initiate connection with a remote G2 process.
   *
   * <P>If the G2Gateway succeeds in establishing a connection with the remote
   * G2, then a new GSI-INTERFACE is created within G2. If the connection
   * is successful, then the conenction will inform all its G2ConnectionListeners
   * of a G2_CONNECTION_INITIALIZED event.
   *
   *@param info The G2ConnectionInfo defining the connection
   *@param timeout The length of time to wait for the connection
   *@return true if a connection was initiated successfully
   *@exception ConnectionTimedOutException If the connection takes longer than timeout
   *@exception G2AccessInitiationException If the connection could not be initiated for some reason
   */
  protected boolean initiateConnection(G2ConnectionInfo info)
    throws ConnectionTimedOutException, G2AccessInitiationException {
    
    setConnectionInfo(info);
    Boolean perm = info.getPermanent();
    /* Give the user a permanent connection if they make
       no preference. This allows access to disabled items.
       This is the one place where this decision is made -vkp, 1/27/98 */
    boolean isPerm = (perm == null ? true : perm.booleanValue());
    //System.out.println("NativeInitiation");
    
    String protocol = (info.getProtocol() == null ?
		       G2ConnectionInfo.GSI_PROTOCOL :
		       info.getProtocol());
    
    if (G2ConnectionInfo.GSI_PROTOCOL.equals(protocol)) {
      // First ensure the G2 library is started
      try {
	//System.out.println("Initializing");
	initialize();
      } catch (AlreadyInitializedException E) {
	//E.printStackTrace ();
      }
      startup();
    }
    
    String connHost = info.getHost();
    String connPort = info.getPort();
    boolean secure = info.getSecure();
    G2ConnectionNotificationFlag = false;
    G2ConnectionAbortedEvent = null;
//System.out.println ("G2 gateway opening connection: "+ this.uniqueIdent); System.out.flush ();
    boolean initiationStarted =
      _nativeInterface.initiateConnection(info.getInterfaceName(),
					  info.getGsiInterfaceClassName(),
					  isPerm,
					  "TCPIP",
					  connHost,
					  connPort,
					  info.getRpis(),
					  this,
					  this.uniqueIdent,
					  secure);
    
    //System.out.println("NativeInitiation Done");
    
    if (timeOut >= 0 ) {
      
      long systemTimeEnd = System.currentTimeMillis() + timeOut;
      if (initiationStarted) {
	// Poll until we have received a connection notification or timedout
	while(!G2ConnectionNotificationFlag &&
	      System.currentTimeMillis() <= systemTimeEnd) {
	  try {
	    Thread.sleep(500);  // 0.5s
	  } catch (InterruptedException ex) {}
	}
      } else
	throw new G2AccessInitiationException("Native connection initiation to "+ connHost + ":" + connPort +
					      " failed.  Possible need to call G2Gateway.setGSIContextLimit");
      if (G2ConnectionAbortedEvent != null) {
	_nativeInterface.deregisterContextObject(this);
       	ConnectionResolver.clearWrapper(this);
	throw new G2AccessInitiationException(G2ConnectionAbortedEvent.getMessage());
      }
      else if (!G2ConnectionNotificationFlag) {
	throw new ConnectionTimedOutException("G2 Connection InitiationTimeout Host:" + connHost + ",Port:" + connPort);
      }
    }
    
    String str = checkForHandleOK(0);
    
    if (str != null)
      throw new G2AccessInitiationException (str);
    
    //Synchronizing on the static openConnections member prevents any other 
    //connections from interfering and getting something stored twice.
    synchronized (openConnections) {
      if (initiationStarted && (findOpenConnection(info) == null))
	storeOpenConnection();
    }
    
    checkAndStoreVersion ();
    
    synchronized(info) {
      info.notifyAll();
    }

    return initiationStarted;
  }

  /**
   * Called early when connection is initialized
   */
  void setLoader (StubClassLoader loader) {
    this.loader = loader;
  }

  /**
   * @undocumented
   * Check for an authorization to see if has passed for this connection
   *@param type currently type = 0 (Javalink), type = 1 (JavaLink/Professional)
   *@return an error str if not authorized, or null if is authroized
   */
  public String checkForHandleOK(int type) {
    return _nativeInterface.checkForHandleOK(context, type);
  }

  private void checkAndStoreVersion () throws G2AccessInitiationException {
    try {
      Structure versionStruct = g2getVersionStructure();
      version = new G2Version(versionStruct);
    } catch (G2AccessException gae) {
      /* The likely reason is that we're connecting to an older G2 that
       * doesn't include this new RPC (7/99). Try the older string-based RPC instead. */
      try {
	String versionString = g2getBuildVersion();
	version = new G2Version(versionString);
      } catch (G2AccessException gae2) {
	Trace.exception (gae2, "Problem getting G2 version information" +
			 "\nProbably connecting to a old G2. Upgrade to 5.1 rev 0 or better");
	closeConnection ();
	throw new G2AccessInitiationException (gae2);
      }
    }
  
    G2Version minimumVersion = getMinimumVersion ();
    if (version.compareTo (minimumVersion) < 0) {
      closeConnection ();
      throw new G2AccessInitiationException ("Version mismatch. " + version + 
					     " is older than minimum required version " + 
					     minimumVersion);
    }
  }


  

  /**
   * Returns the version information for the G2 that
   * we are connected to. This includes the software version,
   * release level, and build identifier.
   * @return a Structure describing the remote G2 version.
   */
  public Structure g2getVersionStructure() throws G2AccessException {
    return (Structure) callRPC (G2_GET_STRUCTURED_VERSION_, new Object[] {} );
  }

  /**
   * Returns the build identification string for the G2 that
   * we are connected to. This includes the software version,
   * platform, and the build identifier.
   * @return a String describing the remote G2 version.
   */
  public String g2getBuildVersion () throws G2AccessException {
    return (String) callRPC (G2_GET_BUILD_VERSION_, new Object[] {});
  }

  /**
   * The oldest version of G2 at the other end
   * of a G2Gateway connection. This can change on every
   * release of JavaLink.
   */
  public static final G2Version G2_MINIMUM_VERSION = new G2Version (5, 1, "Rev", 0, "H15");

  /**
   * Returns the mininum version of G2 that we are allowed to
   * make a connection to. This can be overriden by subclasses
   * to indicate that those type of connections may only be made
   * to newer versions of G2. It is not a good idea to specify
   * an version older than that specified by a superclass.
   * @return a G2Version describing the oldest G2 we expect to talk to
   */
  public G2Version getMinimumVersion () {
    return G2_MINIMUM_VERSION;
  }

  /**
   * @undocumented
   */
  @Override
  public G2Version getG2Version () {
    return version;
  }

  /**
   * Returns the FIRST connection whose G2ConnectionInfo matches()
   * the given G2ConnectionInfo.
   * @see com.gensym.jgi.G2ConnectionInfo#matches
   */
  protected static G2Connection findConnection(G2ConnectionInfo connectionInfo) {
    for (Enumeration en = getConnections(); en.hasMoreElements();) {
      G2Connection cnxm = (G2Connection)en.nextElement();
      G2ConnectionInfo info = null; //= cnxm.getG2ConnctionInfo();
      if (connectionInfo.matches(info))
	return cnxm;
    }

    return null;
  }

  /**
   * Looks for a connection with a given "profile" and returns it, if found.
   * otherwise, creates a new connection and initiates the connection.
   * @exception ConnectionTimedOutException when a new connection is not initiated within
   *   the default timeout
   * @exception G2AccessInitiationException Indicates some error occured
   *   during the connection attempt.
   */
  public static G2Connection getOrMakeConnection (String host, String port)
       throws ConnectionTimedOutException, G2AccessInitiationException {
       
  return getOrMakeConnection(null, host, port);
  }

  /**
   * Looks for or creates a connection with given url, host, and port.
   * A newly created connection connects to the broker specified by
   * <code>brokerURL</code>, then
   * requests that broker to connect to the G2 on <code>host</code>
   * that is listening at <code>port</code>.
   * Currently, the <code>host</code> is resolved by the broker, not
   * by the client.
   * @exception ConnectionTimedOutException when a new connection is not initiated within
   *   the default timeout
   * @exception G2AccessInitiationException Indicates some error occured
   *   during the connection attempt.
   */
  public static G2Connection getOrMakeConnection(String brokerURL,
						 String host, String port)
    throws ConnectionTimedOutException, G2AccessInitiationException {
      G2ConnectionInfo info =
	new G2ConnectionInfo(brokerURL, host, port,
			     (brokerURL == null ?
			      DEFAULT_TWO_TIER_CLASS_NAME : DEFAULT_RMI_CLASS_NAME),
			     DEFAULT_GSI_CLASS_NAME);
      //System.out.println("info: "+info+"  CALLING getOrMakeConnection with info");
      return getOrMakeConnection(info);
  }

  /**
   * Looks for a connection with a given "profile" and returns it, if found.
   * otherwise, creates a new connection and initiates the connection.
   * @exception ConnectionTimedOutException when a new connection is not initiated within
   *   the default timeout
   * @exception G2AccessInitiationException Indicates some error occured
   *   during the connection attempt.
   * @see G2ConnectionInfo
   */
  public static G2Connection getOrMakeConnection(G2ConnectionInfo info)
     throws G2AccessInitiationException, ConnectionTimedOutException {
    
  Trace.send(5, traceKey, i18nTrace, "g2ggetOrMakeConnection1", info);
  //System.out.println ("G2Gateway.getOrMakeConnection (" + info + ")");
  //System.out.flush ();
    
  G2Gateway cnxm = null;
  // If the connection is not to be forced then look for an
  // existing open connection that is sharable
  if (!info.isForceNew()) {
    G2ConnectionInfo other = findOrPutPendingConnection(info);
    if (other != null) {
      //Someone else is trying our connection, let's wait for them to finish and use that one.
        waitForPendingConnection(other);
    }

    cnxm = findOpenConnection(info);
  }

  Trace.send(5, traceKey, i18nTrace, info.toString());

  if (cnxm != null) {
    removePendingConnection(info);
    return cnxm;
  }    

  try {
    // Choose the class to make before deciding whether to
    // initialize() or not: don't want to in RMI case.
    Class connectionImplClass =
      chooseConnectionImplClass(info);
      
    cnxm = (G2Gateway)connectionImplClass.newInstance();
      
    Trace.send(5, traceKey, i18nTrace, "g2ggetOrMakeConnection2", cnxm);

    // This will be changed by initiateConnection
    cnxm.g2ConnectionInfo = info;

    // No new connection ....
    cnxm.initiateConnection(info);


  } catch (G2AccessInitiationException gaie) {
    throw gaie;
  } catch (Exception ex) {
    Trace.exception (ex);
    String mess = ex.getMessage();
    if (mess != null)
      throw new G2AccessInitiationException(ex, mess);
    else
      throw new G2AccessInitiationException(ex);
  } finally {
    removePendingConnection(info);
  }

    
  return cnxm;
  }

  private static void waitForPendingConnection(G2ConnectionInfo pendinginfo) {
    try {
      synchronized (pendinginfo) {
    	  long endTime = System.currentTimeMillis() + DEFAULT_CONNECTION_TIMEOUT;
    	  long remainingTime = DEFAULT_CONNECTION_TIMEOUT;
    	  while (remainingTime > 0){
    		  pendinginfo.wait(remainingTime);
    		  remainingTime = endTime - System.currentTimeMillis();
    	  }
      }
    } catch (java.lang.InterruptedException e) {
      Trace.exception (e, "thread interrupted while waiting for connection to finish: " + pendinginfo);
    }
  }

  /**
   * The name of the class used for the Gateway on the second tier
   * if no class is specified explicitly in the G2ConnectionInfo.
   */
  public static final String DEFAULT_TWO_TIER_CLASS_NAME = "com.gensym.jgi.G2Gateway";

  /**
   * The name of the class used for the Gateway on the third tier
   * if no class is specified explicitly in the G2ConnectionInfo.
   */
  public static final String DEFAULT_RMI_CLASS_NAME = "com.gensym.jgi.rmi.G2RMIClientImpl";

  /**
   * The name of the class used for the GSI-INTERFACE object in G2
   * if none is specified explicitly in the G2ConnectionInfo.
   */
  public static final String DEFAULT_GSI_CLASS_NAME = "GSI-INTERFACE";


  /**
   * Returns a subclass of G2Gateway, the choice of which
   * is based on
   * the <code>className</code> and <code>protocol</code> of
   * the G2ConnectionInfo object.
   * The Class object returned by this method must satisfy
   * <code>G2Gateway.class.isAssignableFrom(returnValue)</code>.
   * Otherwise an IllegalArgumentException will be thrown.
   *@exception ClassNotFoundException If the subClass can not be found
   */
  protected static Class chooseConnectionImplClass(G2ConnectionInfo info)
throws ClassNotFoundException {
  String className = info.getConnectionClassName();
  String protocol = info.getProtocol();

  if (className == null) {
    if (G2ConnectionInfo.RMI_PROTOCOL.equals(protocol)) {
      className = DEFAULT_RMI_CLASS_NAME;
    } else {
      className = DEFAULT_TWO_TIER_CLASS_NAME;
    }
  }
    
  Class returnValue = Class.forName(className);

  if (!G2Gateway.class.isAssignableFrom(returnValue))
    throw new IllegalArgumentException(className);

  return returnValue;
  }

  /** A non-synchronized access to the currently open connections */
  protected static Enumeration getOpenConnections() {
    return openConnections.elements();
  }

  /** Finds any stored connections that match with <code>info</code>.
   * Currently this is a linear search.*/
  protected static G2Gateway findOpenConnection(G2ConnectionInfo info) {
    synchronized (openConnections) {
      // If these lists ever get large we may want to optimize this:
      for (Enumeration en = getOpenConnections();
	   en.hasMoreElements();) {
	G2Gateway cnxm = (G2Gateway)en.nextElement();
	if (cnxm.matches(info))
	  return cnxm;
      }
      return null;
    }
  }

  private static void removeOpenConnection(G2ConnectionInfo info) {
    openConnections.remove(info);
  }
      
  /** Finds any prior connection attempt that matches <code>info</code>.
   * Currently this is a linear search.  If not found, stores <code>info</code>.
   * so that future connect attempts can match it.  Synchronized on
   * pendingConnections so that only one thread can be involved. */
  private static G2ConnectionInfo findOrPutPendingConnection(G2ConnectionInfo info) {
    synchronized (pendingConnections) {
      for (int i=0;i<pendingConnections.size();i++) {
	G2ConnectionInfo newinfo = (G2ConnectionInfo)pendingConnections.get(i);
	if (newinfo.matches(info))
	  return newinfo;
      }
      //Otherwise, we didn't find it, put ourselves in and say we lost.
      pendingConnections.addElement(info);
      return null;
    }
  }

  private static void removePendingConnection(G2ConnectionInfo info) {
    pendingConnections.remove(info);
  }

  /** The matches method is the preferred means of finding out whether
   *  a G2Gateway satisfies all the criteria of a G2ConnectionInfo.
   *  @see com.gensym.jgi.G2ConnectionInfo#matches
   */
  public boolean matches(G2ConnectionInfo info)
  {
    try {
      String desiredClassName = info.getConnectionClassName();
      if (g2ConnectionInfo == null)
	return false;
      else if (info == null || desiredClassName == null)
	return g2ConnectionInfo.matches(info);
      else
	{
	  Class desiredClass = Class.forName(desiredClassName);
	  return (g2ConnectionInfo.matches(info) &&
		  desiredClass.isInstance(this));
	}
    }
    catch (ClassNotFoundException cnfe)
      {
	return g2ConnectionInfo.matches(info);
      }
  }

  /** Stores the open connection in a place that can be found
   * by findOpenConnection */
  protected void storeOpenConnection() {
    openConnections.put(g2ConnectionInfo, this);
  }

  /**
   * Returns a short description of this connection
   * @return a String that contains the host and port info for this connection
   * @undocumented For Gensym use only. Used to display current connection in TW tool-bar.
   */
  @Override
  public String toShortString() {
    if (g2ConnectionInfo == null)
      return "?";
    else
      return (g2ConnectionInfo.getHost () + " : " + g2ConnectionInfo.getPort ());
  }
  
  /**
   * Returns a string that refers to this particular G2
   * @return a String describing this connection suitable for use in a URL
   * @undocumented For Gensym use only. Used to create G2 URLs
   */
  @Override
  public String toURLString() {
    if (g2ConnectionInfo == null)
      return "?";
    else
      return ("g2://" + g2ConnectionInfo.getHost () + ":" + g2ConnectionInfo.getPort ());
  }


  /**
   * This method will preload and initialize a given array of G2 classes.
   * Loading and initializing G2 classes can sometimes be time consuming.
   * This method can be used to preload a number of known classes (optionally
   * within an independent thread).
   * @param g2ClassNames An array of known G2 class names to load
   * @param createThread set true to preload in an independent thread
   */
  public void preloadG2Classes(Symbol[] g2ClassNames, boolean createThread) {
    if (_nativeInterface == null)
      throwNotInitializedException();

    if (!_connectionAlive)
      throwConnectionNotAliveException();   

    G2ClassPreloader preloader = new G2ClassPreloader(getCurrentStubLoader(), g2ClassNames);
    if (createThread)
      preloader.start();
    else
      preloader.preloadG2Classes();
  }

  /**
   * Return the Stub Loader for a native connection.
   */
  private StubClassLoader getCurrentStubLoader() {
    if (loader == null) {
      if (_nativeInterface == null)
	throw new RuntimeException ("Stub Loader not installed for non-native connections");

      G2StubFactory stubFactory = _nativeInterface.getStubFactory(context);
      
      if (stubFactory == null)
	throw new Error ("G2 Stub Factory not installed for" + context);
      loader = stubFactory.getStubClassLoader();  
    } 
      
    return loader;
  }

  /**
   * @undocumented
   */
  protected void clearModuleMappings() {
    if (makesOwnStubs())
      getCurrentStubLoader().loseModuleMappings();
  }

  /**
   * @undocumented
   */
  public Symbol[] getClassesReceived () {
    return loader.getStubClasses ();
  }

  /**
   * @undocumented
   */
  protected static final Class SYMBOL_CLASS = Symbol.class;
  /**
   * @undocumented
   */
  protected static final Class ITEM_CLASS = Item.class;
  /**
   * @undocumented
   */
  protected static final Class SEQUENCE_CLASS = Sequence.class;
  /**
   * @undocumented
   */
  protected static final Class OBJECT_CLASS = Object.class;

  /**
   * Private Initialize of Local RPC's used for this connection of class.
   * This method will only be called once just before the first G2InitializeConnection
   * is called for a connection to this class
   * NOTE: Subclasses who override this method must call super.initializeLocalRPCs()
   */
  private void privateInitializeLocalRPCs()
  {
    registerJavaMethod (this, "setInterfaceFundebug", Symbol.intern("JGI-SET-FUNDEBUG"));
    registerJavaMethod (this, "setInterfaceFulldebug", Symbol.intern("JGI-SET-FULLDEBUG"));
    registerJavaMethod (this, "setInterfaceOutput", Symbol.intern("JGI-SET-INTERFACEOUTPUT"));

    // Introspection callback
    
    try {

      Method handleSubsMethod =
	G2Gateway.class.getDeclaredMethod("HANDLESUBSCRIPTIONS",
					  new Class[] {SYMBOL_CLASS,
							 ITEM_CLASS,
							 SEQUENCE_CLASS,
							 OBJECT_CLASS,
							 OBJECT_CLASS,
							 Integer.TYPE});

      registerJavaMethod (this, handleSubsMethod, HANDLESUBSCRIPTIONS_, false);

    } catch (NoSuchMethodException e) {
      // This is serious
      System.err.println("Cant Find HANDLESUBSCRIPTIONS Method !!! ");
      e.printStackTrace();
      throw new Error("Cant Find HANDLESUBSCRIPTIONS Method in G2Gateway");
    }
  }


  /**
   * Initialize all Local RPC's used for this class connection.
   * This method will only be called once just before the first G2InitializeConnection
   * is called for a connection to this class
   */
  protected void initializeLocalRPCs()
  {
  }


  /**
   * Private Intialize all Remote G2 RPC's needed for a connection.
   * This method will be called just before G2InitializeConnection is called
   */
  private void privateInitializeConnectionRPCs()
  {

    // Introspection API

    // Set return types for procedures returning items 2/4/97
    setRemoteRPCReturnKind (G2_GET_UNIQUE_NAMED_ITEM_, PASS_BY_HANDLE);
    setRemoteRPCReturnKind (G2_SUBSCRIBE_TO_ITEM_, PASS_BY_HANDLE);
    setRemoteRPCReturnKind (G2_SUBSCRIBE_TO_ITEM_MULTIPLE_, PASS_BY_HANDLE);
    setRemoteRPCReturnKind (G2_GET_FROM_ITEM_, PASS_BY_HANDLE);
    setRemoteRPCReturnKind (G2_GET_FROM_ITEM_MULTIPLE_, PASS_BY_HANDLE);
    setRemoteRPCReturnKind (G2_GET_STRICT_INSTANCES_OF_CLASS_, PASS_BY_HANDLE);
    setRemoteRPCReturnKind (G2_GET_DIRECT_SUBCLASSES_, PASS_BY_HANDLE);
    setRemoteRPCReturnKind (G2_CREATE_ITEM_, PASS_BY_HANDLE);
    // For G2 proxy support
    declareRemoteRPC (jgiCreateClassAndReturnProxy_,
		      "asynchronousCatchAll", G2APITimeout);

    setRemoteRPCReturnKind (jgiCreateClassAndReturnProxy_, G2Gateway.PASS_BY_HANDLE);

  }

  /**
   * Initialize all Remote G2 RPC's needed for a connection.
   * This method will be called just before G2InitializeConnection is called.
   * Users should never need to call this directly.
   * NOTE: Subclasses who override this method must call super.initializeConnectionRPCs()
   */
  protected void initializeConnectionRPCs()
  {
    setRemoteRPCReturnKind (G2_GET_CONNECTION_INPUT_AND_OUTPUT_, PASS_BY_HANDLE);
    setRemoteRPCReturnKind (G2_GET_CONTAINMENT_HIERARCHY_, PASS_BY_HANDLE);
    setRemoteRPCReturnKind (G2_GET_CURRENT_USER_MENU_CHOICES_, PASS_BY_HANDLE);
  }


  // Introspection API defintions - General API calls are defined in this class

  private static final Symbol HANDLESUBSCRIPTIONS_
  = Symbol.intern ("HANDLESUBSCRIPTIONS");
  private static final Symbol G2_GET_FROM_ITEM_
  = Symbol.intern ("G2-GET-FROM-ITEM");
  private static final Symbol G2_GET_FROM_ITEM_MULTIPLE_
  = Symbol.intern ("G2-GET-FROM-ITEM-MULTIPLE");
  private static final Symbol G2_CONCLUDE_IN_ITEM_
  = Symbol.intern ("G2-CONCLUDE-IN-ITEM");
  private static final Symbol G2_GET_UNIQUE_NAMED_ITEM_
  = Symbol.intern ("G2-GET-UNIQUE-NAMED-ITEM");
  private static final Symbol G2_GET_ITEM_WITH_UUID_
  = Symbol.intern ("G2-GET-ITEM-WITH-UUID");
  private static final Symbol G2_GET_TEXT_OF_ATTRIBUTE_
  = Symbol.intern ("G2-GET-TEXT-OF-ATTRIBUTE");
  private static final Symbol G2_GET_ATTRIBUTE_FROM_CLASS_
  = Symbol.intern("G2-GET-ATTRIBUTE-FROM-CLASS");
  private static final Symbol G2_GET_ATTRIBUTES_FROM_CLASS_
  = Symbol.intern("G2-GET-ATTRIBUTES-FROM-CLASS");
  private static final Symbol G2_GET_ATTRIBUTE_DESCRIPTIONS_OF_CLASS_
  = Symbol.intern("G2-GET-ATTRIBUTE-DESCRIPTIONS-OF-CLASS");
  private static final Symbol G2_SET_V5_MODE_
  = Symbol.intern("G2-SET-V5-MODE");
  private static final Symbol G2_SUBSCRIBE_TO_ITEM_
  = Symbol.intern("G2-SUBSCRIBE-TO-ITEM");
  private static final Symbol G2_UNSUBSCRIBE_TO_ITEM_
  = Symbol.intern("G2-UNSUBSCRIBE-TO-ITEM");
  private static final Symbol G2_SUBSCRIBE_TO_ITEM_MULTIPLE_
  = Symbol.intern("G2-SUBSCRIBE-TO-ITEM-MULTIPLE");
  private static final Symbol G2_UNSUBSCRIBE_TO_ITEM_MULTIPLE_
  = Symbol.intern("G2-UNSUBSCRIBE-TO-ITEM-MULTIPLE");
  private static final Symbol G2_SUBSCRIBE_TO_CLASS_
  = Symbol.intern("G2-SUBSCRIBE-TO-CLASS");
  private static final Symbol G2_UNIX_TIME_
  = Symbol.intern("G2-UNIX-TIME");
  private static final Symbol G2_UNIX_TIME_AT_START_
  = Symbol.intern("G2-UNIX-TIME-AT-START");
  private static final Symbol G2_GET_HOST_NAME_
  = Symbol.intern("G2-GET-HOST-NAME");
  private static final Symbol G2_GET_PORT_NUMBER_OR_NAME_
  = Symbol.intern("G2-GET-PORT-NUMBER-OR-NAME");
  private static final Symbol G2_GET_PORT_NUMBER_OR_NAME_GIVEN_INDEX_
  = Symbol.intern("G2-GET-PORT-NUMBER-OR-NAME-GIVEN-INDEX");
  private static final Symbol G2_GET_STRUCTURED_VERSION_
  = Symbol.intern("G2-GET-STRUCTURED-VERSION");
  private static final Symbol G2_GET_SOFTWARE_VERSION_
  = Symbol.intern("G2-GET-SOFTWARE-VERSION");
  private static final Symbol G2_GET_BUILD_VERSION_ 
  = Symbol.intern ("G2-GET-BUILD-VERSION");
  private static final Symbol G2_WARMBOOT_KB_
  = Symbol.intern("G2-WARMBOOT-KB");
  private static final Symbol G2_LOAD_KB_
  = Symbol.intern("G2-LOAD-KB");
  private static final Symbol G2_SET_G2_STATE_
  = Symbol.intern ("G2-SET-G2-STATE");
  private static final Symbol G2_GET_G2_STATE_
  = Symbol.intern ("G2-GET-G2-STATE");
  private static final Symbol G2_GET_STRICT_INSTANCES_OF_CLASS_
  = Symbol.intern ("G2-GET-STRICT-INSTANCES-OF-CLASS");
  private static final Symbol G2_GET_DIRECT_SUBCLASSES_
  = Symbol.intern ("G2-GET-DIRECT-SUBCLASSES");
  private static final Symbol G2_GET_CONTAINMENT_HIERARCHY_
  = Symbol.intern ("G2-GET-CONTAINMENT-HIERARCHY");
  private static final Symbol G2_GET_CURRENT_USER_MENU_CHOICES_
  = Symbol.intern ("G2-GET-CURRENT-USER-MENU-CHOICES");
  private static final Symbol G2_GET_CONNECTION_INPUT_AND_OUTPUT_
  = Symbol.intern ("G2-GET-CONNECTION-INPUT-AND-OUTPUT");
  private static final Symbol G2_CREATE_ITEM_
  = Symbol.intern ("G2-CREATE-ITEM");


  // G2 Proxy support
  private static final Symbol jgiCreateClassAndReturnProxy_ = Symbol.intern("JGI-CREATE-CLASS-AND-RETURN-PROXY");

  private static int G2APITimeout = 0; // indefinite

  // Holds subscription handles, created from a connection to a G2
  private Hashtable subscpnTable = new Hashtable ();

  private static boolean handleSubscriptionsDebugp = false;


  // Introspection API entry points

  /**
   * Creates a new Item in G2 and returns it
   * @param className a Symbol naming the class of the item to create
   * @exception G2AccessException if any error occurs while communicating
   *   with G2
   */
  @Override
  public Item createItem (Symbol className) throws G2AccessException {
    Object[] args = new Object[1];
    args[0] = className;
    return (Item)
      callRPC(G2_CREATE_ITEM_, args);
  }


  /**
   * Returns the item-or-value that is obtained by travesing the denotation from
   * the item as root.
   * @itm the root item
   * @denotation the denotation to traverse
   * @exception G2AccessException if any error occurs during communication or
   *   within the call
   * @undocumented For Gensym use only. Others should use com.gensym.classes.Item#getPropertyValue
   *   or other public methods.
   */
  @Override
  public Object getValue (Item itm,
			  Denotation denotation)
throws G2AccessException
  {
    //System.out.println ("getValue (" + itm + ", " + denotation + ") = ");
    //Thread.dumpStack();
    Object x = callRPC(G2_GET_FROM_ITEM_,  new Object[] {itm, denotation});
    //System.out.println ("gotValue = " + x);
    return x;
  }


  /**
   * Concludes the value at the place pointed to by the denotation
   * @itm the root item
   * @denotation the denotation to traverse
   * @value the new value for the place
   * @exception G2AccessException if any error occurs during communication or
   *   within the call
   * @undocumented For Gensym use only. Others should use com.gensym.classes.Item#setPropertyValue
   *   or other public methods.
   */
  @Override
  public boolean setValue (Item itm,
			   Denotation denotation,
			   Object value)
       throws G2AccessException
  {

    Boolean retnvalue = (Boolean)
      callRPC(G2_CONCLUDE_IN_ITEM_, new Object[] {itm, denotation, value});
    return retnvalue.booleanValue ();
  }


  /**
   * Warning, called directly from Native code...dont change signature without
   * changing native code.
   */
  com.gensym.classes.Item getG2Stub (Symbol className,
				     int handle,
				     G2Access context,
				     Structure attributes,
				     boolean incompleteStubConversion) {
    //System.out.println ("In G2Gateway::getG2Stub (" + className + ", " + handle + "...)");
    //System.out.println ("              will call factory method on " + JGInterface.currentFactory);
    if (JGInterface.currentFactory == null)
      throw new Error ("G2 Stub Factory not installed");
    try {
      //System.out.println ("Calling DefaultStubFactory::createG2Stub in thread " + Thread.currentThread ());

      //System.out.println ("In G2Gateway::getG2Stub (" + className + ", " + handle + "...)");
      //Thread.dumpStack ();

      // If there has already been an incomplete stub conversion, we must always
      // create deffered stubs, even if we can resolve now...as we must ensure all
      // attributes of any Items, get resolved.
      if (incompleteStubConversion)
	return new com.gensym.classes.DeferredStub (JGInterface.currentFactory,
						    className, handle, context, attributes);

      return JGInterface.currentFactory.createG2Stub (className, handle, context, attributes);
    } catch (StubCreationException sce) {
      // this is fine
    } catch (Throwable e) {
      // do we really need this catch clause? the prior one should
      // be the circumstances under which we make a stub.
      Trace.exception ((Exception)e, null);
    }
    com.gensym.classes.DeferredStub stub =
      new com.gensym.classes.DeferredStub (JGInterface.currentFactory,
					   className, handle, context, attributes);
    //System.err.println ("Error in createStub " + e + "\nCreating DeferredStub =>" + stub);
    return stub;
  }

  /**
   * Warning, called directly from Native code...dont change signature without
   * changing native code.
   */
  void invalidateG2Stub (int handle, G2Access connection /* this? */) {
    //System.out.println ("Invalidating G2 Stub #" + handle + " in context " + context);
    _nativeInterface.invalidateG2Stub (handle, context, connection);
  }


  /**
   * Return an Item that represents a G2 ITEM that is a proxy for a
   * Java Object.
   *
   *@param g2ProxyClass the G2 Class name, used to create an instance of a proxy
   * in the event that an existing proxy could not be found. Set null to
   * use the default G2 Class registered for the class of JavaObject.
   *@param g2ParentClass the G2 class created that will inherit from this G2 Class
   *@param javaObject the Java Object to create a proxy for.
   *@exception G2AccessException When there is a problem communicating with G2 or
   * a G2 Class could not be found to create the proxy ITEM
   */
  @Override
  public Item getG2ProxyForJavaObject(String g2ProxyClass,
				      Symbol g2ParentClass,
				      Object javaObject)
       throws G2AccessException
  {
    if (_nativeInterface == null)
      throwNotInitializedException();

    if (!_connectionAlive)
      throwConnectionNotAliveException();

    return _nativeInterface.getG2ProxyForJavaObject (this,
						     g2ProxyClass,
						     g2ParentClass, 
						     javaObject);
  }


  /**
   * Retrieves a specific named Item from a G2. Use this
   * method to get a "root" item after making a connection to G2.
   * @param itmClass a Symbol naming the class of the Item
   * @param itmName the name of the Item
   * @return the requested Item
   * @exception G2AccessException if any error occurs during communication or if
   *   no such Item exists
   */
  @Override
  public Item getUniqueNamedItem (Symbol itmClass,
				  Symbol itmName)
    throws G2AccessException {
    
    Object[] args = new Object[2];
    args[0] = itmClass;
    args[1] = itmName;
    Object returnValue = callRPC(G2_GET_UNIQUE_NAMED_ITEM_, args);
    if (Boolean.FALSE.equals(returnValue))
      throw new G2AccessException(i18n.format("noSuchG2Item",
					      new Object[]
					      {itmClass, itmName,
						 this}));
    return (Item)returnValue;
  }

  /**
   * Retrieves a specific Item with the specified uuid from a G2. Use this
   * method to get a "root" item after making a connection to G2.
   * Requires G2 version 6.0 or greater   
   * @param uuid a String specifying the uuid of the Item;
   * @return the requested Item
   * @exception G2AccessException if any error occurs during communication or if
   *   no such Item exists
   */  
  @Override
  public Item getItemWithUUID(String uuid)
       throws G2AccessException
  {
    
    Object[] args = new Object[1];
    args[0] = uuid;
    Object returnValue = callRPC(G2_GET_ITEM_WITH_UUID_, args);
    if (Boolean.FALSE.equals(returnValue))
      throw new G2AccessException(i18n.format("noSuchG2ItemWithUUID",
					      new Object[]
					      {uuid, this}));    
    return (Item)returnValue;
  }
  
  /**
   * @undocumented
   */
  @Override
  public String getAttributeAsText (Item itm,
				    Symbol slotName,
				    Symbol specificClassIfAny)
    throws G2AccessException {
 
    Object[] args = new Object[3];
    args[0] = itm;
    args[1] = slotName;
    args[2] =  (specificClassIfAny != null ?  specificClassIfAny : (Object)Boolean.FALSE);
    
    return (String) callRPC(G2_GET_TEXT_OF_ATTRIBUTE_, args);
  }

  /**
   * Returns the ClassManager used to manage classes for this connection.
   *
   */
  @Override
  public ClassManager getClassManager() {
    return classManager;
  }


  /**
   *
   * @undocumented obviously
   */
  public int getGenerationMode () {
    return getCurrentStubLoader().getGenerationMode ();
  }

  /**
   * @undocumented
   */
  public void setGenerationMode (int mode) {
    getCurrentStubLoader().setGenerationMode (mode);
  }

  /**
   * @undocumented
   */
  public boolean getForceDownload () {
    return getCurrentStubLoader().getForceDownload ();
  }

  /**
   * @undocumented
   */
  public void setForceDownload (boolean mode) {
    getCurrentStubLoader().setForceDownload (mode);
  }

  /**
   * Returns the interface Class corresponding to a particular G2 class
   * @param g2ClassName_ a Symbol naming the G2 class
   * @return The interface corresponding to <code>g2ClassName_</code>
   *   if that interface has already been loaded, <code>null</code> otherwise.
   */
  @Override
  public Class getInterfaceForG2Class (Symbol g2ClassName_) {
    return getCurrentStubLoader().getInterface (g2ClassName_);
  }

  /**
   * @undocumented
   */
  public void unloadClass(Symbol g2ClassName) {
    getCurrentStubLoader().unloadClass(g2ClassName); 
  }

  /**
   * @undocumented
   */
  public boolean makesOwnStubs() {
    return true; // in middle tier
  }

  /**
   * STUB METHOD. FOR INTERNAL USE ONLY.
   * Stores the interface by its G2 Class name symbol.
   * Will be properly hidden in later releases.
   * @param thisInterface should be an interface, not a class.
   * @deprecated
   * @undocumented
   */
  public void storeInterfaceForG2Class(Class thisInterface) {
  }

  /**
   * @undocumented For Gensym use only. Used by the stub loader to initialize class info
   */
  @Override
  public Object getClassAttributeValue (Symbol className,
					Symbol attrName)
       throws G2AccessException
  {

    Object[] args = new Object[2];
    args[0] = className;
    args[1] = attrName;
    return callRPC(G2_GET_ATTRIBUTE_FROM_CLASS_, args);
  }

  private static final int LONG_TIMEOUT = 3*60*1000; // 3 minutes
  /**
   * @undocumented For Gensym use only. Used by the stub loader to initialize class info
   */
  @Override
  public Structure getClassAttributeValues (Symbol className,
					    Sequence attrNames)
       throws G2AccessException
  {

    Object[] args = new Object[2];
    args[0] = className;
    args[1] = attrNames;
    //System.out.println(attrNames);
    return (Structure)callRPC(G2_GET_ATTRIBUTES_FROM_CLASS_, args, LONG_TIMEOUT);
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
  @Override
  public Sequence getAttributeDescriptions (Symbol className, Sequence attributeNames)
throws G2AccessException
  {
    Object[] args = new Object[2];
    args[0] = className;
    args[1] = attributeNames;
    return (Sequence)callRPC (G2_GET_ATTRIBUTE_DESCRIPTIONS_OF_CLASS_, args);
  }


  private boolean setV5Mode(boolean state)
throws G2AccessException
  {
    Object[] args = {new Boolean(state)};
    Boolean retnvalue = (Boolean)callRPC(G2_SET_V5_MODE_, args);
    return retnvalue.booleanValue();
  }

  /**
   * Returns the current system time in the connected G2
   * @return The current unix system time (elapsed since Jan 1, 1970) at the connected G2.
   * @exception G2AccessException When there is a problem communicating with G2
   */
  @Override
  public double g2UnixTime() throws G2AccessException {
    Object[] args = {};
    Double retnvalue = (Double)callRPC(G2_UNIX_TIME_, args);
    return retnvalue.doubleValue();
  }

  /**
   * Returns the time when G2 was started most recently.
   * @return The double value of the time when G2 was most recently started.
   * @exception G2AccessException When there is a problem communicating with G2
   */
  @Override
  public double g2UnixTimeAtStart() throws G2AccessException {
    Object[] args = {};
    Double retnvalue = (Double)callRPC(G2_UNIX_TIME_AT_START_, args);
    return retnvalue.doubleValue();
  }

  /**
   * Gets the host name of the machince on which the connected G2 is running on.
   * @return The machine's host name of the connected G2.
   * @exception G2AccessException When there is a problem communicating with G2
   */
  @Override
  public String g2GetHostName() throws G2AccessException {
    Object[] args = {};
    return (host = (String)callRPC(G2_GET_HOST_NAME_, args));
  }

  /**
   * Gets the TCP/IP port number or port name on which the connected G2 is listening for network connections.
   * @return The connected G2's listener TCP/IP port number or port name as a String.
   * @exception G2AccessException When there is a problem communicating with G2
   */
  @Override
  public String g2GetPortNumberOrName() throws G2AccessException {
    Object[] args = {};
    return (port = (String)callRPC(G2_GET_PORT_NUMBER_OR_NAME_, args));
  }

  /**
   * Returns the current port number or name based on a network type index.
   * @param index An integer of 1 or 2.
   * @return A Text string of the current port number or name.
   * @exception G2AccessException When there is a problem communicating with G2
   */
  @Override
  public String g2GetPortNumberOrNameGivenIndex(int index)
throws G2AccessException {
  Object[] args = {index};
  return (String)callRPC(G2_GET_PORT_NUMBER_OR_NAME_GIVEN_INDEX_, args);
  }

  /**
   * Gets the current version of the G2 Software.
   * @return A String value of the system and software version of the connected G2 process.
   * @exception G2AccessException When there is a problem communicating with G2.
   */
  @Override
  public String g2GetSoftwareVersion() throws G2AccessException {
    Object[] args = {};
    return (String)callRPC(G2_GET_SOFTWARE_VERSION_, args);
  }

  /**
   * Returns the current run state of G2.
   * @return a symbol that is one of RUNNING, PAUSED, or RESET
   * @exception G2AccessException if any error occurs during communication
   *   with G2
   * @see #setG2State
   * @see #RUNNING_
   * @see #PAUSED_
   * @see #RESET_
   */
  @Override
  public Symbol getG2State() throws G2AccessException {
    if (currentG2State == null) {
      Object[] args = {};
      currentG2State = (Symbol) callRPC(G2_GET_G2_STATE_, args);
    } 
    return currentG2State;
  }

  /**
   * Sets the run state of G2. In order to restart G2, first change to
   * RESET then change to RUNNING.
   * @param the desired new state of G2. This should be one of the following
   *   Symbols - RUNNING, PAUSED, or RESET
   * @exception G2AccessException if any error occurs during communication
   *   with G2
   * @see #getG2State
   * @see #RUNNING_
   * @see #PAUSED_
   * @see #RESET_
   */
  @Override
  public Symbol setG2State (Symbol newState) throws G2AccessException {
    if (!((RUNNING_.equals(newState))||(PAUSED_.equals(newState))||
	  (RESET_.equals(newState)))) throw new IllegalArgumentException();
    Object[] args = {newState};
    return (Symbol)
      callRPC(G2_SET_G2_STATE_, args);
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
  @Override
  public Sequence getStrictInstancesOfClass (Symbol g2ClassName_) throws G2AccessException {
    Object[] args = { g2ClassName_ };
    return (Sequence) callRPC (G2_GET_STRICT_INSTANCES_OF_CLASS_, args);
  }

  /**
   * Retreives the names of all direct subclasses of a given class.
   * Use this method recursively to gather all subclasses of a given class.
   * @param g2ClassName_ a Symbol naming a class
   * @return a Sequence of Symbols naming the direct subclasses
   * @exception G2AccessException if there any errors during communication or within the call
   */
  @Override
  public Sequence getDirectSubclasses (Symbol g2ClassName_) throws G2AccessException {
    Object[] args = { g2ClassName_ };
    return (Sequence) callRPC (G2_GET_DIRECT_SUBCLASSES_, args);
  }


  /**
   * Return the subscription table for use by subclasses
   *
   * @undocumented
   */
  protected Hashtable getSubscpnTable () {
    return subscpnTable;
  }

  private static final Symbol SUBSCRIPTION_HANDLE_ = Symbol.intern ("SUBSCRIPTION-HANDLE");

  /**
   * @param itm The item for which updates are being requested.
   * @param denotation a sequence specifying the path from itm to the place being observed
   * @param userData any user-defined data included in the callback
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   *
   * @undocumented
   */
  @Override
  public Structure subscribeToItem (Item itm, Sequence denotation, java.lang.Object userData) throws G2AccessException {
    //JGInterface.setFulldebug (true);
    Structure subscrpnData = subscribeToItem(itm, denotation, HANDLESUBSCRIPTIONS_, userData);
    Structure bogusData =  subscribeToItem(itm, new com.gensym.util.AttributeDenotation(Symbol.intern("NAMES")), HANDLESUBSCRIPTIONS_, userData);
    Integer subscrpnHandle = (Integer)subscrpnData.getAttributeValue (SUBSCRIPTION_HANDLE_, null);
    subscpnTable.put(subscrpnHandle, itm);
    //System.out.println ("subscribeToItem (" + itm + ", " + denotation + ") = " + subscrpnData);
    return subscrpnData;
  }


  /**
   *
   *@undocumentated
   */
  protected Structure subscribeToItem(Item itm,
				      Sequence denotation,
				      Symbol callback,
				      Object userData) throws G2AccessException
  {
    Object[] args = {itm, denotation, callback, userData ,
                     Boolean.FALSE };
    //System.out.println("subscribing to " + denotation + " for " + itm);
    Structure retnvalue = (Structure)callRPC(G2_SUBSCRIBE_TO_ITEM_, args);
    //System.out.println("Got back " + retnvalue);
    return retnvalue;
  }

  /**
   * @param itm The item for which updates are being requested.
   * @param denotations a sequence specifying the path from itm to the place being observed
   * @param userData any user-defined data included in the callback
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   *
   * @undocumented
   * @author fy 02/22/00
   */
  @Override
  public Sequence subscribeToItemMultiple (Item itm, Sequence denotation_sequences, java.lang.Object userData) throws G2AccessException {
    Sequence subscrpnData = subscribeToItemMultiple(itm, denotation_sequences, HANDLESUBSCRIPTIONS_, userData);
    for (int i=0; i < subscrpnData.size(); i++) {
        Integer subscrpnHandle = (Integer)((Structure) subscrpnData.get(i)).getAttributeValue (SUBSCRIPTION_HANDLE_, null);
        subscpnTable.put(subscrpnHandle, itm);
    }
    return subscrpnData;
  }

  /**
   *
   *@undocumentated
   *@author fy 02/22/00
   */
  protected Sequence subscribeToItemMultiple(Item itm,
					     Sequence denotation_sequences,
					     Symbol callback,
					     Object userData) throws G2AccessException
  {
    //Denotations here is a Sequence of denotation sequences
    Object[] args = {itm, denotation_sequences, callback, userData ,
                     Boolean.FALSE };
    //System.out.println("subscribing to " + denotation + " for " + itm);
    Sequence retnvalue = (Sequence)callRPC(G2_SUBSCRIBE_TO_ITEM_MULTIPLE_, args);
    //System.out.println("Got back " + retnvalue);
    return retnvalue;
  }

  /**
   * Removes a subscription.
   * @param subscrpnHandle the Integer obtained from subscribeToItem
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   * @return a boolean specifying whether the unsubscribe was successful
   *
   * @undocumented
   */
  @Override
  public boolean unsubscribeToItem (int subscrpnHandle) throws G2AccessException {
    Item itm = (Item) subscpnTable.remove (subscrpnHandle);
    if (itm != null && itm.isValid()) {
      if (_connectionAlive) {
	Object[] args = {subscrpnHandle};
	callRPC(G2_UNSUBSCRIBE_TO_ITEM_, args);
      }
      return true;
    } else
      return false;
  }

  /**
   * Removes a set of subscriptions.
   * @param subscrpnHandles the array of Integers obtained from subscribeToItem
   * @exception G2AccessException when a problem occurs as a result of calling this RPC in G2.
   * @return a boolean specifying whether the unsubscribe was successful
   *
   * @undocumented
   * @author fy 02/22/00
   */
  @Override
  public boolean unsubscribeToItemMultiple (Sequence handles) throws G2AccessException {
    for (int i=0; i < handles.size(); i++) {
       subscpnTable.remove ((Integer) handles.elementAt(i));
    }
    
    if (_connectionAlive) {
	Object[] args = { handles };
	callRPC(G2_UNSUBSCRIBE_TO_ITEM_MULTIPLE_, args);
        return true;
    } else
        return false;
  }

  /* Local RPCs that are callbacks for subscriptions
   */
  // -vkp, 10/26/97 Consider taking the context out of the Event

  Object HANDLESUBSCRIPTIONS (final Symbol modfnCode, final Item item, final Sequence denotation,
		  final Object newValue, final Object userData, final int subscriptionHandle) {

    //     System.out.println("HANDLESUBSCRIPTIONS " +modfnCode + " " +
    // 		       newValue + " " + userData +
    // 		       " " + itm + " " + subscriptionHandle);
	Item itemBean = item;
    if (traceOn) {
      Trace.send(10, traceKey, i18nTrace, "Received event2: {0}");
    }
    if (itemBean == null) {
      itemBean = (Item) subscpnTable.get (subscriptionHandle);
    }
    if (itemBean != null) // Workaround for bug while deleting connection from T2
      itemBean.processItemEvent(new ItemEvent(itemBean, modfnCode, itemBean, denotation,
					 newValue, userData, subscriptionHandle));
    return 5471962;
  }

  /*
   * The accepted way to get a G2Definition from the symbolic class-name
   * is context.getClassManager().getDefinition(className_). This method
   * exists to facilitate that API. If the requested defintion has not
   * been stored in the ClassManager, it invokes this method. On the
   * second tier, we force to get the stub-factory to get the definition.
   * Caution: the RMI subclasses must override this method, because
   * the native interface is not initialized on the 3rd tier. It
   * must ask its corresponding server to retrieve the Definition.
   */
  /**
   * Returns the definition Item for any G2 class
   * @exception G2AccessException when a problem occurs as a result
   *   of communicating with G2.
   * @undocumented
   */
  @Override
  public G2Definition getDefinition (Symbol g2ClassName_) throws G2AccessException {
    DefaultStubFactory stubFactory = (DefaultStubFactory)_nativeInterface.getStubFactory(context);
    return stubFactory.getOrLoadDefinition (g2ClassName_);
  }

  /**
   * @undocumented
   */
  public G2Definition getDefinition(int handle, int version) throws G2AccessException{
    throw new UnexpectedException(null, i18n.getString("badCallToGetDefinition"));
  }

  /**
   * Get the definition for this item
   * @undocumented
   */
  public G2Definition getDefinition(Item item) throws G2AccessException{
    throw new CorruptionException(null, "getDefinition(Item) incorrectly called in middle tier");
  }

  /**
   * Get the system inheritance for this item
   * @undocumented
   */
  public Sequence getSystemClassInheritancePath(G2Definition definition)
  throws G2AccessException {
    throw new CorruptionException(null, "getSystemClassInheritancePath(G2Definition) incorrectly called in middle tier");
  }

  //public void finalize() {
  //  System.out.println("Bye Bye " + this);
  //}

  /**
   * @undocumented Needs review by mdg before public release.
   * Determines if the Gateway passed in as an argument is connected to
   * the same G2 as this G2Gateway. If either Gateway is not "alive",
   * it returns false. It then allows for the trivial case of
   * the same Gateway. The next thing to do is to check the host
   * and port by calling the remote G2. It is better to do this
   * than to use the local G2ConnectionInfo which may contain
   * aliases or incomplete information. -vkp, 7/27/98
   */
  public boolean connectedToSameG2 (G2Gateway otherGateway) {
    if (!isAlive() || !otherGateway.isAlive ())
      return false;
    if (this.equals(otherGateway))
      return true;
    try {
      if (host == null)
	g2GetHostName ();
      if (otherGateway.host == null)
	otherGateway.g2GetHostName ();
      if (!(host.equals (otherGateway.host)))
	return false;
      if (port == null)
	g2GetPortNumberOrName ();
      if (otherGateway.port == null)
	otherGateway.g2GetPortNumberOrName ();
      if (!(port.equals (otherGateway.port)))
	return false;
    } catch (G2AccessException gae) {
      throw new com.gensym.util.UnexpectedException (gae, "Error while matching remote G2s");
    }
    return true;
  }

  /**
   *
   * @undocumented
   */
  public void appendProcedureTable (String fileName) {
    try {
      FileOutputStream fo = new FileOutputStream (fileName, true);
      dumpProcedureTable (fo);
      fo.close ();
      System.out.println ("Finished Appending Procedure Table!");
    } catch (IOException ie) {
      System.err.println (ie);
      Trace.exception (ie);
    }
  }

  private void dumpProcedureTable (OutputStream o) {
    PrintWriter pw = new PrintWriter (new OutputStreamWriter(o, Charset.defaultCharset()));
    pw.println ("\n\nProcedure table for context : " + toShortString () + "\n");
    Enumeration eKeys = remoteRPCTable.keys ();
    Enumeration eElts = remoteRPCTable.elements ();
    while (eKeys.hasMoreElements ()) {
      Symbol key = (Symbol) eKeys.nextElement ();
      RPCDefinition defn = (RPCDefinition) eElts.nextElement ();
      pw.println (defn.handle + "    " + key);
      
    }
    pw.flush ();
  }
}


