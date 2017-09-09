/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilExtensionObject.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:28 EDT 2007
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

public interface UilExtensionObject extends com.gensym.classes.modules.uilroot.UilGrobj {

  public static final Symbol UIL_EXTENSION_OBJECT_ = Symbol.intern ("UIL-EXTENSION-OBJECT");
  static final Symbol g2ClassName = UIL_EXTENSION_OBJECT_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_EXTENSION_OBJECT_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-HAS-BEEN-CLONED
   * @return the value of the UIL-HAS-BEEN-CLONED attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-HAS-BEEN-CLONED is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilHasBeenCloned() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-HAS-BEEN-CLONED
   * @param uilHasBeenCloned new value to conclude for UIL-HAS-BEEN-CLONED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilHasBeenCloned(java.lang.Object uilHasBeenCloned) throws G2AccessException;

}
