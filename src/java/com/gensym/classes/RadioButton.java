/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      RadioButton.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:05:34 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface RadioButton extends com.gensym.classes.Item, com.gensym.classes.OnOffSwitch {

  public static final Symbol RADIO_BUTTON_ = com.gensym.util.symbol.G2ClassSymbols.RADIO_BUTTON_;
  static final Symbol g2ClassName = RADIO_BUTTON_;
  static final Symbol[] classInheritancePath = new Symbol[] {RADIO_BUTTON_, ITEM_, ON_OFF_SWITCH_, NON_ACTION_BUTTON_, BUTTON_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- ON-VALUE
   * @return the value of the ON-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ON-VALUE is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text
      (Sequence)
      (Structure))
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
   * Generated Property Getter for attribute -- BUTTON-STATUS
   * @return the value of the BUTTON-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for BUTTON-STATUS is : 
   * (OR NoItem
      (MEMBER ON OFF))
   *
   */
  public com.gensym.util.Symbol getButtonStatus() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- BUTTON-STATUS
   * @param buttonStatus new value to conclude for BUTTON-STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setButtonStatus(com.gensym.util.Symbol buttonStatus) throws G2AccessException;

}
