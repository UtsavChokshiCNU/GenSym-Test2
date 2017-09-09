package com.gensym.tests.jgi.testharness;

import java.util.Hashtable;
import java.util.Random;
import java.lang.Math.*;
import java.lang.reflect.*;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.Item;
import java.util.Enumeration;
import com.gensym.jgi.dataservice.*;
import com.gensym.classes.GsiDataService;
import com.gensym.classes.SymbolicVariable;
import com.gensym.classes.TextVariable;
import com.gensym.classes.LogicalVariable;
import com.gensym.classes.IntegerVariable;
import com.gensym.core.*;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2Access;
import com.gensym.util.VariableValueEvent;
import com.gensym.util.VariableValueListener;
import com.gensym.classes.VariableOrParameter;
import com.gensym.jgi.download.*;

import com.gensym.classes.modules.javalinktestharness.*;
import com.gensym.classes.modules.jgithmain.*;
import java.util.Vector;


/**
 * ThGI is the main Java class used by the G2 JavaLink testharness for accessing JavaLink.
 * The Java connection and tests are controlled from G2. It is better to trace each test from the
 * individual test instance inside the KB.
 * 
 * TBD..
 * .Split into more managable classes
 * .Framework for Java generated tests ?
 *
 * @author JP 9/97
 */
