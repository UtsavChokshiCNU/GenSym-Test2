/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilSliderImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:52 EDT 2007
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

public class UilSliderImpl extends com.gensym.classes.modules.uilslide.UilSliderObjectImpl implements UilSlider {


  static final long serialVersionUID = 2L;
  private static final Symbol ORIENTATION_ = Symbol.intern ("ORIENTATION");
  private static final Symbol CURRENT_VALUE_ = Symbol.intern ("CURRENT-VALUE");
  private static final Symbol HI_VALUE_ = Symbol.intern ("HI-VALUE");
  private static final Symbol LO_VALUE_ = Symbol.intern ("LO-VALUE");
  private static final Symbol PERMITTED_INCREMENT_ = Symbol.intern ("PERMITTED-INCREMENT");
  private static final Symbol ALLOW_FRACTIONAL_INCREMENTS_ = Symbol.intern ("ALLOW-FRACTIONAL-INCREMENTS");
  private static final Symbol X_MARGIN_ = Symbol.intern ("X-MARGIN");
  private static final Symbol Y_MARGIN_ = Symbol.intern ("Y-MARGIN");
  private static final Symbol SET_VALUE_WHILE_SLIDING_ = Symbol.intern ("SET-VALUE-WHILE-SLIDING");
  private static final Symbol UIL_SLIDER_POINTER_CLASS_TO_CREATE_ = Symbol.intern ("UIL-SLIDER-POINTER-CLASS-TO-CREATE");
  private static final Symbol STATE_ = Symbol.intern ("STATE");
  private static final Symbol VALUE_CHANGED_CALLBACK_ = Symbol.intern ("VALUE-CHANGED-CALLBACK");

  /* Generated constructors */

  public UilSliderImpl() {
    super();
  }

  public UilSliderImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilSliderImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
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

  /**
   * Generated Property Setter for attribute -- CURRENT-VALUE
   * @param currentValue new value to conclude for CURRENT-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setCurrentValue(java.lang.Object currentValue) throws G2AccessException {
    setAttributeValue (CURRENT_VALUE_, currentValue);
  }

  /**
   * Generated Property Getter for attribute -- CURRENT-VALUE
   * @return the value of the CURRENT-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getCurrentValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (CURRENT_VALUE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- HI-VALUE
   * @param hiValue new value to conclude for HI-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setHiValue(java.lang.Object hiValue) throws G2AccessException {
    setAttributeValue (HI_VALUE_, hiValue);
  }

  /**
   * Generated Property Getter for attribute -- HI-VALUE
   * @return the value of the HI-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getHiValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (HI_VALUE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- LO-VALUE
   * @param loValue new value to conclude for LO-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setLoValue(java.lang.Object loValue) throws G2AccessException {
    setAttributeValue (LO_VALUE_, loValue);
  }

  /**
   * Generated Property Getter for attribute -- LO-VALUE
   * @return the value of the LO-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getLoValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (LO_VALUE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- PERMITTED-INCREMENT
   * @param permittedIncrement new value to conclude for PERMITTED-INCREMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPermittedIncrement(java.lang.Object permittedIncrement) throws G2AccessException {
    setAttributeValue (PERMITTED_INCREMENT_, permittedIncrement);
  }

  /**
   * Generated Property Getter for attribute -- PERMITTED-INCREMENT
   * @return the value of the PERMITTED-INCREMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getPermittedIncrement() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (PERMITTED_INCREMENT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ALLOW-FRACTIONAL-INCREMENTS
   * @param allowFractionalIncrements new value to conclude for ALLOW-FRACTIONAL-INCREMENTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAllowFractionalIncrements(java.lang.Object allowFractionalIncrements) throws G2AccessException {
    setAttributeValue (ALLOW_FRACTIONAL_INCREMENTS_, allowFractionalIncrements);
  }

  /**
   * Generated Property Getter for attribute -- ALLOW-FRACTIONAL-INCREMENTS
   * @return the value of the ALLOW-FRACTIONAL-INCREMENTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getAllowFractionalIncrements() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (ALLOW_FRACTIONAL_INCREMENTS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- X-MARGIN
   * @param xMargin new value to conclude for X-MARGIN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setXMargin(java.lang.Object xMargin) throws G2AccessException {
    setAttributeValue (X_MARGIN_, xMargin);
  }

  /**
   * Generated Property Getter for attribute -- X-MARGIN
   * @return the value of the X-MARGIN attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getXMargin() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (X_MARGIN_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- Y-MARGIN
   * @param yMargin new value to conclude for Y-MARGIN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setYMargin(java.lang.Object yMargin) throws G2AccessException {
    setAttributeValue (Y_MARGIN_, yMargin);
  }

  /**
   * Generated Property Getter for attribute -- Y-MARGIN
   * @return the value of the Y-MARGIN attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getYMargin() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (Y_MARGIN_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SET-VALUE-WHILE-SLIDING
   * @param setValueWhileSliding new value to conclude for SET-VALUE-WHILE-SLIDING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSetValueWhileSliding(java.lang.Object setValueWhileSliding) throws G2AccessException {
    setAttributeValue (SET_VALUE_WHILE_SLIDING_, setValueWhileSliding);
  }

  /**
   * Generated Property Getter for attribute -- SET-VALUE-WHILE-SLIDING
   * @return the value of the SET-VALUE-WHILE-SLIDING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getSetValueWhileSliding() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SET_VALUE_WHILE_SLIDING_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-SLIDER-POINTER-CLASS-TO-CREATE
   * @param uilSliderPointerClassToCreate new value to conclude for UIL-SLIDER-POINTER-CLASS-TO-CREATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilSliderPointerClassToCreate(java.lang.Object uilSliderPointerClassToCreate) throws G2AccessException {
    setAttributeValue (UIL_SLIDER_POINTER_CLASS_TO_CREATE_, uilSliderPointerClassToCreate);
  }

  /**
   * Generated Property Getter for attribute -- UIL-SLIDER-POINTER-CLASS-TO-CREATE
   * @return the value of the UIL-SLIDER-POINTER-CLASS-TO-CREATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilSliderPointerClassToCreate() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_SLIDER_POINTER_CLASS_TO_CREATE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- STATE
   * @param state new value to conclude for STATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setState(java.lang.Object state) throws G2AccessException {
    setAttributeValue (STATE_, state);
  }

  /**
   * Generated Property Getter for attribute -- STATE
   * @return the value of the STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getState() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (STATE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- VALUE-CHANGED-CALLBACK
   * @param valueChangedCallback new value to conclude for VALUE-CHANGED-CALLBACK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setValueChangedCallback(com.gensym.util.Symbol valueChangedCallback) throws G2AccessException {
    setAttributeValue (VALUE_CHANGED_CALLBACK_, valueChangedCallback);
  }

  /**
   * Generated Property Getter for attribute -- VALUE-CHANGED-CALLBACK
   * @return the value of the VALUE-CHANGED-CALLBACK attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getValueChangedCallback() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (VALUE_CHANGED_CALLBACK_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
