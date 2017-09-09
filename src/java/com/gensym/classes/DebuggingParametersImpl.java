/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      DebuggingParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:37:40 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class DebuggingParametersImpl extends com.gensym.classes.SystemTableImpl implements DebuggingParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public DebuggingParametersImpl() {
    super();
  }

  public DebuggingParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public DebuggingParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- WARNING-MESSAGE-LEVEL
   * @param warningMessageLevel new value to conclude for WARNING-MESSAGE-LEVEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setWarningMessageLevel(com.gensym.util.Symbol warningMessageLevel) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.WARNING_MESSAGE_LEVEL_, warningMessageLevel);
  }

  /**
   * Generated Property Getter for attribute -- WARNING-MESSAGE-LEVEL
   * @return the value of the WARNING-MESSAGE-LEVEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getWarningMessageLevel() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.WARNING_MESSAGE_LEVEL_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TRACING-MESSAGE-LEVEL
   * @param tracingMessageLevel new value to conclude for TRACING-MESSAGE-LEVEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTracingMessageLevel(com.gensym.util.Symbol tracingMessageLevel) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TRACING_MESSAGE_LEVEL_, tracingMessageLevel);
  }

  /**
   * Generated Property Getter for attribute -- TRACING-MESSAGE-LEVEL
   * @return the value of the TRACING-MESSAGE-LEVEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getTracingMessageLevel() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TRACING_MESSAGE_LEVEL_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- BREAKPOINT-LEVEL
   * @param breakpointLevel new value to conclude for BREAKPOINT-LEVEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setBreakpointLevel(com.gensym.util.Symbol breakpointLevel) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.BREAKPOINT_LEVEL_, breakpointLevel);
  }

  /**
   * Generated Property Getter for attribute -- BREAKPOINT-LEVEL
   * @return the value of the BREAKPOINT-LEVEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getBreakpointLevel() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.BREAKPOINT_LEVEL_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SOURCE-STEPPING-LEVEL
   * @param sourceSteppingLevel new value to conclude for SOURCE-STEPPING-LEVEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSourceSteppingLevel(com.gensym.util.Symbol sourceSteppingLevel) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SOURCE_STEPPING_LEVEL_, sourceSteppingLevel);
  }

  /**
   * Generated Property Getter for attribute -- SOURCE-STEPPING-LEVEL
   * @return the value of the SOURCE-STEPPING-LEVEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getSourceSteppingLevel() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SOURCE_STEPPING_LEVEL_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TRACING-AND-BREAKPOINTS-ENABLED?
   * @param tracingAndBreakpointsEnabled new value to conclude for TRACING-AND-BREAKPOINTS-ENABLED?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTracingAndBreakpointsEnabled(boolean tracingAndBreakpointsEnabled) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TRACING_AND_BREAKPOINTS_ENABLEDQ_, new Boolean (tracingAndBreakpointsEnabled));
  }

  /**
   * Generated Property Getter for attribute -- TRACING-AND-BREAKPOINTS-ENABLED?
   * @return the value of the TRACING-AND-BREAKPOINTS-ENABLED? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getTracingAndBreakpointsEnabled() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TRACING_AND_BREAKPOINTS_ENABLEDQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- SHOW-PROCEDURE-INVOCATION-HIERARCHY-AT-PAUSE-FROM-BREAKPOINT
   * @param showProcedureInvocationHierarchyAtPauseFromBreakpoint new value to conclude for SHOW-PROCEDURE-INVOCATION-HIERARCHY-AT-PAUSE-FROM-BREAKPOINT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setShowProcedureInvocationHierarchyAtPauseFromBreakpoint(boolean showProcedureInvocationHierarchyAtPauseFromBreakpoint) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SHOW_PROCEDURE_INVOCATION_HIERARCHY_AT_PAUSE_FROM_BREAKPOINT_, new Boolean (showProcedureInvocationHierarchyAtPauseFromBreakpoint));
  }

  /**
   * Generated Property Getter for attribute -- SHOW-PROCEDURE-INVOCATION-HIERARCHY-AT-PAUSE-FROM-BREAKPOINT
   * @return the value of the SHOW-PROCEDURE-INVOCATION-HIERARCHY-AT-PAUSE-FROM-BREAKPOINT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getShowProcedureInvocationHierarchyAtPauseFromBreakpoint() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SHOW_PROCEDURE_INVOCATION_HIERARCHY_AT_PAUSE_FROM_BREAKPOINT_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- DISASSEMBLER-ENABLED?
   * @param disassemblerEnabled new value to conclude for DISASSEMBLER-ENABLED?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDisassemblerEnabled(boolean disassemblerEnabled) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DISASSEMBLER_ENABLEDQ_, new Boolean (disassemblerEnabled));
  }

  /**
   * Generated Property Getter for attribute -- DISASSEMBLER-ENABLED?
   * @return the value of the DISASSEMBLER-ENABLED? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getDisassemblerEnabled() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DISASSEMBLER_ENABLEDQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- GENERATE-SOURCE-ANNOTATION-INFO
   * @param generateSourceAnnotationInfo new value to conclude for GENERATE-SOURCE-ANNOTATION-INFO
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGenerateSourceAnnotationInfo(boolean generateSourceAnnotationInfo) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GENERATE_SOURCE_ANNOTATION_INFO_, new Boolean (generateSourceAnnotationInfo));
  }

  /**
   * Generated Property Getter for attribute -- GENERATE-SOURCE-ANNOTATION-INFO
   * @return the value of the GENERATE-SOURCE-ANNOTATION-INFO attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getGenerateSourceAnnotationInfo() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GENERATE_SOURCE_ANNOTATION_INFO_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- TRACING-FILE
   * @param tracingFile new value to conclude for TRACING-FILE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTracingFile(java.lang.Object tracingFile) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TRACING_FILE_, tracingFile);
  }

  /**
   * Generated Property Getter for attribute -- TRACING-FILE
   * @return the value of the TRACING-FILE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getTracingFile() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TRACING_FILE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DYNAMIC-DISPLAY-DELAY-IN-MILLISECONDS
   * @param dynamicDisplayDelayInMilliseconds new value to conclude for DYNAMIC-DISPLAY-DELAY-IN-MILLISECONDS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDynamicDisplayDelayInMilliseconds(java.lang.Integer dynamicDisplayDelayInMilliseconds) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DYNAMIC_DISPLAY_DELAY_IN_MILLISECONDS_, dynamicDisplayDelayInMilliseconds);
  }

  /**
   * Generated Property Getter for attribute -- DYNAMIC-DISPLAY-DELAY-IN-MILLISECONDS
   * @return the value of the DYNAMIC-DISPLAY-DELAY-IN-MILLISECONDS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Integer getDynamicDisplayDelayInMilliseconds() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DYNAMIC_DISPLAY_DELAY_IN_MILLISECONDS_);
    return (java.lang.Integer)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
