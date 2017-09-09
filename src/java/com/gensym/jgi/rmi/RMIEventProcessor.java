package com.gensym.jgi.rmi;

import java.util.*;

import com.gensym.util.*;
import com.gensym.message.*;

/** This is the currently used processing mechanism. It is simpler,
 * but does not guarantee that events will be processed in the same
 * order as they are received, as a new Thread is started for each
 * set of events, making it possible for these Threads to achieve
 * a race condition.
 * @deprecated */
public class RMIEventProcessor implements Runnable {
  private static MessageKey messageKey =
  Trace.registerMessageKey("com.gensym.rmi", "com.gensym.rmi.TwRMIClientImpl");
  private static Resource i18n = Trace.getBundle("com.gensym.rmi.Messages",
						 Locale.getDefault());

  private RMIPollingClient client;
  private Vector events;

  public RMIEventProcessor(RMIPollingClient client, Vector events) {
    this.client = client;
    this.events = events;
  }

  @Override
  public void run() {
    if (events == null)
      return;
    for (Enumeration en = events.elements(); en.hasMoreElements();) {
      EventObject event = (EventObject)en.nextElement();
      
      try {
	client.processEvent(event);
      } catch (Exception ex) {
	Trace.exception(ex, null);
      }
    }
  }
}
