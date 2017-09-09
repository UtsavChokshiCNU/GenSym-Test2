/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2DeadlockErrorImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JJ11)
 *
 *          Date: Thu Oct 11 15:46:31 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2DeadlockErrorImpl extends com.gensym.classes.G2ErrorImpl implements G2DeadlockError {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2DeadlockErrorImpl() {
    super();
  }

  public G2DeadlockErrorImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2DeadlockErrorImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
