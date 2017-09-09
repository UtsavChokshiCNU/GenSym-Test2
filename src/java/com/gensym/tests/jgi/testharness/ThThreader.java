package com.gensym.tests.jgi.testharness;

import java.util.Hashtable;
import java.util.Random;
import java.lang.Math.*;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.classes.modules.javalinktestharness.*;


public class ThThreader implements Runnable, G2ConnectionListener // G2_EventSourceListener
{

  private Hashtable _threadTable = new Hashtable();
  private int _threadLoopCount = 0;
  private boolean _enableOutput = true;
  private static ATestClass _threadObject = null;
  private G2Connection g2Connection = null;
  private int id = 0;

  // Its good practice to pre lookup Symbols that will be used often
  private static Symbol _javaCallG2ProcNameSymbol = Symbol.intern("JAVA-CALL");
  private static Symbol _javaCall2G2ProcNameSymbol = Symbol.intern("JAVA-CALL-2");




  /**
   * Constructor
   */
  public ThThreader(G2Connection connection)
  {
    this.g2Connection = connection;
    initializeLocalRPCs(connection);
    connection.addG2ConnectionListener(this);
  }

  /**
   * Constructor
   */
  public ThThreader(G2Connection connection, int i)
  {
    System.out.println("ThThreader G2Connection int " + i + "\n");
    this.g2Connection = connection;
    connection.returnMessage("Connected to ThThreader "+ i + "\n");
    this.id = i;
    initializeLocalRPCs(connection);
    connection.addG2ConnectionListener(this);
    this.threadedTestFunc( 1000);
  }


  /**
   * Initialize all Local RPC's used by this subclass, this method is called only once
   * just before the first connection.
   */
  public void initializeLocalRPCs(G2Connection con)
  {
    System.out.println("ThThreader G2Connection int " + this.id + " initializeLocalRPCs \n");
    // we can only declare the following RPC once

    // Declare which Java methods and thier equivalent G2 RPC NAME,
    // in this class that can be called by the G2 connection



    // Example of declaring a Java method that, if called by G2,
    // will be executed in a new thread...As we may send a large array
    // and print it out which could delay other calls from this G2 connection.
    // N.B. Normally any requests to call Java Methods from G2
    // are placed on an execution queue (one per G2Connection)


    con.registerJavaMethod(this,
			    "terminate",
			    Symbol.intern("JAVA-TERMINATE"));

	con.registerJavaMethod(this,
			    "startLoopThread",
			    Symbol.intern("JAVA-START-LOOP-THREAD"));


        con.registerJavaMethod(this, "test_func",
           Symbol.intern("TEST_FUNC") );


    con.registerJavaMethod(this,
			    "receiveSend",
			    Symbol.intern("JAVA-RECEIVE-SEND"));



    // We can also prelook up methods and register those as accessible by a G2Connection

    try {
      java.lang.reflect.Method method =
	    this.getClass().getDeclaredMethod("threadedTestFunc",
					  new Class[] {Integer.TYPE});
      con.registerJavaMethod(this,
			      method,
			      Symbol.intern("THREADED_TEST_FUNC"),
			      true);


    } catch (NoSuchMethodException e) {
      System.err.println("Could not find Method " +
			 e.toString()); }

  }

  // *****************************************************************
  // G2ConnectionListener implementations

  /**
   * This Method is called when the connected G2 has been paused .
   */
  @Override
  public void g2IsPaused(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been paused :o(");
  }
  /**
   * This method is called when the connected G2 has been resumed.
   */
  @Override
  public void g2IsResumed(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been resumed :o)");
  }

