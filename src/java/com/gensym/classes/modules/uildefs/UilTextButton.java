/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilTextButton.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:04 EDT 2007
 *
 */


package com.gensym.classes.modules.uildefs;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface UilTextButton extends com.gensym.classes.modules.uilroot.UilButton {

  public static final Symbol UIL_TEXT_BUTTON_ = Symbol.intern ("UIL-TEXT-BUTTON");
  static final Symbol g2ClassName = UIL_TEXT_BUTTON_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_TEXT_BUTTON_, UIL_BUTTON_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- LABEL
   * @return the value of the LABEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LABEL is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getLabel() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LABEL
   * @param label new value to conclude for LABEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLabel(java.lang.Object label) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-RESIZE-TO-FIT-LABEL
   * @return the value of the UIL-RESIZE-TO-FIT-LABEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-RESIZE-TO-FIT-LABEL is : 
   * BooleanTruthValue
   *
   */
  public boolean getUilResizeToFitLabel() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-RESIZE-TO-FIT-LABEL
   * @param uilResizeToFitLabel new value to conclude for UIL-RESIZE-TO-FIT-LABEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilResizeToFitLabel(boolean uilResizeToFitLabel) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-MINIMUM-HEIGHT
   * @return the value of the UIL-MINIMUM-HEIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-MINIMUM-HEIGHT is : 
   * Integer
   *
   */
  public int getUilMinimumHeight() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-MINIMUM-HEIGHT
   * @param uilMinimumHeight new value to conclude for UIL-MINIMUM-HEIGHT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilMinimumHeight(int uilMinimumHeight) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-MINIMUM-WIDTH
   * @return the value of the UIL-MINIMUM-WIDTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-MINIMUM-WIDTH is : 
   * Integer
   *
   */
  public int getUilMinimumWidth() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-MINIMUM-WIDTH
   * @param uilMinimumWidth new value to conclude for UIL-MINIMUM-WIDTH
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilMinimumWidth(int uilMinimumWidth) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * UIL-TEXT-BUTTON::UPP-SET-BUTTON-LABEL
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-TEXT-BUTTON,arg1:TEXT) = ()
   */
  public  void uppSetButtonLabel(java.lang.String arg1) throws G2AccessException;
  
}
