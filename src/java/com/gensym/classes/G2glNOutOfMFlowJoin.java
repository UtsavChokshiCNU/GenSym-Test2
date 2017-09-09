/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glNOutOfMFlowJoin.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JJ11)
 *
 *          Date: Thu Oct 11 15:46:20 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2glNOutOfMFlowJoin extends com.gensym.classes.G2glFlowJoin {

  public static final Symbol G2GL_N_OUT_OF_M_FLOW_JOIN_ = com.gensym.util.symbol.G2ClassSymbols.G2GL_N_OUT_OF_M_FLOW_JOIN_;
  static final Symbol g2ClassName = G2GL_N_OUT_OF_M_FLOW_JOIN_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2GL_N_OUT_OF_M_FLOW_JOIN_, G2GL_FLOW_JOIN_, G2GL_ACTIVITY_, G2GL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- NUMBER-OF-BRANCHES-TO-SYNCHRONIZE
   * @return the value of the NUMBER-OF-BRANCHES-TO-SYNCHRONIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NUMBER-OF-BRANCHES-TO-SYNCHRONIZE is : 
   * Integer
   *
   */
  public int getNumberOfBranchesToSynchronize() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-BRANCHES-TO-SYNCHRONIZE
   * @param numberOfBranchesToSynchronize new value to conclude for NUMBER-OF-BRANCHES-TO-SYNCHRONIZE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNumberOfBranchesToSynchronize(int numberOfBranchesToSynchronize) throws G2AccessException;

}
