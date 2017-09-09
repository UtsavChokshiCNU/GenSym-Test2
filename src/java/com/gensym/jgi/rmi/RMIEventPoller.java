package com.gensym.jgi.rmi;

import java.util.*;

import com.gensym.util.*;
import com.gensym.message.*;

/** NOTE: This polling loop is designed to keep event order consistent.
 * The way it does this is by running in a single loop, not starting a
 * a new thread to collect new events. As a result, it is possible for
 * it to "run behind". When that happens, warnings will be issued.
 */
public class RMIEventPoller implements Runnable {
  private G2RMIAccess server;
  private RMIPollingClient client;
  volatile long pollingWait;

  public RMIEventPoller(G2RMIAccess server, RMIPollingClient client,
		 long pollingWait) {
    this.server = server;
    this.client = client;
    this.pollingWait = pollingWait;
  }

  void setPollingWait(long newPollingWait) {
    pollingWait = newPollingWait;
  }

  @Override
  public void run() {
    //    G2RMIClientImpl.enableNetscapeSecurity();
    while (true) {
      long before = System.currentTimeMillis();
      long nextTime = before + pollingWait;
      try {
	// slow
	Vector newEvents = client.getEvents();
	// quick
	client.processEvents(newEvents);
	//      } catch (RemoteException re) {
	//	client.handleException(re);
      } catch (Exception e) {
	Trace.exception(e, null);
      }
      
      long now;
      
      while((now = System.currentTimeMillis()) < nextTime) {
	try {
	  Thread.sleep(nextTime - now);
	} catch (InterruptedException ie) {
	}
      }
    }
  }
}

/** This is not currently used. The purpose of this implementation
 * is to guarantee to race condition in event processing. Events
 * will be processed in the order in which they were received. However,
 * it is possible for this single-threaded technique to fall behind the
 * events. */
class RMIEventProcessor1 implements Runnable {
  private RMIPollingClient client;

  RMIEventProcessor1(RMIPollingClient client) {
    this.client = client;
  }

  @Override
  public void run() {
    Vector eventCollection = null;
    synchronized(client) {
      while (true) {
	while ((eventCollection = client.getEvents()) == null) {
	  try {
	    wait();
	  } catch (InterruptedException ie) {
	  }
	}
	processEventCollection(eventCollection);
      }
    }
  }

  private void processEventCollection(Vector eventCollection) {
  }
}
