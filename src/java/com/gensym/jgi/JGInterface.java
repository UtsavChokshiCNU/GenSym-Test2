/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 JGInterface.java
 *
 *   Description: 
 *     Native Interface access to Gensym GSI Lib.
 *     Warning : native methods and stubs must be created for this class
 *     utilizing javah, If the class definition changes remake the native interface
 *     
 *
 *	 Author:
 *		M.D.Gribble		Feb/97
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
import java.io.StringWriter;
import java.io.PrintWriter;
import java.lang.reflect.Method;
import java.rmi.RemoteException;
import java.lang.reflect.InvocationTargetException;
import com.gensym.core.GensymApplication;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.util.Structure; 
import com.gensym.util.Symbol; 
import com.gensym.util.Sequence; 
import com.gensym.util.Dispatcher; 
import com.gensym.jgi.download.G2StubFactory;
import com.gensym.jgi.download.DefaultStubFactory;
import com.gensym.message.*;
import com.gensym.classes.Item;
import com.gensym.classes.DeferredStub;
import com.gensym.classes.ImplAccess;
import com.gensym.classes.G2__BaseImpl;
import com.gensym.jgi.dataservice.DataServiceEvent;
import com.gensym.jgi.Work;
import com.gensym.jgi.Return;


/**
 * This class provides a network connection to the GSI object library.
 * 
 *
 * <P>JGInterface utilizes a Java native interface to access
 * GSI libraries, therefore, your environment must be set up correctly
 * otherwise JGInterface will throw an UnsatisfiedLinkErrorException. Please
 * refer to your platforms installation notes.
 * 
 * @version 	1.2,  12 Jun 97
 *
 * @author M.D.Gribble
 * @author Vikram Pillai
 */
public class JGInterface extends Thread 
{

  static final int PASS_BY_HANDLE = 0;
  static final int PASS_BY_COPY = 1;
  static final int PASS_BY_COPY_WITH_HANDLE = 2;
  static final int PASS_BY_REFERENCE = 3;
  /** The default host: "localhost" */
  public static final String DEFAULT_HOST = "localhost";
  /** The default G2 port: "1111" */
  public static final String DEFAULT_PORT = "1111";

  static final boolean CALL_METHOD_IN_QUEUED_THREAD = true;
  static final boolean DONT_CALL_METHOD_IN_QUEUED_THREAD = false;
  static final boolean CALL_METHOD_OUTSIDE_GSI_THREAD = true;
  static final boolean DONT_CALL_METHOD_OUTSIDE_GSI_THREAD = false;
  static final boolean FORCE_RPC_RETURN_FOR_VOID = true;
  static final boolean DONT_FORCE_RPC_RETURN_FOR_VOID = false;

  // Cmdline options
  static final String DEBUG_GATEWAY_SWITCH_OPTION = "-debuggateway";
  static final String GSI_LISTENER_PORT_OPTION ="-tcpport";
  static final String GSI_TCPIP_EXACT_OPTION = "-tcpipexact";
  static final String GSI_NO_LISTENER_PORT_OPTION = "-nolistener";
  static final String LISTENER_PORT_OPTION = "-listenerport";
  static final String NO_LISTENER_OPTION = "-nolistener";
  static final String GSI_CERT_OPTION = "-cert";
  static final String GSI_SECURE_OPTION = "-secure";
  // Private attributes
 
  /**
   * PRIVATE - Java level debugging switch
   */
  boolean fulldebug = false;
  private static final MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.jgi", JGInterface.class);
  private static Resource i18n =
  Trace.getBundle("com.gensym.jgi.TraceMessages");
  public static final boolean traceOn = false;

  //if you change this initial value then you must also change the assumptions
  // in startupGSI
  static int gsiLoopThreadPriority = Thread.NORM_PRIORITY; 
  static GsiLoopThread gsiLoopThread = null;	// Thread to run GSI Run loop
  private static Hashtable g2_connections = new Hashtable();
  private static Hashtable g2_connections_object_ids = new Hashtable();
  private static Hashtable localRPCTable = new Hashtable();
  private static JGInterface jgi_interface = null; // There will only be one JGInterface
  private static Class g2connection_interface = null;
  private static String g2connection_interface_fullname = "com.gensym.jgi.G2Connection";
  private static volatile G2ConnectionHandlerFactory g2connection_handler_factory = null;
  private static volatile Method G2ConnectionDispatchMethod = null;
  private static volatile Method G2ConnectionDispatchDataServiceMethod = null;
  static Dispatcher methodDispatcher = new Dispatcher(); 
  private static boolean isInitialized = false;
  private static boolean gsiRunning = false;
  //static G2StubFactory factory = new com.gensym.util.DefaultStubFactory();

  // WARNING...currentFactory MUST only be set by calls to setCurrentContext() and
  //           this MUST only be called by native code...The native code
  //           only sets this factory when a change in current context is detected.
  static volatile G2StubFactory currentFactory;

  private static boolean stubFactorySet = false;
  //private static StubResolver stubResolver = new StubResolver(factory);
  private static final G2JavaStubController g2StubController  =  
                       com.gensym.jgi.rmi.G2RMIJavaStubControllerImpl.getG2JavaStubController();
                       // RMI version, as it "may" need to be exported, if a RMI client connects



  static synchronized void initialize() 
  {
    if(isInitialized)
      return;
    try
      {
	// We force these classes to be loaded to overcome a JDK1.2 problem
	// where these classes (and dependants) fail to initialize
	// correctly, if loaded as a result of a GSI/JNI callback, when they had
	// been loaded previoulsy as result of a non system classloader.
	Class x = DefaultStubFactory.class;
	Class y = G2__BaseImpl.class;

	/* we must load our native library or we can not function ! */
	System.loadLibrary("JgiInterface");
	Trace.send(1, traceKey, i18n, "jgiInitialize");
      } catch (UnsatisfiedLinkError e) 
	{
	  System.err.println("Please Ensure that JgiInterface Native LIBRARY/DLL is on your PATH");
	  System.err.flush ();
	  throw new RuntimeException(e);
	}
      
      // Open Gensym Application properties
      GensymApplication.initialize();

      isInitialized = true;  
  }



  /**
   * Creates a JGInterface.
   *
   */
  private JGInterface(String []args) 
  {

    initialize(); // ensure that the Native Library is loaded

    // The only gsi options we allow is listener port, nolistener, tcpipexact

    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);
    String []gsi_args;
    Vector gsiArgsVector = new Vector();
    boolean noListenerPort = cmdline.getSwitchValue (GSI_NO_LISTENER_PORT_OPTION);
    if (noListenerPort)
      gsiArgsVector.addElement(GSI_NO_LISTENER_PORT_OPTION);
    String listenerPort = cmdline.getOptionValue (LISTENER_PORT_OPTION);
    if (listenerPort != null) {
      gsiArgsVector.addElement(GSI_LISTENER_PORT_OPTION);
      gsiArgsVector.addElement(listenerPort);
    }
    listenerPort = cmdline.getOptionValue (GSI_LISTENER_PORT_OPTION);
    if (listenerPort != null) {
      gsiArgsVector.addElement(GSI_LISTENER_PORT_OPTION);
      gsiArgsVector.addElement(listenerPort);
    }
    boolean tcpipExact = cmdline.getSwitchValue (GSI_TCPIP_EXACT_OPTION);
    if (tcpipExact)
      gsiArgsVector.addElement(GSI_TCPIP_EXACT_OPTION);

    boolean secure = cmdline.getSwitchValue (GSI_SECURE_OPTION);
    if (secure)
      gsiArgsVector.addElement(GSI_SECURE_OPTION);

    String certificate = cmdline.getOptionValue (GSI_CERT_OPTION);
    if (certificate != null) {
      gsiArgsVector.addElement(GSI_CERT_OPTION);
      gsiArgsVector.addElement(certificate);
    }

    gsi_args = new String[gsiArgsVector.size()];
    for (int i = 0; i < gsi_args.length; i++) {
      gsi_args[i] = (String)gsiArgsVector.elementAt(i);
      //System.out.println(gsi_args[i]);
    }

    boolean option_debug = cmdline.getSwitchValue(DEBUG_GATEWAY_SWITCH_OPTION);

    // Startup the GSI interface, but not the gsi_run_loop
    startupGSI(gsi_args,option_debug);

