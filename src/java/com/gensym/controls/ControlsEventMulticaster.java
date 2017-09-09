/*
 * @(#)ControlsEventMulticaster.java	1.0 98/02/25
 * 
 * Copyright (c) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 
 */
package com.gensym.controls;

import java.util.EventListener;
import java.io.Serializable;
import java.io.ObjectOutputStream;
import java.io.IOException;

/**
 * A class which implements efficient and thread-safe multi-cast event 
 * dispatching for events defined in the com.gensym.util package.
 * This class will manage an immutable structure consisting of a chain of 
 * event listeners and will dispatch events to those listeners.  Because
 * the structure is immutable, it is safe to use this API to add/remove
 * listeners during the process of an event dispatch operation.
 *
 * @version 	1.00, 10/22/97
 * @author      vkp
 */

class ControlsEventMulticaster implements Serializable, EventListener, ItemRetrievalListener {

  static final long serialVersioUID = 6560771083612673685L;
  protected final EventListener a, b;

    /**
     * Creates an event multicaster instance which chains listener-a
     * with listener-b.
     * @param a listener-a
     * @param b listener-b
     */ 
  ControlsEventMulticaster(EventListener a, EventListener b) {
    this.a = a; this.b = b;
  }

    /**
     * Removes a listener from this multicaster and returns the
     * resulting multicast listener.
     * @param oldl the listener to be removed
     */
  EventListener remove(EventListener oldl) {
    if (oldl == a)  return b;
    if (oldl == b)  return a;
    EventListener a2 = removeInternal(a, oldl);
    EventListener b2 = removeInternal(b, oldl);
    if (a2 == a && b2 == b) {
      return this;	// it's not here
    }
    return addInternal(a2, b2);
  }

    /** 
     * Returns the resulting multicast listener from adding listener-a
     * and listener-b together.  
     * If listener-a is null, it returns listener-b;  
     * If listener-b is null, it returns listener-a
     * If neither are null, then it creates and returns
     * a new ControlsEventMulticaster instance which chains a with b.
     * @param a event listener-a
     * @param b event listener-b
     */
  static EventListener addInternal(EventListener a, EventListener b) {
    if (a == null)  return b;
    if (b == null)  return a;
    return new ControlsEventMulticaster(a, b);
  }

    /** 
     * Returns the resulting multicast listener after removing the
     * old listener from listener-l.
     * If listener-l equals the old listener OR listener-l is null, 
     * returns null.
     * Else if listener-l is an instance of ControlsEventMulticaster, 
     * then it removes the old listener from it.
     * Else, returns listener l.
     * @param l the listener being removed from
     * @param oldl the listener being removed
     */
  static EventListener removeInternal(EventListener l, EventListener oldl) {
    if (l == oldl || l == null) {
      return null;
    } else if (l instanceof ControlsEventMulticaster) {
      return ((ControlsEventMulticaster)l).remove(oldl);
    } else {
      return l;		// it's not here
    }
  }
      

    /*
     * Serialization support.  Huh? -vkp, 10/22/97
     */

  protected void saveInternal(ObjectOutputStream s, String k) throws IOException {
    if (a instanceof ControlsEventMulticaster) {
      ((ControlsEventMulticaster)a).saveInternal(s, k);
    }
    else if (a instanceof Serializable) {
      s.writeObject(k);
      s.writeObject(a);
    }
        
    if (b instanceof ControlsEventMulticaster) {
      ((ControlsEventMulticaster)b).saveInternal(s, k);
    }
    else if (b instanceof Serializable) {
      s.writeObject(k);
      s.writeObject(b);
    }
  }

  protected static void save(ObjectOutputStream s, String k, EventListener l) throws IOException {
    if (l == null) {
      return;
    } 
    else if (l instanceof ControlsEventMulticaster) {
      ((ControlsEventMulticaster)l).saveInternal(s, k);
    }
    else if (l instanceof Serializable) {
      s.writeObject(k);
      s.writeObject(l);
    }
  }

    /**
     * Adds item-retrieval-listener-a with item-retrieval-listener-b and returns
     * the resulting multicast listener.
     * @param a item-retrieval-listener-a
     * @param b item-retrieval-listener-b
     */
  static ItemRetrievalListener add (ItemRetrievalListener a, ItemRetrievalListener b) {
    return (ItemRetrievalListener) addInternal (a, b);
  }
     
    /**
     * Removes the old item-retrieval-listener from item-retrieval-listener-list and
     * returns the resulting multicast listener.
     * @param l item-retrieval-listener-l
     * @param old-l the item-retrieval-listener being removed
     */
  static ItemRetrievalListener remove (ItemRetrievalListener l, ItemRetrievalListener oldl) {
    return (ItemRetrievalListener) removeInternal (l, oldl);
  }

    /**
     * Handles the itemRetrieved event by invoking itemRetrieved on
     * listener-a and listener-b.
     * @param e the ItemRetrievalEvent.
     */
  @Override
  public void itemRetrieved(ItemRetrievalEvent e) {
    ((ItemRetrievalListener)a).itemRetrieved(e);
    ((ItemRetrievalListener)b).itemRetrieved(e);
  }

    /**
     * Handles the itemRetrievalFailed event by invoking itemRetrievalFailed on
     * listener-a and listener-b.
     * @param e the ItemRetrievalEvent.
     */
  @Override
  public void itemRetrievalFailed(ItemRetrievalEvent e) {
    ((ItemRetrievalListener)a).itemRetrievalFailed(e);
    ((ItemRetrievalListener)b).itemRetrievalFailed(e);
  }
}
