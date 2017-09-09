/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilBoxBorderLeftImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:38 EDT 2007
 *
 */


package com.gensym.classes.modules.uillib;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class UilBoxBorderLeftImpl extends com.gensym.classes.modules.uillib.UilBoxBorderImpl implements UilBoxBorderLeft {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_BOX_BORDER_MARGIN_LEFT_ = Symbol.intern ("UIL-BOX-BORDER-MARGIN-LEFT");
  private static final Symbol UIL_BOX_BORDER_MARGIN_RIGHT_ = Symbol.intern ("UIL-BOX-BORDER-MARGIN-RIGHT");
  private static final Symbol UIL_BOX_BORDER_MARGIN_TOP_ = Symbol.intern ("UIL-BOX-BORDER-MARGIN-TOP");
  private static final Symbol UIL_BOX_BORDER_MARGIN_BOTTOM_ = Symbol.intern ("UIL-BOX-BORDER-MARGIN-BOTTOM");
  private static final Symbol UIL_CORNER_ANCHORED_TO_WORKSPACE_ = Symbol.intern ("UIL-CORNER-ANCHORED-TO-WORKSPACE");

  /* Generated constructors */

  public UilBoxBorderLeftImpl() {
    super();
  }

  public UilBoxBorderLeftImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilBoxBorderLeftImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-BOX-BORDER-MARGIN-LEFT
   * @param uilBoxBorderMarginLeft new value to conclude for UIL-BOX-BORDER-MARGIN-LEFT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilBoxBorderMarginLeft(java.lang.Object uilBoxBorderMarginLeft) throws G2AccessException {
    setAttributeValue (UIL_BOX_BORDER_MARGIN_LEFT_, uilBoxBorderMarginLeft);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BOX-BORDER-MARGIN-LEFT
   * @return the value of the UIL-BOX-BORDER-MARGIN-LEFT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilBoxBorderMarginLeft() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BOX_BORDER_MARGIN_LEFT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BOX-BORDER-MARGIN-RIGHT
   * @param uilBoxBorderMarginRight new value to conclude for UIL-BOX-BORDER-MARGIN-RIGHT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilBoxBorderMarginRight(java.lang.Object uilBoxBorderMarginRight) throws G2AccessException {
    setAttributeValue (UIL_BOX_BORDER_MARGIN_RIGHT_, uilBoxBorderMarginRight);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BOX-BORDER-MARGIN-RIGHT
   * @return the value of the UIL-BOX-BORDER-MARGIN-RIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilBoxBorderMarginRight() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BOX_BORDER_MARGIN_RIGHT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BOX-BORDER-MARGIN-TOP
   * @param uilBoxBorderMarginTop new value to conclude for UIL-BOX-BORDER-MARGIN-TOP
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilBoxBorderMarginTop(java.lang.Object uilBoxBorderMarginTop) throws G2AccessException {
    setAttributeValue (UIL_BOX_BORDER_MARGIN_TOP_, uilBoxBorderMarginTop);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BOX-BORDER-MARGIN-TOP
   * @return the value of the UIL-BOX-BORDER-MARGIN-TOP attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilBoxBorderMarginTop() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BOX_BORDER_MARGIN_TOP_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BOX-BORDER-MARGIN-BOTTOM
   * @param uilBoxBorderMarginBottom new value to conclude for UIL-BOX-BORDER-MARGIN-BOTTOM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilBoxBorderMarginBottom(java.lang.Object uilBoxBorderMarginBottom) throws G2AccessException {
    setAttributeValue (UIL_BOX_BORDER_MARGIN_BOTTOM_, uilBoxBorderMarginBottom);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BOX-BORDER-MARGIN-BOTTOM
   * @return the value of the UIL-BOX-BORDER-MARGIN-BOTTOM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilBoxBorderMarginBottom() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BOX_BORDER_MARGIN_BOTTOM_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-CORNER-ANCHORED-TO-WORKSPACE
   * @param uilCornerAnchoredToWorkspace new value to conclude for UIL-CORNER-ANCHORED-TO-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilCornerAnchoredToWorkspace(java.lang.Object uilCornerAnchoredToWorkspace) throws G2AccessException {
    setAttributeValue (UIL_CORNER_ANCHORED_TO_WORKSPACE_, uilCornerAnchoredToWorkspace);
  }

  /**
   * Generated Property Getter for attribute -- UIL-CORNER-ANCHORED-TO-WORKSPACE
   * @return the value of the UIL-CORNER-ANCHORED-TO-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilCornerAnchoredToWorkspace() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_CORNER_ANCHORED_TO_WORKSPACE_);
    return (java.lang.Object)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_GOLD_MAP_ITEM_TO_CONTEXT_ = Symbol.intern ("GOLD-MAP-ITEM-TO-CONTEXT");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * UIL-BOX-BORDER-LEFT::GOLD-MAP-ITEM-TO-CONTEXT
   * @return the return from calling GOLD-MAP-ITEM-TO-CONTEXT
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-BOX-BORDER-LEFT,arg1:CLASS UI-CLIENT-ITEM) = (ITEM-OR-VALUE)
   */
  @Override
  public  java.lang.Object goldMapItemToContext(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GOLD_MAP_ITEM_TO_CONTEXT_, args);
      return (java.lang.Object)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
