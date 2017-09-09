/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      VersionControlParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JJ11)
 *
 *          Date: Thu Oct 11 15:46:04 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface VersionControlParameters extends com.gensym.classes.SystemTable {

  public static final Symbol VERSION_CONTROL_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.VERSION_CONTROL_PARAMETERS_;
  static final Symbol g2ClassName = VERSION_CONTROL_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {VERSION_CONTROL_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


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
