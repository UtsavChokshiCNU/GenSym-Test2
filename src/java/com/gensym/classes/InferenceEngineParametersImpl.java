/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      InferenceEngineParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:57:31 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class InferenceEngineParametersImpl extends com.gensym.classes.SystemTableImpl implements InferenceEngineParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public InferenceEngineParametersImpl() {
    super();
  }

  public InferenceEngineParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public InferenceEngineParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- RECURSION-LIMIT
   * @param recursionLimit new value to conclude for RECURSION-LIMIT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRecursionLimit(int recursionLimit) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.RECURSION_LIMIT_, recursionLimit);
  }

  /**
   * Generated Property Getter for attribute -- RECURSION-LIMIT
   * @return the value of the RECURSION-LIMIT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getRecursionLimit() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.RECURSION_LIMIT_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- TRUTH-THRESHOLD
   * @param truthThreshold new value to conclude for TRUTH-THRESHOLD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTruthThreshold(boolean truthThreshold) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TRUTH_THRESHOLD_, new Boolean (truthThreshold));
  }

  /**
   * Generated Property Getter for attribute -- TRUTH-THRESHOLD
   * @return the value of the TRUTH-THRESHOLD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getTruthThreshold() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TRUTH_THRESHOLD_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
