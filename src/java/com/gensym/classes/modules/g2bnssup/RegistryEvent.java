/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      RegistryEvent.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 0 (H15)
 *
 *          Date: Tue Dec 01 13:36:57 EST 1998
 *
 */


package com.gensym.classes.modules.g2bnssup;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface RegistryEvent extends com.gensym.classes.modules.g2evliss.G2EventObject {

  public static final Symbol REGISTRY_EVENT_ = Symbol.intern ("REGISTRY-EVENT");
  static final Symbol g2ClassName = REGISTRY_EVENT_;
  static final Symbol[] classInheritancePath = new Symbol[] {REGISTRY_EVENT_, G2_EVENT_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- CLASS-DATA
   * @return the value of the CLASS-DATA attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CLASS-DATA is : 
   * Value
   *
   */
  public java.lang.Object getClassData() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CLASS-DATA
   * @param classData new value to conclude for CLASS-DATA
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setClassData(java.lang.Object classData) throws G2AccessException;

}
