/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GsiInterface.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:57:06 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface GsiInterface extends com.gensym.classes.NetworkInterface {

  public static final Symbol GSI_INTERFACE_ = com.gensym.util.symbol.G2ClassSymbols.GSI_INTERFACE_;
  static final Symbol g2ClassName = GSI_INTERFACE_;
  static final Symbol[] classInheritancePath = new Symbol[] {GSI_INTERFACE_, NETWORK_INTERFACE_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- GSI-CONNECTION-CONFIGURATION
   * @return the value of the GSI-CONNECTION-CONFIGURATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GSI-CONNECTION-CONFIGURATION is : 
   * (OR NoItem
      (Structure 
        NETWORK-TRANSPORT
          (MEMBER TCP-IP)
        HOSTNAME
          (OR Text
              Symbol)
        PORT
          (OR Integer
              Symbol)))
   *
   */
  public com.gensym.util.Structure getGsiConnectionConfiguration() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GSI-CONNECTION-CONFIGURATION
   * @param gsiConnectionConfiguration new value to conclude for GSI-CONNECTION-CONFIGURATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGsiConnectionConfiguration(com.gensym.util.Structure gsiConnectionConfiguration) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- EXTERNAL-SYSTEM-HAS-A-SCHEDULER
   * @return the value of the EXTERNAL-SYSTEM-HAS-A-SCHEDULER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for EXTERNAL-SYSTEM-HAS-A-SCHEDULER is : 
   * BooleanTruthValue
   *
   */
  public boolean getExternalSystemHasAScheduler() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- EXTERNAL-SYSTEM-HAS-A-SCHEDULER
   * @param externalSystemHasAScheduler new value to conclude for EXTERNAL-SYSTEM-HAS-A-SCHEDULER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setExternalSystemHasAScheduler(boolean externalSystemHasAScheduler) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- POLL-EXTERNAL-SYSTEM-FOR-DATA
   * @return the value of the POLL-EXTERNAL-SYSTEM-FOR-DATA attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for POLL-EXTERNAL-SYSTEM-FOR-DATA is : 
   * BooleanTruthValue
   *
   */
  public boolean getPollExternalSystemForData() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- POLL-EXTERNAL-SYSTEM-FOR-DATA
   * @param pollExternalSystemForData new value to conclude for POLL-EXTERNAL-SYSTEM-FOR-DATA
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPollExternalSystemForData(boolean pollExternalSystemForData) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GROUPING-SPECIFICATION
   * @return the value of the GROUPING-SPECIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GROUPING-SPECIFICATION is : 
   * (OR NoItem
      (Sequence Symbol 1))
   *
   */
  public com.gensym.util.Sequence getGroupingSpecification() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GROUPING-SPECIFICATION
   * @param groupingSpecification new value to conclude for GROUPING-SPECIFICATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGroupingSpecification(com.gensym.util.Sequence groupingSpecification) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- REMOTE-PROCESS-INITIALIZATION-STRING
   * @return the value of the REMOTE-PROCESS-INITIALIZATION-STRING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for REMOTE-PROCESS-INITIALIZATION-STRING is : 
   * Text
   *
   */
  public java.lang.String getRemoteProcessInitializationString() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- REMOTE-PROCESS-INITIALIZATION-STRING
   * @param remoteProcessInitializationString new value to conclude for REMOTE-PROCESS-INITIALIZATION-STRING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRemoteProcessInitializationString(java.lang.String remoteProcessInitializationString) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GSI-APPLICATION-NAME
   * @return the value of the GSI-APPLICATION-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GSI-APPLICATION-NAME is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getGsiApplicationName() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GSI-APPLICATION-NAME
   * @param gsiApplicationName new value to conclude for GSI-APPLICATION-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGsiApplicationName(com.gensym.util.Symbol gsiApplicationName) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GSI-INTERFACE-STATUS
   * @return the value of the GSI-INTERFACE-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GSI-INTERFACE-STATUS is : 
   * Integer
   *
   */
  public int getGsiInterfaceStatus() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GSI-INTERFACE-IS-SECURE
   * @return the value of the GSI-INTERFACE-IS-SECURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GSI-INTERFACE-IS-SECURE is : 
   * BooleanTruthValue
   *
   */
  public boolean getGsiInterfaceIsSecure() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INTERVAL-TO-POLL-EXTERNAL-SYSTEM
   * @return the value of the INTERVAL-TO-POLL-EXTERNAL-SYSTEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INTERVAL-TO-POLL-EXTERNAL-SYSTEM is : 
   * (OR (MEMBER USE-DEFAULT)
      Integer)
   *
   */
  public java.lang.Object getIntervalToPollExternalSystem() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INTERVAL-TO-POLL-EXTERNAL-SYSTEM
   * @param intervalToPollExternalSystem new value to conclude for INTERVAL-TO-POLL-EXTERNAL-SYSTEM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIntervalToPollExternalSystem(java.lang.Object intervalToPollExternalSystem) throws G2AccessException;

}
