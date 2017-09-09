/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      InferenceEngineParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:57:26 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface InferenceEngineParameters extends com.gensym.classes.SystemTable {

  public static final Symbol INFERENCE_ENGINE_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.INFERENCE_ENGINE_PARAMETERS_;
  static final Symbol g2ClassName = INFERENCE_ENGINE_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {INFERENCE_ENGINE_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- RECURSION-LIMIT
   * @return the value of the RECURSION-LIMIT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for RECURSION-LIMIT is : 
   * Integer
   *
   */
  public int getRecursionLimit() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- RECURSION-LIMIT
   * @param recursionLimit new value to conclude for RECURSION-LIMIT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRecursionLimit(int recursionLimit) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TRUTH-THRESHOLD
   * @return the value of the TRUTH-THRESHOLD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TRUTH-THRESHOLD is : 
   * BooleanTruthValue
   *
   */
  public boolean getTruthThreshold() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TRUTH-THRESHOLD
   * @param truthThreshold new value to conclude for TRUTH-THRESHOLD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTruthThreshold(boolean truthThreshold) throws G2AccessException;

}
