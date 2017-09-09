/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GrtlEventSource.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Nov 18 17:48:49 EST 2002
 *
 */


package com.gensym.classes.modules.grtl;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GrtlEventSource extends com.gensym.classes.modules.grtl.GrtlItem {

  public static final Symbol GRTL_EVENT_SOURCE_ = Symbol.intern ("GRTL-EVENT-SOURCE");
  static final Symbol g2ClassName = GRTL_EVENT_SOURCE_;
  static final Symbol[] classInheritancePath = new Symbol[] {GRTL_EVENT_SOURCE_, GRTL_ITEM_, ITEM_, SYSTEM_ITEM_, ROOT_};

  static final Symbol _LISTENERS_ = Symbol.intern ("_LISTENERS");

  static final Symbol[] staticAttributes = new Symbol[] {_LISTENERS_};


  /**
   * Generated Property Getter for attribute -- _EVENT-NOTIFICATION-ENABLED
   * @return the value of the _EVENT-NOTIFICATION-ENABLED attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _EVENT-NOTIFICATION-ENABLED is : 
   * BooleanTruthValue
   *
   */
  public boolean get_eventNotificationEnabled() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _EVENT-NOTIFICATION-ENABLED
   * @param _eventNotificationEnabled new value to conclude for _EVENT-NOTIFICATION-ENABLED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_eventNotificationEnabled(boolean _eventNotificationEnabled) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _LISTENERS
   * @return the value of the _LISTENERS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _LISTENERS is : 
   * (Structure)
   *
   */
  public com.gensym.util.Structure get_listeners() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _LISTENERS
   * @param _listeners new value to conclude for _LISTENERS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_listeners(com.gensym.util.Structure _listeners) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _LISTENERS
   * @return the value of the _LISTENERS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _LISTENERS is : 
   * (Structure)
   *
   */
  public com.gensym.util.Structure get_listenersForClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _LISTENERS
   * @param _listeners new value to conclude for _LISTENERS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_listenersForClass(com.gensym.util.Structure _listeners) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * GRTL-EVENT-SOURCE::GRTL-DISPATCH-EVENT
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GRTL-EVENT-SOURCE,arg1:SYMBOL,arg2:SEQUENCE) = ()
   */
  public  void grtlDispatchEvent(com.gensym.util.Symbol arg1,com.gensym.util.Sequence arg2) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GRTL-EVENT-SOURCE::GRTL-ADD-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GRTL-EVENT-SOURCE,arg1:ITEM-OR-VALUE,arg2:TRUTH-VALUE,arg3:TEXT,arg4:SEQUENCE) = ()
   */
  public  void grtlAddEventListener(java.lang.Object arg1,boolean arg2,java.lang.String arg3,com.gensym.util.Sequence arg4) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GRTL-EVENT-SOURCE::GRTL-REMOVE-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GRTL-EVENT-SOURCE,arg1:ITEM-OR-VALUE,arg2:TRUTH-VALUE,arg3:TEXT) = ()
   */
  public  void grtlRemoveEventListener(java.lang.Object arg1,boolean arg2,java.lang.String arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GRTL-EVENT-SOURCE::GRTL-REMOVE-ALL-EVENT-LISTENERS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GRTL-EVENT-SOURCE) = ()
   */
  public  void grtlRemoveAllEventListeners() throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GRTL-EVENT-SOURCE::GRTL-ENABLE-EVENT-NOTIFICATION
   * @return the return from calling GRTL-ENABLE-EVENT-NOTIFICATION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GRTL-EVENT-SOURCE) = (TRUTH-VALUE)
   */
  public  boolean grtlEnableEventNotification() throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GRTL-EVENT-SOURCE::GRTL-DISABLE-EVENT-NOTIFICATION
   * @return the return from calling GRTL-DISABLE-EVENT-NOTIFICATION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GRTL-EVENT-SOURCE) = (TRUTH-VALUE)
   */
  public  boolean grtlDisableEventNotification() throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GRTL-EVENT-SOURCE::GRTL-IS-EVENT-NOTIFICATION-ENABLED
   * @return the return from calling GRTL-IS-EVENT-NOTIFICATION-ENABLED
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GRTL-EVENT-SOURCE) = (TRUTH-VALUE)
   */
  public  boolean grtlIsEventNotificationEnabled() throws G2AccessException;
  
}
