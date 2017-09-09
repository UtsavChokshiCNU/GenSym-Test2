/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ConnectionPostImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:37:35 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class ConnectionPostImpl extends com.gensym.classes.ObjectImpl implements ConnectionPost {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public ConnectionPostImpl() {
    super();
  }

  public ConnectionPostImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public ConnectionPostImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- SUPERIOR-CONNECTION
   * @param superiorConnection new value to conclude for SUPERIOR-CONNECTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSuperiorConnection(java.lang.Object superiorConnection) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SUPERIOR_CONNECTION_, superiorConnection);
  }

  /**
   * Generated Property Getter for attribute -- SUPERIOR-CONNECTION
   * @return the value of the SUPERIOR-CONNECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getSuperiorConnection() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SUPERIOR_CONNECTION_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
