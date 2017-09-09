/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlTaskOrEventImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 27 07:59:12 EDT 2000
 *
 */


package com.gensym.classes.modules.gdl;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class GdlTaskOrEventImpl extends com.gensym.classes.modules.gdl.GdlObjectImpl implements GdlTaskOrEvent {


  static final long serialVersionUID = 2L;
  private static final Symbol EVALUATOR_ = Symbol.intern ("EVALUATOR");

  /* Generated constructors */

  public GdlTaskOrEventImpl() {
    super();
  }

  public GdlTaskOrEventImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- EVALUATOR
   * @param evaluator new value to conclude for EVALUATOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEvaluator(com.gensym.util.Symbol evaluator) throws G2AccessException {
    setAttributeValue (EVALUATOR_, evaluator);
  }

  /**
   * Generated Property Getter for attribute -- EVALUATOR
   * @return the value of the EVALUATOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getEvaluator() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (EVALUATOR_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
