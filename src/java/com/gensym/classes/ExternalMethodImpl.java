/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ExternalMethodImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:41:10 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class ExternalMethodImpl extends com.gensym.classes.ExternalProcedureImpl implements ExternalMethod {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public ExternalMethodImpl() {
    super();
  }

  public ExternalMethodImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public ExternalMethodImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
