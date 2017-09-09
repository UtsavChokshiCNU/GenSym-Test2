/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilTextPushbuttonImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:15 EDT 2007
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

public class UilTextPushbuttonImpl extends com.gensym.classes.modules.uildefs.UilTextButtonImpl implements UilTextPushbutton {


  static final long serialVersionUID = 2L;
  private static final Symbol CALLBACK_ = Symbol.intern ("CALLBACK");
  private static final Symbol UIL_DEFAULTED_BUTTON_ = Symbol.intern ("UIL-DEFAULTED-BUTTON");
  private static final Symbol UIL_CANCEL_BUTTON_ = Symbol.intern ("UIL-CANCEL-BUTTON");
  private static final Symbol UIL_UPDATE_BUTTON_ = Symbol.intern ("UIL-UPDATE-BUTTON");
  private static final Symbol UIL_BUTTON_SELECTION_STATUS_ = Symbol.intern ("UIL-BUTTON-SELECTION-STATUS");
  private static final Symbol UIL_RELEASE_BUTTON_AFTER_SELECTION_ = Symbol.intern ("UIL-RELEASE-BUTTON-AFTER-SELECTION");
  private static final Symbol UIL_ACTION_DESCRIPTION_ = Symbol.intern ("UIL-ACTION-DESCRIPTION");
  private static final Symbol UIL_UPDATE_VALUE_ = Symbol.intern ("UIL-UPDATE-VALUE");

  /* Generated constructors */

  public UilTextPushbuttonImpl() {
    super();
  }

  public UilTextPushbuttonImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilTextPushbuttonImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- CALLBACK
   * @param callback new value to conclude for CALLBACK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setCallback(java.lang.Object callback) throws G2AccessException {
    setAttributeValue (CALLBACK_, callback);
  }

  /**
   * Generated Property Getter for attribute -- CALLBACK
   * @return the value of the CALLBACK attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getCallback() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (CALLBACK_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-DEFAULTED-BUTTON
   * @param uilDefaultedButton new value to conclude for UIL-DEFAULTED-BUTTON
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilDefaultedButton(java.lang.Object uilDefaultedButton) throws G2AccessException {
    setAttributeValue (UIL_DEFAULTED_BUTTON_, uilDefaultedButton);
  }

  /**
   * Generated Property Getter for attribute -- UIL-DEFAULTED-BUTTON
   * @return the value of the UIL-DEFAULTED-BUTTON attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilDefaultedButton() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_DEFAULTED_BUTTON_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-CANCEL-BUTTON
   * @param uilCancelButton new value to conclude for UIL-CANCEL-BUTTON
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilCancelButton(java.lang.Object uilCancelButton) throws G2AccessException {
    setAttributeValue (UIL_CANCEL_BUTTON_, uilCancelButton);
  }

  /**
   * Generated Property Getter for attribute -- UIL-CANCEL-BUTTON
   * @return the value of the UIL-CANCEL-BUTTON attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilCancelButton() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_CANCEL_BUTTON_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-UPDATE-BUTTON
   * @param uilUpdateButton new value to conclude for UIL-UPDATE-BUTTON
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilUpdateButton(java.lang.Object uilUpdateButton) throws G2AccessException {
    setAttributeValue (UIL_UPDATE_BUTTON_, uilUpdateButton);
  }

  /**
   * Generated Property Getter for attribute -- UIL-UPDATE-BUTTON
   * @return the value of the UIL-UPDATE-BUTTON attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilUpdateButton() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_UPDATE_BUTTON_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-SELECTION-STATUS
   * @param uilButtonSelectionStatus new value to conclude for UIL-BUTTON-SELECTION-STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilButtonSelectionStatus(java.lang.Object uilButtonSelectionStatus) throws G2AccessException {
    setAttributeValue (UIL_BUTTON_SELECTION_STATUS_, uilButtonSelectionStatus);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-SELECTION-STATUS
   * @return the value of the UIL-BUTTON-SELECTION-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilButtonSelectionStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BUTTON_SELECTION_STATUS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-RELEASE-BUTTON-AFTER-SELECTION
   * @param uilReleaseButtonAfterSelection new value to conclude for UIL-RELEASE-BUTTON-AFTER-SELECTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilReleaseButtonAfterSelection(java.lang.Object uilReleaseButtonAfterSelection) throws G2AccessException {
    setAttributeValue (UIL_RELEASE_BUTTON_AFTER_SELECTION_, uilReleaseButtonAfterSelection);
  }

  /**
   * Generated Property Getter for attribute -- UIL-RELEASE-BUTTON-AFTER-SELECTION
   * @return the value of the UIL-RELEASE-BUTTON-AFTER-SELECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilReleaseButtonAfterSelection() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_RELEASE_BUTTON_AFTER_SELECTION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-ACTION-DESCRIPTION
   * @param uilActionDescription new value to conclude for UIL-ACTION-DESCRIPTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilActionDescription(java.lang.Object uilActionDescription) throws G2AccessException {
    setAttributeValue (UIL_ACTION_DESCRIPTION_, uilActionDescription);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ACTION-DESCRIPTION
   * @return the value of the UIL-ACTION-DESCRIPTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilActionDescription() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ACTION_DESCRIPTION_);
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

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
