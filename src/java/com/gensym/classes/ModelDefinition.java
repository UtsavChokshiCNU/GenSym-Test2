/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ModelDefinition.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:53 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface ModelDefinition extends com.gensym.classes.Item, com.gensym.classes.Entity {

  public static final Symbol MODEL_DEFINITION_ = com.gensym.util.symbol.G2ClassSymbols.MODEL_DEFINITION_;
  static final Symbol g2ClassName = MODEL_DEFINITION_;
  static final Symbol[] classInheritancePath = new Symbol[] {MODEL_DEFINITION_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


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
   * Generated Property Getter for attribute -- ITEMS-BELONGING-TO-THIS-MODEL
   * @return the value of the ITEMS-BELONGING-TO-THIS-MODEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ITEMS-BELONGING-TO-THIS-MODEL is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getItemsBelongingToThisModel() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ITEMS-BELONGING-TO-THIS-MODEL
   * @param itemsBelongingToThisModel new value to conclude for ITEMS-BELONGING-TO-THIS-MODEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setItemsBelongingToThisModel(java.lang.String itemsBelongingToThisModel) throws G2AccessException;

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
   * Generated Property Getter for attribute -- SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE
   * @return the value of the SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE is : 
   * BooleanTruthValue
   *
   */
  public boolean getSendAllValuesAtBeginningOfCycle() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE
   * @param sendAllValuesAtBeginningOfCycle new value to conclude for SEND-ALL-VALUES-AT-BEGINNING-OF-CYCLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSendAllValuesAtBeginningOfCycle(boolean sendAllValuesAtBeginningOfCycle) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MODEL-SIMULATION-STATUS
   * @return the value of the MODEL-SIMULATION-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MODEL-SIMULATION-STATUS is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text
      (Sequence)
      (Structure))
   *
   */
  public java.lang.Object getModelSimulationStatus() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SIMULATION-CONTROL-SPECIFICATIONS
   * @return the value of the SIMULATION-CONTROL-SPECIFICATIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SIMULATION-CONTROL-SPECIFICATIONS is : 
   * (Structure 
    SYNCHRONIZATION-MODE
      (MEMBER RUN-SYNCHRONOUSLY RUN-AS-FAST-AS-POSSIBLE)
    WITHOUT-INCREMENTING-SIMULATION-TIME BooleanTruthValue
    WITHOUT-WAITING-FOR-EXTERNAL-SIMULATION-CYCLE BooleanTruthValue)
   *
   */
  public com.gensym.util.Structure getSimulationControlSpecifications() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SIMULATION-CONTROL-SPECIFICATIONS
   * @param simulationControlSpecifications new value to conclude for SIMULATION-CONTROL-SPECIFICATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSimulationControlSpecifications(com.gensym.util.Structure simulationControlSpecifications) throws G2AccessException;

}
