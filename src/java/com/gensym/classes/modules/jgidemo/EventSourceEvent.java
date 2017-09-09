/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      EventSourceEvent.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Sep 21 13:49:51 EDT 2007
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

public interface EventSourceEvent extends com.gensym.classes.modules.g2evliss.G2EventObject {

  public static final Symbol EVENT_SOURCE_EVENT_ = Symbol.intern ("EVENT-SOURCE-EVENT");
  static final Symbol g2ClassName = EVENT_SOURCE_EVENT_;
  static final Symbol[] classInheritancePath = new Symbol[] {EVENT_SOURCE_EVENT_, G2_EVENT_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- MESSAGE
   * @return the value of the MESSAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MESSAGE is : 
   * Text
   *
   */
  public java.lang.String getMessage() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MESSAGE
   * @param message new value to conclude for MESSAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMessage(java.lang.String message) throws G2AccessException;

}
