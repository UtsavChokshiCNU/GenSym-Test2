/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Trace.java
 *
 *  Description:
 *              A static class for sending translatable and
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

package com.gensym.message;

import java.util.*;
import java.io.*;
import com.gensym.core.DebugUtil;

/**
 *  Provides convenience methods for sending messages while tracing.
 * NOTE: Do not generate garbage in the arguments to calls to 
 * <code>send</code> unless these calls are not made when tracing is off. The
 * convenience <code>send</code> methods are provided to help avoid
 * unnecessary garbage in complex tracing statements.
 * <p>
 * Since Tracing should not affect the normal operation of an application,
 * the methods in this class will not throw exceptions.
 * <p>
 * The following shows a typical usage of this class.: 
 * <blockquote>
 * <pre>
 * // DECLARATIONS:
 * private static final Resource i18nTrace =
 *         Trace.getBundle("com.gensym.foo.TraceMessages");
 * private static final MessageKey traceKey =
 *         Trace.registerMessageKey("com.gensym.foo", MyClass.class);
 * ...
 * // CALL IN CODE BODY
 * Trace.send(5, traceKey, i18nTrace, "interestingThingHappened",
 *            arg1, arg2, arg3);
 * </pre>
 * </blockquote>
 * When adding tracing to your own application, it is necessary to add a
 * MessageListener that will receive the Trace messages and print them out
 * in whatever manner is appropriate for your application. A simple
 * implemention of MessageListener can be seen in com.gensym.message.TraceOut.
 * @see com.gensym.message.TraceOut
 * @author Robert Penny
 * @version 1.0
 */
public class Trace extends Message {

  private static boolean traceOn;
  private static boolean exceptionTraceOn;

  private static volatile Resource i18n = null;
  private static Resource defaultResource = new DummyResource();
  private static final Class objectArrayClass = (new Object[0]).getClass ();

  /*
   * Support for "tracing" exceptions
   */
  private static MessageKey exceptionTraceKey =
    Trace.registerMessageKey ("com.gensym.trace.exception", Trace.class);
  private static Resource i18nTrace =
    Trace.getBundle("com.gensym.message.Messages", Locale.getDefault());

  /**
   * Need to use this method to help avoid circularity in class-loading
   * with the Resource class.
   */
  private static final Resource getI18n() {
    if (i18n == null) {
      synchronized (Trace.class) {
        if (i18n == null) {
          try {
            i18n = Resource.getBundle("com.gensym.message.Messages");
          } catch (Exception e) {
            System.out
                .println("Unable to locate resource com.gensym.message.Messages because: "
                    + e.getMessage()
                    + ", using a dummy resource for messages from Trace class");
            e.printStackTrace();
            i18n = defaultResource;
          }
        }
      }
    }
    return i18n;
  }
			 
  private static MessageKey traceKey =
  registerMessageKey("com.gensym.message", "com.gensym.message.Trace");

  /**
   * prevent instantiation, but not subclassing
   */
  protected Trace() {
  }

  /**
   * Turn tracing on or off
   */
  public static void setTraceOn(boolean on) {
    traceOn = on;
  }

  public static boolean getTraceOn() {
    return traceOn;
  }

  /**
   * Turn Exception tracing on or off
   */
  public static void setExceptionTraceOn (boolean traceState) {
    exceptionTraceOn = traceState;
  }

  public static boolean getExceptionTraceOn() {
    return exceptionTraceOn;
  }

  /**
   * Provided as a wrapper around Resource.getBundle so that
   * missing tracing resources cause no exceptions. If the requested
   * Resource is missing, it returns a "dummy" Resource.
   * @see com.gensym.message.Resource#getBundle(String)
   * @see com.gensym.message.Resource#(boolean)
   */
  public static Resource getBundle(String resourceName) {
    try {
      return Resource.getBundle(resourceName);
    } catch (Exception ex) {
      if (traceOn) {
	System.out.println(getI18n().format("Trace_unableToLocateResource",
					    resourceName));
	exception(ex);
      }
      return defaultResource;
    }
  }

  /**
   * Provided as a wrapper around Resource.getBundle so that
   * missing tracing resources cause no exceptions. If the requested
   * Resource is missing, it returns a "dummy" Resource.
   * @see com.gensym.message.Resource#getBundle(String, Locale)
   * @see com.gensym.message.Resource#(boolean)
   */
  public static Resource getBundle(String resourceName, Locale locale) {
    try {
      return Resource.getBundle(resourceName, locale);
    } catch (Exception ex) {
      return defaultResource;
    }
  }

  private static void setTraceVariable(Class traceClass, boolean value) {
    try {
      java.lang.reflect.Field field = traceClass.getField("traceOn");
      field.setBoolean(traceClass, true);
    } catch (Exception iae) {
      send(1, traceKey, getI18n(), "Trace_UnableToSetTraceInClass",
	   traceClass.toString(), iae.toString());
    }
  }

