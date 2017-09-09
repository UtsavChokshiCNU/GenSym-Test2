/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      MethodDeclaration.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:48 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface MethodDeclaration extends com.gensym.classes.Procedure {

  public static final Symbol METHOD_DECLARATION_ = com.gensym.util.symbol.G2ClassSymbols.METHOD_DECLARATION_;
  static final Symbol g2ClassName = METHOD_DECLARATION_;
  static final Symbol[] classInheritancePath = new Symbol[] {METHOD_DECLARATION_, PROCEDURE_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- REQUIRES-CALL-NEXT-METHOD?
   * @return the value of the REQUIRES-CALL-NEXT-METHOD? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for REQUIRES-CALL-NEXT-METHOD? is : 
   * BooleanTruthValue
   *
   */
  public boolean getRequiresCallNextMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- REQUIRES-CALL-NEXT-METHOD?
   * @param requiresCallNextMethod new value to conclude for REQUIRES-CALL-NEXT-METHOD?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRequiresCallNextMethod(boolean requiresCallNextMethod) throws G2AccessException;

}
