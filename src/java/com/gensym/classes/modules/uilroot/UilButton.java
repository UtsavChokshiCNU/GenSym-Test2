/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilButton.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:14:24 EDT 2007
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

public interface UilButton extends com.gensym.classes.modules.uilroot.UilGrobj {

  public static final Symbol UIL_BUTTON_ = Symbol.intern ("UIL-BUTTON");
  static final Symbol g2ClassName = UIL_BUTTON_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_BUTTON_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


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
   * Generated Property Getter for attribute -- UIL-HANDLER-METHOD
   * @return the value of the UIL-HANDLER-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-HANDLER-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilHandlerMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-HANDLER-METHOD
   * @param uilHandlerMethod new value to conclude for UIL-HANDLER-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilHandlerMethod(java.lang.Object uilHandlerMethod) throws G2AccessException;

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
   * Generated Property Getter for attribute -- UIL-LABEL-SIZE
   * @return the value of the UIL-LABEL-SIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-LABEL-SIZE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilLabelSize() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-LABEL-SIZE
   * @param uilLabelSize new value to conclude for UIL-LABEL-SIZE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilLabelSize(java.lang.Object uilLabelSize) throws G2AccessException;

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
   * Generated Property Getter for attribute -- UIL-IS-DIALOG-BUTTON
   * @return the value of the UIL-IS-DIALOG-BUTTON attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-IS-DIALOG-BUTTON is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilIsDialogButton() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-IS-DIALOG-BUTTON
   * @param uilIsDialogButton new value to conclude for UIL-IS-DIALOG-BUTTON
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilIsDialogButton(java.lang.Object uilIsDialogButton) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SHORT-DESCRIPTION
   * @return the value of the UIL-SHORT-DESCRIPTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SHORT-DESCRIPTION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilShortDescription() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SHORT-DESCRIPTION
   * @param uilShortDescription new value to conclude for UIL-SHORT-DESCRIPTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilShortDescription(java.lang.Object uilShortDescription) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * UIL-BUTTON::UPP-UPDATE-BUTTON-LABEL
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-BUTTON) = ()
   */
  public  void uppUpdateButtonLabel() throws G2AccessException;
  
}
