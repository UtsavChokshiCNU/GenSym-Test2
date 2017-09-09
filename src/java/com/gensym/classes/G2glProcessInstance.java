/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glProcessInstance.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JJ11)
 *
 *          Date: Thu Oct 11 15:46:17 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2glProcessInstance extends com.gensym.classes.G2glObject {

  public static final Symbol G2GL_PROCESS_INSTANCE_ = com.gensym.util.symbol.G2ClassSymbols.G2GL_PROCESS_INSTANCE_;
  static final Symbol g2ClassName = G2GL_PROCESS_INSTANCE_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2GL_PROCESS_INSTANCE_, G2GL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- G2GL-PROCESS-INSTANCE-IS-PAUSED
   * @return the value of the G2GL-PROCESS-INSTANCE-IS-PAUSED attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2GL-PROCESS-INSTANCE-IS-PAUSED is : 
   * BooleanTruthValue
   *
   */
  public boolean getG2glProcessInstanceIsPaused() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- G2GL-PROCESS-INSTANCE-IS-PAUSED
   * @param g2glProcessInstanceIsPaused new value to conclude for G2GL-PROCESS-INSTANCE-IS-PAUSED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setG2glProcessInstanceIsPaused(boolean g2glProcessInstanceIsPaused) throws G2AccessException;

}
