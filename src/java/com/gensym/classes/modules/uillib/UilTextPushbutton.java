/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilTextPushbutton.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:14 EDT 2007
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

public interface UilTextPushbutton extends com.gensym.classes.modules.uildefs.UilTextButton {

  public static final Symbol UIL_TEXT_PUSHBUTTON_ = Symbol.intern ("UIL-TEXT-PUSHBUTTON");
  static final Symbol g2ClassName = UIL_TEXT_PUSHBUTTON_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_TEXT_PUSHBUTTON_, UIL_TEXT_BUTTON_, UIL_BUTTON_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- CALLBACK
   * @return the value of the CALLBACK attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CALLBACK is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getCallback() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CALLBACK
   * @param callback new value to conclude for CALLBACK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setCallback(java.lang.Object callback) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DEFAULTED-BUTTON
   * @return the value of the UIL-DEFAULTED-BUTTON attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DEFAULTED-BUTTON is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDefaultedButton() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DEFAULTED-BUTTON
   * @param uilDefaultedButton new value to conclude for UIL-DEFAULTED-BUTTON
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDefaultedButton(java.lang.Object uilDefaultedButton) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-CANCEL-BUTTON
   * @return the value of the UIL-CANCEL-BUTTON attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-CANCEL-BUTTON is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilCancelButton() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-CANCEL-BUTTON
   * @param uilCancelButton new value to conclude for UIL-CANCEL-BUTTON
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilCancelButton(java.lang.Object uilCancelButton) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-UPDATE-BUTTON
   * @return the value of the UIL-UPDATE-BUTTON attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-UPDATE-BUTTON is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilUpdateButton() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-UPDATE-BUTTON
   * @param uilUpdateButton new value to conclude for UIL-UPDATE-BUTTON
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilUpdateButton(java.lang.Object uilUpdateButton) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BUTTON-SELECTION-STATUS
   * @return the value of the UIL-BUTTON-SELECTION-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BUTTON-SELECTION-STATUS is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilButtonSelectionStatus() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BUTTON-SELECTION-STATUS
   * @param uilButtonSelectionStatus new value to conclude for UIL-BUTTON-SELECTION-STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilButtonSelectionStatus(java.lang.Object uilButtonSelectionStatus) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-RELEASE-BUTTON-AFTER-SELECTION
   * @return the value of the UIL-RELEASE-BUTTON-AFTER-SELECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-RELEASE-BUTTON-AFTER-SELECTION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilReleaseButtonAfterSelection() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-RELEASE-BUTTON-AFTER-SELECTION
   * @param uilReleaseButtonAfterSelection new value to conclude for UIL-RELEASE-BUTTON-AFTER-SELECTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilReleaseButtonAfterSelection(java.lang.Object uilReleaseButtonAfterSelection) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ACTION-DESCRIPTION
   * @return the value of the UIL-ACTION-DESCRIPTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ACTION-DESCRIPTION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilActionDescription() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ACTION-DESCRIPTION
   * @param uilActionDescription new value to conclude for UIL-ACTION-DESCRIPTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilActionDescription(java.lang.Object uilActionDescription) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-UPDATE-VALUE
   * @return the value of the UIL-UPDATE-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-UPDATE-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilUpdateValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-UPDATE-VALUE
   * @param uilUpdateValue new value to conclude for UIL-UPDATE-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilUpdateValue(java.lang.Object uilUpdateValue) throws G2AccessException;

}