 /**
   * This method is called when the connected G2 has been reset.
   */
  @Override
  public void g2IsReset(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been reset :]");
  }

  /**
   * This method is called when the connected G2 has been started.
   */
  @Override
  public void g2IsStarted(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been Started ;)");
  }

  /**
   * Called when G2 sends a message to the G2Connection.
   */
  @Override
  public void g2MessageReceived(G2ConnectionEvent e)
  {
    System.out.println("Message received from G2 was: " + e.getMessage());
  }

  /**
   * Called when an asynchronous error has occured in the G2 communications interface
   * for the G2Connection
   *
   *@param error_event An G2CommunicationErrorEvent describing the error that occured.
   */
  @Override
  public void communicationError(G2CommunicationErrorEvent error_event)
  {
    System.out.println(error_event.getMessage());
  }

  /**
   * Called when the network cannot deliver data that Java is attempting to write to G2.
   */
  @Override
  public void readBlockage(G2ConnectionEvent event) {}

  /**
   * Called when the network cannot deliver data that G2 is attempting to write to Java.
   */
  @Override
  public void writeBlockage(G2ConnectionEvent event) {}

  /**
   * This method is called when the G2 connection has been shutdown.
   * Must call super() here.
   */
  @Override
  public void g2ConnectionClosed(G2ConnectionEvent e)
  {
    System.out.println("G2 Connection has been closed ");
  }


  /**
   * A connection has been established between this connection and a G2 GSI-INTERFACE.
   * This method is called, so the connection specific information can be set up.
   * Specifically, declaring G2 methods and procedures that this connection would like to call.
   * Note: G2 method and procedure declarations are connection specific.
   */
  @Override
  public void g2ConnectionInitialized(G2ConnectionEvent e)
  {

    String remote_process_string = e.getMessage();


    // Send a "hi" message to G2's message board
    g2Connection.returnMessage("Connected to ThThreader (rpis = " + remote_process_string + ")\n Hi There from G2Gateway Java VM, how are you G2 ?");

    // Also Send an error message
    g2Connection.reportLogBookErrorMessage
      (Symbol.intern("ERROR"),
       "Dont worry this message is just a test Error message from Java class ThThreader");
  }

  // *****************************************************************


  // *****************************************************************
  // To Implement G2_EventSourceListener exported from G2-EVENT-SOURCE-CLASS

  /**
   * To Implement G2_EventSourceListener exported from G2 Event
   * Generator class G2EventSourceClass.
   */
  /*public void anEvent(G2_EventSourceEvent arg1) throws G2AccessException
  {
    System.out.println("Received an event..." + arg1.getMessage());
  }
*/
  // *****************************************************************


public void test_func(int j)
	{ Object args[] = new Object[1];

		int z;
		z = 0;
		for (int i=0; i< 2; i++ ){
			z = z + 1;
			z = i + z;
	  }

	  System.out.println("tf" + j);

      args[0] = new Integer( j ) ;

/*	try{

      this.callRPC(_javaCallThG2ReceiverSymbol, args, 100000);

	} catch (Exception E) { System.out.println(E.toString());
	   E.printStackTrace(System.out);}
*/

   g2Connection.startRPC(Symbol.intern("JAVA-TH-RECEIVER2"), args);
	}


// used for queue and thread thrashing tests
	public void threadedTestFunc(int j)
	{ Object args[] = new Object[1];
	    int z;
		z = 0;
		for (int i=0; i< 2000; i++ ){
			z = z + 1;
			z = i + z;


		System.out.println("Tht(T):"+ j + " " + i);

		args[0] = new Integer( i ) ;
		g2Connection.startRPC(Symbol.intern("JAVA-TH-RECEIVER"), args );
  }

	}

  // *****************************************************************
  // Implements Runnable

  /**
   * Run method, for execution of a new thread. Here we call G2 procs and methods
   * _threadLoopCount times, this shows that G2 procs and methods can be
   * called from multiple Java threads.
   */
  @Override
  public void run()
  {
    // Loop calling two G2 Procs
    int thisLoop = this._threadLoopCount;
    ATestClass threadObject = this._threadObject;
    String threadName = Thread.currentThread().getName();
    Random randomGen = new Random();

    System.out.println( " Thread " + threadName + " Starting");

    // Loop for for the number times requested, calling G2 each time
    try {
      for (int i=0; i<thisLoop; i++) {


/* broken
	// Set the Items A-INT and A-FLOAT attributes
	double f = (int)Math.abs(randomGen.nextFloat()*1000);
	threadObject.setAInt((int)f);
	threadObject.setAFloat(f);
	// Call A-TEST-METHOD on this object
	threadObject.testMethod("Hi There called Proxy Method " + threadName );
	// Get its A-SEQUENCE and A-STRUCTURE attribute
	// Demonstrate calling a bean interafce on a G2 object.

	int aInt = threadObject.getAInt();
	Structure struct = threadObject.getAStructure();
	Sequence seq = threadObject.getASequence();



	if (_enableOutput)
	    System.out.println("Current Value of A-INT is " + aInt);

	// Call JAVA-CALL-2 with the sequence and structures just read
	retval = g2JavaCall2(seq, struct);
*/
	// Let other threads have a look in
	Thread.currentThread().yield();
      }
    } catch (Exception E) {
       System.out.println(E.toString());
    }

    System.out.println("Thread " + threadName + " ending");

    // Remove thread from thread table
    _threadTable.remove(new Integer(Thread.currentThread().hashCode()));
  }


  // *****************************************************************
  // Methods expected by test KB

  /**
   * This methods is registered as callable from G2, So that G2 can "ask"
   * Java to add a G2EventSourceListener to a EVENT-SOURCE-CLASS instance passed
   * from G2. This allows us to test Java objects add themselves as
   * listeners to G2 events.
   */
