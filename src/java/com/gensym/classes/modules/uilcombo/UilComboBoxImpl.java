/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilComboBoxImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:09 EDT 2007
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

public class UilComboBoxImpl extends com.gensym.classes.modules.uillib.UilEditBoxImpl implements UilComboBox {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_COMBO_BOX_BUTTON_ID_ = Symbol.intern ("UIL-COMBO-BOX-BUTTON-ID");

  /* Generated constructors */

  public UilComboBoxImpl() {
    super();
  }

  public UilComboBoxImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilComboBoxImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-COMBO-BOX-BUTTON-ID
   * @param uilComboBoxButtonId new value to conclude for UIL-COMBO-BOX-BUTTON-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilComboBoxButtonId(java.lang.Object uilComboBoxButtonId) throws G2AccessException {
    setAttributeValue (UIL_COMBO_BOX_BUTTON_ID_, uilComboBoxButtonId);
  }

  /**
   * Generated Property Getter for attribute -- UIL-COMBO-BOX-BUTTON-ID
   * @return the value of the UIL-COMBO-BOX-BUTTON-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilComboBoxButtonId() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_COMBO_BOX_BUTTON_ID_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
