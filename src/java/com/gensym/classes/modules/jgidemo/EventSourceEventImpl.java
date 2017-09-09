/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      EventSourceEventImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Sep 21 13:49:58 EDT 2007
 *
 */


package com.gensym.classes.modules.jgidemo;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class EventSourceEventImpl extends com.gensym.classes.modules.g2evliss.G2EventObjectImpl implements EventSourceEvent {


  static final long serialVersionUID = 2L;
  private static final Symbol MESSAGE_ = Symbol.intern ("MESSAGE");

  /* Generated constructors */

  public EventSourceEventImpl() {
    super();
  }

  public EventSourceEventImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public EventSourceEventImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- MESSAGE
   * @param message new value to conclude for MESSAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMessage(java.lang.String message) throws G2AccessException {
    setAttributeValue (MESSAGE_, message);
  }

  /**
   * Generated Property Getter for attribute -- MESSAGE
   * @return the value of the MESSAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getMessage() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (MESSAGE_);
    return (java.lang.String)retnValue;
  }

  /* com.gensym.classes.G2_EventObject support */
  @Override
  public Class getExternalEventClass() {
    return com.gensym.classes.modules.jgidemo.G2_EventSourceEvent.class;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
