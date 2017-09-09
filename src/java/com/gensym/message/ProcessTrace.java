package com.gensym.message;

import java.util.Enumeration;
import java.util.Hashtable;
import java.util.WeakHashMap;
import java.util.Vector;
import java.util.Locale;

import com.gensym.core.DebugUtil;

/**
 * A ProcessTrace can be used to report trace messages for an identified "process".
 * An instance of a ProcessTrace could be passed/utilized by the collection of 
 * instances that make up a given java process or task allowing trace messages
 * to be grouped per process.
 * Provides convenience methods for sending messages while tracing.
 * NOTE: Does not generate garbage in the arguments to calls to 
 * <code>report</code> unless these calls are not made when tracing is off. The
 * convenience <code>report</code> methods are provided to help avoid
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
 * processTrace.send(this, 5, traceKey, i18nTrace, "interestingThingHappened",
 *              arg1, arg2, arg3);
 * </pre>
 * </blockquote>
 * When adding tracing to your own application, it is necessary to add a
 * MessageListener that will receive the Trace messages and print them out
 * in whatever manner is appropriate for your application. A simple
 * implemention of MessageListener can be seen in com.gensym.message.TraceOut.
 * @see com.gensym.message.TraceOut
 * @author M.D.Gribble
 * @version 1.0
 */
public class ProcessTrace implements MessageGenerator
{

  /**
   * Common ProcessID for general process tracing.
   */
  public static final String GENERAL_TRACE_PROCESS_ID = "_general_process_";

  protected String processID;
  private Hashtable objectSubscribers = new Hashtable();
  private Hashtable messageSubscriptions = new Hashtable();
  protected boolean traceOn = false;
  protected Resource dummyResource = new DummyResource();

  private static Hashtable processTraceTable = new Hashtable();
  private static MessageKey exceptionTraceKey =
    Trace.registerMessageKey ("com.gensym.trace.exception", Trace.class);
  private static Resource i18nTrace =
    Trace.getBundle("com.gensym.message.Messages", Locale.getDefault());

  /**
   * Construct a ProcessTrace with a given processID.
   */
  protected ProcessTrace(String processID)
  {
    this.processID = processID;
  }

  /**
   * Return a ProcessTrace for a given processID. A ProcessTrace is created
   * if one does not exist for a give processID.
   * @param processID a non-null processID.
   */
  public static ProcessTrace getProcessTrace(String processID)
  {
    ProcessTrace processTrace = (ProcessTrace)processTraceTable.get(processID);

    if (processTrace == null) {
      processTrace = new ProcessTrace(processID);
      processTraceTable.put(processTrace, processID);
    }
    return processTrace;
  }

  /**
   * Convenience method for setting the ProcessTrace on an Enumeration of
   * TraceableProcessObjects.
   * @param processTrace The possibly-null ProcessTrace to set.
   * @param enum An Enumeration of objects that if implement TraceableProcessObject, will
   *        be called with setProcessTrace(processTrace).
   */
  public static void setProcessTrace(ProcessTrace processTrace,
				     Object source,
				     Enumeration en)
  {
    try {
      while(en.hasMoreElements()) {
	Object obj = en.nextElement();
	if (obj instanceof TraceableProcessObject) {
	  ((TraceableProcessObject)obj).setProcessTrace(processTrace);
	}
      }
    } catch (Throwable e) {
      processTrace.exception(source, e, " while calling setProcessTrace");
    }
  }

  /**
   * Return an Enumeration of the ProcessTraces that have been created in this VM.
   * @return A non-null Enumeration of ProcessTraces.
   */
  public static Enumeration getProcessTraces()
  {
    return processTraceTable.elements();
  }

  // Implement Traceable

  /**
   * Subscribe a MessageListener to receive Trace messages from this Traceable object.
   * @param listener The non-null MessageListener.
   * @param key A non-null String detailing the trace topic the subscriber is interested in.
   * @param classKey A non-null Class detailing the Class of the trace message generators that
   *        the subscriber is interested in.
   * @param level An int detailing the level at which level of messages the subscriber wises to
   *        to receive messages.
   */
  @Override
  public synchronized void addMessageListener(MessageListener listener,
					      String key,
					      Class classKey,
					      int level) 
  {
    Vector listeners = (Vector)messageSubscriptions.get(key);
    //System.out.println ("Adding Listener " + listener + " for Key: " + key +
    //" ClassKey = " + classKey + ", Level = " + level);
    
    if (listeners == null) {
      listeners = new Vector();
      messageSubscriptions.put(key, listeners);
    }

    listeners.addElement(new MessageSubscription(listener, classKey, level));
	
  }


