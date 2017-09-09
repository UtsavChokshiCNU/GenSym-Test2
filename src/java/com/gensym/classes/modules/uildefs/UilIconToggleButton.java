/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilIconToggleButton.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:05:59 EDT 2007
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

public interface UilIconToggleButton extends com.gensym.classes.modules.uilroot.UilIconButton {

  public static final Symbol UIL_ICON_TOGGLE_BUTTON_ = Symbol.intern ("UIL-ICON-TOGGLE-BUTTON");
  static final Symbol g2ClassName = UIL_ICON_TOGGLE_BUTTON_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_ICON_TOGGLE_BUTTON_, UIL_ICON_BUTTON_, UIL_BUTTON_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- CALLBACK
   * @return the value of the CALLBACK attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CALLBACK is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getCallback() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CALLBACK
   * @param callback new value to conclude for CALLBACK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setCallback(java.lang.Object callback) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TOGGLE-STATE
   * @return the value of the TOGGLE-STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TOGGLE-STATE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getToggleState() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TOGGLE-STATE
   * @param toggleState new value to conclude for TOGGLE-STATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setToggleState(java.lang.Object toggleState) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TOGGLELABEL
   * @return the value of the TOGGLELABEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TOGGLELABEL is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getTogglelabel() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TOGGLELABEL
   * @param togglelabel new value to conclude for TOGGLELABEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTogglelabel(java.lang.Object togglelabel) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ON-VALUE
   * @return the value of the ON-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ON-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getOnValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ON-VALUE
   * @param onValue new value to conclude for ON-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setOnValue(java.lang.Object onValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- OFF-VALUE
   * @return the value of the OFF-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for OFF-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getOffValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- OFF-VALUE
   * @param offValue new value to conclude for OFF-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setOffValue(java.lang.Object offValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-UPDATE-VALUE
   * @return the value of the UIL-UPDATE-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-UPDATE-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilUpdateValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-UPDATE-VALUE
   * @param uilUpdateValue new value to conclude for UIL-UPDATE-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilUpdateValue(java.lang.Object uilUpdateValue) throws G2AccessException;

}
