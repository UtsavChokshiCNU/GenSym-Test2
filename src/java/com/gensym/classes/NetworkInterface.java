/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      NetworkInterface.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:04:03 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface NetworkInterface extends com.gensym.classes.Object {

  public static final Symbol NETWORK_INTERFACE_ = com.gensym.util.symbol.G2ClassSymbols.NETWORK_INTERFACE_;
  static final Symbol g2ClassName = NETWORK_INTERFACE_;
  static final Symbol[] classInheritancePath = new Symbol[] {NETWORK_INTERFACE_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- IDENTIFYING-ATTRIBUTES
   * @return the value of the IDENTIFYING-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for IDENTIFYING-ATTRIBUTES is : 
   * (OR NoItem
      (Sequence 
        (OR Symbol
            (Structure 
              CLASS Symbol
              CLASS-IDENTIFYING-ATTRIBUTES
                (Sequence 
                  (OR Symbol
                      (Structure 
                        ATTRIBUTE Symbol
                        NAME-FOR-NETWORK Symbol))
                  1))))
        1)))
   *
   */
  public com.gensym.util.Sequence getIdentifyingAttributes() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- IDENTIFYING-ATTRIBUTES
   * @param identifyingAttributes new value to conclude for IDENTIFYING-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIdentifyingAttributes(com.gensym.util.Sequence identifyingAttributes) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INTERFACE-WARNING-MESSAGE-LEVEL
   * @return the value of the INTERFACE-WARNING-MESSAGE-LEVEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INTERFACE-WARNING-MESSAGE-LEVEL is : 
   * (MEMBER WARNING-MESSAGE-LEVEL 0 1 2 3)
   *
   */
  public com.gensym.util.Symbol getInterfaceWarningMessageLevel() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INTERFACE-WARNING-MESSAGE-LEVEL
   * @param interfaceWarningMessageLevel new value to conclude for INTERFACE-WARNING-MESSAGE-LEVEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInterfaceWarningMessageLevel(com.gensym.util.Symbol interfaceWarningMessageLevel) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DISABLE-INTERLEAVING-OF-LARGE-MESSAGES
   * @return the value of the DISABLE-INTERLEAVING-OF-LARGE-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DISABLE-INTERLEAVING-OF-LARGE-MESSAGES is : 
   * BooleanTruthValue
   *
   */
  public boolean getDisableInterleavingOfLargeMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DISABLE-INTERLEAVING-OF-LARGE-MESSAGES
   * @param disableInterleavingOfLargeMessages new value to conclude for DISABLE-INTERLEAVING-OF-LARGE-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDisableInterleavingOfLargeMessages(boolean disableInterleavingOfLargeMessages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INTERFACE-TIMEOUT-PERIOD
   * @return the value of the INTERFACE-TIMEOUT-PERIOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INTERFACE-TIMEOUT-PERIOD is : 
   * (OR (MEMBER USE-DEFAULT)
      Integer)
   *
   */
  public java.lang.Object getInterfaceTimeoutPeriod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INTERFACE-TIMEOUT-PERIOD
   * @param interfaceTimeoutPeriod new value to conclude for INTERFACE-TIMEOUT-PERIOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInterfaceTimeoutPeriod(java.lang.Object interfaceTimeoutPeriod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INTERFACE-INITIALIZATION-TIMEOUT-PERIOD
   * @return the value of the INTERFACE-INITIALIZATION-TIMEOUT-PERIOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INTERFACE-INITIALIZATION-TIMEOUT-PERIOD is : 
   * (OR (MEMBER USE-DEFAULT UNLIMITED)
      Integer)
   *
   */
  public java.lang.Object getInterfaceInitializationTimeoutPeriod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INTERFACE-INITIALIZATION-TIMEOUT-PERIOD
   * @param interfaceInitializationTimeoutPeriod new value to conclude for INTERFACE-INITIALIZATION-TIMEOUT-PERIOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInterfaceInitializationTimeoutPeriod(java.lang.Object interfaceInitializationTimeoutPeriod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- EVALUATION-ATTRIBUTES
   * @return the value of the EVALUATION-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for EVALUATION-ATTRIBUTES is : 
   * (OR NoItem
      (Structure 
        MAY-REFER-TO-INACTIVE-ITEMS BooleanTruthValue
        MAY-RUN-WHILE-INACTIVE BooleanTruthValue))
   *
   */
  public com.gensym.util.Structure getEvaluationAttributes() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- EVALUATION-ATTRIBUTES
   * @param evaluationAttributes new value to conclude for EVALUATION-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEvaluationAttributes(com.gensym.util.Structure evaluationAttributes) throws G2AccessException;

}