  /**
   * Remove a MessageListener from subscribing to Trace messages.
   * @param listener The non-null MessageListener no-longer interested in messages.
   */
  @Override
  public synchronized void removeMessageListener(MessageListener listener) 
  {
    for (Enumeration e = messageSubscriptions.keys(); e.hasMoreElements();) {
      String key = (String)e.nextElement();
      Vector listeners = (Vector)messageSubscriptions.get(key);
      listeners.remove(listener);

      if (listeners.isEmpty())
	messageSubscriptions.remove(key);
    }
  }



  /**
   * Return the trace status of this ProcessTrace.
   * @return True if messages sent to the ProcessTrace are processed further and 
   *         forwarded to subscribers.
   */
  public boolean getTraceOn()
  {
    return traceOn;
  }

  /**
   * Set the current trace status of this ProcessTrace.
   * @param traceOn set TRUE for messages sent to the ProcessTrace to be forewarded to 
   *        interesed subscribers. Set FALSE for no processing and minmial overhead.
   */
  public void setTraceOn(boolean traceOn)
  {
    this.traceOn = traceOn;
  }

  /**
   * Get the process ID for this ProcessTrace.
   * @return The non-null processID for this ProcessTrace.
   */
  public String getProcessID()
  {
    return processID;
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
  public boolean send(Object source,
		      int level, 
		      MessageKey key, 
		      Resource res,
		      String message) 
  {
    Vector listeners;
    if (traceOn &&
	((listeners = (Vector)messageSubscriptions.get(key.msgKey)) != null)) {
      //System.out.println ("Calling Message.send0");
      return send(new ProcessMessageEvent(source,
					  processID, 
					  level, 
					  key, 
					  (res == null ? dummyResource : res), 
					  message, 
					  null),
		  listeners);
    } else
      return false;
  }

  public boolean send(Object source,
		      int level, 
		      MessageKey key, 
		      Resource res,
		      String message,
		      Object arg1) 
  {
    if (traceOn)
      return send(source, level, key, res, message, new Object[] {arg1});
    else return false;
  }

  public boolean send(Object source,
		      int level, 
		      MessageKey key, 
		      Resource res,
		      String message,
		      Object arg1,
		      Object arg2) 
  {
    if (traceOn)
      return send(source, level, key, res, message, new Object[] {arg1, arg2});
    else
      return false;
  }

  public boolean send(Object source,
		      int level, 
		      MessageKey key, 
		      Resource res,
		      String message,
		      Object arg1,
		      Object arg2,
		      Object arg3) 
  {
    if (traceOn) 
      return send(source, level, key, res, message, new Object[] {arg1, arg2, arg3});
    else
      return false;
  }


  public boolean send(Object source,
		      int level, 
		      MessageKey key, 
		      Resource res,
		      String message,
		      Object[] args) 
  {
    Vector listeners;
    if (traceOn &&
	((listeners = (Vector)messageSubscriptions.get(key.msgKey)) != null)) {
      return send(new ProcessMessageEvent(source,
					  processID, 
					  level, 
					  key, 
					  (res == null ? dummyResource : res), 
					  message, 
					  args),
		  listeners);
    } else
      return false;
  }

  /**
   * Send a message detailing a Method Entry.
   */
  public boolean sendMethodEntry(Object source,
				 int level,
				 MessageKey key,
				 String methodName,
				 String message,
				 Object[] args)
  {
    return sendMethodMessage(source, level, key, 
			     ProcessMethodMessageEvent.METHOD_ENTRY, methodName, message, args, null);
  }

  /**
   * Send a message detailing a Method Exit.
   */
  public boolean sendMethodExit(Object source,
				int level,
				MessageKey key,
				String methodName,
				String message,
				Object returnObj)
  {
    return sendMethodMessage(source, level, key, 
			     ProcessMethodMessageEvent.METHOD_EXIT, methodName, message, null, returnObj);
  }

  /**
   * Send a message detailing a Method message.
   */
  public boolean sendMethodMessage(Object source,
				   int level,
				   MessageKey key,
				   String methodName,
				   String message,
				   Object[] args)
  {
    return sendMethodMessage(source, level, key, 
			     ProcessMethodMessageEvent.METHOD_INNER, methodName, message, args, null);
  }

  private boolean sendMethodMessage(Object source,
				    int level,
				    MessageKey key,
				    int type,
				    String methodName,
				    String message,
				    Object[] args,
				    Object returnObj)
  {
    Vector listeners;
    if (traceOn &&
	((listeners = (Vector)messageSubscriptions.get(key.msgKey)) != null)) {
      return send(new ProcessMethodMessageEvent(source,
						processID, 
						level, 
						key, 
						type,
						methodName,
						dummyResource, 
						message, 
						args,
						returnObj),
		  listeners);
    } else
      return false;
  }

  /**
   * Traces  a backtrace using <code>Thread.dumpStack()</code> if
   * there are any listeners for <code>key</code>.
   */
  public void dumpStack (Object source, int level, MessageKey key) {
    Vector listeners = null;
    if (traceOn &&
	((listeners = (Vector)messageSubscriptions.get(key.msgKey)) != null))
	send (new ProcessMessageEvent (source, 
				       processID, 
				       0, 
				       exceptionTraceKey, 
				       i18nTrace, 
				       "dumpStack",
				       new Object[] {DebugUtil.getStackTrace()}),
	      listeners);
  }

  /**
   * Prints out the message, the t.getMessage(), t.printStackTrace()
   * and a Thread.dumpStack(), to provide maximum debugging information.
   * Only does these things when tracing is on
   */
  public void exception (Object source, 
			 Throwable t, 
			 String message) {
    if (traceOn) {
      if (t == null)
	return;
      //if (message != null)
      //System.err.println(message);
      
      //System.out.println(t);
      String origBackTrace = DebugUtil.getStackTrace (t);
      //System.out.println (origBackTrace);
      //System.out.println ("Caught and traced from: ");
      String catchBackTrace;
      catchBackTrace = DebugUtil.getStackTrace (1, -1);
      //System.out.println (catchBackTrace);

      // Tell listeners
      Vector listeners = null;
      if ((listeners = (Vector)messageSubscriptions.get (exceptionTraceKey.msgKey)) != null)
	send (new ProcessMessageEvent (source, 
				       processID, 
				       0, exceptionTraceKey, 
				       i18nTrace, "tracingException",
				       new Object[] {message + "\n" + t.getMessage (), 
						       origBackTrace, catchBackTrace}),
	      listeners);
      if (t instanceof java.lang.reflect.InvocationTargetException)
	exception (source, ((java.lang.reflect.InvocationTargetException)t).getTargetException ());
      else if (t instanceof ExceptionInInitializerError)
	exception (source, ((ExceptionInInitializerError)t).getException ());
    }
  }

  public void exception (Object source, Throwable t) {
    if (traceOn)
      exception(source, t, null);
  }



  private boolean send(MessageEvent message, Vector listenerVector) {
    MessageSubscription[] listeners = new MessageSubscription[listenerVector.size()];
    listenerVector.copyInto(listeners);
    boolean anySent = false;
    int level = message.getMessageLevel();
    Class classKey = Object.class;
    try {
      classKey = message.getMessageClassKey();
    } catch (ClassNotFoundException cnfe) {
      // uses Object if the class is not available.
    } 
    for(int i = 0; i<listeners.length; i++) {
      MessageSubscription sub = listeners[i];
      if (sub.interestedInMessage(classKey, level)){
	anySent = true;
	try {
	  sub.listener.processMessageEvent(message);
	} catch (Exception ex) {
	  ex.printStackTrace();
	  System.err.println(message.getMessageLookup());
	}
      }
    }
    return anySent;
    
  }

  class MessageSubscription {
    final MessageListener listener;
    final Class classKey;
    final int level;

    MessageSubscription(MessageListener listener, Class classKey, int level) {
      this.listener = listener;
      if (classKey == null)
	throw new NullPointerException("MustSpecifyClass");
      this.classKey = classKey;
      this.level = level;
    }

    boolean interestedInMessage(Class classKeyIn, int messageLevel) {
      // fix this: debugging
      return (((messageLevel <= level) || level < 0) &&
	      classKey.isAssignableFrom(classKeyIn));
    }
}



}
