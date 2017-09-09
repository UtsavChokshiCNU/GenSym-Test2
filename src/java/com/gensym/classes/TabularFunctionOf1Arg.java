/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      TabularFunctionOf1Arg.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:10:48 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface TabularFunctionOf1Arg extends com.gensym.classes.TabularFunction {

  public static final Symbol TABULAR_FUNCTION_OF_1_ARG_ = com.gensym.util.symbol.G2ClassSymbols.TABULAR_FUNCTION_OF_1_ARG_;
  static final Symbol g2ClassName = TABULAR_FUNCTION_OF_1_ARG_;
  static final Symbol[] classInheritancePath = new Symbol[] {TABULAR_FUNCTION_OF_1_ARG_, TABULAR_FUNCTION_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- KEEP-SORTED
   * @return the value of the KEEP-SORTED attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for KEEP-SORTED is : 
   * (MEMBER NO ARGS VALUES)
   *
   */
  public com.gensym.util.Symbol getKeepSorted() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- KEEP-SORTED
   * @param keepSorted new value to conclude for KEEP-SORTED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setKeepSorted(com.gensym.util.Symbol keepSorted) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INTERPOLATE
   * @return the value of the INTERPOLATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INTERPOLATE is : 
   * BooleanTruthValue
   *
   */
  public boolean getInterpolate() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INTERPOLATE
   * @param interpolate new value to conclude for INTERPOLATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInterpolate(boolean interpolate) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- VALUES-FOR-TABLE-OF-VALUES
   * @return the value of the VALUES-FOR-TABLE-OF-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for VALUES-FOR-TABLE-OF-VALUES is : 
   * (Sequence 
    (Structure 
      X
        (OR NoItem
            Symbol
            Integer
            Float
            Text)
      F-OF-X
        (OR NoItem
            Symbol
            Integer
            Float
            Text))))
   *
   */
  public com.gensym.util.Sequence getValuesForTableOfValues() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- VALUES-FOR-TABLE-OF-VALUES
   * @param valuesForTableOfValues new value to conclude for VALUES-FOR-TABLE-OF-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setValuesForTableOfValues(com.gensym.util.Sequence valuesForTableOfValues) throws G2AccessException;

}
