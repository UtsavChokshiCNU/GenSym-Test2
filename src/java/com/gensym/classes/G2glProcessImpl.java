/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glProcessImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:53:37 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2glProcessImpl extends com.gensym.classes.G2glDefinitionImpl implements G2glProcess {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2glProcessImpl() {
    super();
  }

  public G2glProcessImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2glProcessImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- CALLABLE-AS-A-PROCEDURE
   * @param callableAsAProcedure new value to conclude for CALLABLE-AS-A-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setCallableAsAProcedure(boolean callableAsAProcedure) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.CALLABLE_AS_A_PROCEDURE_, new Boolean (callableAsAProcedure));
  }

  /**
   * Generated Property Getter for attribute -- CALLABLE-AS-A-PROCEDURE
   * @return the value of the CALLABLE-AS-A-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getCallableAsAProcedure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CALLABLE_AS_A_PROCEDURE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- ENABLE-INSTANCE-COMPENSATION
   * @param enableInstanceCompensation new value to conclude for ENABLE-INSTANCE-COMPENSATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setEnableInstanceCompensation(boolean enableInstanceCompensation) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ENABLE_INSTANCE_COMPENSATION_, new Boolean (enableInstanceCompensation));
  }

  /**
   * Generated Property Getter for attribute -- ENABLE-INSTANCE-COMPENSATION
   * @return the value of the ENABLE-INSTANCE-COMPENSATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getEnableInstanceCompensation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ENABLE_INSTANCE_COMPENSATION_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- THIS-IS-AN-ABSTRACT-PROCESS
   * @param thisIsAnAbstractProcess new value to conclude for THIS-IS-AN-ABSTRACT-PROCESS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setThisIsAnAbstractProcess(boolean thisIsAnAbstractProcess) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.THIS_IS_AN_ABSTRACT_PROCESS_, new Boolean (thisIsAnAbstractProcess));
  }

  /**
   * Generated Property Getter for attribute -- THIS-IS-AN-ABSTRACT-PROCESS
   * @return the value of the THIS-IS-AN-ABSTRACT-PROCESS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getThisIsAnAbstractProcess() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.THIS_IS_AN_ABSTRACT_PROCESS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- BREAK-ON-EXECUTION-FAULT
   * @param breakOnExecutionFault new value to conclude for BREAK-ON-EXECUTION-FAULT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setBreakOnExecutionFault(boolean breakOnExecutionFault) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.BREAK_ON_EXECUTION_FAULT_, new Boolean (breakOnExecutionFault));
  }

  /**
   * Generated Property Getter for attribute -- BREAK-ON-EXECUTION-FAULT
   * @return the value of the BREAK-ON-EXECUTION-FAULT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getBreakOnExecutionFault() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.BREAK_ON_EXECUTION_FAULT_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- THREAD-TOKEN-CLASS
   * @param threadTokenClass new value to conclude for THREAD-TOKEN-CLASS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setThreadTokenClass(com.gensym.util.Symbol threadTokenClass) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.THREAD_TOKEN_CLASS_, threadTokenClass);
  }

  /**
   * Generated Property Getter for attribute -- THREAD-TOKEN-CLASS
   * @return the value of the THREAD-TOKEN-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getThreadTokenClass() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.THREAD_TOKEN_CLASS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- LATEST-ATTEMPTED-COMPILATION-VERSION-NUMBER
   * @return the value of the LATEST-ATTEMPTED-COMPILATION-VERSION-NUMBER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Integer getLatestAttemptedCompilationVersionNumber() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.LATEST_ATTEMPTED_COMPILATION_VERSION_NUMBER_);
    return (java.lang.Integer)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-ERRORS-IN-LATEST-ATTEMPTED-COMPILATION
   * @return the value of the NUMBER-OF-ERRORS-IN-LATEST-ATTEMPTED-COMPILATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getNumberOfErrorsInLatestAttemptedCompilation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.NUMBER_OF_ERRORS_IN_LATEST_ATTEMPTED_COMPILATION_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-WARNINGS-IN-LATEST-ATTEMPTED-COMPILATION
   * @return the value of the NUMBER-OF-WARNINGS-IN-LATEST-ATTEMPTED-COMPILATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getNumberOfWarningsInLatestAttemptedCompilation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.NUMBER_OF_WARNINGS_IN_LATEST_ATTEMPTED_COMPILATION_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- G2GL-PROCESS-COMPILATION-VERSION-NUMBER
   * @return the value of the G2GL-PROCESS-COMPILATION-VERSION-NUMBER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Integer getG2glProcessCompilationVersionNumber() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2GL_PROCESS_COMPILATION_VERSION_NUMBER_);
    return (java.lang.Integer)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2GL-PROCESS-PROCEDURE-SIGNATURE
   * @return the value of the G2GL-PROCESS-PROCEDURE-SIGNATURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2glProcessProcedureSignature() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2GL_PROCESS_PROCEDURE_SIGNATURE_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
