/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Parameter.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:11:21 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Parameter extends com.gensym.classes.VariableOrParameter {

  public static final Symbol PARAMETER_ = com.gensym.util.symbol.G2ClassSymbols.PARAMETER_;
  static final Symbol g2ClassName = PARAMETER_;
  static final Symbol[] classInheritancePath = new Symbol[] {PARAMETER_, VARIABLE_OR_PARAMETER_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


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

}
