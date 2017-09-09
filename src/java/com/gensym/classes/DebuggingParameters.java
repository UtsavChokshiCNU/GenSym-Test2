/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      DebuggingParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:37:39 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface DebuggingParameters extends com.gensym.classes.SystemTable {

  public static final Symbol DEBUGGING_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.DEBUGGING_PARAMETERS_;
  static final Symbol g2ClassName = DEBUGGING_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {DEBUGGING_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- WARNING-MESSAGE-LEVEL
   * @return the value of the WARNING-MESSAGE-LEVEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for WARNING-MESSAGE-LEVEL is : 
   * (MEMBER 0 1 2 3)
   *
   */
  public com.gensym.util.Symbol getWarningMessageLevel() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- WARNING-MESSAGE-LEVEL
   * @param warningMessageLevel new value to conclude for WARNING-MESSAGE-LEVEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setWarningMessageLevel(com.gensym.util.Symbol warningMessageLevel) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TRACING-MESSAGE-LEVEL
   * @return the value of the TRACING-MESSAGE-LEVEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TRACING-MESSAGE-LEVEL is : 
   * (MEMBER 0 1 2 3)
   *
   */
  public com.gensym.util.Symbol getTracingMessageLevel() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TRACING-MESSAGE-LEVEL
   * @param tracingMessageLevel new value to conclude for TRACING-MESSAGE-LEVEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTracingMessageLevel(com.gensym.util.Symbol tracingMessageLevel) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- BREAKPOINT-LEVEL
   * @return the value of the BREAKPOINT-LEVEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for BREAKPOINT-LEVEL is : 
   * (MEMBER 0 1 2 3)
   *
   */
  public com.gensym.util.Symbol getBreakpointLevel() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- BREAKPOINT-LEVEL
   * @param breakpointLevel new value to conclude for BREAKPOINT-LEVEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setBreakpointLevel(com.gensym.util.Symbol breakpointLevel) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SOURCE-STEPPING-LEVEL
   * @return the value of the SOURCE-STEPPING-LEVEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SOURCE-STEPPING-LEVEL is : 
   * (MEMBER 0 1)
   *
   */
  public com.gensym.util.Symbol getSourceSteppingLevel() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SOURCE-STEPPING-LEVEL
   * @param sourceSteppingLevel new value to conclude for SOURCE-STEPPING-LEVEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSourceSteppingLevel(com.gensym.util.Symbol sourceSteppingLevel) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TRACING-AND-BREAKPOINTS-ENABLED?
   * @return the value of the TRACING-AND-BREAKPOINTS-ENABLED? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TRACING-AND-BREAKPOINTS-ENABLED? is : 
   * BooleanTruthValue
   *
   */
  public boolean getTracingAndBreakpointsEnabled() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TRACING-AND-BREAKPOINTS-ENABLED?
   * @param tracingAndBreakpointsEnabled new value to conclude for TRACING-AND-BREAKPOINTS-ENABLED?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTracingAndBreakpointsEnabled(boolean tracingAndBreakpointsEnabled) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SHOW-PROCEDURE-INVOCATION-HIERARCHY-AT-PAUSE-FROM-BREAKPOINT
   * @return the value of the SHOW-PROCEDURE-INVOCATION-HIERARCHY-AT-PAUSE-FROM-BREAKPOINT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SHOW-PROCEDURE-INVOCATION-HIERARCHY-AT-PAUSE-FROM-BREAKPOINT is : 
   * BooleanTruthValue
   *
   */
  public boolean getShowProcedureInvocationHierarchyAtPauseFromBreakpoint() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SHOW-PROCEDURE-INVOCATION-HIERARCHY-AT-PAUSE-FROM-BREAKPOINT
   * @param showProcedureInvocationHierarchyAtPauseFromBreakpoint new value to conclude for SHOW-PROCEDURE-INVOCATION-HIERARCHY-AT-PAUSE-FROM-BREAKPOINT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setShowProcedureInvocationHierarchyAtPauseFromBreakpoint(boolean showProcedureInvocationHierarchyAtPauseFromBreakpoint) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DISASSEMBLER-ENABLED?
   * @return the value of the DISASSEMBLER-ENABLED? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DISASSEMBLER-ENABLED? is : 
   * BooleanTruthValue
   *
   */
  public boolean getDisassemblerEnabled() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DISASSEMBLER-ENABLED?
   * @param disassemblerEnabled new value to conclude for DISASSEMBLER-ENABLED?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDisassemblerEnabled(boolean disassemblerEnabled) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GENERATE-SOURCE-ANNOTATION-INFO
   * @return the value of the GENERATE-SOURCE-ANNOTATION-INFO attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GENERATE-SOURCE-ANNOTATION-INFO is : 
   * BooleanTruthValue
   *
   */
  public boolean getGenerateSourceAnnotationInfo() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GENERATE-SOURCE-ANNOTATION-INFO
   * @param generateSourceAnnotationInfo new value to conclude for GENERATE-SOURCE-ANNOTATION-INFO
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGenerateSourceAnnotationInfo(boolean generateSourceAnnotationInfo) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TRACING-FILE
   * @return the value of the TRACING-FILE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TRACING-FILE is : 
   * (OR Symbol
      Text)
   *
   */
  public java.lang.Object getTracingFile() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TRACING-FILE
   * @param tracingFile new value to conclude for TRACING-FILE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTracingFile(java.lang.Object tracingFile) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DYNAMIC-DISPLAY-DELAY-IN-MILLISECONDS
   * @return the value of the DYNAMIC-DISPLAY-DELAY-IN-MILLISECONDS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DYNAMIC-DISPLAY-DELAY-IN-MILLISECONDS is : 
   * (OR NoItem
      Integer)
   *
   */
  public java.lang.Integer getDynamicDisplayDelayInMilliseconds() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DYNAMIC-DISPLAY-DELAY-IN-MILLISECONDS
   * @param dynamicDisplayDelayInMilliseconds new value to conclude for DYNAMIC-DISPLAY-DELAY-IN-MILLISECONDS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDynamicDisplayDelayInMilliseconds(java.lang.Integer dynamicDisplayDelayInMilliseconds) throws G2AccessException;

}