    try {


    // Pre lookup G2Gateway methods
    // (mdg) I would have liked to use G2Connection/some interface here, but the gateway methods we
    // are calling need to be private...an Interface defines public interfaces only 
    Class g2connection_class = G2Gateway.class;
    Class g2JavaStubController_class  = G2JavaStubController.class;
    Class event_signature[] = {G2ConnectionEvent.class};   
    G2ConnectionDispatchMethod = 
      g2connection_class.getDeclaredMethod("dispatchG2ConnectionEvent",  event_signature );
    Class objectArrayClass = (new Object[0]).getClass();
    G2ConnectionDispatchDataServiceMethod =
      g2connection_class.getDeclaredMethod("dispatchDataServiceHandlerEvent", new Class[] 
					   { Object.class, Integer.TYPE, objectArrayClass} );

    // Predeclare direct stubController methods that can be called by G2 fast !
    // The reason, we are defining them here and not in G2Gateway, is that the creation and control
    // of Java objects from G2 is public to every G2 regardless of any G2Connections.
    // These are reserved RPC calls by JGI and these method names can not be called on any
    // G2Connection class from G2.

    Method method;

    {
      Class signature[] = { String.class, String.class }; 
      method = g2JavaStubController_class.getDeclaredMethod("loadJavaClass", signature );
      // Method called in its own thread, it may take a while !
      declareLocalRPC (g2StubController, method, Symbol.intern("JGI-LOAD-JAVA-CLASS") ,
		       DONT_FORCE_RPC_RETURN_FOR_VOID ,
		       CALL_METHOD_OUTSIDE_GSI_THREAD, 
		       DONT_CALL_METHOD_IN_QUEUED_THREAD);
    }

    {
      Class signature[] = { Item.class, String.class, Sequence.class };
      method = g2JavaStubController_class.getDeclaredMethod("newInstance", signature);
      declareLocalRPC( g2StubController, method, Symbol.intern("JGI-CREATE-JAVA-INSTANCE"), 
		       DONT_FORCE_RPC_RETURN_FOR_VOID, 
		       CALL_METHOD_OUTSIDE_GSI_THREAD , 
		       CALL_METHOD_IN_QUEUED_THREAD );
    }


    {
      Class signature[] = { Item.class, String.class, Sequence.class };
      method = g2JavaStubController_class.getDeclaredMethod("callMethod", signature);
      declareLocalRPC( g2StubController, method, Symbol.intern("JGI-CALL-JAVA-METHOD"),  
		       FORCE_RPC_RETURN_FOR_VOID, 
		       CALL_METHOD_OUTSIDE_GSI_THREAD,
		       CALL_METHOD_IN_QUEUED_THREAD);
    }

    

    {
      Class signature[] = { Item.class, String.class, Item.class, Sequence.class };
      method = g2JavaStubController_class.getDeclaredMethod("callMethod", signature);
      declareLocalRPC( g2StubController, method, Symbol.intern("JGI-CALL-JAVA-DECLARED-METHOD"),  
		       FORCE_RPC_RETURN_FOR_VOID, 
		       CALL_METHOD_OUTSIDE_GSI_THREAD,
		       CALL_METHOD_IN_QUEUED_THREAD);
    }

    {
      Class signature[] = { Item.class, String.class, Item.class, Symbol.class, Structure.class, Item.class };
      method = g2JavaStubController_class.getDeclaredMethod("callG2ItemListenerMethod", signature);
      declareLocalRPC( g2StubController, method, Symbol.intern("JGI-CALL-G2ITEM-LISTENER-METHOD"),  
		       DONT_FORCE_RPC_RETURN_FOR_VOID, 
		       CALL_METHOD_OUTSIDE_GSI_THREAD,
		       CALL_METHOD_IN_QUEUED_THREAD);
    }
    

    // callMethod RPC's have true for second to last parameter, to to tell the native interface
    // to always return a value to G2 RPC even when Java returns void
    // as CallMethod can call any method of any return type but is declared in G2
    // to always return something

    {
      Class signature[] = { Item.class, String.class,  String.class, Sequence.class };
      method = g2JavaStubController_class.getDeclaredMethod("callStaticMethod", signature);
      declareLocalRPC ( g2StubController, method, Symbol.intern("JGI-CALL-JAVA-STATIC-METHOD") , 
			FORCE_RPC_RETURN_FOR_VOID, 
			CALL_METHOD_OUTSIDE_GSI_THREAD,
			CALL_METHOD_IN_QUEUED_THREAD);
    }

    {
      Class signature[] = { Item.class, String.class,  String.class, Item.class, Sequence.class };
      method = g2JavaStubController_class.getDeclaredMethod("callStaticMethod", signature);
      declareLocalRPC ( g2StubController, method, Symbol.intern("JGI-CALL-JAVA-DECLARED-STATIC-METHOD") , 
			FORCE_RPC_RETURN_FOR_VOID, 
			CALL_METHOD_OUTSIDE_GSI_THREAD,
			CALL_METHOD_IN_QUEUED_THREAD);
    }

    {
      Class signature[] = { Item.class };
      method = g2JavaStubController_class.getDeclaredMethod("deleteInstance", signature );
      declareLocalRPC(g2StubController, method , Symbol.intern("JGI-DELETE-JAVA-INSTANCE"), 
		      DONT_FORCE_RPC_RETURN_FOR_VOID, 
		      CALL_METHOD_OUTSIDE_GSI_THREAD, 
		      CALL_METHOD_IN_QUEUED_THREAD );
    }

    {
      Class signature[] = { Item.class, String.class };
      method = g2JavaStubController_class.getDeclaredMethod("registerG2ClassWithJavaClass", signature );
      declareLocalRPC(g2StubController, method , Symbol.intern("JGI-REGISTER-G2-CLASS-AS-JAVAPROXY"), 
		      DONT_FORCE_RPC_RETURN_FOR_VOID, 
		      CALL_METHOD_OUTSIDE_GSI_THREAD, 
		      CALL_METHOD_IN_QUEUED_THREAD );
    }

    {
      Class signature[] = { String.class, Symbol.class, Boolean.TYPE };
      method = g2JavaStubController_class.getDeclaredMethod("getG2StubsForJavaClass", signature );
      declareLocalRPC(g2StubController, method , Symbol.intern("JGI-GET-G2-STUBS-FOR-JAVA-CLASS"), 
		      DONT_FORCE_RPC_RETURN_FOR_VOID, 
		      DONT_CALL_METHOD_OUTSIDE_GSI_THREAD , 
		      DONT_CALL_METHOD_IN_QUEUED_THREAD);
                      // Possible Very Large return - dont run in own thread
                      // Seems to hang GSI !!! - known gsi bug
    }



    {
      Class signature[] = { String.class, Symbol.class, Boolean.TYPE };
      method = g2JavaStubController_class.getDeclaredMethod("getG2StubsForJavaBeanClass", signature );
      declareLocalRPC(g2StubController, method , Symbol.intern("JGI-GET-G2-STUBS-FOR-JAVA-BEAN-CLASS"), 
		      DONT_FORCE_RPC_RETURN_FOR_VOID, 
		      DONT_CALL_METHOD_OUTSIDE_GSI_THREAD , 
		      DONT_CALL_METHOD_IN_QUEUED_THREAD);
                      // Possible Very Large return - dont run in own thread
                      // Seems to hang GSI !!! - known gsi bug
    }

    {
      Class signature[] = { String.class, Boolean.TYPE };
      method = g2JavaStubController_class.getDeclaredMethod("findStubHierarchyForjavaClass", signature );
      declareLocalRPC(g2StubController, method , Symbol.intern("JGI-FIND-STUB-HIERARCHY-FOR-JAVA-CLASS"),
		      DONT_FORCE_RPC_RETURN_FOR_VOID,
		      DONT_CALL_METHOD_OUTSIDE_GSI_THREAD ,
		      DONT_CALL_METHOD_IN_QUEUED_THREAD);
    }

    {
      Class signature[] = { Item.class, String.class, Integer.TYPE };
      method = g2JavaStubController_class.getDeclaredMethod("newArrayInstance", signature);
      declareLocalRPC( g2StubController, method, Symbol.intern("JGI-CREATE-JAVA-ARRAY-INSTANCE"), 
		       DONT_FORCE_RPC_RETURN_FOR_VOID, 
		       CALL_METHOD_OUTSIDE_GSI_THREAD , 
		       CALL_METHOD_IN_QUEUED_THREAD );
    }

        {
      Class signature[] = { Item.class, String.class, Sequence.class };
      method = g2JavaStubController_class.getDeclaredMethod("newArrayInstanceWithDimensions", signature);
      declareLocalRPC( g2StubController, method, Symbol.intern("JGI-CREATE-JAVA-ARRAY-INSTANCE-WITH-DIMENSIONS"), 
		       DONT_FORCE_RPC_RETURN_FOR_VOID, 
		       CALL_METHOD_OUTSIDE_GSI_THREAD , 
		       CALL_METHOD_IN_QUEUED_THREAD );
    }

    {
      Class signature[] = { Item.class, Integer.TYPE };
      method = g2JavaStubController_class.getDeclaredMethod("getArrayElement", signature );
      declareLocalRPC(g2StubController, method , Symbol.intern("JGI-GET-JAVA-ARRAY-ELEMENT"),
		      FORCE_RPC_RETURN_FOR_VOID,
		      CALL_METHOD_OUTSIDE_GSI_THREAD ,
		      CALL_METHOD_IN_QUEUED_THREAD);
    }

    {
      Class signature[] = { Item.class, Integer.TYPE, Object.class };
      method = g2JavaStubController_class.getDeclaredMethod("setArrayElement", signature );
      declareLocalRPC(g2StubController, method , Symbol.intern("JGI-SET-JAVA-ARRAY-ELEMENT"),
		      DONT_FORCE_RPC_RETURN_FOR_VOID,
		      CALL_METHOD_OUTSIDE_GSI_THREAD ,
		      CALL_METHOD_IN_QUEUED_THREAD);
    }

    {
      Class signature[] = { Item.class };
      method = g2JavaStubController_class.getDeclaredMethod("getArrayContents", signature );
      declareLocalRPC(g2StubController, method , Symbol.intern("JGI-GET-JAVA-ARRAY-CONTENTS"),
		      DONT_FORCE_RPC_RETURN_FOR_VOID,
		      CALL_METHOD_OUTSIDE_GSI_THREAD ,
		      CALL_METHOD_IN_QUEUED_THREAD);
    }

    {
      Class signature[] = { Item.class };
      method = g2JavaStubController_class.getDeclaredMethod("setArrayContents", signature );
      declareLocalRPC(g2StubController, method , Symbol.intern("JGI-SET-JAVA-ARRAY-CONTENTS"),
		      DONT_FORCE_RPC_RETURN_FOR_VOID,
		      CALL_METHOD_OUTSIDE_GSI_THREAD ,
		      CALL_METHOD_IN_QUEUED_THREAD);
    }

    } catch (NoSuchMethodException e) { 
    	System.err.println("Error Reported during creation of JGInterface " + e.toString());
        e.printStackTrace();
    } catch (DuplicateLocalRPCException e) { 
    	System.err.println("Error Reported during creation of JGInterface " + e.toString());
        e.printStackTrace();
    } catch (RuntimeException e) { 
    	System.err.println("Error Reported during creation of JGInterface " + e.toString());
    	e.printStackTrace();
    }
  }
 

  /**
   * initialize Gsi processing, Must be called before any JGInterface
   * can used.  This method initialises the GSI libraries and network
   * monitors.
   *
   * @param cmdline Standard GSI command line options as String[] (see GSI manual)
   */
  final synchronized void startupGSI(String []args, boolean option_debug)
  {
    

    if (traceOn) {
      Trace.send(1, traceKey, i18n, "Starting GSI!");
    }
		
    // start up gsi run loop thread	if not already running

    if (gsiLoopThread == null) {
      gsiLoopThread = new GsiLoopThread(this, args, option_debug);
      if (gsiLoopThreadPriority != Thread.NORM_PRIORITY)//assumes this is still the default
	gsiLoopThread.setPriority(gsiLoopThreadPriority);
      gsiLoopThread.start();
    }
  }

  /**
   *@undocumented
   */
  public static void setGSILoopThreadPriority(int priority)
       throws IllegalArgumentException
  {
    if (priority < Thread.MIN_PRIORITY ||
	priority > Thread.MAX_PRIORITY)
      throw new IllegalArgumentException("Thread priority of " + priority + " out of range");
    gsiLoopThreadPriority = priority;
    if (gsiLoopThread != null)
      gsiLoopThread.setPriority(gsiLoopThreadPriority);      
  }

  /**
   * Start up Gsi processings and network monitors...The gsi run loop
   */

  final synchronized void startup()
  {
    if (gsiRunning || gsiLoopThread == null)
      return;

    gsiLoopThread.enableRunLoop();

    gsiRunning = true;
  }

  






   /**
   * Sets the G2ConnectionHandlerFactory of an application. It can be called at most once 
   * by an application. A G2ConnectionHandlerFactory is responsible for selecting an
   * appropriate G2Connection for an incomming unsolicited (g2 initiated) G2 connection.<P>
   * Throws an Error if the factory has already been defined
   *
   * Note this method is not Static - to force a JGInterface to be created which starts up 
   * the GSI interface this allowing unsolicted connections
   *
   * @param fac the desired factory
   */
  final void setConnectionHandlerFactory(G2ConnectionHandlerFactory fac)
  {
    if (g2connection_handler_factory == null) {
      synchronized (JGInterface.class) {
        if (g2connection_handler_factory == null) {
          g2connection_handler_factory = fac;
        }
      }
    }
  }

  final void deregisterContextObject(G2Connection connection) {

    // Clear out references to G2Connection objects
    for (Enumeration e = g2_connections.keys(); e.hasMoreElements();) {
      Object ele = e.nextElement();
      if (g2_connections.get(ele).equals(connection)) {
	g2_connections.remove(ele);
      }
    }

    for (Enumeration e = g2_connections_object_ids.keys(); e.hasMoreElements();) {
      Object ele = e.nextElement();
      if (g2_connections_object_ids.get(ele).equals(connection)) {
	g2_connections_object_ids.remove(ele);
      }
    }

    clearMethodCallQueue(connection);
  }

  /**
   * Register a connection object associated with context number (a G2 connection)
   * will be called when a connection has been made
   * The association is made if context_object_id mathes the unique id of context_object
   */
  private final G2Connection registerContextObject(int context,
						   String remote_process_string, 
						   String connection_data)
       throws ClassNotFoundException
  {
    
    G2Connection context_object = ( connection_data != null ? 
				    (G2Connection)g2_connections_object_ids.get(connection_data)
				    : null);

    if (context_object == null) 
      {

      // Ask the G2Connection handler factory to find us a G2Connection
      if (g2connection_handler_factory != null)
	{
	  context_object = g2connection_handler_factory.createG2Connection(remote_process_string);

	  if (context_object == null)    
	    throw(new RuntimeException("No Java G2Connection object could be found for Attempted G2 Connection from the installed G2ConnectionHandlerFactory"));
	  else 
	    {
	      // Must make sure a Gateway has a ConnectionInfo for this unsolicted connection
	      if (context_object instanceof G2Gateway)
		if (((G2Gateway)context_object).getG2ConnectionInfo() == null)
		  ((G2Gateway)context_object).setConnectionInfo(new G2ConnectionInfo("", 
									  getRemoteHostNative(context),
									  "" + getRemotePortNative(context),
									  true,
									  false));
	      g2_connections.put(context, context_object);
	      return context_object;
	    }
	}
      else
	// No factory
	throw(new RuntimeException("No G2ConnectionHandlerFactory installed to handle unsolicited G2 connections"));

    } else 
      {
	g2_connections.put(context, context_object);
	if (fulldebug) {
		System.out.println("Found connection object " + context_object.toString());
	}

	return context_object;
    }
  }

  /**
   * Dispatch an event to a connection, outside the GSI thread
   */
  void dispatchG2ConnectionEvent(G2Connection connection,  
					 int context_num, 
					 G2ConnectionEvent event) {

    Object args[] = { event };
    invokeMethod(connection, 
		 G2ConnectionDispatchMethod, 
		 args, 
                 -1, 
		 false, 
		 CALL_METHOD_OUTSIDE_GSI_THREAD, 
		 DONT_CALL_METHOD_IN_QUEUED_THREAD,
		 false,
		 context_num);	
  }

