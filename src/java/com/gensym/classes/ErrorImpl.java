/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ErrorImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:44:43 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class ErrorImpl extends com.gensym.classes.ObjectImpl implements Error {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public ErrorImpl() {
    super();
  }

  public ErrorImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public ErrorImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- ERROR-DESCRIPTION
   * @param errorDescription new value to conclude for ERROR-DESCRIPTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setErrorDescription(java.lang.String errorDescription) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ERROR_DESCRIPTION_, errorDescription);
  }

  /**
   * Generated Property Getter for attribute -- ERROR-DESCRIPTION
   * @return the value of the ERROR-DESCRIPTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getErrorDescription() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ERROR_DESCRIPTION_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ERROR-SOURCE-ITEM
   * @return the value of the ERROR-SOURCE-ITEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getErrorSourceItem() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ERROR_SOURCE_ITEM_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ERROR-SOURCE-LINE
   * @return the value of the ERROR-SOURCE-LINE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getErrorSourceLine() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ERROR_SOURCE_LINE_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- ERROR-SOURCE-COLUMN
   * @return the value of the ERROR-SOURCE-COLUMN attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getErrorSourceColumn() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ERROR_SOURCE_COLUMN_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- ERROR-SOURCE-TRACE
   * @return the value of the ERROR-SOURCE-TRACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getErrorSourceTrace() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ERROR_SOURCE_TRACE_);
    return (com.gensym.util.Sequence)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
