/*
 * 
 * Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 * 
 * GENSYM MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
 * SOFTWARE, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, OR NON-INFRINGEMENT. GENSYM SHALL NOT BE LIABLE FOR ANY DAMAGES
 * SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
 * THIS SOFTWARE OR ITS DERIVATIVES.
 * 
 */
package com.gensym.demos.jgi;

import java.util.Hashtable;
import java.util.Date;
import java.awt.*;
import java.security.SecureRandom;

import com.gensym.jgi.*;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.util.*;
import com.gensym.jgi.download.G2StubResolver;
import com.gensym.jgi.download.G2StubCreationException;
import com.gensym.classes.modules.jgidemo.*;

/**
 * G2 Gateway/Java Test Class to be used with jgidemo.kb.
 * This class demonstrates the use of Javalink as a means to communicate
 * with a G2 server via RPC's to G2 from Java and G2 to Java Methods. It  
 * shows how complex and simple data and objects are mapped between the
 * the two systems. It also demonstrates multiple thread accessing a 
 * G2 connection.
 * To use:
 * <p>1. make sure jgidemo.kb is loaded and started, 
 * <p>2. run this class: java com.gensym.demos.jgi.ExampleG2Gateway
 * <p>3. Press the connect button in G2
 * <P>4. Follow instructions in the G2 Kb
 *
 */
public class ExampleG2Gateway implements Runnable, G2ConnectionListener, G2_EventSourceListener
{
  private Hashtable _threadTable = new Hashtable();
  private int _threadLoopCount = 0;
  private boolean _enableOutput = true;
  private static volatile ATestClass _threadObject = null;
  private static UnicodeDisplay _unicodeDisplay = new UnicodeDisplay();
  private G2Connection g2Connection = null;

  // Its good practice to pre lookup Symbols that will be used often
  private static Symbol _javaCallG2ProcNameSymbol = Symbol.intern("JAVA-CALL");
  private static Symbol _javaCall2G2ProcNameSymbol = Symbol.intern("JAVA-CALL-2");

  /**
   * Constructor
   */
  public ExampleG2Gateway(G2Connection connection)
  {
    this.g2Connection = connection;
    initializeLocalRPCs(connection);
    connection.addG2ConnectionListener(this);
  }

  private static Class gensymObjectClass = com.gensym.classes.Object.class;
  private static Class eventSourceClass = EventSourceClass.class;

  /**
   * Initialize all Local RPC's used by this subclass, this method is called only once
   * just before the first connection. 
   */
  public void initializeLocalRPCs(G2Connection con)
  {

    // we can only declare the following RPC once

    // Declare which Java methods and thier equivalent G2 RPC NAME,
    // in this class that can be called by the G2 connection


    con.registerJavaMethod(this, 
			    "setWindowTime", 
			    Symbol.intern("JAVA-SET-WINDOW-TIME"));
    con.registerJavaMethod(this, 
			    "setWindowMessage", 
			    Symbol.intern("JAVA-SET-WINDOW-MESSAGE"));

    // Example of declaring a Java method that, if called by G2,
    // will be executed in a new thread...As we may send a large array 
    // and print it out which could delay other calls from this G2 connection.
    // N.B. Normally any requests to call Java Methods from G2
    // are placed on an execution queue (one per G2Connection)
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
    con.registerJavaMethod(this, "receiveSend_float", 
			    Symbol.intern("JAVA-RECEIVE-SEND-FLOAT-TYPE"));
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


    // Here we are declaring that two different G2 procedures will call
    // the same method name. The actual version of callJavaTestVararg depends
    // on the number of arguments sent down
    con.registerJavaMethod(this, "callJavaTestVararg", 
			    Symbol.intern("CALL-JAVA-TEST-VARARG"));
    con.registerJavaMethod(this, "callJavaTestVararg", 
			    Symbol.intern("CALL-JAVA-TEST-VARARG-WITH-HANDLE"));	

    // We can also prelook up methods and register those as accessible by a G2Connection

    try {
      java.lang.reflect.Method method = 
	this.getClass().getDeclaredMethod("javaTestMethodParams", 
					  new Class[] {String.class,
							 Boolean.TYPE,
							 Double.TYPE,
							 Integer.TYPE,
							 gensymObjectClass});
      con.registerJavaMethod(this,
			      method,
			      Symbol.intern("JAVA-TEST-METHOD-PARAMS"),
			      false);

      con.registerJavaMethod(this,
			      method, 
			      Symbol.intern("JAVA-TEST-METHOD-PARAMS-HANDLE"),
			      false);


      java.lang.reflect.Method method2 = 
	this.getClass().getDeclaredMethod("attachToG2EventSource", 
					  new Class[] {eventSourceClass});

      con.registerJavaMethod(this,
			      method2, 
			      Symbol.intern("JAVA-ATTACH-TO-G2-EVENT-SOURCE"),
			      false);
      

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
    System.out.println("G2 Has been paused");
  }

  /**
   * This method is called when the connected G2 has been resumed.
   */
  @Override
  public void g2IsResumed(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been resumed");
  }

 /**
   * This method is called when the connected G2 has been reset.
   */
  @Override
  public void g2IsReset(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been reset");
  }

  /**
   * This method is called when the connected G2 has been started.
   */
  @Override
  public void g2IsStarted(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been Started");
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

    try {
      System.out.println("Connected to G2 @" + 
		       g2Connection.g2GetHostName() + ":" + g2Connection.
		       g2GetPortNumberOrName());
    } catch (G2AccessException E) { System.out.println(E.toString()); }


    _unicodeDisplay.setMessage("G2InitializeConnection called with rpis = '"+ remote_process_string + "'");

    // Send a "hi" message to G2's message board
    g2Connection.returnMessage("Connected to ExampleG2Gateway (rpis = " + remote_process_string + ")\n Hi There from G2Gateway Java VM, how are you G2 ?");

    // Also Send an error message 
    g2Connection.reportLogBookErrorMessage
      (Symbol.intern("ERROR"), 
       "Dont worry this message is just a test Error message from Java class ExampleG2Gateway");


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
  @Override
  public void anEvent(G2_EventSourceEvent arg1) throws G2AccessException
  {
    System.out.println("Received an event from " + arg1.getSource() + "..." + arg1.getMessage());
  }
  
  // *****************************************************************



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
    SecureRandom randomGen = new SecureRandom();

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

	// Let other threads have a look in
	Thread.currentThread().yield();
	// Have we been told to stop
	if (_threadTable.get(Thread.currentThread().hashCode()) == null)
	  break;
      }
    } catch (G2AccessException E) {
       System.out.println(E.toString());
    }

