/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GenericActionButtonImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:54:18 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class GenericActionButtonImpl extends com.gensym.classes.ButtonImpl implements GenericActionButton {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public GenericActionButtonImpl() {
    super();
  }

  public GenericActionButtonImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public GenericActionButtonImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAuthors(com.gensym.util.Structure authors) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.AUTHORS_, authors);
  }

  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getAuthors() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.AUTHORS_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getChangeLog() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CHANGE_LOG_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ACTION
   * @param action new value to conclude for ACTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAction(java.lang.String action) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ACTION_, action);
  }

  /**
   * Generated Property Getter for attribute -- ACTION
   * @return the value of the ACTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getAction() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ACTION_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ACTION-PRIORITY
   * @param actionPriority new value to conclude for ACTION-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setActionPriority(com.gensym.util.Symbol actionPriority) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ACTION_PRIORITY_, actionPriority);
  }

  /**
   * Generated Property Getter for attribute -- ACTION-PRIORITY
   * @return the value of the ACTION-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getActionPriority() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ACTION_PRIORITY_);
    return (com.gensym.util.Symbol)retnValue;
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
