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
package com.gensym.demos.jlp;

import java.util.Hashtable;
import java.util.Random;
import java.lang.Math.*;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.core.*;
import com.gensym.jgi.download.G2StubResolver;
import com.gensym.jgi.download.G2StubCreationException;
import com.gensym.message.*;
import com.gensym.classes.Item;

/**
 * JavaLink Professional Java Test Class to be used with jlpdemo.kb.
 * To use:
 * <p>1. make sure jlpdemo.kb is loaded and started,
 * <p>2. run this class: java com.gensym.demos.jlp.ExampleJLPGateway
 * <p>3. Press the connect button in G2
 * <P>4. Follow instructions in the G2 Kb
 *
 */
public class ExampleJLPGateway implements  G2ConnectionListener
{
  private boolean _enableOutput = true;
  private G2Connection g2Connection = null;

  /**
   * Constructor
   */
  public ExampleJLPGateway(G2Connection connection)
  {
    System.out.println("Getting connection...");
    this.g2Connection = connection;
    System.out.println("Init connection...");
    initializeLocalRPCs(connection);
    System.out.println("Enabling JLP");
    com.gensym.jlp.JLPSupport.enableJLP(connection);
    System.out.println("Done...");
  }

  /**
   * Initialize all Local RPC's used by this subclass, this method is called only once
   * just before the first connection.
   */
  public void initializeLocalRPCs(G2Connection con)
  {
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

    try {
      System.out.println("Connected to G2 @" +
		       g2Connection.g2GetHostName() + ":" + g2Connection.
		       g2GetPortNumberOrName());
    } catch (G2AccessException E) { System.out.println(E.toString()); }

    // Send a "hi" message to G2's message board
    g2Connection.returnMessage("Connected to ExampleJLPGateway (rpis = " + remote_process_string + ")\n Hi There from JavaLink Professional, how are you G2 ?");
  }

  // *****************************************************************




  /**
   * Turn the lots of output on/off
   */
  public void setOutput(boolean state)
  {
    _enableOutput = state;
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
    try {
      G2Gateway.initialize(new String[] {"-listenerport", "22044"});
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
	  ExampleJLPGateway egw = new ExampleJLPGateway(new_gateway);
	  return new_gateway;
	} });

    // 3. Startup the G2 gateway interface, allowing network connections and communication
    //    This is done after the connection handle factory is setup, just is case a
    //    G2 has already initiated an unsolicited connection
    G2Gateway.startup();

    System.out.println("ExampleJLPGateway...started...waiting...");

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

	  ExampleJLPGateway egw = new ExampleJLPGateway(g2_connection);
	  g2_connection.returnMessage("Connected to ExampleJLPGateway \n Hi There from G2Gateway Java VM, how are you G2 ?");
	  System.out.println("Connected to G2 OK");

	} catch (Exception E) { System.out.println(E.toString()); }
	//} catch (ConnectionTimedOutException E) { System.out.println(E.toString()); }


      }

  }



}

