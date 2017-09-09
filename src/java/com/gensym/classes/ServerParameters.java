/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ServerParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:08:10 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface ServerParameters extends com.gensym.classes.SystemTable {

  public static final Symbol SERVER_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.SERVER_PARAMETERS_;
  static final Symbol g2ClassName = SERVER_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {SERVER_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- G2-IS-SECURE
   * @return the value of the G2-IS-SECURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-IS-SECURE is : 
   * BooleanTruthValue
   *
   */
  public boolean getG2IsSecure() throws G2AccessException;

}
