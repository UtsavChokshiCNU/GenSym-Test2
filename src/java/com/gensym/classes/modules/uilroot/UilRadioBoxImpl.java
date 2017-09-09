/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilRadioBoxImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:05:35 EDT 2007
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

public class UilRadioBoxImpl extends com.gensym.classes.modules.uilroot.UilSelectionBoxImpl implements UilRadioBox {


  static final long serialVersionUID = 2L;
  private static final Symbol RADIO_BOX_CURRENT_VALUE_ = Symbol.intern ("RADIO-BOX-CURRENT-VALUE");

  /* Generated constructors */

  public UilRadioBoxImpl() {
    super();
  }

  public UilRadioBoxImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilRadioBoxImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- RADIO-BOX-CURRENT-VALUE
   * @param radioBoxCurrentValue new value to conclude for RADIO-BOX-CURRENT-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRadioBoxCurrentValue(java.lang.Object radioBoxCurrentValue) throws G2AccessException {
    setAttributeValue (RADIO_BOX_CURRENT_VALUE_, radioBoxCurrentValue);
  }

  /**
   * Generated Property Getter for attribute -- RADIO-BOX-CURRENT-VALUE
   * @return the value of the RADIO-BOX-CURRENT-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getRadioBoxCurrentValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (RADIO_BOX_CURRENT_VALUE_);
    return (java.lang.Object)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_UPP_EXTRACT_VALUE_FROM_ITEM_ = Symbol.intern ("UPP-EXTRACT-VALUE-FROM-ITEM");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * UIL-RADIO-BOX::UPP-EXTRACT-VALUE-FROM-ITEM
   * @return the return from calling UPP-EXTRACT-VALUE-FROM-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-RADIO-BOX) = (VALUE,TRUTH-VALUE)
   */
  @Override
  public  com.gensym.util.Sequence uppExtractValueFromItem() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_UPP_EXTRACT_VALUE_FROM_ITEM_, args);
      return (com.gensym.util.Sequence)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
