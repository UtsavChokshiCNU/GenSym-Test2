/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TraceOut.java
 *
 *  Description:
 *              A class for receiving translatable and
 *              serializable trace messages, with a flexible way of
 *              categorizing the messages and registering interest
 *              in various categories of messages.
 *
 *              Optimized to reduce overhead when tracing is off.
 *
 *	 Author:
 *		Robert Penny		Jul/97
 *
 *     
 *   Modifications:
 *
 */


package com.gensym.nols.deployutil;

import java.util.*;

/** The default simple tracer that sends its messages to standard out.
 * It has its own way of adding itself as a listener that is called
 * from within its <code>initialize</code> method.
 * It can be added to an application in the following way:
 * <blockquote>
 * <pre>
 * // DECLARATION PROBABLY IN THE TOP LEVEL CLASS:
 * private static TraceOut traceListener = new TraceOut();
 * ...
 * // PROBABLY DONE EARLY IN THE "main" METHOD:
 *   traceListener.initialize(traceKeys, traceLevel, messages);
 * </pre>
 * </blockquote>
 * @see com.gensym.message.TraceOut#initialize
 */
public class TraceOut implements MessageListener {
  private static Resource i18n =
  Resource.getBundle("com.gensym.message.Messages");
  private boolean showMessageLookup = true;
  private boolean showClassName = true;

  private static boolean debug = false;

  public static void setDebug(boolean on) {
    debug = on;
  }

  private Hashtable messageTable = null;
  

  /** A simple initializer that set the debugging level fully on for
   * all levels and classes for a key.
   * @param keys a string containing keys separated by spaces, tokenized
   * using the default <code>StringTokenizer</code>
   * @param level the level of verbosity to be listened for. The higher the
   * level, the more MessageEvents will be received.
   * @param messages a string containing messageLookups separated by spaces
   * tokenized using the default <code>StringTokenizer</code>. If
   * <code>null</code> all messages will be printed out, otherwise, only those
   * in <code>messages</code> will be.
   * @see com.gensym.message.Message
   * @see com.gensym.message.MessageEvent
   * @see java.util.StringTokenizer */
  public void initialize(String keys, int level, String messages) {
    StringTokenizer st = new StringTokenizer(keys);
    String token;
    while(st.hasMoreElements()) {
      token = st.nextToken();
      Trace.addMessageListener(this, token, Object.class, level);
    }

    if (messages != null) {
      messageTable = new Hashtable();
      StringTokenizer st2 = new StringTokenizer(messages);
      while(st2.hasMoreElements()) {
	token = st2.nextToken();
	messageTable.put(token, token);
      }
      //      for (Enumeration en = messageTable.keys(); en.hasMoreElements();)
      //System.out.println(en.nextElement());
    }
  }

  public void initialize (String[] keys, int level, String messages[]) {

  }

  public void initialize (String[] keys, int[] levels, String[] messages) {

  }

  public void setShowMessageLookup(boolean yes) {
    showMessageLookup = yes;
  }

  public void setShowClassName(boolean yes) {
    showClassName = yes;
  }

  /** sends messages to standard out. If debugging is enabled it
   * prints stack traces for failed messages (messages that had no
   * translation). Otherwise it prints it out preceded by "Untranslatable
   * Message".
   * If debugging is on, a stack trace is printed out for failed messages.
   */
  @Override
  public void processMessageEvent(MessageEvent event) {
    String message = null;
    String lookup = event.getMessageLookup();
    boolean containsLookup = ((messageTable != null) &&
			      messageTable.containsKey(lookup));
    //    System.out.println("MessageLookup: " + lookup + "; " + containsLookup);
    if ((messageTable == null) ||
	(messageTable.containsKey(event.getMessageLookup()))) {
      try {
	message = event.getMessage();
	StringBuffer buf = new StringBuffer();
	if (showClassName) {
	  buf.append(event.getMessageClassKey().getName());
	  buf.append(": ");
	}

	if (showMessageLookup) {
	  buf.append(lookup);
	  buf.append(": ");
	}
	buf.append(message);
	System.out.println(buf.toString());
      } catch (Exception e) {
	if(debug) {
	  System.err.println (e);
	  e.printStackTrace();
	}
	message = i18n.format("TraceOut_FailedTrace", lookup);
	System.out.println(message);
      }
    }
  }
}    
