/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilSpinControlEntryBoxImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:13 EDT 2007
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

public class UilSpinControlEntryBoxImpl extends com.gensym.classes.modules.uillib.UilEditBoxImpl implements UilSpinControlEntryBox {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_SPIN_UP_BUTTON_ID_ = Symbol.intern ("UIL-SPIN-UP-BUTTON-ID");
  private static final Symbol UIL_SPIN_DOWN_BUTTON_ID_ = Symbol.intern ("UIL-SPIN-DOWN-BUTTON-ID");
  private static final Symbol UIL_SPIN_CONTROL_LOW_VALUE_ = Symbol.intern ("UIL-SPIN-CONTROL-LOW-VALUE");
  private static final Symbol UIL_SPIN_CONTROL_HI_VALUE_ = Symbol.intern ("UIL-SPIN-CONTROL-HI-VALUE");
  private static final Symbol UIL_SPIN_CONTROL_INCREMENT_ = Symbol.intern ("UIL-SPIN-CONTROL-INCREMENT");
  private static final Symbol UIL_SPIN_CONTROL_PERMIT_WRAPPING_ = Symbol.intern ("UIL-SPIN-CONTROL-PERMIT-WRAPPING");
  private static final Symbol UIL_SPIN_CONTROL_INITIAL_VALUE_ = Symbol.intern ("UIL-SPIN-CONTROL-INITIAL-VALUE");
  private static final Symbol UIL_SPIN_CONTROL_ATTACH_BORDER_ = Symbol.intern ("UIL-SPIN-CONTROL-ATTACH-BORDER");

  /* Generated constructors */

  public UilSpinControlEntryBoxImpl() {
    super();
  }

  public UilSpinControlEntryBoxImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilSpinControlEntryBoxImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-SPIN-UP-BUTTON-ID
   * @param uilSpinUpButtonId new value to conclude for UIL-SPIN-UP-BUTTON-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilSpinUpButtonId(java.lang.Object uilSpinUpButtonId) throws G2AccessException {
    setAttributeValue (UIL_SPIN_UP_BUTTON_ID_, uilSpinUpButtonId);
  }

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-UP-BUTTON-ID
   * @return the value of the UIL-SPIN-UP-BUTTON-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilSpinUpButtonId() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_SPIN_UP_BUTTON_ID_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-DOWN-BUTTON-ID
   * @param uilSpinDownButtonId new value to conclude for UIL-SPIN-DOWN-BUTTON-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilSpinDownButtonId(java.lang.Object uilSpinDownButtonId) throws G2AccessException {
    setAttributeValue (UIL_SPIN_DOWN_BUTTON_ID_, uilSpinDownButtonId);
  }

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-DOWN-BUTTON-ID
   * @return the value of the UIL-SPIN-DOWN-BUTTON-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilSpinDownButtonId() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_SPIN_DOWN_BUTTON_ID_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-CONTROL-LOW-VALUE
   * @param uilSpinControlLowValue new value to conclude for UIL-SPIN-CONTROL-LOW-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilSpinControlLowValue(java.lang.Object uilSpinControlLowValue) throws G2AccessException {
    setAttributeValue (UIL_SPIN_CONTROL_LOW_VALUE_, uilSpinControlLowValue);
  }

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-CONTROL-LOW-VALUE
   * @return the value of the UIL-SPIN-CONTROL-LOW-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilSpinControlLowValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_SPIN_CONTROL_LOW_VALUE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-CONTROL-HI-VALUE
   * @param uilSpinControlHiValue new value to conclude for UIL-SPIN-CONTROL-HI-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilSpinControlHiValue(java.lang.Object uilSpinControlHiValue) throws G2AccessException {
    setAttributeValue (UIL_SPIN_CONTROL_HI_VALUE_, uilSpinControlHiValue);
  }

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-CONTROL-HI-VALUE
   * @return the value of the UIL-SPIN-CONTROL-HI-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilSpinControlHiValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_SPIN_CONTROL_HI_VALUE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-CONTROL-INCREMENT
   * @param uilSpinControlIncrement new value to conclude for UIL-SPIN-CONTROL-INCREMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilSpinControlIncrement(java.lang.Object uilSpinControlIncrement) throws G2AccessException {
    setAttributeValue (UIL_SPIN_CONTROL_INCREMENT_, uilSpinControlIncrement);
  }

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-CONTROL-INCREMENT
   * @return the value of the UIL-SPIN-CONTROL-INCREMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilSpinControlIncrement() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_SPIN_CONTROL_INCREMENT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-CONTROL-PERMIT-WRAPPING
   * @param uilSpinControlPermitWrapping new value to conclude for UIL-SPIN-CONTROL-PERMIT-WRAPPING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilSpinControlPermitWrapping(java.lang.Object uilSpinControlPermitWrapping) throws G2AccessException {
    setAttributeValue (UIL_SPIN_CONTROL_PERMIT_WRAPPING_, uilSpinControlPermitWrapping);
  }

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-CONTROL-PERMIT-WRAPPING
   * @return the value of the UIL-SPIN-CONTROL-PERMIT-WRAPPING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilSpinControlPermitWrapping() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_SPIN_CONTROL_PERMIT_WRAPPING_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-CONTROL-INITIAL-VALUE
   * @param uilSpinControlInitialValue new value to conclude for UIL-SPIN-CONTROL-INITIAL-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilSpinControlInitialValue(java.lang.Object uilSpinControlInitialValue) throws G2AccessException {
    setAttributeValue (UIL_SPIN_CONTROL_INITIAL_VALUE_, uilSpinControlInitialValue);
  }

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-CONTROL-INITIAL-VALUE
   * @return the value of the UIL-SPIN-CONTROL-INITIAL-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilSpinControlInitialValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_SPIN_CONTROL_INITIAL_VALUE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-SPIN-CONTROL-ATTACH-BORDER
   * @param uilSpinControlAttachBorder new value to conclude for UIL-SPIN-CONTROL-ATTACH-BORDER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilSpinControlAttachBorder(java.lang.Object uilSpinControlAttachBorder) throws G2AccessException {
    setAttributeValue (UIL_SPIN_CONTROL_ATTACH_BORDER_, uilSpinControlAttachBorder);
  }

  /**
   * Generated Property Getter for attribute -- UIL-SPIN-CONTROL-ATTACH-BORDER
   * @return the value of the UIL-SPIN-CONTROL-ATTACH-BORDER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilSpinControlAttachBorder() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_SPIN_CONTROL_ATTACH_BORDER_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
