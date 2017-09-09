/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilActionDescriptionArrayImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:42 EDT 2007
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

public class UilActionDescriptionArrayImpl extends com.gensym.classes.modules.uilroot.UilObjectImpl implements UilActionDescriptionArray {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_ACTION_SPECIFICS_ = Symbol.intern ("UIL-ACTION-SPECIFICS");

  /* Generated constructors */

  public UilActionDescriptionArrayImpl() {
    super();
  }

  public UilActionDescriptionArrayImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilActionDescriptionArrayImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-ACTION-SPECIFICS
   * @param uilActionSpecifics new value to conclude for UIL-ACTION-SPECIFICS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilActionSpecifics(java.lang.Object uilActionSpecifics) throws G2AccessException {
    setAttributeValue (UIL_ACTION_SPECIFICS_, uilActionSpecifics);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ACTION-SPECIFICS
   * @return the value of the UIL-ACTION-SPECIFICS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilActionSpecifics() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ACTION_SPECIFICS_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
