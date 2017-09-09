/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlTaskOrEvent.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Jun 26 18:45:35 EDT 2000
 *
 */


package com.gensym.classes.modules.gdl;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GdlTaskOrEvent extends com.gensym.classes.modules.gdl.GdlObject {

  public static final Symbol GDL_TASK_OR_EVENT_ = Symbol.intern ("GDL-TASK-OR-EVENT");
  static final Symbol g2ClassName = GDL_TASK_OR_EVENT_;
  static final Symbol[] classInheritancePath = new Symbol[] {GDL_TASK_OR_EVENT_, GDL_OBJECT_, GFR_OBJECT_WITH_UUID_, OBJECT_, GFR_ITEM_WITH_UUID_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- EVALUATOR
   * @return the value of the EVALUATOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for EVALUATOR is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getEvaluator() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- EVALUATOR
   * @param evaluator new value to conclude for EVALUATOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEvaluator(com.gensym.util.Symbol evaluator) throws G2AccessException;

}
