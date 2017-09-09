/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GsiDataService.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:57:02 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.util.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2Gateway;

public interface GsiDataService extends com.gensym.classes.Variable {

  public static final Symbol GSI_DATA_SERVICE_ = com.gensym.util.symbol.G2ClassSymbols.GSI_DATA_SERVICE_;
  static final Symbol g2ClassName = GSI_DATA_SERVICE_;
  static final Symbol[] classInheritancePath = new Symbol[] {GSI_DATA_SERVICE_, VARIABLE_, VARIABLE_OR_PARAMETER_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /* Overriden Property - STORED-GSI-VARIABLE-STATUS */
  /**
   * Get the stored GSI-VARIABLE-STATUS of this GSI variable. This GSI status of this Data item is not updated
   * in G2 until the variables value is updated using VaraiableOrParameter.setValue
   */
  public int getStoredGsiVariableStatus();

  /* Overriden Property - GSI-VARIABLE-VALUE */
  /**
   * Set the value of the corresponding Gsi Variable in G2, updating its GSI-VARIABLE-STATUS, as set by
   * storeGsiVariableStatus().
   */
  public void setGsiVariableValue(java.lang.Object value, int status) throws G2AccessException;

  /* Overriden Property - STORED-GSI-VARIABLE-VALUE */
  /**
   * Get the stored value to be sent back to this GSI variable during a batch update operation.
   * (For example using com.gensym.jgi.dataservice.DataService.setGsiVariables())
   * @param The Value to store for this GSI-VARIABLE
   */
  public java.lang.Object getStoredGsiVariableValue();

  /* Overriden Property - VALUE-FROM-SET-ACTION */
  /**
   * Return the value of this GSI-VARIABLE as set by a SET G2 action.
   */
  public java.lang.Object getValueFromSetAction();

  /**
   * Generated Property Getter for attribute -- GSI-INTERFACE-NAME
   * @return the value of the GSI-INTERFACE-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GSI-INTERFACE-NAME is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getGsiInterfaceName() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GSI-INTERFACE-NAME
   * @param gsiInterfaceName new value to conclude for GSI-INTERFACE-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGsiInterfaceName(com.gensym.util.Symbol gsiInterfaceName) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GSI-VARIABLE-STATUS
   * @return the value of the GSI-VARIABLE-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GSI-VARIABLE-STATUS is : 
   * Integer
   *
   */
  public int getGsiVariableStatus() throws G2AccessException;

  /* Overriden method - STORE-GSI-VARIABLE-VALUE */
  /**
   * Store a value to be sent back to this GSI variable during a batch update operation.
   * (For example using com.gensym.jgi.dataservice.DataService.setGsiVariables())
   * @param The Value to store for this GSI-VARIABLE
   */
  public void storeGsiVariableValue(java.lang.Object value);

  /* Overriden method - RETURN-GSI-VARIABLE-VALUE */
  /**
   * Set the value of the corresponding Gsi Variable in G2 as set by storeGSIVariableValue and
   * updating its GSI-VARIABLE-STATUS, as set by storeGsiVariableStatus().
   */
  public void returnGsiVariableValue() throws G2AccessException;

  /* Overriden method - STORE-GSI-VARIABLE-STATUS */
  /**
   * Store the GSI-VARIABLE-STATUS of this GSI variable. The GSI status of this Data item is not updated
   * in G2 until the variables value is updated.
   */
  public void storeGsiVariableStatus(int statusValue);

}
