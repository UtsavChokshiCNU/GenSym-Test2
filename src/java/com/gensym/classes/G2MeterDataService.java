/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2MeterDataService.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:45:09 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2MeterDataService extends com.gensym.classes.Variable {

  public static final Symbol G2_METER_DATA_SERVICE_ = com.gensym.util.symbol.G2ClassSymbols.G2_METER_DATA_SERVICE_;
  static final Symbol g2ClassName = G2_METER_DATA_SERVICE_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2_METER_DATA_SERVICE_, VARIABLE_, VARIABLE_OR_PARAMETER_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- G2-METER-NAME
   * @return the value of the G2-METER-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-METER-NAME is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getG2MeterName() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- G2-METER-NAME
   * @param g2MeterName new value to conclude for G2-METER-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setG2MeterName(com.gensym.util.Symbol g2MeterName) throws G2AccessException;

}
