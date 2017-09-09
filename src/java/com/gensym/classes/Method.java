/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Method.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:44 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Method extends com.gensym.classes.Procedure {

  public static final Symbol METHOD_ = com.gensym.util.symbol.G2ClassSymbols.METHOD_;
  static final Symbol g2ClassName = METHOD_;
  static final Symbol[] classInheritancePath = new Symbol[] {METHOD_, PROCEDURE_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- SYNCHRONIZED
   * @return the value of the SYNCHRONIZED attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SYNCHRONIZED is : 
   * BooleanTruthValue
   *
   */
  public boolean getSynchronized() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SYNCHRONIZED
   * @param synchronized$ new value to conclude for SYNCHRONIZED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSynchronized(boolean synchronized$) throws G2AccessException;

}
