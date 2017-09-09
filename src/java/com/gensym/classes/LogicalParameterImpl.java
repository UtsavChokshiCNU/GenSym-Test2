/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      LogicalParameterImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:01 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class LogicalParameterImpl extends com.gensym.classes.ParameterImpl implements LogicalParameter {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public LogicalParameterImpl() {
    super();
  }

  public LogicalParameterImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public LogicalParameterImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- INITIAL-VALUE
   * @param initialValue new value to conclude for INITIAL-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setInitialValue(boolean initialValue) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.INITIAL_VALUE_, new Boolean (initialValue));
  }

  /**
   * Generated Property Getter for attribute -- INITIAL-VALUE
   * @return the value of the INITIAL-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getInitialValue() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INITIAL_VALUE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
