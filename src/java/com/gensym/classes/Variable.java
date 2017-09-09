/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Variable.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:19 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Variable extends com.gensym.classes.VariableOrParameter {

  public static final Symbol VARIABLE_ = com.gensym.util.symbol.G2ClassSymbols.VARIABLE_;
  static final Symbol g2ClassName = VARIABLE_;
  static final Symbol[] classInheritancePath = new Symbol[] {VARIABLE_, VARIABLE_OR_PARAMETER_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- OPTIONS
   * @return the value of the OPTIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for OPTIONS is : 
   * (Structure 
    FORWARD-CHAIN BooleanTruthValue
    FORWARD-CHAIN-EVEN-FOR-SAME-VALUE BooleanTruthValue
    BACKWARD-CHAIN
      (MEMBER BREADTH-FIRST DEPTH-FIRST DO-NOT-BACKWARD-CHAIN DO-NOT-SEEK-DATA)
    EXPLANATION-DATA BooleanTruthValue)
   *
   */
  public com.gensym.util.Structure getOptions() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- OPTIONS
   * @param options new value to conclude for OPTIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setOptions(com.gensym.util.Structure options) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- VALIDITY-INTERVAL
   * @return the value of the VALIDITY-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for VALIDITY-INTERVAL is : 
   * (OR (MEMBER SUPPLIED INDEFINITE)
      Integer)
   *
   */
  public java.lang.Object getValidityInterval() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- VALIDITY-INTERVAL
   * @param validityInterval new value to conclude for VALIDITY-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setValidityInterval(java.lang.Object validityInterval) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FORMULA
   * @return the value of the FORMULA attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FORMULA is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getFormula() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FORMULA
   * @param formula new value to conclude for FORMULA
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFormula(java.lang.String formula) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SIMULATION-DETAILS
   * @return the value of the SIMULATION-DETAILS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SIMULATION-DETAILS is : 
   * (Class SIMULATION-SUBTABLE)
   *
   */
  public com.gensym.classes.SimulationSubtable getSimulationDetails() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DATA-SERVER
   * @return the value of the DATA-SERVER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DATA-SERVER is : 
   * (OR (MEMBER INFERENCE-ENGINE G2-SIMULATOR G2-METER GFI-DATA-SERVER GSI-DATA-SERVER G2-DATA-SERVER)
      Symbol)
   *
   */
  public com.gensym.util.Symbol getDataServer() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DATA-SERVER
   * @param dataServer new value to conclude for DATA-SERVER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDataServer(com.gensym.util.Symbol dataServer) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DEFAULT-UPDATE-INTERVAL
   * @return the value of the DEFAULT-UPDATE-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DEFAULT-UPDATE-INTERVAL is : 
   * (OR Quantity
      NoItem)
   *
   */
  public java.lang.Number getDefaultUpdateInterval() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DEFAULT-UPDATE-INTERVAL
   * @param defaultUpdateInterval new value to conclude for DEFAULT-UPDATE-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDefaultUpdateInterval(java.lang.Number defaultUpdateInterval) throws G2AccessException;

}
