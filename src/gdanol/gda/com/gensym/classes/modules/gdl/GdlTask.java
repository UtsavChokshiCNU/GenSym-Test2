/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlTask.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Jun 26 18:45:40 EDT 2000
 *
 */


package com.gensym.classes.modules.gdl;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GdlTask extends com.gensym.classes.modules.gdl.GdlTaskOrEvent {

  public static final Symbol GDL_TASK_ = Symbol.intern ("GDL-TASK");
  static final Symbol g2ClassName = GDL_TASK_;
  static final Symbol[] classInheritancePath = new Symbol[] {GDL_TASK_, GDL_TASK_OR_EVENT_, GDL_OBJECT_, GFR_OBJECT_WITH_UUID_, OBJECT_, GFR_ITEM_WITH_UUID_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- ENCAPSULATION-ID
   * @return the value of the ENCAPSULATION-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ENCAPSULATION-ID is : 
   * Text
   *
   */
  public java.lang.String getEncapsulationId() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ENCAPSULATION-ID
   * @param encapsulationId new value to conclude for ENCAPSULATION-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEncapsulationId(java.lang.String encapsulationId) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INVOCATIONS-WAITING
   * @return the value of the INVOCATIONS-WAITING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INVOCATIONS-WAITING is : 
   * Integer
   *
   */
  public int getInvocationsWaiting() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INVOCATIONS-WAITING
   * @param invocationsWaiting new value to conclude for INVOCATIONS-WAITING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInvocationsWaiting(int invocationsWaiting) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- LOCAL-TASK-INDEX
   * @return the value of the LOCAL-TASK-INDEX attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LOCAL-TASK-INDEX is : 
   * Integer
   *
   */
  public int getLocalTaskIndex() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LOCAL-TASK-INDEX
   * @param localTaskIndex new value to conclude for LOCAL-TASK-INDEX
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLocalTaskIndex(int localTaskIndex) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FEEDFORWARD-INDEX
   * @return the value of the FEEDFORWARD-INDEX attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FEEDFORWARD-INDEX is : 
   * Integer
   *
   */
  public int getFeedforwardIndex() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FEEDFORWARD-INDEX
   * @param feedforwardIndex new value to conclude for FEEDFORWARD-INDEX
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFeedforwardIndex(int feedforwardIndex) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- OP-CODE
   * @return the value of the OP-CODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for OP-CODE is : 
   * Integer
   *
   */
  public int getOpCode() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- OP-CODE
   * @param opCode new value to conclude for OP-CODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setOpCode(int opCode) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ATTACHED-CAPABILITIES
   * @return the value of the ATTACHED-CAPABILITIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ATTACHED-CAPABILITIES is : 
   * BooleanTruthValue
   *
   */
  public boolean getAttachedCapabilities() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ATTACHED-CAPABILITIES
   * @param attachedCapabilities new value to conclude for ATTACHED-CAPABILITIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAttachedCapabilities(boolean attachedCapabilities) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ANIMATE
   * @return the value of the ANIMATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ANIMATE is : 
   * BooleanTruthValue
   *
   */
  public boolean getAnimate() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ANIMATE
   * @param animate new value to conclude for ANIMATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAnimate(boolean animate) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- STATUS
   * @return the value of the STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for STATUS is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getStatus() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- STATUS
   * @param status new value to conclude for STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStatus(com.gensym.util.Symbol status) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * GDL-TASK::_GDL-GENERIC-EVALUATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-TASK,arg1:SYMBOL,arg2:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void _gdlGenericEvaluate(com.gensym.util.Symbol arg1,com.gensym.classes.UiClientItem arg2) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-TASK::GDL-RESET
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-TASK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReset(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-TASK::GDL-DEANIMATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-TASK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlDeanimate(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-TASK::GDL-ENABLE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-TASK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlEnable(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-TASK::GDL-DISABLE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-TASK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlDisable(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
}
