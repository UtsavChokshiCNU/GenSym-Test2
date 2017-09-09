/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      RemoteQueueEventImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 13 11:45:48 EDT 2000
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

public class RemoteQueueEventImpl extends com.gensym.classes.modules.g2evliss.G2EventObjectImpl implements RemoteQueueEvent {


  static final long serialVersionUID = 2L;
  private static final Symbol REMOTE_QUEUE_EVENT_DATA_ = Symbol.intern ("REMOTE-QUEUE-EVENT-DATA");

  /* Generated constructors */

  public RemoteQueueEventImpl() {
    super();
  }

  public RemoteQueueEventImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- REMOTE-QUEUE-EVENT-DATA
   * @param remoteQueueEventData new value to conclude for REMOTE-QUEUE-EVENT-DATA
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRemoteQueueEventData(com.gensym.util.Structure remoteQueueEventData) throws G2AccessException {
    setAttributeValue (REMOTE_QUEUE_EVENT_DATA_, remoteQueueEventData);
  }

  /**
   * Generated Property Getter for attribute -- REMOTE-QUEUE-EVENT-DATA
   * @return the value of the REMOTE-QUEUE-EVENT-DATA attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Structure getRemoteQueueEventData() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (REMOTE_QUEUE_EVENT_DATA_);
    return (com.gensym.util.Structure)retnValue;
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

  /* com.gensym.classes.G2_EventObject support */
  public Class getExternalEventClass() {
    return com.gensym.classes.modules.grl.G2_RemoteQueueEvent.class;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
