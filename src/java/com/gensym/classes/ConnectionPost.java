/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ConnectionPost.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:37:32 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface ConnectionPost extends com.gensym.classes.Object {

  public static final Symbol CONNECTION_POST_ = com.gensym.util.symbol.G2ClassSymbols.CONNECTION_POST_;
  static final Symbol g2ClassName = CONNECTION_POST_;
  static final Symbol[] classInheritancePath = new Symbol[] {CONNECTION_POST_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- SUPERIOR-CONNECTION
   * @return the value of the SUPERIOR-CONNECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SUPERIOR-CONNECTION is : 
   * (OR NoItem
      Symbol
      (Structure 
        EDGE
          (MEMBER TOP BOTTOM RIGHT LEFT)
        POSITION Integer))
   *
   */
  public java.lang.Object getSuperiorConnection() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SUPERIOR-CONNECTION
   * @param superiorConnection new value to conclude for SUPERIOR-CONNECTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSuperiorConnection(java.lang.Object superiorConnection) throws G2AccessException;

}
