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

import java.security.SecureRandom;
import com.gensym.jgi.*;  
import com.gensym.core.CmdLineArgHandler;
import com.gensym.util.Symbol;

/**
 * This Class simply demonstrates how multiple Java threads can communicate
 * with a G2 server.
 * This Java example should be connected to G2 KB JavaLink-Tutorial.kb
 *@version 1.0
 */
public class JavaThreadsCallingG2 implements Runnable {

  // This will hold our connection to G2
  private G2Connection g2Connection = null;

  /**
   * Constructor
   */
  public JavaThreadsCallingG2(G2Connection connection) {
    this.g2Connection = connection;
  }

  
  /**
   * This method will call the G2 procedure "A-G2-PROCEDURE" across g2Connection
   *@param i    The INTEGER parameter 
   *@param txt  The TEXT parameter (String converts to G2 TEXT)
   *@param dbl  The FLOAT paramter (double [and float] convert to G2 FLOAT)
   *@param sym  The SYMBOL parameter (com.gensym.util.Symbol converts to G2 SYMBOL)
   *@return     The current real time from G2, as a double
   *@exception G2AccessException, If an error occurs while calling the RPC
   */
  public double aG2Procedure(int i, String txt, double dbl, Symbol sym) throws G2AccessException {
    Double ret = (Double)g2Connection.callRPC(Symbol.intern("A-G2-PROCEDURE"), 
					      new Object[] {i, txt, dbl, sym},
					      10000); // 10 Seconds Timeout
    return ret.doubleValue();
  }
    
  // Runnable Interface implementation
  
  /**
   * Thread execution method...called when thread started
   */
  @Override
  public void run() {
    // Try to call a g2 procedure in a loop
    try {
      for (int i=0; i<20; i++) {
	// Call the G2 Procedure
    SecureRandom randomGen = new SecureRandom();	  
	double g2Time = aG2Procedure(i, 
				     "Hi there from Java " + Thread.currentThread(),
				     randomGen.nextDouble()*1000, 
				     Symbol.intern("JAVALINK"));
	System.out.println(i + ". " + 
			   Thread.currentThread() + 
			   " Reported...current G2 real time is " + 
			   g2Time);
      }
    } catch (G2AccessException e) {
      System.out.println("Error occured while calling G2 Procedure, error was " + e.toString());
    }
  }


  public static void main(String args[]) {

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

	System.out.print("Connected to G2 OK...");	

	// We have connected OK, create a new CallG2Procedure 
	JavaThreadsCallingG2 G2procCall = new JavaThreadsCallingG2(g2_connection);
	
	for (int i=0; i<10; i++) {
	  Thread callingThread = new Thread(G2procCall);
	  callingThread.start();
	}
	
	System.out.println("finished");

      } else
	System.out.println("Usage: -g2host <g2hostname> [-g2port <g2portName>]");
      

    //System.exit(0);
  }

}
