package com.gensym.tests.jgi.testharness;

import java.util.Hashtable;
import java.util.Random;
import java.lang.Math.*;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.core.*;
import com.gensym.core.CmdLineArgHandler;

import java.util.Vector;

/**
 * Connects to G2 and attempts to start G2.
 */
public class G2Starter
{
  public static void main(String args[])
  {

    System.out.println("Attempting to Start G2...\n");

    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);

    String host = cmdline.getOptionValue("-host");
    String port = cmdline.getOptionValue("-port");
    boolean result = false;

    if (port != null || host != null)
      {
	//try to connect to a g2 if we are asked
	try {

	  G2Connection g2_connection  =
	    G2Gateway.getOrMakeConnection((host == null ? "localhost" : host),
					  (port == null ? "1111" : port));

	  g2_connection.returnMessage("Connected to G2Starter \n Java TestHarness starting G2 tests");
	  System.out.println("Test Harness Starter...\n");
	  System.out.println("Connected to G2 OK...");
	  try{
	    Thread.sleep(5000); // wait for other processes to start
	    g2_connection.callRPC(Symbol.intern("SIGNAL-JAVA-SIDE-READY-TO-START"), new Object [0]);
	    //g2_connection.setG2State(G2Gateway.RESET_);
	    //g2_connection.setG2State(G2Gateway.RUNNING_);
	  }catch (Exception e){};
	  System.out.println("G2 Test Harness Started...\n");


	} catch (Exception E) { 
	  System.out.println(E.toString()); }

      }
    System.exit(0);
  }



}

