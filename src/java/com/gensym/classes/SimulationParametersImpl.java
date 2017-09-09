/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      SimulationParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:08:14 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class SimulationParametersImpl extends com.gensym.classes.SystemTableImpl implements SimulationParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public SimulationParametersImpl() {
    super();
  }

  public SimulationParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public SimulationParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- DEFAULT-SIMULATION-TIME-INCREMENT
   * @param defaultSimulationTimeIncrement new value to conclude for DEFAULT-SIMULATION-TIME-INCREMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDefaultSimulationTimeIncrement(java.lang.Number defaultSimulationTimeIncrement) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DEFAULT_SIMULATION_TIME_INCREMENT_, defaultSimulationTimeIncrement);
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-SIMULATION-TIME-INCREMENT
   * @return the value of the DEFAULT-SIMULATION-TIME-INCREMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Number getDefaultSimulationTimeIncrement() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DEFAULT_SIMULATION_TIME_INCREMENT_);
    return (java.lang.Number)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- INTEGRATION-ALGORITHM
   * @param integrationAlgorithm new value to conclude for INTEGRATION-ALGORITHM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setIntegrationAlgorithm(com.gensym.util.Symbol integrationAlgorithm) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.INTEGRATION_ALGORITHM_, integrationAlgorithm);
  }

  /**
   * Generated Property Getter for attribute -- INTEGRATION-ALGORITHM
   * @return the value of the INTEGRATION-ALGORITHM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getIntegrationAlgorithm() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INTEGRATION_ALGORITHM_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SIMULATOR-ON
   * @param simulatorOn new value to conclude for SIMULATOR-ON
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSimulatorOn(boolean simulatorOn) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SIMULATOR_ON_, new Boolean (simulatorOn));
  }

  /**
   * Generated Property Getter for attribute -- SIMULATOR-ON
   * @return the value of the SIMULATOR-ON attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getSimulatorOn() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SIMULATOR_ON_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- SIMULATION-PROCEDURE
   * @param simulationProcedure new value to conclude for SIMULATION-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSimulationProcedure(com.gensym.util.Symbol simulationProcedure) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SIMULATION_PROCEDURE_, simulationProcedure);
  }

  /**
   * Generated Property Getter for attribute -- SIMULATION-PROCEDURE
   * @return the value of the SIMULATION-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getSimulationProcedure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SIMULATION_PROCEDURE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE?
   * @param sendAllValuesAtBeginningOfCycle new value to conclude for SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSendAllValuesAtBeginningOfCycle(boolean sendAllValuesAtBeginningOfCycle) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SEND_ALL_VALUES_AT_BEGINNING_OF_CYCLEQ_, new Boolean (sendAllValuesAtBeginningOfCycle));
  }

  /**
   * Generated Property Getter for attribute -- SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE?
   * @return the value of the SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getSendAllValuesAtBeginningOfCycle() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SEND_ALL_VALUES_AT_BEGINNING_OF_CYCLEQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
