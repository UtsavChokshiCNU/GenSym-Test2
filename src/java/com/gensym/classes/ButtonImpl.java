/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ButtonImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:13:37 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class ButtonImpl extends com.gensym.classes.EntityImpl implements Button {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public ButtonImpl() {
    super();
  }

  public ButtonImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public ButtonImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- LABEL
   * @param label new value to conclude for LABEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setLabel(java.lang.String label) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.LABEL_, label);
  }

  /**
   * Generated Property Getter for attribute -- LABEL
   * @return the value of the LABEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getLabel() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.LABEL_);
    return (java.lang.String)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
