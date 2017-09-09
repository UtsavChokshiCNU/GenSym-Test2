/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ModuleInformation.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:57 EDT 2007
 *
 */


package com.gensym.classes;

import java.io.Serializable;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface ModuleInformation extends com.gensym.classes.SystemTable, Serializable {

  public static final Symbol MODULE_INFORMATION_ = com.gensym.util.symbol.G2ClassSymbols.MODULE_INFORMATION_;
  static final Symbol g2ClassName = MODULE_INFORMATION_;
  static final Symbol[] classInheritancePath = new Symbol[] {MODULE_INFORMATION_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- MODULE-FILE-NAME
   * @return the value of the MODULE-FILE-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MODULE-FILE-NAME is : 
   * (OR NoItem
      Text
      Symbol)
   *
   */
  public java.lang.Object getModuleFileName() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MODULE-FILE-NAME
   * @param moduleFileName new value to conclude for MODULE-FILE-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setModuleFileName(java.lang.Object moduleFileName) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TOP-LEVEL-MODULE
   * @return the value of the TOP-LEVEL-MODULE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TOP-LEVEL-MODULE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getTopLevelModule() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TOP-LEVEL-MODULE
   * @param topLevelModule new value to conclude for TOP-LEVEL-MODULE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTopLevelModule(com.gensym.util.Symbol topLevelModule) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DIRECTLY-REQUIRED-MODULES
   * @return the value of the DIRECTLY-REQUIRED-MODULES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DIRECTLY-REQUIRED-MODULES is : 
   * (OR NoItem
      (Sequence Symbol 0))
   *
   */
  public com.gensym.util.Sequence getDirectlyRequiredModules() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DIRECTLY-REQUIRED-MODULES
   * @param directlyRequiredModules new value to conclude for DIRECTLY-REQUIRED-MODULES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDirectlyRequiredModules(com.gensym.util.Sequence directlyRequiredModules) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MODULE-ANNOTATIONS
   * @return the value of the MODULE-ANNOTATIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MODULE-ANNOTATIONS is : 
   * (Sequence 
    (Structure 
      ANNOTATION-NAME Symbol
      ANNOTATION-VALUE Value)
    0))
   *
   */
  public com.gensym.util.Sequence getModuleAnnotations() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MODULE-ANNOTATIONS
   * @param moduleAnnotations new value to conclude for MODULE-ANNOTATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setModuleAnnotations(com.gensym.util.Sequence moduleAnnotations) throws G2AccessException;

}
