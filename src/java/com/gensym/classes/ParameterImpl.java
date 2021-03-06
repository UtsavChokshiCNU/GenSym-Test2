/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ParameterImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:11:25 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class ParameterImpl extends com.gensym.classes.VariableOrParameterImpl implements Parameter {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public ParameterImpl() {
    super();
  }

  public ParameterImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public ParameterImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- OPTIONS
   * @param options new value to conclude for OPTIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setOptions(com.gensym.util.Structure options) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.OPTIONS_, options);
  }

  /**
   * Generated Property Getter for attribute -- OPTIONS
   * @return the value of the OPTIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getOptions() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.OPTIONS_);
    return (com.gensym.util.Structure)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
