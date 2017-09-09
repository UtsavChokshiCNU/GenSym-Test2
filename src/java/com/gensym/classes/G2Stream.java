/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2Stream.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:45:20 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2Stream extends com.gensym.classes.Item, com.gensym.classes.Entity {

  public static final Symbol G2_STREAM_ = com.gensym.util.symbol.G2ClassSymbols.G2_STREAM_;
  static final Symbol g2ClassName = G2_STREAM_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2_STREAM_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- NAME-OF-FILE
   * @return the value of the NAME-OF-FILE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NAME-OF-FILE is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text
      (Sequence)
      (Structure))
   *
   */
  public java.lang.Object getNameOfFile() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FILE-SYSTEM
   * @return the value of the FILE-SYSTEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FILE-SYSTEM is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text
      (Sequence)
      (Structure))
   *
   */
  public java.lang.Object getFileSystem() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ACCESS-DIRECTION
   * @return the value of the ACCESS-DIRECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ACCESS-DIRECTION is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text
      (Sequence)
      (Structure))
   *
   */
  public java.lang.Object getAccessDirection() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- POSITION-IN-FILE
   * @return the value of the POSITION-IN-FILE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for POSITION-IN-FILE is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text
      (Sequence)
      (Structure))
   *
   */
  public java.lang.Object getPositionInFile() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-STREAM-STATUS
   * @return the value of the G2-STREAM-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-STREAM-STATUS is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text
      (Sequence)
      (Structure))
   *
   */
  public java.lang.Object getG2StreamStatus() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TEXT-CONVERSION-STYLE
   * @return the value of the TEXT-CONVERSION-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TEXT-CONVERSION-STYLE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getTextConversionStyle() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TEXT-CONVERSION-STYLE
   * @param textConversionStyle new value to conclude for TEXT-CONVERSION-STYLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTextConversionStyle(com.gensym.util.Symbol textConversionStyle) throws G2AccessException;

}
