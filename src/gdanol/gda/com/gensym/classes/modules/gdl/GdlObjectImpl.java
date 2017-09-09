/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlObjectImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 27 07:59:09 EDT 2000
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

public class GdlObjectImpl extends com.gensym.classes.modules.gfr.GfrObjectWithUuidImpl implements GdlObject {


  static final long serialVersionUID = 2L;
  private static final Symbol ERROR_ = Symbol.intern ("ERROR");
  private static final Symbol COMMENTS_ = Symbol.intern ("COMMENTS");

  /* Generated constructors */

  public GdlObjectImpl() {
    super();
  }

  public GdlObjectImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- ERROR
   * @param error new value to conclude for ERROR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setError(java.lang.String error) throws G2AccessException {
    setAttributeValue (ERROR_, error);
  }

  /**
   * Generated Property Getter for attribute -- ERROR
   * @return the value of the ERROR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String getError() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (ERROR_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- COMMENTS
   * @param comments new value to conclude for COMMENTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setComments(java.lang.Object comments) throws G2AccessException {
    setAttributeValue (COMMENTS_, comments);
  }

  /**
   * Generated Property Getter for attribute -- COMMENTS
   * @return the value of the COMMENTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getComments() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (COMMENTS_);
    return (java.lang.Object)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_GDL_SSE_PRESERVE_SPECIAL_ATTRIBUTE_VALUES_ = Symbol.intern ("GDL-SSE-PRESERVE-SPECIAL-ATTRIBUTE-VALUES");
  private static final Symbol MethodName_GFR_HANDLE_INVALID_UUID_ = Symbol.intern ("GFR-HANDLE-INVALID-UUID");
  private static final Symbol MethodName_GDL_RESET_ = Symbol.intern ("GDL-RESET");
  private static final Symbol MethodName_GDL_CLEAR_ERROR_ = Symbol.intern ("GDL-CLEAR-ERROR");
  private static final Symbol MethodName_GDL_REANIMATE_ = Symbol.intern ("GDL-REANIMATE");
  private static final Symbol MethodName_GDL_DEANIMATE_ = Symbol.intern ("GDL-DEANIMATE");
  private static final Symbol MethodName_GDL_INITIALIZE_ = Symbol.intern ("GDL-INITIALIZE");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * GDL-OBJECT::GDL-SSE-PRESERVE-SPECIAL-ATTRIBUTE-VALUES
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT,arg1:CLASS GDL-BLOCK) = ()
   */
  public  void gdlSsePreserveSpecialAttributeValues(com.gensym.classes.modules.gdl.GdlBlock arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_SSE_PRESERVE_SPECIAL_ATTRIBUTE_VALUES_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-OBJECT::GFR-HANDLE-INVALID-UUID
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gfrHandleInvalidUuid(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GFR_HANDLE_INVALID_UUID_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-OBJECT::GDL-RESET
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT,arg1:CLASS UI-CLIENT-ITEM) = ()
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
   * GDL-OBJECT::GDL-CLEAR-ERROR
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT) = ()
   */
  public  void gdlClearError() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_GDL_CLEAR_ERROR_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-OBJECT::GDL-REANIMATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReanimate(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_REANIMATE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-OBJECT::GDL-DEANIMATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT,arg1:CLASS UI-CLIENT-ITEM) = ()
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
   * GDL-OBJECT::GDL-INITIALIZE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlInitialize(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_INITIALIZE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