void registerIncomingConnection(int context, 
							String remote_process_string, 
							String context_object_id)
{
    gsiLoopThread.enqueue(new Work_registerIncomingConnection(context, remote_process_string, context_object_id));
}

 /**
   * Called when a G2 process has just initiated a connection.
   *
   *
   * @return An object that is associated with the context and will accept callbacks
   *         from a connected G2
   *
   */
  //  synchronized  
void handleRegisterIncomingConnection (int context, 
							String remote_process_string, 
							String context_object_id) 
       throws Exception
  {    
    G2Connection context_object = null; 
    //try
    // {
    context_object =  registerContextObject(context, remote_process_string, context_object_id);
    // } catch (Exception E) {System.out.println(E.toString());}

    
    if (context_object != null) {
      ((G2Gateway)context_object).initializeInstance ();
      // To keep setConnectionID private, it can not be in the G2Connection interface.
      // We unfortunately, have to assume that we are always dealing with a G2Gateway
      ((G2Gateway)context_object).setConnectionID(context);
    }
    
    setupNewNativeConnection (context_object, context);

    nativeRegisterContextObject(context_object, context, remote_process_string);
  }

   /**
   * Called when a connection has been registered and has had authorization checks
   * , inform the G2 connection.
   *
   * <P>G2 calls <B>initializeConnection</B> each time you activate a GSI
   * Interface that specifies the machine name and port number on which the Java 
   * JGInterface instance is listening. It can also be called as a result 
   * of calling method <B>initiateConnection</B>.
   *
   * @return An object that is associated with the context and will accept callbacks
   *         from a connected G2
   *
   */
  void G2InitializeConnection (G2Connection connection,
						    int context, 
						    String remote_process_string) 

  {
    // invoke the initiate connection of the G2Connection in another thread
    G2ConnectionEvent event = new G2ConnectionEvent(connection, 
						    G2ConnectionEvent.G2_CONNECTION_INITIALIZED,
						    remote_process_string, 
						    false);
    
    gsiLoopThread.enqueue(new Work_dispatchG2ConnectionEvent(connection, context, event));
  }

 /**
   * Called when an initiate a connection to a G2 was aborted
   *
   */
  synchronized G2Connection G2InitializeConnectionAbort (String error_txt, String context_object_id)
  {    

    G2Connection context_object = null; 

    context_object = ( context_object_id != null ? 
				    (G2Connection)g2_connections_object_ids.get(context_object_id)
				    : null);
    if (context_object != null)
      {
	// invoke the initiate connection of the G2Connection in another thread
	G2ConnectionEvent event = new G2ConnectionEvent(context_object, 
						G2ConnectionEvent.G2_CONNECTION_ABORTED,
						error_txt, 
						false);

	dispatchG2ConnectionEvent(context_object, 0, event);
      }

    return context_object;
  }

 /** 
  * Called when a connected G2 closes an active connection.
  *
  * <P><B>G2ConnectionClosed()</B>is called when:
  *<P>
  * <LI>The connected G2 process disables, deactivates, or deletes the GSI
  * Interface
  * <LI> The connected G2 process changes the text of the
  * GSI-CONNECTION-CONFIGURATION attribute of the G2 GSI-INTERFACE that
  * is connected to a G2Gateway.
  * <LI>When the connected G2 is reset.
  * <LI>When a network error or failure causes the connection to the G2 process
  * to be lost.
  *
  *
  * <P>Do not try to send data to G2 or invoke any G2 procedures from this
  * method. By the time <B>G2ConnectionClosed()</B> is called, G2 has already
  * closed the network connection, or the connection has been lost due to
  * a network failure.
  */
  void G2ConnectionClosed(G2Connection connection, int context) 
  {
    synchronized (JGInterface.class) {
      // not needed anymore? -vkp, 5/23/98
      factoryTable[context].invalidateStubClassLoader(connection);
    }
    G2ConnectionEvent event = new G2ConnectionEvent(connection, 
					      G2ConnectionEvent.G2_CONNECTION_CLOSED,
					      "", 
					      false);
 

    gsiLoopThread.enqueue(new Work_dispatchG2ConnectionClose(connection, context, event));
  }

