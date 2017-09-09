/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      SimulationParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:08:13 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface SimulationParameters extends com.gensym.classes.SystemTable {

  public static final Symbol SIMULATION_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.SIMULATION_PARAMETERS_;
  static final Symbol g2ClassName = SIMULATION_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {SIMULATION_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- DEFAULT-SIMULATION-TIME-INCREMENT
   * @return the value of the DEFAULT-SIMULATION-TIME-INCREMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DEFAULT-SIMULATION-TIME-INCREMENT is : 
   * Quantity
   *
   */
  public java.lang.Number getDefaultSimulationTimeIncrement() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DEFAULT-SIMULATION-TIME-INCREMENT
   * @param defaultSimulationTimeIncrement new value to conclude for DEFAULT-SIMULATION-TIME-INCREMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDefaultSimulationTimeIncrement(java.lang.Number defaultSimulationTimeIncrement) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INTEGRATION-ALGORITHM
   * @return the value of the INTEGRATION-ALGORITHM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INTEGRATION-ALGORITHM is : 
   * (MEMBER EULER RUNGA-KUTTA-4)
   *
   */
  public com.gensym.util.Symbol getIntegrationAlgorithm() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INTEGRATION-ALGORITHM
   * @param integrationAlgorithm new value to conclude for INTEGRATION-ALGORITHM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIntegrationAlgorithm(com.gensym.util.Symbol integrationAlgorithm) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SIMULATOR-ON
   * @return the value of the SIMULATOR-ON attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SIMULATOR-ON is : 
   * BooleanTruthValue
   *
   */
  public boolean getSimulatorOn() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SIMULATOR-ON
   * @param simulatorOn new value to conclude for SIMULATOR-ON
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSimulatorOn(boolean simulatorOn) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SIMULATION-PROCEDURE
   * @return the value of the SIMULATION-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SIMULATION-PROCEDURE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getSimulationProcedure() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SIMULATION-PROCEDURE
   * @param simulationProcedure new value to conclude for SIMULATION-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSimulationProcedure(com.gensym.util.Symbol simulationProcedure) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE?
   * @return the value of the SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE? is : 
   * BooleanTruthValue
   *
   */
  public boolean getSendAllValuesAtBeginningOfCycle() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE?
   * @param sendAllValuesAtBeginningOfCycle new value to conclude for SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSendAllValuesAtBeginningOfCycle(boolean sendAllValuesAtBeginningOfCycle) throws G2AccessException;

}
