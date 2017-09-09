/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Table.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:10:35 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Table extends com.gensym.classes.Block {

  public static final Symbol TABLE_ = com.gensym.util.symbol.G2ClassSymbols.TABLE_;
  static final Symbol g2ClassName = TABLE_;
  static final Symbol[] classInheritancePath = new Symbol[] {TABLE_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- TABLE-ROWS
   * @return the value of the TABLE-ROWS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TABLE-ROWS is : 
   * (OR (Sequence)
      NoItem)
   *
   */
  public com.gensym.util.Sequence getTableRows() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FORMAT-TYPE
   * @return the value of the FORMAT-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FORMAT-TYPE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getFormatType() throws G2AccessException;

}
