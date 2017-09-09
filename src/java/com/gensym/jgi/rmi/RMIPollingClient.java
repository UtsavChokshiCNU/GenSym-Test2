package com.gensym.jgi.rmi;

import java.util.Vector;
import java.util.EventObject;

import com.gensym.jgi.G2CallbacksException;

public interface RMIPollingClient {
  public void processEvents (Vector newEvents);
  public void processEvent (EventObject event) throws G2CallbacksException;
  public Vector getEvents ();
}
