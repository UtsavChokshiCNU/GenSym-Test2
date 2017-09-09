/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilSlider.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:49 EDT 2007
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

public interface UilSlider extends com.gensym.classes.modules.uilslide.UilSliderObject {

  public static final Symbol UIL_SLIDER_ = Symbol.intern ("UIL-SLIDER");
  static final Symbol g2ClassName = UIL_SLIDER_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_SLIDER_, UIL_SLIDER_OBJECT_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- ORIENTATION
   * @return the value of the ORIENTATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ORIENTATION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getOrientation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ORIENTATION
   * @param orientation new value to conclude for ORIENTATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setOrientation(java.lang.Object orientation) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CURRENT-VALUE
   * @return the value of the CURRENT-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CURRENT-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getCurrentValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CURRENT-VALUE
   * @param currentValue new value to conclude for CURRENT-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setCurrentValue(java.lang.Object currentValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- HI-VALUE
   * @return the value of the HI-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for HI-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getHiValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- HI-VALUE
   * @param hiValue new value to conclude for HI-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setHiValue(java.lang.Object hiValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- LO-VALUE
   * @return the value of the LO-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LO-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getLoValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LO-VALUE
   * @param loValue new value to conclude for LO-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLoValue(java.lang.Object loValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PERMITTED-INCREMENT
   * @return the value of the PERMITTED-INCREMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PERMITTED-INCREMENT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getPermittedIncrement() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PERMITTED-INCREMENT
   * @param permittedIncrement new value to conclude for PERMITTED-INCREMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPermittedIncrement(java.lang.Object permittedIncrement) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ALLOW-FRACTIONAL-INCREMENTS
   * @return the value of the ALLOW-FRACTIONAL-INCREMENTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ALLOW-FRACTIONAL-INCREMENTS is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getAllowFractionalIncrements() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ALLOW-FRACTIONAL-INCREMENTS
   * @param allowFractionalIncrements new value to conclude for ALLOW-FRACTIONAL-INCREMENTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAllowFractionalIncrements(java.lang.Object allowFractionalIncrements) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- X-MARGIN
   * @return the value of the X-MARGIN attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for X-MARGIN is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getXMargin() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- X-MARGIN
   * @param xMargin new value to conclude for X-MARGIN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setXMargin(java.lang.Object xMargin) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- Y-MARGIN
   * @return the value of the Y-MARGIN attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for Y-MARGIN is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getYMargin() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- Y-MARGIN
   * @param yMargin new value to conclude for Y-MARGIN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setYMargin(java.lang.Object yMargin) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SET-VALUE-WHILE-SLIDING
   * @return the value of the SET-VALUE-WHILE-SLIDING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SET-VALUE-WHILE-SLIDING is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getSetValueWhileSliding() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SET-VALUE-WHILE-SLIDING
   * @param setValueWhileSliding new value to conclude for SET-VALUE-WHILE-SLIDING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSetValueWhileSliding(java.lang.Object setValueWhileSliding) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SLIDER-POINTER-CLASS-TO-CREATE
   * @return the value of the UIL-SLIDER-POINTER-CLASS-TO-CREATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SLIDER-POINTER-CLASS-TO-CREATE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilSliderPointerClassToCreate() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SLIDER-POINTER-CLASS-TO-CREATE
   * @param uilSliderPointerClassToCreate new value to conclude for UIL-SLIDER-POINTER-CLASS-TO-CREATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilSliderPointerClassToCreate(java.lang.Object uilSliderPointerClassToCreate) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- STATE
   * @return the value of the STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for STATE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getState() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- STATE
   * @param state new value to conclude for STATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setState(java.lang.Object state) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- VALUE-CHANGED-CALLBACK
   * @return the value of the VALUE-CHANGED-CALLBACK attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for VALUE-CHANGED-CALLBACK is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getValueChangedCallback() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- VALUE-CHANGED-CALLBACK
   * @param valueChangedCallback new value to conclude for VALUE-CHANGED-CALLBACK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setValueChangedCallback(com.gensym.util.Symbol valueChangedCallback) throws G2AccessException;

}
