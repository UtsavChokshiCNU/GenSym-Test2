/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      TabularFunctionOf1ArgImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:10:49 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class TabularFunctionOf1ArgImpl extends com.gensym.classes.TabularFunctionImpl implements TabularFunctionOf1Arg {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public TabularFunctionOf1ArgImpl() {
    super();
  }

  public TabularFunctionOf1ArgImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public TabularFunctionOf1ArgImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- KEEP-SORTED
   * @param keepSorted new value to conclude for KEEP-SORTED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setKeepSorted(com.gensym.util.Symbol keepSorted) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.KEEP_SORTED_, keepSorted);
  }

  /**
   * Generated Property Getter for attribute -- KEEP-SORTED
   * @return the value of the KEEP-SORTED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getKeepSorted() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.KEEP_SORTED_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- INTERPOLATE
   * @param interpolate new value to conclude for INTERPOLATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setInterpolate(boolean interpolate) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.INTERPOLATE_, new Boolean (interpolate));
  }

  /**
   * Generated Property Getter for attribute -- INTERPOLATE
   * @return the value of the INTERPOLATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getInterpolate() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INTERPOLATE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- VALUES-FOR-TABLE-OF-VALUES
   * @param valuesForTableOfValues new value to conclude for VALUES-FOR-TABLE-OF-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setValuesForTableOfValues(com.gensym.util.Sequence valuesForTableOfValues) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.VALUES_FOR_TABLE_OF_VALUES_, valuesForTableOfValues);
  }

  /**
   * Generated Property Getter for attribute -- VALUES-FOR-TABLE-OF-VALUES
   * @return the value of the VALUES-FOR-TABLE-OF-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getValuesForTableOfValues() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.VALUES_FOR_TABLE_OF_VALUES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