  /**
   * for use in RMI packages where prohibitions on "Inner Classes" (i.e.
   * use of <code>MyClass.class</code>) makes use of the other signatures
   * difficult in a static initializer
   */
  public static MessageKey registerMessageKey(String key, String otherKey) {
    Class classKey = Object.class;

    try {
      classKey = Class.forName(otherKey);
    } catch (Exception ex) {
      send(1, traceKey, getI18n(), "Trace_ClassFailedRegistration", ex, key, otherKey);
      ex.printStackTrace();
    }

    return registerMessageKey(key, classKey);
  }

  /**
   * Creates a <code>MessageKey</code> to be used later in
   * <code>Trace.send()</code> methods. MessageListeners can register
   * interest in either the Class or the String, or both.
   * @see com.gensym.message.Message#registerMessageKey
   * @see com.gensym.message.Message#addMessageListener.
   */
  public static MessageKey registerMessageKey(final String key, final Class classKey) {
    try {
    Class messageKey = classKey;
    if (messageKey == null)
      messageKey = Class.forName("java.lang.Object");
      return Message.registerMessageKey(key, messageKey);
    } catch (Exception ex) {
      ex.printStackTrace();
    }

    return null;
  }

  /**
   * Allow to specify whether the key is for internal tracing or for
   * public consumption.
   * NOTE: this is a proposed signature that currently ignores the
   * third argument.
   */
  public static MessageKey registerMessageKey(String key, Class classKey,
					      boolean internal){
    return registerMessageKey(key, classKey);
  }

  /**
   * Send a tracing event if tracing is on.
   * The remaining signatures of <code>send</code> are convenience
   * methods that also allow for less generation of garbage.
   * @param level the level of verbosity associated with this message.
   * @param key the special key associated with this tracing method
   * @param res the resource used to translate the message
   * @param message the key for looking up the message in the given
   * <code>Resource</code>
   * @param args the arguments to be formatted into the message specified by
   * <code>message</code> NOTE: the toString() method is called on the
   * elements of this array if a message is to be sent.
   */
  public static boolean send(int level, MessageKey key, Resource res,
			     String message, Object[] args) {
    Enumeration listeners;
    if (traceOn &&
	((listeners = getSubscriptions(key.msgKey)) != null)) {
      if (args == null || args.getClass () == objectArrayClass) { // Describe the elements
	return Message.send(new MessageEvent(level, key, res, message, args),
			    listeners);
      } else {			// Treat as single Object
	return Trace.send (level, key, res, message, (Object)args);
      }
    } else
      return false;
  }

  public static boolean send (MessageEvent message) {
    Enumeration listeners;
    if (traceOn &&
	((listeners = getSubscriptions(message.getMessageKey())) != null))
      return Message.send(message, listeners);
    else
      return false;
  }

  /**
   * Allows a message to be sent without first registering a key.
   */
  public static boolean send(int level, String key, Class classKey,
			     Resource res, String message, Object[] args) {
    Enumeration listeners;
    if (traceOn && ((listeners = getSubscriptions(key)) != null))
      return Message.send(new MessageEvent(level, key, classKey,
					   res, message, args),
			  listeners);
    else
      return false;
  }

  public static boolean send(int level, MessageKey key, Resource res,
			     String message) {
    Enumeration listeners;
    if (traceOn &&
	((listeners = getSubscriptions(key.msgKey)) != null)) {
      //System.out.println ("Calling Message.send0");
      return Message.send(new MessageEvent(level, key, res, message, null),
			  listeners);
    } else
      return false;
  }

  public static boolean send(int level, MessageKey key, Resource res,
			     String message, Object arg) {
    Enumeration listeners;
    if (traceOn &&
	((listeners = getSubscriptions(key.msgKey)) != null))
      return Message.send(new MessageEvent(level, key, res, message,
					   new Object[] {arg}),
			  listeners);
    else
      return false;
  }

  public static boolean send(int level, MessageKey key, Resource res,
			     String message, Object arg1, Object arg2) {
    Enumeration listeners;
    if (traceOn &&
	((listeners = getSubscriptions(key.msgKey)) != null))
      return Message.send(new MessageEvent (level, key, res, message,
					    new Object[] {arg1, arg2}),
			  listeners);
    else
      return false;
  }

  public static boolean send(int level, MessageKey key, Resource res,
			     String message,
			     Object arg1, Object arg2, Object arg3) {
    Enumeration listeners;
    if (traceOn &&
	((listeners = getSubscriptions(key.msgKey)) != null))
      return Message.send(new MessageEvent(level, key, res, message,
					   new Object[] {arg1, arg2, arg3}),
			  listeners);
    else
      return false;
  }

