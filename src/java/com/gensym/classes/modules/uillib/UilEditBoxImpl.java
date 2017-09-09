/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilEditBoxImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:08 EDT 2007
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

public class UilEditBoxImpl extends com.gensym.classes.modules.uilroot.UilGrmesImpl implements UilEditBox {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_EDIT_STYLE_ = Symbol.intern ("UIL-EDIT-STYLE");
  private static final Symbol UIL_VALIDATE_VALUE_IMMEDIATELY_ = Symbol.intern ("UIL-VALIDATE-VALUE-IMMEDIATELY");
  private static final Symbol UIL_ALLOW_FIELD_EDIT_OF_THIS_MESSAGE_ = Symbol.intern ("UIL-ALLOW-FIELD-EDIT-OF-THIS-MESSAGE");
  private static final Symbol UIL_CLEAR_TEXT_BEFORE_EDIT_ = Symbol.intern ("UIL-CLEAR-TEXT-BEFORE-EDIT");
  private static final Symbol UIL_FORMAT_SPECIFICATION_ = Symbol.intern ("UIL-FORMAT-SPECIFICATION");
  private static final Symbol UIL_CONCLUDE_METHOD_ = Symbol.intern ("UIL-CONCLUDE-METHOD");
  private static final Symbol UIL_VALIDATION_METHOD_ = Symbol.intern ("UIL-VALIDATION-METHOD");
  private static final Symbol UIL_MESSAGE_SELECTION_METHOD_ = Symbol.intern ("UIL-MESSAGE-SELECTION-METHOD");
  private static final Symbol UIL_MESSAGE_UNSELECTION_METHOD_ = Symbol.intern ("UIL-MESSAGE-UNSELECTION-METHOD");
  private static final Symbol UIL_BORDER_RELATION_ = Symbol.intern ("UIL-BORDER-RELATION");
  private static final Symbol UIL_BORDER_ID_ = Symbol.intern ("UIL-BORDER-ID");
  private static final Symbol UIL_TEXT_RELATION_ = Symbol.intern ("UIL-TEXT-RELATION");
  private static final Symbol UIL_LABEL_ID_ = Symbol.intern ("UIL-LABEL-ID");
  private static final Symbol LABEL_ = Symbol.intern ("LABEL");
  private static final Symbol STATE_ = Symbol.intern ("STATE");
  private static final Symbol MESSAGE_CONTENTS_ = Symbol.intern ("MESSAGE-CONTENTS");
  private static final Symbol UIL_UPDATE_VALUE_ = Symbol.intern ("UIL-UPDATE-VALUE");
  private static final Symbol UIL_EDIT_SESSION_RESULT_ = Symbol.intern ("UIL-EDIT-SESSION-RESULT");
  private static final Symbol UIL_EDIT_STATUS_ = Symbol.intern ("UIL-EDIT-STATUS");
  private static final Symbol UIL_USE_GRAMMAR_PER_TARGET_SPECIFICATIONS_ = Symbol.intern ("UIL-USE-GRAMMAR-PER-TARGET-SPECIFICATIONS");

  /* Generated constructors */

  public UilEditBoxImpl() {
    super();
  }

  public UilEditBoxImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilEditBoxImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
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
   * Generated Property Setter for attribute -- UIL-VALIDATE-VALUE-IMMEDIATELY
   * @param uilValidateValueImmediately new value to conclude for UIL-VALIDATE-VALUE-IMMEDIATELY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilValidateValueImmediately(java.lang.Object uilValidateValueImmediately) throws G2AccessException {
    setAttributeValue (UIL_VALIDATE_VALUE_IMMEDIATELY_, uilValidateValueImmediately);
  }

