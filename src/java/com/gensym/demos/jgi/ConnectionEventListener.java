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

import com.gensym.jgi.*;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.util.*;
import com.gensym.message.*;

/**
 * This class demostrates how a class can listen for G2ConnectionListener events
 * that may occur for a particular G2Connection. A G2ConnectionListener is informed of;
 * <LI>The connected G2 has resumed.
 * <LI>The connected G2 has paused.
 * <LI>The connected G2 has been reset.
 * <LI>The connected G2 has been started.
 * <LI>The connected G2 has send a message (VIA INFORM THE...)
 * <LI>The connection to G2 has been closed.
 * <LI>A connection to G2 has just been established.
 * <LI>A communicationError has occured while the connection to a G2 is active.
 * <LI>The network cannot deliver data that Java is attempting to write to G2.
 * <LI>The network cannot deliver data that G2 is attempting to write to Java.
 *
 * <P>A G2ConnectionListener can register interest in these events by calling
 * <B>G2Gateway.addG2ConnectionListener</B> and can remove interest by calling 
 * <B>G2Gateway.removeG2ConnectionListener</B>.
 *
 *@version 1.0
 */
public class ConnectionEventListener implements G2ConnectionListener
{

  // This will hold our connection to G2
  private G2Connection g2Connection = null;

  /**
   * Constructor
   */
  public ConnectionEventListener(G2Connection connection) {
    this.g2Connection = connection;
    // We would like to listen to any Connection events (G2 Pause, Resume, etc...)
    connection.addG2ConnectionListener(this);
  }


  // G2ConnectionListener implementations
  /**
   * This Method is called when the G2 connected has been paused .
   */
  @Override
  public void g2IsPaused(G2ConnectionEvent e) {
    System.out.println("G2 Has been paused");
  }

  /**
   * This method is called when the G2 connected has been resumed.
   */
  @Override
  public void g2IsResumed(G2ConnectionEvent e) {
    System.out.println("G2 Has been resumed");
  }

  /**
   * This Method is called when the G2 connected has been reset .
   */
  @Override
  public void g2IsReset(G2ConnectionEvent e) {
    System.out.println("G2 Has been reset");
  }

  /**
   * This method is called when the G2 connected has been started.
   */
  @Override
  public void g2IsStarted(G2ConnectionEvent e) {
    System.out.println("G2 Has been started");
  }

  /**
   * Called when G2 sends a message to the G2Connection.
   */
  @Override
  public void g2MessageReceived(G2ConnectionEvent e) {
    System.out.println("Message received from G2 was: " + e.getMessage());
  }

  /**
   * Called when an asynchronous error has occured in the G2 communications interface
   * for the G2Connection
   *
   *@param error_event An G2CommunicationErrorEvent describing the error that occured.
   */
  @Override
  public void communicationError(G2CommunicationErrorEvent error_event) {
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
   */
  @Override
  public void g2ConnectionInitialized(G2ConnectionEvent e)
  {

    String remote_process_string = e.getMessage();
		
    // Send a "hi" message to G2's message board
    g2Connection.returnMessage("You have Connected to ConnectionEventListener (rpis = " + remote_process_string + ")\n Hi There from Java VM, how are you G2 ?");

  }

  public static void main(String args[]) {

    // A connection to a G2 server can be initiated from Java using G2Gateway.getOrMakeConnection
    // Here an attempt to connect to a G2 server if a port ('-g2port <port>')
    // and/or host name ('-g2host <host>') is specified on the commandline
    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);

    String host = cmdline.getOptionValue("-g2host");
    String port = cmdline.getOptionValue("-g2port");
    String tsName = cmdline.getOptionValue("-tsName");
    G2Connection g2_connection = null;

    if (port != null || host != null)
      {
	try { 
	  // Attempt to connect to G2, and wait until successful or timeout
	  g2_connection = 
	    G2Gateway.getOrMakeConnection((tsName == null ? null : tsName),
					  (host == null ? "localhost" : host),
					  (port == null ? "1111" : port));
	} catch (Exception e) {
	  System.out.println("Could not connect to G2, error was " + e.toString());
	  System.exit(0);
	}

	System.out.println("Connected to G2 OK...");	

	// We have connected OK, create a new CallG2Procedure 
	ConnectionEventListener listener = new ConnectionEventListener(g2_connection);

	// The main thread will terminate here, but the G2Connection thread is still alive
	// So we will receive G2ConnectionListener events

      } else {
	System.out.println("Usage: -g2host <g2hostname> [-g2port <g2portName>]");
	System.exit(0);
      }

  }



}
	
