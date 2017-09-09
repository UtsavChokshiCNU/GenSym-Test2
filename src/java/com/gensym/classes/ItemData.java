/*
 * @(#)ItemData.java	1.0 97/11/05
 * 
 * Copyright (c) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 
 */
package com.gensym.classes;

import java.util.Hashtable;
import java.util.Vector;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.SubscriptionManager;

/**
 * A package private class that is used to hold the data in a G2
 * ItemImpl stub. This facilitates 3-tier operation where a number
 * of copies of the stub may be created by deserialization. The
 * data for the item is held in a ItemData kept in a hashtable.
 * All variables are volatile, as the object represents the data for
 * multiple "instances" of what is essentially the same object.
 * <p>
 * There would be little or no need for this class if
 * <code>resolveObject()</code> could be called when passing
 * <code>Items</code> during RMI calls.
 * @version    1.00 11/05/97
 * @author     vkp
 */
public class ItemData {
  volatile SubscriptionManager subscriptionManager;

  /**
   * @deprecated
   */
  volatile Structure attributes;

  /**
   * @deprecated
   */
  volatile boolean workspaceCurrentlySubscribed;
  /**
   * @deprecated
   */
  volatile boolean fullyInitialized;
  /**
   * @deprecated
   */
  volatile int listenerCount;
  /**
   * @deprecated
   */
  int referenceCount = 0;
  /**
   * @deprecated
   */
  int handleVersion = 0;

  // fix this: should really find a better
  // place to set this to true
  boolean itemIsValid = true;


//   // for now the WILDCARD_DENOTATION
//   // involved in addItemListener is handled separately
//   Hashtable denotation2HandleMap;

//   Hashtable handle2ListenerMap;

  void setAttributes (Structure newAttributes) {
    attributes = newAttributes;
  }
  @Override
  public String toString () {
    return super.toString () + "(v" + handleVersion+":"+ (itemIsValid ? "valid" : "invalid")+")";
  }
  /**
   * Is an object becuase "null" is a possible value, indicating
   * that the state is undetermined.
   */
  Boolean itemIsProprietaryThroughContainment;

  KbWorkspace parentWorkspace;

  // the following two slots are for caching workspace
  // snapshots of the corresponding value, and are not
  // intended for use outside of KbWorkspaceImpl
  Sequence wsSnapshotOfConfiguration;

  Symbol wsSnapshotOfConnectionStyle;

  G2Definition definition;

  Vector invalidationListeners;

}
