/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glFlowGate.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:50:57 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2glFlowGate extends com.gensym.classes.G2glActivity {

  public static final Symbol G2GL_FLOW_GATE_ = com.gensym.util.symbol.G2ClassSymbols.G2GL_FLOW_GATE_;
  static final Symbol g2ClassName = G2GL_FLOW_GATE_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2GL_FLOW_GATE_, G2GL_ACTIVITY_, G2GL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- SUPPRESS-JOIN-FAILURE
   * @return the value of the SUPPRESS-JOIN-FAILURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SUPPRESS-JOIN-FAILURE is : 
   * BooleanTruthValue
   *
   */
  public boolean getSuppressJoinFailure() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SUPPRESS-JOIN-FAILURE
   * @param suppressJoinFailure new value to conclude for SUPPRESS-JOIN-FAILURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSuppressJoinFailure(boolean suppressJoinFailure) throws G2AccessException;

}
