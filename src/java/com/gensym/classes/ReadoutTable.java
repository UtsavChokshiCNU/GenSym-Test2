/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ReadoutTable.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:07:10 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface ReadoutTable extends com.gensym.classes.Item, com.gensym.classes.Table {

  public static final Symbol READOUT_TABLE_ = com.gensym.util.symbol.G2ClassSymbols.READOUT_TABLE_;
  static final Symbol g2ClassName = READOUT_TABLE_;
  static final Symbol[] classInheritancePath = new Symbol[] {READOUT_TABLE_, ITEM_, TABLE_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};

  static final Symbol DEFAULT_READOUT_TABLE_FORMAT_NAME_ = Symbol.intern ("DEFAULT-READOUT-TABLE-FORMAT-NAME");

  static final Symbol[] staticAttributes = new Symbol[] {DEFAULT_READOUT_TABLE_FORMAT_NAME_};


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
   * Generated Property Getter for attribute -- LABEL-TO-DISPLAY
   * @return the value of the LABEL-TO-DISPLAY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LABEL-TO-DISPLAY is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getLabelToDisplay() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LABEL-TO-DISPLAY
   * @param labelToDisplay new value to conclude for LABEL-TO-DISPLAY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLabelToDisplay(java.lang.String labelToDisplay) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DISPLAY-FORMAT
   * @return the value of the DISPLAY-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DISPLAY-FORMAT is : 
   * (OR (MEMBER DEFAULT INTERVAL TIME-STAMP FREE-TEXT)
      Symbol
      (Structure 
        WHOLE-NUMBER-PRECISION Integer
        FRACTION-PRECISION Integer))
   *
   */
  public java.lang.Object getDisplayFormat() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DISPLAY-FORMAT
   * @param displayFormat new value to conclude for DISPLAY-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDisplayFormat(java.lang.Object displayFormat) throws G2AccessException;

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

  /**
   * Generated Property Getter for attribute -- SIZE-IN-WORKSPACE
   * @return the value of the SIZE-IN-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SIZE-IN-WORKSPACE is : 
   * (OR NoItem
      (Structure 
        WIDTH Quantity
        HEIGHT Quantity))
   *
   */
  public com.gensym.util.Structure getSizeInWorkspace() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SIZE-IN-WORKSPACE
   * @param sizeInWorkspace new value to conclude for SIZE-IN-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSizeInWorkspace(com.gensym.util.Structure sizeInWorkspace) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DEFAULT-READOUT-TABLE-FORMAT-NAME
   * @return the value of the DEFAULT-READOUT-TABLE-FORMAT-NAME attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DEFAULT-READOUT-TABLE-FORMAT-NAME is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getDefaultReadoutTableFormatNameForClass() throws G2AccessException;

}
