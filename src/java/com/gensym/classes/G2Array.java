/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2Array.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:06 EDT 2007
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

public interface G2Array extends com.gensym.classes.Object {

  public static final Symbol G2_ARRAY_ = com.gensym.util.symbol.G2ClassSymbols.G2_ARRAY_;
  static final Symbol g2ClassName = G2_ARRAY_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2_ARRAY_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /* Overriden Property - ARRAY-LENGTH */
  /**
   * Property Getter for attribute -- ARRAY-LENGTH
   * @return the value of the ARRAY-LENGTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getArrayLength() throws com.gensym.jgi.G2AccessException;

  /* Overriden Property - G2ARRAY-CONTENTS */
  /**
   * Gets the contents of the G2 Array.
   * @return the current array contents (as an java.lang.Object[])
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getG2ArrayContents() 
       throws com.gensym.jgi.G2AccessException;
  /**
   * Sets the contents of the G2 Array from the contents of a Java array.
   * @param arrayContents must be a java.lang.Object[]
   * @exception G2AccessException if there are any communication problems
   */
  public void setG2ArrayContents(java.lang.Object arrayContentsObj) 
       throws com.gensym.jgi.G2AccessException;

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
   * Generated Property Getter for attribute -- INITIAL-VALUES
   * @return the value of the INITIAL-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INITIAL-VALUES is : 
   * (OR NoItem
      (Sequence ItemOrValue 1)
      (Structure 
        VALUES
          (Sequence 
            (OR ItemOrValue
                NoItem)
            1))
        ITEMS
          (Sequence 
            (OR Value
                NoItem)
            1))))
   *
   */
  public java.lang.Object getInitialValues() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INITIAL-VALUES
   * @param initialValues new value to conclude for INITIAL-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInitialValues(java.lang.Object initialValues) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ARRAY-IS-PERMANENT
   * @return the value of the ARRAY-IS-PERMANENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ARRAY-IS-PERMANENT is : 
   * BooleanTruthValue
   *
   */
  public boolean getArrayIsPermanent() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ARRAY-IS-PERMANENT
   * @param arrayIsPermanent new value to conclude for ARRAY-IS-PERMANENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setArrayIsPermanent(boolean arrayIsPermanent) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-ARRAY-SEQUENCE
   * @return the value of the G2-ARRAY-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-ARRAY-SEQUENCE is : 
   * (OR NoItem
      (Sequence))
   *
   */
  public com.gensym.util.Sequence getG2ArraySequence() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- G2-ARRAY-SEQUENCE
   * @param g2ArraySequence new value to conclude for G2-ARRAY-SEQUENCE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setG2ArraySequence(com.gensym.util.Sequence g2ArraySequence) throws G2AccessException;

}
