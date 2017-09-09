/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Root.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:25:43 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Root extends com.gensym.classes.G2__Base {

  public static final Symbol ROOT_ = com.gensym.util.symbol.G2ClassSymbols.ROOT_;
  static final Symbol g2ClassName = ROOT_;
  static final Symbol[] classInheritancePath = new Symbol[] {ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /* Overriden Property - G2CLASS-NAME */
  /**  Property Getter for G2CLASS-NAME */
  public com.gensym.util.Symbol getG2ClassName() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FOUNDATION-CLASS
   * @return the value of the FOUNDATION-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FOUNDATION-CLASS is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getFoundationClass() throws G2AccessException;

}
