/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      MethodImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:47 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class MethodImpl extends com.gensym.classes.ProcedureImpl implements Method {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public MethodImpl() {
    super();
  }

  public MethodImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public MethodImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- SYNCHRONIZED
   * @param synchronized$ new value to conclude for SYNCHRONIZED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSynchronized(boolean synchronized$) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SYNCHRONIZED_, new Boolean (synchronized$));
  }

  /**
   * Generated Property Getter for attribute -- SYNCHRONIZED
   * @return the value of the SYNCHRONIZED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getSynchronized() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SYNCHRONIZED_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