    System.out.println("Thread " + threadName + " ending");

    // Remove thread from thread table
    _threadTable.remove(Thread.currentThread().hashCode());	 
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
    Object args[] = new Object[] {intParam, 
				    strParam, 
				    symParam, 
				    dblParam, 
				    booleanParam, 
				    itemParam};

    Object retval = g2Connection.callRPC(_javaCallG2ProcNameSymbol, args, 0);
    return ((Integer)retval).intValue();
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
  public void attachToG2EventSource(EventSourceClass eventSource) throws G2AccessException
  {
    eventSource.addG2_EventSourceListener(this);
    System.out.println("Added " + this.toString() + " as listener to Event-Source-Class events");
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
    System.out.println("MT" + item1 + " " + Runtime.getRuntime().freeMemory());

    Object args[] = { item1 };
    g2Connection.startRPC(Symbol.intern("SIMPLE_CALLBACK"), args );
  }


  /**
   * Method to test Variable argument calling - one argument
   */
  public void callJavaTestVararg(ATestClass item, String item1 ) 
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
  public void callJavaTestVararg(ATestClass item, String item1, Sequence item2)
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


  /**
   * Start a Thread of execution that loops calling G2 loopCount times
   * as well as passing a ATestClass for the thread to use 
   */
  public int startLoopThread(int loopCount, ATestClass itm) throws G2AccessException
  {
    _threadObject = itm;
    _threadLoopCount = loopCount;
    Thread newThread = new Thread(this);
    _threadTable.put(newThread.hashCode(), newThread);
    newThread.start();
    return newThread.hashCode();
  }

