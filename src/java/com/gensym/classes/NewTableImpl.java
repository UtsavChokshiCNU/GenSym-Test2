/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      NewTableImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:04:16 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class NewTableImpl extends com.gensym.classes.BlockImpl implements NewTable {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public NewTableImpl() {
    super();
  }

  public NewTableImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public NewTableImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- DEFAULT-CELL-FORMAT
   * @param defaultCellFormat new value to conclude for DEFAULT-CELL-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDefaultCellFormat(com.gensym.util.Structure defaultCellFormat) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DEFAULT_CELL_FORMAT_, defaultCellFormat);
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-CELL-FORMAT
   * @return the value of the DEFAULT-CELL-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getDefaultCellFormat() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DEFAULT_CELL_FORMAT_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DEFAULT-EVALUATION-SETTING
   * @param defaultEvaluationSetting new value to conclude for DEFAULT-EVALUATION-SETTING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDefaultEvaluationSetting(com.gensym.util.Structure defaultEvaluationSetting) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DEFAULT_EVALUATION_SETTING_, defaultEvaluationSetting);
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-EVALUATION-SETTING
   * @return the value of the DEFAULT-EVALUATION-SETTING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getDefaultEvaluationSetting() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DEFAULT_EVALUATION_SETTING_);
    return (com.gensym.util.Structure)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
