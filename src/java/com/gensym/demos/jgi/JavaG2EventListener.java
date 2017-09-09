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

import java.util.Random;
import com.gensym.jgi.*;  
import com.gensym.core.CmdLineArgHandler;
import com.gensym.util.Symbol;
import com.gensym.classes.modules.jgidemo.G2_EventSourceListener;
import com.gensym.classes.modules.jgidemo.EventSourceClass;
import com.gensym.classes.modules.jgidemo.G2_EventSourceEvent;

/**
 * This Class simply demonstrates how com.gensym.jgi.G2Gateway can be used to 
 * connect to a G2 server and listen to Events from a G2 Event Source.
 * Load jgidemo.kb for the G2 side of this demonstration.
 *@version 1.0
 */
public class JavaG2EventListener implements G2_EventSourceListener {

  // This will hold our connection to G2
  private G2Connection g2Connection = null;

  /**
   * Constructor
   */
  public JavaG2EventListener(G2Connection connection) {
    this.g2Connection = connection;
  }

  // *****************************************************************
  // To Implement G2_EventSourceListener exported from G2-EVENT-SOURCE-CLASS
  int evtCnt = 0;
  /**
   * To Implement G2_EventSourceListener exported from G2 Event 
   * Generator class G2EventSourceClass.
   */
  @Override
  public void anEvent(G2_EventSourceEvent arg1) throws G2AccessException
  {
    System.out.println("Received an event from " + arg1.getSource() + "..." + arg1.getMessage());
    evtCnt++;
    if (evtCnt == 10) {
      // For fun lets reattach to the listener after 10 events.
      // Note: There may not be a one-one mapping for objects added to event sources in G2
      //       and the number of Java Listeners. This is because JavaLink will use a MultiCast listener, that 
      //       will be added once for a particular G2 event source, but can serve many Java event listeners.
      deattachFromG2EventSource(g2EventSource);
      attachToG2EventSource(g2EventSource);
      evtCnt = 0;
    }
  }
  
  /**
   * Add ourself as a listener for event being fired from an EVENT-SOURCE-CLASS
   */
  public void attachToG2EventSource(EventSourceClass g2EventSource) throws G2AccessException
  {
    g2EventSource.addG2_EventSourceListener(this);
    System.out.println("Added " + this.toString() + " as listener to Event-Source-Class events");
  }

  /**
   * Remove ourself as a listener for event being fired from an EVENT-SOURCE-CLASS
   */
  public void deattachFromG2EventSource(EventSourceClass g2EventSource) throws G2AccessException
  {
    g2EventSource.removeG2_EventSourceListener(this);
    System.out.println("Removed " + this.toString() + " as listener to Event-Source-Class events");
  }
  
  EventSourceClass g2EventSource = null;   

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
	  g2_connection = (G2Connection)
	    G2Gateway.getOrMakeConnection(tsname,
					   (host == null ? "localhost" : host),
					   (port == null ? "1111" : port));
	} catch (Exception e) {
	  System.out.println("Could not connect to G2, error was " + e.toString());
	  System.exit(0);
	}

	System.out.print("Connected to G2 OK...");	

	// We have connected OK, create a JavaCallingG2Methods
	JavaG2EventListener g2EventListener = new JavaG2EventListener(g2_connection);

	try {
	  g2EventListener.g2EventSource = (EventSourceClass)g2_connection.getUniqueNamedItem
	    (Symbol.intern("EVENT-SOURCE-CLASS"),
	     Symbol.intern("AN-EVENT-GENERATOR"));
	  g2EventListener.attachToG2EventSource(g2EventListener.g2EventSource);
	} catch (G2AccessException e) {
	  e.printStackTrace();
	}

	// now wait for events

      } else
	System.out.println("Usage: -g2host <g2hostname> [-g2port <g2portName>] [-tsName <rmiservername>]");
      
  }

}



