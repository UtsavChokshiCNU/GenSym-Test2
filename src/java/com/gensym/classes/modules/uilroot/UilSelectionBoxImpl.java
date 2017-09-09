/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilSelectionBoxImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:05:34 EDT 2007
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

public class UilSelectionBoxImpl extends com.gensym.classes.modules.uilroot.UilGrobjImpl implements UilSelectionBox {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_BUTTON_ORIENTATION_ = Symbol.intern ("UIL-BUTTON-ORIENTATION");
  private static final Symbol MEMBERS_ = Symbol.intern ("MEMBERS");
  private static final Symbol MEMBERS_INDEX_ = Symbol.intern ("MEMBERS-INDEX");
  private static final Symbol UIL_UPDATE_VALUE_ = Symbol.intern ("UIL-UPDATE-VALUE");
  private static final Symbol STATE_ = Symbol.intern ("STATE");
  private static final Symbol LABEL_ = Symbol.intern ("LABEL");
  private static final Symbol UIL_TEXT_RELATION_ = Symbol.intern ("UIL-TEXT-RELATION");
  private static final Symbol UIL_LABEL_ID_ = Symbol.intern ("UIL-LABEL-ID");
  private static final Symbol UIL_BORDER_X_OFFSET_ = Symbol.intern ("UIL-BORDER-X-OFFSET");
  private static final Symbol UIL_BORDER_Y_OFFSET_ = Symbol.intern ("UIL-BORDER-Y-OFFSET");
  private static final Symbol UIL_BORDER_WIDTH_ = Symbol.intern ("UIL-BORDER-WIDTH");
  private static final Symbol UIL_BORDER_HEIGHT_ = Symbol.intern ("UIL-BORDER-HEIGHT");
  private static final Symbol UIL_LABEL_X_OFFSET_ = Symbol.intern ("UIL-LABEL-X-OFFSET");
  private static final Symbol UIL_LABEL_Y_OFFSET_ = Symbol.intern ("UIL-LABEL-Y-OFFSET");
  private static final Symbol UIL_LABEL_SIZE_ = Symbol.intern ("UIL-LABEL-SIZE");

  /* Generated constructors */

  public UilSelectionBoxImpl() {
    super();
  }

