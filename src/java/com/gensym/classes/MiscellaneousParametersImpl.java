/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      MiscellaneousParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:52 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class MiscellaneousParametersImpl extends com.gensym.classes.SystemTableImpl implements MiscellaneousParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public MiscellaneousParametersImpl() {
    super();
  }

  public MiscellaneousParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public MiscellaneousParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- REPEAT-RANDOM-FUNCTION-ON-RESET?
   * @param repeatRandomFunctionOnReset new value to conclude for REPEAT-RANDOM-FUNCTION-ON-RESET?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRepeatRandomFunctionOnReset(boolean repeatRandomFunctionOnReset) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.REPEAT_RANDOM_FUNCTION_ON_RESETQ_, repeatRandomFunctionOnReset);
  }

  /**
   * Generated Property Getter for attribute -- REPEAT-RANDOM-FUNCTION-ON-RESET?
   * @return the value of the REPEAT-RANDOM-FUNCTION-ON-RESET? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getRepeatRandomFunctionOnReset() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.REPEAT_RANDOM_FUNCTION_ON_RESETQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- INITIAL-MARGIN-FOR-WORKSPACES
   * @param initialMarginForWorkspaces new value to conclude for INITIAL-MARGIN-FOR-WORKSPACES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setInitialMarginForWorkspaces(int initialMarginForWorkspaces) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.INITIAL_MARGIN_FOR_WORKSPACES_, initialMarginForWorkspaces);
  }

  /**
   * Generated Property Getter for attribute -- INITIAL-MARGIN-FOR-WORKSPACES
   * @return the value of the INITIAL-MARGIN-FOR-WORKSPACES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getInitialMarginForWorkspaces() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INITIAL_MARGIN_FOR_WORKSPACES_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- START-KB-AFTER-LOAD?
   * @param startKbAfterLoad new value to conclude for START-KB-AFTER-LOAD?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setStartKbAfterLoad(boolean startKbAfterLoad) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.START_KB_AFTER_LOADQ_, startKbAfterLoad);
  }

  /**
   * Generated Property Getter for attribute -- START-KB-AFTER-LOAD?
   * @return the value of the START-KB-AFTER-LOAD? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getStartKbAfterLoad() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.START_KB_AFTER_LOADQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Getter for attribute -- G2-RUN-STATE
   * @return the value of the G2-RUN-STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getG2RunState() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_RUN_STATE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CONFIRM-RUN-STATE-CHANGES
   * @param confirmRunStateChanges new value to conclude for CONFIRM-RUN-STATE-CHANGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setConfirmRunStateChanges(boolean confirmRunStateChanges) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.CONFIRM_RUN_STATE_CHANGES_, confirmRunStateChanges);
  }

  /**
   * Generated Property Getter for attribute -- CONFIRM-RUN-STATE-CHANGES
   * @return the value of the CONFIRM-RUN-STATE-CHANGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getConfirmRunStateChanges() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CONFIRM_RUN_STATE_CHANGES_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- BACKWARD-COMPATIBILITY-FEATURES
   * @param backwardCompatibilityFeatures new value to conclude for BACKWARD-COMPATIBILITY-FEATURES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setBackwardCompatibilityFeatures(com.gensym.util.Sequence backwardCompatibilityFeatures) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.BACKWARD_COMPATIBILITY_FEATURES_, backwardCompatibilityFeatures);
  }

  /**
   * Generated Property Getter for attribute -- BACKWARD-COMPATIBILITY-FEATURES
   * @return the value of the BACKWARD-COMPATIBILITY-FEATURES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getBackwardCompatibilityFeatures() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.BACKWARD_COMPATIBILITY_FEATURES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- SHOW-UUIDS-IN-ATTRIBUTE-TABLES
   * @param showUuidsInAttributeTables new value to conclude for SHOW-UUIDS-IN-ATTRIBUTE-TABLES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setShowUuidsInAttributeTables(boolean showUuidsInAttributeTables) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SHOW_UUIDS_IN_ATTRIBUTE_TABLES_, showUuidsInAttributeTables);
  }

  /**
   * Generated Property Getter for attribute -- SHOW-UUIDS-IN-ATTRIBUTE-TABLES
   * @return the value of the SHOW-UUIDS-IN-ATTRIBUTE-TABLES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getShowUuidsInAttributeTables() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SHOW_UUIDS_IN_ATTRIBUTE_TABLES_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- ENABLE-EXPLANATION-CONTROLS
   * @param enableExplanationControls new value to conclude for ENABLE-EXPLANATION-CONTROLS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setEnableExplanationControls(boolean enableExplanationControls) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ENABLE_EXPLANATION_CONTROLS_, enableExplanationControls);
  }

  /**
   * Generated Property Getter for attribute -- ENABLE-EXPLANATION-CONTROLS
   * @return the value of the ENABLE-EXPLANATION-CONTROLS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getEnableExplanationControls() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ENABLE_EXPLANATION_CONTROLS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- CONNECTION-CACHING-ENABLED?
   * @param connectionCachingEnabled new value to conclude for CONNECTION-CACHING-ENABLED?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setConnectionCachingEnabled(boolean connectionCachingEnabled) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.CONNECTION_CACHING_ENABLEDQ_, connectionCachingEnabled);
  }

  /**
   * Generated Property Getter for attribute -- CONNECTION-CACHING-ENABLED?
   * @return the value of the CONNECTION-CACHING-ENABLED? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getConnectionCachingEnabled() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CONNECTION_CACHING_ENABLEDQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- PREFER-NATIVE-LOGIN-DIALOG
   * @param preferNativeLoginDialog new value to conclude for PREFER-NATIVE-LOGIN-DIALOG
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPreferNativeLoginDialog(boolean preferNativeLoginDialog) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PREFER_NATIVE_LOGIN_DIALOG_, preferNativeLoginDialog);
  }

  /**
   * Generated Property Getter for attribute -- PREFER-NATIVE-LOGIN-DIALOG
   * @return the value of the PREFER-NATIVE-LOGIN-DIALOG attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getPreferNativeLoginDialog() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PREFER_NATIVE_LOGIN_DIALOG_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- AUTOMATIC-DEADLOCK-DETECTION-FREQUENCY
   * @param automaticDeadlockDetectionFrequency new value to conclude for AUTOMATIC-DEADLOCK-DETECTION-FREQUENCY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAutomaticDeadlockDetectionFrequency(java.lang.Object automaticDeadlockDetectionFrequency) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.AUTOMATIC_DEADLOCK_DETECTION_FREQUENCY_, automaticDeadlockDetectionFrequency);
  }

  /**
   * Generated Property Getter for attribute -- AUTOMATIC-DEADLOCK-DETECTION-FREQUENCY
   * @return the value of the AUTOMATIC-DEADLOCK-DETECTION-FREQUENCY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getAutomaticDeadlockDetectionFrequency() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.AUTOMATIC_DEADLOCK_DETECTION_FREQUENCY_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
