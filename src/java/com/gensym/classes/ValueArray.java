/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ValueArray.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:08 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.util.Sequence;
import com.gensym.util.symbol.SystemAttributeSymbols;

public interface ValueArray extends com.gensym.classes.G2Array {

  public static final Symbol VALUE_ARRAY_ = com.gensym.util.symbol.G2ClassSymbols.VALUE_ARRAY_;
  static final Symbol g2ClassName = VALUE_ARRAY_;
  static final Symbol[] classInheritancePath = new Symbol[] {VALUE_ARRAY_, G2_ARRAY_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /* Overriden Property - G2ARRAY-CONTENTS */
  /**
   * Gets the contents of the G2 Array.
   * @return the current array contents (as an java.lang.Object[])
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2ArrayContents() 
       throws com.gensym.jgi.G2AccessException;
  /**
   * Sets the contents of the G2 Array from the contents of a Java array.
   * @param arrayContents must be a java.lang.Object[]
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public void setG2ArrayContents(java.lang.Object arrayContentsObj) 
       throws com.gensym.jgi.G2AccessException;

}