  public UilSelectionBoxImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilSelectionBoxImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-ORIENTATION
   * @param uilButtonOrientation new value to conclude for UIL-BUTTON-ORIENTATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilButtonOrientation(com.gensym.util.Symbol uilButtonOrientation) throws G2AccessException {
    setAttributeValue (UIL_BUTTON_ORIENTATION_, uilButtonOrientation);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-ORIENTATION
   * @return the value of the UIL-BUTTON-ORIENTATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUilButtonOrientation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BUTTON_ORIENTATION_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- MEMBERS
   * @param members new value to conclude for MEMBERS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMembers(java.lang.Object members) throws G2AccessException {
    setAttributeValue (MEMBERS_, members);
  }

  /**
   * Generated Property Getter for attribute -- MEMBERS
   * @return the value of the MEMBERS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getMembers() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (MEMBERS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- MEMBERS-INDEX
   * @param membersIndex new value to conclude for MEMBERS-INDEX
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMembersIndex(java.lang.Object membersIndex) throws G2AccessException {
    setAttributeValue (MEMBERS_INDEX_, membersIndex);
  }

  /**
   * Generated Property Getter for attribute -- MEMBERS-INDEX
   * @return the value of the MEMBERS-INDEX attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getMembersIndex() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (MEMBERS_INDEX_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-UPDATE-VALUE
   * @param uilUpdateValue new value to conclude for UIL-UPDATE-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilUpdateValue(java.lang.Object uilUpdateValue) throws G2AccessException {
    setAttributeValue (UIL_UPDATE_VALUE_, uilUpdateValue);
  }

  /**
   * Generated Property Getter for attribute -- UIL-UPDATE-VALUE
   * @return the value of the UIL-UPDATE-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilUpdateValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_UPDATE_VALUE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- STATE
   * @param state new value to conclude for STATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setState(java.lang.Object state) throws G2AccessException {
    setAttributeValue (STATE_, state);
  }

  /**
   * Generated Property Getter for attribute -- STATE
   * @return the value of the STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getState() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (STATE_);
    return (java.lang.Object)retnValue;
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
   * Generated Property Setter for attribute -- UIL-TEXT-RELATION
   * @param uilTextRelation new value to conclude for UIL-TEXT-RELATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilTextRelation(java.lang.Object uilTextRelation) throws G2AccessException {
    setAttributeValue (UIL_TEXT_RELATION_, uilTextRelation);
  }

  /**
   * Generated Property Getter for attribute -- UIL-TEXT-RELATION
   * @return the value of the UIL-TEXT-RELATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilTextRelation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_TEXT_RELATION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-LABEL-ID
   * @param uilLabelId new value to conclude for UIL-LABEL-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilLabelId(java.lang.Object uilLabelId) throws G2AccessException {
    setAttributeValue (UIL_LABEL_ID_, uilLabelId);
  }

  /**
   * Generated Property Getter for attribute -- UIL-LABEL-ID
   * @return the value of the UIL-LABEL-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilLabelId() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_LABEL_ID_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BORDER-X-OFFSET
   * @param uilBorderXOffset new value to conclude for UIL-BORDER-X-OFFSET
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilBorderXOffset(java.lang.Object uilBorderXOffset) throws G2AccessException {
    setAttributeValue (UIL_BORDER_X_OFFSET_, uilBorderXOffset);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BORDER-X-OFFSET
   * @return the value of the UIL-BORDER-X-OFFSET attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilBorderXOffset() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BORDER_X_OFFSET_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BORDER-Y-OFFSET
   * @param uilBorderYOffset new value to conclude for UIL-BORDER-Y-OFFSET
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilBorderYOffset(java.lang.Object uilBorderYOffset) throws G2AccessException {
    setAttributeValue (UIL_BORDER_Y_OFFSET_, uilBorderYOffset);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BORDER-Y-OFFSET
   * @return the value of the UIL-BORDER-Y-OFFSET attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilBorderYOffset() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BORDER_Y_OFFSET_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BORDER-WIDTH
   * @param uilBorderWidth new value to conclude for UIL-BORDER-WIDTH
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilBorderWidth(java.lang.Object uilBorderWidth) throws G2AccessException {
    setAttributeValue (UIL_BORDER_WIDTH_, uilBorderWidth);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BORDER-WIDTH
   * @return the value of the UIL-BORDER-WIDTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilBorderWidth() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BORDER_WIDTH_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BORDER-HEIGHT
   * @param uilBorderHeight new value to conclude for UIL-BORDER-HEIGHT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilBorderHeight(java.lang.Object uilBorderHeight) throws G2AccessException {
    setAttributeValue (UIL_BORDER_HEIGHT_, uilBorderHeight);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BORDER-HEIGHT
   * @return the value of the UIL-BORDER-HEIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilBorderHeight() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BORDER_HEIGHT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-LABEL-X-OFFSET
   * @param uilLabelXOffset new value to conclude for UIL-LABEL-X-OFFSET
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilLabelXOffset(java.lang.Object uilLabelXOffset) throws G2AccessException {
    setAttributeValue (UIL_LABEL_X_OFFSET_, uilLabelXOffset);
  }

  /**
   * Generated Property Getter for attribute -- UIL-LABEL-X-OFFSET
   * @return the value of the UIL-LABEL-X-OFFSET attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilLabelXOffset() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_LABEL_X_OFFSET_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-LABEL-Y-OFFSET
   * @param uilLabelYOffset new value to conclude for UIL-LABEL-Y-OFFSET
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilLabelYOffset(java.lang.Object uilLabelYOffset) throws G2AccessException {
    setAttributeValue (UIL_LABEL_Y_OFFSET_, uilLabelYOffset);
  }

  /**
   * Generated Property Getter for attribute -- UIL-LABEL-Y-OFFSET
   * @return the value of the UIL-LABEL-Y-OFFSET attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilLabelYOffset() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_LABEL_Y_OFFSET_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-LABEL-SIZE
   * @param uilLabelSize new value to conclude for UIL-LABEL-SIZE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilLabelSize(java.lang.Object uilLabelSize) throws G2AccessException {
    setAttributeValue (UIL_LABEL_SIZE_, uilLabelSize);
  }

  /**
   * Generated Property Getter for attribute -- UIL-LABEL-SIZE
   * @return the value of the UIL-LABEL-SIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilLabelSize() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_LABEL_SIZE_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
