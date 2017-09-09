/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilSliderObjectImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:51 EDT 2007
 *
 */


package com.gensym.classes.modules.uilslide;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class UilSliderObjectImpl extends com.gensym.classes.modules.uilroot.UilGrobjImpl implements UilSliderObject {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_SLIDER_CREATION_FLAG_ = Symbol.intern ("UIL-SLIDER-CREATION-FLAG");
  private static final Symbol UIL_UPDATE_VALUE_ = Symbol.intern ("UIL-UPDATE-VALUE");

  /* Generated constructors */

  public UilSliderObjectImpl() {
    super();
  }

  public UilSliderObjectImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilSliderObjectImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-SLIDER-CREATION-FLAG
   * @param uilSliderCreationFlag new value to conclude for UIL-SLIDER-CREATION-FLAG
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilSliderCreationFlag(java.lang.Object uilSliderCreationFlag) throws G2AccessException {
    setAttributeValue (UIL_SLIDER_CREATION_FLAG_, uilSliderCreationFlag);
  }

  /**
   * Generated Property Getter for attribute -- UIL-SLIDER-CREATION-FLAG
   * @return the value of the UIL-SLIDER-CREATION-FLAG attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilSliderCreationFlag() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_SLIDER_CREATION_FLAG_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-UPDATE-VALUE
   * @param uilUpdateValue new value to conclude for UIL-UPDATE-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilUpdateValue(java.lang.Object uilUpdateValue) throws G2AccessException {
    setAttributeValue (UIL_UPDATE_VALUE_, uilUpdateValue);
  }

  /**
   * Generated Property Getter for attribute -- UIL-UPDATE-VALUE
   * @return the value of the UIL-UPDATE-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilUpdateValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_UPDATE_VALUE_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
