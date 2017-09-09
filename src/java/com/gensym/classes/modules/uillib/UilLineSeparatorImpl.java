/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilLineSeparatorImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:44 EDT 2007
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

public class UilLineSeparatorImpl extends com.gensym.classes.modules.uillib.UilExtensionObjectImpl implements UilLineSeparator {


  static final long serialVersionUID = 2L;
  private static final Symbol ORIENTATION_ = Symbol.intern ("ORIENTATION");

  /* Generated constructors */

  public UilLineSeparatorImpl() {
    super();
  }

  public UilLineSeparatorImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilLineSeparatorImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- ORIENTATION
   * @param orientation new value to conclude for ORIENTATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setOrientation(java.lang.Object orientation) throws G2AccessException {
    setAttributeValue (ORIENTATION_, orientation);
  }

  /**
   * Generated Property Getter for attribute -- ORIENTATION
   * @return the value of the ORIENTATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getOrientation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (ORIENTATION_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