/*  public void attachToG2EventSource(EventSourceClass eventSource) throws G2AccessException
  {
    eventSource.addG2_EventSourceListener(this);
  }
*/
  /**
   * Raise Exception of class given.
   */
  public void raiseException(String exception_name)
       throws Throwable
  {
    Class eclass = Class.forName(exception_name);

    Throwable throwable = (Throwable)eclass.newInstance();

    throw throwable;
  }




  /**
   * Start a Thread of execution that loops calling G2 loopCount times
   * as well as passing a ATestClass for the thread to use
   */
  public int startLoopThread(int loopCount, ATestClass itm) throws G2AccessException
  {
    _threadObject = itm;
    _threadLoopCount = loopCount;
    Thread newThread = new Thread(this);
    _threadTable.put(new Integer(newThread.hashCode()), newThread);
    newThread.start();
    return newThread.hashCode();
  }

  public void stopLoopThread(int thread_index) throws Exception
  {
    try {
      Thread thread = (Thread)_threadTable.get(new Integer(thread_index));
      thread.stop();
      System.out.println("Stopped thread for index " + thread_index);
    } catch (Exception E) { throw new Exception("Cant find Thread for index " + thread_index); }
  }

  /**
   * Turn the lots of output on/off
   */
  public void setOutput(boolean state)
  {
    _enableOutput = state;
  }

  /**
   * Set the Time message on the Parent applet
   */
  public void setAppletTime(double time)
  {

    System.out.println((long)time);
  }

  /**
   * Set the Message on the Parent applet
   */
  public void setAppletMessage(String message)
  {
    System.out.println(message);
  }




  /*
   * The next series of Methods , are different versions of
   * the method receiveSend. This tests that Javalink dispatches to the
   * correct method signature, when G2 sends different parameters types to
   * the same method name.
   */

  /**
   * Generic catch all for any Object sent
   * ff a match cant be found in any of the following signatures.
   */
  public Object receiveSend(Object obj)
  {
    if (_enableOutput) System.out.println("Generic Object Received Class " + obj.getClass() + "\nData " + obj.toString());
    return obj;
  }


 public void terminate()
 {  System.out.println("Test Harness Termination...\n");
    System.exit(0);
    System.out.println("Test Harness has a problem...\n");
 }

  // *****************************************************************

  /**
   * Main method
   */
  public static void main(String args[])
  {
    // If a Java class wishes to listen for unsolicited connections from a G2 Server
    // Then it must follow the following steps

	System.out.println("Test Threader Started...\n");


    // 1. Initialize the G2 Gateway Class
    try {
      G2Gateway.initialize(new String[] {"-listenerport", "22041"});
    }
    catch (AlreadyInitializedException E) { System.out.println(E.toString());};

    // 2. Set up a connection factory deal with unsolicited G2 connections
    G2Gateway.setConnectionHandlerFactory(new G2ConnectionHandlerFactory() {
      /**
       * To support G2ConnectionHandlerFactory, called when an unsolicated connection
       * is detected. It is the responsibility of this method to return a G2Connection
       * that will handle the new connection.
       */
      @Override
      public G2Connection createG2Connection(String connection_data)
	{
	  G2Gateway new_gateway = new G2Gateway();
	  ThThreader egw = new ThThreader(new_gateway);
	  return new_gateway;
	} });

    // 3. Startup the G2 gateway interface, allowing network connections and communication
    //    This is done after the connection handle factory is setup, just is case a
    //    G2 has already initiated an unsolicited connection
    G2Gateway.startup();

    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);

    String host = cmdline.getOptionValue("-g2host");
    String port = cmdline.getOptionValue("-g2port");
    boolean result = false;

    if (port != null || host != null)
      {
	//try to connect to a g2 if we are asked
	try {

	  G2Connection g2_connection =
	    G2Gateway.getOrMakeConnection((host == null ? "localhost" : host),
					  (port == null ? "1111" : port));

	  ThThreader egw = new ThThreader(g2_connection);

	  g2_connection.returnMessage("Connected to ThThreader \n");
	  System.out.println("ThThreader  Connected to G2 OK");

	} catch (Exception E) { System.out.println(E.toString()); }

      }

  }



}


