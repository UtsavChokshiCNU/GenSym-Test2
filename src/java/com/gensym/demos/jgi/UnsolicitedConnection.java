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
import com.gensym.util.*;

/**
 * This Class demonstrates how G2 can initiate an unsolicited connection to a Java VM
 * running JavaLink.
 * A G2ConnectionHandlerFactory is registered to create a G2Connection to handle
 * incomming network connections from G2 to Java.
 * To use:
 * 1. make sure jgidemo.kb is loaded and started, 
 * 2. run this class: java com.gensym.demos.jgi.UnsolicitedConnection
 * 3. Press the connect button in G2
 * 4. Should see a Message appear on the G2 message board
 *
 *@version 1.0
 */
public class UnsolicitedConnection implements G2ConnectionListener
{

  // This will hold our connection to G2
  private G2Connection g2Connection = null;

  /**
   * Constructor
   */
  public UnsolicitedConnection(G2Connection connection) {
    this.g2Connection = connection;
    g2Connection.addG2ConnectionListener(this);
  }

  // G2ConnectionListener implementation
    
  /**
   * A connection has been established between the connection we are listening too
   * and a G2 GSI-INTERFACE. 
   */
  @Override
  public void g2ConnectionInitialized(G2ConnectionEvent e)
  {

    String remote_process_string = e.getMessage();
		
    // Send a "hi" message to G2's message board
    g2Connection.returnMessage("You have Connected to UnsolicitedConnection (rpis = " + remote_process_string + ")\n Hi There from Java VM, how are you G2 ?");

  }

  // We are only interested in g2ConnectionInitialized

  @Override
  public void g2IsPaused(G2ConnectionEvent e) {}
  @Override
  public void g2IsResumed(G2ConnectionEvent e) {}
  @Override
  public void g2IsReset(G2ConnectionEvent e) {}
  @Override
  public void g2IsStarted(G2ConnectionEvent e) {}
  @Override
  public void g2MessageReceived(G2ConnectionEvent e) {}
  @Override
  public void communicationError(G2CommunicationErrorEvent error_event) {}
  @Override
  public void readBlockage(G2ConnectionEvent event) {}
  @Override
  public void writeBlockage(G2ConnectionEvent event) {}
  @Override
  public void g2ConnectionClosed(G2ConnectionEvent e) {}


  public static void main(String args[])
  {

    // If a Java class wishes to listen for unsolicited connections from a G2 Server
    // Then it must follow the following steps

    // 1. Initialize the G2 Gateway Class
    // jgidemo connects to 22044 port
    G2Gateway.initialize(new String[] {"-listenerport", "22044"});
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
	  UnsolicitedConnection egw = new UnsolicitedConnection(new_gateway);
	  return new_gateway;
	} });

    // 3. Startup the G2 gateway interface, allowing network connections and communication
    //    This is done after the connection handle factory is setup, just is case a
    //    G2 has already initiated an unsolicited connection
    G2Gateway.startup();

  }


}
	
