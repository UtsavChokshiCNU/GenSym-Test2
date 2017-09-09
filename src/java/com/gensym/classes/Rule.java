/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Rule.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:07:43 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Rule extends com.gensym.classes.Statement {

  public static final Symbol RULE_ = com.gensym.util.symbol.G2ClassSymbols.RULE_;
  static final Symbol g2ClassName = RULE_;
  static final Symbol[] classInheritancePath = new Symbol[] {RULE_, STATEMENT_, ITEM_, STATEMENT_OR_PROCEDURE_STEP_, TEXT_BOX_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- OPTIONS
   * @return the value of the OPTIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for OPTIONS is : 
   * (Structure 
    BACKWARD-CHAIN BooleanTruthValue
    FORWARD-CHAIN BooleanTruthValue
    DATA-SEEKING BooleanTruthValue
    CAUSE-FORWARD BooleanTruthValue
    EXPLANATION-DATA BooleanTruthValue)
   *
   */
  public com.gensym.util.Structure getOptions() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- OPTIONS
   * @param options new value to conclude for OPTIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setOptions(com.gensym.util.Structure options) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for AUTHORS is : 
   * (OR NoItem
      (Structure 
        TIMESTAMP
          (Structure 
            YEAR Integer
            MONTH Integer
            DATE Integer
            HOURS Integer
            MINUTES Integer)
        AUTHORS
          (Sequence Symbol 0)))
   *
   */
  public com.gensym.util.Structure getAuthors() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAuthors(com.gensym.util.Structure authors) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CHANGE-LOG is : 
   * (OR (Sequence)
      NoItem)
   *
   */
  public com.gensym.util.Sequence getChangeLog() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TRACING-AND-BREAKPOINTS
   * @return the value of the TRACING-AND-BREAKPOINTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TRACING-AND-BREAKPOINTS is : 
   * (OR (MEMBER DEFAULT)
      (Structure 
        WARNING-MESSAGE-LEVEL
          (MEMBER 0 1 2 3)
        TRACING-MESSAGE-LEVEL
          (MEMBER 0 1 2 3)
        BREAKPOINT-LEVEL
          (MEMBER 0 1 2 3)
        SOURCE-STEPPING-LEVEL
          (MEMBER 0 1)))
   *
   */
  public java.lang.Object getTracingAndBreakpoints() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TRACING-AND-BREAKPOINTS
   * @param tracingAndBreakpoints new value to conclude for TRACING-AND-BREAKPOINTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTracingAndBreakpoints(java.lang.Object tracingAndBreakpoints) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SCAN-INTERVAL
   * @return the value of the SCAN-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SCAN-INTERVAL is : 
   * (OR Quantity
      NoItem)
   *
   */
  public java.lang.Number getScanInterval() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SCAN-INTERVAL
   * @param scanInterval new value to conclude for SCAN-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setScanInterval(java.lang.Number scanInterval) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FOCAL-CLASSES
   * @return the value of the FOCAL-CLASSES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FOCAL-CLASSES is : 
   * (OR NoItem
      (Sequence Symbol 1))
   *
   */
  public com.gensym.util.Sequence getFocalClasses() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FOCAL-CLASSES
   * @param focalClasses new value to conclude for FOCAL-CLASSES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFocalClasses(com.gensym.util.Sequence focalClasses) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FOCAL-OBJECTS
   * @return the value of the FOCAL-OBJECTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FOCAL-OBJECTS is : 
   * (OR NoItem
      (Sequence Symbol 1))
   *
   */
  public com.gensym.util.Sequence getFocalObjects() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FOCAL-OBJECTS
   * @param focalObjects new value to conclude for FOCAL-OBJECTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFocalObjects(com.gensym.util.Sequence focalObjects) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CATEGORIES
   * @return the value of the CATEGORIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CATEGORIES is : 
   * (OR NoItem
      (Sequence Symbol 1))
   *
   */
  public com.gensym.util.Sequence getCategories() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CATEGORIES
   * @param categories new value to conclude for CATEGORIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setCategories(com.gensym.util.Sequence categories) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- RULE-PRIORITY
   * @return the value of the RULE-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for RULE-PRIORITY is : 
   * (MEMBER 1 2 3 4 5 6 7 8 9 10)
   *
   */
  public com.gensym.util.Symbol getRulePriority() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- RULE-PRIORITY
   * @param rulePriority new value to conclude for RULE-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRulePriority(com.gensym.util.Symbol rulePriority) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DEPTH-FIRST-BACKWARD-CHAINING-PRECEDENCE
   * @return the value of the DEPTH-FIRST-BACKWARD-CHAINING-PRECEDENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DEPTH-FIRST-BACKWARD-CHAINING-PRECEDENCE is : 
   * Integer
   *
   */
  public int getDepthFirstBackwardChainingPrecedence() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DEPTH-FIRST-BACKWARD-CHAINING-PRECEDENCE
   * @param depthFirstBackwardChainingPrecedence new value to conclude for DEPTH-FIRST-BACKWARD-CHAINING-PRECEDENCE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDepthFirstBackwardChainingPrecedence(int depthFirstBackwardChainingPrecedence) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TIMEOUT-FOR-RULE-COMPLETION
   * @return the value of the TIMEOUT-FOR-RULE-COMPLETION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TIMEOUT-FOR-RULE-COMPLETION is : 
   * (OR NoItem
      (MEMBER USE-DEFAULT)
      Integer)
   *
   */
  public java.lang.Object getTimeoutForRuleCompletion() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TIMEOUT-FOR-RULE-COMPLETION
   * @param timeoutForRuleCompletion new value to conclude for TIMEOUT-FOR-RULE-COMPLETION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTimeoutForRuleCompletion(java.lang.Object timeoutForRuleCompletion) throws G2AccessException;

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
