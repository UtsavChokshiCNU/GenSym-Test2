package com.gensym.beansruntime;

import java.util.Vector;

public class Hookup implements java.io.Serializable
{
  static final long serialVersionUID = 3823424906331228787L;

  /**
   *  This field is made accessible to subclasses of Hookup directly.  See the
   *  documentation for the getDebug and setDebug methods for documentation.
   */
  protected transient boolean debug = false;
  private transient Vector listeners = null;
  private transient Vector continuations = null;
  private transient boolean paused = false;
  private boolean sourceSet = false;
  private boolean targetSet = false;
  protected Object source = null;
  protected Object target = null;
  private boolean argumentCountSet = false;
  private static transient HookupListener debugger = null;
  private int index;
  int argumentCount = 1;

  // change me, change the switch statements
  public static final int MAX_HOOKUP_EVENT_ARGS = 4; 
  
  /**
   * addHookupListeners registers interest in event delivery through a
   * hookup.  When the hookup is in debugging mode, event delivery will
   * be paused, and events will be sent to all listeners.  Hookup listeners
   * are NOT serialized when a hookup is saved, an editor or debugger must
   * manually re-establish linkage.
   */
  public final synchronized void addHookupListener(HookupListener listener)
  {
    if (listeners == null)
      listeners = new Vector();
    listeners.addElement(listener);
  }
  
  /**
   * removeHookupListener does what its name implies.
   */
  public final synchronized void removeHookupListener(HookupListener listener)
  {
    listeners.removeElement(listener);
    if (listeners.isEmpty())
      listeners = null;
  }


  /** 
   * Enables/disables the debugging of hookups, primarily for
   * use by the ComponentEditor.  This property is not saved when
   * a hookup is serialized; hookups always deserialize into a running 
   * state to simplify things for runtime containers.
   */
  public final void setDebug(boolean debug)
  {
    this.debug = debug;
  }

  /**
   * This retrives the debugging state of the hookup.
   */
  public final boolean getDebug()
  {
    return debug;
  }

  /**
   * Set the index.  Indices can be used to matchup hookup identity accross
   * serialization/deserialization for use by development tools.
   */
  public void setIndex(int index)
  {
    this.index = index;
  }

  /**
   *   Get the index.
   */
  public int getIndex()
  {
    return index;
  }
       

  /**
   * Sets the target object of this hookup.  It has no effect if called
   * a second time.  It effectively provides an additional argument to the
   * constructor.
   */
  public final void setTarget(Object target)
  {
    if (!targetSet)
      {
	this.target = target;
	targetSet = true;
      }
  }

  /**
   * Sets the source object of this hookup.  It has no effect if called
   * a second time.  It effectively provides an additional argument to the
   * constructor.
   */
  public final void setSource(Object source)
  {
    if (!sourceSet)
      {
	this.source = source;
	sourceSet = true;
      }
  }
  
  /**
   * Sets the argumentCount of this hookup.  It has no effect if called
   * a second time.  It effectively provides an additional argument to the
   * constructor.
   */
  public final void setArgument(int argumentCount)
  {
    if (!argumentCountSet)
      {
	if (argumentCount > MAX_HOOKUP_EVENT_ARGS)
	  throw new IllegalArgumentException("argumentCount "+argumentCount+
					     " > MAX_HOOKUP_EVENT_ARGS, which is "+
					     MAX_HOOKUP_EVENT_ARGS);
	this.argumentCount = argumentCount;
	argumentCountSet = true;
      }
  }

  /**
   * pauseHookupEvent is called by the listener methods of subclasses of
   * Hookup when debugging is enabled for that hookup.  Events entering 
   * this hookup will be enqueued until continueHookupEvent() is called.
   */
  protected final synchronized void pauseHookupEvent(Object[] eventArgs)
  {
    Vector listenersCopy = null;
	paused = true;
	if (continuations == null)
	  continuations = new Vector();
	continuations.addElement(new Continuation(this,eventArgs));
	if (listeners != null)
	  listenersCopy = (Vector) listeners.clone();
    
	if (listeners != null)
      {
	HookupEvent hookupEvent 
	  = new HookupEvent(this, (eventArgs.length == 0 ? null : eventArgs[0]));
	int i,size = listenersCopy.size();
	for (i=0; i<size; i++)
	  ((HookupListener)listenersCopy.elementAt(i)).hookupPaused(hookupEvent);
      }
  }

  /**
   * continueHookupEvnet allows event processing for a hookup to continue.  
   * All queued events will be delivered.  The events will be delivered from
   * a different thread than the caller's.  
   */
  public final synchronized void continueHookupEvent()
  {
    if (paused)
      {
	int i,size = continuations.size();
	for (i=0 ; i<size ; i++)
	  {
	    Thread thread = new Thread((Continuation)continuations.elementAt(i));
	    thread.start();
	  }
	continuations.removeAllElements();
	paused = false;
      }
  }

  /* example of use in hookup class */
  // public void fooHappened(FooEvent e)
  // {
  //   if (debug)
  //     pauseHookupEvent(new Object[] {e});
  //   else
  //     deliverEvent(e);
  // }

  /** The deliverEvent method is specialized in subclasses
   *  of Hookup to be called from the listenerMethod
   *  or upon the resumption of a paused event.  There is a version
   *  of this method for each of up to
   */
  protected void deliverEvent(Object event)
  {

  }

  protected void deliverEvent(Object event, Object arg2)
  {

  }

  protected void deliverEvent(Object event, Object arg2, Object arg3)
  {

  }

  protected void deliverEvent(Object event, Object arg2, Object arg3, Object arg4)
  {

  }

  public static synchronized void setDebugger(HookupListener listener)
  {
    debugger = listener;
  }

  private void readObject(java.io.ObjectInputStream stream) throws
  java.lang.ClassNotFoundException, java.io.IOException,
    java.io.NotActiveException
  {
    stream.defaultReadObject();
    synchronized (Hookup.class) {
		if (debugger != null) {
			setDebug(true);
			addHookupListener(debugger);
		}
	}
  } 


}

class Continuation implements Runnable
{
  private Object[] eventArgs;
  private Hookup hookup;
  
  Continuation(Hookup hookup, Object[] eventArgs)
  {
    this.hookup = hookup;
    this.eventArgs = eventArgs;
  }
  
  @Override
  public void run()
  {
    switch (hookup.argumentCount)
      {
      case 1:
	hookup.deliverEvent(eventArgs[0]);
	break;
      case 2:
	hookup.deliverEvent(eventArgs[0], eventArgs[1]);
	break;
      case 3:
	hookup.deliverEvent(eventArgs[0], eventArgs[1], eventArgs[2]);
	break;
      case 4:
	hookup.deliverEvent(eventArgs[0], eventArgs[1],
			    eventArgs[2], eventArgs[3]);
	break;
	  default:
      }
  }
}

