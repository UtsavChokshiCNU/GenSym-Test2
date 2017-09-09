/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      SavingParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:07:48 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface SavingParameters extends com.gensym.classes.SystemTable {

  public static final Symbol SAVING_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.SAVING_PARAMETERS_;
  static final Symbol g2ClassName = SAVING_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {SAVING_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- DEFAULT-PRIORITY-FOR-RUNTIME-SAVING
   * @return the value of the DEFAULT-PRIORITY-FOR-RUNTIME-SAVING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DEFAULT-PRIORITY-FOR-RUNTIME-SAVING is : 
   * (MEMBER 1 2 3 4 5 6 7 8 9 10)
   *
   */
  public com.gensym.util.Symbol getDefaultPriorityForRuntimeSaving() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DEFAULT-PRIORITY-FOR-RUNTIME-SAVING
   * @param defaultPriorityForRuntimeSaving new value to conclude for DEFAULT-PRIORITY-FOR-RUNTIME-SAVING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDefaultPriorityForRuntimeSaving(com.gensym.util.Symbol defaultPriorityForRuntimeSaving) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- IDENTIFIER-OF-BASIS-KB
   * @return the value of the IDENTIFIER-OF-BASIS-KB attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for IDENTIFIER-OF-BASIS-KB is : 
   * (OR NoItem
      Text)
   *
   */
  public java.lang.String getIdentifierOfBasisKb() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- KB-FILE-COMMENT
   * @return the value of the KB-FILE-COMMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for KB-FILE-COMMENT is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getKbFileComment() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- KB-FILE-COMMENT
   * @param kbFileComment new value to conclude for KB-FILE-COMMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setKbFileComment(java.lang.String kbFileComment) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ENABLE-KB-CHANGE-LOGGING
   * @return the value of the ENABLE-KB-CHANGE-LOGGING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ENABLE-KB-CHANGE-LOGGING is : 
   * BooleanTruthValue
   *
   */
  public boolean getEnableKbChangeLogging() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ENABLE-KB-CHANGE-LOGGING
   * @param enableKbChangeLogging new value to conclude for ENABLE-KB-CHANGE-LOGGING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEnableKbChangeLogging(boolean enableKbChangeLogging) throws G2AccessException;

}
