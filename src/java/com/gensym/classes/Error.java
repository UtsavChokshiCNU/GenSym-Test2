/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Error.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:44:41 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Error extends com.gensym.classes.Object {

  public static final Symbol ERROR_ = com.gensym.util.symbol.G2ClassSymbols.ERROR_;
  static final Symbol g2ClassName = ERROR_;
  static final Symbol[] classInheritancePath = new Symbol[] {ERROR_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- ERROR-DESCRIPTION
   * @return the value of the ERROR-DESCRIPTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ERROR-DESCRIPTION is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getErrorDescription() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ERROR-DESCRIPTION
   * @param errorDescription new value to conclude for ERROR-DESCRIPTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setErrorDescription(java.lang.String errorDescription) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ERROR-SOURCE-ITEM
   * @return the value of the ERROR-SOURCE-ITEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ERROR-SOURCE-ITEM is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getErrorSourceItem() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ERROR-SOURCE-LINE
   * @return the value of the ERROR-SOURCE-LINE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ERROR-SOURCE-LINE is : 
   * Integer
   *
   */
  public int getErrorSourceLine() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ERROR-SOURCE-COLUMN
   * @return the value of the ERROR-SOURCE-COLUMN attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ERROR-SOURCE-COLUMN is : 
   * Integer
   *
   */
  public int getErrorSourceColumn() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ERROR-SOURCE-TRACE
   * @return the value of the ERROR-SOURCE-TRACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ERROR-SOURCE-TRACE is : 
   * (Sequence)
   *
   */
  public com.gensym.util.Sequence getErrorSourceTrace() throws G2AccessException;

}
