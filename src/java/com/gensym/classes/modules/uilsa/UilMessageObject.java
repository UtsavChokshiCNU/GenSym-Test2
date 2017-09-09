/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilMessageObject.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:23 EDT 2007
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

public interface UilMessageObject extends com.gensym.classes.modules.uilroot.UilGrmes {

  public static final Symbol UIL_MESSAGE_OBJECT_ = Symbol.intern ("UIL-MESSAGE-OBJECT");
  static final Symbol g2ClassName = UIL_MESSAGE_OBJECT_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_MESSAGE_OBJECT_, UIL_GRMES_, UIL_MESSAGE_, MESSAGE_, ITEM_, TEXT_BOX_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- MESSAGE-DISPLAY-PRIORITY
   * @return the value of the MESSAGE-DISPLAY-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MESSAGE-DISPLAY-PRIORITY is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getMessageDisplayPriority() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MESSAGE-DISPLAY-PRIORITY
   * @param messageDisplayPriority new value to conclude for MESSAGE-DISPLAY-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMessageDisplayPriority(java.lang.Object messageDisplayPriority) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-CONCLUDE-METHOD
   * @return the value of the UIL-CONCLUDE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-CONCLUDE-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilConcludeMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-CONCLUDE-METHOD
   * @param uilConcludeMethod new value to conclude for UIL-CONCLUDE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilConcludeMethod(java.lang.Object uilConcludeMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-MESSAGE-SELECTION-METHOD
   * @return the value of the UIL-MESSAGE-SELECTION-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-MESSAGE-SELECTION-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilMessageSelectionMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-MESSAGE-SELECTION-METHOD
   * @param uilMessageSelectionMethod new value to conclude for UIL-MESSAGE-SELECTION-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilMessageSelectionMethod(java.lang.Object uilMessageSelectionMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-MESSAGE-UNSELECTION-METHOD
   * @return the value of the UIL-MESSAGE-UNSELECTION-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-MESSAGE-UNSELECTION-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilMessageUnselectionMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-MESSAGE-UNSELECTION-METHOD
   * @param uilMessageUnselectionMethod new value to conclude for UIL-MESSAGE-UNSELECTION-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilMessageUnselectionMethod(java.lang.Object uilMessageUnselectionMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-FORMAT-SPECIFICATION
   * @return the value of the UIL-FORMAT-SPECIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-FORMAT-SPECIFICATION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilFormatSpecification() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-FORMAT-SPECIFICATION
   * @param uilFormatSpecification new value to conclude for UIL-FORMAT-SPECIFICATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilFormatSpecification(java.lang.Object uilFormatSpecification) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-EDIT-STYLE
   * @return the value of the UIL-EDIT-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-EDIT-STYLE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilEditStyle() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-EDIT-STYLE
   * @param uilEditStyle new value to conclude for UIL-EDIT-STYLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilEditStyle(java.lang.Object uilEditStyle) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MESSAGE-CONTENTS
   * @return the value of the MESSAGE-CONTENTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MESSAGE-CONTENTS is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getMessageContents() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MESSAGE-CONTENTS
   * @param messageContents new value to conclude for MESSAGE-CONTENTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMessageContents(java.lang.Object messageContents) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ACTIVATION-STATE
   * @return the value of the UIL-ACTIVATION-STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ACTIVATION-STATE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilActivationState() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ACTIVATION-STATE
   * @param uilActivationState new value to conclude for UIL-ACTIVATION-STATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilActivationState(java.lang.Object uilActivationState) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SAVED-MESSAGE-HEIGHT
   * @return the value of the SAVED-MESSAGE-HEIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SAVED-MESSAGE-HEIGHT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getSavedMessageHeight() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SAVED-MESSAGE-HEIGHT
   * @param savedMessageHeight new value to conclude for SAVED-MESSAGE-HEIGHT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSavedMessageHeight(java.lang.Object savedMessageHeight) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SAVED-MESSAGE-SEQUENCE
   * @return the value of the SAVED-MESSAGE-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SAVED-MESSAGE-SEQUENCE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getSavedMessageSequence() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SAVED-MESSAGE-SEQUENCE
   * @param savedMessageSequence new value to conclude for SAVED-MESSAGE-SEQUENCE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSavedMessageSequence(java.lang.Object savedMessageSequence) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SAVED-SCROLL-AREA-KEY
   * @return the value of the SAVED-SCROLL-AREA-KEY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SAVED-SCROLL-AREA-KEY is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getSavedScrollAreaKey() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SAVED-SCROLL-AREA-KEY
   * @param savedScrollAreaKey new value to conclude for SAVED-SCROLL-AREA-KEY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSavedScrollAreaKey(java.lang.Object savedScrollAreaKey) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-TIME-STAMP
   * @return the value of the UIL-TIME-STAMP attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-TIME-STAMP is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilTimeStamp() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-TIME-STAMP
   * @param uilTimeStamp new value to conclude for UIL-TIME-STAMP
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilTimeStamp(java.lang.Object uilTimeStamp) throws G2AccessException;

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

  /**
   * Generated Property Getter for attribute -- UIL-APPENDED-ITEM-ID
   * @return the value of the UIL-APPENDED-ITEM-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-APPENDED-ITEM-ID is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilAppendedItemId() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-APPENDED-ITEM-ID
   * @param uilAppendedItemId new value to conclude for UIL-APPENDED-ITEM-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilAppendedItemId(java.lang.Object uilAppendedItemId) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-APPENDED-ITEM-X-OFFSET
   * @return the value of the UIL-APPENDED-ITEM-X-OFFSET attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-APPENDED-ITEM-X-OFFSET is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilAppendedItemXOffset() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-APPENDED-ITEM-X-OFFSET
   * @param uilAppendedItemXOffset new value to conclude for UIL-APPENDED-ITEM-X-OFFSET
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilAppendedItemXOffset(java.lang.Object uilAppendedItemXOffset) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * UIL-MESSAGE-OBJECT::UPP-EXTRACT-VALUE-FROM-ITEM
   * @return the return from calling UPP-EXTRACT-VALUE-FROM-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-MESSAGE-OBJECT) = (VALUE,TRUTH-VALUE)
   */
  public  com.gensym.util.Sequence uppExtractValueFromItem() throws G2AccessException;
  
}
