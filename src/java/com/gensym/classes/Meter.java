/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Meter.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:39 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Meter extends com.gensym.classes.Item, com.gensym.classes.Entity {

  public static final Symbol METER_ = com.gensym.util.symbol.G2ClassSymbols.METER_;
  static final Symbol g2ClassName = METER_;
  static final Symbol[] classInheritancePath = new Symbol[] {METER_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


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
   * Generated Property Getter for attribute -- LOW-VALUE-FOR-METER-RULING
   * @return the value of the LOW-VALUE-FOR-METER-RULING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LOW-VALUE-FOR-METER-RULING is : 
   * Quantity
   *
   */
  public java.lang.Number getLowValueForMeterRuling() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LOW-VALUE-FOR-METER-RULING
   * @param lowValueForMeterRuling new value to conclude for LOW-VALUE-FOR-METER-RULING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLowValueForMeterRuling(java.lang.Number lowValueForMeterRuling) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INCREMENT-PER-METER-RULING
   * @return the value of the INCREMENT-PER-METER-RULING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INCREMENT-PER-METER-RULING is : 
   * Quantity
   *
   */
  public java.lang.Number getIncrementPerMeterRuling() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INCREMENT-PER-METER-RULING
   * @param incrementPerMeterRuling new value to conclude for INCREMENT-PER-METER-RULING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIncrementPerMeterRuling(java.lang.Number incrementPerMeterRuling) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- EXPRESSION-TO-DISPLAY
   * @return the value of the EXPRESSION-TO-DISPLAY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for EXPRESSION-TO-DISPLAY is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getExpressionToDisplay() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- EXPRESSION-TO-DISPLAY
   * @param expressionToDisplay new value to conclude for EXPRESSION-TO-DISPLAY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setExpressionToDisplay(java.lang.String expressionToDisplay) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DISPLAY-UPDATE-INTERVAL
   * @return the value of the DISPLAY-UPDATE-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DISPLAY-UPDATE-INTERVAL is : 
   * Quantity
   *
   */
  public java.lang.Number getDisplayUpdateInterval() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DISPLAY-UPDATE-INTERVAL
   * @param displayUpdateInterval new value to conclude for DISPLAY-UPDATE-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDisplayUpdateInterval(java.lang.Number displayUpdateInterval) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DISPLAY-WAIT-INTERVAL
   * @return the value of the DISPLAY-WAIT-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DISPLAY-WAIT-INTERVAL is : 
   * Quantity
   *
   */
  public java.lang.Number getDisplayWaitInterval() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DISPLAY-WAIT-INTERVAL
   * @param displayWaitInterval new value to conclude for DISPLAY-WAIT-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDisplayWaitInterval(java.lang.Number displayWaitInterval) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DISPLAY-UPDATE-PRIORITY
   * @return the value of the DISPLAY-UPDATE-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DISPLAY-UPDATE-PRIORITY is : 
   * (MEMBER 1 2 3 4 5 6 7 8 9 10)
   *
   */
  public com.gensym.util.Symbol getDisplayUpdatePriority() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DISPLAY-UPDATE-PRIORITY
   * @param displayUpdatePriority new value to conclude for DISPLAY-UPDATE-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDisplayUpdatePriority(com.gensym.util.Symbol displayUpdatePriority) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SHOW-SIMULATED-VALUES
   * @return the value of the SHOW-SIMULATED-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SHOW-SIMULATED-VALUES is : 
   * BooleanTruthValue
   *
   */
  public boolean getShowSimulatedValues() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SHOW-SIMULATED-VALUES
   * @param showSimulatedValues new value to conclude for SHOW-SIMULATED-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setShowSimulatedValues(boolean showSimulatedValues) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- VALUE-TO-DISPLAY
   * @return the value of the VALUE-TO-DISPLAY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for VALUE-TO-DISPLAY is : 
   * Quantity
   *
   */
  public java.lang.Number getValueToDisplay() throws G2AccessException;

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