  public void stopLoopThread(int thread_index) throws Exception
  {
    try {
      _threadTable.remove(thread_index);
      System.out.println("Stopping thread for index " + thread_index);
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
   * Set the Time message on the UnicodeWindow
   */
  public void setWindowTime(double time)
  {

    _unicodeDisplay.setTime((long)time);
  }

  /**
   * Set the Message on the UnicodeWindow
   */
  public void setWindowMessage(String message)
  {
    _unicodeDisplay.setMessage(message);
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
    if (_enableOutput){
    	System.out.println("Generic Object Received Class " + obj.getClass() + "\nData " + obj.toString());
    }
    return obj;
  }

  public Object receiveSend(Sequence seq)
  {
    if (_enableOutput) {
    	System.out.println("Received Sequence " + seq.toString());
    }
    return seq;
  }

  
  public Object receiveSend(Structure struct) throws Exception
  {
    if (_enableOutput) {
    	System.out.println("Received Structure " + struct.toString());
    }
    return struct;
  }

  public Object receiveSend(com.gensym.classes.G2Array obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received G2Array " + obj.toString());
    }
    receiveSend((Object[])obj.getG2ArrayContents());
    obj.setG2ArrayContents(obj.getG2ArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.ItemArray obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received ItemArray " + obj.toString());
    }
    receiveSend((Object[])obj.getG2ArrayContents());
    obj.setG2ArrayContents(obj.getG2ArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    com.gensym.classes.ItemArray ia2 = null;
    try {
      // This is a example of creating a new ItemArray and filling its array locally
      // with the contents we have just received from G2
      ia2 = (com.gensym.classes.ItemArray)
	G2StubResolver.createStubForG2Interface(com.gensym.classes.ItemArray.class);
      ia2.setG2ArrayContents(obj.getG2ArrayContents());
    } catch (G2StubCreationException e) {}
    // Send our new array back to G2
    return ia2;
  }
  
  public Object receiveSend(com.gensym.classes.ValueArray obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received ValueArray " + obj.toString());
    }
    receiveSend((Object[])obj.getG2ArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    return obj;
  }
  
  public Object receiveSend(com.gensym.classes.FloatArray obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received FloatArray " + obj.toString());
    }
    receiveSend(obj.getFloatArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    return obj;
  }
  
  public Object receiveSend(com.gensym.classes.TextArray obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received TextArray " + obj.toString());
    }
    receiveSend(obj.getTextArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.SymbolArray obj) throws G2AccessException
  {
    if (_enableOutput){
    	System.out.println("Received SymbolArray " + obj.toString());
    }
    receiveSend(obj.getSymbolArrayContents());
    obj.setG2ArrayContents(obj.getSymbolArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.TruthValueArray obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received TruthValueArray " + obj.toString());
    }
    receiveSend(obj.getTruthValueArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    return obj;
  }

  
  public Object receiveSend(com.gensym.classes.QuantityArray obj) throws G2AccessException 
  {
    if (_enableOutput) {
    	System.out.println("Received QuantityArray " + obj.toString());
    }
    receiveSend((Number[])obj.getG2ArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    return obj;
  }

  public Object receiveSend(com.gensym.classes.IntegerArray obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received IntegerArray " + obj.toString());
    }
    receiveSend(obj.getIntegerArrayContents());
    obj.setG2ArrayContents(obj.getIntegerArrayContents());
    System.out.println("Size is " + obj.getArrayLength());
    com.gensym.classes.IntegerArray ia2 = null;
    try {
      // This is a example of creating a new IntegerArray and filling its array locally
      // with the contents of the array we have just received from G2
      ia2 = (com.gensym.classes.IntegerArray)
	G2StubResolver.createStubForG2Interface(com.gensym.classes.IntegerArray.class);
      ia2.setG2ArrayContents(obj.getIntegerArrayContents());
    } catch (G2StubCreationException e) {}
    // Return the new array back to G2
    return ia2;
  }

  /**
   * This method creates a new G2 List class and fills its contents locally from contents
   */
  Object createNewList(Class listClass, Sequence contents) throws G2AccessException {
    com.gensym.classes.G2List list = null;
    try {
      list = (com.gensym.classes.G2List)
	G2StubResolver.createStubForG2Interface(listClass);
      list.setG2ListSequence(contents);
    } catch (G2StubCreationException e) {}
    return list;
  }

  public Object receiveSend(com.gensym.classes.IntegerList obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received IntegerList " + obj.toString());
    }
    receiveSend(obj.getG2ListSequence());
    // For fun, create a new list copy the list contents from G2, and send it back to G2 !
    return createNewList(com.gensym.classes.IntegerList.class, obj.getG2ListSequence());
  }

  public Object receiveSend(com.gensym.classes.FloatList obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received FloatList " + obj.toString());
    }
     // For fun, create a new list copy the list contents from G2, and send it back to G2 !
    return createNewList(com.gensym.classes.FloatList.class, obj.getG2ListSequence());
  }

  public Object receiveSend(com.gensym.classes.TruthValueList obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received TruthValueList " + obj.toString());
    }
    return obj;
  }

