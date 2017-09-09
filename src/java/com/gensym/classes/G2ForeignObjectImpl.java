/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2ForeignObjectImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:44:47 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2ForeignObjectImpl extends com.gensym.classes.ObjectImpl implements G2ForeignObject {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2ForeignObjectImpl() {
    super();
  }

  public G2ForeignObjectImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2ForeignObjectImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- ACTIVE-STUBS
   * @param activeStubs new value to conclude for ACTIVE-STUBS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setActiveStubs(com.gensym.util.Sequence activeStubs) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ACTIVE_STUBS_, activeStubs);
  }

  /**
   * Generated Property Getter for attribute -- ACTIVE-STUBS
   * @return the value of the ACTIVE-STUBS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getActiveStubs() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ACTIVE_STUBS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
