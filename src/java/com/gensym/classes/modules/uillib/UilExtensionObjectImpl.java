/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilExtensionObjectImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:34 EDT 2007
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

public class UilExtensionObjectImpl extends com.gensym.classes.modules.uilroot.UilGrobjImpl implements UilExtensionObject {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_HAS_BEEN_CLONED_ = Symbol.intern ("UIL-HAS-BEEN-CLONED");

  /* Generated constructors */

  public UilExtensionObjectImpl() {
    super();
  }

  public UilExtensionObjectImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilExtensionObjectImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-HAS-BEEN-CLONED
   * @param uilHasBeenCloned new value to conclude for UIL-HAS-BEEN-CLONED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilHasBeenCloned(java.lang.Object uilHasBeenCloned) throws G2AccessException {
    setAttributeValue (UIL_HAS_BEEN_CLONED_, uilHasBeenCloned);
  }

  /**
   * Generated Property Getter for attribute -- UIL-HAS-BEEN-CLONED
   * @return the value of the UIL-HAS-BEEN-CLONED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilHasBeenCloned() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_HAS_BEEN_CLONED_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