  /**
   * Generated Property Getter for attribute -- UIL-VALIDATE-VALUE-IMMEDIATELY
   * @return the value of the UIL-VALIDATE-VALUE-IMMEDIATELY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilValidateValueImmediately() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_VALIDATE_VALUE_IMMEDIATELY_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-ALLOW-FIELD-EDIT-OF-THIS-MESSAGE
   * @param uilAllowFieldEditOfThisMessage new value to conclude for UIL-ALLOW-FIELD-EDIT-OF-THIS-MESSAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilAllowFieldEditOfThisMessage(java.lang.Object uilAllowFieldEditOfThisMessage) throws G2AccessException {
    setAttributeValue (UIL_ALLOW_FIELD_EDIT_OF_THIS_MESSAGE_, uilAllowFieldEditOfThisMessage);
  }

  /**
   * Generated Property Getter for attribute -- UIL-ALLOW-FIELD-EDIT-OF-THIS-MESSAGE
   * @return the value of the UIL-ALLOW-FIELD-EDIT-OF-THIS-MESSAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilAllowFieldEditOfThisMessage() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_ALLOW_FIELD_EDIT_OF_THIS_MESSAGE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-CLEAR-TEXT-BEFORE-EDIT
   * @param uilClearTextBeforeEdit new value to conclude for UIL-CLEAR-TEXT-BEFORE-EDIT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilClearTextBeforeEdit(java.lang.Object uilClearTextBeforeEdit) throws G2AccessException {
    setAttributeValue (UIL_CLEAR_TEXT_BEFORE_EDIT_, uilClearTextBeforeEdit);
  }

  /**
   * Generated Property Getter for attribute -- UIL-CLEAR-TEXT-BEFORE-EDIT
   * @return the value of the UIL-CLEAR-TEXT-BEFORE-EDIT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilClearTextBeforeEdit() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_CLEAR_TEXT_BEFORE_EDIT_);
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
   * Generated Property Setter for attribute -- UIL-VALIDATION-METHOD
   * @param uilValidationMethod new value to conclude for UIL-VALIDATION-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilValidationMethod(java.lang.Object uilValidationMethod) throws G2AccessException {
    setAttributeValue (UIL_VALIDATION_METHOD_, uilValidationMethod);
  }

  /**
   * Generated Property Getter for attribute -- UIL-VALIDATION-METHOD
   * @return the value of the UIL-VALIDATION-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilValidationMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_VALIDATION_METHOD_);
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

  /**
   * Generated Property Setter for attribute -- UIL-EDIT-SESSION-RESULT
   * @param uilEditSessionResult new value to conclude for UIL-EDIT-SESSION-RESULT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilEditSessionResult(java.lang.Object uilEditSessionResult) throws G2AccessException {
    setAttributeValue (UIL_EDIT_SESSION_RESULT_, uilEditSessionResult);
  }

  /**
   * Generated Property Getter for attribute -- UIL-EDIT-SESSION-RESULT
   * @return the value of the UIL-EDIT-SESSION-RESULT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilEditSessionResult() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_EDIT_SESSION_RESULT_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-EDIT-STATUS
   * @param uilEditStatus new value to conclude for UIL-EDIT-STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilEditStatus(java.lang.Object uilEditStatus) throws G2AccessException {
    setAttributeValue (UIL_EDIT_STATUS_, uilEditStatus);
  }

  /**
   * Generated Property Getter for attribute -- UIL-EDIT-STATUS
   * @return the value of the UIL-EDIT-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilEditStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_EDIT_STATUS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-USE-GRAMMAR-PER-TARGET-SPECIFICATIONS
   * @param uilUseGrammarPerTargetSpecifications new value to conclude for UIL-USE-GRAMMAR-PER-TARGET-SPECIFICATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilUseGrammarPerTargetSpecifications(java.lang.Object uilUseGrammarPerTargetSpecifications) throws G2AccessException {
    setAttributeValue (UIL_USE_GRAMMAR_PER_TARGET_SPECIFICATIONS_, uilUseGrammarPerTargetSpecifications);
  }

  /**
   * Generated Property Getter for attribute -- UIL-USE-GRAMMAR-PER-TARGET-SPECIFICATIONS
   * @return the value of the UIL-USE-GRAMMAR-PER-TARGET-SPECIFICATIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilUseGrammarPerTargetSpecifications() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_USE_GRAMMAR_PER_TARGET_SPECIFICATIONS_);
    return (java.lang.Object)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_UPP_EXTRACT_VALUE_FROM_ITEM_ = Symbol.intern ("UPP-EXTRACT-VALUE-FROM-ITEM");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * UIL-EDIT-BOX::UPP-EXTRACT-VALUE-FROM-ITEM
   * @return the return from calling UPP-EXTRACT-VALUE-FROM-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-EDIT-BOX) = (VALUE,TRUTH-VALUE)
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
