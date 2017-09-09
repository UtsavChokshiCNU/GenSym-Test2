/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      TimingParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:11:39 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class TimingParametersImpl extends com.gensym.classes.SystemTableImpl implements TimingParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public TimingParametersImpl() {
    super();
  }

  public TimingParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public TimingParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- SCHEDULER-MODE
   * @param schedulerMode new value to conclude for SCHEDULER-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSchedulerMode(com.gensym.util.Symbol schedulerMode) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SCHEDULER_MODE_, schedulerMode);
  }

  /**
   * Generated Property Getter for attribute -- SCHEDULER-MODE
   * @return the value of the SCHEDULER-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getSchedulerMode() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SCHEDULER_MODE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLOCK-ADJUSTMENT-IN-MINUTES
   * @param clockAdjustmentInMinutes new value to conclude for CLOCK-ADJUSTMENT-IN-MINUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setClockAdjustmentInMinutes(int clockAdjustmentInMinutes) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.CLOCK_ADJUSTMENT_IN_MINUTES_, clockAdjustmentInMinutes);
  }

  /**
   * Generated Property Getter for attribute -- CLOCK-ADJUSTMENT-IN-MINUTES
   * @return the value of the CLOCK-ADJUSTMENT-IN-MINUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getClockAdjustmentInMinutes() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CLOCK_ADJUSTMENT_IN_MINUTES_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- FOREIGN-FUNCTION-TIMEOUT-INTERVAL
   * @param foreignFunctionTimeoutInterval new value to conclude for FOREIGN-FUNCTION-TIMEOUT-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setForeignFunctionTimeoutInterval(java.lang.Object foreignFunctionTimeoutInterval) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FOREIGN_FUNCTION_TIMEOUT_INTERVAL_, foreignFunctionTimeoutInterval);
  }

  /**
   * Generated Property Getter for attribute -- FOREIGN-FUNCTION-TIMEOUT-INTERVAL
   * @return the value of the FOREIGN-FUNCTION-TIMEOUT-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getForeignFunctionTimeoutInterval() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FOREIGN_FUNCTION_TIMEOUT_INTERVAL_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- RECONNECT-TO-FOREIGN-IMAGE-AFTER-TIMEOUT?
   * @param reconnectToForeignImageAfterTimeout new value to conclude for RECONNECT-TO-FOREIGN-IMAGE-AFTER-TIMEOUT?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setReconnectToForeignImageAfterTimeout(boolean reconnectToForeignImageAfterTimeout) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.RECONNECT_TO_FOREIGN_IMAGE_AFTER_TIMEOUTQ_, new Boolean (reconnectToForeignImageAfterTimeout));
  }

  /**
   * Generated Property Getter for attribute -- RECONNECT-TO-FOREIGN-IMAGE-AFTER-TIMEOUT?
   * @return the value of the RECONNECT-TO-FOREIGN-IMAGE-AFTER-TIMEOUT? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getReconnectToForeignImageAfterTimeout() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.RECONNECT_TO_FOREIGN_IMAGE_AFTER_TIMEOUTQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-DISPLAY-UPDATE-INTERVAL
   * @param attributeDisplayUpdateInterval new value to conclude for ATTRIBUTE-DISPLAY-UPDATE-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAttributeDisplayUpdateInterval(java.lang.Object attributeDisplayUpdateInterval) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ATTRIBUTE_DISPLAY_UPDATE_INTERVAL_, attributeDisplayUpdateInterval);
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-DISPLAY-UPDATE-INTERVAL
   * @return the value of the ATTRIBUTE-DISPLAY-UPDATE-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getAttributeDisplayUpdateInterval() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ATTRIBUTE_DISPLAY_UPDATE_INTERVAL_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
