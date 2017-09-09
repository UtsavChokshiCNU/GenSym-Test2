/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilButtonImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:14:39 EDT 2007
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

public class UilButtonImpl extends com.gensym.classes.modules.uilroot.UilGrobjImpl implements UilButton {


  static final long serialVersionUID = 2L;
  private static final Symbol STATE_ = Symbol.intern ("STATE");
  private static final Symbol UIL_HANDLER_METHOD_ = Symbol.intern ("UIL-HANDLER-METHOD");
  private static final Symbol UIL_TEXT_RELATION_ = Symbol.intern ("UIL-TEXT-RELATION");
  private static final Symbol UIL_LABEL_ID_ = Symbol.intern ("UIL-LABEL-ID");
  private static final Symbol UIL_LABEL_SIZE_ = Symbol.intern ("UIL-LABEL-SIZE");
  private static final Symbol UIL_LABEL_CONSTANT_ = Symbol.intern ("UIL-LABEL-CONSTANT");
  private static final Symbol UIL_TRANSLATION_CONSTRAINTS_ = Symbol.intern ("UIL-TRANSLATION-CONSTRAINTS");
  private static final Symbol UIL_IS_DIALOG_BUTTON_ = Symbol.intern ("UIL-IS-DIALOG-BUTTON");
  private static final Symbol UIL_SHORT_DESCRIPTION_ = Symbol.intern ("UIL-SHORT-DESCRIPTION");

  /* Generated constructors */

  public UilButtonImpl() {
    super();
  }

  public UilButtonImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilButtonImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
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
   * Generated Property Setter for attribute -- UIL-HANDLER-METHOD
   * @param uilHandlerMethod new value to conclude for UIL-HANDLER-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilHandlerMethod(java.lang.Object uilHandlerMethod) throws G2AccessException {
    setAttributeValue (UIL_HANDLER_METHOD_, uilHandlerMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-HANDLER-METHOD
   * @return the value of the UIL-HANDLER-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilHandlerMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_HANDLER_METHOD_);
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
   * Generated Property Setter for attribute -- UIL-IS-DIALOG-BUTTON
   * @param uilIsDialogButton new value to conclude for UIL-IS-DIALOG-BUTTON
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilIsDialogButton(java.lang.Object uilIsDialogButton) throws G2AccessException {
    setAttributeValue (UIL_IS_DIALOG_BUTTON_, uilIsDialogButton);
  }

  /**
   * Generated Property Getter for attribute -- UIL-IS-DIALOG-BUTTON
   * @return the value of the UIL-IS-DIALOG-BUTTON attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilIsDialogButton() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_IS_DIALOG_BUTTON_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-SHORT-DESCRIPTION
   * @param uilShortDescription new value to conclude for UIL-SHORT-DESCRIPTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilShortDescription(java.lang.Object uilShortDescription) throws G2AccessException {
    setAttributeValue (UIL_SHORT_DESCRIPTION_, uilShortDescription);
  }

  /**
   * Generated Property Getter for attribute -- UIL-SHORT-DESCRIPTION
   * @return the value of the UIL-SHORT-DESCRIPTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilShortDescription() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_SHORT_DESCRIPTION_);
    return (java.lang.Object)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_UPP_UPDATE_BUTTON_LABEL_ = Symbol.intern ("UPP-UPDATE-BUTTON-LABEL");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * UIL-BUTTON::UPP-UPDATE-BUTTON-LABEL
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-BUTTON) = ()
   */
  @Override
  public  void uppUpdateButtonLabel() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_UPP_UPDATE_BUTTON_LABEL_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
