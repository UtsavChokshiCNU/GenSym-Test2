/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      RuleImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:07:45 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class RuleImpl extends com.gensym.classes.StatementImpl implements Rule {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public RuleImpl() {
    super();
  }

  public RuleImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public RuleImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- OPTIONS
   * @param options new value to conclude for OPTIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setOptions(com.gensym.util.Structure options) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.OPTIONS_, options);
  }

  /**
   * Generated Property Getter for attribute -- OPTIONS
   * @return the value of the OPTIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getOptions() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.OPTIONS_);
    return (com.gensym.util.Structure)retnValue;
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
   * Generated Property Setter for attribute -- TRACING-AND-BREAKPOINTS
   * @param tracingAndBreakpoints new value to conclude for TRACING-AND-BREAKPOINTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTracingAndBreakpoints(java.lang.Object tracingAndBreakpoints) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TRACING_AND_BREAKPOINTS_, tracingAndBreakpoints);
  }

  /**
   * Generated Property Getter for attribute -- TRACING-AND-BREAKPOINTS
   * @return the value of the TRACING-AND-BREAKPOINTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getTracingAndBreakpoints() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TRACING_AND_BREAKPOINTS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SCAN-INTERVAL
   * @param scanInterval new value to conclude for SCAN-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setScanInterval(java.lang.Number scanInterval) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SCAN_INTERVAL_, scanInterval);
  }

  /**
   * Generated Property Getter for attribute -- SCAN-INTERVAL
   * @return the value of the SCAN-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Number getScanInterval() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SCAN_INTERVAL_);
    return (java.lang.Number)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- FOCAL-CLASSES
   * @param focalClasses new value to conclude for FOCAL-CLASSES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFocalClasses(com.gensym.util.Sequence focalClasses) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FOCAL_CLASSES_, focalClasses);
  }

  /**
   * Generated Property Getter for attribute -- FOCAL-CLASSES
   * @return the value of the FOCAL-CLASSES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getFocalClasses() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FOCAL_CLASSES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- FOCAL-OBJECTS
   * @param focalObjects new value to conclude for FOCAL-OBJECTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFocalObjects(com.gensym.util.Sequence focalObjects) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FOCAL_OBJECTS_, focalObjects);
  }

  /**
   * Generated Property Getter for attribute -- FOCAL-OBJECTS
   * @return the value of the FOCAL-OBJECTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getFocalObjects() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FOCAL_OBJECTS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CATEGORIES
   * @param categories new value to conclude for CATEGORIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setCategories(com.gensym.util.Sequence categories) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.CATEGORIES_, categories);
  }

  /**
   * Generated Property Getter for attribute -- CATEGORIES
   * @return the value of the CATEGORIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getCategories() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CATEGORIES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- RULE-PRIORITY
   * @param rulePriority new value to conclude for RULE-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRulePriority(com.gensym.util.Symbol rulePriority) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.RULE_PRIORITY_, rulePriority);
  }

  /**
   * Generated Property Getter for attribute -- RULE-PRIORITY
   * @return the value of the RULE-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getRulePriority() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.RULE_PRIORITY_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DEPTH-FIRST-BACKWARD-CHAINING-PRECEDENCE
   * @param depthFirstBackwardChainingPrecedence new value to conclude for DEPTH-FIRST-BACKWARD-CHAINING-PRECEDENCE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDepthFirstBackwardChainingPrecedence(int depthFirstBackwardChainingPrecedence) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DEPTH_FIRST_BACKWARD_CHAINING_PRECEDENCE_, depthFirstBackwardChainingPrecedence);
  }

  /**
   * Generated Property Getter for attribute -- DEPTH-FIRST-BACKWARD-CHAINING-PRECEDENCE
   * @return the value of the DEPTH-FIRST-BACKWARD-CHAINING-PRECEDENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getDepthFirstBackwardChainingPrecedence() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DEPTH_FIRST_BACKWARD_CHAINING_PRECEDENCE_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- TIMEOUT-FOR-RULE-COMPLETION
   * @param timeoutForRuleCompletion new value to conclude for TIMEOUT-FOR-RULE-COMPLETION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTimeoutForRuleCompletion(java.lang.Object timeoutForRuleCompletion) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TIMEOUT_FOR_RULE_COMPLETION_, timeoutForRuleCompletion);
  }

  /**
   * Generated Property Getter for attribute -- TIMEOUT-FOR-RULE-COMPLETION
   * @return the value of the TIMEOUT-FOR-RULE-COMPLETION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getTimeoutForRuleCompletion() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TIMEOUT_FOR_RULE_COMPLETION_);
    return (java.lang.Object)retnValue;
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
