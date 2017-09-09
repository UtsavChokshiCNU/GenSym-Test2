/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilMessageObjectImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:24 EDT 2007
 *
 */


package com.gensym.classes.modules.uilsa;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class UilMessageObjectImpl extends com.gensym.classes.modules.uilroot.UilGrmesImpl implements UilMessageObject {


  static final long serialVersionUID = 2L;
  private static final Symbol MESSAGE_DISPLAY_PRIORITY_ = Symbol.intern ("MESSAGE-DISPLAY-PRIORITY");
  private static final Symbol UIL_CONCLUDE_METHOD_ = Symbol.intern ("UIL-CONCLUDE-METHOD");
  private static final Symbol UIL_MESSAGE_SELECTION_METHOD_ = Symbol.intern ("UIL-MESSAGE-SELECTION-METHOD");
  private static final Symbol UIL_MESSAGE_UNSELECTION_METHOD_ = Symbol.intern ("UIL-MESSAGE-UNSELECTION-METHOD");
  private static final Symbol UIL_FORMAT_SPECIFICATION_ = Symbol.intern ("UIL-FORMAT-SPECIFICATION");
  private static final Symbol UIL_EDIT_STYLE_ = Symbol.intern ("UIL-EDIT-STYLE");
  private static final Symbol MESSAGE_CONTENTS_ = Symbol.intern ("MESSAGE-CONTENTS");
  private static final Symbol UIL_ACTIVATION_STATE_ = Symbol.intern ("UIL-ACTIVATION-STATE");
  private static final Symbol SAVED_MESSAGE_HEIGHT_ = Symbol.intern ("SAVED-MESSAGE-HEIGHT");
  private static final Symbol SAVED_MESSAGE_SEQUENCE_ = Symbol.intern ("SAVED-MESSAGE-SEQUENCE");
  private static final Symbol SAVED_SCROLL_AREA_KEY_ = Symbol.intern ("SAVED-SCROLL-AREA-KEY");
  private static final Symbol UIL_TIME_STAMP_ = Symbol.intern ("UIL-TIME-STAMP");
  private static final Symbol UIL_UPDATE_VALUE_ = Symbol.intern ("UIL-UPDATE-VALUE");
  private static final Symbol UIL_APPENDED_ITEM_ID_ = Symbol.intern ("UIL-APPENDED-ITEM-ID");
  private static final Symbol UIL_APPENDED_ITEM_X_OFFSET_ = Symbol.intern ("UIL-APPENDED-ITEM-X-OFFSET");

  /* Generated constructors */

  public UilMessageObjectImpl() {
    super();
  }

  public UilMessageObjectImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilMessageObjectImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- MESSAGE-DISPLAY-PRIORITY
   * @param messageDisplayPriority new value to conclude for MESSAGE-DISPLAY-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMessageDisplayPriority(java.lang.Object messageDisplayPriority) throws G2AccessException {
    setAttributeValue (MESSAGE_DISPLAY_PRIORITY_, messageDisplayPriority);
  }

  /**
   * Generated Property Getter for attribute -- MESSAGE-DISPLAY-PRIORITY
   * @return the value of the MESSAGE-DISPLAY-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getMessageDisplayPriority() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (MESSAGE_DISPLAY_PRIORITY_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-CONCLUDE-METHOD
   * @param uilConcludeMethod new value to conclude for UIL-CONCLUDE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilConcludeMethod(java.lang.Object uilConcludeMethod) throws G2AccessException {
    setAttributeValue (UIL_CONCLUDE_METHOD_, uilConcludeMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-CONCLUDE-METHOD
   * @return the value of the UIL-CONCLUDE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilConcludeMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_CONCLUDE_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-MESSAGE-SELECTION-METHOD
   * @param uilMessageSelectionMethod new value to conclude for UIL-MESSAGE-SELECTION-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilMessageSelectionMethod(java.lang.Object uilMessageSelectionMethod) throws G2AccessException {
    setAttributeValue (UIL_MESSAGE_SELECTION_METHOD_, uilMessageSelectionMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-MESSAGE-SELECTION-METHOD
   * @return the value of the UIL-MESSAGE-SELECTION-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilMessageSelectionMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_MESSAGE_SELECTION_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-MESSAGE-UNSELECTION-METHOD
   * @param uilMessageUnselectionMethod new value to conclude for UIL-MESSAGE-UNSELECTION-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilMessageUnselectionMethod(java.lang.Object uilMessageUnselectionMethod) throws G2AccessException {
    setAttributeValue (UIL_MESSAGE_UNSELECTION_METHOD_, uilMessageUnselectionMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-MESSAGE-UNSELECTION-METHOD
   * @return the value of the UIL-MESSAGE-UNSELECTION-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilMessageUnselectionMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_MESSAGE_UNSELECTION_METHOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-FORMAT-SPECIFICATION
   * @param uilFormatSpecification new value to conclude for UIL-FORMAT-SPECIFICATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilFormatSpecification(java.lang.Object uilFormatSpecification) throws G2AccessException {
    setAttributeValue (UIL_FORMAT_SPECIFICATION_, uilFormatSpecification);
  }

  /**
   * Generated Property Getter for attribute -- UIL-FORMAT-SPECIFICATION
   * @return the value of the UIL-FORMAT-SPECIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilFormatSpecification() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_FORMAT_SPECIFICATION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-EDIT-STYLE
   * @param uilEditStyle new value to conclude for UIL-EDIT-STYLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilEditStyle(java.lang.Object uilEditStyle) throws G2AccessException {
    setAttributeValue (UIL_EDIT_STYLE_, uilEditStyle);
  }

  /**
   * Generated Property Getter for attribute -- UIL-EDIT-STYLE
   * @return the value of the UIL-EDIT-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilEditStyle() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_EDIT_STYLE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- MESSAGE-CONTENTS
   * @param messageContents new value to conclude for MESSAGE-CONTENTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMessageContents(java.lang.Object messageContents) throws G2AccessException {
    setAttributeValue (MESSAGE_CONTENTS_, messageContents);
  }

  /**
   * Generated Property Getter for attribute -- MESSAGE-CONTENTS
   * @return the value of the MESSAGE-CONTENTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getMessageContents() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (MESSAGE_CONTENTS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-ACTIVATION-STATE
   * @param uilActivationState new value to conclude for UIL-ACTIVATION-STATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilActivationState(java.lang.Object uilActivationState) throws G2AccessException {
    setAttributeValue (UIL_ACTIVATION_STATE_, uilActivationState);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ACTIVATION-STATE
   * @return the value of the UIL-ACTIVATION-STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilActivationState() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ACTIVATION_STATE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SAVED-MESSAGE-HEIGHT
   * @param savedMessageHeight new value to conclude for SAVED-MESSAGE-HEIGHT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSavedMessageHeight(java.lang.Object savedMessageHeight) throws G2AccessException {
    setAttributeValue (SAVED_MESSAGE_HEIGHT_, savedMessageHeight);
  }

  /**
   * Generated Property Getter for attribute -- SAVED-MESSAGE-HEIGHT
   * @return the value of the SAVED-MESSAGE-HEIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getSavedMessageHeight() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SAVED_MESSAGE_HEIGHT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SAVED-MESSAGE-SEQUENCE
   * @param savedMessageSequence new value to conclude for SAVED-MESSAGE-SEQUENCE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSavedMessageSequence(java.lang.Object savedMessageSequence) throws G2AccessException {
    setAttributeValue (SAVED_MESSAGE_SEQUENCE_, savedMessageSequence);
  }

  /**
   * Generated Property Getter for attribute -- SAVED-MESSAGE-SEQUENCE
   * @return the value of the SAVED-MESSAGE-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getSavedMessageSequence() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SAVED_MESSAGE_SEQUENCE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SAVED-SCROLL-AREA-KEY
   * @param savedScrollAreaKey new value to conclude for SAVED-SCROLL-AREA-KEY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSavedScrollAreaKey(java.lang.Object savedScrollAreaKey) throws G2AccessException {
    setAttributeValue (SAVED_SCROLL_AREA_KEY_, savedScrollAreaKey);
  }

  /**
   * Generated Property Getter for attribute -- SAVED-SCROLL-AREA-KEY
   * @return the value of the SAVED-SCROLL-AREA-KEY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getSavedScrollAreaKey() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SAVED_SCROLL_AREA_KEY_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-TIME-STAMP
   * @param uilTimeStamp new value to conclude for UIL-TIME-STAMP
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilTimeStamp(java.lang.Object uilTimeStamp) throws G2AccessException {
    setAttributeValue (UIL_TIME_STAMP_, uilTimeStamp);
  }

  /**
   * Generated Property Getter for attribute -- UIL-TIME-STAMP
   * @return the value of the UIL-TIME-STAMP attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilTimeStamp() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_TIME_STAMP_);
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
   * Generated Property Setter for attribute -- UIL-APPENDED-ITEM-ID
   * @param uilAppendedItemId new value to conclude for UIL-APPENDED-ITEM-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilAppendedItemId(java.lang.Object uilAppendedItemId) throws G2AccessException {
    setAttributeValue (UIL_APPENDED_ITEM_ID_, uilAppendedItemId);
  }

  /**
   * Generated Property Getter for attribute -- UIL-APPENDED-ITEM-ID
   * @return the value of the UIL-APPENDED-ITEM-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilAppendedItemId() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_APPENDED_ITEM_ID_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-APPENDED-ITEM-X-OFFSET
   * @param uilAppendedItemXOffset new value to conclude for UIL-APPENDED-ITEM-X-OFFSET
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilAppendedItemXOffset(java.lang.Object uilAppendedItemXOffset) throws G2AccessException {
    setAttributeValue (UIL_APPENDED_ITEM_X_OFFSET_, uilAppendedItemXOffset);
  }

  /**
   * Generated Property Getter for attribute -- UIL-APPENDED-ITEM-X-OFFSET
   * @return the value of the UIL-APPENDED-ITEM-X-OFFSET attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilAppendedItemXOffset() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_APPENDED_ITEM_X_OFFSET_);
    return (java.lang.Object)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_UPP_EXTRACT_VALUE_FROM_ITEM_ = Symbol.intern ("UPP-EXTRACT-VALUE-FROM-ITEM");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * UIL-MESSAGE-OBJECT::UPP-EXTRACT-VALUE-FROM-ITEM
   * @return the return from calling UPP-EXTRACT-VALUE-FROM-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-MESSAGE-OBJECT) = (VALUE,TRUTH-VALUE)
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
