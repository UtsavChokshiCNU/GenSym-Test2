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

import com.gensym.jgi.G2Gateway;
import com.gensym.jgi.G2Access;
import com.gensym.util.VariableValueEvent;
import com.gensym.util.VariableValueListener;
import com.gensym.util.Symbol;
import com.gensym.core.CmdLineArgHandler;
import com.gensym.classes.VariableOrParameter;

/** A simple class that demonstrates how to connect to a G2, obtain an
 * <code>Item</code> by class and name, and subscribe to that
 * <code>Item</code>.
 * <p>
 * To execute the code of this class, the command-line is as follows:
 * <blockquote>
 * <pre>
 * java com.gensym.demos.jgi.SimpleSubscription [-url <url>] [-host <host>] [-port port] [-class <class>] -name [name]
 * </pre>
 * </blockquote>
 * <p>
 * The meaning of the url, host, and port are described in
 * <code>G2Gateway.getOrMakeConnection()</code>, and the class and name are
 * described in <code>getUniqueNamedItem</code>. The url defaults to
 * <code>null</code>, the host to localhost, and the port to 1111.
 * The class defaults to
 * <code>ITEM</code>, and only the name is absolutely required.
 * <p>
 * After the class is started, any change to a subscribable attribute on
 * the named item will result in a printout to stdout showing the
 * contents of the ItemEvent that was sent because of that change. This
 * makes this class a useful tool in developing applications that depend
 * on subscriptions, as it enables the developer to see the structure of
 * the data that is sent for that subscription. Pay particular attention
 * to the "new value" part of the printout.
 * @see com.gensym.jgi.G2Gateway#getOrMakeConnection(String, String, String)
 * @see com.gensym.jgi.G2Gateway#getUniqueNamedItem(com.gensym.Symbol, com.gensym.Symbol)
 */
public class SimpleVariableSubscription {
  // The correct way to make a Symbol.
  public static final Symbol ITEM_ = Symbol.intern ("ITEM");
  public static final Symbol A_TEST_CLASS_INSTANCE_ = Symbol.intern ("TEST-QUANTITATIVE-PARAMETER");

  public static void main(String[] args) {
    // read command-line
    CmdLineArgHandler cmdLine = new CmdLineArgHandler (args);
    // information for connecting to G2
    String url   = cmdLine.getOptionValue ("-url");
    String host  = cmdLine.getOptionValue ("-g2host");
    host = (host == null ? "localhost" : host);
    String port  = cmdLine.getOptionValue ("-g2port");
    port = (port == null ? "1111" : port);
    // information to find a unique named item in G2
    String classString = cmdLine.getOptionValue ("-class");
    String nameString  = cmdLine.getOptionValue ("-name");
    // convert the strings to symbols
    Symbol clazz = (classString == null ? ITEM_ : 
		    Symbol.intern(classString.toUpperCase()));
    Symbol name = (nameString == null ? A_TEST_CLASS_INSTANCE_ : 
		   Symbol.intern(nameString.toUpperCase()));
    // do actual work
    try {
      // connect to G2
      G2Access context = G2Gateway.getOrMakeConnection(url, host, port);
      // obtain a java object that represents a G2 ITEM
      VariableOrParameter item = (VariableOrParameter)(context.getUniqueNamedItem(clazz, name));

      // Define a simple implementation of the ItemListener interface
      VariableValueListener vil =
	new VariableValueListener() {
	@Override
	public void valueChanged(VariableValueEvent e) {
	  System.out.println("valueChanged: " + e);
	}
	@Override
	public void receivedInitialValue(VariableValueEvent e) {
	  System.out.println("receivedInitialValues: " + e);
	}
      };

      // initiate the subscription
      item.addVariableValueListener(vil);
    } catch (Exception ex) {
      System.out.println(ex.getMessage());
      ex.printStackTrace();
      System.exit(-1);
    }
  }
}
