/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glFlowGateImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:50:58 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2glFlowGateImpl extends com.gensym.classes.G2glActivityImpl implements G2glFlowGate {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2glFlowGateImpl() {
    super();
  }

  public G2glFlowGateImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2glFlowGateImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- SUPPRESS-JOIN-FAILURE
   * @param suppressJoinFailure new value to conclude for SUPPRESS-JOIN-FAILURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSuppressJoinFailure(boolean suppressJoinFailure) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SUPPRESS_JOIN_FAILURE_, new Boolean (suppressJoinFailure));
  }

  /**
   * Generated Property Getter for attribute -- SUPPRESS-JOIN-FAILURE
   * @return the value of the SUPPRESS-JOIN-FAILURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getSuppressJoinFailure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SUPPRESS_JOIN_FAILURE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
