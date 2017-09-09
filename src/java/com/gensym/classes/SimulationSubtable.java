/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      SimulationSubtable.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:18 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface SimulationSubtable extends com.gensym.classes.Item, com.gensym.classes.Block {

  public static final Symbol SIMULATION_SUBTABLE_ = com.gensym.util.symbol.G2ClassSymbols.SIMULATION_SUBTABLE_;
  static final Symbol g2ClassName = SIMULATION_SUBTABLE_;
  static final Symbol[] classInheritancePath = new Symbol[] {SIMULATION_SUBTABLE_, ITEM_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


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
   * Generated Property Getter for attribute -- TIME-INCREMENT-FOR-UPDATE
   * @return the value of the TIME-INCREMENT-FOR-UPDATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TIME-INCREMENT-FOR-UPDATE is : 
   * (OR NoItem
      Quantity)
   *
   */
  public java.lang.Number getTimeIncrementForUpdate() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TIME-INCREMENT-FOR-UPDATE
   * @param timeIncrementForUpdate new value to conclude for TIME-INCREMENT-FOR-UPDATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTimeIncrementForUpdate(java.lang.Number timeIncrementForUpdate) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- HISTORY-KEEPING-SPEC
   * @return the value of the HISTORY-KEEPING-SPEC attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for HISTORY-KEEPING-SPEC is : 
   * (OR NoItem
      (Structure 
        MAXIMUM-NUMBER-OF-DATA-POINTS Integer
        MAXIMUM-AGE-OF-DATA-POINTS Integer
        MINIMUM-INTERVAL-BETWEEN-DATA-POINTS Quantity))
   *
   */
  public com.gensym.util.Structure getHistoryKeepingSpec() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- HISTORY-KEEPING-SPEC
   * @param historyKeepingSpec new value to conclude for HISTORY-KEEPING-SPEC
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setHistoryKeepingSpec(com.gensym.util.Structure historyKeepingSpec) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- HISTORY-USING-UNIX-TIME
   * @return the value of the HISTORY-USING-UNIX-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for HISTORY-USING-UNIX-TIME is : 
   * (OR NoItem
      (Sequence 
        (Structure 
          HISTORY-VALUE Value
          HISTORY-COLLECTION-TIME Float)
        1)))
   *
   */
  public com.gensym.util.Sequence getHistoryUsingUnixTime() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- HISTORY-USING-UNIX-TIME
   * @param historyUsingUnixTime new value to conclude for HISTORY-USING-UNIX-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setHistoryUsingUnixTime(com.gensym.util.Sequence historyUsingUnixTime) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- HISTORY
   * @return the value of the HISTORY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for HISTORY is : 
   * (OR NoItem
      (Sequence 
        (Structure 
          HISTORY-VALUE Value
          HISTORY-COLLECTION-TIME Float)
        1)))
   *
   */
  public com.gensym.util.Sequence getHistory() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- HISTORY
   * @param history new value to conclude for HISTORY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setHistory(com.gensym.util.Sequence history) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- EFFECTIVE-DATA-TYPE
   * @return the value of the EFFECTIVE-DATA-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for EFFECTIVE-DATA-TYPE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getEffectiveDataType() throws G2AccessException;

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
