/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      RemoteQueueEventListenerImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 13 11:45:54 EDT 2000
 *
 */


package com.gensym.classes.modules.grl;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class RemoteQueueEventListenerImpl extends com.gensym.classes.modules.g2evliss.G2EventListenerImpl implements RemoteQueueEventListener {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public RemoteQueueEventListenerImpl() {
    super();
  }

  public RemoteQueueEventListenerImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-DISPLAYS
   * @param attributeDisplays new value to conclude for ATTRIBUTE-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAttributeDisplaysForClass(java.lang.Object attributeDisplays) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_DISPLAYS_, attributeDisplays);
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-DISPLAYS
   * @return the value of the ATTRIBUTE-DISPLAYS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getAttributeDisplaysForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_DISPLAYS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- STUBS
   * @param stubs new value to conclude for STUBS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStubsForClass(java.lang.Object stubs) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.STUBS_, stubs);
  }

  /**
   * Generated Property Getter for attribute -- STUBS
   * @return the value of the STUBS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getStubsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.STUBS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-SETTINGS
   * @return the value of the DEFAULT-SETTINGS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getDefaultSettingsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.DEFAULT_SETTINGS_);
    return (java.lang.Object)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_QUEUE_ITEMS_ADDED_ = Symbol.intern ("QUEUE-ITEMS-ADDED");
  private static final Symbol MethodName_QUEUE_ITEMS_REMOVED_ = Symbol.intern ("QUEUE-ITEMS-REMOVED");
  private static final Symbol MethodName_QUEUE_ITEMS_ATTRIBUTE_CHANGED_ = Symbol.intern ("QUEUE-ITEMS-ATTRIBUTE-CHANGED");
  private static final Symbol MethodName_QUEUE_RECEIVED_INITIAL_STATE_ = Symbol.intern ("QUEUE-RECEIVED-INITIAL-STATE");
  private static final Symbol MethodName_QUEUE_INVALIDATE_STATE_ = Symbol.intern ("QUEUE-INVALIDATE-STATE");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-LISTENER::QUEUE-ITEMS-ADDED
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-LISTENER,arg1:CLASS REMOTE-QUEUE-EVENT) = ()
   */
  public  void queueItemsAdded(com.gensym.classes.modules.grl.RemoteQueueEvent arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_QUEUE_ITEMS_ADDED_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-LISTENER::QUEUE-ITEMS-REMOVED
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-LISTENER,arg1:CLASS REMOTE-QUEUE-EVENT) = ()
   */
  public  void queueItemsRemoved(com.gensym.classes.modules.grl.RemoteQueueEvent arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_QUEUE_ITEMS_REMOVED_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-LISTENER::QUEUE-ITEMS-ATTRIBUTE-CHANGED
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-LISTENER,arg1:CLASS REMOTE-QUEUE-EVENT) = ()
   */
  public  void queueItemsAttributeChanged(com.gensym.classes.modules.grl.RemoteQueueEvent arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_QUEUE_ITEMS_ATTRIBUTE_CHANGED_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-LISTENER::QUEUE-RECEIVED-INITIAL-STATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-LISTENER,arg1:CLASS REMOTE-QUEUE-EVENT) = ()
   */
  public  void queueReceivedInitialState(com.gensym.classes.modules.grl.RemoteQueueEvent arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_QUEUE_RECEIVED_INITIAL_STATE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-LISTENER::QUEUE-INVALIDATE-STATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-LISTENER,arg1:CLASS REMOTE-QUEUE-EVENT) = ()
   */
  public  void queueInvalidateState(com.gensym.classes.modules.grl.RemoteQueueEvent arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_QUEUE_INVALIDATE_STATE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
