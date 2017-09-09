/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      VariableImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:24 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class VariableImpl extends com.gensym.classes.VariableOrParameterImpl implements Variable {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public VariableImpl() {
    super();
  }

  public VariableImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public VariableImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- OPTIONS
   * @param options new value to conclude for OPTIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setOptions(com.gensym.util.Structure options) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.OPTIONS_, options);
  }

  /**
   * Generated Property Getter for attribute -- OPTIONS
   * @return the value of the OPTIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getOptions() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.OPTIONS_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- VALIDITY-INTERVAL
   * @param validityInterval new value to conclude for VALIDITY-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setValidityInterval(java.lang.Object validityInterval) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.VALIDITY_INTERVAL_, validityInterval);
  }

  /**
   * Generated Property Getter for attribute -- VALIDITY-INTERVAL
   * @return the value of the VALIDITY-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getValidityInterval() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.VALIDITY_INTERVAL_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- FORMULA
   * @param formula new value to conclude for FORMULA
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFormula(java.lang.String formula) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FORMULA_, formula);
  }

  /**
   * Generated Property Getter for attribute -- FORMULA
   * @return the value of the FORMULA attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getFormula() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FORMULA_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- SIMULATION-DETAILS
   * @return the value of the SIMULATION-DETAILS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.SimulationSubtable getSimulationDetails() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SIMULATION_DETAILS_);
    return (com.gensym.classes.SimulationSubtable)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DATA-SERVER
   * @param dataServer new value to conclude for DATA-SERVER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDataServer(com.gensym.util.Symbol dataServer) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DATA_SERVER_, dataServer);
  }

  /**
   * Generated Property Getter for attribute -- DATA-SERVER
   * @return the value of the DATA-SERVER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getDataServer() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DATA_SERVER_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DEFAULT-UPDATE-INTERVAL
   * @param defaultUpdateInterval new value to conclude for DEFAULT-UPDATE-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDefaultUpdateInterval(java.lang.Number defaultUpdateInterval) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DEFAULT_UPDATE_INTERVAL_, defaultUpdateInterval);
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-UPDATE-INTERVAL
   * @return the value of the DEFAULT-UPDATE-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Number getDefaultUpdateInterval() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DEFAULT_UPDATE_INTERVAL_);
    return (java.lang.Number)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
