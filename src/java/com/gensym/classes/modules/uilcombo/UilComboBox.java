/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilComboBox.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:07 EDT 2007
 *
 */


package com.gensym.classes.modules.uilcombo;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface UilComboBox extends com.gensym.classes.modules.uillib.UilEditBox {

  public static final Symbol UIL_COMBO_BOX_ = Symbol.intern ("UIL-COMBO-BOX");
  static final Symbol g2ClassName = UIL_COMBO_BOX_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_COMBO_BOX_, UIL_EDIT_BOX_, UIL_GRMES_, UIL_MESSAGE_, MESSAGE_, ITEM_, TEXT_BOX_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-COMBO-BOX-BUTTON-ID
   * @return the value of the UIL-COMBO-BOX-BUTTON-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-COMBO-BOX-BUTTON-ID is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilComboBoxButtonId() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-COMBO-BOX-BUTTON-ID
   * @param uilComboBoxButtonId new value to conclude for UIL-COMBO-BOX-BUTTON-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilComboBoxButtonId(java.lang.Object uilComboBoxButtonId) throws G2AccessException;

}
