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
package com.gensym.jgope.deploy;

import java.util.Hashtable;
import java.util.Random;
import java.util.Date;
import java.awt.*;
import com.gensym.jgi.*;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.util.*;
import com.gensym.jgi.download.G2StubResolver;
import com.gensym.jgi.download.G2StubCreationException;
import com.gensym.message.*;
import com.gensym.classes.Item;
import com.gensym.classes.modules.jgidemo.*;
import com.gensym.classes.FloatArray;
import com.gensym.classes.modules.gope.*;

/**
 *
 */
public class JGopeG2Gateway implements Runnable, G2ConnectionListener, G2_EventSourceListener
{
  private boolean _enableOutput = true;
  private Hashtable _threadTable = new Hashtable();
  private G2Connection g2Connection = null;
  private Hashtable _managerTable = new Hashtable();


  /**
   * Constructor
   */
  public JGopeG2Gateway(G2Connection connection)
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
			    "calculateOptimization", 
			    Symbol.intern("_GOPE_CALCULATE_OPTIMIZATION"));

  }

  public double[] getOptimizationResults(){

	  OnlineManager onlineManager =  (OnlineManager)_managerTable.get(new Integer(Thread.currentThread().hashCode()));
	  if(onlineManager.isCalculated()){
		  double[] resultx = onlineManager.getResultX();
		  double[] results = new double[resultx.length+2];
		  results[0] = onlineManager.getObjective();
		  results[1] = onlineManager.getStatus();
		  for(int  i=0;i<resultx.length;i++){
			  results[i+2] = resultx[i];
		  }
		  return results;

	  }else {
		  return new double[0];

	  }
  }

  public int calculateOptimization(GopeNlpOptimizationObject optObj) throws G2AccessException
  {
    Thread newThread = new Thread(this);
	Integer key = new Integer(newThread.hashCode());
    _threadTable.put(key, optObj);

	OnlineManager onlineManager = new OnlineManager("g2OnlineManager");
	onlineManager.setG2Gateway(this);
    _managerTable.put(key, onlineManager);

    newThread.start();
    return newThread.hashCode();
  }



  // *****************************************************************
  // G2ConnectionListener implementations

  /**
   * This Method is called when the connected G2 has been paused .
   */
  public void g2IsPaused(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been paused");
  }

  /**
   * This method is called when the connected G2 has been resumed.
   */
  public void g2IsResumed(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been resumed");
  }

 /**
   * This method is called when the connected G2 has been reset.
   */
  public void g2IsReset(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been reset");
  }

  /**
   * This method is called when the connected G2 has been started.
   */
  public void g2IsStarted(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been Started");
  }

  /**
   * Called when G2 sends a message to the G2Connection.
   */
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
  public void communicationError(G2CommunicationErrorEvent error_event)
  {
    System.out.println(error_event.getMessage());
  }

  /**
   * Called when the network cannot deliver data that Java is attempting to write to G2.
   */
  public void readBlockage(G2ConnectionEvent event) {}

  /**
   * Called when the network cannot deliver data that G2 is attempting to write to Java.
   */
  public void writeBlockage(G2ConnectionEvent event) {}

  /** 
   * This method is called when the G2 connection has been shutdown.
   */
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
  public void g2ConnectionInitialized(G2ConnectionEvent e)
  {    

    String remote_process_string = e.getMessage();

    try {
      System.out.println("Connected to G2 @" + 
		       g2Connection.g2GetHostName() + ":" + g2Connection.
		       g2GetPortNumberOrName());
    } catch (G2AccessException E) { System.out.println(E.toString()); }


//    _unicodeDisplay.setMessage("G2InitializeConnection called with rpis = '"+ remote_process_string + "'");

    // Send a "hi" message to G2's message board
    g2Connection.returnMessage("Connected to JGopeG2Gateway (rpis = " + remote_process_string + ")\n Hi There from G2Gateway Java VM, how are you G2 ?");

    // Also Send an error message 
    g2Connection.reportLogBookErrorMessage
      (Symbol.intern("ERROR"), 
       "Dont worry this message is just a test Error message from Java class JGopeG2Gateway");
  }

  // *****************************************************************
  

  // *****************************************************************
  // To Implement G2_EventSourceListener exported from G2-EVENT-SOURCE-CLASS

  /**
   * To Implement G2_EventSourceListener exported from G2 Event 
   * Generator class G2EventSourceClass.
   */
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
  public void run()
  {
	try{
		GopeNlpOptimizationObject optObj = (GopeNlpOptimizationObject)_threadTable.get(new Integer(Thread.currentThread().hashCode()));
		OnlineManager onlineManager =  (OnlineManager)_managerTable.get(new Integer(Thread.currentThread().hashCode()));

//System.out.println("run isByHandle()="+((GopeOptimizationObjectImpl)optObj).isByHandle());

		double[] x = optObj.getXinits().getFloatArrayContents();
		double[] exog = optObj.getExtrparam().getFloatArrayContents();
		double[] ub = optObj.getXubs().getFloatArrayContents();
		double[] lb = optObj.getXlbs().getFloatArrayContents();
		int nc = optObj.getNumberOfConstraints();

		String sense = optObj.getSenseOfConstraints();

//System.out.println("initx 1 = "+ x[0]);
		String dllName = "OptProb";
		onlineManager.setDLLName(dllName);
		onlineManager.setInitX(x);
		onlineManager.setIndependentUpperBounds(ub);
		onlineManager.setIndependentLowerBounds(lb);
		onlineManager.setMinimize(optObj.getIsMinimizationProblem());
		if(exog.length > 0 )
			onlineManager.setExtraParameters(exog);
		if(nc>0){
			onlineManager.setRhsForConstraints(optObj.getRhv().getFloatArrayContents());
			onlineManager.setNumberOfConstraints(nc);
			onlineManager.setSenseForConstraints(optObj.getSenseOfConstraints());
		}
		onlineManager.run();
System.out.println("obj="+onlineManager.getObjective());
System.out.println("status="+onlineManager.getStatus());

		double[] xresult = onlineManager.getResultX();
		optObj.setY(onlineManager.getObjective());
		optObj.setFinalStatus(onlineManager.getStatus());
		FloatArray xf = optObj.getX();
		xf.setG2ArrayContents(xresult);
		optObj.gopeReturnResults(xf);

// Remove thread from thread table
		_threadTable.remove(new Integer(Thread.currentThread().hashCode()));	 
		_managerTable.remove(new Integer(Thread.currentThread().hashCode()));	 
	} catch (G2AccessException E) {
	   System.out.println(E.toString());
	}
  }


  public double g2ObjFunction(double[] x){
	  try{
		GopeNlpOptimizationObject optObj = (GopeNlpOptimizationObject)_threadTable.get(new Integer(Thread.currentThread().hashCode()));
		FloatArray ax = optObj.getXinits();
		ax.setG2ArrayContents(x);
		return optObj.gopeObjectiveFunction(ax);
	} catch (G2AccessException E) {
	   System.out.println(E.toString());
	}
	return 0.0;
  }
		
  public double g2ConstraintFunction(double[] x, int index){

	try{
		GopeNlpOptimizationObject optObj = (GopeNlpOptimizationObject)_threadTable.get(new Integer(Thread.currentThread().hashCode()));
		FloatArray ax = optObj.getXinits();
		ax.setG2ArrayContents(x);
		return optObj.gopeConstraintFunction(ax, index);
	} catch (G2AccessException E) {
	   System.out.println(E.toString());
	}
	return 0.0;
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

    Object args[] = { new Integer(item1) };
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

	  System.out.println("Time ="+time);
//    _unicodeDisplay.setTime((long)time);
  }

  /**
   * Set the Message on the UnicodeWindow
   */
  public void setWindowMessage(String message)
  {
	  System.out.println("message ="+message);
//    _unicodeDisplay.setMessage(message);
  }


  /*
   * Gets the version of JavaLink.
   * (Look at the core.jar->products.dat for the names of the products)
   * If the product cannot be found, an exception of class UnknownProductException is thrown, but that is a private class.
   */
  public static String getJavaLinkVersion(){
    String productName = "javalink";
    String version = "none";
    try{
      com.gensym.core.Product product = com.gensym.core.ProductManager.getProduct(productName);
      if (product != null){
        version = product.getDisplayVersion();
      }
    }
    catch (Exception ex) {
      version = "the product named '"+ productName + "' is unknown";
    }
    return version;
  }


  // *****************************************************************

  /**
   * Main method
   */
  public static void main(String args[])
  {
    System.out.println();
	  System.out.println("+--------------------------------------------------+");
	  System.out.println("|                                                  |");
	  System.out.println("|    G2 Optimization Engine Bridge                 |");
	  System.out.println("|    " + G2Version.VERSION_INFORMATION + " (Build " + G2Version.BUILD_INFORMATION + ")" + "                |");
	  System.out.println("|                                                  |");
	  System.out.println("|    " + G2Version.COPYRIGHT_INFORMATION + "        |");
	  System.out.println("|                                                  |");
	  System.out.println("+--------------------------------------------------+");
	  System.out.println("");
	  System.out.println("JavaLink version: " + JGopeG2Gateway.getJavaLinkVersion());
	  System.out.println("");

    // If a Java class wishes to listen for unsolicited connections from a G2 Server
    // Then it must follow the following steps
    
    // 1. Initialize the G2 Gateway Class
    com.gensym.core.GensymApplication.initialize (args);
    try {
      G2Gateway.initialize(new String[] {"-listenerport", "22044"});
    }
    catch (AlreadyInitializedException E) { System.out.println(E.toString());};

    try {
    // 2. Set up a connection factory deal with unsolicited G2 connections
    G2Gateway.setConnectionHandlerFactory(new G2ConnectionHandlerFactory() {
      /**
       * To support G2ConnectionHandlerFactory, called when an unsolicated connection
       * is detected. It is the responsibility of this method to return a G2Connection 
       * that will handle the new connection.
       */
      public G2Connection createG2Connection(String connection_data)
	{  
	  G2Gateway new_gateway = new G2Gateway();
	  JGopeG2Gateway egw = new JGopeG2Gateway(new_gateway);
	  return new_gateway;
	} });
    } catch (Error e) { System.out.println("Caught error"); }

    // 3. Startup the G2 gateway interface, allowing network connections and communication
    //    This is done after the connection handle factory is setup, just is case a
    //    G2 has already initiated an unsolicited connection
    G2Gateway.startup();

    System.out.println("JGopeG2Gateway...started...waiting...");

    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);

    String host = cmdline.getOptionValue("-g2host");
    String port = cmdline.getOptionValue("-g2port");
    String gsiname = cmdline.getOptionValue("-gsiname");
    boolean result = false;

    if (port != null || host != null)
      {
	//try to connect to a g2 if we are asked
	try {
	  
		G2Connection g2_connection =
			G2Gateway.getOrMakeConnection((host == null ? "localhost" : host),
	  			  (port == null ? "1111" : port));

	  JGopeG2Gateway egw = new JGopeG2Gateway(g2_connection);
	  g2_connection.returnMessage("Connected to JGopeG2Gateway \n Hi There from G2Gateway Java VM, how are you G2 ?");
	  System.out.println("Connected to G2 OK");			
	
	} catch (Exception E) { System.out.println(E.toString()); }
	//} catch (ConnectionTimedOutException E) { System.out.println(E.toString()); }


      }
  }
}

