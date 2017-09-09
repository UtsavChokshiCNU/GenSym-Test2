/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      SymbolArray.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:08:28 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.util.Sequence;

public interface SymbolArray extends com.gensym.classes.ValueArray {

  public static final Symbol SYMBOL_ARRAY_ = com.gensym.util.symbol.G2ClassSymbols.SYMBOL_ARRAY_;
  static final Symbol g2ClassName = SYMBOL_ARRAY_;
  static final Symbol[] classInheritancePath = new Symbol[] {SYMBOL_ARRAY_, VALUE_ARRAY_, G2_ARRAY_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /* Overriden Property - G2ARRAY-CONTENTS */
  /**
   * Gets the contents of the G2 Array.
   * @return the current array contents (as a Symbol[])
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2ArrayContents() 
       throws com.gensym.jgi.G2AccessException;
  /**
   * Sets the contents of the G2 Array from the contents of a Java array.
   * @param arrayContents must be an Symbol[]
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public void setG2ArrayContents(java.lang.Object arrayContentsObj) 
       throws com.gensym.jgi.G2AccessException;

  /* Overriden Property - SYMBOL-ARRAY-CONTENTS */
  /**
   * Gets the contents of the Symbol-Array.
   * @return the current array contents as a Symbol[]
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol[] getSymbolArrayContents() 
       throws com.gensym.jgi.G2AccessException;

}
