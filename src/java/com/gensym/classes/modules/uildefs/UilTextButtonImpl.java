/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilTextButtonImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:06 EDT 2007
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

public class UilTextButtonImpl extends com.gensym.classes.modules.uilroot.UilButtonImpl implements UilTextButton {


  static final long serialVersionUID = 2L;
  private static final Symbol LABEL_ = Symbol.intern ("LABEL");
  private static final Symbol UIL_RESIZE_TO_FIT_LABEL_ = Symbol.intern ("UIL-RESIZE-TO-FIT-LABEL");
  private static final Symbol UIL_MINIMUM_HEIGHT_ = Symbol.intern ("UIL-MINIMUM-HEIGHT");
  private static final Symbol UIL_MINIMUM_WIDTH_ = Symbol.intern ("UIL-MINIMUM-WIDTH");

  /* Generated constructors */

  public UilTextButtonImpl() {
    super();
  }

  public UilTextButtonImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilTextButtonImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- LABEL
   * @param label new value to conclude for LABEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setLabel(java.lang.Object label) throws G2AccessException {
    setAttributeValue (LABEL_, label);
  }

  /**
   * Generated Property Getter for attribute -- LABEL
   * @return the value of the LABEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getLabel() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (LABEL_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-RESIZE-TO-FIT-LABEL
   * @param uilResizeToFitLabel new value to conclude for UIL-RESIZE-TO-FIT-LABEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilResizeToFitLabel(boolean uilResizeToFitLabel) throws G2AccessException {
    setAttributeValue (UIL_RESIZE_TO_FIT_LABEL_, new Boolean (uilResizeToFitLabel));
  }

  /**
   * Generated Property Getter for attribute -- UIL-RESIZE-TO-FIT-LABEL
   * @return the value of the UIL-RESIZE-TO-FIT-LABEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getUilResizeToFitLabel() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_RESIZE_TO_FIT_LABEL_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- UIL-MINIMUM-HEIGHT
   * @param uilMinimumHeight new value to conclude for UIL-MINIMUM-HEIGHT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilMinimumHeight(int uilMinimumHeight) throws G2AccessException {
    setAttributeValue (UIL_MINIMUM_HEIGHT_, new Integer (uilMinimumHeight));
  }

  /**
   * Generated Property Getter for attribute -- UIL-MINIMUM-HEIGHT
   * @return the value of the UIL-MINIMUM-HEIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getUilMinimumHeight() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_MINIMUM_HEIGHT_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- UIL-MINIMUM-WIDTH
   * @param uilMinimumWidth new value to conclude for UIL-MINIMUM-WIDTH
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilMinimumWidth(int uilMinimumWidth) throws G2AccessException {
    setAttributeValue (UIL_MINIMUM_WIDTH_, new Integer (uilMinimumWidth));
  }

  /**
   * Generated Property Getter for attribute -- UIL-MINIMUM-WIDTH
   * @return the value of the UIL-MINIMUM-WIDTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getUilMinimumWidth() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_MINIMUM_WIDTH_);
    return ((Integer)retnValue).intValue ();
  }

  // Method Name Constants
  private static final Symbol MethodName_UPP_SET_BUTTON_LABEL_ = Symbol.intern ("UPP-SET-BUTTON-LABEL");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * UIL-TEXT-BUTTON::UPP-SET-BUTTON-LABEL
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-TEXT-BUTTON,arg1:TEXT) = ()
   */
  @Override
  public  void uppSetButtonLabel(java.lang.String arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_UPP_SET_BUTTON_LABEL_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
