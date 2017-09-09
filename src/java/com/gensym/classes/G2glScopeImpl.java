/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glScopeImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:53:49 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2glScopeImpl extends com.gensym.classes.G2glActivityWithBodyImpl implements G2glScope {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2glScopeImpl() {
    super();
  }

  public G2glScopeImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2glScopeImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- VARIABLE-ACCESS-SERIALIZABLE
   * @param variableAccessSerializable new value to conclude for VARIABLE-ACCESS-SERIALIZABLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setVariableAccessSerializable(boolean variableAccessSerializable) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.VARIABLE_ACCESS_SERIALIZABLE_, new Boolean (variableAccessSerializable));
  }

  /**
   * Generated Property Getter for attribute -- VARIABLE-ACCESS-SERIALIZABLE
   * @return the value of the VARIABLE-ACCESS-SERIALIZABLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getVariableAccessSerializable() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.VARIABLE_ACCESS_SERIALIZABLE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
