/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      RootImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:25:54 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class RootImpl extends com.gensym.classes.G2__BaseImpl implements Root {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public RootImpl() {
    super();
  }

  public RootImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public RootImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /* Overriden Property - G2CLASS-NAME */
  /**  Property Getter for G2CLASS-NAME */
  @Override
  public com.gensym.util.Symbol getG2ClassName() throws G2AccessException {
    
        java.lang.Object retnValue = getDefinition().getClassName();
        return (com.gensym.util.Symbol)retnValue;
      
  }


  /**
   * Generated Property Getter for attribute -- FOUNDATION-CLASS
   * @return the value of the FOUNDATION-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFoundationClass() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FOUNDATION_CLASS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
