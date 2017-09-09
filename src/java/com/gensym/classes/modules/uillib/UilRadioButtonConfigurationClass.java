/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilRadioButtonConfigurationClass.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:33 EDT 2007
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

public interface UilRadioButtonConfigurationClass extends com.gensym.classes.modules.uilroot.UilConfigurationClass {

  public static final Symbol UIL_RADIO_BUTTON_CONFIGURATION_CLASS_ = Symbol.intern ("UIL-RADIO-BUTTON-CONFIGURATION-CLASS");
  static final Symbol g2ClassName = UIL_RADIO_BUTTON_CONFIGURATION_CLASS_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_RADIO_BUTTON_CONFIGURATION_CLASS_, UIL_CONFIGURATION_CLASS_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-SIZE
   * @return the value of the UIL-BUTTON-SIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BUTTON-SIZE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilButtonSize() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-SIZE
   * @param uilButtonSize new value to conclude for UIL-BUTTON-SIZE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilButtonSize(java.lang.Object uilButtonSize) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-SEPARATION
   * @return the value of the UIL-BUTTON-SEPARATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BUTTON-SEPARATION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilButtonSeparation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-SEPARATION
   * @param uilButtonSeparation new value to conclude for UIL-BUTTON-SEPARATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilButtonSeparation(java.lang.Object uilButtonSeparation) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-LIGHT-COLOR
   * @return the value of the UIL-BUTTON-LIGHT-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BUTTON-LIGHT-COLOR is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilButtonLightColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-LIGHT-COLOR
   * @param uilButtonLightColor new value to conclude for UIL-BUTTON-LIGHT-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilButtonLightColor(java.lang.Object uilButtonLightColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-DARK-COLOR
   * @return the value of the UIL-BUTTON-DARK-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BUTTON-DARK-COLOR is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilButtonDarkColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-DARK-COLOR
   * @param uilButtonDarkColor new value to conclude for UIL-BUTTON-DARK-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilButtonDarkColor(java.lang.Object uilButtonDarkColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-FACE-COLOR
   * @return the value of the UIL-BUTTON-FACE-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BUTTON-FACE-COLOR is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilButtonFaceColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-FACE-COLOR
   * @param uilButtonFaceColor new value to conclude for UIL-BUTTON-FACE-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilButtonFaceColor(java.lang.Object uilButtonFaceColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-LAMP-COLOR
   * @return the value of the UIL-BUTTON-LAMP-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BUTTON-LAMP-COLOR is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilButtonLampColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-LAMP-COLOR
   * @param uilButtonLampColor new value to conclude for UIL-BUTTON-LAMP-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilButtonLampColor(java.lang.Object uilButtonLampColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-DISABLED-COLOR
   * @return the value of the UIL-BUTTON-DISABLED-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BUTTON-DISABLED-COLOR is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilButtonDisabledColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-DISABLED-COLOR
   * @param uilButtonDisabledColor new value to conclude for UIL-BUTTON-DISABLED-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilButtonDisabledColor(java.lang.Object uilButtonDisabledColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-BORDER-COLOR
   * @return the value of the UIL-BUTTON-BORDER-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BUTTON-BORDER-COLOR is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilButtonBorderColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-BORDER-COLOR
   * @param uilButtonBorderColor new value to conclude for UIL-BUTTON-BORDER-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilButtonBorderColor(java.lang.Object uilButtonBorderColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BOX-BORDER-COLOR
   * @return the value of the UIL-BOX-BORDER-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BOX-BORDER-COLOR is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilBoxBorderColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BOX-BORDER-COLOR
   * @param uilBoxBorderColor new value to conclude for UIL-BOX-BORDER-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilBoxBorderColor(java.lang.Object uilBoxBorderColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BOX-FILL-COLOR
   * @return the value of the UIL-BOX-FILL-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BOX-FILL-COLOR is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilBoxFillColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BOX-FILL-COLOR
   * @param uilBoxFillColor new value to conclude for UIL-BOX-FILL-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilBoxFillColor(java.lang.Object uilBoxFillColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-LABEL-COLOR
   * @return the value of the UIL-BUTTON-LABEL-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BUTTON-LABEL-COLOR is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilButtonLabelColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-LABEL-COLOR
   * @param uilButtonLabelColor new value to conclude for UIL-BUTTON-LABEL-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilButtonLabelColor(java.lang.Object uilButtonLabelColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-DISABLED-LABEL-COLOR
   * @return the value of the UIL-BUTTON-DISABLED-LABEL-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BUTTON-DISABLED-LABEL-COLOR is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilButtonDisabledLabelColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-DISABLED-LABEL-COLOR
   * @param uilButtonDisabledLabelColor new value to conclude for UIL-BUTTON-DISABLED-LABEL-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilButtonDisabledLabelColor(java.lang.Object uilButtonDisabledLabelColor) throws G2AccessException;

}
