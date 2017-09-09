/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilBoxBorderImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:36 EDT 2007
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

public class UilBoxBorderImpl extends com.gensym.classes.modules.uillib.UilBoxObjectImpl implements UilBoxBorder {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_BORDER_ID_ = Symbol.intern ("UIL-BORDER-ID");

  /* Generated constructors */

  public UilBoxBorderImpl() {
    super();
  }

  public UilBoxBorderImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilBoxBorderImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-BORDER-ID
   * @param uilBorderId new value to conclude for UIL-BORDER-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilBorderId(java.lang.Object uilBorderId) throws G2AccessException {
    setAttributeValue (UIL_BORDER_ID_, uilBorderId);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BORDER-ID
   * @return the value of the UIL-BORDER-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilBorderId() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BORDER_ID_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
