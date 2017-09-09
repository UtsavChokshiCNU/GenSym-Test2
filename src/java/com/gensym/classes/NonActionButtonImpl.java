/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      NonActionButtonImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:13:39 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class NonActionButtonImpl extends com.gensym.classes.ButtonImpl implements NonActionButton {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public NonActionButtonImpl() {
    super();
  }

  public NonActionButtonImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public NonActionButtonImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- VALUE-ON-ACTIVATION
   * @param valueOnActivation new value to conclude for VALUE-ON-ACTIVATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setValueOnActivation(java.lang.Object valueOnActivation) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.VALUE_ON_ACTIVATION_, valueOnActivation);
  }

  /**
   * Generated Property Getter for attribute -- VALUE-ON-ACTIVATION
   * @return the value of the VALUE-ON-ACTIVATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getValueOnActivation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.VALUE_ON_ACTIVATION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- VARIABLE-OR-PARAMETER
   * @param variableOrParameter new value to conclude for VARIABLE-OR-PARAMETER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setVariableOrParameter(java.lang.String variableOrParameter) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.VARIABLE_OR_PARAMETER_, variableOrParameter);
  }

  /**
   * Generated Property Getter for attribute -- VARIABLE-OR-PARAMETER
   * @return the value of the VARIABLE-OR-PARAMETER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getVariableOrParameter() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.VARIABLE_OR_PARAMETER_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- EVALUATION-ATTRIBUTES
   * @param evaluationAttributes new value to conclude for EVALUATION-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setEvaluationAttributes(com.gensym.util.Structure evaluationAttributes) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.EVALUATION_ATTRIBUTES_, evaluationAttributes);
  }

  /**
   * Generated Property Getter for attribute -- EVALUATION-ATTRIBUTES
   * @return the value of the EVALUATION-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getEvaluationAttributes() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.EVALUATION_ATTRIBUTES_);
    return (com.gensym.util.Structure)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
