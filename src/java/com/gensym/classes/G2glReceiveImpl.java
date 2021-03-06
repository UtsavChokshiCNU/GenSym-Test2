/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glReceiveImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:53:39 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2glReceiveImpl extends com.gensym.classes.G2glActivityImpl implements G2glReceive {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2glReceiveImpl() {
    super();
  }

  public G2glReceiveImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2glReceiveImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- THIS-IS-AN-INSTANTIATION-TRIGGER
   * @param thisIsAnInstantiationTrigger new value to conclude for THIS-IS-AN-INSTANTIATION-TRIGGER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setThisIsAnInstantiationTrigger(boolean thisIsAnInstantiationTrigger) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.THIS_IS_AN_INSTANTIATION_TRIGGER_, new Boolean (thisIsAnInstantiationTrigger));
  }

  /**
   * Generated Property Getter for attribute -- THIS-IS-AN-INSTANTIATION-TRIGGER
   * @return the value of the THIS-IS-AN-INSTANTIATION-TRIGGER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getThisIsAnInstantiationTrigger() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.THIS_IS_AN_INSTANTIATION_TRIGGER_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
