/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      TimingParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:11:38 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface TimingParameters extends com.gensym.classes.SystemTable {

  public static final Symbol TIMING_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.TIMING_PARAMETERS_;
  static final Symbol g2ClassName = TIMING_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {TIMING_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- SCHEDULER-MODE
   * @return the value of the SCHEDULER-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SCHEDULER-MODE is : 
   * (MEMBER REAL-TIME SIMULATED-TIME AS-FAST-AS-POSSIBLE)
   *
   */
  public com.gensym.util.Symbol getSchedulerMode() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SCHEDULER-MODE
   * @param schedulerMode new value to conclude for SCHEDULER-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSchedulerMode(com.gensym.util.Symbol schedulerMode) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CLOCK-ADJUSTMENT-IN-MINUTES
   * @return the value of the CLOCK-ADJUSTMENT-IN-MINUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CLOCK-ADJUSTMENT-IN-MINUTES is : 
   * Integer
   *
   */
  public int getClockAdjustmentInMinutes() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CLOCK-ADJUSTMENT-IN-MINUTES
   * @param clockAdjustmentInMinutes new value to conclude for CLOCK-ADJUSTMENT-IN-MINUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setClockAdjustmentInMinutes(int clockAdjustmentInMinutes) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FOREIGN-FUNCTION-TIMEOUT-INTERVAL
   * @return the value of the FOREIGN-FUNCTION-TIMEOUT-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FOREIGN-FUNCTION-TIMEOUT-INTERVAL is : 
   * (OR (MEMBER USE-DEFAULT)
      Integer)
   *
   */
  public java.lang.Object getForeignFunctionTimeoutInterval() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FOREIGN-FUNCTION-TIMEOUT-INTERVAL
   * @param foreignFunctionTimeoutInterval new value to conclude for FOREIGN-FUNCTION-TIMEOUT-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setForeignFunctionTimeoutInterval(java.lang.Object foreignFunctionTimeoutInterval) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- RECONNECT-TO-FOREIGN-IMAGE-AFTER-TIMEOUT?
   * @return the value of the RECONNECT-TO-FOREIGN-IMAGE-AFTER-TIMEOUT? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for RECONNECT-TO-FOREIGN-IMAGE-AFTER-TIMEOUT? is : 
   * BooleanTruthValue
   *
   */
  public boolean getReconnectToForeignImageAfterTimeout() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- RECONNECT-TO-FOREIGN-IMAGE-AFTER-TIMEOUT?
   * @param reconnectToForeignImageAfterTimeout new value to conclude for RECONNECT-TO-FOREIGN-IMAGE-AFTER-TIMEOUT?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setReconnectToForeignImageAfterTimeout(boolean reconnectToForeignImageAfterTimeout) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-DISPLAY-UPDATE-INTERVAL
   * @return the value of the ATTRIBUTE-DISPLAY-UPDATE-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ATTRIBUTE-DISPLAY-UPDATE-INTERVAL is : 
   * (OR (MEMBER CONTINUOUS)
      Float)
   *
   */
  public java.lang.Object getAttributeDisplayUpdateInterval() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-DISPLAY-UPDATE-INTERVAL
   * @param attributeDisplayUpdateInterval new value to conclude for ATTRIBUTE-DISPLAY-UPDATE-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAttributeDisplayUpdateInterval(java.lang.Object attributeDisplayUpdateInterval) throws G2AccessException;

}
