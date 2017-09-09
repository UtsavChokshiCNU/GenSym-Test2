/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilBoxObjectImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:35 EDT 2007
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

public class UilBoxObjectImpl extends com.gensym.classes.modules.uillib.UilExtensionObjectImpl implements UilBoxObject {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_CURRENT_X_POSITION_ = Symbol.intern ("UIL-CURRENT-X-POSITION");
  private static final Symbol UIL_CURRENT_Y_POSITION_ = Symbol.intern ("UIL-CURRENT-Y-POSITION");

  /* Generated constructors */

  public UilBoxObjectImpl() {
    super();
  }

  public UilBoxObjectImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilBoxObjectImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-CURRENT-X-POSITION
   * @param uilCurrentXPosition new value to conclude for UIL-CURRENT-X-POSITION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilCurrentXPosition(java.lang.Object uilCurrentXPosition) throws G2AccessException {
    setAttributeValue (UIL_CURRENT_X_POSITION_, uilCurrentXPosition);
  }

  /**
   * Generated Property Getter for attribute -- UIL-CURRENT-X-POSITION
   * @return the value of the UIL-CURRENT-X-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilCurrentXPosition() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_CURRENT_X_POSITION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-CURRENT-Y-POSITION
   * @param uilCurrentYPosition new value to conclude for UIL-CURRENT-Y-POSITION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilCurrentYPosition(java.lang.Object uilCurrentYPosition) throws G2AccessException {
    setAttributeValue (UIL_CURRENT_Y_POSITION_, uilCurrentYPosition);
  }

  /**
   * Generated Property Getter for attribute -- UIL-CURRENT-Y-POSITION
   * @return the value of the UIL-CURRENT-Y-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilCurrentYPosition() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_CURRENT_Y_POSITION_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
