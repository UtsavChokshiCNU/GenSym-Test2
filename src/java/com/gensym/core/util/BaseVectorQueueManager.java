/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   VectorQueueManager.java 
 * 
 * 
 */ 
  
package com.gensym.core.util;

import java.util.Vector;
import java.util.EventObject;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;

/** A class that accumulates events, then processes them in groups.
 * Is useful in cases where some efficiency can be derived in the
 * processing of events in groups rather than one-at-a-time.
 */
public abstract class BaseVectorQueueManager extends Thread {

  private static MessageKey traceKey =
  Trace.registerMessageKey ("com.gensym.util.queue",
			    BaseVectorQueueManager.class);
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.core.util.TraceMessages");
  // can probably use the queue as the queueLock, as there
  // seems to be no need to actually expose the lock.
  protected final Object queueLock = new Object();

  private final Vector queue = new Vector();

  protected volatile boolean running;

  /** Queues up a new event for the QueueManager.
   * This method obtains the queueLock.
   */
  public void addEvent(EventObject event) {
    Trace.send(30, traceKey, i18nTrace, "vqmaddEvent", this, event);
    synchronized (queueLock) {
      queue.addElement(event);
      queueLock.notifyAll();
    }
  }

  /**
    * Returns the number of events currently waiting in the queue
    */
  public int getEventCount()
  {
    synchronized (queueLock) {
      return queue.size();
    }
  }

  public void setRunning(boolean newState) {
    running = newState;
    synchronized (queueLock) {
      queueLock.notifyAll();
    }
  }

  /** Waits for events to be added to the queue by addEvent, copies the
   * queue, clears it out, then processes the queue copy.
   * This method obtains the queueLock and waits on it.
   */
  @Override
  public void run() {
    Vector queueCopy = null;
    running = true;

    while (running) {
      Trace.send(30, traceKey, i18nTrace, "vqmrun1", this,
		 new Boolean(running));
      synchronized (queueLock) {
	Trace.send(30, traceKey, i18nTrace, "vqmrun2", this, queue);
	if (queue.isEmpty()) {
	  queueCopy = null;
	  try {
	    Trace.send(30, traceKey, i18nTrace, "vqmrun3", this);
	    queueLock.wait();
	    Trace.send(30, traceKey, i18nTrace, "vqmrun4", this);
	  } catch (InterruptedException ie) {
	    Trace.send(30, traceKey, i18nTrace, "vqmrun5", this);
	    running = false;
	    // fix this: should have a client queue monitor
	    // hook here that allows us to notify someone that
	    // we are stopping.
	    // should I drop out of everything right here?
	    // probably, as somebody has politely asked this
	    // thread to stop.
	    unsubscribeAll();
	    return;
	  }
	} else {
	  Trace.send(30, traceKey, i18nTrace, "vqmrun6", this);
	  queueCopy = drainQueue(true);
	  // oops: this seems to be called twice for no good reason
	  // that I can see.
	  queue.removeAllElements();
	}
      }

      // "bug": this should be isEmpty(), but we would never get to
      // here if it was either empty or "null"
      if (queueCopy != null) {
	try {
	  Trace.send(30, traceKey, i18nTrace, "vqmrun7", this);
	  processQueue(queueCopy);
	} catch (Exception ex) {
	  Trace.send(30, traceKey, i18nTrace, "vqmrun8", this);
	  Trace.exception(ex);
	}
      }
      Trace.send(30, traceKey, i18nTrace, "vqmrun9", this,
		 new Boolean(running));
    }
    Trace.send(30, traceKey, i18nTrace, "vqmrun10", this);
  }

  /** Returns the current contents of the queue and drains the queue.
   * Also stops the automatic queue-draining.
   */
  public Vector drainQueue(boolean keepRunning) {
    synchronized (queueLock) {
      running = keepRunning;
      Vector queueCopy = (Vector)queue.clone(); //shallow clone
      Trace.send(30, traceKey, i18nTrace, "vqmdrainQueue", this, queue);
      queue.removeAllElements();
      return queueCopy;
    }
  }

  /** Tell all your event sources that you are no longer listening.
   */
  protected abstract void unsubscribeAll();

  /** It is may not be necessary that this method be synchronized,
   * but if it is, it should not be not synchronized
   * on the queueLock. Is called by run() whenever events have been added to
   * the queue.
   */
  protected abstract void processQueue(Vector queueCopy);
}
	
