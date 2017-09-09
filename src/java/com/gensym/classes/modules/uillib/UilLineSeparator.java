/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilLineSeparator.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:41 EDT 2007
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

public interface UilLineSeparator extends com.gensym.classes.modules.uillib.UilExtensionObject {

  public static final Symbol UIL_LINE_SEPARATOR_ = Symbol.intern ("UIL-LINE-SEPARATOR");
  static final Symbol g2ClassName = UIL_LINE_SEPARATOR_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_LINE_SEPARATOR_, UIL_EXTENSION_OBJECT_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- ORIENTATION
   * @return the value of the ORIENTATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ORIENTATION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getOrientation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ORIENTATION
   * @param orientation new value to conclude for ORIENTATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setOrientation(java.lang.Object orientation) throws G2AccessException;

}
