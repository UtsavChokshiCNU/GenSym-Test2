/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      NonActionButton.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:13:35 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface NonActionButton extends com.gensym.classes.Button {

  public static final Symbol NON_ACTION_BUTTON_ = com.gensym.util.symbol.G2ClassSymbols.NON_ACTION_BUTTON_;
  static final Symbol g2ClassName = NON_ACTION_BUTTON_;
  static final Symbol[] classInheritancePath = new Symbol[] {NON_ACTION_BUTTON_, BUTTON_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- VALUE-ON-ACTIVATION
   * @return the value of the VALUE-ON-ACTIVATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for VALUE-ON-ACTIVATION is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text
      (Sequence)
      (Structure))
   *
   */
  public java.lang.Object getValueOnActivation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- VALUE-ON-ACTIVATION
   * @param valueOnActivation new value to conclude for VALUE-ON-ACTIVATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setValueOnActivation(java.lang.Object valueOnActivation) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- VARIABLE-OR-PARAMETER
   * @return the value of the VARIABLE-OR-PARAMETER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for VARIABLE-OR-PARAMETER is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getVariableOrParameter() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- VARIABLE-OR-PARAMETER
   * @param variableOrParameter new value to conclude for VARIABLE-OR-PARAMETER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setVariableOrParameter(java.lang.String variableOrParameter) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- EVALUATION-ATTRIBUTES
   * @return the value of the EVALUATION-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for EVALUATION-ATTRIBUTES is : 
   * (OR NoItem
      (Structure 
        MAY-REFER-TO-INACTIVE-ITEMS BooleanTruthValue
        MAY-RUN-WHILE-INACTIVE BooleanTruthValue))
   *
   */
  public com.gensym.util.Structure getEvaluationAttributes() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- EVALUATION-ATTRIBUTES
   * @param evaluationAttributes new value to conclude for EVALUATION-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEvaluationAttributes(com.gensym.util.Structure evaluationAttributes) throws G2AccessException;

}
