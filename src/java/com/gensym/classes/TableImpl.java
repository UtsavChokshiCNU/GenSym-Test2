/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      TableImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:10:36 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class TableImpl extends com.gensym.classes.BlockImpl implements Table {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public TableImpl() {
    super();
  }

  public TableImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public TableImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Getter for attribute -- TABLE-ROWS
   * @return the value of the TABLE-ROWS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getTableRows() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TABLE_ROWS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- FORMAT-TYPE
   * @return the value of the FORMAT-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFormatType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FORMAT_TYPE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
