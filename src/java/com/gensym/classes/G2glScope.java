/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glScope.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:53:47 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2glScope extends com.gensym.classes.G2glActivityWithBody {

  public static final Symbol G2GL_SCOPE_ = com.gensym.util.symbol.G2ClassSymbols.G2GL_SCOPE_;
  static final Symbol g2ClassName = G2GL_SCOPE_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2GL_SCOPE_, G2GL_ACTIVITY_WITH_BODY_, G2GL_ACTIVITY_, G2GL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- VARIABLE-ACCESS-SERIALIZABLE
   * @return the value of the VARIABLE-ACCESS-SERIALIZABLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for VARIABLE-ACCESS-SERIALIZABLE is : 
   * BooleanTruthValue
   *
   */
  public boolean getVariableAccessSerializable() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- VARIABLE-ACCESS-SERIALIZABLE
   * @param variableAccessSerializable new value to conclude for VARIABLE-ACCESS-SERIALIZABLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setVariableAccessSerializable(boolean variableAccessSerializable) throws G2AccessException;

}
