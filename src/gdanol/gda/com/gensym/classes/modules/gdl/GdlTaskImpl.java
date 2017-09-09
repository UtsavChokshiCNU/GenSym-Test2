/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlTaskImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 27 07:59:13 EDT 2000
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

public class GdlTaskImpl extends com.gensym.classes.modules.gdl.GdlTaskOrEventImpl implements GdlTask {


  static final long serialVersionUID = 2L;
  private static final Symbol ENCAPSULATION_ID_ = Symbol.intern ("ENCAPSULATION-ID");
  private static final Symbol INVOCATIONS_WAITING_ = Symbol.intern ("INVOCATIONS-WAITING");
  private static final Symbol LOCAL_TASK_INDEX_ = Symbol.intern ("LOCAL-TASK-INDEX");
  private static final Symbol FEEDFORWARD_INDEX_ = Symbol.intern ("FEEDFORWARD-INDEX");
  private static final Symbol OP_CODE_ = Symbol.intern ("OP-CODE");
  private static final Symbol ATTACHED_CAPABILITIES_ = Symbol.intern ("ATTACHED-CAPABILITIES");
  private static final Symbol ANIMATE_ = Symbol.intern ("ANIMATE");
  private static final Symbol STATUS_ = Symbol.intern ("STATUS");

  /* Generated constructors */

  public GdlTaskImpl() {
    super();
  }

  public GdlTaskImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- ENCAPSULATION-ID
   * @param encapsulationId new value to conclude for ENCAPSULATION-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEncapsulationId(java.lang.String encapsulationId) throws G2AccessException {
    setAttributeValue (ENCAPSULATION_ID_, encapsulationId);
  }

  /**
   * Generated Property Getter for attribute -- ENCAPSULATION-ID
   * @return the value of the ENCAPSULATION-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String getEncapsulationId() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (ENCAPSULATION_ID_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- INVOCATIONS-WAITING
   * @param invocationsWaiting new value to conclude for INVOCATIONS-WAITING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInvocationsWaiting(int invocationsWaiting) throws G2AccessException {
    setAttributeValue (INVOCATIONS_WAITING_, new Integer (invocationsWaiting));
  }

  /**
   * Generated Property Getter for attribute -- INVOCATIONS-WAITING
   * @return the value of the INVOCATIONS-WAITING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getInvocationsWaiting() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (INVOCATIONS_WAITING_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- LOCAL-TASK-INDEX
   * @param localTaskIndex new value to conclude for LOCAL-TASK-INDEX
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLocalTaskIndex(int localTaskIndex) throws G2AccessException {
    setAttributeValue (LOCAL_TASK_INDEX_, new Integer (localTaskIndex));
  }

  /**
   * Generated Property Getter for attribute -- LOCAL-TASK-INDEX
   * @return the value of the LOCAL-TASK-INDEX attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getLocalTaskIndex() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (LOCAL_TASK_INDEX_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- FEEDFORWARD-INDEX
   * @param feedforwardIndex new value to conclude for FEEDFORWARD-INDEX
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFeedforwardIndex(int feedforwardIndex) throws G2AccessException {
    setAttributeValue (FEEDFORWARD_INDEX_, new Integer (feedforwardIndex));
  }

  /**
   * Generated Property Getter for attribute -- FEEDFORWARD-INDEX
   * @return the value of the FEEDFORWARD-INDEX attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getFeedforwardIndex() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (FEEDFORWARD_INDEX_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- OP-CODE
   * @param opCode new value to conclude for OP-CODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setOpCode(int opCode) throws G2AccessException {
    setAttributeValue (OP_CODE_, new Integer (opCode));
  }

  /**
   * Generated Property Getter for attribute -- OP-CODE
   * @return the value of the OP-CODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getOpCode() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (OP_CODE_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- ATTACHED-CAPABILITIES
   * @param attachedCapabilities new value to conclude for ATTACHED-CAPABILITIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAttachedCapabilities(boolean attachedCapabilities) throws G2AccessException {
    setAttributeValue (ATTACHED_CAPABILITIES_, new Boolean (attachedCapabilities));
  }

  /**
   * Generated Property Getter for attribute -- ATTACHED-CAPABILITIES
   * @return the value of the ATTACHED-CAPABILITIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getAttachedCapabilities() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (ATTACHED_CAPABILITIES_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- ANIMATE
   * @param animate new value to conclude for ANIMATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAnimate(boolean animate) throws G2AccessException {
    setAttributeValue (ANIMATE_, new Boolean (animate));
  }

  /**
   * Generated Property Getter for attribute -- ANIMATE
   * @return the value of the ANIMATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getAnimate() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (ANIMATE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- STATUS
   * @param status new value to conclude for STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStatus(com.gensym.util.Symbol status) throws G2AccessException {
    setAttributeValue (STATUS_, status);
  }

  /**
   * Generated Property Getter for attribute -- STATUS
   * @return the value of the STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (STATUS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName__GDL_GENERIC_EVALUATE_ = Symbol.intern ("_GDL-GENERIC-EVALUATE");
  private static final Symbol MethodName_GDL_RESET_ = Symbol.intern ("GDL-RESET");
  private static final Symbol MethodName_GDL_DEANIMATE_ = Symbol.intern ("GDL-DEANIMATE");
  private static final Symbol MethodName_GDL_ENABLE_ = Symbol.intern ("GDL-ENABLE");
  private static final Symbol MethodName_GDL_DISABLE_ = Symbol.intern ("GDL-DISABLE");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * GDL-TASK::_GDL-GENERIC-EVALUATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-TASK,arg1:SYMBOL,arg2:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void _gdlGenericEvaluate(com.gensym.util.Symbol arg1,com.gensym.classes.UiClientItem arg2) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
      result = (java.lang.Object)callRPC(MethodName__GDL_GENERIC_EVALUATE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-TASK::GDL-RESET
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-TASK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReset(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_RESET_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-TASK::GDL-DEANIMATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-TASK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlDeanimate(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_DEANIMATE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-TASK::GDL-ENABLE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-TASK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlEnable(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_ENABLE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-TASK::GDL-DISABLE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-TASK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlDisable(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_DISABLE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
