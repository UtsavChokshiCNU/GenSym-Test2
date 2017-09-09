/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glProcess.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:53:34 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2glProcess extends com.gensym.classes.G2glDefinition {

  public static final Symbol G2GL_PROCESS_ = com.gensym.util.symbol.G2ClassSymbols.G2GL_PROCESS_;
  static final Symbol g2ClassName = G2GL_PROCESS_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2GL_PROCESS_, G2GL_DEFINITION_, G2GL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- CALLABLE-AS-A-PROCEDURE
   * @return the value of the CALLABLE-AS-A-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CALLABLE-AS-A-PROCEDURE is : 
   * BooleanTruthValue
   *
   */
  public boolean getCallableAsAProcedure() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CALLABLE-AS-A-PROCEDURE
   * @param callableAsAProcedure new value to conclude for CALLABLE-AS-A-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setCallableAsAProcedure(boolean callableAsAProcedure) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ENABLE-INSTANCE-COMPENSATION
   * @return the value of the ENABLE-INSTANCE-COMPENSATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ENABLE-INSTANCE-COMPENSATION is : 
   * BooleanTruthValue
   *
   */
  public boolean getEnableInstanceCompensation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ENABLE-INSTANCE-COMPENSATION
   * @param enableInstanceCompensation new value to conclude for ENABLE-INSTANCE-COMPENSATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEnableInstanceCompensation(boolean enableInstanceCompensation) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- THIS-IS-AN-ABSTRACT-PROCESS
   * @return the value of the THIS-IS-AN-ABSTRACT-PROCESS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for THIS-IS-AN-ABSTRACT-PROCESS is : 
   * BooleanTruthValue
   *
   */
  public boolean getThisIsAnAbstractProcess() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- THIS-IS-AN-ABSTRACT-PROCESS
   * @param thisIsAnAbstractProcess new value to conclude for THIS-IS-AN-ABSTRACT-PROCESS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setThisIsAnAbstractProcess(boolean thisIsAnAbstractProcess) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- BREAK-ON-EXECUTION-FAULT
   * @return the value of the BREAK-ON-EXECUTION-FAULT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for BREAK-ON-EXECUTION-FAULT is : 
   * BooleanTruthValue
   *
   */
  public boolean getBreakOnExecutionFault() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- BREAK-ON-EXECUTION-FAULT
   * @param breakOnExecutionFault new value to conclude for BREAK-ON-EXECUTION-FAULT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setBreakOnExecutionFault(boolean breakOnExecutionFault) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- THREAD-TOKEN-CLASS
   * @return the value of the THREAD-TOKEN-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for THREAD-TOKEN-CLASS is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getThreadTokenClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- THREAD-TOKEN-CLASS
   * @param threadTokenClass new value to conclude for THREAD-TOKEN-CLASS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setThreadTokenClass(com.gensym.util.Symbol threadTokenClass) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- LATEST-ATTEMPTED-COMPILATION-VERSION-NUMBER
   * @return the value of the LATEST-ATTEMPTED-COMPILATION-VERSION-NUMBER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LATEST-ATTEMPTED-COMPILATION-VERSION-NUMBER is : 
   * (OR NoItem
      Integer)
   *
   */
  public java.lang.Integer getLatestAttemptedCompilationVersionNumber() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-ERRORS-IN-LATEST-ATTEMPTED-COMPILATION
   * @return the value of the NUMBER-OF-ERRORS-IN-LATEST-ATTEMPTED-COMPILATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NUMBER-OF-ERRORS-IN-LATEST-ATTEMPTED-COMPILATION is : 
   * Integer
   *
   */
  public int getNumberOfErrorsInLatestAttemptedCompilation() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-WARNINGS-IN-LATEST-ATTEMPTED-COMPILATION
   * @return the value of the NUMBER-OF-WARNINGS-IN-LATEST-ATTEMPTED-COMPILATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NUMBER-OF-WARNINGS-IN-LATEST-ATTEMPTED-COMPILATION is : 
   * Integer
   *
   */
  public int getNumberOfWarningsInLatestAttemptedCompilation() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2GL-PROCESS-COMPILATION-VERSION-NUMBER
   * @return the value of the G2GL-PROCESS-COMPILATION-VERSION-NUMBER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2GL-PROCESS-COMPILATION-VERSION-NUMBER is : 
   * (OR NoItem
      Integer)
   *
   */
  public java.lang.Integer getG2glProcessCompilationVersionNumber() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2GL-PROCESS-PROCEDURE-SIGNATURE
   * @return the value of the G2GL-PROCESS-PROCEDURE-SIGNATURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2GL-PROCESS-PROCEDURE-SIGNATURE is : 
   * (OR (MEMBER NO-SIGNATURE)
      (Sequence 
        (Structure 
          VARIABLE-NAME Symbol
          VARIABLE-TYPE
            (OR (MEMBER GENERAL INTEGER FLOAT TRUTH-VALUE TEXT SYMBOL CLASS)
                (Sequence Symbol))
          DEFAULT-VALUE
            (OR NoItem
                Integer
                Float
                BooleanTruthValue
                Text
                Symbol)))))
   *
   */
  public java.lang.Object getG2glProcessProcedureSignature() throws G2AccessException;

}
