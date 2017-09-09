/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GsiInterfaceImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI25)
 *
 *          Date: Wed Sep 26 10:44:38 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class GsiInterfaceImpl extends com.gensym.classes.NetworkInterfaceImpl implements GsiInterface {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public GsiInterfaceImpl() {
    super();
  }

  public GsiInterfaceImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public GsiInterfaceImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- GSI-CONNECTION-CONFIGURATION
   * @param gsiConnectionConfiguration new value to conclude for GSI-CONNECTION-CONFIGURATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGsiConnectionConfiguration(com.gensym.util.Structure gsiConnectionConfiguration) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GSI_CONNECTION_CONFIGURATION_, gsiConnectionConfiguration);
  }

  /**
   * Generated Property Getter for attribute -- GSI-CONNECTION-CONFIGURATION
   * @return the value of the GSI-CONNECTION-CONFIGURATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getGsiConnectionConfiguration() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GSI_CONNECTION_CONFIGURATION_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- EXTERNAL-SYSTEM-HAS-A-SCHEDULER
   * @param externalSystemHasAScheduler new value to conclude for EXTERNAL-SYSTEM-HAS-A-SCHEDULER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setExternalSystemHasAScheduler(boolean externalSystemHasAScheduler) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.EXTERNAL_SYSTEM_HAS_A_SCHEDULER_, new Boolean (externalSystemHasAScheduler));
  }

  /**
   * Generated Property Getter for attribute -- EXTERNAL-SYSTEM-HAS-A-SCHEDULER
   * @return the value of the EXTERNAL-SYSTEM-HAS-A-SCHEDULER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getExternalSystemHasAScheduler() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.EXTERNAL_SYSTEM_HAS_A_SCHEDULER_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- POLL-EXTERNAL-SYSTEM-FOR-DATA
   * @param pollExternalSystemForData new value to conclude for POLL-EXTERNAL-SYSTEM-FOR-DATA
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPollExternalSystemForData(boolean pollExternalSystemForData) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.POLL_EXTERNAL_SYSTEM_FOR_DATA_, new Boolean (pollExternalSystemForData));
  }

  /**
   * Generated Property Getter for attribute -- POLL-EXTERNAL-SYSTEM-FOR-DATA
   * @return the value of the POLL-EXTERNAL-SYSTEM-FOR-DATA attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getPollExternalSystemForData() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.POLL_EXTERNAL_SYSTEM_FOR_DATA_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- GROUPING-SPECIFICATION
   * @param groupingSpecification new value to conclude for GROUPING-SPECIFICATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGroupingSpecification(com.gensym.util.Sequence groupingSpecification) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GROUPING_SPECIFICATION_, groupingSpecification);
  }

  /**
   * Generated Property Getter for attribute -- GROUPING-SPECIFICATION
   * @return the value of the GROUPING-SPECIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getGroupingSpecification() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GROUPING_SPECIFICATION_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- REMOTE-PROCESS-INITIALIZATION-STRING
   * @param remoteProcessInitializationString new value to conclude for REMOTE-PROCESS-INITIALIZATION-STRING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRemoteProcessInitializationString(java.lang.String remoteProcessInitializationString) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.REMOTE_PROCESS_INITIALIZATION_STRING_, remoteProcessInitializationString);
  }

  /**
   * Generated Property Getter for attribute -- REMOTE-PROCESS-INITIALIZATION-STRING
   * @return the value of the REMOTE-PROCESS-INITIALIZATION-STRING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getRemoteProcessInitializationString() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.REMOTE_PROCESS_INITIALIZATION_STRING_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GSI-APPLICATION-NAME
   * @param gsiApplicationName new value to conclude for GSI-APPLICATION-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGsiApplicationName(com.gensym.util.Symbol gsiApplicationName) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GSI_APPLICATION_NAME_, gsiApplicationName);
  }

  /**
   * Generated Property Getter for attribute -- GSI-APPLICATION-NAME
   * @return the value of the GSI-APPLICATION-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getGsiApplicationName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GSI_APPLICATION_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- GSI-INTERFACE-STATUS
   * @return the value of the GSI-INTERFACE-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getGsiInterfaceStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GSI_INTERFACE_STATUS_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Getter for attribute -- GSI-INTERFACE-IS-SECURE
   * @return the value of the GSI-INTERFACE-IS-SECURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getGsiInterfaceIsSecure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GSI_INTERFACE_IS_SECURE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- INTERVAL-TO-POLL-EXTERNAL-SYSTEM
   * @param intervalToPollExternalSystem new value to conclude for INTERVAL-TO-POLL-EXTERNAL-SYSTEM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setIntervalToPollExternalSystem(java.lang.Object intervalToPollExternalSystem) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.INTERVAL_TO_POLL_EXTERNAL_SYSTEM_, intervalToPollExternalSystem);
  }

  /**
   * Generated Property Getter for attribute -- INTERVAL-TO-POLL-EXTERNAL-SYSTEM
   * @return the value of the INTERVAL-TO-POLL-EXTERNAL-SYSTEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getIntervalToPollExternalSystem() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INTERVAL_TO_POLL_EXTERNAL_SYSTEM_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
