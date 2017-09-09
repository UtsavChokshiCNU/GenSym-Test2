/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      StatementOrProcedureStepImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:13:59 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class StatementOrProcedureStepImpl extends com.gensym.classes.TextBoxImpl implements StatementOrProcedureStep {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public StatementOrProcedureStepImpl() {
    super();
  }

  public StatementOrProcedureStepImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public StatementOrProcedureStepImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
