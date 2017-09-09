/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilSelectionButtonImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:05:48 EDT 2007
 *
 */


package com.gensym.classes.modules.uilroot;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class UilSelectionButtonImpl extends com.gensym.classes.modules.uilroot.UilIconButtonImpl implements UilSelectionButton {


  static final long serialVersionUID = 2L;
  private static final Symbol ON_VALUE_ = Symbol.intern ("ON-VALUE");
  private static final Symbol OFF_VALUE_ = Symbol.intern ("OFF-VALUE");
  private static final Symbol TOGGLE_STATE_ = Symbol.intern ("TOGGLE-STATE");
  private static final Symbol CALLBACK_ = Symbol.intern ("CALLBACK");
  private static final Symbol UIL_HAS_BEEN_CLONED_ = Symbol.intern ("UIL-HAS-BEEN-CLONED");
  private static final Symbol UIL_UPDATE_VALUE_ = Symbol.intern ("UIL-UPDATE-VALUE");
  private static final Symbol UIL_BUTTON_ID_ = Symbol.intern ("UIL-BUTTON-ID");

  /* Generated constructors */

  public UilSelectionButtonImpl() {
    super();
  }

  public UilSelectionButtonImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilSelectionButtonImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- ON-VALUE
   * @param onValue new value to conclude for ON-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setOnValue(java.lang.Object onValue) throws G2AccessException {
    setAttributeValue (ON_VALUE_, onValue);
  }

  /**
   * Generated Property Getter for attribute -- ON-VALUE
   * @return the value of the ON-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getOnValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (ON_VALUE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- OFF-VALUE
   * @param offValue new value to conclude for OFF-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setOffValue(java.lang.Object offValue) throws G2AccessException {
    setAttributeValue (OFF_VALUE_, offValue);
  }

  /**
   * Generated Property Getter for attribute -- OFF-VALUE
   * @return the value of the OFF-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getOffValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (OFF_VALUE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TOGGLE-STATE
   * @param toggleState new value to conclude for TOGGLE-STATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setToggleState(java.lang.Object toggleState) throws G2AccessException {
    setAttributeValue (TOGGLE_STATE_, toggleState);
  }

  /**
   * Generated Property Getter for attribute -- TOGGLE-STATE
   * @return the value of the TOGGLE-STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getToggleState() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (TOGGLE_STATE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CALLBACK
   * @param callback new value to conclude for CALLBACK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setCallback(java.lang.Object callback) throws G2AccessException {
    setAttributeValue (CALLBACK_, callback);
  }

  /**
   * Generated Property Getter for attribute -- CALLBACK
   * @return the value of the CALLBACK attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getCallback() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (CALLBACK_);
    return (java.lang.Object)retnValue;
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

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-ID
   * @param uilButtonId new value to conclude for UIL-BUTTON-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilButtonId(java.lang.Object uilButtonId) throws G2AccessException {
    setAttributeValue (UIL_BUTTON_ID_, uilButtonId);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-ID
   * @return the value of the UIL-BUTTON-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilButtonId() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BUTTON_ID_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
