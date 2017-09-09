/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      SavingParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:07:52 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class SavingParametersImpl extends com.gensym.classes.SystemTableImpl implements SavingParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public SavingParametersImpl() {
    super();
  }

  public SavingParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public SavingParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- DEFAULT-PRIORITY-FOR-RUNTIME-SAVING
   * @param defaultPriorityForRuntimeSaving new value to conclude for DEFAULT-PRIORITY-FOR-RUNTIME-SAVING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDefaultPriorityForRuntimeSaving(com.gensym.util.Symbol defaultPriorityForRuntimeSaving) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DEFAULT_PRIORITY_FOR_RUNTIME_SAVING_, defaultPriorityForRuntimeSaving);
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-PRIORITY-FOR-RUNTIME-SAVING
   * @return the value of the DEFAULT-PRIORITY-FOR-RUNTIME-SAVING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getDefaultPriorityForRuntimeSaving() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DEFAULT_PRIORITY_FOR_RUNTIME_SAVING_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- IDENTIFIER-OF-BASIS-KB
   * @return the value of the IDENTIFIER-OF-BASIS-KB attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getIdentifierOfBasisKb() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.IDENTIFIER_OF_BASIS_KB_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- KB-FILE-COMMENT
   * @param kbFileComment new value to conclude for KB-FILE-COMMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setKbFileComment(java.lang.String kbFileComment) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.KB_FILE_COMMENT_, kbFileComment);
  }

  /**
   * Generated Property Getter for attribute -- KB-FILE-COMMENT
   * @return the value of the KB-FILE-COMMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getKbFileComment() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.KB_FILE_COMMENT_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ENABLE-KB-CHANGE-LOGGING
   * @param enableKbChangeLogging new value to conclude for ENABLE-KB-CHANGE-LOGGING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setEnableKbChangeLogging(boolean enableKbChangeLogging) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ENABLE_KB_CHANGE_LOGGING_, new Boolean (enableKbChangeLogging));
  }

  /**
   * Generated Property Getter for attribute -- ENABLE-KB-CHANGE-LOGGING
   * @return the value of the ENABLE-KB-CHANGE-LOGGING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getEnableKbChangeLogging() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ENABLE_KB_CHANGE_LOGGING_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
