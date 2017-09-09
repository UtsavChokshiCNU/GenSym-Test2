/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      NameBox.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:38 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface NameBox extends com.gensym.classes.ExportedSystemItem, com.gensym.classes.SubordinateTextBox {

  public static final Symbol NAME_BOX_ = com.gensym.util.symbol.G2ClassSymbols.NAME_BOX_;
  static final Symbol g2ClassName = NAME_BOX_;
  static final Symbol[] classInheritancePath = new Symbol[] {NAME_BOX_, EXPORTED_SYSTEM_ITEM_, ITEM_, SUBORDINATE_TEXT_BOX_, TEXT_BOX_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


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
