/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ServerParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:08:11 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class ServerParametersImpl extends com.gensym.classes.SystemTableImpl implements ServerParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public ServerParametersImpl() {
    super();
  }

  public ServerParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public ServerParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Getter for attribute -- G2-IS-SECURE
   * @return the value of the G2-IS-SECURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getG2IsSecure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_IS_SECURE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
