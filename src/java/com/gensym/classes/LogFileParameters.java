/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      LogFileParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:00:39 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface LogFileParameters extends com.gensym.classes.SystemTable {

  public static final Symbol LOG_FILE_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.LOG_FILE_PARAMETERS_;
  static final Symbol g2ClassName = LOG_FILE_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {LOG_FILE_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- LOG-FILE-ENABLED
   * @return the value of the LOG-FILE-ENABLED attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LOG-FILE-ENABLED is : 
   * BooleanTruthValue
   *
   */
  public boolean getLogFileEnabled() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LOG-FILE-ENABLED
   * @param logFileEnabled new value to conclude for LOG-FILE-ENABLED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLogFileEnabled(boolean logFileEnabled) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DIRECTORY-FOR-LOG-FILES
   * @return the value of the DIRECTORY-FOR-LOG-FILES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DIRECTORY-FOR-LOG-FILES is : 
   * (OR (MEMBER DEFAULT)
      Text)
   *
   */
  public java.lang.Object getDirectoryForLogFiles() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DIRECTORY-FOR-LOG-FILES
   * @param directoryForLogFiles new value to conclude for DIRECTORY-FOR-LOG-FILES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDirectoryForLogFiles(java.lang.Object directoryForLogFiles) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ROOT-NAME-FOR-LOG-FILES
   * @return the value of the ROOT-NAME-FOR-LOG-FILES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ROOT-NAME-FOR-LOG-FILES is : 
   * Text
   *
   */
  public java.lang.String getRootNameForLogFiles() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ROOT-NAME-FOR-LOG-FILES
   * @param rootNameForLogFiles new value to conclude for ROOT-NAME-FOR-LOG-FILES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRootNameForLogFiles(java.lang.String rootNameForLogFiles) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CURRENT-LOG-FILE
   * @return the value of the CURRENT-LOG-FILE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CURRENT-LOG-FILE is : 
   * (OR NoItem
      Text)
   *
   */
  public java.lang.String getCurrentLogFile() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- WHEN-TO-CLOSE-CURRENT-LOG-FILE-AND-OPEN-NEXT-ONE
   * @return the value of the WHEN-TO-CLOSE-CURRENT-LOG-FILE-AND-OPEN-NEXT-ONE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for WHEN-TO-CLOSE-CURRENT-LOG-FILE-AND-OPEN-NEXT-ONE is : 
   * (OR NoItem
      (Structure 
        AFTER-MESSAGES Integer
        AFTER-INTERVAL Integer))
   *
   */
  public com.gensym.util.Structure getWhenToCloseCurrentLogFileAndOpenNextOne() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- WHEN-TO-CLOSE-CURRENT-LOG-FILE-AND-OPEN-NEXT-ONE
   * @param whenToCloseCurrentLogFileAndOpenNextOne new value to conclude for WHEN-TO-CLOSE-CURRENT-LOG-FILE-AND-OPEN-NEXT-ONE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setWhenToCloseCurrentLogFileAndOpenNextOne(com.gensym.util.Structure whenToCloseCurrentLogFileAndOpenNextOne) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- WHEN-TO-BACK-UP-CURRENT-LOG-FILE-OTHER-THAN-WHEN-CLOSING
   * @return the value of the WHEN-TO-BACK-UP-CURRENT-LOG-FILE-OTHER-THAN-WHEN-CLOSING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for WHEN-TO-BACK-UP-CURRENT-LOG-FILE-OTHER-THAN-WHEN-CLOSING is : 
   * (OR (MEMBER NEVER)
      (OR NoItem
          (Structure 
            AFTER-MESSAGES Integer
            AFTER-INTERVAL Integer)))
   *
   */
  public java.lang.Object getWhenToBackUpCurrentLogFileOtherThanWhenClosing() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- WHEN-TO-BACK-UP-CURRENT-LOG-FILE-OTHER-THAN-WHEN-CLOSING
   * @param whenToBackUpCurrentLogFileOtherThanWhenClosing new value to conclude for WHEN-TO-BACK-UP-CURRENT-LOG-FILE-OTHER-THAN-WHEN-CLOSING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setWhenToBackUpCurrentLogFileOtherThanWhenClosing(java.lang.Object whenToBackUpCurrentLogFileOtherThanWhenClosing) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-LOG-FILES
   * @return the value of the MAXIMUM-NUMBER-OF-LOG-FILES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MAXIMUM-NUMBER-OF-LOG-FILES is : 
   * (OR NoItem
      Integer)
   *
   */
  public java.lang.Integer getMaximumNumberOfLogFiles() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-LOG-FILES
   * @param maximumNumberOfLogFiles new value to conclude for MAXIMUM-NUMBER-OF-LOG-FILES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMaximumNumberOfLogFiles(java.lang.Integer maximumNumberOfLogFiles) throws G2AccessException;

}
