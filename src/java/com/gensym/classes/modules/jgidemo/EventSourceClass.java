/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      EventSourceClass.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Sep 21 13:49:55 EDT 2007
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

public interface EventSourceClass extends com.gensym.classes.modules.jgidemo.GenericREmployee, com.gensym.classes.modules.g2evliss.G2EventListenerSupport {

  public static final Symbol EVENT_SOURCE_CLASS_ = Symbol.intern ("EVENT-SOURCE-CLASS");
  static final Symbol g2ClassName = EVENT_SOURCE_CLASS_;
  static final Symbol[] classInheritancePath = new Symbol[] {EVENT_SOURCE_CLASS_, GENERIC_R_EMPLOYEE_, R_EMPLOYEE_, REPOSITORY_OBJECT_, GENERIC_R_OBJECT_, G2_EVENT_LISTENER_SUPPORT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Auto Generated method for G2 Method
   * EVENT-SOURCE-CLASS::ADD-EVENT-SOURCE-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS EVENT-SOURCE-CLASS,arg1:CLASS EVENT-SOURCE-LISTENER) = ()
   */
  public  void addEventSourceListener(com.gensym.classes.modules.jgidemo.EventSourceListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * EVENT-SOURCE-CLASS::ADD-EVENT-SOURCE-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS EVENT-SOURCE-CLASS,arg1:CLASS EVENT-SOURCE-LISTENER) = ()
   */
  public  void addG2_EventSourceListener(G2_EventSourceListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * EVENT-SOURCE-CLASS::REMOVE-EVENT-SOURCE-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS EVENT-SOURCE-CLASS,arg1:CLASS EVENT-SOURCE-LISTENER) = ()
   */
  public  void removeEventSourceListener(com.gensym.classes.modules.jgidemo.EventSourceListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * EVENT-SOURCE-CLASS::REMOVE-EVENT-SOURCE-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS EVENT-SOURCE-CLASS,arg1:CLASS EVENT-SOURCE-LISTENER) = ()
   */
  public  void removeG2_EventSourceListener(G2_EventSourceListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * EVENT-SOURCE-CLASS::FIRE-AN-EVENT
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS EVENT-SOURCE-CLASS,arg1:TEXT) = ()
   */
  public  void fireAnEvent(java.lang.String arg1) throws G2AccessException;
  
}
