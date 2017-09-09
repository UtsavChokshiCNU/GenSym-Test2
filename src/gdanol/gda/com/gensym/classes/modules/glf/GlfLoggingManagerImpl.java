/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GlfLoggingManagerImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 13 11:45:52 EDT 2000
 *
 */


package com.gensym.classes.modules.glf;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class GlfLoggingManagerImpl extends com.gensym.classes.ObjectImpl implements GlfLoggingManager {


  static final long serialVersionUID = 2L;
  private static final Symbol GLF_LOGGING_ENABLED_ = Symbol.intern ("GLF-LOGGING-ENABLED");
  private static final Symbol GLF_LOG_DIRECTORY_ = Symbol.intern ("GLF-LOG-DIRECTORY");
  private static final Symbol GLF_LOG_FILE_NAME_TEMPLATE_ = Symbol.intern ("GLF-LOG-FILE-NAME-TEMPLATE");
  private static final Symbol GLF_LOG_FILE_NAME_GENERATOR_ = Symbol.intern ("GLF-LOG-FILE-NAME-GENERATOR");
  private static final Symbol GLF_CURRENT_LOG_FILE_ = Symbol.intern ("GLF-CURRENT-LOG-FILE");
  private static final Symbol GLF_FILE_HEADER_WRITER_ = Symbol.intern ("GLF-FILE-HEADER-WRITER");
  private static final Symbol GLF_TIME_INTERVAL_TO_OPEN_NEW_LOG_FILE_ = Symbol.intern ("GLF-TIME-INTERVAL-TO-OPEN-NEW-LOG-FILE");
  private static final Symbol GLF_MAXIMUM_FILE_SIZE_IN_BYTES_ = Symbol.intern ("GLF-MAXIMUM-FILE-SIZE-IN-BYTES");
  private static final Symbol GLF_LOG_FILE_SCHEDULER_ = Symbol.intern ("GLF-LOG-FILE-SCHEDULER");
  private static final Symbol GLF_AUTOMATICALLY_DELETE_EMPTY_LOG_FILES_ = Symbol.intern ("GLF-AUTOMATICALLY-DELETE-EMPTY-LOG-FILES");
  private static final Symbol _GLF_OPEN_TIME_ = Symbol.intern ("_GLF-OPEN-TIME");
  private static final Symbol _GLF_SCHEDULED_CLOSE_TIME_ = Symbol.intern ("_GLF-SCHEDULED-CLOSE-TIME");
  private static final Symbol _GLF_TIMES_TO_START_NEW_LOG_FILES_ = Symbol.intern ("_GLF-TIMES-TO-START-NEW-LOG-FILES");
  private static final Symbol _GLF_BASE_FILE_SIZE_ = Symbol.intern ("_GLF-BASE-FILE-SIZE");

  /* Generated constructors */

  public GlfLoggingManagerImpl() {
    super();
  }

  public GlfLoggingManagerImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- GLF-LOGGING-ENABLED
   * @param glfLoggingEnabled new value to conclude for GLF-LOGGING-ENABLED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfLoggingEnabled(boolean glfLoggingEnabled) throws G2AccessException {
    setAttributeValue (GLF_LOGGING_ENABLED_, new Boolean (glfLoggingEnabled));
  }

  /**
   * Generated Property Getter for attribute -- GLF-LOGGING-ENABLED
   * @return the value of the GLF-LOGGING-ENABLED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getGlfLoggingEnabled() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GLF_LOGGING_ENABLED_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- GLF-LOG-DIRECTORY
   * @param glfLogDirectory new value to conclude for GLF-LOG-DIRECTORY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfLogDirectory(java.lang.String glfLogDirectory) throws G2AccessException {
    setAttributeValue (GLF_LOG_DIRECTORY_, glfLogDirectory);
  }

  /**
   * Generated Property Getter for attribute -- GLF-LOG-DIRECTORY
   * @return the value of the GLF-LOG-DIRECTORY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String getGlfLogDirectory() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GLF_LOG_DIRECTORY_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GLF-LOG-FILE-NAME-TEMPLATE
   * @param glfLogFileNameTemplate new value to conclude for GLF-LOG-FILE-NAME-TEMPLATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfLogFileNameTemplate(java.lang.String glfLogFileNameTemplate) throws G2AccessException {
    setAttributeValue (GLF_LOG_FILE_NAME_TEMPLATE_, glfLogFileNameTemplate);
  }

  /**
   * Generated Property Getter for attribute -- GLF-LOG-FILE-NAME-TEMPLATE
   * @return the value of the GLF-LOG-FILE-NAME-TEMPLATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String getGlfLogFileNameTemplate() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GLF_LOG_FILE_NAME_TEMPLATE_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GLF-LOG-FILE-NAME-GENERATOR
   * @param glfLogFileNameGenerator new value to conclude for GLF-LOG-FILE-NAME-GENERATOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfLogFileNameGenerator(com.gensym.util.Symbol glfLogFileNameGenerator) throws G2AccessException {
    setAttributeValue (GLF_LOG_FILE_NAME_GENERATOR_, glfLogFileNameGenerator);
  }

  /**
   * Generated Property Getter for attribute -- GLF-LOG-FILE-NAME-GENERATOR
   * @return the value of the GLF-LOG-FILE-NAME-GENERATOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getGlfLogFileNameGenerator() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GLF_LOG_FILE_NAME_GENERATOR_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GLF-CURRENT-LOG-FILE
   * @param glfCurrentLogFile new value to conclude for GLF-CURRENT-LOG-FILE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfCurrentLogFile(java.lang.String glfCurrentLogFile) throws G2AccessException {
    setAttributeValue (GLF_CURRENT_LOG_FILE_, glfCurrentLogFile);
  }

  /**
   * Generated Property Getter for attribute -- GLF-CURRENT-LOG-FILE
   * @return the value of the GLF-CURRENT-LOG-FILE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String getGlfCurrentLogFile() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GLF_CURRENT_LOG_FILE_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GLF-FILE-HEADER-WRITER
   * @param glfFileHeaderWriter new value to conclude for GLF-FILE-HEADER-WRITER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfFileHeaderWriter(com.gensym.util.Symbol glfFileHeaderWriter) throws G2AccessException {
    setAttributeValue (GLF_FILE_HEADER_WRITER_, glfFileHeaderWriter);
  }

  /**
   * Generated Property Getter for attribute -- GLF-FILE-HEADER-WRITER
   * @return the value of the GLF-FILE-HEADER-WRITER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getGlfFileHeaderWriter() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GLF_FILE_HEADER_WRITER_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GLF-TIME-INTERVAL-TO-OPEN-NEW-LOG-FILE
   * @param glfTimeIntervalToOpenNewLogFile new value to conclude for GLF-TIME-INTERVAL-TO-OPEN-NEW-LOG-FILE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfTimeIntervalToOpenNewLogFile(int glfTimeIntervalToOpenNewLogFile) throws G2AccessException {
    setAttributeValue (GLF_TIME_INTERVAL_TO_OPEN_NEW_LOG_FILE_, new Integer (glfTimeIntervalToOpenNewLogFile));
  }

  /**
   * Generated Property Getter for attribute -- GLF-TIME-INTERVAL-TO-OPEN-NEW-LOG-FILE
   * @return the value of the GLF-TIME-INTERVAL-TO-OPEN-NEW-LOG-FILE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getGlfTimeIntervalToOpenNewLogFile() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GLF_TIME_INTERVAL_TO_OPEN_NEW_LOG_FILE_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- GLF-MAXIMUM-FILE-SIZE-IN-BYTES
   * @param glfMaximumFileSizeInBytes new value to conclude for GLF-MAXIMUM-FILE-SIZE-IN-BYTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfMaximumFileSizeInBytes(int glfMaximumFileSizeInBytes) throws G2AccessException {
    setAttributeValue (GLF_MAXIMUM_FILE_SIZE_IN_BYTES_, new Integer (glfMaximumFileSizeInBytes));
  }

  /**
   * Generated Property Getter for attribute -- GLF-MAXIMUM-FILE-SIZE-IN-BYTES
   * @return the value of the GLF-MAXIMUM-FILE-SIZE-IN-BYTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getGlfMaximumFileSizeInBytes() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GLF_MAXIMUM_FILE_SIZE_IN_BYTES_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- GLF-LOG-FILE-SCHEDULER
   * @param glfLogFileScheduler new value to conclude for GLF-LOG-FILE-SCHEDULER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfLogFileScheduler(com.gensym.util.Symbol glfLogFileScheduler) throws G2AccessException {
    setAttributeValue (GLF_LOG_FILE_SCHEDULER_, glfLogFileScheduler);
  }

  /**
   * Generated Property Getter for attribute -- GLF-LOG-FILE-SCHEDULER
   * @return the value of the GLF-LOG-FILE-SCHEDULER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getGlfLogFileScheduler() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GLF_LOG_FILE_SCHEDULER_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GLF-AUTOMATICALLY-DELETE-EMPTY-LOG-FILES
   * @param glfAutomaticallyDeleteEmptyLogFiles new value to conclude for GLF-AUTOMATICALLY-DELETE-EMPTY-LOG-FILES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfAutomaticallyDeleteEmptyLogFiles(boolean glfAutomaticallyDeleteEmptyLogFiles) throws G2AccessException {
    setAttributeValue (GLF_AUTOMATICALLY_DELETE_EMPTY_LOG_FILES_, new Boolean (glfAutomaticallyDeleteEmptyLogFiles));
  }

  /**
   * Generated Property Getter for attribute -- GLF-AUTOMATICALLY-DELETE-EMPTY-LOG-FILES
   * @return the value of the GLF-AUTOMATICALLY-DELETE-EMPTY-LOG-FILES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getGlfAutomaticallyDeleteEmptyLogFiles() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GLF_AUTOMATICALLY_DELETE_EMPTY_LOG_FILES_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- _GLF-OPEN-TIME
   * @param _glfOpenTime new value to conclude for _GLF-OPEN-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_glfOpenTime(int _glfOpenTime) throws G2AccessException {
    setAttributeValue (_GLF_OPEN_TIME_, new Integer (_glfOpenTime));
  }

  /**
   * Generated Property Getter for attribute -- _GLF-OPEN-TIME
   * @return the value of the _GLF-OPEN-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int get_glfOpenTime() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_GLF_OPEN_TIME_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- _GLF-SCHEDULED-CLOSE-TIME
   * @param _glfScheduledCloseTime new value to conclude for _GLF-SCHEDULED-CLOSE-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_glfScheduledCloseTime(int _glfScheduledCloseTime) throws G2AccessException {
    setAttributeValue (_GLF_SCHEDULED_CLOSE_TIME_, new Integer (_glfScheduledCloseTime));
  }

  /**
   * Generated Property Getter for attribute -- _GLF-SCHEDULED-CLOSE-TIME
   * @return the value of the _GLF-SCHEDULED-CLOSE-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int get_glfScheduledCloseTime() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_GLF_SCHEDULED_CLOSE_TIME_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- _GLF-TIMES-TO-START-NEW-LOG-FILES
   * @param _glfTimesToStartNewLogFiles new value to conclude for _GLF-TIMES-TO-START-NEW-LOG-FILES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_glfTimesToStartNewLogFiles(com.gensym.classes.IntegerArray _glfTimesToStartNewLogFiles) throws G2AccessException {
    setAttributeValue (_GLF_TIMES_TO_START_NEW_LOG_FILES_, _glfTimesToStartNewLogFiles);
  }

  /**
   * Generated Property Getter for attribute -- _GLF-TIMES-TO-START-NEW-LOG-FILES
   * @return the value of the _GLF-TIMES-TO-START-NEW-LOG-FILES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.classes.IntegerArray get_glfTimesToStartNewLogFiles() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_GLF_TIMES_TO_START_NEW_LOG_FILES_);
    return (com.gensym.classes.IntegerArray)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- _GLF-BASE-FILE-SIZE
   * @param _glfBaseFileSize new value to conclude for _GLF-BASE-FILE-SIZE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_glfBaseFileSize(int _glfBaseFileSize) throws G2AccessException {
    setAttributeValue (_GLF_BASE_FILE_SIZE_, new Integer (_glfBaseFileSize));
  }

  /**
   * Generated Property Getter for attribute -- _GLF-BASE-FILE-SIZE
   * @return the value of the _GLF-BASE-FILE-SIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int get_glfBaseFileSize() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_GLF_BASE_FILE_SIZE_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAuthorsForClass(com.gensym.util.Structure authors) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.AUTHORS_, authors);
  }

  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Structure getAuthorsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.AUTHORS_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String getChangeLogForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_LOG_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-NAME
   * @param className new value to conclude for CLASS-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setClassNameForClass(com.gensym.util.Symbol className) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.CLASS_NAME_, className);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-NAME
   * @return the value of the CLASS-NAME attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getClassNameForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @param classSpecificAttributes new value to conclude for CLASS-SPECIFIC-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setClassSpecificAttributesForClass(com.gensym.util.Sequence classSpecificAttributes) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_, classSpecificAttributes);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @return the value of the CLASS-SPECIFIC-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getClassSpecificAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CLASS-RESTRICTIONS
   * @return the value of the CLASS-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getClassRestrictionsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_RESTRICTIONS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- INSTANCE-CONFIGURATION
   * @param instanceConfiguration new value to conclude for INSTANCE-CONFIGURATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInstanceConfigurationForClass(com.gensym.util.Sequence instanceConfiguration) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.INSTANCE_CONFIGURATION_, instanceConfiguration);
  }

  /**
   * Generated Property Getter for attribute -- INSTANCE-CONFIGURATION
   * @return the value of the INSTANCE-CONFIGURATION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getInstanceConfigurationForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INSTANCE_CONFIGURATION_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CLASS-INHERITANCE-PATH
   * @return the value of the CLASS-INHERITANCE-PATH attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getClassInheritancePathForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_INHERITANCE_PATH_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INHERITED-ATTRIBUTES
   * @return the value of the INHERITED-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getInheritedAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INHERITED_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- SUPERIOR-CLASS
   * @return the value of the SUPERIOR-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getSuperiorClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.SUPERIOR_CLASS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CAPABILITIES-AND-RESTRICTIONS
   * @return the value of the CAPABILITIES-AND-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getCapabilitiesAndRestrictionsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CAPABILITIES_AND_RESTRICTIONS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTES-SPECIFIC-TO-CLASS
   * @return the value of the ATTRIBUTES-SPECIFIC-TO-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getAttributesSpecificToClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTES_SPECIFIC_TO_CLASS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- MENU-OPTION
   * @return the value of the MENU-OPTION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getMenuOptionForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.MENU_OPTION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @param directSuperiorClasses new value to conclude for DIRECT-SUPERIOR-CLASSES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDirectSuperiorClassesForClass(com.gensym.util.Sequence directSuperiorClasses) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_, directSuperiorClasses);
  }

  /**
   * Generated Property Getter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @return the value of the DIRECT-SUPERIOR-CLASSES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getDirectSuperiorClassesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE
   * @return the value of the CHANGE attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getChangeForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @param attributeInitializations new value to conclude for ATTRIBUTE-INITIALIZATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAttributeInitializationsForClass(com.gensym.util.Sequence attributeInitializations) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_, attributeInitializations);
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @return the value of the ATTRIBUTE-INITIALIZATIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getAttributeInitializationsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-DISPLAYS
   * @param attributeDisplays new value to conclude for ATTRIBUTE-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAttributeDisplaysForClass(java.lang.Object attributeDisplays) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_DISPLAYS_, attributeDisplays);
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-DISPLAYS
   * @return the value of the ATTRIBUTE-DISPLAYS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getAttributeDisplaysForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_DISPLAYS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- STUBS
   * @param stubs new value to conclude for STUBS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStubsForClass(java.lang.Object stubs) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.STUBS_, stubs);
  }

  /**
   * Generated Property Getter for attribute -- STUBS
   * @return the value of the STUBS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getStubsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.STUBS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-SETTINGS
   * @return the value of the DEFAULT-SETTINGS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getDefaultSettingsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.DEFAULT_SETTINGS_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
