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
package com.gensym.tests;

import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.QuantitativeVariable;

/**
 * G2 Skeleton Gateway/Java Class to be used with jgi-java-test1.kb.
 * This class demonstrates a minimal G2Gateway as a means to communicate
 * with a G2 server.
 *@version 1.0
 */
public class SkeletonG2Gateway implements G2ConnectionListener
{

  // Its good practice to pre lookup Symbols that will be used often
  private static Symbol _javaCallG2ProcNameSymbol = Symbol.intern("JAVA-CALL");

  // This will hold our connection to G2
  private G2Connection g2Connection = null;

  /**
   * Constructor
   */
  public SkeletonG2Gateway(G2Connection connection)
  {
    this.g2Connection = connection;
    registerJavaMethods(connection);
    // We would like to listen to any Connection events (G2 Pause, Resume, etc...)
    connection.addG2ConnectionListener(this);
  }

  /**
   * Register any Java Methods that G2 can call as Remote Procedures.
   */
  private void registerJavaMethods(G2Connection con)
  {

    // Declare which Java methods of this class are associated with equivalent G2 RPC NAMEs,
    // that can be called by a G2 server over a G2Connection.
  
    con.registerJavaMethod(this, 
			   "receiveSend",  // java method to call
			   Symbol.intern("JAVA-RECEIVE-SEND")); // when refered to by this G2 RPC name
		
  }

  // G2ConnectionListener implementations
  /**
   * This Method is called when the G2 connected has been paused .
   */
  @Override
  public void g2IsPaused(G2ConnectionEvent e)
  {
    System.out.println("G2 Has been paused");
  }

  /**
   * This method is called when the G2 connected has been resumed.
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
   * Must call super() here.
   */
  @Override
  public void g2ConnectionClosed(G2ConnectionEvent e)
  {
    System.out.println("G2 Connection has been closed ");
  }
    

  /**
   * A connection has been established between a connection and a G2 GSI-INTERFACE.
   */
  @Override
  public void g2ConnectionInitialized(G2ConnectionEvent e)
  {

    String remote_process_string = e.getMessage();
		
    // Send a "hi" message to G2's message board
    g2Connection.returnMessage("You have Connected to SkeletonG2Gateway (rpis = " + remote_process_string + ")\n Hi There from G2Gateway Java VM, how are you G2 ?");

    // Call some RPC's in the connected G2.
    callG2RPC();

  }


  /**
   * Method to call into Java and call a G2 procedure.
   */
  public Object callG2RPC()
  {

    Object ret_obj;
    
    // G2 proc arguments must be objects
    Object args[] = new Object[6];
    args[0] = new Integer(111);
    args[2] = Symbol.intern("SYMBOL"); 
    args[3] = new Double(1.238293823);
    args[4] = new Boolean(false);

    // we will send back a new QUANTITATIVE-VARIABLE for the fifth parameter
    QuantitativeVariable quantVar = null;
    try {
      quantVar = (QuantitativeVariable)
	G2StubResolver.createStubForG2Interface(QuantitativeVariable.class);
    } catch (Exception e) {
      System.out.println(e.toString());
      System.exit(0);
    }
    args[5] = quantVar;

    // call the G2 Proc JAVA-CALL with the above parameters
    try {
	    
      System.out.println("Starting a G2 Proc..");
      args[1] = new String("From a startRPC");
      g2Connection.startRPC(_javaCallG2ProcNameSymbol, args);  

      System.out.println("Callng a G2 Proc Synchronously..");
      args[1] = new String("From a synchronous CallRPC");
      ret_obj = g2Connection.callRPC(_javaCallG2ProcNameSymbol, args, 5000);  // 5s timeout

      return ret_obj;
	  
    }
    catch (G2AccessException E)
      {
	System.out.println(E.toString());
      }

    return null;
  }




  /**
   * Method that has been declared to be callable by G2 (via registerJavaMethod).
   */
  public Object receiveSend(Object obj)
  {
   System.out.println("Received Class " + obj.getClass() + "\nData " + obj.toString());
   return obj;
  }


  public static void main(String args[])
  {

    // If a Java class wishes to listen for unsolicited connections from a G2 Server
    // Then it must follow the following steps

    // 1. Initialize the G2 Gateway Class
    try {
      G2Gateway.initialize(args);
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
	  SkeletonG2Gateway egw = new SkeletonG2Gateway(new_gateway);
	  return new_gateway;
	} });

    // 3. Startup the G2 gateway interface, allowing network connections and communication
    //    This is done after the connection handle factory is setup, just is case a
    //    G2 has already initiated an unsolicited connection
    G2Gateway.startup();


    // A connection to a G2 server can also be initiated from Java
    // Here an attempt to connect to a G2 server if a port ('-g2port <port>')
    // and/or host name ('-g2host <host>') is specified on the commandline
    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);

    String host = cmdline.getOptionValue("-g2host");
    String port = cmdline.getOptionValue("-g2port");
    boolean result = false;

    if (port != null || host != null)
      {
	//try to connect to a G2 if we are asked
	try {
 
	  G2Connection g2_connection = 
	    G2Gateway.getOrMakeConnection((host == null ? "localhost" : host),
					  (port == null ? "1111" : port));

	  SkeletonG2Gateway egw = new SkeletonG2Gateway(g2_connection);
	  g2_connection.returnMessage("Connected to SkeletonG2Gateway \n Hi There from G2Gateway Java VM, how are you G2 ?");
	  System.out.println("Connected to G2 OK");			
	
	} catch (Exception E) { System.out.println(E.toString()); }


      }

  }


}
	
