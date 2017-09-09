/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Slider.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:08:17 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Slider extends com.gensym.classes.Item, com.gensym.classes.NonActionButton {

  public static final Symbol SLIDER_ = com.gensym.util.symbol.G2ClassSymbols.SLIDER_;
  static final Symbol g2ClassName = SLIDER_;
  static final Symbol[] classInheritancePath = new Symbol[] {SLIDER_, ITEM_, NON_ACTION_BUTTON_, BUTTON_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- MINIMUM-VALUE
   * @return the value of the MINIMUM-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MINIMUM-VALUE is : 
   * (OR NoItem
      Quantity)
   *
   */
  public java.lang.Number getMinimumValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MINIMUM-VALUE
   * @param minimumValue new value to conclude for MINIMUM-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMinimumValue(java.lang.Number minimumValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MAXIMUM-VALUE
   * @return the value of the MAXIMUM-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MAXIMUM-VALUE is : 
   * (OR NoItem
      Quantity)
   *
   */
  public java.lang.Number getMaximumValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MAXIMUM-VALUE
   * @param maximumValue new value to conclude for MAXIMUM-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMaximumValue(java.lang.Number maximumValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SET-VALUE-WHILE-SLIDING?
   * @return the value of the SET-VALUE-WHILE-SLIDING? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SET-VALUE-WHILE-SLIDING? is : 
   * BooleanTruthValue
   *
   */
  public boolean getSetValueWhileSliding() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SET-VALUE-WHILE-SLIDING?
   * @param setValueWhileSliding new value to conclude for SET-VALUE-WHILE-SLIDING?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSetValueWhileSliding(boolean setValueWhileSliding) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- WHEN-TO-SHOW-VALUE
   * @return the value of the WHEN-TO-SHOW-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for WHEN-TO-SHOW-VALUE is : 
   * (MEMBER ONLY-WHILE-SLIDING ALWAYS NEVER)
   *
   */
  public com.gensym.util.Symbol getWhenToShowValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- WHEN-TO-SHOW-VALUE
   * @param whenToShowValue new value to conclude for WHEN-TO-SHOW-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setWhenToShowValue(com.gensym.util.Symbol whenToShowValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SLIDER-VALUE
   * @return the value of the SLIDER-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SLIDER-VALUE is : 
   * Quantity
   *
   */
  public java.lang.Number getSliderValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SLIDER-VALUE
   * @param sliderValue new value to conclude for SLIDER-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSliderValue(java.lang.Number sliderValue) throws G2AccessException;

}
