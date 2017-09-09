/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:51:35 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2glParametersImpl extends com.gensym.classes.SystemTableImpl implements G2glParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2glParametersImpl() {
    super();
  }

  public G2glParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2glParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- BREAK-ON-ALL-EXECUTION-FAULTS
   * @param breakOnAllExecutionFaults new value to conclude for BREAK-ON-ALL-EXECUTION-FAULTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setBreakOnAllExecutionFaults(boolean breakOnAllExecutionFaults) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.BREAK_ON_ALL_EXECUTION_FAULTS_, new Boolean (breakOnAllExecutionFaults));
  }

  /**
   * Generated Property Getter for attribute -- BREAK-ON-ALL-EXECUTION-FAULTS
   * @return the value of the BREAK-ON-ALL-EXECUTION-FAULTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getBreakOnAllExecutionFaults() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.BREAK_ON_ALL_EXECUTION_FAULTS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- SUPPRESS-UNSPECIFIED-PARTNER-LINK-VARIABLE-TYPE-FAULTS
   * @param suppressUnspecifiedPartnerLinkVariableTypeFaults new value to conclude for SUPPRESS-UNSPECIFIED-PARTNER-LINK-VARIABLE-TYPE-FAULTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSuppressUnspecifiedPartnerLinkVariableTypeFaults(boolean suppressUnspecifiedPartnerLinkVariableTypeFaults) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SUPPRESS_UNSPECIFIED_PARTNER_LINK_VARIABLE_TYPE_FAULTS_, new Boolean (suppressUnspecifiedPartnerLinkVariableTypeFaults));
  }

  /**
   * Generated Property Getter for attribute -- SUPPRESS-UNSPECIFIED-PARTNER-LINK-VARIABLE-TYPE-FAULTS
   * @return the value of the SUPPRESS-UNSPECIFIED-PARTNER-LINK-VARIABLE-TYPE-FAULTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getSuppressUnspecifiedPartnerLinkVariableTypeFaults() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SUPPRESS_UNSPECIFIED_PARTNER_LINK_VARIABLE_TYPE_FAULTS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- COMPILE-TEXT-ELEMENTS-IN-SOURCE-FOR-EXECUTION-DISPLAYS
   * @param compileTextElementsInSourceForExecutionDisplays new value to conclude for COMPILE-TEXT-ELEMENTS-IN-SOURCE-FOR-EXECUTION-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setCompileTextElementsInSourceForExecutionDisplays(boolean compileTextElementsInSourceForExecutionDisplays) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.COMPILE_TEXT_ELEMENTS_IN_SOURCE_FOR_EXECUTION_DISPLAYS_, new Boolean (compileTextElementsInSourceForExecutionDisplays));
  }

  /**
   * Generated Property Getter for attribute -- COMPILE-TEXT-ELEMENTS-IN-SOURCE-FOR-EXECUTION-DISPLAYS
   * @return the value of the COMPILE-TEXT-ELEMENTS-IN-SOURCE-FOR-EXECUTION-DISPLAYS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getCompileTextElementsInSourceForExecutionDisplays() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.COMPILE_TEXT_ELEMENTS_IN_SOURCE_FOR_EXECUTION_DISPLAYS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- DEFAULT-THREAD-TOKEN-COLOR
   * @param defaultThreadTokenColor new value to conclude for DEFAULT-THREAD-TOKEN-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDefaultThreadTokenColor(com.gensym.util.Symbol defaultThreadTokenColor) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DEFAULT_THREAD_TOKEN_COLOR_, defaultThreadTokenColor);
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-THREAD-TOKEN-COLOR
   * @return the value of the DEFAULT-THREAD-TOKEN-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getDefaultThreadTokenColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DEFAULT_THREAD_TOKEN_COLOR_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
