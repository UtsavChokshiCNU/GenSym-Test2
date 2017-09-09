/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2Extension.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:47:30 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2Extension extends com.gensym.classes.Object {

  public static final Symbol G2_EXTENSION_ = com.gensym.util.symbol.G2ClassSymbols.G2_EXTENSION_;
  static final Symbol g2ClassName = G2_EXTENSION_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2_EXTENSION_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- G2-USER-NAME
   * @return the value of the G2-USER-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-USER-NAME is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text)
   *
   */
  public java.lang.Object getG2UserName() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-CONNECTION-STATUS
   * @return the value of the G2-CONNECTION-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-CONNECTION-STATUS is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text)
   *
   */
  public java.lang.Object getG2ConnectionStatus() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-ROUTING-INFORMATION
   * @return the value of the G2-ROUTING-INFORMATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-ROUTING-INFORMATION is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text)
   *
   */
  public java.lang.Object getG2RoutingInformation() throws G2AccessException;

}
