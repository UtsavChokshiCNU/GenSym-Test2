/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlObject.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Jun 26 18:45:46 EDT 2000
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

public interface GdlObject extends com.gensym.classes.modules.gfr.GfrObjectWithUuid {

  public static final Symbol GDL_OBJECT_ = Symbol.intern ("GDL-OBJECT");
  static final Symbol g2ClassName = GDL_OBJECT_;
  static final Symbol[] classInheritancePath = new Symbol[] {GDL_OBJECT_, GFR_OBJECT_WITH_UUID_, OBJECT_, GFR_ITEM_WITH_UUID_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- ERROR
   * @return the value of the ERROR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ERROR is : 
   * Text
   *
   */
  public java.lang.String getError() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ERROR
   * @param error new value to conclude for ERROR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setError(java.lang.String error) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- COMMENTS
   * @return the value of the COMMENTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for COMMENTS is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getComments() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- COMMENTS
   * @param comments new value to conclude for COMMENTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setComments(java.lang.Object comments) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * GDL-OBJECT::GDL-SSE-PRESERVE-SPECIAL-ATTRIBUTE-VALUES
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT,arg1:CLASS GDL-BLOCK) = ()
   */
  public  void gdlSsePreserveSpecialAttributeValues(com.gensym.classes.modules.gdl.GdlBlock arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-OBJECT::GFR-HANDLE-INVALID-UUID
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gfrHandleInvalidUuid(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-OBJECT::GDL-RESET
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReset(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-OBJECT::GDL-CLEAR-ERROR
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT) = ()
   */
  public  void gdlClearError() throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-OBJECT::GDL-REANIMATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReanimate(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-OBJECT::GDL-DEANIMATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlDeanimate(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-OBJECT::GDL-INITIALIZE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlInitialize(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
}
