/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ValueList.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:13 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.G2AccessException;

public interface ValueList extends com.gensym.classes.G2List {

  public static final Symbol VALUE_LIST_ = com.gensym.util.symbol.G2ClassSymbols.VALUE_LIST_;
  static final Symbol g2ClassName = VALUE_LIST_;
  static final Symbol[] classInheritancePath = new Symbol[] {VALUE_LIST_, G2_LIST_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /* Overriden Property - G2LIST-SEQUENCE */
  /**
   * Generated Property Getter for attribute -- G2-LIST-SEQUENCE
   * @return the value of the G2-LIST-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getG2ListSequence() 
       throws G2AccessException;
  /**
   * Generated Property Setter for attribute -- G2-LIST-SEQUENCE
   * @param g2ListSequence new value to conclude for G2-LIST-SEQUENCE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setG2ListSequence(com.gensym.util.Sequence g2ListSequence) 
       throws G2AccessException;

}
