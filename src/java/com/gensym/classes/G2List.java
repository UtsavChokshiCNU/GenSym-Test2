/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2List.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:12 EDT 2007
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

public interface G2List extends com.gensym.classes.Object {

  public static final Symbol G2_LIST_ = com.gensym.util.symbol.G2ClassSymbols.G2_LIST_;
  static final Symbol g2ClassName = G2_LIST_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2_LIST_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /* Overriden Property - G2LIST-SEQUENCE */
  /**
   * Generated Property Getter for attribute -- G2-LIST-SEQUENCE
   * @return the value of the G2-LIST-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getG2ListSequence() throws G2AccessException;
  /**
   * Generated Property Setter for attribute -- G2-LIST-SEQUENCE
   * @param g2ListSequence new value to conclude for G2-LIST-SEQUENCE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setG2ListSequence(com.gensym.util.Sequence g2ListSequence) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ELEMENT-TYPE
   * @return the value of the ELEMENT-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ELEMENT-TYPE is : 
   * (MEMBER VALUE ITEM-OR-VALUE QUANTITY TEXT TRUTH-VALUE ITEM INTEGER FLOAT SYMBOL)
   *
   */
  public com.gensym.util.Symbol getElementType() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ALLOW-DUPLICATE-ELEMENTS
   * @return the value of the ALLOW-DUPLICATE-ELEMENTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ALLOW-DUPLICATE-ELEMENTS is : 
   * BooleanTruthValue
   *
   */
  public boolean getAllowDuplicateElements() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ALLOW-DUPLICATE-ELEMENTS
   * @param allowDuplicateElements new value to conclude for ALLOW-DUPLICATE-ELEMENTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAllowDuplicateElements(boolean allowDuplicateElements) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- LIST-IS-PERMANENT
   * @return the value of the LIST-IS-PERMANENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LIST-IS-PERMANENT is : 
   * BooleanTruthValue
   *
   */
  public boolean getListIsPermanent() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LIST-IS-PERMANENT
   * @param listIsPermanent new value to conclude for LIST-IS-PERMANENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setListIsPermanent(boolean listIsPermanent) throws G2AccessException;

}
