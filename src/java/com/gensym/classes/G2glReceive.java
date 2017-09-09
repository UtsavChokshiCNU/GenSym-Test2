/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glReceive.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:53:38 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2glReceive extends com.gensym.classes.G2glActivity {

  public static final Symbol G2GL_RECEIVE_ = com.gensym.util.symbol.G2ClassSymbols.G2GL_RECEIVE_;
  static final Symbol g2ClassName = G2GL_RECEIVE_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2GL_RECEIVE_, G2GL_ACTIVITY_, G2GL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- THIS-IS-AN-INSTANTIATION-TRIGGER
   * @return the value of the THIS-IS-AN-INSTANTIATION-TRIGGER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for THIS-IS-AN-INSTANTIATION-TRIGGER is : 
   * BooleanTruthValue
   *
   */
  public boolean getThisIsAnInstantiationTrigger() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- THIS-IS-AN-INSTANTIATION-TRIGGER
   * @param thisIsAnInstantiationTrigger new value to conclude for THIS-IS-AN-INSTANTIATION-TRIGGER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setThisIsAnInstantiationTrigger(boolean thisIsAnInstantiationTrigger) throws G2AccessException;

}
