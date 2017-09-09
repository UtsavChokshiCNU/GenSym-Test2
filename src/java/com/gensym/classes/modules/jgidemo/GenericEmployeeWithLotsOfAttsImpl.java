/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GenericEmployeeWithLotsOfAttsImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Sep 21 13:50:21 EDT 2007
 *
 */


package com.gensym.classes.modules.jgidemo;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class GenericEmployeeWithLotsOfAttsImpl extends com.gensym.classes.modules.jgidemo.GenericREmployeeImpl implements GenericEmployeeWithLotsOfAtts {


  static final long serialVersionUID = 2L;
  private static final Symbol LOTS_OF_ATTS_ = Symbol.intern ("LOTS-OF-ATTS");

  /* Generated constructors */

  public GenericEmployeeWithLotsOfAttsImpl() {
    super();
  }

  public GenericEmployeeWithLotsOfAttsImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public GenericEmployeeWithLotsOfAttsImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- LOTS-OF-ATTS
   * @param lotsOfAtts new value to conclude for LOTS-OF-ATTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setLotsOfAtts(java.lang.Object lotsOfAtts) throws G2AccessException {
    setAttributeValue (LOTS_OF_ATTS_, lotsOfAtts);
  }

  /**
   * Generated Property Getter for attribute -- LOTS-OF-ATTS
   * @return the value of the LOTS-OF-ATTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getLotsOfAtts() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (LOTS_OF_ATTS_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
