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

/**
 * This Class simply demonstrates how com.gensym.jgi.G2Gateway can be used to 
 * connect to a G2 server and send a message to its message board.
 *
 *@version 1.0
 */
public class SendG2Message {

  public static void main(String args[])
  {

    // A connection to a G2 server can be initiated from Java using G2Gateway.getOrMakeConnection
    // Here an attempt to connect to a G2 server if a port ('-g2port <port>')
    // and/or host name ('-g2host <host>') is specified on the commandline
    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);

    String host = cmdline.getOptionValue("-g2host");
    String port = cmdline.getOptionValue("-g2port");
    G2Connection g2_connection = null;

    if (port != null || host != null)
      {
	try { 
	  // Attempt to connect to G2, and wait until successful or timeout
	  g2_connection = 
	    G2Gateway.getOrMakeConnection((host == null ? "localhost" : host),
					  (port == null ? "1111" : port));
	} catch (Exception e) {
	  System.out.println("Could not connect to G2, error was " + e.toString());
	  System.exit(0);
	}

	System.out.print("Connected to G2 OK...\n");	

	// We have connected OK, send a message to the G2's message board
        String msg = "Connected to JavaLink.\nHi there from Java VM.\nHow are you, G2?";
        send1(g2_connection, msg);
      } else
	System.out.println("Usage: -g2host <g2hostname> [-g2port <g2portName>]");
      

    try {
      Thread.sleep(2000);  // give other threads two seconds to finish processing
    } catch (Exception e) {
      System.out.println (e);
    }

    System.exit(0);
  }

  public static void send1(G2Connection g2_connection, String msg)
  {
    System.out.println("Message:\n");
    System.out.println(msg);
    System.out.println("\n");

    g2_connection.returnMessage(msg);

    System.out.println("Sent Message Successfully...");
    System.out.println("Finished.");
  }
}
