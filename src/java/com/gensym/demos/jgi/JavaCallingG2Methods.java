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
import com.gensym.classes.modules.jgidemo.GenericREmployee;

/**
 * This Class simply demonstrates how com.gensym.jgi.G2Gateway can be used to 
 * connect to a G2 server and Call a G2 Procedure.
 * This Java example should be connected to G2 KB JavaLink-Tutorial.kb
 *@version 1.0
 */
public class JavaCallingG2Methods {

  // This will hold our connection to G2
  private G2Connection g2Connection = null;

  // Its good practice to pre lookup Symbols that will be used often
  private static Symbol getEmployeeSymbol = Symbol.intern("GET-EMPLOYEE");

  /**
   * Constructor
   */
  public JavaCallingG2Methods(G2Connection connection) {
    this.g2Connection = connection;

    // We want any objects returned by GET-EMPLOYEE to by passed "By Handle"
    // so that we can communicate directly with the returned G2 Object
    connection.setRemoteRPCReturnKind(getEmployeeSymbol, G2Gateway.PASS_BY_HANDLE);
  }

  
  /**
   * This method will call the G2 procedure "GET-EMPLOYEE" across g2Connection
   *@exception G2AccessException, If an error occurs while calling the RPC
   */
  public GenericREmployee getEmployee() throws G2AccessException {
    return (GenericREmployee)g2Connection.callRPC(getEmployeeSymbol, 
						  new Object[0],
						  10000); // 10 Seconds Timeout
  }
    

  public static void main(String args[]) {

    // A connection to a G2 server can be initiated from Java using G2Gateway.getOrMakeConnection
    // Here an attempt to connect to a G2 server if a port ('-g2port <port>')
    // and/or host name ('-g2host <host>') is specified on the commandline
    CmdLineArgHandler cmdline = new CmdLineArgHandler(args);

    String host = cmdline.getOptionValue("-g2host");
    String port = cmdline.getOptionValue("-g2port");
    String tsname = cmdline.getOptionValue("-tsName");
    G2Connection g2_connection = null;

    if (port != null || host != null)
      {
	try { 
	  // Attempt to connect to G2, and wait until successful or timeout
	  g2_connection = 
	    G2Gateway.getOrMakeConnection(tsname,
					  (host == null ? "localhost" : host),
					  (port == null ? "1111" : port));
	} catch (Exception e) {
	  System.out.println("Could not connect to G2, error was " + e.toString());
	  System.exit(0);
	}

	System.out.print("Connected to G2 OK...");	

	// We have connected OK, create a JavaCallingG2Methods
	JavaCallingG2Methods G2ProcCaller = new JavaCallingG2Methods(g2_connection);
	SecureRandom randomGen = new SecureRandom();

	try {
	  // Get the employee
	  GenericREmployee employee = G2ProcCaller.getEmployee();

	  for (int i=0; i<100; i++) {

	    // Set the employee's Repository-Tag Attribute to a random integer
	    employee.setRepositoryTag((int)Math.abs(randomGen.nextFloat()*1000));
	    // Call the TEST-METHOD on employee
	    Object res = employee.testMethod("JavaLink, called me");

	    System.out.println(i + ".Called TEST-METHOD successfully...returned "+ res);
	  }
	  
	  // Can also reference Names items directly using getUniqueNamedItem
	  employee = (GenericREmployee)
	    g2_connection.getUniqueNamedItem(Symbol.intern("GENERIC-R-EMPLOYEE"),
					     Symbol.intern("GENERIC-EMPLOYEE"));
	  // Call the TEST-METHOD on employee
	  Object res = employee.testMethod("Got item using getUniqueNamesItem");
	  System.out.println("Called a TEST-METHOD successfully...returned : "+ res);

	  
	} catch (G2AccessException e) {
	  System.out.println("Error occured while calling G2 Procedure, error was " + e.toString());
	}

	System.out.println("finished");

      } else
	System.out.println("Usage: -g2host <g2hostname> [-g2port <g2portName>]");
      

    System.exit(0);
  }

}
