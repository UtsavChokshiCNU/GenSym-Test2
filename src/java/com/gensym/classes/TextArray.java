/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      TextArray.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:10:54 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.util.Sequence;

public interface TextArray extends com.gensym.classes.ValueArray {

  public static final Symbol TEXT_ARRAY_ = com.gensym.util.symbol.G2ClassSymbols.TEXT_ARRAY_;
  static final Symbol g2ClassName = TEXT_ARRAY_;
  static final Symbol[] classInheritancePath = new Symbol[] {TEXT_ARRAY_, VALUE_ARRAY_, G2_ARRAY_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /* Overriden Property - G2ARRAY-CONTENTS */
  /**
   * Gets the contents of the G2 Array.
   * @return the current array contents (as a java.lang.String[])
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2ArrayContents() 
       throws com.gensym.jgi.G2AccessException;
  /**
   * Sets the contents of the G2 Array from the contents of a Java array.
   * @param arrayContents must be an java.lang.String[]
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public void setG2ArrayContents(java.lang.Object arrayContentsObj) 
       throws com.gensym.jgi.G2AccessException;

  /* Overriden Property - TEXT-ARRAY-CONTENTS */
  /**
   * Gets the contents of the Text-Array.
   * @return the current array contents as a String[]
   * @exception G2AccessException if there are any communication problems
   */
  public String[] getTextArrayContents() 
       throws com.gensym.jgi.G2AccessException;

}