public class ThGI implements Runnable,
            G2ConnectionListener ,
            com.gensym.classes.modules.jgithmain.G2_EventSourceListener,
            DataServiceListener
{

//data service
  private DataService dataService = null;
  private Hashtable externalDataPointsTable = new Hashtable(211);
  private Scheduler scheduler = new Scheduler();
// eo data service

  private Hashtable _threadTable = new Hashtable();
  private int _threadLoopCount = 0;
  private boolean _enableOutput = true;
  private static ATestClass _threadObject = null;


  static    G2Connection G_connection ;
  static    ThGI G2_gw;
  static    G2Gateway new_gateway;

  private G2Connection g2Connection = null;
  private static String[] mailResultsTo;

  private Vector ThThreadings = new Vector(100);
    // The correct way to make a Symbol.
  public static final Symbol ITEM_ = Symbol.intern ("ITEM");
  public static final Symbol A_TEST_CLASS_INSTANCE_ = Symbol.intern ("TEST-QUANTITATIVE-PARAMETER");

  // Its good practice to pre lookup Symbols that will be used often
  private static Symbol _javaCallG2ProcNameSymbol =
    Symbol.intern("JAVA-CALL");

  private static Symbol _javaCall2G2ProcNameSymbol =
    Symbol.intern("JAVA-CALL-2");

  private static Symbol _javaReturnEventCall =
    Symbol.intern("JAVA-RETURN-EVENT-CALL");


  /**
   * Constructor
   */
  public ThGI(G2Connection connection)
  {
    this.g2Connection = connection;
    initializeLocalRPCs(connection);
    connection.addG2ConnectionListener(this);

//    com.gensym.jlp.JLPSupport.enableJLP(connection);

    // Declare a Dataservice for this connection, this listens for updates
    dataService = new DataService(connection, this);
    scheduler.start();
    System.out.println("Got connection...data service enabled");

  }




   /**
   * Initialize all Local RPC's used by this subclass, this method is called only once
   * just before the first connection.
   */
  public void initializeLocalRPCs(G2Connection con)
  {

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

        con.registerJavaMethod(this, "test_func",
           Symbol.intern("TEST_FUNC") );

    con.registerJavaMethod(this, "receiveSend",
    Symbol.intern("JAVA-RECEIVE-SEND-BY-HANDLE"));//,
    //			 true);



    con.registerJavaMethod(this,
			    "receiveSendCheckClass",
			    Symbol.intern("JAVA-RECEIVE-SEND-CHECK-CLASS"));

    con.registerJavaMethod(this,
			    "receiveSend",
			    Symbol.intern("JAVA-RECEIVE-SEND"));

    con.registerJavaMethod(this,
			    "receiveSend_int",
			    Symbol.intern("JAVA-RECEIVE-SEND-INT"));

    con.registerJavaMethod(this,
			    "receiveSend_int",
			    Symbol.intern("JAVA-RECEIVE-SEND-FULL-INT"));

    con.registerJavaMethod(this, "receiveSend_float",
			    Symbol.intern("JAVA-RECEIVE-SEND-FLOAT"));
    con.registerJavaMethod(this, "receiveSend_byte",
			    Symbol.intern("JAVA-RECEIVE-SEND-BYTE"));
    con.registerJavaMethod(this,"receiveSend_short",
			    Symbol.intern("JAVA-RECEIVE-SEND-SHORT"));
    con.registerJavaMethod(this,"receiveSend_long",
			    Symbol.intern("JAVA-RECEIVE-SEND-LONG"));
    con.registerJavaMethod(this,"receiveSend_char",
			    Symbol.intern("JAVA-RECEIVE-SEND-CHAR"));
    con.registerJavaMethod(this,"receiveSend_bool",
			    Symbol.intern("JAVA-RECEIVE-SEND-BOOL"));
    con.registerJavaMethod(this,"startLoopThread",
			    Symbol.intern("JAVA-START-LOOP-THREAD"));
    con.registerJavaMethod(this,"stopLoopThread",
			    Symbol.intern("JAVA-STOP-LOOP-THREAD"));
    con.registerJavaMethod(this,"initiateConnection",
			    Symbol.intern("JAVA-INITIATE-CONNECTION"));
    con.registerJavaMethod(this,"setOutput",
			    Symbol.intern("JAVA-SET-OUTPUT"));
    con.registerJavaMethod(this,"raiseException",
			    Symbol.intern("JAVA-RAISE-EXCEPTION"));

     con.registerJavaMethod(this,"hookEventHandler",
			    Symbol.intern("JAVA-HOOK-EVENT-HANDLER"));

    con.registerJavaMethod(this,"mailTestResults",
        Symbol.intern("JAVA-MAIL-TEST-RESULTS"));

    // Here we are declaring that two different G2 procedures will call
    // the same method name. The actual version of callJavaTestVararg depends
    // on the number of arguments sent down
    con.registerJavaMethod(this, "callJavaTestVararg",
			    Symbol.intern("CALL-JAVA-TEST-VARARG"));
    con.registerJavaMethod(this, "callJavaTestVararg",
			    Symbol.intern("CALL-JAVA-TEST-VARARG-WITH-HANDLE"));


    // serialization tests
    con.registerJavaMethod(this,
			    "getSer",
			    Symbol.intern("GET-SER"));


    con.registerJavaMethod(this,
          "receiveSendWs",
			    Symbol.intern("JAVA-RECEIVE-SEND-WS"));

   //new receiveSend methods

   con.registerJavaMethod(this,
			    "jReceiveSend",
			    Symbol.intern("J-JAVA-RECEIVE-SEND"));
    con.registerJavaMethod(this,
			    "jReceiveSend_int",
			    Symbol.intern("J-JAVA-RECEIVE-SEND-INT"));
    con.registerJavaMethod(this, "jReceiveSend_float",
			    Symbol.intern("J-JAVA-RECEIVE-SEND-FLOAT"));
    con.registerJavaMethod(this, "jReceiveSend_byte",
			    Symbol.intern("J-JAVA-RECEIVE-SEND-BYTE"));
    con.registerJavaMethod(this,"jReceiveSend_short",
			    Symbol.intern("J-JAVA-RECEIVE-SEND-SHORT"));
    con.registerJavaMethod(this,"jReceiveSend_long",
			    Symbol.intern("J-JAVA-RECEIVE-SEND-LONG"));
    con.registerJavaMethod(this,"jReceiveSend_char",
			    Symbol.intern("J-JAVA-RECEIVE-SEND-CHAR"));
    con.registerJavaMethod(this,"jReceiveSend_bool",
			    Symbol.intern("J-JAVA-RECEIVE-SEND-BOOL"));
   //---------------


    // We can also prelook up methods and register those as accessible by a G2Connection

    try {
      java.lang.reflect.Method method =
	    this.getClass().getDeclaredMethod("javaTestMethodParams",
					  new Class[] {String.class,
							 Boolean.TYPE,
							 Double.TYPE,
							 Integer.TYPE,
							 com.gensym.classes.Object.class});
      con.registerJavaMethod(this,
			      method,
			      Symbol.intern("JAVA-TEST-METHOD-PARAMS"),
			      false);

      con.registerJavaMethod(this,
			      method,
			      Symbol.intern("JAVA-TEST-METHOD-PARAMS-HANDLE"),
			      false);

     method =
	    this.getClass().getDeclaredMethod("threadedTestFunc",
					  new Class[] {Integer.TYPE});
      con.registerJavaMethod(this,
			      method,
			      Symbol.intern("THREADED_TEST_FUNC"),
			      true);


        con.registerJavaMethod(this,
			    "setForceDownload",
			    Symbol.intern("JAVA-SET-FORCE-DOWNLOAD"));


      java.lang.reflect.Method method2 =
	this.getClass().getDeclaredMethod("attachToG2EventSource",
					  new Class[] {EventSourceClass.class});

      con.registerJavaMethod(this,
			      method2,
			      Symbol.intern("JAVA-ATTACH-TO-G2-EVENT-SOURCE"),
			      false);


    } catch (NoSuchMethodException e) {
      System.err.println("Could not find Method " +
			 e.toString()); }

  }


  public void setForceDownload(boolean mode)
  {
         System.out.println("setGenerationMode "+mode);
	 if (mode)
         	new_gateway.setGenerationMode(StubClassLoader.GENERATION_AUTO);
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
    g2Connection.returnMessage("Connected to ThGI (rpis = " + remote_process_string + ")\n Hi There from G2Gateway Java VM, how are you G2 ?");

    // Also Send an error message
    g2Connection.reportLogBookErrorMessage
      (Symbol.intern("ERROR"),
       "Dont worry this message is just a test Error message from Java class ThGI");


    // Now lets call a G2 procedure, JAVA-CALL
    try {
      g2JavaCall(111,
		 "Hi from initiate connection",
		 Symbol.intern("SYMBOL"),
		 1.238293823,
		 false,
		 "A String object");

    } catch (Exception E) {
	System.out.println(E.toString());
    }
  }

  // *****************************************************************


  // *****************************************************************
  // To Implement G2_EventSourceListener exported from G2-EVENT-SOURCE-CLASS

  /**
   * To Implement G2_EventSourceListener exported from G2 Event
   * Generator class G2EventSourceClass.
   */
  public void anEvent(com.gensym.classes.modules.jgithmain.G2_EventSourceEvent arg1) throws G2AccessException
  {
    System.out.println("TH anEvent : Received an event..." + arg1.getMessage());

    Object args[] = new Object[] {new Boolean(true)};

    Object retval = g2Connection.callRPC(_javaReturnEventCall, args, 0);

  }


  public void  aTextEvent(com.gensym.classes.modules.jgithmain.G2_EventSourceEvent arg1) throws G2AccessException
  {
    System.out.println("TH aTextEvent: Received an event..." + arg1.getMessage());

    Object args[] = new Object[] {new Boolean(true)};

    Object retval = g2Connection.callRPC(_javaReturnEventCall, args, 0);

  }

    public void  aFloatEvent(com.gensym.classes.modules.jgithmain.G2_EventSourceEvent arg1) throws G2AccessException
  {
    System.out.println("TH aFloatEvent : Received an event..." + arg1.getMessage());

    Object args[] = new Object[] {new Boolean(true)};

    Object retval = g2Connection.callRPC(_javaReturnEventCall, args, 0);

  }
  

  // *****************************************************************


  public void test_func(int j)
  { 
    Object args[] = new Object[1];
	
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
  { 
    Object args[] = new Object[1];
    int z;
    z = 0;
    for (int i=0; i< 20000; i++ ){
      z = z + 1;
      z = i + z;
    }

    System.out.println("TF(T):" + j);
    
    args[0] = new Integer( j ) ;
    g2Connection.startRPC(Symbol.intern("JAVA-TH-RECEIVER"), args );
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

    System.out.println("Thread " + threadName + " Starting");

    // Loop for for the number times requested, calling G2 each time
    try {
      for (int i=0; i<thisLoop; i++) {

	int retval = g2JavaCall(i,
				"Hi there a Java Thread "+ threadName,
				Symbol.intern("A-SYMBOL"),
				randomGen.nextFloat()*1000,
				true,
				threadObject);


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
    } catch (G2AccessException E) {
       System.out.println(E.toString());
    }

    System.out.println("Thread " + threadName + " ending");

    // Remove thread from thread table
    _threadTable.remove(new Integer(Thread.currentThread().hashCode()));
  }

  // ******************************************************************
  // Methods to call know G2 Procedures

 /**
   * Call JAVA-CALL acorss the connected G2.
   * JAVA-CALL(integer, text, symbol, float, truth-value, class item) = ( integer)
   */
  public int g2JavaCall(int intParam,
			String strParam,
			Symbol symParam,
			double dblParam,
			boolean booleanParam,
			Object itemParam) throws G2AccessException {

    // Set params up call to
    // JAVA-CALL(integer, text, symbol, float, truth-value, class item) = ( integer)
    Object args[] = new Object[] {new Integer(intParam),
				    strParam,
				    symParam,
				    new Double(dblParam),
				    new Boolean(booleanParam),
				    itemParam};

    Object retval = g2Connection.callRPC(_javaCallG2ProcNameSymbol, args, 0);
    return ((Integer)retval).intValue();
  }

  
  // Mail results, only if mail address specified
  public void mailTestResults(String subject , String msg) throws Throwable
  {
    String host = "hqmail";
    String from = "testHarness";

    if (mailResultsTo != null) {
      if (mailResultsTo.length > 0) {
	Class[] sendSig = new Class[] {String.class,
					 String.class,
					 (new String[0]).getClass(),
					 String.class,
				       String.class};

	// Use reflection here as javaMail may not be setup
	Class mailClass = Class.forName("com.gensym.tests.jgi.testharness.MailSender");
	Method method = mailClass.getMethod("send", sendSig);
	Object[] args = new Object[] {host, from, mailResultsTo, subject, msg};
	try {
	  method.invoke(null, args);
	} catch (InvocationTargetException e) {
	  throw e.getTargetException();
	}
      }
    }
  }



  /**
   * Call JAVA-CALL2 across the connected G2.
   * JAVA-CALL2(Sequence, Structure) = ( integer)
   */
  public int g2JavaCall2(Sequence seqParam,
			 Structure structParam) throws G2AccessException {

    // Set params up call to
    // JAVA-CALL2(Sequence, Structure) = ( integer)
    Object args[] = new Object[] {seqParam,
				    structParam,};

    Object retval = g2Connection.callRPC(_javaCall2G2ProcNameSymbol, args, 0);
    return ((Integer)retval).intValue();
  }

  // *****************************************************************
  // Methods expected by test KB

  /**
   * This methods is registered as callable from G2, So that G2 can "ask"
   * Java to add a G2EventSourceListener to a EVENT-SOURCE-CLASS instance passed
   * from G2. This allows us to test Java objects add themselves as
   * listeners to G2 events.
   */
  public void attachToG2EventSource(com.gensym.classes.modules.jgithmain.EventSourceClass eventSource) throws G2AccessException
  {
    eventSource.addG2_EventSourceListener(this);
  }

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


  public void callJavaTestVararg(int item1 )
       throws G2AccessException
  {
    System.out.println("*** Sanity Check :o) ");

    System.out.println("MT" + item1 + " " + Runtime.getRuntime().freeMemory());

    Object args[] = { new Integer(item1) };
    g2Connection.startRPC(Symbol.intern("SIMPLE_CALLBACK"), args );
  }


  /**
   * Method to test Variable argument calling - one argument
   */
  public void callNoReturnJavaTestVararg( ATestClass item, String item1 )
       throws G2AccessException
  {
    //System.out.println("ASymbol is " + item.getASymbol().toString());
    if (item.isItemLocal())
      {
	//System.out.println("Got item " + item.getAttributes());

	// G2 RPC's with first args set a object, will cause a method lookup
	Object args[] = { item, item1 };
	g2Connection.callRPC(Symbol.intern("A-TEST-METHOD-VARARG"), args,0 );
      }
    else
      {
	// The Item was passed as a remote object, we can ask the stub to call the
	// the G2 method for us.
	item.aTestMethodVararg(item1);
      }
  }

  /**
   * Method to test Variable argument calling - two arguments
   */
  public void callNoReturnJavaTestVararg(ATestClass item, String item1, Sequence item2)
       throws G2AccessException
  {
    if (item.isItemLocal())
      {
	// G2 RPC's with first args set a object, will cause a method lookup
	Object args[] = { item, item1, item2 };
	g2Connection.callRPC(Symbol.intern("A-TEST-METHOD-VARARG"), args, 0);
      }
    else
      {
	// The Item was passed as a remote object, we can ask the stub to call the
	// the G2 method for us.
	item.aTestMethodVararg(item1, item2);
      }
  }



//- with return values
/**
   * Method to test Variable argument calling - one argument
   */
  public int callJavaTestVararg( ATestClass item, String item1 )
       throws G2AccessException
  { int rv=0;

     System.out.println("*** 2nd Sanity Check :o) ");


    //System.out.println("ASymbol is " + item.getASymbol().toString());
    if (item.isItemLocal())
      {
	//System.out.println("Got item " + item.getAttributes());

	// G2 RPC's with first args set a object, will cause a method lookup
	Object args[] = { item, item1 };
	g2Connection.callRPC(Symbol.intern("A-TEST-METHOD-VARARG"), args,0 );
     rv = 2; }
    else
      {
	// The Item was passed as a remote object, we can ask the stub to call the
	// the G2 method for us.
	item.aTestMethodVararg(item1);
	rv  = 1;
      }

      return (100 + rv);
  }

  /**
   * Method to test Variable argument calling - two arguments
   */
  public int callJavaTestVararg(ATestClass item, String item1, Sequence item2)
       throws G2AccessException
  {
    if (item.isItemLocal())
      {
	// G2 RPC's with first args set a object, will cause a method lookup
	Object args[] = { item, item1, item2 };
	g2Connection.callRPC(Symbol.intern("A-TEST-METHOD-VARARG"), args, 0);
	return 3;
      }
    else
      {
	// The Item was passed as a remote object, we can ask the stub to call the
	// the G2 method for us.
	item.aTestMethodVararg(item1, item2);
	return 2;
      }
  }



//



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



  /**
   * This Method receives various parameter types from G2.
   * As the item parameter refers to a local Item, we can set its name
   * and sent it pack to G2.
   */
  public Object javaTestMethodParams( String itemstr,
				      boolean item1,
				      double item2,
				      int item3,
				      com.gensym.classes.Object item4) throws G2AccessException
  {
    //System.out.println(itemstr);
    //System.out.println(item1);
    //System.out.println(item2);
    //System.out.println(item3 + 10);

    if (_enableOutput) {
      System.out.println("Received G2-CLASS " + item4.getG2ClassName());
      System.out.println("Its G2 Name is " + item4.getNames());
    }

    // Change items name if its local
    if (item4.isItemLocal())
      item4.setNames(Symbol.intern("JAVA-CHANGED-THIS-"+item3));

    return item4;

  }


  static public void startThThreads(ThGI egw, G2Connection con ,int i)
  {int j;
   System.out.println("starting "+ i + " Th Threads\n");
        for (j = 1;j < i;j++) {
              ThThreader  t = new ThThreader(con,j);
              egw.ThThreadings.addElement(t);
              System.out.println(j+"\n");
        }


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

  public Object receiveSendCheckClass(com.gensym.classes.Item obj, Symbol g2ClassName) throws G2AccessException {
	if (_enableOutput) System.out.println("ItemImpl Object Received Class " + obj.toString() + " Should have "  + g2ClassName);
	if (!obj.getG2ClassName().equals(g2ClassName))
	   throw new ClassCastException("Received Class " + obj.getClass() + " should have been " + " an stub for " + g2ClassName);
    return obj;
  }

  public Object receiveSend(Sequence seq)
  {
    if (_enableOutput) System.out.println("Received Sequence " + seq.toString());
    return seq;
  }


  public Object receiveSend(Structure struct) throws Exception
  {
    if (_enableOutput) System.out.println("Received Structure " + struct.toString());

    return struct;
  }

  public Object receiveSend(com.gensym.classes.G2Array obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("Received G2Array " + obj.toString());
   // receiveSend(obj.getG2ArraySequence().getContents());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.ItemArray obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("Received ItemArray " + obj.toString());
    //receiveSend(obj.getG2ArraySequence().getContents());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.ValueArray obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("Received ValueArray " + obj.toString());
    //receiveSend(obj.getG2ArraySequence().getContents());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.FloatArray obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("Received FloatArray " + obj.toString());
    //receiveSend(obj.getG2ArraySequence().getContents());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.TextArray obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("Received TextArray " + obj.toString());
    //receiveSend(obj.getG2ArraySequence().getContents());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.SymbolArray obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("Received SymbolArray " + obj.toString());
    //receiveSend(obj.getG2ArraySequence().getContents());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.TruthValueArray obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("Received TruthValueArray " + obj.toString());
    //receiveSend(obj.getG2ArraySequence().getContents());
    return obj;
  }


  public Object receiveSend(com.gensym.classes.QuantityArray obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("Received TextArray " + obj.toString());
    //receiveSend(obj.getG2ArraySequence().getContents());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.IntegerArray obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("Received IntegerArray " + obj.toString());
    //receiveSend(obj.getG2ArraySequence().getContents());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.IntegerList obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("Received IntegerList " + obj.toString());
    receiveSend(obj.getG2ListSequence().getContents());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.FloatList obj)
  {
    if (_enableOutput) System.out.println("Received FloatList " + obj.toString());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.TruthValueList obj)
  {
    if (_enableOutput) System.out.println("Received TruthValueList " + obj.toString());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.SymbolList obj)
  {
    if (_enableOutput) System.out.println("Received SymbolList " + obj.toString());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.TextList obj)
  {
    if (_enableOutput) System.out.println("Received TextList " + obj.toString());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.ItemList obj)
  {
    if (_enableOutput) System.out.println("Received ItemList " + obj.toString());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.QuantityList obj)
  {
    if (_enableOutput) System.out.println("Received QuantityList " + obj.toString());
    return obj;
  }


  public Object receiveSend(com.gensym.classes.ValueList obj)
  {
    if (_enableOutput) System.out.println("Received ValueList " + obj.toString());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.G2List obj)
  {
    if (_enableOutput) System.out.println("Received G2List " + obj.toString());
    return obj;
  }

  public Object receiveSend(Symbol obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("Received Symbol " + obj.toString());

    return obj;
  }

  public Object receiveSend(String obj)
  {
    if (_enableOutput) System.out.println("Received String " + obj.toString());
    return obj;
  }

  public int receiveSend_int(int integer)
  {
    if (_enableOutput) System.out.println("Received Integer " + integer);
    return integer;
    //return 10 + 536870911; // OF > 30 bits for G2
  }

  public boolean receiveSend_bool(boolean bool)
  {
    if (_enableOutput) System.out.println("Received boolean"  + bool);
    return bool;
  }

  public double receiveSend_float(double flt)
  {
    if (_enableOutput) System.out.println("Received float " + flt);
    return flt;
  }

  public byte receiveSend_byte(byte byt)
  {
    if (_enableOutput) System.out.println("Receive byte " + byt);
    return byt;
  }

  public short receiveSend_short(short sht)
  {
    if (_enableOutput) System.out.println("Received short " + sht);
    return sht;
  }

  public long receiveSend_long(long lng)
  {
    if (_enableOutput) System.out.println("Received long " + lng);
    return lng;
  }

  public char receiveSend_char(char ch)
  {
    if (_enableOutput) System.out.println("Received char " + ch);
    return ch;
  }

  public Object receiveSend(double array[])
  {
    if (_enableOutput)
      {
	System.out.println("Received double array"  + array);
	for (int i=0; i<array.length; i++ )
	  System.out.println("Element["+i+"] = "+ array[i]);
      }
    return array;
  }

  public Object receiveSend(int array[])
  {
    if (_enableOutput)
      {
	System.out.println("Received integer"  + array);
	for (int i=0; i<array.length; i++ )
	  if (_enableOutput) System.out.println("Element["+i+"] = "+ array[i]);
      }
    return array;
  }


  public Object receiveSend(Symbol array[])
  {
    if (_enableOutput)
      {
	System.out.println("Received Symbol"  + array);
	for (int i=0; i<array.length; i++ )
	  System.out.println("Element["+i+"] = "+ array[i].toString());
      }
    return array;
  }

  public Object receiveSend(String array[])
  {
    if (_enableOutput)
      {
	System.out.println("Received String array"  + array);
	for (int i=0; i<array.length; i++ )
	  System.out.println("Element["+i+"] = "+ array[i]);
      }
    return array;
  }

  public Object receiveSend(Object array[])
  {
    if (_enableOutput)
      {
	System.out.println("Received Object array"  + array);
	for (int i=0; i<array.length; i++ )
	  System.out.println("Element["+i+"] = "+ array[i].toString());
      }
    return array;
  }

  public Object receiveSend(Number array[])
  {
    if (_enableOutput) {
      System.out.println("Received Number array"  + array);
      for (int i=0; i<array.length; i++ )
	System.out.println("Element["+i+"] = "+ array[i].toString());
    }
    return array;
  }

  public Object receiveSend(boolean array[])
  {
    if (_enableOutput)
      {
	System.out.println("Received boolean array"  + array);
	for (int i=0; i<array.length; i++ )
	  System.out.println("Element["+i+"] = "+ array[i]);
      }
    return array;
  }


  //*********************************


  public Object jReceiveSend(com.gensym.classes.G2Array obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("J-Received G2Array " + obj.toString());
    receiveSend((Object[])obj.getG2ArrayContents());
    obj.setG2ArrayContents(obj.getG2ArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    return obj;
  }
  public Object jReceiveSend(com.gensym.classes.ItemArray obj) throws G2AccessException
  {    if (_enableOutput) System.out.println("J-Received ItemArray " + obj.toString());
    receiveSend((Object[])obj.getG2ArrayContents());
    obj.setG2ArrayContents(obj.getG2ArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    com.gensym.classes.ItemArray ia2 = null;
    try {
      ia2 = (com.gensym.classes.ItemArray)
	G2StubResolver.createStubForG2Interface(com.gensym.classes.ItemArray.class);
      ia2.setG2ArrayContents(obj.getG2ArrayContents());
    } catch (Exception ex1) { throw new G2AccessException(ex1, ex1.toString()); }
    return ia2;
  }

  public Object jReceiveSend(com.gensym.classes.ValueArray obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("J-Received ValueArray " + obj.toString());
    receiveSend((Object[])obj.getG2ArrayContents());
    obj.setG2ArrayContents(obj.getG2ArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    return obj;
  }  
 
 public Object jReceiveSend(com.gensym.classes.FloatArray obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("J-Received FloatArray " + obj.toString());
    receiveSend(obj.getFloatArrayContents());
    obj.setG2ArrayContents(obj.getFloatArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    return obj;
  }  

  public Object jReceiveSend(com.gensym.classes.TextArray obj) throws G2AccessException
  {    if (_enableOutput) System.out.println("J-Received TextArray " + obj.toString());
    receiveSend(obj.getTextArrayContents());
    obj.setG2ArrayContents(obj.getTextArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    return obj;
  }
  
  public Object jReceiveSend(com.gensym.classes.SymbolArray obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("J-Received SymbolArray " + obj.toString());
    receiveSend(obj.getSymbolArrayContents());
    obj.setG2ArrayContents(obj.getSymbolArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    return obj;
  }  
  public Object jReceiveSend(com.gensym.classes.TruthValueArray obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("J-Received TruthValueArray " + obj.toString());
    receiveSend(obj.getTruthValueArrayContents());
    obj.setG2ArrayContents(obj.getG2ArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    return obj;
  }
 
 public Object jReceiveSend(com.gensym.classes.QuantityArray obj) throws G2AccessException  {
    if (_enableOutput) System.out.println("J-Received QuantityArray " + obj.toString());
    receiveSend((Number[])obj.getG2ArrayContents());
    obj.setG2ArrayContents(obj.getG2ArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    return obj;
  }
 
 public Object jReceiveSend(com.gensym.classes.IntegerArray obj) throws G2AccessException
 {    if (_enableOutput) System.out.println("J-Received IntegerArray " + obj.toString());
    receiveSend(obj.getIntegerArrayContents());
    obj.setG2ArrayContents(obj.getIntegerArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    com.gensym.classes.IntegerArray ia2 = null;
    try {
      ia2 = (com.gensym.classes.IntegerArray)	G2StubResolver.createStubForG2Interface(com.gensym.classes.IntegerArray.class);
      ia2.setG2ArrayContents(obj.getIntegerArrayContents());
    } catch (Exception  ex2) { throw new G2AccessException(ex2, ex2.toString()); }
    return ia2;
  }  

  Object createNewList(Class listClass, Sequence contents) throws G2AccessException {
    com.gensym.classes.G2List list = null;
    try {
      list = (com.gensym.classes.G2List)G2StubResolver.createStubForG2Interface(listClass);
      list.setG2ListSequence(contents);
    } catch (Exception ex3) {
      ex3.printStackTrace();
      throw new G2AccessException(ex3.toString());
    }
    return list;  
  }
 
 public Object jReceiveSend(com.gensym.classes.IntegerList obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("J-Received IntegerList " + obj.toString());
    receiveSend(obj.getG2ListSequence());
    return createNewList(com.gensym.classes.IntegerList.class, obj.getG2ListSequence());
  }  

  public Object jReceiveSend(com.gensym.classes.FloatList obj) throws G2AccessException
  {    if (_enableOutput) System.out.println("vReceived FloatList " + obj.toString());
  return createNewList(com.gensym.classes.FloatList.class, obj.getG2ListSequence());  
  }  

  public Object jReceiveSend(com.gensym.classes.TruthValueList obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("J-Received TruthValueList " + obj.toString());
    return createNewList(com.gensym.classes.TruthValueList.class, obj.getG2ListSequence());
  }  

  public Object jReceiveSend(com.gensym.classes.SymbolList obj) throws G2AccessException
  {    if (_enableOutput) System.out.println("J-Received SymbolList " + obj.toString());
    return createNewList(com.gensym.classes.SymbolList.class, obj.getG2ListSequence());
    //return obj;
  }  

  public Object jReceiveSend(com.gensym.classes.TextList obj) throws G2AccessException  
  {
    if (_enableOutput) System.out.println("J-Received TextList " + obj.toString());
    return createNewList(com.gensym.classes.TextList.class, obj.getG2ListSequence());
    //return obj; 
 }  

  public Object jReceiveSend(com.gensym.classes.ItemList obj) throws G2AccessException
  {    if (_enableOutput) System.out.println("J-Received ItemList " + obj.toString());
     return createNewList(com.gensym.classes.ItemList.class, obj.getG2ListSequence());
     //return obj;  
  } 

 public Object jReceiveSend(com.gensym.classes.QuantityList obj) throws G2AccessException  
  {
    if (_enableOutput) System.out.println("J-Received QuantityList " + obj.toString());
    return createNewList(com.gensym.classes.QuantityList.class, obj.getG2ListSequence());
    // return obj;  
  }  

  public Object jReceiveSend(com.gensym.classes.ValueList obj) throws G2AccessException
  {    
    if (_enableOutput) System.out.println("J-Received ValueList " + obj.toString());
    return createNewList(com.gensym.classes.ValueList.class, obj.getG2ListSequence());
    // return obj;  
  }  

  public Object jReceiveSend(com.gensym.classes.G2List obj) throws G2AccessException
  {
    if (_enableOutput) System.out.println("J-Received G2List " + obj.toString());
      return createNewList(com.gensym.classes.G2List.class, obj.getG2ListSequence());
      //return obj;  
  }
  //*********************************







 public void terminate()
 {  System.out.println("Test Harness Termination...\n");
    System.exit(0);
    System.out.println("Test Harness has a problem...\n");
 }




  //************** serialization *************************************
  // Receive a obj from G2 By-copy, serialize it and save yo a file
  //
  public boolean receiveSendWs(com.gensym.classes.Item obj) {
    System.out.println("Serialization Test " + obj + " Was received ");
    try {
      java.io.FileOutputStream f = new java.io.FileOutputStream("ws.ser");
      java.io.ObjectOutput s = new java.io.ObjectOutputStream(f);
      s.writeObject (obj);
    } catch (Exception e) { 
      e.printStackTrace();
      return true; // it failed
    } return false; // it passed
  }  

  // Deserialize the obj from a file and send back to G2.
  public Object getSer() throws Exception {
    java.io.InputStream dataStrm =
      new java.io.FileInputStream("ws.ser");
    java.io.ObjectInput s = new java.io.ObjectInputStream (dataStrm);
    Object obj = s.readObject();
    s.close ();
    System.out.println(obj);
    return obj;  
  }



  // *****************************************************************

  /**
   * Main method
   */

   /*
         String classString = cmdLine.getOptionValue ("-class");
    String nameString  = cmdLine.getOptionValue ("-name");
    // convert the strings to symbols
    Symbol clazz = (classString == null ? ITEM_ :
		    Symbol.intern(classString.toUpperCase()));
    Symbol name = (nameString == null ? A_TEST_CLASS_INSTANCE_ :
		   Symbol.intern(nameString.toUpperCase()));

   */


  public void hookEventHandler(String host , String port ,
			       String classString , Symbol clazz ,String nameString )
  {
    G2Connection g2_connection=null;
    Symbol name = (nameString == null ? A_TEST_CLASS_INSTANCE_ :
		   Symbol.intern(nameString.toUpperCase()));
    
    System.out.println("**IN hookEventHandler**");
    
    //try to connect to a g2 if we are asked
    try {
      
      g2_connection  =
	G2Gateway.getOrMakeConnection((host == null ? "localhost" : host),
				      (port == null ? "1111" : port));
      
      ThGI egw = new ThGI(g2_connection);
      
      //G_gw = egw;
      G_connection=g2_connection;
      g2_connection.returnMessage("Connected to ThGI \n Hi There from G2Gateway Java VM, how are you G2 ?");
      System.out.println("Connected to G2 OK");
      
    } catch (Exception E) { System.out.println(E.toString()); }
    
    try{
      VariableOrParameter item = (VariableOrParameter)(g2_connection.getUniqueNamedItem(clazz, name));
    }catch (Exception Ex) { System.out.println(Ex.toString()); }
    // Define a simple implementation of the ItemListener interface
    VariableValueListener vil =
      new VariableValueListener() {
      @Override
      public void valueChanged(VariableValueEvent e) {
	System.out.println("valueChanged: " + e);
      }
      
      @Override
      public void receivedInitialValue(VariableValueEvent e) {
	System.out.println("receivedInitialValues: " + e);
      }
    };
    
    
  }

//------------data service code

  private ExternalDataPoint getExternalDataPointFromIdentifingAttributes(Object[] identAtts,
									 GsiDataService g2Variable) {
    // Here we would work out which external data point to assoicate with
    // the g2Variable, depending on its identAtts
    // .....
    ExternalDataPoint dataPoint = new ExternalDataPoint(identAtts, g2Variable);
    externalDataPointsTable.put(g2Variable, dataPoint);
    return dataPoint;
  }
  
  // Implement DataServiceListener, which provides all DataService callbacks
  
  /**
   * setData is called by G2 when a value has been set on a Gsi Variable using the SET action.
   */
  @Override
  public void setData(DataServiceEvent e) {
    GsiDataService g2Var = e.getDataItem();
    System.out.println("setData being called for " + e.getDataItem() +
		       " set value is " +e.getValue());
    try {
      ExternalDataPoint dataPoint = (ExternalDataPoint)externalDataPointsTable.get(g2Var);
      dataPoint.setExternalValue(e.getValue());
      dataPoint.updateG2();  // make sure that G2 reflects the new external value
    } catch (G2AccessException E) {
      System.out.println("During setData ");
      E.printStackTrace();
    }
  }
  
  /**
   * getData is called by G2 when it requires a new value from the external system for a Gsi Variable.
   */
  @Override
  public void getData(DataServiceEvent e) {
    GsiDataService g2Var = e.getDataItem();
    //System.out.println("getData being called for " + e.getDataItem());
    try {
      ExternalDataPoint dataPoint = (ExternalDataPoint)externalDataPointsTable.get(g2Var);
      dataPoint.updateG2();
    } catch (G2AccessException E) {
      System.out.println("During getData ");
      E.printStackTrace();
    }
  }

  /**
   * variableRegistration is called when a Variable in G2 requires servicing from a DataService.
   */
  @Override
  public void variableRegistration(DataServiceEvent e) {
    GsiDataService g2Var = e.getDataItem();
    System.out.println("In variableRegistration for " + g2Var);
    Object[] identifyingAttributes = e.getIdentifingAttributes();
    for (int i = 0; i<identifyingAttributes.length; i++)
      System.out.println("Identifying Attribute " + i + " = " + identifyingAttributes[i]);

    ExternalDataPoint dataPoint = getExternalDataPointFromIdentifingAttributes(identifyingAttributes, g2Var);
    try {
      dataPoint.updateG2();  // Must update G2 with the external variable value on registration
                             // to ensure that G2 knows that this variable has a value and will update
                             // it (via getData)
    } catch (G2AccessException E) {
      System.out.println("During variableRegistration ");
      E.printStackTrace();
    }

  }

  /**
   * variableDeregistration is called by G2 when the variable (previously registered on a DataService)
   * is no longer available (disabled, deleted, or G2 reset/restarted).
   */
  @Override
  public void variableDeregistration(DataServiceEvent e) {
    System.out.println("Variable Deregistration of " + e.getDataItem());
    GsiDataService g2Var = e.getDataItem();
    ExternalDataPoint dataPoint = (ExternalDataPoint)externalDataPointsTable.remove(g2Var);
    if (dataPoint != null)
      dataPoint.setDeregistered();
  }

  // End Implement DataServiceListener

  private static Random random = new Random();

  // Inner class to simulate an ExternalDataPoint

  class ExternalDataPoint {

    int    status = 1;
    Object[] identAtts = null;
    int externalUpdateRate = 1; // 100ms
    long lastUpdate = 0;
    GsiDataService g2Variable = null;
    Object lastValue = null;

    public ExternalDataPoint(Object[] identAtts, GsiDataService g2Variable) {
      this.identAtts = identAtts;
      this.g2Variable = g2Variable;
      // We can set the externalUpdateRate from the first IdentAtt
      if ((identAtts.length>0) && (identAtts[0].getClass() == Integer.class)) {
	externalUpdateRate = (int)((Integer)identAtts[0]).intValue();
	System.out.println("externalUpdateRate = " + externalUpdateRate);
      }
    }

    public void setDeregistered() {
      g2Variable = null;  // + Any thing else to the Extrenal Data point.
    }

    public int getExternalUpdateRate() {
	return externalUpdateRate;
    }

    public long getLastUpdate() {
      return lastUpdate;
    }

    public void setLastUpdate(long lastUpdate) {
      this.lastUpdate = lastUpdate;
    }

    public Object getExternalValue() {
      if (g2Variable == null) return null;
      // Here we would fetch the new value
      if (g2Variable instanceof SymbolicVariable)
	lastValue = Symbol.intern("DATA-SERVER-SYMBOL");
      else if (g2Variable instanceof TextVariable)
	lastValue = "Current millis " + System.currentTimeMillis();
      else if (g2Variable instanceof LogicalVariable)
	lastValue =  Boolean.TRUE ;
      else if (g2Variable instanceof IntegerVariable)
	lastValue = new Integer((int)(random.nextDouble()*10) + 1);
      else // quantity, float or integer
	lastValue = new Double(random.nextDouble() + 1.0); // simulation, just return random value
      return lastValue;
    }


    public void setExternalValue(Object value) {
      // simulation do nothing !
      // Must work out what value type is
      lastValue = value;
    }

    public int getExternalStatus() {
      // Here we would fetch the internal status
      return (int)(random.nextDouble() * 10); // simulation, just return a random value
    }

    public void updateG2() throws G2AccessException {
       if (g2Variable == null) return;
      if (lastValue == null) getExternalValue();
      g2Variable.setGsiVariableValue(lastValue, getExternalStatus());
    }

  }

  // Inner class to schedule unsolicited updates back to registered variables
  class Scheduler extends Thread {

    @Override
    public void run() {
      Vector pointsToUpdate = new Vector(10);
      for (;;) {
	// Collect all External Data points to update
	long currentTime = System.currentTimeMillis();
	for (Enumeration e = externalDataPointsTable.keys(); e.hasMoreElements();) {

	  GsiDataService g2Variable = (GsiDataService)e.nextElement();
	  ExternalDataPoint dataPoint = (ExternalDataPoint)externalDataPointsTable.get(g2Variable);

	  if (dataPoint.getExternalUpdateRate() > 0 && // 0 means no unsolicated updates
	      ((currentTime - dataPoint.getLastUpdate()) >
	       (dataPoint.getExternalUpdateRate() * 100))) { //100ms
	    g2Variable.storeGsiVariableStatus(dataPoint.getExternalStatus());
	    g2Variable.storeGsiVariableValue(dataPoint.getExternalValue());
	    pointsToUpdate.addElement(g2Variable);
	    dataPoint.setLastUpdate(currentTime);
	  }
	}
	// Return the value for these variables in one batch
	GsiDataService[] pointsToUpdateArray = new GsiDataService[pointsToUpdate.size()];
	//System.out.println("Sending " + pointsToUpdateArray.length + " var updates to G2 ");
	pointsToUpdate.copyInto(pointsToUpdateArray);
	try {

	  dataService.returnValues(pointsToUpdateArray);

	} catch (G2CommunicationException E) {
	  System.out.println("In scheduler returnValues ");
	  E.printStackTrace();
	} catch (G2AccessException E) {
	  System.out.println("In scheduler returnValues ");
	  E.printStackTrace();
	  }
	pointsToUpdate.removeAllElements();

	try {
	  Thread.sleep(100);
	} catch (Exception e) {}
      }
    }
  }
//---------- eo data service code

  public static void main(String args[])
  {
    
    System.out.println("Test Harness Started...T1.4 (07/May/99)\n");

    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);
    mailResultsTo = cmdline.getOptionValues("-mailto");
	
    try {
      G2Gateway.initialize(new String[] {"-listenerport", "22101"});
    }
    catch (AlreadyInitializedException E) { System.out.println(E.toString());};
    
    G2Gateway.setConnectionHandlerFactory(new G2ConnectionHandlerFactory() {
      
      @Override
      public G2Connection createG2Connection(String connection_data)
	{
	  new_gateway = new G2Gateway();
	  ThGI egw = new ThGI(new_gateway);
	  return new_gateway;
	} });
    
    
    G2Gateway.startup();

    String host = cmdline.getOptionValue("-g2host");
    String port = cmdline.getOptionValue("-g2port");
    String tsname = cmdline.getOptionValue("-tsName");
    boolean result = false;

    if (port != null || host != null)
      {
	//try to connect to a g2 if we are asked
	try {
	  
	  G2Connection g2_connection  =
	    G2Gateway.getOrMakeConnection(tsname,
					  (host == null ? "localhost" : host),
					  (port == null ? "1111" : port));
	  
	  ThGI egw = new ThGI(g2_connection);
	  
	  //G_gw = egw;
	  G_connection=g2_connection;
	  g2_connection.returnMessage("Connected to ThGI \n Hi There from G2Gateway Java VM, how are you G2 ?");
	  System.out.println("Connected to G2 OK");
	  
	} catch (Exception E) { System.out.println(E.toString()); }
	
      }
    //startThThreads(G_gw ,G_connection,50);
  }
  
  
  
}








