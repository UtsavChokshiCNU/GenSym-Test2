/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Procedure.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:04:59 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Procedure extends com.gensym.classes.Item, com.gensym.classes.Entity {

  public static final Symbol PROCEDURE_ = com.gensym.util.symbol.G2ClassSymbols.PROCEDURE_;
  static final Symbol g2ClassName = PROCEDURE_;
  static final Symbol[] classInheritancePath = new Symbol[] {PROCEDURE_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


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
   * Generated Property Getter for attribute -- CLASS-OF-PROCEDURE-INVOCATION
   * @return the value of the CLASS-OF-PROCEDURE-INVOCATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CLASS-OF-PROCEDURE-INVOCATION is : 
   * (OR NoItem
      (MEMBER PROCEDURE-INVOCATION)
      Symbol)
   *
   */
  public com.gensym.util.Symbol getClassOfProcedureInvocation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CLASS-OF-PROCEDURE-INVOCATION
   * @param classOfProcedureInvocation new value to conclude for CLASS-OF-PROCEDURE-INVOCATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setClassOfProcedureInvocation(com.gensym.util.Symbol classOfProcedureInvocation) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DEFAULT-PROCEDURE-PRIORITY
   * @return the value of the DEFAULT-PROCEDURE-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DEFAULT-PROCEDURE-PRIORITY is : 
   * (MEMBER 1 2 3 4 5 6 7 8 9 10)
   *
   */
  public com.gensym.util.Symbol getDefaultProcedurePriority() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DEFAULT-PROCEDURE-PRIORITY
   * @param defaultProcedurePriority new value to conclude for DEFAULT-PROCEDURE-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDefaultProcedurePriority(com.gensym.util.Symbol defaultProcedurePriority) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UNINTERRUPTED-PROCEDURE-EXECUTION-LIMIT
   * @return the value of the UNINTERRUPTED-PROCEDURE-EXECUTION-LIMIT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UNINTERRUPTED-PROCEDURE-EXECUTION-LIMIT is : 
   * (OR NoItem
      (MEMBER USE-DEFAULT)
      Integer)
   *
   */
  public java.lang.Object getUninterruptedProcedureExecutionLimit() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UNINTERRUPTED-PROCEDURE-EXECUTION-LIMIT
   * @param uninterruptedProcedureExecutionLimit new value to conclude for UNINTERRUPTED-PROCEDURE-EXECUTION-LIMIT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUninterruptedProcedureExecutionLimit(java.lang.Object uninterruptedProcedureExecutionLimit) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TEXT
   * @return the value of the TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TEXT is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getText() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TEXT
   * @param text new value to conclude for TEXT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setText(java.lang.String text) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DYNAMIC-BREAKPOINTS
   * @return the value of the DYNAMIC-BREAKPOINTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DYNAMIC-BREAKPOINTS is : 
   * (Sequence 
    (Structure 
      LINE-NUMBER Integer
      IS-ENABLED BooleanTruthValue
      IS-VALID BooleanTruthValue)))
   *
   */
  public com.gensym.util.Sequence getDynamicBreakpoints() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DYNAMIC-BREAKPOINTS
   * @param dynamicBreakpoints new value to conclude for DYNAMIC-BREAKPOINTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDynamicBreakpoints(com.gensym.util.Sequence dynamicBreakpoints) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INLINED-CALLS
   * @return the value of the INLINED-CALLS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INLINED-CALLS is : 
   * (OR (Sequence Symbol)
      NoItem)
   *
   */
  public com.gensym.util.Sequence getInlinedCalls() throws G2AccessException;

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
