/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilEditBox.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:05 EDT 2007
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

public interface UilEditBox extends com.gensym.classes.modules.uilroot.UilGrmes {

  public static final Symbol UIL_EDIT_BOX_ = Symbol.intern ("UIL-EDIT-BOX");
  static final Symbol g2ClassName = UIL_EDIT_BOX_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_EDIT_BOX_, UIL_GRMES_, UIL_MESSAGE_, MESSAGE_, ITEM_, TEXT_BOX_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


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
   * Generated Property Getter for attribute -- UIL-VALIDATE-VALUE-IMMEDIATELY
   * @return the value of the UIL-VALIDATE-VALUE-IMMEDIATELY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-VALIDATE-VALUE-IMMEDIATELY is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilValidateValueImmediately() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-VALIDATE-VALUE-IMMEDIATELY
   * @param uilValidateValueImmediately new value to conclude for UIL-VALIDATE-VALUE-IMMEDIATELY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilValidateValueImmediately(java.lang.Object uilValidateValueImmediately) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ALLOW-FIELD-EDIT-OF-THIS-MESSAGE
   * @return the value of the UIL-ALLOW-FIELD-EDIT-OF-THIS-MESSAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ALLOW-FIELD-EDIT-OF-THIS-MESSAGE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilAllowFieldEditOfThisMessage() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ALLOW-FIELD-EDIT-OF-THIS-MESSAGE
   * @param uilAllowFieldEditOfThisMessage new value to conclude for UIL-ALLOW-FIELD-EDIT-OF-THIS-MESSAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilAllowFieldEditOfThisMessage(java.lang.Object uilAllowFieldEditOfThisMessage) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-CLEAR-TEXT-BEFORE-EDIT
   * @return the value of the UIL-CLEAR-TEXT-BEFORE-EDIT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-CLEAR-TEXT-BEFORE-EDIT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilClearTextBeforeEdit() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-CLEAR-TEXT-BEFORE-EDIT
   * @param uilClearTextBeforeEdit new value to conclude for UIL-CLEAR-TEXT-BEFORE-EDIT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilClearTextBeforeEdit(java.lang.Object uilClearTextBeforeEdit) throws G2AccessException;

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
   * Generated Property Getter for attribute -- UIL-VALIDATION-METHOD
   * @return the value of the UIL-VALIDATION-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-VALIDATION-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilValidationMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-VALIDATION-METHOD
   * @param uilValidationMethod new value to conclude for UIL-VALIDATION-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilValidationMethod(java.lang.Object uilValidationMethod) throws G2AccessException;

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
   * Generated Property Getter for attribute -- UIL-TEXT-RELATION
   * @return the value of the UIL-TEXT-RELATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-TEXT-RELATION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilTextRelation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-TEXT-RELATION
   * @param uilTextRelation new value to conclude for UIL-TEXT-RELATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilTextRelation(java.lang.Object uilTextRelation) throws G2AccessException;

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
   * Generated Property Getter for attribute -- LABEL
   * @return the value of the LABEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LABEL is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getLabel() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LABEL
   * @param label new value to conclude for LABEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLabel(java.lang.Object label) throws G2AccessException;

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
   * Generated Property Getter for attribute -- UIL-EDIT-SESSION-RESULT
   * @return the value of the UIL-EDIT-SESSION-RESULT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-EDIT-SESSION-RESULT is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilEditSessionResult() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-EDIT-SESSION-RESULT
   * @param uilEditSessionResult new value to conclude for UIL-EDIT-SESSION-RESULT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilEditSessionResult(java.lang.Object uilEditSessionResult) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-EDIT-STATUS
   * @return the value of the UIL-EDIT-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-EDIT-STATUS is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilEditStatus() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-EDIT-STATUS
   * @param uilEditStatus new value to conclude for UIL-EDIT-STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilEditStatus(java.lang.Object uilEditStatus) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-USE-GRAMMAR-PER-TARGET-SPECIFICATIONS
   * @return the value of the UIL-USE-GRAMMAR-PER-TARGET-SPECIFICATIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-USE-GRAMMAR-PER-TARGET-SPECIFICATIONS is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilUseGrammarPerTargetSpecifications() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-USE-GRAMMAR-PER-TARGET-SPECIFICATIONS
   * @param uilUseGrammarPerTargetSpecifications new value to conclude for UIL-USE-GRAMMAR-PER-TARGET-SPECIFICATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilUseGrammarPerTargetSpecifications(java.lang.Object uilUseGrammarPerTargetSpecifications) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * UIL-EDIT-BOX::UPP-EXTRACT-VALUE-FROM-ITEM
   * @return the return from calling UPP-EXTRACT-VALUE-FROM-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-EDIT-BOX) = (VALUE,TRUTH-VALUE)
   */
  public  com.gensym.util.Sequence uppExtractValueFromItem() throws G2AccessException;
  
}