  public static boolean send(int level, MessageKey key, Resource res,
			     String message, Object arg1, Object arg2,
			     Object arg3, Object arg4) {
    Enumeration listeners;
    if (traceOn &&
	((listeners = getSubscriptions(key.msgKey)) != null))
      return Message.send(new MessageEvent(level, key, res, message,
					   new Object[] {arg1, arg2,
							 arg3, arg4}),
			  listeners);
    else
      return false;
  }

  /**
   * Convenience method for storing an object for later use
   */
  public static boolean writeObjectToFile(int level, MessageKey key,
					  String path, Object obj){
    Enumeration listeners;
    if (traceOn &&
	((listeners = getSubscriptions(key.msgKey)) != null)) {
      File file = new File(path);
      return writeObjectToFile(level, key, file, obj);
    }

    return false;
  }

  public static boolean writeObjectToFile(int level, MessageKey key,
					  File file, Object obj){
    ObjectOutputStream output = null;
    boolean succeeded = false;
    try {
      FileOutputStream fileOutput = new FileOutputStream(file);
      output = new ObjectOutputStream(fileOutput);
      output.writeObject(obj);
    } catch (Exception ex) {
      ex.printStackTrace();
    } finally {
      if(output != null) {
	try {
	  output.close();
	  succeeded = true;
	} catch (IOException ex) {}
      }
    }
    return succeeded;
  }

  /**
   * retrieve objects stored by <code>writeObjectsToFile </code>
   */
  public static Object readObjectFromFile(int level, MessageKey key,
					  String path)
  throws ClassNotFoundException, InvalidClassException,
  StreamCorruptedException, OptionalDataException, IOException {
    File file = new File(path);
    ObjectInputStream input = null;
    Object returnVal = null;
    try {
      FileInputStream fileInput = new FileInputStream(file);
      input = new ObjectInputStream(fileInput);
      returnVal = input.readObject();
    } finally {
      if (input != null)
	input.close();
    }

    return returnVal;
  }

  /**
   * Prints out a backtrace using <code>Thread.dumpStack()</code> if
   * there are any listeners for <code>key</code>.
   */
  public static void backTrace (int level, MessageKey key) {
    Enumeration listeners;
    if (traceOn &&
	((listeners = getSubscriptions(key.msgKey)) != null))
      Thread.dumpStack();
  }

  /**
   * Prints out the message, the t.getMessage(), t.printStackTrace()
   * and a Thread.dumpStack(), to provide maximum debugging information.
   * Only does these things when tracing is on
   */
  public static void exception (Throwable t, String message) {
    if (exceptionTraceOn) {
      if (t == null)
	return;
      if (message != null)
	System.err.println(message);
      
      System.out.println(t);
      String origBackTrace = DebugUtil.getStackTrace (t);
      System.out.println (origBackTrace);
      System.out.println ("Caught and traced from: ");
      String catchBackTrace;
      catchBackTrace = DebugUtil.getStackTrace (1, -1);
      System.out.println (catchBackTrace);

      // Tell listeners
      Enumeration listeners = null;
      if ((listeners = getSubscriptions (exceptionTraceKey.msgKey)) != null)
	Message.send (new MessageEvent (0, exceptionTraceKey, i18nTrace, "tracingException",
					new Object[] {message + "\n" + t.getMessage (), origBackTrace, catchBackTrace}),
		      listeners);
      if (t instanceof java.lang.reflect.InvocationTargetException)
	exception (((java.lang.reflect.InvocationTargetException)t).getTargetException ());
      else if (t instanceof ExceptionInInitializerError)
	exception (((ExceptionInInitializerError)t).getException ());
    }
  }

  public static void exception (Throwable t) {
    if (exceptionTraceOn)
      exception(t, null);
  }

  /**
   * pretty-print a buffer of integer
   */
  public static String pprint(final int[] buf, final int count) {
    StringBuffer strBuf = new StringBuffer();
    int countLocal = count;
    if (countLocal > buf.length)
      countLocal = buf.length;

    for (int i = 0; i < countLocal; i++) {
      strBuf.append(i).append("=").append(buf[i]).append(";");
    }
    return strBuf.toString();
  }

  /**
   * pretty-print a buffer of integer
   */
  public static String pprint(int[] buf) {
    return pprint(buf, buf.length);
  }
    
  /**
   * pretty-print a buffer of Objects
   */
  public static String pprint(final Object[] buf, final int count) {
    StringBuffer strBuf = new StringBuffer();
    int countLocal = count;
    if (countLocal > buf.length)
      countLocal = buf.length;

    for (int i = 0; i < countLocal; i++) {
      strBuf.append(i).append("=").append(buf[i]).append(";");
    }
    return strBuf.toString();
  }

  /**
   * pretty-print a buffer of Objects
   */
  public static String pprint(Object[] buf) {
    return pprint(buf, buf.length);
  }
}