void handleG2ConnectionClosed(G2Connection connection, int context, G2ConnectionEvent event) {

    dispatchG2ConnectionEvent(connection, context, event);

    deregisterContextObject(connection);
    synchronized (JGInterface.class) {
      if (currentFactory .equals(factoryTable[context]))
        currentFactory = null;
      factoryTable[context] = null;
      stubResolverTable[context] = null;
    }
}

  /**
   * Called whenever a connected G2 process pauses
   * its current knowledge base (KB).
   *
   * <P>G2isPaused() is useful for pausing any methods/threads in a 
   * G2Gateway that operate asynchronously to G2. You can use 
   * G2isPaused() to suspend these functions until G2 resumes operation.
   */
  void G2isPaused(G2Connection connection, int context) 
  {
    G2ConnectionEvent event = new G2ConnectionEvent(connection, G2ConnectionEvent.G2_IS_PAUSED);
    gsiLoopThread.enqueue(new Work_dispatchG2ConnectionEvent(connection, context, event));
    
  }

  /** 
  * Called when a connected G2 process resumes its current knowledge base (KB).
  *
  * <P><B>G2isResumed</B> is called when a connected G2 process resumes running
  * its current knowledge base(KB). If a G2Gateway has any asynchronous 
  * operations  that are suspended by a call to <B>G2isPaused()</B>, you can
  * include code in G2isResumed() to resume those operations.
  *
  */
  void G2isResumed(G2Connection connection, int context) 
  {
    G2ConnectionEvent event = new G2ConnectionEvent(connection, G2ConnectionEvent.G2_IS_RESUMED);
    
    gsiLoopThread.enqueue(new Work_dispatchG2ConnectionEvent(connection, context, event));
  }
  
  /**
   * Called whenever a connected G2 process pauses
   * its current knowledge base (KB).
   *
   * <P>G2isPaused() is useful for pausing any methods/threads in a 
   * G2Gateway that operate asynchronously to G2. You can use 
   * G2isPaused() to suspend these functions until G2 resumes operation.
   */
  void G2isReset(G2Connection connection, int context) 
  {
    G2ConnectionEvent event = new G2ConnectionEvent(connection, G2ConnectionEvent.G2_IS_RESET);

    gsiLoopThread.enqueue(new Work_dispatchG2ConnectionEvent(connection, context, event));
    
  }

  /**
   * Called whenever a connected G2 process pauses
   * its current knowledge base (KB).
   *
   * <P>G2isPaused() is useful for pausing any methods/threads in a 
   * G2Gateway that operate asynchronously to G2. You can use 
   * G2isPaused() to suspend these functions until G2 resumes operation.
   */
  void G2isStarted(G2Connection connection, int context) 
  {
    G2ConnectionEvent event = new G2ConnectionEvent(connection, G2ConnectionEvent.G2_IS_STARTED);

    gsiLoopThread.enqueue(new Work_dispatchG2ConnectionEvent(connection, context, event));
    
  }

  /**
   * Called by G2 when a message is sent to a G2Gateway from a connected G2.
   *
   * <P><B>receiveMessage()</B> is called when a G2Gateway receives a message from a 
   * connected G2. G2 can sent a message by executing an inform action on a 
   * GSI-INTERFACE that is configured as a GSI message server.
   *
   * @param message  The message sent from G2.
   */
  void receiveMessage(G2Connection connection, int context, String message) 
  {
    G2ConnectionEvent event = new G2ConnectionEvent(connection, 
					    G2ConnectionEvent.G2_MESSAGE_RECEIVED, 
					    message, 
					    false);

    gsiLoopThread.enqueue(new Work_dispatchG2ConnectionEvent(connection, context, event));
  }

  /**
   * Called when the network cannot deliver data that Java is attempting to write to G2.
   *
   * @param state true - The network cannot deliver data, 
   *              false - The network can now deliver data once again
   */
  void writeCallback(G2Connection connection, int context, boolean state)
  {
    G2ConnectionEvent event = new G2ConnectionEvent(connection, 
					    G2ConnectionEvent.G2_WRITE_BLOCKAGE, 
					    null, 
					    state);

    gsiLoopThread.enqueue(new Work_dispatchG2ConnectionEvent(connection, context, event));
  }

  /**
   * Called when the network cannot deliver data that G2 is attempting to write to Java.
   *
   * @param state true - The network cannot deilver data,
   *              false - The network can now deliver data once again
   */
  void readCallback(G2Connection connection, int context, boolean state)
  {
    G2ConnectionEvent event = new G2ConnectionEvent(connection, 
					    G2ConnectionEvent.G2_READ_BLOCKAGE, 
					    null, 
					    state);

    gsiLoopThread.enqueue(new Work_dispatchG2ConnectionEvent(connection, context, event));
  }

  private void  dispatchDataServiceHandlerEvent(G2Connection connection, 
						int context, 
						Object data,
						Integer eventId,
						Object[] identifyingAttributes,
						boolean incompleteStubConversion) {
    // We shold really create an event her to contain this dispatch data
    // but we must make sure that an deferred stubs get resolved
    // which will not happen if we hide data in an event type

     invokeMethod(connection, 
		 G2ConnectionDispatchDataServiceMethod,
		 new Object[] { data, eventId, identifyingAttributes }, 
                 -1, 
		 false, 
		 CALL_METHOD_OUTSIDE_GSI_THREAD, 
		 CALL_METHOD_IN_QUEUED_THREAD,
		 incompleteStubConversion,
		 context);	
  }

  private static final Integer SET_DATA_ID_INTEGER_ = DataServiceEvent.SET_DATA_ID;
  private static final Integer GET_DATA_ID_INTEGER_ = DataServiceEvent.GET_DATA_ID;
  private static final Integer VARIABLE_REGISTRATION_ID_INTEGER_ = DataServiceEvent.VARIABLE_REGISTRATION;
  private static final Integer VARIABLE_DEREGISTRATION_ID_INTEGER_ = DataServiceEvent.VARIABLE_DEREGISTRATION;

  /** Called by native lib when a gsi_set_data called
   */
  void setData(G2Connection connection, 
	       int context, 
	       Item[] items, 
	       boolean incompleteStubConversion) {

    // dispatch the call (return any values ?)
    //System.out.println("setData called, with " + items.length + " in " + items[0]);
    dispatchDataServiceHandlerEvent(connection, 
				    context, 
				    items,
				    SET_DATA_ID_INTEGER_,
				    null,
				    incompleteStubConversion);
  }

  /** Called by native lib when a gsi_data_data called
   */
  void getData(G2Connection connection, int context, Item[] items, boolean incompleteStubConversion) {
    // Need to create a dispatch here that allows the return of 
    // Multiple values
    //System.out.println("getData called, with " + items.length + " in " + items);
    dispatchDataServiceHandlerEvent(connection, 
				    context, 
				    items, 
				    GET_DATA_ID_INTEGER_,
				    null,
				    incompleteStubConversion);
  }

  /** Called by the native lib when receive_registration called */
  void receiveRegistration(G2Connection connection, 
			   int context, 
			   Item item, 
			   Object[] identAtts,
			   boolean incompleteStubConversion) {
    //System.out.println("Got receiveRegistration with " + item );
    //for (int i=0; i<identAtts.length; i++)
    //  System.out.println("Atts" + " " + i + " " + identAtts[i]);

    dispatchDataServiceHandlerEvent(connection,
				    context,
				    item,
				    VARIABLE_REGISTRATION_ID_INTEGER_,
				    identAtts,
				    incompleteStubConversion);
				    
  }

  /**
   * Return the JGI Connection object that will deal with communications from G2
   * for this VM
   * @param cmdline options: -tcpport/-listenerport [number] -tcpipexact -nolistener
   */
  static final synchronized JGInterface getJGInterface(String []cmdline)
  {
    if (jgi_interface == null)
      jgi_interface = new JGInterface(cmdline);
    return jgi_interface;

  }
  /**
   * Try to initiate connection with a remote G2 process.
   *
   * <P>If the JGInterface succeeds in establishing a connection with the remote
   * G2, then a new GSI-INTERFACE is created within G2. If successful the
   * connected G2 will then attempt to call <B>G2InitializeConnection</B> method
   * on the callback object.
   *
   * @param interface_name  The name given to the GSI-INTERFACE created in G2(Optional)
   * @param class_name  The class of the GSI-INTERFACE created in G2(Optional)
   *      (must be a subclass of GSI-INTERFACE)
   * @param keep_connection  Dont delete the connect when the KB is reset (N/A)
   * @param network  Specify DECNET or TCPIP (default)
   * @param host  The host computer name running the G2 process (default localhost)
   * @param port  The network port to try use for the connection (default 1111)
   * @param rpis  The remote process identification string
   * @param callback_object The object that will be associated with the connection
   *                        if made
   */
  boolean initiateConnection(final String interface_name,
		  final String class_name,
		  final boolean keep_connection,
		  final String network,
		  final String host,
		  final String port,
		  final String rpis,
		  final G2Connection callback_object,
		  final String callback_identification,
                                                        boolean secure)
  {
    /* Record the objects identification */

    g2_connections_object_ids.put(callback_identification, callback_object);
  
    if (traceOn) {
      Trace.send(1, traceKey, i18n, class_name + network + host + port +
		    rpis + callback_identification);
    }

    String connHost = (host == null ? DEFAULT_HOST : host);
    String connPort = (port == null ? DEFAULT_PORT : port);
    String g2InterfaceName = (interface_name == null ? "NO-NAME" : interface_name);
    String g2ClassName = (class_name == null ? "GSI-INTERFACE" : class_name);
    String g2Rpis = (rpis == null ? "" : rpis);
  

    boolean res = initiateConnectionNative(g2InterfaceName.toUpperCase(),
    		     g2ClassName,
			     keep_connection,
			     network,
			     connHost,
			     connPort,
			     g2Rpis,
			     callback_identification,
                             secure);  

    /* Note when a G2 connects - the JGI interface will call registerContextObject */
    /* thus linking a GSI context with a the callback object */

    return res;
  }

  /** 
   * Shutdown an existing connection
   *
   * @param context - The context to close
   */
  final void closeConnection(int context) 
  {
 
    //System.out.println("Close for context : " + g2_connections.get(new Integer(context)));
    Object context_object = g2_connections.get(context);

    if (context_object != null)
      closeConnectionNative(context);
      
  }


 /**
   * Predeclare a method name on a target object so that is can be called by a connected G2.
   *
   * 
   */
  final void declareLocalRPC(G2Connection connection,
			     Object target,
			     String java_method_name, 
			     Symbol g2_RPD_name, 
			     boolean run_in_queued_thread ) 

       throws DuplicateLocalRPCException
  {
    String RPCname = (String)localRPCTable.get(g2_RPD_name);

    LocalRPCDeclaration dec = ((G2Gateway)connection).getLocalRPCDeclaration(g2_RPD_name);

    if (RPCname != null && dec != null)
	// Native function uses memory for each definition, so we dont allow duplicates
      throw(new 
	    DuplicateLocalRPCException(
	    "Local Java method for G2 RPD" + g2_RPD_name + " Already declared for this connection"));
    else {

      dec = new LocalRPCDeclaration(target, 
				    null,
				    java_method_name,
				    run_in_queued_thread,
				    CALL_METHOD_OUTSIDE_GSI_THREAD,
				    false);

      ((G2Gateway)connection).setLocalRPCDeclaration(g2_RPD_name, dec);

      // User declared RPCs always run outside the GSI dispatcher thread
      declareLocalRPCNative(g2_RPD_name, true);
    }
  }

     

  /**
   * Predeclare a prelooked up Method so that is can be called by a connected G2.
   * 
   * <P>The java_method must be a valid java.lang.refelect.Method for the
   * class of java_object
   *
   *      
   * <LI> RPC runs in gsi thread ->  run_outside_gsi_thread = false
   * <LI> RPC runs in new thread for wach call -> run_outside_gsi_thread = true and 
   * run_in_queued_thread = false
   * <LI> RPC runs in one queued thread seperate form gsi thread -> run_outside_gsi_thread = true
   * and run_in_queued_thread = true
   * 
   */
  final void declareLocalRPC(G2Connection connection,
				     Object java_object,
				     Method java_method,
				     Symbol g2_RPD_name,
				     boolean run_in_queued_thread)
       throws DuplicateLocalRPCException
  {
    String RPCname = (String)localRPCTable.get(g2_RPD_name);

    LocalRPCDeclaration dec = ((G2Gateway)connection).getLocalRPCDeclaration(g2_RPD_name);

    if (RPCname != null && dec != null)
	// Native function uses memory for each definition, so we dont allow duplicates
      throw(new 
	    DuplicateLocalRPCException(
	    "Local Java method for G2 RPD" + g2_RPD_name + " Already declared for this connection"));
    else {

      dec = new LocalRPCDeclaration(java_object, 
				    java_method,
				    null,
				    run_in_queued_thread,
				    CALL_METHOD_OUTSIDE_GSI_THREAD,
				    false);

      ((G2Gateway)connection).setLocalRPCDeclaration(g2_RPD_name, dec);

      // User declared RPCs always run outside the GSI dispatcher thread
      declareLocalRPCNative(g2_RPD_name, true);
    }
  }


  /**
   * Predeclare a method so that is can be called by a connected G2.
   * This method is used internally, to declare that a paraticular G2
   * call will call on a defined method of an defined target, regardless
   * of the connection
   * 
   * <P>The java_method must be a valid java.lang.refelect.Method for the
   * class of java_object
   *
   *      
   * <LI> RPC runs in gsi thread ->  run_outside_gsi_thread = false
   * <LI> RPC runs in new thread for wach call -> run_outside_gsi_thread = true and 
   * run_in_queued_thread = false
   * <LI> RPC runs in one queued thread seperate form gsi thread -> run_outside_gsi_thread = true
   * and run_in_queued_thread = true
   * 
   */
  private final void declareLocalRPC(Object java_object,
			     Method java_method,
			     Symbol G2_RPD_name,
			     boolean force_return_value,
			     boolean run_outside_gsi_thread,
			     boolean run_in_queued_thread)
       throws DuplicateLocalRPCException
  {
     String RPCname = (String)localRPCTable.get(G2_RPD_name); 

     if (RPCname != null)
       // Native function use memory for each definition, so we dont allow duplicates
       throw(new 
	     DuplicateLocalRPCException("Local Java method for G2 RPD" 
                                         + G2_RPD_name + " Already declared"));
     else 
       {
	 LocalRPCDeclaration dec = new LocalRPCDeclaration(java_object, 
				       java_method,
				       null,
				       run_in_queued_thread,
				       run_outside_gsi_thread,
				       force_return_value);

	 // This is a hashtable for jgi, predeclared localRPCs , non-connection
	 // specific, can not bne overridden
	 localRPCTable.put(G2_RPD_name, dec);
	 
	 declareLocalRPCNative( G2_RPD_name, false );
       }
  }
  

  /** 
   * Declares a G2 procedure/method in a G2 process to be invocable, as a remote
   * process, by a connected JGInterface.
   *
   *<P>Calls to gsiDeclareRemote should be made in callback method 
   * <B>gsiG2InitiaizeConnection</B>, because remote procedure declarations
   * specfic to a G2 connection.
   * 
   *@param g2_function_name  The G2 procedure name to call
   *@param java_receiver_method_name For reception of asynchronous RPC calls
   */
  Object declareRemoteRPC(Symbol g2_procedure_name, 
			       String java_receiver_method_name,
			       int context)
  {
    return declareRemoteRPCNative(g2_procedure_name.toString(), 
							 -1, /* Varargs */
							 -1, /* Varargs */
							 java_receiver_method_name,
							 context);
  }
  
  
  /** 
   * Declares a G2 procedure/method in a G2 process to be invocable, as a remote
   * process, by a connected JGInterface. The G2 Procedure/Method is limited to
   * delared must match the number of input and return argument counts specifed
   *
   *<P>Calls to gsiDeclareRemote should be made in callback method 
   * <B>gsiG2InitiaizeConnection</B>, because remote procedure declarations
   * specfic to a G2 connection.
   * 
   *@param g2_function_name  The G2 procedure name to call
   *@param input_arg_count   The number args in the G2 procedure
   *@param return_arg_count  The number args expected to be returned
   *@param java_receiver_method_name For reception of asynchronous RPC calls
   */
  Object declareRemoteRPC(Symbol g2_procedure_name, 
			       int input_arg_count,
			       int return_arg_count,
			       String java_receiver_method_name,
			       int context)
  {
    return declareRemoteRPCNative(g2_procedure_name.toString(), 
							input_arg_count,
							return_arg_count,
							java_receiver_method_name,
							context);
  }


		
  /**
   * Call A predeclared G2 procedure and return immidently.
   *
   * <P>The called G2 procedure is called asynchronusly, any return values
   * are returned by G2 calling a specified JGInterface method.
   * The G2 procedure must have been predeclared by GsiRpcDeclareRemote.
   *
   * @param g2_procedure_name  The name of the predeclared G2 procedure to call
   * @param items  The array of objects to send as arguments
   */
  void callRPCAsynchronous (Object g2_procedure_handle, 
			    Object items[],
			    int context)
  {

    if (g2_procedure_handle == null)
      throw(new 
	    G2RemoteRPCNotPredeclaredException(
			    "G2 RPC" + g2_procedure_handle + " Not Valid"));
    else
      {					   // false == CALL
	callRPCNative (((Long)g2_procedure_handle).longValue(), items, false, null, context );
      }
  }

  
  
  /**
   * Call a predeclared G2 procedure synchronously (wait until completed.
   * The current thread will wait until the remote G2 has executed.
   * TIMEOUT exception ??????.
   * The G2 procedure must have been previously declared using
   * declareRPCRemote.
   * RETRUN VALUES LIMITED TO ONE ?????
   *
   * @param g2_procedure_name  The predeclared G2 procedure to call
   * @param items  The array of objects to pass to the procedure
   */
    Object callRPC (Object g2_procedure_handle, Object items[], int timeout, int context) throws G2AccessException {
        if (g2_procedure_handle == null) {
            throw new G2RemoteRPCNotPredeclaredException("G2 RPC null handle Not Valid");
        }
        else {
            if (Thread.currentThread().equals(gsiLoopThread)) {
                throw new RuntimeException("Cant use CallRPC(Synchronous) while in dispatch thread");
            }
            G2RemoteRPCThreadData td = new G2RemoteRPCThreadData (timeout);
            try {
                synchronized (td) {
                    callRPCNative(((Long)g2_procedure_handle).longValue (), items, false, td, context);
                    final long endTime = System.currentTimeMillis() + timeout;
                    long waitTime = timeout;
                    while ((waitTime >= 0) && !td.isRPCdone()) {
                        td.wait(waitTime);
			if (timeout > 0) {
                            waitTime = endTime - System.currentTimeMillis();
			}
                    }
                }
            }
            catch (InterruptedException ie) {
                Trace.exception(ie);
            }
            Object retnval = td.getData();  // will throw G2AccessException if G2 complains
            if (td.threadHasIncompleteConversionData) {
              synchronized (JGInterface.class) {
                retnval = stubResolverTable[context].resolveDeferredStubs (retnval);
              }
            }
            return retnval;
        }
    }
    

  /**
   * This method is called from native code only. It guarantees
   * that the "current" context does not change between calls
   * to this method or the connection being closed.
   */
  private void setCurrentContext (int contextID) {
    synchronized (JGInterface.class) {
      currentFactory = factoryTable[contextID];
      //System.out.println ("Setting Current Context = " + contextID);
    }
  }

  G2StubFactory getStubFactory (int contextID) {
    synchronized (JGInterface.class) {
      return factoryTable[contextID];
    }
  }

  /**
   * Start a predeclared remote G2 procedure, ignore any return values.
   * The method returns Immediately. The G2 procedure must have been
   * previously declared using method <B>declareRemoteRPC</B>
   *
   * @param g2_procedure_name  The G2 procedure to call
   * @param items  The array of objects to pass as arguments
   */
  void startRPC(Object g2_procedure_handle, 
		       Object items[],
		       int context)
  {


    if (g2_procedure_handle == null)
      throw(new 
	    G2RemoteRPCNotPredeclaredException(
			    "G2 RPC null handle Not Valid"));
    else
      {
	// true == START
	callRPCNative (((Long)g2_procedure_handle).longValue(), items, true, null, context );
      }
  }

  /**
   * Set the value type of the return type of a object parameter from a remote RPC call
   */
  void setRemoteRPCReturnKind (Object g2_procedure_handle,
						    int return_value_index,
						    int return_value_type,
					   int context) {
   
    // System.out.println ("Method JAVA gsi_set_rpc_remote_return_value_kind : " + g2_procedure_handle);

    if (g2_procedure_handle == null) {
      throw(new 
	    G2RemoteRPCNotPredeclaredException(
			    "G2 RPC null handle Not Valid"));
    } else {
      setRPCRemoteReturnValueKindNative (((Long)g2_procedure_handle).longValue(),
					return_value_index,
					return_value_type,
					context);
    }
  }

  /**
   * Return a "known" "by-copy" structure that represents the contents of a G2 Item.
   * As the native interface will call this method to extract information about
   * a G2 Item, the native code does not need to know specific information
   * about a G2 ItemImpl and its accessor methods.
   */
  final Structure getG2ItemInfo(ImplAccess g2Item)
  {
    Structure attributes = g2Item.getAttributes();
    return attributes;
  }



  final void communicationError(int context, 
				int error_code, 
				String error_msg,
				String initiateConnectionId)
  {
    gsiLoopThread.enqueue(new Work_communicationError(context, error_code, error_msg, initiateConnectionId));
  }


  /**
   * Called by native interface when an asynchronous communication error occurs
   */
  final void handleCommunicationError(int context, 
				int error_code, 
				String error_msg,
				String initiateConnectionId)
  {

    if (traceOn) {
      Trace.send(1, traceKey, i18n, 
		 "Received Error for " + context + " code " + error_code + "  msg " + error_msg);
    }

    // Special case during Intiate Connection, we have not got a context
    // but should have a ident, must inform the G2Connection waiting for 
    // the connection that the attempt has been aborted
    if (initiateConnectionId != null) {
      G2InitializeConnectionAbort(error_msg, initiateConnectionId);
      return;
    }

     G2Connection connection = (G2Connection)g2_connections.get(context);
     boolean have_connection = false;

     if (connection != null)
       {
	 // Send the event to the connection
	 G2CommunicationErrorEvent error_event = 
	   new G2CommunicationErrorEvent(connection,
					 G2ConnectionEvent.G2_COMMUNICATION_ERROR,
					 error_code, 
					 error_msg);

	 dispatchG2ConnectionEvent(connection, context, error_event);
	 have_connection = true;
       }
     
     else {
       // No particular connection, so send to all connections
       Enumeration cnum = g2_connections.keys();
       for (Enumeration e  = g2_connections.elements(); e.hasMoreElements();)
	 {
	   connection = (G2Connection)e.nextElement();
	   Integer contextnum = (Integer)cnum.nextElement();
	   if (connection != null && contextnum != null)
	     {
	       have_connection = true;
	       G2CommunicationErrorEvent error_event = 
		 new G2CommunicationErrorEvent(connection,
					       G2ConnectionEvent.G2_COMMUNICATION_ERROR,
					       error_code, 
					       error_msg);

	       dispatchG2ConnectionEvent(connection, contextnum.intValue(), error_event);
	     }
	   
	 }
     }

     if (!have_connection || context == -1)  // we dont have a error listener yet (mdg) !
       {
	 // Must tell someone about the problem
	 //G2CommunicationErrorEvent error_event = 
	 //  new G2CommunicationErrorEvent(this, // cant do this, must be a connection
	 //			 G2ConnectionEvent.G2_NOCONNECTION_COMMUNICATION_ERROR,
	 //			 error_code, 
	 //			 error_msg);

	 // send to System.err until we know what to do...this should not normally happen
	 System.err.println("A G2 communication layer error occured->" + error_msg.toString());
       }
									    
  }

  /**
   * Determine whether the current thread is running
   * a g2 callback.
   * @return true if we are in the context of a g2 callback else false
   */
  static boolean inCallbackThread () {
    return Thread.currentThread().equals(gsiLoopThread);
  }

  /**
   * Override the default Stub factory, used when creating Java stubs
   * for G2 classes.
   *@param fac The new G2 Stub factory
   */
  public static synchronized void setG2StubFactory (G2StubFactory fac) {
    if (stubFactorySet)
      throw new Error ("G2 Stub factory already defined");
    //factory = fac;
    //stubResolver = new StubResolver(fac);
    stubFactorySet = true;
  }

  /* Move to top */
  private static final int INITIAL_NATIVE_CONNECTION_CAPACITY = 10;
  private static G2StubFactory[] factoryTable = new G2StubFactory[INITIAL_NATIVE_CONNECTION_CAPACITY];
  private static StubResolver[] stubResolverTable = new StubResolver[INITIAL_NATIVE_CONNECTION_CAPACITY];

  private static synchronized void setupNewNativeConnection (G2Connection cxn, int contextID) {
    ensureConnectionCapacity (contextID);
    factoryTable[contextID] = new DefaultStubFactory (cxn);
    stubResolverTable[contextID] = new StubResolver (factoryTable[contextID]);
    ((G2Gateway)cxn).setLoader (factoryTable[contextID].getStubClassLoader ());
  }

  
  private static synchronized void ensureConnectionCapacity (int newID) {
    int newCapacity = newID + 1;
    int existingCapacity = factoryTable.length;
    if (existingCapacity >= newCapacity)
      return;
    newCapacity = (existingCapacity*15)/10; // Grow 50%. Very arbitrary
    G2StubFactory[] newFactoryTable = new G2StubFactory[newCapacity];
    System.arraycopy (factoryTable, 0, newFactoryTable, 0, existingCapacity);
    factoryTable = newFactoryTable;
    StubResolver[] newStubResolverTable = new StubResolver[newCapacity];
    System.arraycopy (stubResolverTable, 0, newStubResolverTable, 0, existingCapacity);
    stubResolverTable = newStubResolverTable;
  }

  final void invalidateG2Stub (int handle, int contextID, G2Access context) {
    //System.out.println ("JGinterface Invalidating G2 Stub #" + handle + " in context " + context);
    G2StubFactory localCurrentFactory;
    synchronized (JGInterface.class) {
      localCurrentFactory = factoryTable[contextID];
    }
    if (localCurrentFactory == null)
      throw new Error ("G2 Stub Factory not installed for " + context);
    Item stub = localCurrentFactory.getG2StubForHandle(handle, context);
    try {
      if (stub != null) {
	g2StubController.deleteInstance(stub, false);
	dispatchDataServiceHandlerEvent((G2Connection)context, 
					contextID, 
					stub, 
					VARIABLE_DEREGISTRATION_ID_INTEGER_,
					null,
					false);
      }
    } catch (IllegalAccessException e) {
  	} catch (G2AccessException e) {
    } catch (RemoteException e) {
    } catch (RuntimeException e) {}
    localCurrentFactory.invalidateG2Stub (handle, context);
  }

  /**
   * Return an Item that represents a G2 ITEM that is a proxy for a
   * Java Object.
   *
   *@param g2Connection the G2 where to access the proxy.
   *@param g2ProxyClass the G2 Class name, used to create an instance of a proxy
   * in the event that an existing proxy could not be found. Set null to
   * use the default G2 Class registered for the class of JavaObject.
   *@param javaObject the Java Object to create a proxy for.
   *@exception G2AccessException When there is a problem communicating with G2 or
   * a G2 Class could not be found to create the proxy ITEM
   */
  final Item getG2ProxyForJavaObject (G2Connection g2Connection,
				      String g2ProxyClass,
				      Symbol g2ParentClass,
				      Object javaObject)
       throws G2AccessException
  {
    return g2StubController.getG2ProxyForJavaObject (g2Connection,
						     g2ProxyClass,
						     g2ParentClass,
						     javaObject);
  }

	
  // Table to hold Method execution queues
  static Hashtable G2MethodExecutionsQueues = new Hashtable();
  private static volatile TaskHandler methodDispatchHandler = null;

  /**
   * Set a TaskHandler that will be used to dispatch G2 requests to invoke Java Methods.
   * @param handler The TaskHandler to use.
   * @throws An Error if the Handler has already been set.
   * @undocumented For Gensym use only.
   */
  public static void setMethodDispatchHandler(TaskHandler handler)
  {
    if (methodDispatchHandler != null)
      throw new Error("A Method Dispatch Handler has already been defined");
    methodDispatchHandler = handler;
  }

  /**
   * Invoke a Java method request from a connection
   * for a predeclared localRPC, entry point from
   * native call.
   *
   * <P>Called by Native interface.
   */
  final void invokeMethod (G2Connection connection,
			   Symbol G2_RPD_name,
			   boolean non_connection_specific,
			   Object args[], 
			   Class args_classes[],
			   long return_call_index,
			   boolean incomplete_stub_conversion,
			   int context) 
  {
    // Get the target for this method call
    LocalRPCDeclaration dec;

    if (non_connection_specific)
      dec = (LocalRPCDeclaration)localRPCTable.get(G2_RPD_name);  // This is a global (non connection specific definition)
    else
      dec = ((G2Gateway)connection).getLocalRPCDeclaration(G2_RPD_name);

    //System.out.println("********>>>>> G2 wants to call " +  G2_RPD_name + 
    //	       " " + dec);

    if (dec == null)
      throw new NoJavaMethodForG2RPCException("No Java Method could be found to invoke for the G2 RPC name " +
				  G2_RPD_name + "which G2 attempted to invoke from G2Connection " +
				  connection);
    RunMethodThread run_method;

    if (dec.target_method == null)
      // Only a method name has been given
      run_method = new RunMethodThread(this, 
			dec.target, 
			dec.target_method_name, 
			args, 
			args_classes,
			return_call_index,
			dec.force_return_value,
			incomplete_stub_conversion,
			context);
    else 
      // We have a pre-looked up a target method for this call
      run_method = new RunMethodThread(this,
			 dec.target,
			 dec.target_method,
			 args,
			 return_call_index,
			 dec.force_return_value,
			 incomplete_stub_conversion,
			 context);

    dispatchMethodCall(dec.run_outside_gsi_thread,
		       dec.run_in_queued_thread,
		       run_method,
		       connection);
  }

  void clearMethodCallQueue(Object target) {
    //    System.out.println("clearingMethodCallQueue for target=" + target);
    MethodCallQueue queue = (MethodCallQueue)G2MethodExecutionsQueues.remove(target);
    if (queue != null) {
      queue.die();
    } else {
      //System.out.println("queues=" + G2MethodExecutionsQueues + ";hash=" +
      //		 G2MethodExecutionsQueues.hashCode());
    }
  }

  /**
   * Invoke a predeclared Java method from G2, this is a non connection specific call
   *
   * <P>Called by Native interface.
   */
  final void invokeMethod (Object target,
			   Method java_method,
			   Object args[],
			   long return_call_index,
			   boolean force_return_value,
			   boolean run_outside_gsi_thread,
			   boolean run_in_queued_thread,
			   boolean incomplete_stub_conversion,
			   int context)
  { 
    //System.out.println ("G2 Calling invokeMethod:2 (" + target + ", " + java_method + ", Args = " + args + "[" +
    //		 run_outside_gsi_thread + ", " + run_in_queued_thread + "]");
    //System.out.flush ();
    RunMethodThread run_method = new RunMethodThread(this,
			 target,
			 java_method,
			 args,
			 return_call_index,
			 force_return_value,
			 incomplete_stub_conversion,
			 context);

    dispatchMethodCall(run_outside_gsi_thread,
		       run_in_queued_thread,
		       run_method,
		       target);
  }


  private void dispatchMethodCall(boolean runOutsideGsiThread,
				  boolean runInQueuedThread,
				  RunMethodThread methodCall,
				  Object target)
  {
    if (runOutsideGsiThread)
      {
	boolean handled = false;
	if (methodDispatchHandler != null)
	  handled = methodDispatchHandler.start(methodCall, 
						target,
						runInQueuedThread);
	if (!handled) {
	  if (runInQueuedThread)
	    {
	      // try to find a method queue for this object
	      MethodCallQueue queue = (MethodCallQueue)G2MethodExecutionsQueues.get(target);
	      if (queue == null)
		{
		  queue = new MethodCallQueue();
	          queue.setName("MethodCallQueue for " + target.toString());
		  G2MethodExecutionsQueues.put(target, queue);
		  queue.insert(methodCall);
		  queue.start();
		}
	      else
		queue.insert(methodCall); 
	    }
	  else
	    {
	      Thread exeMethodThread = new Thread(methodCall);
	      exeMethodThread.start();
	    }
	}
      }
    else
      methodCall.run(); // in GSI Thread
  }


  static volatile Class InvocationException_Class = null;

  /**
   * Internal Class to deal with invoking the java method, within an independant
   * thread, thus not blocking the GSI dispatch loop
   */
  class RunMethodThread implements Runnable
  {
    JGInterface itf;
    Object target;
    Object args[];
    String method_name = null;
    Method method = null;
    Class args_classes[];
    long return_call_index;
    int context;
    boolean incomplete_stub_conversion;
    boolean force_return_value;

    @Override
    public String toString () {
      StringBuffer sb = new StringBuffer (100);
      sb.append(super.toString()).append (" {target=").append(target).append(",args=").
	append(com.gensym.core.DebugUtil.printArray (args)).append(",method=").
	append(method_name).append("/").append(method);
      return sb.toString ();
    }

    /**
     * Construct a RunMethodThread with a method_name to lookup before invoking it
     */
    RunMethodThread(JGInterface itf,
		    Object target,
		    String method_name,
		    Object args[],
		    Class args_classes[],
		    long return_call_index,
		    boolean force_return_value,
		    boolean incomplete_stub_conversion,
		    int context)
    {
      this.itf = itf;
      this.target = target;
      this.method_name = method_name;
      this.args = args;
      this.args_classes = args_classes;
      this.return_call_index = return_call_index;
      this.force_return_value = force_return_value;
      this.incomplete_stub_conversion = incomplete_stub_conversion;
      this.context = context;

/*
      Trace.send(1, traceKey, i18n, "runmethodthreadcall",
		  target, method_name);
*/
      if (InvocationException_Class == null)
	try 
	{ 
	   InvocationException_Class = Class.forName("java.lang.reflect.InvocationTargetException"); 
	} catch (Exception E) {}
    }

    /**
     * Construct a new RunMethodThread with a prelooked up method to invoke
     */
    RunMethodThread(JGInterface itf,
		    Object target,
		    Method java_method,
		    Object args[],
		    long return_call_index,
		    boolean force_return_value,
		    boolean incomplete_stub_conversion,
		    int context)
    {
      this.itf = itf;
      this.target = target;
      this.method = java_method;
      this.args = args;
      this.return_call_index = return_call_index;
      this.force_return_value = force_return_value;
      this.incomplete_stub_conversion = incomplete_stub_conversion;
      this.context = context;

/*
      Trace.send(1, traceKey, i18n, "runmethodthreadcallprelook",
		 java_method);
*/
      if (InvocationException_Class == null)
	try 
	{ 
	  InvocationException_Class = Class.forName("java.lang.reflect.InvocationTargetException"); 
	} catch (Exception E) {}
    }

    /**
     * Ensure that any DeferredStubs are converted to real objects.
     */
    void ResolveDeferredStubsInArguments(Object args[], Class arg_classes[])
    {
      for (int i=0; i<args.length; i++)
	{
	  // We have no idea where the DeferredStub(s) are so we 
	  // deep parse all the arguments
    synchronized (JGInterface.class) {
      args[i] = stubResolverTable[context].resolveDeferredStubs(args[i]);
    }
	  // If one of the arguments is a DeferredStub
	  // and converted then arg_class needs to be updated
	  // with the new argument class.
	  // TAKE CARE WRITING OVER THIS CLASS INFO, AS
	  // IT WILL CONTAIN CLASS INFO DIFFERENT FROM args[i].class
	  // IN THE CASE OF PRIMITIVE CLASSES (e.g. args[x] = Interger, args_class[x] == int)

	  if (args_classes != null && args_classes[i] == DeferredStub.class) {
	    arg_classes[i] = args[i].getClass();
	    //System.out.println("Resolved param[" + i + "] to " + args[i].toString());
	  }
	}
    }

    /** 
     * Main run method to execute the method on the object defined atr creation
     */
    @Override
    public void run()
    {
      Thread.currentThread().setName("RunMethodThread for " + (method_name != null ? method_name : method.getName()));
      //System.out.println ("G2 -> " + this)
      for (int i=0; i<args.length; i++) {
	//System.out.println("Got Arg " + args[i] + 
	//" of Class " + (args_classes == null ? "" : " of Class " + args_classes[i]));
	  if (args[i] instanceof com.gensym.classes.ClassDefinition)
	    try {
	    //System.out.println("Class name is : " + 
	    //	       ((com.gensym.classes.ClassDefinition)args[i]).getClassName());
	  } catch (Exception e) {System.out.println(e.toString());}
      }
/*
      Trace.send(1, traceKey, i18n, "runmethodrun",
		 method_name != null ? method_name : method.getName(),
                 target, Long.toHexString(return_call_index));
*/
    //System.out.println("****** method_name is **** " + 
    //    method_name + " Class name " + target);
      
      try {
     
	// Ensure that we have generated the actual Stub for any G2 object
	// incomplete_stub_conversion may be set because a deferred stub has been 
	// found during the conversion of GSI items to Java parameters for this call
	if (incomplete_stub_conversion)
	  ResolveDeferredStubsInArguments(args, args_classes);

	if (method == null) 
	  {
	    // Get the method for these parameter types and name

	    //for (int i=0; i<args.length; i++)
	    //System.out.println("Got Arg " + args[i].toString() + 
	    //" of Class " + args_classes[i].getName());
	    //System.out.println("****** method_name is **** " + 
	    // method_name + " Class name " + target.getClass().getName());

	    try 
	      {
		// fast simply lookup using reflection
		method = target.getClass().getMethod(method_name, args_classes);
	      } 
	    catch (NoSuchMethodException E) 
	      {
		// Could no find a match, use our own dispather to find an applicable method
		// from subclass of target Class or Overridden method
		method =  itf.methodDispatcher.findInstanceMethod(method_name,
					     target.getClass(),
					     args_classes);
		if (method == null)
		  // Still no joy, make a meaningful error message, the method signature
		  // we attempted to call
		  {
		    String err_msg = method_name + "(";
		    for (int i=0; i<args_classes.length; i++)
		      {
			if (i>0) {
				err_msg = err_msg + ",";
			}
			err_msg = err_msg + args_classes[i].getName();
		      }
		    err_msg = err_msg + ")";
		    throw new NoSuchMethodException(err_msg);
		  }
	      }
		
	  }

/*
        Trace.send(1, traceKey, i18n, "runmethodthreadinvoke",
 		   method.toString());
*/
	// call the method
	Object result = method.invoke(target, args);

	// return any value
     
	
/*
        Trace.send(1, traceKey, i18n, "runmethodthreadreturn",
                   Long.toHexString(return_call_index), result);
*/
	itf.returnRPCValue(return_call_index, 
			   result, 
			   force_return_value, 
			   false, // no error 
			   null,
			   (String)null,
			   context);
      
     
      } catch (Throwable E) 
	{ // Send Error back to G2 !!! 

	  // The target may have caused the error
      Throwable tagertException = E;
	  if (tagertException.getClass() == InvocationException_Class){
		  tagertException = ((InvocationTargetException)tagertException).getTargetException();
	  }
	  // Construct an Printstream to describe the error
	  StringWriter op = new StringWriter();
	  PrintWriter err = new PrintWriter(op);
	  tagertException.printStackTrace(err);
	  String err_message ="\n Java Stack Trace  " +
	    (method_name != null ? "during call to " + method_name + " \n" : "\n") + op.toString(); 

	  // We also must return something back to G2 to release the waiting proc or
	  // it will not detect that there was an error
	  Symbol error_symbol = Symbol.intern(tagertException.getClass().getName().toUpperCase());  
	  try {
	    if (return_call_index == -1) { // we have nothing in G2 to report back too
	      // is the G2 connection alive
	      if (g2_connections.containsKey(context))
		// yes
		reportLogBookErrorMessage(error_symbol, err_message, context);
	      else {
		// no
		System.err.println("Error during call from G2 to Java (G2 connection is dead) \n" + 
				   err_message);
	      }
	    } else 
	      itf.returnRPCValue(return_call_index, 
				 null, 
				 force_return_value, 
				 true, // error
				 error_symbol,
				 err_message,
				 context);
	 
	  } catch (Exception e) {
	    System.err.println("Error during call from G2 to Java (G2 connection possibly dead) \n" + 
			       err_message + " \n" + e.toString());
	    e.printStackTrace();
	  }
	}
    }

    //protected void finalize()
    //{
    //  System.out.println("In finalize for RunMethodThread");
    //}

  }

  /**
   * Inner Class to handle a queue of RunMethodThread objects.
   * Yes, I could have used a Vector, but this is faster
   */
  class MethodCallQueue extends Thread
  {
    int INCREMENT = 100;
    int queueSize = INCREMENT;
    RunMethodThread []methodQueue = new RunMethodThread[queueSize];
    RunMethodThread []methodRunQueue = new RunMethodThread[queueSize];
    int frontMethodPtr = -1;  // New MethodRequests queued, the front of the queue
    boolean insertToggle = false;

    volatile boolean stayAlive = true;

    void die() {
      stayAlive = false;
      synchronized(this) {
	notifyAll();
      }
    }

    @Override
    public void run()
    {
      int i;
      int num_methods;
      RunMethodThread []local_methodRunQueue;
      while (stayAlive)
	{
	  synchronized(this)
	    {

	      // System.out.println("In run " + frontMethodPtr);

	      // Copy any queued methods, so that we can iterate over them 
	      // in this independant thread
	      //Trace.send(5, traceKey, i18n, "methodcallqueueloop");

	      num_methods = frontMethodPtr + 1;
	      if (num_methods > 0)
		{
		  if (methodRunQueue.length < queueSize)
		    {
		      // make room as the method queue has growen
		      methodRunQueue =  new RunMethodThread[queueSize];
		    } 

		  System.arraycopy(methodQueue, 0, 
				   methodRunQueue, 0, 
				   num_methods);

		  // Reset insert queue
		  for (i = 0; i<=frontMethodPtr; i++)
		    methodQueue[i] = null; // free
		  frontMethodPtr = -1;
		}	 

	      // Reset insert toggle, so we can detect any inserts while we perform some work
	      insertToggle = false;
	    }

	  if (num_methods > 0 )
	    {
/*
	      Trace.send(5, traceKey, i18n, "methodcallqueuecall",
		 new Integer(num_methods));
*/
		  synchronized(this) { 
		    local_methodRunQueue = methodRunQueue; // locals in loops are faster
		    for (i = 0; i<num_methods; i++)
			{
			  local_methodRunQueue[i].run();  // Execute the method
			  local_methodRunQueue[i] = null; // clear up
			}
		  }
	    }
	  else
	    try { 
	      synchronized(this) { 
		// only synchronize here to allow other threads to insert methods while
		// executing another method
		//System.out.println("In wait loop backMethodPtr = " + backMethodPtr);

		// If there was no inserts while we were working then wait for an insert
		if (!insertToggle) {
		  //Trace.send(5, traceKey, i18n, "methodcallqueuewait");

		  wait(); 
                  }

		//System.out.println("after wait loop backMethodPtr = " + backMethodPtr); 
	      }
	    }  
	  catch (java.lang.InterruptedException E) {} // wait to be woken up
	}

    }

    /**
     * Insert a new method RunMethodThread into a queue. 
     * Make room if the queue is full up.
     * The queue is empted
     */
    final synchronized void insert(RunMethodThread method)
    {
      //Trace.send(5, traceKey, i18n, "methodcallqueueinsert");

      // System.out.println("In insert");
      frontMethodPtr += 1;
      if (frontMethodPtr >= queueSize)
	{
	  // make room
	  RunMethodThread []methodQueueNew =  new RunMethodThread[queueSize + INCREMENT];
	  System.arraycopy(methodQueue, 0, methodQueueNew, 0,  queueSize);
	  queueSize  += INCREMENT;
	  methodQueue = methodQueueNew;
	}
        
      methodQueue[frontMethodPtr] = method;

      insertToggle = true; // An insert has been made
      notifyAll(); // kick the unqueue thread into life if waiting for inserts
	
    }
      

  }
  
  /**
   * @undocumented For Gensym use only.
   */
  public static void startCollectingRPCStats () {
    if (!Thread.currentThread().equals(gsiLoopThread)) 
      gsiLoopThread.enqueue(new Work_startCollectingRPCStats0 ());
    else
      gsiLoopThread.startCollectingRPCStats0 ();
  }

  /**
   * @undocumented For Gensym use only.
   */
  public static void stopCollectingRPCStats () {
    if (!Thread.currentThread().equals(gsiLoopThread)) 
      gsiLoopThread.enqueue(new Work_stopCollectingRPCStats0 ());
    else
      gsiLoopThread.stopCollectingRPCStats0 ();
  }

  /**
   * @undocumented For Gensym use only.
   */
  public static void writeRPCStats (String fileName) {
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue (new Work_writeRPCStats0(fileName));
    else
      gsiLoopThread.writeRPCStats0(fileName);
  }

  /**
   * @undocumented For Gensym use only.
   */
  public static void initializeStatBuffers (int numCalls) {
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_initializeStatBuffers0 (numCalls));
    else
      gsiLoopThread.initializeStatBuffers0 (numCalls);
  }

  /**
   * @undocumented For Gensym use only.
   */
  public static void clearProfilingData () {
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_clearProfilingData0 ());
    else
      gsiLoopThread.clearProfilingData0 ();
  }

  /* here is a huge wad of code that enqueues requests to the GSI loop
     thread, one for each native method.  The first set are all ones
     that do not return any values. */

  public void setFulldebug(boolean state) {
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue (new Work_setFulldebug(state));    
    else
      gsiLoopThread.setFulldebug(state);
  }

  public void setFundebug(boolean state){
    if (!Thread.currentThread ().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_setFundebug(state));
    else
      gsiLoopThread.setFundebug(state);
  }

  public void setConvdebug(boolean state){
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_setConvdebug(state));
    else
      gsiLoopThread.setConvdebug(state);
  }

  public void startInterface(Object intrface, String[] command){
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_startInterface(intrface, command));
    else
      gsiLoopThread.startInterface(intrface, command);
  }

  public void checkHandleType(int context, int handle){
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_checkHandleType(context, handle));
    else
      gsiLoopThread.checkHandleType(context, handle);
  }

  public void closeConnectionNative(int context){
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_closeConnectionNative(context));
    else
      gsiLoopThread.closeConnectionNative(context);
  }

  public void declareLocalRPCNative(Symbol g2_RPD_name, boolean connectionSpecific){
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_declareLocalRPCNative(g2_RPD_name, connectionSpecific));
    else
      gsiLoopThread.declareLocalRPCNative(g2_RPD_name, connectionSpecific);
  }

  public void reportLogBookErrorMessage(Symbol error_symbol, String error_message, int context){
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_reportLogBookErrorMessage(error_symbol, error_message, context));
    else
      gsiLoopThread.reportLogBookErrorMessage(error_symbol, error_message, context);
  }

  public void returnAttrs(Item variable, Structure attributesArray, Object values, int statusValues, int context){
    gsiLoopThread.enqueue(new Work_returnAttrs(variable, attributesArray, values, statusValues, context));
  }

  public void returnMessage(String message, int context){
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_returnMessage(message, context));
    else
      gsiLoopThread.returnMessage(message, context);
  }

  public void setGSIContextLimit(int limit) {
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_setGSIContextLimit(limit));
    else
      gsiLoopThread.setGSIContextLimit(limit);
  }

  public int getSecureContext(int context) {
    if (Thread.currentThread().equals(gsiLoopThread))
      return gsiLoopThread.getRemoteSecureContext(context);
    else {
      Return_int synchronizer = new Return_int();

      Work work = new Work_getRemoteSecureContext(context, synchronizer);
      doWait(synchronizer, work, "get secure context");
      return synchronizer.getValue ();
    }
  }

  public void nativeRegisterContextObject(G2Connection context_object, int context, String remote_process_string){
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_nativeRegisterContextObject(context_object, context, remote_process_string));
    else
      gsiLoopThread.nativeRegisterContextObject(context_object, context, remote_process_string);
  }

  public void returnRPCValue(long call_index, Object result, boolean force_return_value, boolean error, Symbol error_symbol, String error_text, int context){
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_returnRPCValue(call_index, result, force_return_value, error, error_symbol, error_text, context));
    else
      gsiLoopThread.returnRPCValue(call_index, result, force_return_value, error, error_symbol, error_text, context);
  }

  public void returnValues(Object[] variables, Structure[] attributesArray, Object[] values, int[] statusValues, int context){
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_returnValues(variables, attributesArray, values, statusValues, context));
    else
      gsiLoopThread.returnValues(variables, attributesArray, values, statusValues, context);
  }

  public void setInterfaceOutput(boolean state){
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_setInterfaceOutput(state));
    else
      gsiLoopThread.setInterfaceOutput(state);
  }

  public void setRPCRemoteReturnValueKindNative(long g2_function_handle, int return_value_index, int return_value_type, int context){
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_setRPCRemoteReturnValueKindNative(g2_function_handle, return_value_index, return_value_type, context));
    else
      gsiLoopThread.setRPCRemoteReturnValueKindNative(g2_function_handle, return_value_index, return_value_type, context);
  }

  public void setReceiveRegistrations(int context, boolean status){
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_setReceiveRegistrations(context, status));
    else
      gsiLoopThread.setReceiveRegistrations(context, status);
  }

  void callRPCNative(long function_handle,  Object arguments[], boolean start_proc, Object user_data, int context){
    if (!Thread.currentThread().equals(gsiLoopThread))
      gsiLoopThread.enqueue(new Work_callRPCNative(function_handle, arguments, start_proc, user_data, context));
    else
      gsiLoopThread.callRPCNative(function_handle, arguments, start_proc, user_data, context);
  }


  /* these methods all return values, and so they have to do a little
     more work in order to wait for the value to be returned. */

  long declareRemoteRPCNative(String g2_procedure_name, 
				 int input_arg_count,
				 int return_arg_count,
				 String java_receiver_method_name,
				 int context)
  {
    if (Thread.currentThread().equals(gsiLoopThread))
      return gsiLoopThread.declareRemoteRPCNative(g2_procedure_name, 
						  input_arg_count,
						  return_arg_count,
						  java_receiver_method_name,
						  context);
    else {
      Return_long synchronizer = new Return_long ();
    
      Work work = new Work_declareRemoteRPCNative(g2_procedure_name, 
							     input_arg_count,
							     return_arg_count,
							     java_receiver_method_name,
							     context,
							     synchronizer); 
      doWait(synchronizer, work, "declareRemoteRPCNative");   
      return synchronizer.getValue ();
    }
  }



  int getCurrentContext() {
    if (Thread.currentThread().equals(gsiLoopThread))
      return gsiLoopThread.getCurrentContext();
    else {
      Return_int synchronizer = new Return_int();

      Work work = new Work_getCurrentContext(synchronizer);
      doWait(synchronizer, work, "get current context");
      return synchronizer.getValue ();
    }
  }

  int getListenerSocket() {
    if (Thread.currentThread().equals(gsiLoopThread))
      return gsiLoopThread.getListenerSocket();
    else {
      Return_int synchronizer = new Return_int();
      Work work = new Work_getListenerSocket(synchronizer);
      doWait(synchronizer, work, "get listener socket");
      return synchronizer.getValue ();
    }
  }

  String getRemoteHostNative(int context) {
    if (Thread.currentThread().equals(gsiLoopThread))
      return gsiLoopThread.getRemoteHostNative(context);
    else {
      Return_String synchronizer = new Return_String();

      Work work = new Work_getRemoteHostNative(context,synchronizer);
      doWait(synchronizer, work, "get remote host native");
      return synchronizer.getValue ();
    }
  }

  int getRemotePortNative(int context) {
    if (Thread.currentThread().equals(gsiLoopThread))
      return gsiLoopThread.getRemotePortNative(context);
    else {
      Return_int synchronizer = new Return_int();

      Work work = new Work_getRemotePortNative(context,synchronizer);
      doWait(synchronizer, work, "get remote port native");
      return synchronizer.getValue ();
    }
  }

  String checkForHandleOK(int context, int handle) {
    if (Thread.currentThread().equals(gsiLoopThread))
      return gsiLoopThread.checkForHandleOK(context, handle);
    else {
      Return_String synchronizer = new Return_String();

      Work work = new Work_checkForHandleOK(context, handle,synchronizer);
      doWait(synchronizer, work, "check for handle okay");
      return synchronizer.getValue ();
    }
  }

  boolean initiateConnectionNative(String interface_name, String class_name, boolean keep_connection, String network, String host, String port, String rpis, String callback_identification, boolean secure){
    if (Thread.currentThread().equals(gsiLoopThread))
      return gsiLoopThread.initiateConnectionNative(interface_name, class_name, keep_connection, network, host, port, rpis, callback_identification, secure);
    else {
      Return_boolean synchronizer = new Return_boolean();

      Work work = new Work_initiateConnectionNative(interface_name, class_name, keep_connection, network, host, port, rpis, callback_identification, secure, synchronizer);
      doWait(synchronizer, work, "initiateConnectionNative");
      return synchronizer.getValue ();
    }
  }


  /* here is the little wait method used. */

  void doWait (Return synchronizer, Work work, String note) {
    try {
      synchronized (synchronizer) {
    	  gsiLoopThread.enqueue (work);
    	  //System.out.println (Thread.currentThread ().toString() + "waiting for " + note + " in " + synchronizer.toString ());
    	  System.out.flush();
    	  while (!synchronizer.isValueSet()) {
			synchronizer.wait();
			//System.out.println ("Done waiting for "+ note);
		}
      }
    } catch (java.lang.InterruptedException e) {
      Trace.exception (e, "thread interrupted while waiting for result from " + note);
    }
  }

}
