/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilBoxObject.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:30 EDT 2007
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

public interface UilBoxObject extends com.gensym.classes.modules.uillib.UilExtensionObject {

  public static final Symbol UIL_BOX_OBJECT_ = Symbol.intern ("UIL-BOX-OBJECT");
  static final Symbol g2ClassName = UIL_BOX_OBJECT_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_BOX_OBJECT_, UIL_EXTENSION_OBJECT_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-CURRENT-X-POSITION
   * @return the value of the UIL-CURRENT-X-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-CURRENT-X-POSITION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilCurrentXPosition() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-CURRENT-X-POSITION
   * @param uilCurrentXPosition new value to conclude for UIL-CURRENT-X-POSITION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilCurrentXPosition(java.lang.Object uilCurrentXPosition) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-CURRENT-Y-POSITION
   * @return the value of the UIL-CURRENT-Y-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-CURRENT-Y-POSITION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilCurrentYPosition() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-CURRENT-Y-POSITION
   * @param uilCurrentYPosition new value to conclude for UIL-CURRENT-Y-POSITION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilCurrentYPosition(java.lang.Object uilCurrentYPosition) throws G2AccessException;

}
