/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GopeOptimizationObject.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Thu Dec 19 22:32:53 EST 2002
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

public interface GopeOptimizationObject extends com.gensym.classes.Object, com.gensym.classes.modules.grtl.GrtlEventSource {

  public static final Symbol GOPE_OPTIMIZATION_OBJECT_ = Symbol.intern ("GOPE-OPTIMIZATION-OBJECT");
  static final Symbol g2ClassName = GOPE_OPTIMIZATION_OBJECT_;
  static final Symbol[] classInheritancePath = new Symbol[] {GOPE_OPTIMIZATION_OBJECT_, OBJECT_, GRTL_EVENT_SOURCE_, GRTL_ITEM_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- IS-MINIMIZATION-PROBLEM
   * @return the value of the IS-MINIMIZATION-PROBLEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for IS-MINIMIZATION-PROBLEM is : 
   * BooleanTruthValue
   *
   */
  public boolean getIsMinimizationProblem() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- IS-MINIMIZATION-PROBLEM
   * @param isMinimizationProblem new value to conclude for IS-MINIMIZATION-PROBLEM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIsMinimizationProblem(boolean isMinimizationProblem) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- XINITS
   * @return the value of the XINITS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for XINITS is : 
   * (Class FLOAT-ARRAY)
   *
   */
  public com.gensym.classes.FloatArray getXinits() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- XINITS
   * @param xinits new value to conclude for XINITS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setXinits(com.gensym.classes.FloatArray xinits) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- X
   * @return the value of the X attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for X is : 
   * (Class FLOAT-ARRAY)
   *
   */
  public com.gensym.classes.FloatArray getX() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- X
   * @param x new value to conclude for X
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setX(com.gensym.classes.FloatArray x) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- EXTRPARAM
   * @return the value of the EXTRPARAM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for EXTRPARAM is : 
   * (Class FLOAT-ARRAY)
   *
   */
  public com.gensym.classes.FloatArray getExtrparam() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- EXTRPARAM
   * @param extrparam new value to conclude for EXTRPARAM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setExtrparam(com.gensym.classes.FloatArray extrparam) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- XUBS
   * @return the value of the XUBS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for XUBS is : 
   * (Class FLOAT-ARRAY)
   *
   */
  public com.gensym.classes.FloatArray getXubs() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- XUBS
   * @param xubs new value to conclude for XUBS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setXubs(com.gensym.classes.FloatArray xubs) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- XLBS
   * @return the value of the XLBS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for XLBS is : 
   * (Class FLOAT-ARRAY)
   *
   */
  public com.gensym.classes.FloatArray getXlbs() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- XLBS
   * @param xlbs new value to conclude for XLBS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setXlbs(com.gensym.classes.FloatArray xlbs) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-CONSTRAINTS
   * @return the value of the NUMBER-OF-CONSTRAINTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NUMBER-OF-CONSTRAINTS is : 
   * Integer
   *
   */
  public int getNumberOfConstraints() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-CONSTRAINTS
   * @param numberOfConstraints new value to conclude for NUMBER-OF-CONSTRAINTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNumberOfConstraints(int numberOfConstraints) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SENSE-OF-CONSTRAINTS
   * @return the value of the SENSE-OF-CONSTRAINTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SENSE-OF-CONSTRAINTS is : 
   * Text
   *
   */
  public java.lang.String getSenseOfConstraints() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SENSE-OF-CONSTRAINTS
   * @param senseOfConstraints new value to conclude for SENSE-OF-CONSTRAINTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSenseOfConstraints(java.lang.String senseOfConstraints) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- RHV
   * @return the value of the RHV attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for RHV is : 
   * (Class FLOAT-ARRAY)
   *
   */
  public com.gensym.classes.FloatArray getRhv() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- RHV
   * @param rhv new value to conclude for RHV
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRhv(com.gensym.classes.FloatArray rhv) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- LHV
   * @return the value of the LHV attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LHV is : 
   * (Class FLOAT-ARRAY)
   *
   */
  public com.gensym.classes.FloatArray getLhv() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LHV
   * @param lhv new value to conclude for LHV
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLhv(com.gensym.classes.FloatArray lhv) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- Y
   * @return the value of the Y attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for Y is : 
   * Float
   *
   */
  public double getY() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- Y
   * @param y new value to conclude for Y
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setY(double y) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NAME-OF-GSI-INTERFACE
   * @return the value of the NAME-OF-GSI-INTERFACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NAME-OF-GSI-INTERFACE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getNameOfGsiInterface() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NAME-OF-GSI-INTERFACE
   * @param nameOfGsiInterface new value to conclude for NAME-OF-GSI-INTERFACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNameOfGsiInterface(com.gensym.util.Symbol nameOfGsiInterface) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NAME-OF-PROBLEM-DLL
   * @return the value of the NAME-OF-PROBLEM-DLL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NAME-OF-PROBLEM-DLL is : 
   * Text
   *
   */
  public java.lang.String getNameOfProblemDll() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NAME-OF-PROBLEM-DLL
   * @param nameOfProblemDll new value to conclude for NAME-OF-PROBLEM-DLL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNameOfProblemDll(java.lang.String nameOfProblemDll) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FINAL-STATUS
   * @return the value of the FINAL-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FINAL-STATUS is : 
   * Integer
   *
   */
  public int getFinalStatus() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FINAL-STATUS
   * @param finalStatus new value to conclude for FINAL-STATUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFinalStatus(int finalStatus) throws G2AccessException;

}
