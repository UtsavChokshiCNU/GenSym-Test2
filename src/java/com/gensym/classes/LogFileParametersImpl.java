/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      LogFileParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:00:40 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class LogFileParametersImpl extends com.gensym.classes.SystemTableImpl implements LogFileParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public LogFileParametersImpl() {
    super();
  }

  public LogFileParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public LogFileParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- LOG-FILE-ENABLED
   * @param logFileEnabled new value to conclude for LOG-FILE-ENABLED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setLogFileEnabled(boolean logFileEnabled) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.LOG_FILE_ENABLED_, new Boolean (logFileEnabled));
  }

  /**
   * Generated Property Getter for attribute -- LOG-FILE-ENABLED
   * @return the value of the LOG-FILE-ENABLED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getLogFileEnabled() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.LOG_FILE_ENABLED_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- DIRECTORY-FOR-LOG-FILES
   * @param directoryForLogFiles new value to conclude for DIRECTORY-FOR-LOG-FILES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDirectoryForLogFiles(java.lang.Object directoryForLogFiles) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DIRECTORY_FOR_LOG_FILES_, directoryForLogFiles);
  }

  /**
   * Generated Property Getter for attribute -- DIRECTORY-FOR-LOG-FILES
   * @return the value of the DIRECTORY-FOR-LOG-FILES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getDirectoryForLogFiles() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DIRECTORY_FOR_LOG_FILES_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ROOT-NAME-FOR-LOG-FILES
   * @param rootNameForLogFiles new value to conclude for ROOT-NAME-FOR-LOG-FILES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRootNameForLogFiles(java.lang.String rootNameForLogFiles) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ROOT_NAME_FOR_LOG_FILES_, rootNameForLogFiles);
  }

  /**
   * Generated Property Getter for attribute -- ROOT-NAME-FOR-LOG-FILES
   * @return the value of the ROOT-NAME-FOR-LOG-FILES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getRootNameForLogFiles() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ROOT_NAME_FOR_LOG_FILES_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CURRENT-LOG-FILE
   * @return the value of the CURRENT-LOG-FILE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getCurrentLogFile() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CURRENT_LOG_FILE_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- WHEN-TO-CLOSE-CURRENT-LOG-FILE-AND-OPEN-NEXT-ONE
   * @param whenToCloseCurrentLogFileAndOpenNextOne new value to conclude for WHEN-TO-CLOSE-CURRENT-LOG-FILE-AND-OPEN-NEXT-ONE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setWhenToCloseCurrentLogFileAndOpenNextOne(com.gensym.util.Structure whenToCloseCurrentLogFileAndOpenNextOne) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.WHEN_TO_CLOSE_CURRENT_LOG_FILE_AND_OPEN_NEXT_ONE_, whenToCloseCurrentLogFileAndOpenNextOne);
  }

  /**
   * Generated Property Getter for attribute -- WHEN-TO-CLOSE-CURRENT-LOG-FILE-AND-OPEN-NEXT-ONE
   * @return the value of the WHEN-TO-CLOSE-CURRENT-LOG-FILE-AND-OPEN-NEXT-ONE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getWhenToCloseCurrentLogFileAndOpenNextOne() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.WHEN_TO_CLOSE_CURRENT_LOG_FILE_AND_OPEN_NEXT_ONE_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- WHEN-TO-BACK-UP-CURRENT-LOG-FILE-OTHER-THAN-WHEN-CLOSING
   * @param whenToBackUpCurrentLogFileOtherThanWhenClosing new value to conclude for WHEN-TO-BACK-UP-CURRENT-LOG-FILE-OTHER-THAN-WHEN-CLOSING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setWhenToBackUpCurrentLogFileOtherThanWhenClosing(java.lang.Object whenToBackUpCurrentLogFileOtherThanWhenClosing) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.WHEN_TO_BACK_UP_CURRENT_LOG_FILE_OTHER_THAN_WHEN_CLOSING_, whenToBackUpCurrentLogFileOtherThanWhenClosing);
  }

  /**
   * Generated Property Getter for attribute -- WHEN-TO-BACK-UP-CURRENT-LOG-FILE-OTHER-THAN-WHEN-CLOSING
   * @return the value of the WHEN-TO-BACK-UP-CURRENT-LOG-FILE-OTHER-THAN-WHEN-CLOSING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getWhenToBackUpCurrentLogFileOtherThanWhenClosing() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.WHEN_TO_BACK_UP_CURRENT_LOG_FILE_OTHER_THAN_WHEN_CLOSING_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-LOG-FILES
   * @param maximumNumberOfLogFiles new value to conclude for MAXIMUM-NUMBER-OF-LOG-FILES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMaximumNumberOfLogFiles(java.lang.Integer maximumNumberOfLogFiles) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_LOG_FILES_, maximumNumberOfLogFiles);
  }

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-LOG-FILES
   * @return the value of the MAXIMUM-NUMBER-OF-LOG-FILES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Integer getMaximumNumberOfLogFiles() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_LOG_FILES_);
    return (java.lang.Integer)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
