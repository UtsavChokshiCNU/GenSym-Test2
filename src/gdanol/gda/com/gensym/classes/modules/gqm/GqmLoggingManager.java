/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GqmLoggingManager.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 13 11:45:42 EDT 2000
 *
 */


package com.gensym.classes.modules.gqm;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GqmLoggingManager extends com.gensym.classes.modules.glf.GlfLoggingManager {

  public static final Symbol GQM_LOGGING_MANAGER_ = Symbol.intern ("GQM-LOGGING-MANAGER");
  static final Symbol g2ClassName = GQM_LOGGING_MANAGER_;
  static final Symbol[] classInheritancePath = new Symbol[] {GQM_LOGGING_MANAGER_, GLF_LOGGING_MANAGER_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- GQM-TIME-FORMAT
   * @return the value of the GQM-TIME-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GQM-TIME-FORMAT is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getGqmTimeFormat() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GQM-TIME-FORMAT
   * @param gqmTimeFormat new value to conclude for GQM-TIME-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmTimeFormat(com.gensym.util.Symbol gqmTimeFormat) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GQM-LOG-COMMENTS
   * @return the value of the GQM-LOG-COMMENTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GQM-LOG-COMMENTS is : 
   * BooleanTruthValue
   *
   */
  public boolean getGqmLogComments() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GQM-LOG-COMMENTS
   * @param gqmLogComments new value to conclude for GQM-LOG-COMMENTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmLogComments(boolean gqmLogComments) throws G2AccessException;

}
