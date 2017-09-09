/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GopeNlpOptimizationObject.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Thu Dec 19 22:33:37 EST 2002
 *
 */


package com.gensym.classes.modules.gope;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GopeNlpOptimizationObject extends com.gensym.classes.modules.gope.GopeOptimizationObject {

  public static final Symbol GOPE_NLP_OPTIMIZATION_OBJECT_ = Symbol.intern ("GOPE-NLP-OPTIMIZATION-OBJECT");
  static final Symbol g2ClassName = GOPE_NLP_OPTIMIZATION_OBJECT_;
  static final Symbol[] classInheritancePath = new Symbol[] {GOPE_NLP_OPTIMIZATION_OBJECT_, GOPE_OPTIMIZATION_OBJECT_, OBJECT_, GRTL_EVENT_SOURCE_, GRTL_ITEM_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- USE-INTERNAL-OBJECTIVE-FUNCTION
   * @return the value of the USE-INTERNAL-OBJECTIVE-FUNCTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for USE-INTERNAL-OBJECTIVE-FUNCTION is : 
   * BooleanTruthValue
   *
   */
  public boolean getUseInternalObjectiveFunction() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- USE-INTERNAL-OBJECTIVE-FUNCTION
   * @param useInternalObjectiveFunction new value to conclude for USE-INTERNAL-OBJECTIVE-FUNCTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUseInternalObjectiveFunction(boolean useInternalObjectiveFunction) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NAME-OF-OBJECTIVE-FUNCTION
   * @return the value of the NAME-OF-OBJECTIVE-FUNCTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NAME-OF-OBJECTIVE-FUNCTION is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getNameOfObjectiveFunction() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NAME-OF-OBJECTIVE-FUNCTION
   * @param nameOfObjectiveFunction new value to conclude for NAME-OF-OBJECTIVE-FUNCTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNameOfObjectiveFunction(com.gensym.util.Symbol nameOfObjectiveFunction) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NAME-OF-CONSTRAINT-FUNCTIONS
   * @return the value of the NAME-OF-CONSTRAINT-FUNCTIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NAME-OF-CONSTRAINT-FUNCTIONS is : 
   * (Sequence)
   *
   */
  public com.gensym.util.Sequence getNameOfConstraintFunctions() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NAME-OF-CONSTRAINT-FUNCTIONS
   * @param nameOfConstraintFunctions new value to conclude for NAME-OF-CONSTRAINT-FUNCTIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNameOfConstraintFunctions(com.gensym.util.Sequence nameOfConstraintFunctions) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * GOPE-NLP-OPTIMIZATION-OBJECT::GOPE-OBJECTIVE-FUNCTION
   * @return the return from calling GOPE-OBJECTIVE-FUNCTION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GOPE-NLP-OPTIMIZATION-OBJECT,arg1:CLASS FLOAT-ARRAY) = (FLOAT)
   */
  public  double gopeObjectiveFunction(com.gensym.classes.FloatArray arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GOPE-NLP-OPTIMIZATION-OBJECT::GOPE-CALCULATE-OPTIMIZATION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GOPE-NLP-OPTIMIZATION-OBJECT) = ()
   */
  public  void gopeCalculateOptimization() throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GOPE-NLP-OPTIMIZATION-OBJECT::GOPE-CONSTRAINT-FUNCTION
   * @return the return from calling GOPE-CONSTRAINT-FUNCTION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GOPE-NLP-OPTIMIZATION-OBJECT,arg1:CLASS FLOAT-ARRAY,arg2:INTEGER) = (FLOAT)
   */
  public  double gopeConstraintFunction(com.gensym.classes.FloatArray arg1,int arg2) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GOPE-NLP-OPTIMIZATION-OBJECT::GOPE-RETURN-RESULTS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GOPE-NLP-OPTIMIZATION-OBJECT,arg1:CLASS FLOAT-ARRAY) = ()
   */
  public  void gopeReturnResults(com.gensym.classes.FloatArray arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GOPE-NLP-OPTIMIZATION-OBJECT::GOPE-INITIALIZE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GOPE-NLP-OPTIMIZATION-OBJECT,arg1:INTEGER,arg2:INTEGER,arg3:INTEGER) = ()
   */
  public  void gopeInitialize(int arg1,int arg2,int arg3) throws G2AccessException;
  
}
