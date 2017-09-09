/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      TableItem.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:10:39 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface TableItem extends com.gensym.classes.ExportedSystemItem, com.gensym.classes.Table {

  public static final Symbol TABLE_ITEM_ = com.gensym.util.symbol.G2ClassSymbols.TABLE_ITEM_;
  static final Symbol g2ClassName = TABLE_ITEM_;
  static final Symbol[] classInheritancePath = new Symbol[] {TABLE_ITEM_, EXPORTED_SYSTEM_ITEM_, ITEM_, TABLE_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- TABLE-LAYOUT
   * @return the value of the TABLE-LAYOUT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TABLE-LAYOUT is : 
   * (OR (Structure)
      NoItem)
   *
   */
  public com.gensym.util.Structure getTableLayout() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TABLE-FONT-SIZE
   * @return the value of the TABLE-FONT-SIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TABLE-FONT-SIZE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getTableFontSize() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- REPRESENTED-ITEM
   * @return the value of the REPRESENTED-ITEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for REPRESENTED-ITEM is : 
   * (OR Value
      NoItem)
   *
   */
  public java.lang.Object getRepresentedItem() throws G2AccessException;

}
