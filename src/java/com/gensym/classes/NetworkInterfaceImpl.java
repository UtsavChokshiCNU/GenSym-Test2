/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      NetworkInterfaceImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:04:08 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class NetworkInterfaceImpl extends com.gensym.classes.ObjectImpl implements NetworkInterface {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public NetworkInterfaceImpl() {
    super();
  }

  public NetworkInterfaceImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public NetworkInterfaceImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- IDENTIFYING-ATTRIBUTES
   * @param identifyingAttributes new value to conclude for IDENTIFYING-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setIdentifyingAttributes(com.gensym.util.Sequence identifyingAttributes) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.IDENTIFYING_ATTRIBUTES_, identifyingAttributes);
  }

  /**
   * Generated Property Getter for attribute -- IDENTIFYING-ATTRIBUTES
   * @return the value of the IDENTIFYING-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getIdentifyingAttributes() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.IDENTIFYING_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- INTERFACE-WARNING-MESSAGE-LEVEL
   * @param interfaceWarningMessageLevel new value to conclude for INTERFACE-WARNING-MESSAGE-LEVEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setInterfaceWarningMessageLevel(com.gensym.util.Symbol interfaceWarningMessageLevel) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.INTERFACE_WARNING_MESSAGE_LEVEL_, interfaceWarningMessageLevel);
  }

  /**
   * Generated Property Getter for attribute -- INTERFACE-WARNING-MESSAGE-LEVEL
   * @return the value of the INTERFACE-WARNING-MESSAGE-LEVEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getInterfaceWarningMessageLevel() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INTERFACE_WARNING_MESSAGE_LEVEL_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DISABLE-INTERLEAVING-OF-LARGE-MESSAGES
   * @param disableInterleavingOfLargeMessages new value to conclude for DISABLE-INTERLEAVING-OF-LARGE-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDisableInterleavingOfLargeMessages(boolean disableInterleavingOfLargeMessages) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DISABLE_INTERLEAVING_OF_LARGE_MESSAGES_, new Boolean (disableInterleavingOfLargeMessages));
  }

  /**
   * Generated Property Getter for attribute -- DISABLE-INTERLEAVING-OF-LARGE-MESSAGES
   * @return the value of the DISABLE-INTERLEAVING-OF-LARGE-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getDisableInterleavingOfLargeMessages() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DISABLE_INTERLEAVING_OF_LARGE_MESSAGES_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- INTERFACE-TIMEOUT-PERIOD
   * @param interfaceTimeoutPeriod new value to conclude for INTERFACE-TIMEOUT-PERIOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setInterfaceTimeoutPeriod(java.lang.Object interfaceTimeoutPeriod) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.INTERFACE_TIMEOUT_PERIOD_, interfaceTimeoutPeriod);
  }

  /**
   * Generated Property Getter for attribute -- INTERFACE-TIMEOUT-PERIOD
   * @return the value of the INTERFACE-TIMEOUT-PERIOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getInterfaceTimeoutPeriod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INTERFACE_TIMEOUT_PERIOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- INTERFACE-INITIALIZATION-TIMEOUT-PERIOD
   * @param interfaceInitializationTimeoutPeriod new value to conclude for INTERFACE-INITIALIZATION-TIMEOUT-PERIOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setInterfaceInitializationTimeoutPeriod(java.lang.Object interfaceInitializationTimeoutPeriod) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.INTERFACE_INITIALIZATION_TIMEOUT_PERIOD_, interfaceInitializationTimeoutPeriod);
  }

  /**
   * Generated Property Getter for attribute -- INTERFACE-INITIALIZATION-TIMEOUT-PERIOD
   * @return the value of the INTERFACE-INITIALIZATION-TIMEOUT-PERIOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getInterfaceInitializationTimeoutPeriod() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INTERFACE_INITIALIZATION_TIMEOUT_PERIOD_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- EVALUATION-ATTRIBUTES
   * @param evaluationAttributes new value to conclude for EVALUATION-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setEvaluationAttributes(com.gensym.util.Structure evaluationAttributes) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.EVALUATION_ATTRIBUTES_, evaluationAttributes);
  }

  /**
   * Generated Property Getter for attribute -- EVALUATION-ATTRIBUTES
   * @return the value of the EVALUATION-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getEvaluationAttributes() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.EVALUATION_ATTRIBUTES_);
    return (com.gensym.util.Structure)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
