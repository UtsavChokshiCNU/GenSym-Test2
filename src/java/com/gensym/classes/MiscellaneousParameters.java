/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      MiscellaneousParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:51 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface MiscellaneousParameters extends com.gensym.classes.SystemTable {

  public static final Symbol MISCELLANEOUS_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.MISCELLANEOUS_PARAMETERS_;
  static final Symbol g2ClassName = MISCELLANEOUS_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {MISCELLANEOUS_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- REPEAT-RANDOM-FUNCTION-ON-RESET?
   * @return the value of the REPEAT-RANDOM-FUNCTION-ON-RESET? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for REPEAT-RANDOM-FUNCTION-ON-RESET? is : 
   * BooleanTruthValue
   *
   */
  public boolean getRepeatRandomFunctionOnReset() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- REPEAT-RANDOM-FUNCTION-ON-RESET?
   * @param repeatRandomFunctionOnReset new value to conclude for REPEAT-RANDOM-FUNCTION-ON-RESET?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRepeatRandomFunctionOnReset(boolean repeatRandomFunctionOnReset) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INITIAL-MARGIN-FOR-WORKSPACES
   * @return the value of the INITIAL-MARGIN-FOR-WORKSPACES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INITIAL-MARGIN-FOR-WORKSPACES is : 
   * Integer
   *
   */
  public int getInitialMarginForWorkspaces() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INITIAL-MARGIN-FOR-WORKSPACES
   * @param initialMarginForWorkspaces new value to conclude for INITIAL-MARGIN-FOR-WORKSPACES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInitialMarginForWorkspaces(int initialMarginForWorkspaces) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- START-KB-AFTER-LOAD?
   * @return the value of the START-KB-AFTER-LOAD? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for START-KB-AFTER-LOAD? is : 
   * BooleanTruthValue
   *
   */
  public boolean getStartKbAfterLoad() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- START-KB-AFTER-LOAD?
   * @param startKbAfterLoad new value to conclude for START-KB-AFTER-LOAD?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStartKbAfterLoad(boolean startKbAfterLoad) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-RUN-STATE
   * @return the value of the G2-RUN-STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-RUN-STATE is : 
   * (MEMBER RESET RUNNING PAUSED)
   *
   */
  public com.gensym.util.Symbol getG2RunState() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CONFIRM-RUN-STATE-CHANGES
   * @return the value of the CONFIRM-RUN-STATE-CHANGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CONFIRM-RUN-STATE-CHANGES is : 
   * BooleanTruthValue
   *
   */
  public boolean getConfirmRunStateChanges() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CONFIRM-RUN-STATE-CHANGES
   * @param confirmRunStateChanges new value to conclude for CONFIRM-RUN-STATE-CHANGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setConfirmRunStateChanges(boolean confirmRunStateChanges) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- BACKWARD-COMPATIBILITY-FEATURES
   * @return the value of the BACKWARD-COMPATIBILITY-FEATURES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for BACKWARD-COMPATIBILITY-FEATURES is : 
   * (OR NoItem
      (Sequence 
        (MEMBER IGNORE-DUPLICATE-LIST-ELEMENT-ERROR EXTRA-VERTICES-IN-G2-GET-CONNECTION-VERTICES 
                PRINT-MEANS-PRINT-TO-SERVER-IN-CONFIGURATIONS 
                INCONSISTENT-BEHAVIOR-OF-MOVE-IN-CONFIGURATIONS 
                IGNORE-SNAP-GRID-IN-TRANSFER-OPERATIONS)
        0)))
   *
   */
  public com.gensym.util.Sequence getBackwardCompatibilityFeatures() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- BACKWARD-COMPATIBILITY-FEATURES
   * @param backwardCompatibilityFeatures new value to conclude for BACKWARD-COMPATIBILITY-FEATURES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setBackwardCompatibilityFeatures(com.gensym.util.Sequence backwardCompatibilityFeatures) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SHOW-UUIDS-IN-ATTRIBUTE-TABLES
   * @return the value of the SHOW-UUIDS-IN-ATTRIBUTE-TABLES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SHOW-UUIDS-IN-ATTRIBUTE-TABLES is : 
   * BooleanTruthValue
   *
   */
  public boolean getShowUuidsInAttributeTables() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SHOW-UUIDS-IN-ATTRIBUTE-TABLES
   * @param showUuidsInAttributeTables new value to conclude for SHOW-UUIDS-IN-ATTRIBUTE-TABLES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setShowUuidsInAttributeTables(boolean showUuidsInAttributeTables) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ENABLE-EXPLANATION-CONTROLS
   * @return the value of the ENABLE-EXPLANATION-CONTROLS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ENABLE-EXPLANATION-CONTROLS is : 
   * BooleanTruthValue
   *
   */
  public boolean getEnableExplanationControls() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ENABLE-EXPLANATION-CONTROLS
   * @param enableExplanationControls new value to conclude for ENABLE-EXPLANATION-CONTROLS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEnableExplanationControls(boolean enableExplanationControls) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CONNECTION-CACHING-ENABLED?
   * @return the value of the CONNECTION-CACHING-ENABLED? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CONNECTION-CACHING-ENABLED? is : 
   * BooleanTruthValue
   *
   */
  public boolean getConnectionCachingEnabled() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CONNECTION-CACHING-ENABLED?
   * @param connectionCachingEnabled new value to conclude for CONNECTION-CACHING-ENABLED?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setConnectionCachingEnabled(boolean connectionCachingEnabled) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PREFER-NATIVE-LOGIN-DIALOG
   * @return the value of the PREFER-NATIVE-LOGIN-DIALOG attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PREFER-NATIVE-LOGIN-DIALOG is : 
   * BooleanTruthValue
   *
   */
  public boolean getPreferNativeLoginDialog() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PREFER-NATIVE-LOGIN-DIALOG
   * @param preferNativeLoginDialog new value to conclude for PREFER-NATIVE-LOGIN-DIALOG
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPreferNativeLoginDialog(boolean preferNativeLoginDialog) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- AUTOMATIC-DEADLOCK-DETECTION-FREQUENCY
   * @return the value of the AUTOMATIC-DEADLOCK-DETECTION-FREQUENCY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for AUTOMATIC-DEADLOCK-DETECTION-FREQUENCY is : 
   * (OR (MEMBER NEVER)
      Integer)
   *
   */
  public java.lang.Object getAutomaticDeadlockDetectionFrequency() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- AUTOMATIC-DEADLOCK-DETECTION-FREQUENCY
   * @param automaticDeadlockDetectionFrequency new value to conclude for AUTOMATIC-DEADLOCK-DETECTION-FREQUENCY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAutomaticDeadlockDetectionFrequency(java.lang.Object automaticDeadlockDetectionFrequency) throws G2AccessException;

}
