/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilBoxBorderLeft.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:33 EDT 2007
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

public interface UilBoxBorderLeft extends com.gensym.classes.modules.uillib.UilBoxBorder {

  public static final Symbol UIL_BOX_BORDER_LEFT_ = Symbol.intern ("UIL-BOX-BORDER-LEFT");
  static final Symbol g2ClassName = UIL_BOX_BORDER_LEFT_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_BOX_BORDER_LEFT_, UIL_BOX_BORDER_, UIL_BOX_OBJECT_, UIL_EXTENSION_OBJECT_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-BOX-BORDER-MARGIN-LEFT
   * @return the value of the UIL-BOX-BORDER-MARGIN-LEFT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BOX-BORDER-MARGIN-LEFT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilBoxBorderMarginLeft() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BOX-BORDER-MARGIN-LEFT
   * @param uilBoxBorderMarginLeft new value to conclude for UIL-BOX-BORDER-MARGIN-LEFT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilBoxBorderMarginLeft(java.lang.Object uilBoxBorderMarginLeft) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BOX-BORDER-MARGIN-RIGHT
   * @return the value of the UIL-BOX-BORDER-MARGIN-RIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BOX-BORDER-MARGIN-RIGHT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilBoxBorderMarginRight() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BOX-BORDER-MARGIN-RIGHT
   * @param uilBoxBorderMarginRight new value to conclude for UIL-BOX-BORDER-MARGIN-RIGHT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilBoxBorderMarginRight(java.lang.Object uilBoxBorderMarginRight) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BOX-BORDER-MARGIN-TOP
   * @return the value of the UIL-BOX-BORDER-MARGIN-TOP attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BOX-BORDER-MARGIN-TOP is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilBoxBorderMarginTop() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BOX-BORDER-MARGIN-TOP
   * @param uilBoxBorderMarginTop new value to conclude for UIL-BOX-BORDER-MARGIN-TOP
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilBoxBorderMarginTop(java.lang.Object uilBoxBorderMarginTop) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BOX-BORDER-MARGIN-BOTTOM
   * @return the value of the UIL-BOX-BORDER-MARGIN-BOTTOM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BOX-BORDER-MARGIN-BOTTOM is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilBoxBorderMarginBottom() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BOX-BORDER-MARGIN-BOTTOM
   * @param uilBoxBorderMarginBottom new value to conclude for UIL-BOX-BORDER-MARGIN-BOTTOM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilBoxBorderMarginBottom(java.lang.Object uilBoxBorderMarginBottom) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-CORNER-ANCHORED-TO-WORKSPACE
   * @return the value of the UIL-CORNER-ANCHORED-TO-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-CORNER-ANCHORED-TO-WORKSPACE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilCornerAnchoredToWorkspace() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-CORNER-ANCHORED-TO-WORKSPACE
   * @param uilCornerAnchoredToWorkspace new value to conclude for UIL-CORNER-ANCHORED-TO-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilCornerAnchoredToWorkspace(java.lang.Object uilCornerAnchoredToWorkspace) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * UIL-BOX-BORDER-LEFT::GOLD-MAP-ITEM-TO-CONTEXT
   * @return the return from calling GOLD-MAP-ITEM-TO-CONTEXT
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-BOX-BORDER-LEFT,arg1:CLASS UI-CLIENT-ITEM) = (ITEM-OR-VALUE)
   */
  @Override
  public  java.lang.Object goldMapItemToContext(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
}
