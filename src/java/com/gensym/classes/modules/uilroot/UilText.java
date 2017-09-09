/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilText.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:58 EDT 2007
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

public interface UilText extends com.gensym.classes.modules.uilroot.UilGrmes {

  public static final Symbol UIL_TEXT_ = Symbol.intern ("UIL-TEXT");
  static final Symbol g2ClassName = UIL_TEXT_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_TEXT_, UIL_GRMES_, UIL_MESSAGE_, MESSAGE_, ITEM_, TEXT_BOX_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-LABEL-CONSTANT
   * @return the value of the UIL-LABEL-CONSTANT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-LABEL-CONSTANT is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getUilLabelConstant() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-LABEL-CONSTANT
   * @param uilLabelConstant new value to conclude for UIL-LABEL-CONSTANT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilLabelConstant(com.gensym.util.Symbol uilLabelConstant) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-TRANSLATION-CONSTRAINTS
   * @return the value of the UIL-TRANSLATION-CONSTRAINTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-TRANSLATION-CONSTRAINTS is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getUilTranslationConstraints() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-TRANSLATION-CONSTRAINTS
   * @param uilTranslationConstraints new value to conclude for UIL-TRANSLATION-CONSTRAINTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilTranslationConstraints(com.gensym.util.Symbol uilTranslationConstraints) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-LABEL-ID
   * @return the value of the UIL-LABEL-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-LABEL-ID is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilLabelId() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-LABEL-ID
   * @param uilLabelId new value to conclude for UIL-LABEL-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilLabelId(java.lang.Object uilLabelId) throws G2AccessException;

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
   * Generated Property Getter for attribute -- UIL-STAND-ALONE-TEXT
   * @return the value of the UIL-STAND-ALONE-TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-STAND-ALONE-TEXT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilStandAloneText() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-STAND-ALONE-TEXT
   * @param uilStandAloneText new value to conclude for UIL-STAND-ALONE-TEXT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilStandAloneText(java.lang.Object uilStandAloneText) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BORDER-RELATION
   * @return the value of the UIL-BORDER-RELATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BORDER-RELATION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilBorderRelation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BORDER-RELATION
   * @param uilBorderRelation new value to conclude for UIL-BORDER-RELATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilBorderRelation(java.lang.Object uilBorderRelation) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-BORDER-ID
   * @return the value of the UIL-BORDER-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-BORDER-ID is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilBorderId() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-BORDER-ID
   * @param uilBorderId new value to conclude for UIL-BORDER-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilBorderId(java.lang.Object uilBorderId) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- STATE
   * @return the value of the STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for STATE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getState() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- STATE
   * @param state new value to conclude for STATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setState(java.lang.Object state) throws G2AccessException;

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
   * Auto Generated method for G2 Method
   * UIL-TEXT::UPP-EXTRACT-VALUE-FROM-ITEM
   * @return the return from calling UPP-EXTRACT-VALUE-FROM-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-TEXT) = (VALUE,TRUTH-VALUE)
   */
  public  com.gensym.util.Sequence uppExtractValueFromItem() throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * UIL-TEXT::GOLD-MAP-ITEM-TO-CONTEXT
   * @return the return from calling GOLD-MAP-ITEM-TO-CONTEXT
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-TEXT,arg1:CLASS UI-CLIENT-ITEM) = (ITEM-OR-VALUE)
   */
  @Override
  public  java.lang.Object goldMapItemToContext(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
}
