/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      MethodDeclarationImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:49 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class MethodDeclarationImpl extends com.gensym.classes.ProcedureImpl implements MethodDeclaration {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public MethodDeclarationImpl() {
    super();
  }

  public MethodDeclarationImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public MethodDeclarationImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- REQUIRES-CALL-NEXT-METHOD?
   * @param requiresCallNextMethod new value to conclude for REQUIRES-CALL-NEXT-METHOD?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRequiresCallNextMethod(boolean requiresCallNextMethod) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.REQUIRES_CALL_NEXT_METHODQ_, new Boolean (requiresCallNextMethod));
  }

  /**
   * Generated Property Getter for attribute -- REQUIRES-CALL-NEXT-METHOD?
   * @return the value of the REQUIRES-CALL-NEXT-METHOD? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getRequiresCallNextMethod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.REQUIRES_CALL_NEXT_METHODQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
