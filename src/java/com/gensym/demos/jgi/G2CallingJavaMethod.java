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
 * This class demonstrates how a Java Method can be registered such that it can 
 * be called by G2 over a G2Connection. This example waits for G2 to initiate 
 * a network connection with the Java VM. Once connected G2 can call the 
 * method receiveSend.
 * To use:
 * <p>1. make sure jgidemo.kb is loaded and started,
 * <p>2. run this class: java com.gensym.demos.jgi.G2CallingJavaMethod
 * <p>3. Press the connect button in G2
 * <p>4. Go to the SENDING-RECEIVING-DATA workspace
 * <p>5. Send data from G2 by pressing Send buttons
 *
 *@version 1.0
 */
public class G2CallingJavaMethod
{


  // This will hold our connection to G2
  private G2Connection g2Connection = null;

  /**
   * Constructor
   */
  public G2CallingJavaMethod(G2Connection connection) {
    this.g2Connection = connection;
    registerJavaMethods(connection);
    System.out.println("Connected OK...");
  }

  /**
   * Register any Java Methods that G2 can call as Remote Procedures.
   */
  private void registerJavaMethods(G2Connection con) {

    // Declare which Java methods of this class are associated with equivalent G2 RPC NAMEs,
    // that can be called by a G2 server over a G2Connection.
  
    // JAVA-RECEIVE-SEND is associated with G2CallingJavaMethod.receiveSend
    con.registerJavaMethod(this, 
			   "receiveSend",  // java method to call
			   Symbol.intern("JAVA-RECEIVE-SEND")); // when refered to by this G2 RPC name
		
  }


  /**
   * Method that has been declared to be callable by G2 (via registerJavaMethod).
   */
  public Object receiveSend(Object obj) {
   System.out.println("Received Class " + obj.getClass() + "\nData " + obj.toString());
   return obj;
  }


  public static void main(String args[]) {

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
	  G2CallingJavaMethod egw = new G2CallingJavaMethod(new_gateway);
	  return new_gateway;
	} });

    // 3. Startup the G2 gateway interface, allowing network connections and communication
    //    This is done after the connection handle factory is setup, just is case a
    //    G2 has already initiated an unsolicited connection
    G2Gateway.startup();

  }


}
	
