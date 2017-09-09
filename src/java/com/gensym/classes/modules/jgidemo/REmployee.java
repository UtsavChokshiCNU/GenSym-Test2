/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      REmployee.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Sep 21 13:49:31 EDT 2007
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

public interface REmployee extends com.gensym.classes.modules.jgidemo.RepositoryObject {

  public static final Symbol R_EMPLOYEE_ = Symbol.intern ("R-EMPLOYEE");
  static final Symbol g2ClassName = R_EMPLOYEE_;
  static final Symbol[] classInheritancePath = new Symbol[] {R_EMPLOYEE_, REPOSITORY_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- SOCIAL-SECURITY-NUMBER
   * @return the value of the SOCIAL-SECURITY-NUMBER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SOCIAL-SECURITY-NUMBER is : 
   * (Class RA-SYMBOLIC-PARAMETER)
   *
   */
  public com.gensym.classes.modules.jgidemo.RaSymbolicParameter getSocialSecurityNumber() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SOCIAL-SECURITY-NUMBER
   * @param socialSecurityNumber new value to conclude for SOCIAL-SECURITY-NUMBER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSocialSecurityNumber(com.gensym.classes.modules.jgidemo.RaSymbolicParameter socialSecurityNumber) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TITLE
   * @return the value of the TITLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TITLE is : 
   * (Class RA-SYMBOLIC-PARAMETER)
   *
   */
  public com.gensym.classes.modules.jgidemo.RaSymbolicParameter getTitle() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TITLE
   * @param title new value to conclude for TITLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTitle(com.gensym.classes.modules.jgidemo.RaSymbolicParameter title) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SUPERVISOR
   * @return the value of the SUPERVISOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SUPERVISOR is : 
   * (Class RA-SYMBOLIC-PARAMETER)
   *
   */
  public com.gensym.classes.modules.jgidemo.RaSymbolicParameter getSupervisor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SUPERVISOR
   * @param supervisor new value to conclude for SUPERVISOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSupervisor(com.gensym.classes.modules.jgidemo.RaSymbolicParameter supervisor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PAY-SCALE
   * @return the value of the PAY-SCALE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PAY-SCALE is : 
   * (Class RA-INTEGER-PARAMETER)
   *
   */
  public com.gensym.classes.modules.jgidemo.RaIntegerParameter getPayScale() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PAY-SCALE
   * @param payScale new value to conclude for PAY-SCALE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPayScale(com.gensym.classes.modules.jgidemo.RaIntegerParameter payScale) throws G2AccessException;

}
