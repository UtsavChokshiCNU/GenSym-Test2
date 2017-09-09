/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glFault.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JJ11)
 *
 *          Date: Thu Oct 11 15:46:24 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2glFault extends com.gensym.classes.G2Error {

  public static final Symbol G2GL_FAULT_ = com.gensym.util.symbol.G2ClassSymbols.G2GL_FAULT_;
  static final Symbol g2ClassName = G2GL_FAULT_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2GL_FAULT_, G2_ERROR_, ERROR_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- FAULT-NAME
   * @return the value of the FAULT-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FAULT-NAME is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getFaultName() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FAULT-DATA
   * @return the value of the FAULT-DATA attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FAULT-DATA is : 
   * ItemOrValue
   *
   */
  public java.lang.Object getFaultData() throws G2AccessException;

}