  public Object receiveSend(com.gensym.classes.SymbolList obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received SymbolList " + obj.toString());
    }
    return obj;
  }

  public Object receiveSend(com.gensym.classes.TextList obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received TextList " + obj.toString());
    }
    return obj;
  }
 
  public Object receiveSend(com.gensym.classes.ItemList obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received ItemList " + obj.toString());
    }
    return obj;
  }

  public Object receiveSend(com.gensym.classes.QuantityList obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received QuantityList " + obj.toString());
    }
    return obj;
  }


  public Object receiveSend(com.gensym.classes.ValueList obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received ValueList " + obj.toString());
    }
    return obj;
  }

  public Object receiveSend(com.gensym.classes.G2List obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received G2List " + obj.toString());
    }
    return obj;
  }

  public Object receiveSend(Symbol obj) throws G2AccessException
  {
    if (_enableOutput) {
    	System.out.println("Received Symbol " + obj.toString());
    }

    return obj;
  }

  public Object receiveSend(String obj)
  {
    if (_enableOutput) {
    	System.out.println("Received String " + obj.toString());
    }
    return obj;
  }

  public int receiveSend_int(int integer)
  {
    if (_enableOutput) {
    	System.out.println("Received Integer " + integer);
    }
    return integer;
  }
  
  public boolean receiveSend_bool(boolean bool)
  {
    if (_enableOutput) {
    	System.out.println("Received boolean"  + bool);
    }
    return bool;
  }
  
  public double receiveSend_float(double flt)
  {
    if (_enableOutput) {
    	System.out.println("Received double " + flt);
    }
    return flt;
  }

  public double receiveSend_float(float flt)
  {
    if (_enableOutput) {
    	System.out.println("Received float " + flt);
    }
    return flt;
  }

  public byte receiveSend_byte(byte byt)
  {
    if (_enableOutput) {
    	System.out.println("Receive byte " + byt);
    }
    return byt;
  }

  public short receiveSend_short(short sht)
  {
    if (_enableOutput) {
    	System.out.println("Received short " + sht);
    }
    return sht;
  }

  public long receiveSend_long(long lng)
  {
    if (_enableOutput) {
    	System.out.println("Received long " + lng);
    }
    return lng;
  }
        
  public char receiveSend_char(char ch)
  {
    if (_enableOutput) {
    	System.out.println("Received char " + ch);
    }
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
	  if (_enableOutput) {
		  System.out.println("Element["+i+"] = "+ array[i]);
	  }
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


  // *****************************************************************

  /**
   * Main method
   */
  public static void main(String args[])
  {
    // If a Java class wishes to listen for unsolicited connections from a G2 Server
    // Then it must follow the following steps
    
    // 1. Initialize the G2 Gateway Class
    com.gensym.core.GensymApplication.initialize (args);
    G2Gateway.initialize(new String[] {"-listenerport", "22044"});

    try {
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
	  ExampleG2Gateway egw = new ExampleG2Gateway(new_gateway);
	  return new_gateway;
	} });
    } catch (Error e) { System.out.println("Caught error"); }

    // 3. Startup the G2 gateway interface, allowing network connections and communication
    //    This is done after the connection handle factory is setup, just is case a
    //    G2 has already initiated an unsolicited connection
    G2Gateway.startup();

    System.out.println("ExampleG2Gateway...started...waiting...");

    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);

    String host = cmdline.getOptionValue("-g2host");
    String port = cmdline.getOptionValue("-g2port");
    String tsname = cmdline.getOptionValue("-tsName");
    boolean result = false;

    if (port != null || host != null)
      {
	//try to connect to a g2 if we are asked
	try {
	  
	  G2Connection g2_connection =
	   G2Gateway.getOrMakeConnection(tsname,
					 (host == null ? "localhost" : host),
	  			  (port == null ? "1111" : port));

	  ExampleG2Gateway egw = new ExampleG2Gateway(g2_connection);
	  g2_connection.returnMessage("Connected to ExampleG2Gateway \n Hi There from G2Gateway Java VM, how are you G2 ?");
	  System.out.println("Connected to G2 OK");			
	
	} catch (Exception E) { System.out.println(E.toString()); }
	//} catch (ConnectionTimedOutException E) { System.out.println(E.toString()); }


      }
  }
}

/*********************************************************************************/
// Class to display Unicode output via AWT window
class UnicodeDisplay {
    
  TextArea textbox = new TextArea("");
  Panel panel = new Panel();
  Label label = new Label("--------- Unicode Output for use with JgiDemo.kb -------------------");
  Font small_font = new Font("TimesRoman", Font.PLAIN,12);
   
  public UnicodeDisplay() 
  {      
    Frame frame = new Frame();
    frame.setLayout(new FlowLayout());
    frame.setSize(400,300);
    frame.add(label);
    frame.add(panel);
    panel.add(textbox);
    textbox.setForeground(Color.black);
    textbox.setBackground(Color.gray);
    textbox.setEditable(true);
    textbox.setFont(small_font);       
    frame.setTitle("ExampleG2Gateway");
    frame.show();
  }
  
    
  public void setMessage(String message){
    textbox.setText(message);
    label.setText(message);
  }
  
  public void setTime(long g2_time) {
    Date date = new Date(g2_time*1000);
      
    label.setText("G2 time is "+ g2_time + " " + date);
  }
     
}	
	
