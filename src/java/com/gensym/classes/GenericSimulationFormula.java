/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GenericSimulationFormula.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:56:19 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface GenericSimulationFormula extends com.gensym.classes.Statement {

  public static final Symbol GENERIC_SIMULATION_FORMULA_ = com.gensym.util.symbol.G2ClassSymbols.GENERIC_SIMULATION_FORMULA_;
  static final Symbol g2ClassName = GENERIC_SIMULATION_FORMULA_;
  static final Symbol[] classInheritancePath = new Symbol[] {GENERIC_SIMULATION_FORMULA_, STATEMENT_, ITEM_, STATEMENT_OR_PROCEDURE_STEP_, TEXT_BOX_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for AUTHORS is : 
   * (OR NoItem
      (Structure 
        TIMESTAMP
          (Structure 
            YEAR Integer
            MONTH Integer
            DATE Integer
            HOURS Integer
            MINUTES Integer)
        AUTHORS
          (Sequence Symbol 0)))
   *
   */
  public com.gensym.util.Structure getAuthors() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAuthors(com.gensym.util.Structure authors) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CHANGE-LOG is : 
   * (OR (Sequence)
      NoItem)
   *
   */
  public com.gensym.util.Sequence getChangeLog() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TRACING-AND-BREAKPOINTS
   * @return the value of the TRACING-AND-BREAKPOINTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TRACING-AND-BREAKPOINTS is : 
   * (OR (MEMBER DEFAULT)
      (Structure 
        WARNING-MESSAGE-LEVEL
          (MEMBER 0 1 2 3)
        TRACING-MESSAGE-LEVEL
          (MEMBER 0 1 2 3)
        BREAKPOINT-LEVEL
          (MEMBER 0 1 2 3)
        SOURCE-STEPPING-LEVEL
          (MEMBER 0 1)))
   *
   */
  public java.lang.Object getTracingAndBreakpoints() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TRACING-AND-BREAKPOINTS
   * @param tracingAndBreakpoints new value to conclude for TRACING-AND-BREAKPOINTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTracingAndBreakpoints(java.lang.Object tracingAndBreakpoints) throws G2AccessException;

}
