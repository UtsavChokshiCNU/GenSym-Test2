/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GopeNlpOptimizationObjectImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Dec 20 00:11:38 EST 2002
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

public class GopeNlpOptimizationObjectImpl extends com.gensym.classes.modules.gope.GopeOptimizationObjectImpl implements GopeNlpOptimizationObject {


  static final long serialVersionUID = 2L;
  private static final Symbol USE_INTERNAL_OBJECTIVE_FUNCTION_ = Symbol.intern ("USE-INTERNAL-OBJECTIVE-FUNCTION");
  private static final Symbol NAME_OF_OBJECTIVE_FUNCTION_ = Symbol.intern ("NAME-OF-OBJECTIVE-FUNCTION");
  private static final Symbol NAME_OF_CONSTRAINT_FUNCTIONS_ = Symbol.intern ("NAME-OF-CONSTRAINT-FUNCTIONS");

  /* Generated constructors */

  public GopeNlpOptimizationObjectImpl() {
    super();
  }

  public GopeNlpOptimizationObjectImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- USE-INTERNAL-OBJECTIVE-FUNCTION
   * @param useInternalObjectiveFunction new value to conclude for USE-INTERNAL-OBJECTIVE-FUNCTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUseInternalObjectiveFunction(boolean useInternalObjectiveFunction) throws G2AccessException {
    setAttributeValue (USE_INTERNAL_OBJECTIVE_FUNCTION_, new Boolean (useInternalObjectiveFunction));
  }

  /**
   * Generated Property Getter for attribute -- USE-INTERNAL-OBJECTIVE-FUNCTION
   * @return the value of the USE-INTERNAL-OBJECTIVE-FUNCTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getUseInternalObjectiveFunction() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (USE_INTERNAL_OBJECTIVE_FUNCTION_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- NAME-OF-OBJECTIVE-FUNCTION
   * @param nameOfObjectiveFunction new value to conclude for NAME-OF-OBJECTIVE-FUNCTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNameOfObjectiveFunction(com.gensym.util.Symbol nameOfObjectiveFunction) throws G2AccessException {
    setAttributeValue (NAME_OF_OBJECTIVE_FUNCTION_, nameOfObjectiveFunction);
  }

  /**
   * Generated Property Getter for attribute -- NAME-OF-OBJECTIVE-FUNCTION
   * @return the value of the NAME-OF-OBJECTIVE-FUNCTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getNameOfObjectiveFunction() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (NAME_OF_OBJECTIVE_FUNCTION_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- NAME-OF-CONSTRAINT-FUNCTIONS
   * @param nameOfConstraintFunctions new value to conclude for NAME-OF-CONSTRAINT-FUNCTIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNameOfConstraintFunctions(com.gensym.util.Sequence nameOfConstraintFunctions) throws G2AccessException {
    setAttributeValue (NAME_OF_CONSTRAINT_FUNCTIONS_, nameOfConstraintFunctions);
  }

  /**
   * Generated Property Getter for attribute -- NAME-OF-CONSTRAINT-FUNCTIONS
   * @return the value of the NAME-OF-CONSTRAINT-FUNCTIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getNameOfConstraintFunctions() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (NAME_OF_CONSTRAINT_FUNCTIONS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_GOPE_OBJECTIVE_FUNCTION_ = Symbol.intern ("GOPE-OBJECTIVE-FUNCTION");
  private static final Symbol MethodName_GOPE_CALCULATE_OPTIMIZATION_ = Symbol.intern ("GOPE-CALCULATE-OPTIMIZATION");
  private static final Symbol MethodName_GOPE_CONSTRAINT_FUNCTION_ = Symbol.intern ("GOPE-CONSTRAINT-FUNCTION");
  private static final Symbol MethodName_GOPE_RETURN_RESULTS_ = Symbol.intern ("GOPE-RETURN-RESULTS");
  private static final Symbol MethodName_GOPE_INITIALIZE_ = Symbol.intern ("GOPE-INITIALIZE");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * GOPE-NLP-OPTIMIZATION-OBJECT::GOPE-OBJECTIVE-FUNCTION
   * @return the return from calling GOPE-OBJECTIVE-FUNCTION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GOPE-NLP-OPTIMIZATION-OBJECT,arg1:CLASS FLOAT-ARRAY) = (FLOAT)
   */
  public  double gopeObjectiveFunction(com.gensym.classes.FloatArray arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GOPE_OBJECTIVE_FUNCTION_, args);
      return ((Double)result).doubleValue ();
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GOPE-NLP-OPTIMIZATION-OBJECT::GOPE-CALCULATE-OPTIMIZATION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GOPE-NLP-OPTIMIZATION-OBJECT) = ()
   */
  public  void gopeCalculateOptimization() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_GOPE_CALCULATE_OPTIMIZATION_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GOPE-NLP-OPTIMIZATION-OBJECT::GOPE-CONSTRAINT-FUNCTION
   * @return the return from calling GOPE-CONSTRAINT-FUNCTION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GOPE-NLP-OPTIMIZATION-OBJECT,arg1:CLASS FLOAT-ARRAY,arg2:INTEGER) = (FLOAT)
   */
  public  double gopeConstraintFunction(com.gensym.classes.FloatArray arg1,int arg2) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,new Integer (arg2)};
      result = (java.lang.Object)callRPC(MethodName_GOPE_CONSTRAINT_FUNCTION_, args);
      return ((Double)result).doubleValue ();
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GOPE-NLP-OPTIMIZATION-OBJECT::GOPE-RETURN-RESULTS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GOPE-NLP-OPTIMIZATION-OBJECT,arg1:CLASS FLOAT-ARRAY) = ()
   */
  public  void gopeReturnResults(com.gensym.classes.FloatArray arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GOPE_RETURN_RESULTS_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GOPE-NLP-OPTIMIZATION-OBJECT::GOPE-INITIALIZE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GOPE-NLP-OPTIMIZATION-OBJECT,arg1:INTEGER,arg2:INTEGER,arg3:INTEGER) = ()
   */
  public  void gopeInitialize(int arg1,int arg2,int arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,new Integer (arg1),new Integer (arg2),new Integer (arg3)};
      result = (java.lang.Object)callRPC(MethodName_GOPE_INITIALIZE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
