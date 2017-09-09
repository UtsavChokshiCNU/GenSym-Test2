/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      DefaultErrorImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:37:46 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class DefaultErrorImpl extends com.gensym.classes.ErrorImpl implements DefaultError {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public DefaultErrorImpl() {
    super();
  }

  public DefaultErrorImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public DefaultErrorImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
