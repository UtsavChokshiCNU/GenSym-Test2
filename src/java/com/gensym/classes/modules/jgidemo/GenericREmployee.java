/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GenericREmployee.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Sep 21 13:49:35 EDT 2007
 *
 */


package com.gensym.classes.modules.jgidemo;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GenericREmployee extends com.gensym.classes.modules.jgidemo.REmployee, com.gensym.classes.modules.jgidemo.GenericRObject {

  public static final Symbol GENERIC_R_EMPLOYEE_ = Symbol.intern ("GENERIC-R-EMPLOYEE");
  static final Symbol g2ClassName = GENERIC_R_EMPLOYEE_;
  static final Symbol[] classInheritancePath = new Symbol[] {GENERIC_R_EMPLOYEE_, R_EMPLOYEE_, REPOSITORY_OBJECT_, GENERIC_R_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- A-SEQUENCE
   * @return the value of the A-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for A-SEQUENCE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getASequence() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- A-SEQUENCE
   * @param aSequence new value to conclude for A-SEQUENCE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setASequence(java.lang.Object aSequence) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- A-STRUCTURE
   * @return the value of the A-STRUCTURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for A-STRUCTURE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getAStructure() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- A-STRUCTURE
   * @param aStructure new value to conclude for A-STRUCTURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAStructure(java.lang.Object aStructure) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * GENERIC-R-EMPLOYEE::TEST-METHOD
   * @return the return from calling TEST-METHOD
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GENERIC-R-EMPLOYEE,arg1:VALUE) = (VALUE)
   */
  public  java.lang.Object testMethod(java.lang.Object arg1) throws G2AccessException;
  
}
