/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilRadioButtonConfigurationClassImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:35 EDT 2007
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

public class UilRadioButtonConfigurationClassImpl extends com.gensym.classes.modules.uilroot.UilConfigurationClassImpl implements UilRadioButtonConfigurationClass {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_BUTTON_SIZE_ = Symbol.intern ("UIL-BUTTON-SIZE");
  private static final Symbol UIL_BUTTON_SEPARATION_ = Symbol.intern ("UIL-BUTTON-SEPARATION");
  private static final Symbol UIL_BUTTON_LIGHT_COLOR_ = Symbol.intern ("UIL-BUTTON-LIGHT-COLOR");
  private static final Symbol UIL_BUTTON_DARK_COLOR_ = Symbol.intern ("UIL-BUTTON-DARK-COLOR");
  private static final Symbol UIL_BUTTON_FACE_COLOR_ = Symbol.intern ("UIL-BUTTON-FACE-COLOR");
  private static final Symbol UIL_BUTTON_LAMP_COLOR_ = Symbol.intern ("UIL-BUTTON-LAMP-COLOR");
  private static final Symbol UIL_BUTTON_DISABLED_COLOR_ = Symbol.intern ("UIL-BUTTON-DISABLED-COLOR");
  private static final Symbol UIL_BUTTON_BORDER_COLOR_ = Symbol.intern ("UIL-BUTTON-BORDER-COLOR");
  private static final Symbol UIL_BOX_BORDER_COLOR_ = Symbol.intern ("UIL-BOX-BORDER-COLOR");
  private static final Symbol UIL_BOX_FILL_COLOR_ = Symbol.intern ("UIL-BOX-FILL-COLOR");
  private static final Symbol UIL_BUTTON_LABEL_COLOR_ = Symbol.intern ("UIL-BUTTON-LABEL-COLOR");
  private static final Symbol UIL_BUTTON_DISABLED_LABEL_COLOR_ = Symbol.intern ("UIL-BUTTON-DISABLED-LABEL-COLOR");

  /* Generated constructors */

  public UilRadioButtonConfigurationClassImpl() {
    super();
  }

  public UilRadioButtonConfigurationClassImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilRadioButtonConfigurationClassImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-SIZE
   * @param uilButtonSize new value to conclude for UIL-BUTTON-SIZE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilButtonSize(java.lang.Object uilButtonSize) throws G2AccessException {
    setAttributeValue (UIL_BUTTON_SIZE_, uilButtonSize);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-SIZE
   * @return the value of the UIL-BUTTON-SIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilButtonSize() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BUTTON_SIZE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-SEPARATION
   * @param uilButtonSeparation new value to conclude for UIL-BUTTON-SEPARATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilButtonSeparation(java.lang.Object uilButtonSeparation) throws G2AccessException {
    setAttributeValue (UIL_BUTTON_SEPARATION_, uilButtonSeparation);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-SEPARATION
   * @return the value of the UIL-BUTTON-SEPARATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilButtonSeparation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BUTTON_SEPARATION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-LIGHT-COLOR
   * @param uilButtonLightColor new value to conclude for UIL-BUTTON-LIGHT-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilButtonLightColor(java.lang.Object uilButtonLightColor) throws G2AccessException {
    setAttributeValue (UIL_BUTTON_LIGHT_COLOR_, uilButtonLightColor);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-LIGHT-COLOR
   * @return the value of the UIL-BUTTON-LIGHT-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilButtonLightColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BUTTON_LIGHT_COLOR_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-DARK-COLOR
   * @param uilButtonDarkColor new value to conclude for UIL-BUTTON-DARK-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilButtonDarkColor(java.lang.Object uilButtonDarkColor) throws G2AccessException {
    setAttributeValue (UIL_BUTTON_DARK_COLOR_, uilButtonDarkColor);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-DARK-COLOR
   * @return the value of the UIL-BUTTON-DARK-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilButtonDarkColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BUTTON_DARK_COLOR_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-FACE-COLOR
   * @param uilButtonFaceColor new value to conclude for UIL-BUTTON-FACE-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilButtonFaceColor(java.lang.Object uilButtonFaceColor) throws G2AccessException {
    setAttributeValue (UIL_BUTTON_FACE_COLOR_, uilButtonFaceColor);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-FACE-COLOR
   * @return the value of the UIL-BUTTON-FACE-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilButtonFaceColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BUTTON_FACE_COLOR_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-LAMP-COLOR
   * @param uilButtonLampColor new value to conclude for UIL-BUTTON-LAMP-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilButtonLampColor(java.lang.Object uilButtonLampColor) throws G2AccessException {
    setAttributeValue (UIL_BUTTON_LAMP_COLOR_, uilButtonLampColor);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-LAMP-COLOR
   * @return the value of the UIL-BUTTON-LAMP-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilButtonLampColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BUTTON_LAMP_COLOR_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-DISABLED-COLOR
   * @param uilButtonDisabledColor new value to conclude for UIL-BUTTON-DISABLED-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilButtonDisabledColor(java.lang.Object uilButtonDisabledColor) throws G2AccessException {
    setAttributeValue (UIL_BUTTON_DISABLED_COLOR_, uilButtonDisabledColor);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-DISABLED-COLOR
   * @return the value of the UIL-BUTTON-DISABLED-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilButtonDisabledColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BUTTON_DISABLED_COLOR_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-BORDER-COLOR
   * @param uilButtonBorderColor new value to conclude for UIL-BUTTON-BORDER-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilButtonBorderColor(java.lang.Object uilButtonBorderColor) throws G2AccessException {
    setAttributeValue (UIL_BUTTON_BORDER_COLOR_, uilButtonBorderColor);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-BORDER-COLOR
   * @return the value of the UIL-BUTTON-BORDER-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilButtonBorderColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BUTTON_BORDER_COLOR_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BOX-BORDER-COLOR
   * @param uilBoxBorderColor new value to conclude for UIL-BOX-BORDER-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilBoxBorderColor(java.lang.Object uilBoxBorderColor) throws G2AccessException {
    setAttributeValue (UIL_BOX_BORDER_COLOR_, uilBoxBorderColor);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BOX-BORDER-COLOR
   * @return the value of the UIL-BOX-BORDER-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilBoxBorderColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BOX_BORDER_COLOR_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BOX-FILL-COLOR
   * @param uilBoxFillColor new value to conclude for UIL-BOX-FILL-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilBoxFillColor(java.lang.Object uilBoxFillColor) throws G2AccessException {
    setAttributeValue (UIL_BOX_FILL_COLOR_, uilBoxFillColor);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BOX-FILL-COLOR
   * @return the value of the UIL-BOX-FILL-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilBoxFillColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BOX_FILL_COLOR_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-LABEL-COLOR
   * @param uilButtonLabelColor new value to conclude for UIL-BUTTON-LABEL-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilButtonLabelColor(java.lang.Object uilButtonLabelColor) throws G2AccessException {
    setAttributeValue (UIL_BUTTON_LABEL_COLOR_, uilButtonLabelColor);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-LABEL-COLOR
   * @return the value of the UIL-BUTTON-LABEL-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilButtonLabelColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BUTTON_LABEL_COLOR_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-DISABLED-LABEL-COLOR
   * @param uilButtonDisabledLabelColor new value to conclude for UIL-BUTTON-DISABLED-LABEL-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilButtonDisabledLabelColor(java.lang.Object uilButtonDisabledLabelColor) throws G2AccessException {
    setAttributeValue (UIL_BUTTON_DISABLED_LABEL_COLOR_, uilButtonDisabledLabelColor);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-DISABLED-LABEL-COLOR
   * @return the value of the UIL-BUTTON-DISABLED-LABEL-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilButtonDisabledLabelColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BUTTON_DISABLED_LABEL_COLOR_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
