/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      VariableOrParameter.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:17 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.util.VariableValueListener;
import com.gensym.util.VariableValueEvent;
import com.gensym.util.Symbol;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.UnexpectedException;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.message.Trace;
import com.gensym.util.EventMulticaster;
import com.gensym.util.ItemEvent;
import com.gensym.jgi.G2AccessException;

public interface VariableOrParameter extends com.gensym.classes.Object {

  public static final Symbol VARIABLE_OR_PARAMETER_ = com.gensym.util.symbol.G2ClassSymbols.VARIABLE_OR_PARAMETER_;
  static final Symbol g2ClassName = VARIABLE_OR_PARAMETER_;
  static final Symbol[] classInheritancePath = new Symbol[] {VARIABLE_OR_PARAMETER_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


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
   * Generated Property Getter for attribute -- DATA-TYPE
   * @return the value of the DATA-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DATA-TYPE is : 
   * (OR (OR (MEMBER QUANTITY)
          (OR (MEMBER FLOAT TIME-STAMP)
              Symbol)
          (OR (MEMBER INTEGER INTERVAL)
              Symbol))
      (MEMBER VALUE SYMBOL TEXT TRUTH-VALUE))
   *
   */
  public com.gensym.util.Symbol getDataType() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DATA-TYPE
   * @param dataType new value to conclude for DATA-TYPE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDataType(com.gensym.util.Symbol dataType) throws G2AccessException;

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
   * Generated Property Getter for attribute -- LAST-RECORDED-VALUE-TEXT
   * @return the value of the LAST-RECORDED-VALUE-TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LAST-RECORDED-VALUE-TEXT is : 
   * (OR NoItem
      Text)
   *
   */
  public java.lang.String getLastRecordedValueText() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- VALUE-STRUCTURE-USING-UNIX-TIME
   * @return the value of the VALUE-STRUCTURE-USING-UNIX-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for VALUE-STRUCTURE-USING-UNIX-TIME is : 
   * (OR NoItem
      (Structure 
        DATA-POINT-VALUE Value
        DATA-POINT-COLLECTION-TIME Quantity
        DATA-POINT-EXPIRATION-TIME
          (OR Quantity
              (MEMBER NEVER))))
   *
   */
  public com.gensym.util.Structure getValueStructureUsingUnixTime() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- VALUE-STRUCTURE-USING-UNIX-TIME
   * @param valueStructureUsingUnixTime new value to conclude for VALUE-STRUCTURE-USING-UNIX-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setValueStructureUsingUnixTime(com.gensym.util.Structure valueStructureUsingUnixTime) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- VALUE-STRUCTURE
   * @return the value of the VALUE-STRUCTURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for VALUE-STRUCTURE is : 
   * (OR NoItem
      (Structure 
        DATA-POINT-VALUE Value
        DATA-POINT-COLLECTION-TIME Quantity
        DATA-POINT-EXPIRATION-TIME
          (OR Quantity
              (MEMBER NEVER))))
   *
   */
  public com.gensym.util.Structure getValueStructure() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- VALUE-STRUCTURE
   * @param valueStructure new value to conclude for VALUE-STRUCTURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setValueStructure(com.gensym.util.Structure valueStructure) throws G2AccessException;

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

  /* Overriden  - VARIABLEVALUE Event Listeners Management */
  /* Adder */
  /**
   * Adds <code>valueListener</code> as a listener receiving updates
   * to changes in the value of this <code>VariableOrParameter</code>.
   * Makes an RPC call to G2 if this is the first listener.
   *
   * @param valueListener the listener to add
   * @exception G2AccessException if the RPC call fails.
   */
  public void addVariableValueListener(VariableValueListener valueListener)
  throws G2AccessException;
  /* Remover */
  /**
   * Removes <code>valueListener</code> as a listener receiving updates
   * to changes in the value of this <code>VariableOrParameter</code>.
   * Makes an RPC call to G2 if this is the last remaining listener.
   *
   * @param valueListener the listener to add
   * @exception G2AccessException if the RPC call fails.
   */
  public void removeVariableValueListener(VariableValueListener valueListener)
  throws G2AccessException;

  /* Overriden method - PROCESS-VARIABLE-VALUE-EVENT */
  /**
   * @undocumented
   */
  public void processVariableValueEvent(VariableValueEvent event);

  /* Overriden method - PROCESS-ITEM-EVENT */
  /**
   * @undocumented
   */
  @Override
  public void processItemEvent(ItemEvent event);

  /* Overriden method - ADD-VARIABLE-VALUE-LISTENER-RETRIEVING-STATE */
  /**
   * @undocumented
   */
  public Structure addVariableValueListenerRetrievingState(VariableValueListener
							   valueListener)
  throws G2AccessException;

}
