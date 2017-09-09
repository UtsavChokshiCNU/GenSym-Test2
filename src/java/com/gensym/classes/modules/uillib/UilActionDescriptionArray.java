/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilActionDescriptionArray.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:41 EDT 2007
 *
 */


package com.gensym.classes.modules.uillib;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface UilActionDescriptionArray extends com.gensym.classes.modules.uilroot.UilObject {

  public static final Symbol UIL_ACTION_DESCRIPTION_ARRAY_ = Symbol.intern ("UIL-ACTION-DESCRIPTION-ARRAY");
  static final Symbol g2ClassName = UIL_ACTION_DESCRIPTION_ARRAY_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_ACTION_DESCRIPTION_ARRAY_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-ACTION-SPECIFICS
   * @return the value of the UIL-ACTION-SPECIFICS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ACTION-SPECIFICS is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilActionSpecifics() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ACTION-SPECIFICS
   * @param uilActionSpecifics new value to conclude for UIL-ACTION-SPECIFICS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilActionSpecifics(java.lang.Object uilActionSpecifics) throws G2AccessException;

}
