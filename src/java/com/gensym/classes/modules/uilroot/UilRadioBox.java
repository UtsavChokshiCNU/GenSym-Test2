/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilRadioBox.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:05:28 EDT 2007
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

public interface UilRadioBox extends com.gensym.classes.modules.uilroot.UilSelectionBox {

  public static final Symbol UIL_RADIO_BOX_ = Symbol.intern ("UIL-RADIO-BOX");
  static final Symbol g2ClassName = UIL_RADIO_BOX_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_RADIO_BOX_, UIL_SELECTION_BOX_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- RADIO-BOX-CURRENT-VALUE
   * @return the value of the RADIO-BOX-CURRENT-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for RADIO-BOX-CURRENT-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getRadioBoxCurrentValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- RADIO-BOX-CURRENT-VALUE
   * @param radioBoxCurrentValue new value to conclude for RADIO-BOX-CURRENT-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRadioBoxCurrentValue(java.lang.Object radioBoxCurrentValue) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * UIL-RADIO-BOX::UPP-EXTRACT-VALUE-FROM-ITEM
   * @return the return from calling UPP-EXTRACT-VALUE-FROM-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-RADIO-BOX) = (VALUE,TRUTH-VALUE)
   */
  public  com.gensym.util.Sequence uppExtractValueFromItem() throws G2AccessException;
  
}
