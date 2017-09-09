/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilTextImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:03 EDT 2007
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

public class UilTextImpl extends com.gensym.classes.modules.uilroot.UilGrmesImpl implements UilText {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_LABEL_CONSTANT_ = Symbol.intern ("UIL-LABEL-CONSTANT");
  private static final Symbol UIL_TRANSLATION_CONSTRAINTS_ = Symbol.intern ("UIL-TRANSLATION-CONSTRAINTS");
  private static final Symbol UIL_LABEL_ID_ = Symbol.intern ("UIL-LABEL-ID");
  private static final Symbol UIL_FORMAT_SPECIFICATION_ = Symbol.intern ("UIL-FORMAT-SPECIFICATION");
  private static final Symbol UIL_STAND_ALONE_TEXT_ = Symbol.intern ("UIL-STAND-ALONE-TEXT");
  private static final Symbol UIL_BORDER_RELATION_ = Symbol.intern ("UIL-BORDER-RELATION");
  private static final Symbol UIL_BORDER_ID_ = Symbol.intern ("UIL-BORDER-ID");
  private static final Symbol STATE_ = Symbol.intern ("STATE");
  private static final Symbol MESSAGE_CONTENTS_ = Symbol.intern ("MESSAGE-CONTENTS");
  private static final Symbol UIL_UPDATE_VALUE_ = Symbol.intern ("UIL-UPDATE-VALUE");

  /* Generated constructors */

  public UilTextImpl() {
    super();
  }

  public UilTextImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilTextImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-LABEL-CONSTANT
   * @param uilLabelConstant new value to conclude for UIL-LABEL-CONSTANT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilLabelConstant(com.gensym.util.Symbol uilLabelConstant) throws G2AccessException {
    setAttributeValue (UIL_LABEL_CONSTANT_, uilLabelConstant);
  }

  /**
   * Generated Property Getter for attribute -- UIL-LABEL-CONSTANT
   * @return the value of the UIL-LABEL-CONSTANT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUilLabelConstant() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_LABEL_CONSTANT_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-TRANSLATION-CONSTRAINTS
   * @param uilTranslationConstraints new value to conclude for UIL-TRANSLATION-CONSTRAINTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilTranslationConstraints(com.gensym.util.Symbol uilTranslationConstraints) throws G2AccessException {
    setAttributeValue (UIL_TRANSLATION_CONSTRAINTS_, uilTranslationConstraints);
  }

  /**
   * Generated Property Getter for attribute -- UIL-TRANSLATION-CONSTRAINTS
   * @return the value of the UIL-TRANSLATION-CONSTRAINTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getUilTranslationConstraints() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_TRANSLATION_CONSTRAINTS_);
    return (com.gensym.util.Symbol)retnValue;
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
   * Generated Property Setter for attribute -- UIL-STAND-ALONE-TEXT
   * @param uilStandAloneText new value to conclude for UIL-STAND-ALONE-TEXT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilStandAloneText(java.lang.Object uilStandAloneText) throws G2AccessException {
    setAttributeValue (UIL_STAND_ALONE_TEXT_, uilStandAloneText);
  }

  /**
   * Generated Property Getter for attribute -- UIL-STAND-ALONE-TEXT
   * @return the value of the UIL-STAND-ALONE-TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilStandAloneText() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_STAND_ALONE_TEXT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BORDER-RELATION
   * @param uilBorderRelation new value to conclude for UIL-BORDER-RELATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilBorderRelation(java.lang.Object uilBorderRelation) throws G2AccessException {
    setAttributeValue (UIL_BORDER_RELATION_, uilBorderRelation);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BORDER-RELATION
   * @return the value of the UIL-BORDER-RELATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilBorderRelation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BORDER_RELATION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-BORDER-ID
   * @param uilBorderId new value to conclude for UIL-BORDER-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilBorderId(java.lang.Object uilBorderId) throws G2AccessException {
    setAttributeValue (UIL_BORDER_ID_, uilBorderId);
  }

  /**
   * Generated Property Getter for attribute -- UIL-BORDER-ID
   * @return the value of the UIL-BORDER-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilBorderId() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_BORDER_ID_);
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

  // Method Name Constants
  private static final Symbol MethodName_UPP_EXTRACT_VALUE_FROM_ITEM_ = Symbol.intern ("UPP-EXTRACT-VALUE-FROM-ITEM");
  private static final Symbol MethodName_GOLD_MAP_ITEM_TO_CONTEXT_ = Symbol.intern ("GOLD-MAP-ITEM-TO-CONTEXT");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * UIL-TEXT::UPP-EXTRACT-VALUE-FROM-ITEM
   * @return the return from calling UPP-EXTRACT-VALUE-FROM-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-TEXT) = (VALUE,TRUTH-VALUE)
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
  
  /**
   * Auto Generated method for G2 Method
   * UIL-TEXT::GOLD-MAP-ITEM-TO-CONTEXT
   * @return the return from calling GOLD-MAP-ITEM-TO-CONTEXT
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-TEXT,arg1:CLASS UI-CLIENT-ITEM) = (ITEM-OR-VALUE)
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
