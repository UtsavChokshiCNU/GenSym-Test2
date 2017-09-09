/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GlfLoggingManager.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Jun 26 13:41:42 EDT 2000
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

public interface GlfLoggingManager extends com.gensym.classes.Object {

  public static final Symbol GLF_LOGGING_MANAGER_ = Symbol.intern ("GLF-LOGGING-MANAGER");
  static final Symbol g2ClassName = GLF_LOGGING_MANAGER_;
  static final Symbol[] classInheritancePath = new Symbol[] {GLF_LOGGING_MANAGER_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};

  static final Symbol AUTHORS_ = Symbol.intern ("AUTHORS");
  static final Symbol CHANGE_LOG_ = Symbol.intern ("CHANGE-LOG");
  static final Symbol CLASS_NAME_ = Symbol.intern ("CLASS-NAME");
  static final Symbol CLASS_SPECIFIC_ATTRIBUTES_ = Symbol.intern ("CLASS-SPECIFIC-ATTRIBUTES");
  static final Symbol CLASS_RESTRICTIONS_ = Symbol.intern ("CLASS-RESTRICTIONS");
  static final Symbol INSTANCE_CONFIGURATION_ = Symbol.intern ("INSTANCE-CONFIGURATION");
  static final Symbol CLASS_INHERITANCE_PATH_ = Symbol.intern ("CLASS-INHERITANCE-PATH");
  static final Symbol INHERITED_ATTRIBUTES_ = Symbol.intern ("INHERITED-ATTRIBUTES");
  static final Symbol SUPERIOR_CLASS_ = Symbol.intern ("SUPERIOR-CLASS");
  static final Symbol CAPABILITIES_AND_RESTRICTIONS_ = Symbol.intern ("CAPABILITIES-AND-RESTRICTIONS");
  static final Symbol ATTRIBUTES_SPECIFIC_TO_CLASS_ = Symbol.intern ("ATTRIBUTES-SPECIFIC-TO-CLASS");
  static final Symbol MENU_OPTION_ = Symbol.intern ("MENU-OPTION");
  static final Symbol DIRECT_SUPERIOR_CLASSES_ = Symbol.intern ("DIRECT-SUPERIOR-CLASSES");
  static final Symbol CHANGE_ = Symbol.intern ("CHANGE");
  static final Symbol ATTRIBUTE_INITIALIZATIONS_ = Symbol.intern ("ATTRIBUTE-INITIALIZATIONS");
  static final Symbol ATTRIBUTE_DISPLAYS_ = Symbol.intern ("ATTRIBUTE-DISPLAYS");
  static final Symbol STUBS_ = Symbol.intern ("STUBS");
  static final Symbol DEFAULT_SETTINGS_ = Symbol.intern ("DEFAULT-SETTINGS");

  static final Symbol[] staticAttributes = new Symbol[] {AUTHORS_, CHANGE_LOG_, CLASS_NAME_, CLASS_SPECIFIC_ATTRIBUTES_, CLASS_RESTRICTIONS_, INSTANCE_CONFIGURATION_, CLASS_INHERITANCE_PATH_, INHERITED_ATTRIBUTES_, SUPERIOR_CLASS_, CAPABILITIES_AND_RESTRICTIONS_, ATTRIBUTES_SPECIFIC_TO_CLASS_, MENU_OPTION_, DIRECT_SUPERIOR_CLASSES_, CHANGE_, ATTRIBUTE_INITIALIZATIONS_, ATTRIBUTE_DISPLAYS_, STUBS_, DEFAULT_SETTINGS_};


  /**
   * Generated Property Getter for attribute -- GLF-LOGGING-ENABLED
   * @return the value of the GLF-LOGGING-ENABLED attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GLF-LOGGING-ENABLED is : 
   * BooleanTruthValue
   *
   */
  public boolean getGlfLoggingEnabled() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GLF-LOGGING-ENABLED
   * @param glfLoggingEnabled new value to conclude for GLF-LOGGING-ENABLED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfLoggingEnabled(boolean glfLoggingEnabled) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GLF-LOG-DIRECTORY
   * @return the value of the GLF-LOG-DIRECTORY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GLF-LOG-DIRECTORY is : 
   * Text
   *
   */
  public java.lang.String getGlfLogDirectory() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GLF-LOG-DIRECTORY
   * @param glfLogDirectory new value to conclude for GLF-LOG-DIRECTORY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfLogDirectory(java.lang.String glfLogDirectory) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GLF-LOG-FILE-NAME-TEMPLATE
   * @return the value of the GLF-LOG-FILE-NAME-TEMPLATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GLF-LOG-FILE-NAME-TEMPLATE is : 
   * Text
   *
   */
  public java.lang.String getGlfLogFileNameTemplate() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GLF-LOG-FILE-NAME-TEMPLATE
   * @param glfLogFileNameTemplate new value to conclude for GLF-LOG-FILE-NAME-TEMPLATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfLogFileNameTemplate(java.lang.String glfLogFileNameTemplate) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GLF-LOG-FILE-NAME-GENERATOR
   * @return the value of the GLF-LOG-FILE-NAME-GENERATOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GLF-LOG-FILE-NAME-GENERATOR is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getGlfLogFileNameGenerator() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GLF-LOG-FILE-NAME-GENERATOR
   * @param glfLogFileNameGenerator new value to conclude for GLF-LOG-FILE-NAME-GENERATOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfLogFileNameGenerator(com.gensym.util.Symbol glfLogFileNameGenerator) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GLF-CURRENT-LOG-FILE
   * @return the value of the GLF-CURRENT-LOG-FILE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GLF-CURRENT-LOG-FILE is : 
   * Text
   *
   */
  public java.lang.String getGlfCurrentLogFile() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GLF-CURRENT-LOG-FILE
   * @param glfCurrentLogFile new value to conclude for GLF-CURRENT-LOG-FILE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfCurrentLogFile(java.lang.String glfCurrentLogFile) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GLF-FILE-HEADER-WRITER
   * @return the value of the GLF-FILE-HEADER-WRITER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GLF-FILE-HEADER-WRITER is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getGlfFileHeaderWriter() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GLF-FILE-HEADER-WRITER
   * @param glfFileHeaderWriter new value to conclude for GLF-FILE-HEADER-WRITER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfFileHeaderWriter(com.gensym.util.Symbol glfFileHeaderWriter) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GLF-TIME-INTERVAL-TO-OPEN-NEW-LOG-FILE
   * @return the value of the GLF-TIME-INTERVAL-TO-OPEN-NEW-LOG-FILE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GLF-TIME-INTERVAL-TO-OPEN-NEW-LOG-FILE is : 
   * Integer
   *
   */
  public int getGlfTimeIntervalToOpenNewLogFile() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GLF-TIME-INTERVAL-TO-OPEN-NEW-LOG-FILE
   * @param glfTimeIntervalToOpenNewLogFile new value to conclude for GLF-TIME-INTERVAL-TO-OPEN-NEW-LOG-FILE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfTimeIntervalToOpenNewLogFile(int glfTimeIntervalToOpenNewLogFile) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GLF-MAXIMUM-FILE-SIZE-IN-BYTES
   * @return the value of the GLF-MAXIMUM-FILE-SIZE-IN-BYTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GLF-MAXIMUM-FILE-SIZE-IN-BYTES is : 
   * Integer
   *
   */
  public int getGlfMaximumFileSizeInBytes() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GLF-MAXIMUM-FILE-SIZE-IN-BYTES
   * @param glfMaximumFileSizeInBytes new value to conclude for GLF-MAXIMUM-FILE-SIZE-IN-BYTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfMaximumFileSizeInBytes(int glfMaximumFileSizeInBytes) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GLF-LOG-FILE-SCHEDULER
   * @return the value of the GLF-LOG-FILE-SCHEDULER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GLF-LOG-FILE-SCHEDULER is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getGlfLogFileScheduler() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GLF-LOG-FILE-SCHEDULER
   * @param glfLogFileScheduler new value to conclude for GLF-LOG-FILE-SCHEDULER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfLogFileScheduler(com.gensym.util.Symbol glfLogFileScheduler) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GLF-AUTOMATICALLY-DELETE-EMPTY-LOG-FILES
   * @return the value of the GLF-AUTOMATICALLY-DELETE-EMPTY-LOG-FILES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GLF-AUTOMATICALLY-DELETE-EMPTY-LOG-FILES is : 
   * BooleanTruthValue
   *
   */
  public boolean getGlfAutomaticallyDeleteEmptyLogFiles() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GLF-AUTOMATICALLY-DELETE-EMPTY-LOG-FILES
   * @param glfAutomaticallyDeleteEmptyLogFiles new value to conclude for GLF-AUTOMATICALLY-DELETE-EMPTY-LOG-FILES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGlfAutomaticallyDeleteEmptyLogFiles(boolean glfAutomaticallyDeleteEmptyLogFiles) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _GLF-OPEN-TIME
   * @return the value of the _GLF-OPEN-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _GLF-OPEN-TIME is : 
   * Integer
   *
   */
  public int get_glfOpenTime() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _GLF-OPEN-TIME
   * @param _glfOpenTime new value to conclude for _GLF-OPEN-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_glfOpenTime(int _glfOpenTime) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _GLF-SCHEDULED-CLOSE-TIME
   * @return the value of the _GLF-SCHEDULED-CLOSE-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _GLF-SCHEDULED-CLOSE-TIME is : 
   * Integer
   *
   */
  public int get_glfScheduledCloseTime() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _GLF-SCHEDULED-CLOSE-TIME
   * @param _glfScheduledCloseTime new value to conclude for _GLF-SCHEDULED-CLOSE-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_glfScheduledCloseTime(int _glfScheduledCloseTime) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _GLF-TIMES-TO-START-NEW-LOG-FILES
   * @return the value of the _GLF-TIMES-TO-START-NEW-LOG-FILES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _GLF-TIMES-TO-START-NEW-LOG-FILES is : 
   * (Class INTEGER-ARRAY)
   *
   */
  public com.gensym.classes.IntegerArray get_glfTimesToStartNewLogFiles() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _GLF-TIMES-TO-START-NEW-LOG-FILES
   * @param _glfTimesToStartNewLogFiles new value to conclude for _GLF-TIMES-TO-START-NEW-LOG-FILES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_glfTimesToStartNewLogFiles(com.gensym.classes.IntegerArray _glfTimesToStartNewLogFiles) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _GLF-BASE-FILE-SIZE
   * @return the value of the _GLF-BASE-FILE-SIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _GLF-BASE-FILE-SIZE is : 
   * Integer
   *
   */
  public int get_glfBaseFileSize() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _GLF-BASE-FILE-SIZE
   * @param _glfBaseFileSize new value to conclude for _GLF-BASE-FILE-SIZE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_glfBaseFileSize(int _glfBaseFileSize) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for AUTHORS is : 
   * (OR NoItem
      (Structure 
        TIMESTAMP
          (Structure 
            YEAR Integer
            MONTH Integer
            DATE Integer
            HOURS Integer
            MINUTES Integer)
        AUTHORS
          (Sequence Symbol 1)))
   *
   */
  public com.gensym.util.Structure getAuthorsForClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAuthorsForClass(com.gensym.util.Structure authors) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CHANGE-LOG is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getChangeLogForClass() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CLASS-NAME
   * @return the value of the CLASS-NAME attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CLASS-NAME is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getClassNameForClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CLASS-NAME
   * @param className new value to conclude for CLASS-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setClassNameForClass(com.gensym.util.Symbol className) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @return the value of the CLASS-SPECIFIC-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CLASS-SPECIFIC-ATTRIBUTES is : 
   * (OR NoItem
      (Sequence 
        (Structure 
          ATTRIBUTE-NAME Symbol
          ATTRIBUTE-TYPE-SPECIFICATION Symbol
          ATTRIBUTE-INITIAL-VALUE Value
          ATTRIBUTE-INITIAL-ITEM-CLASS Symbol
          ATTRIBUTE-RANGE
            (Sequence Symbol 1)
          ATTRIBUTE-IS-INDEXED BooleanTruthValue)
        1)))
   *
   */
  public com.gensym.util.Sequence getClassSpecificAttributesForClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @param classSpecificAttributes new value to conclude for CLASS-SPECIFIC-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setClassSpecificAttributesForClass(com.gensym.util.Sequence classSpecificAttributes) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CLASS-RESTRICTIONS
   * @return the value of the CLASS-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Attribute CLASS-RESTRICTIONS has no type
   *
   */
  public java.lang.Object getClassRestrictionsForClass() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INSTANCE-CONFIGURATION
   * @return the value of the INSTANCE-CONFIGURATION attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INSTANCE-CONFIGURATION is : 
   * (OR NoItem
      (Sequence 
        (Structure 
          TYPE
            (MEMBER CONFIGURE-USER-INTERFACE RESTRICT-PROPRIETARY-ITEMS SET-UP-NETWORK-ACCESS 
                    DECLARE-PROPERTIES COMMENT)
          CLAUSES
            (OR (Sequence 
                  (Structure 
                    APPLICABLE-USER-MODES
                      (Structure 
                        NEGATIVE BooleanTruthValue
                        MODES
                          (Sequence Symbol 1))
                    STATEMENTS
                      (Sequence 
                        (OR (Structure 
                              OPERATION-TYPE
                                (MEMBER WORKSPACE-MENU ITEM-MENU NON-MENU)
                              RESTRICTION-TYPE
                                (MEMBER INCLUDE INCLUDE-ADDITIONALLY EXCLUDE EXCLUDE-ADDITIONALLY 
                                        EXCLUDE-ABSOLUTELY)
                              MENU-CHOICES
                                (Sequence Symbol 0)
                              APPLICABLE-ITEMS
                                (Sequence Symbol 1))
                            (Structure 
                              OPERATION-TYPE
                                (MEMBER TABLE-MENU)
                              RESTRICTION-TYPE
                                (MEMBER INCLUDE INCLUDE-ADDITIONALLY EXCLUDE EXCLUDE-ADDITIONALLY 
                                        EXCLUDE-ABSOLUTELY)
                              MENU-CHOICES
                                (Sequence 
                                  (MEMBER SUBTABLE DELETE-SUBTABLE CHANGE-TO-NO CHANGE-TO-YES 
                                          ADD-OPTIONAL-SUBTABLE TABLE CHOOSE-EXISTING-CLASS EDIT 
                                          EDIT-ICON TRANSFER MOVE CLONE SHOW-ATTRIBUTE-DISPLAY 
                                          ADD-ANOTHER-ATTRIBUTE DELETE-ATTRIBUTE 
                                          ADD-NAME-OF-ATTRIBUTE DELETE-NAME-OF-ATTRIBUTE 
                                          HIDE-ATTRIBUTE-DISPLAY CHANGE-SIZE ENABLE DISABLE 
                                          GO-TO-ORIGINAL DELETE-ORIGINAL TRANSFER-ORIGINAL 
                                          DESCRIBE-CONFIGURATION DESCRIBE VIEW-CHANGE-LOG SHOW-TEXT 
                                          SHOW-SUMMARY-OF-TEXT ADD-SUBTABLE SUBTABLES 
                                          DYNAMIC-BACKWARD-CHAINING DESCRIBE-CHAINING 
                                          DYNAMIC-GENERIC-RULE-DISPLAY HIDE DELETE HIDE-TABLE 
                                          MARK-TO-STRIP-TEXT MARK-TO-STRIP-TEXT-* 
                                          REMOVE-STRIP-TEXT-MARK REMOVE-STRIP-TEXT-MARK-* 
                                          MARK-NOT-TO-STRIP-TEXT-* MARK-NOT-TO-STRIP-TEXT 
                                          REMOVE-DO-NOT-STRIP-TEXT-MARK-* 
                                          REMOVE-DO-NOT-STRIP-TEXT-MARK)
                                  0))
                              APPLICABLE-ATTRIBUTES
                                (Sequence Symbol 0)
                              APPLICABLE-ITEMS
                                (Sequence Symbol 1))
                            (Structure 
                              OPERATION-TYPE
                                (MEMBER ATTRIBUTE-VISIBILITY)
                              RESTRICTION-TYPE
                                (MEMBER INCLUDE INCLUDE-ADDITIONALLY EXCLUDE EXCLUDE-ADDITIONALLY 
                                        EXCLUDE-ABSOLUTELY)
                              ATTRIBUTES
                                (Sequence Symbol 1)
                              APPLICABLE-ITEMS
                                (Sequence Symbol 1))
                            (Structure 
                              OPERATION-TYPE
                                (MEMBER PRESSING RELEASING)
                              KEY-CODE
                                (Structure 
                                  MODIFIERS Integer
                                  MOUSE-BUTTON
                                    (MEMBER ANY))
                              CONSEQUENT-ACTION
                                (OR (OR (MEMBER LIFT-TO-TOP DROP-TO-BOTTOM GO-TO-REFERENCED-ITEM 
                                                CLONE-AS-TREND-CHART TABLE EDIT TRANSFER MOVE CLONE 
                                                CHANGE-MIN-SIZE ALIGN-TEXT COLOR DELETE 
                                                GO-TO-MESSAGE-ORIGIN ENABLE DISABLE DESCRIBE 
                                                VIEW-CHANGE-LOG DYNAMIC-RULE-INVOCATION-DISPLAY 
                                                DESCRIBE-CONFIGURATION MARK-TO-STRIP-TEXT 
                                                MARK-TO-STRIP-TEXT-* REMOVE-STRIP-TEXT-MARK 
                                                REMOVE-STRIP-TEXT-MARK-* MARK-NOT-TO-STRIP-TEXT-* 
                                                MARK-NOT-TO-STRIP-TEXT 
                                                REMOVE-DO-NOT-STRIP-TEXT-MARK-* 
                                                REMOVE-DO-NOT-STRIP-TEXT-MARK GO-TO-SUBWORKSPACE 
                                                CREATE-INSTANCE EDIT-ICON TABLE-OF-VALUES NAME 
                                                ROTATE-REFLECT CHANGE-SIZE DYNAMIC-BACKWARD-CHAINING 
                                                DESCRIBE-CHAINING DYNAMIC-GENERIC-RULE-DISPLAY 
                                                CREATE-SUBWORKSPACE EDIT-CELL-EXPRESSION 
                                                EDIT-CELL-FORMAT OTHER-EDITS ADD-ROW ADD-COLUMN 
                                                DELETE-ROW DELETE-COLUMN HIDE-NAME)
                                        Symbol)
                                    (Structure 
                                      MOUSE-TRACKING-PROCEDURE-NAME Symbol
                                      MOUSE-TRACKING-APPLICABLE-ITEMS
                                        (Sequence Symbol 1)
                                      MOUSE-MOTION-TRACKING? BooleanTruthValue))
                              APPLICABLE-ITEMS
                                (Sequence Symbol 1))
                            (Structure 
                              OPERATION-TYPE
                                (MEMBER TYPING)
                              KEY-CODE
                                (Structure 
                                  MODIFIERS Integer
                                  KEYBOARD-SYMBOL
                                    (MEMBER F1 F2 F3 F4 F5 F6 BACKSPACE TAB LINEFEED RETURN ESCAPE 
                                            0 1 2 3 4 5 6 7 8 9 : ; < = > ? A B C D E F G H I J K L 
                                            M N O P Q R S T U V W X Y Z [ ] ^ _ ` { | } SPACE ! " # 
                                            $ % & ' ( ) * + , - . / DELETE BREAK ENTER HELP INSERT 
                                            REDO MENU FIND HOME BEGIN END PAUSE SELECT PRINT EXECUTE 
                                            ABORT CLEAR-SCREEN UP-ARROW DOWN-ARROW LEFT-ARROW 
                                            RIGHT-ARROW PREVIOUS-SCREEN NEXT-SCREEN))
                              CONSEQUENT-ACTION
                                (OR (OR (MEMBER LIFT-TO-TOP DROP-TO-BOTTOM GO-TO-REFERENCED-ITEM 
                                                CLONE-AS-TREND-CHART TABLE EDIT TRANSFER MOVE CLONE 
                                                CHANGE-MIN-SIZE ALIGN-TEXT COLOR DELETE 
                                                GO-TO-MESSAGE-ORIGIN ENABLE DISABLE DESCRIBE 
                                                VIEW-CHANGE-LOG DYNAMIC-RULE-INVOCATION-DISPLAY 
                                                DESCRIBE-CONFIGURATION MARK-TO-STRIP-TEXT 
                                                MARK-TO-STRIP-TEXT-* REMOVE-STRIP-TEXT-MARK 
                                                REMOVE-STRIP-TEXT-MARK-* MARK-NOT-TO-STRIP-TEXT-* 
                                                MARK-NOT-TO-STRIP-TEXT 
                                                REMOVE-DO-NOT-STRIP-TEXT-MARK-* 
                                                REMOVE-DO-NOT-STRIP-TEXT-MARK GO-TO-SUBWORKSPACE 
                                                CREATE-INSTANCE EDIT-ICON TABLE-OF-VALUES NAME 
                                                ROTATE-REFLECT CHANGE-SIZE DYNAMIC-BACKWARD-CHAINING 
                                                DESCRIBE-CHAINING DYNAMIC-GENERIC-RULE-DISPLAY 
                                                CREATE-SUBWORKSPACE EDIT-CELL-EXPRESSION 
                                                EDIT-CELL-FORMAT OTHER-EDITS ADD-ROW ADD-COLUMN 
                                                DELETE-ROW DELETE-COLUMN HIDE-NAME)
                                        Symbol)
                                    (Structure 
                                      MOUSE-TRACKING-PROCEDURE-NAME Symbol
                                      MOUSE-TRACKING-APPLICABLE-ITEMS
                                        (Sequence Symbol 1)
                                      MOUSE-MOTION-TRACKING? BooleanTruthValue))
                              APPLICABLE-ITEMS
                                (Sequence Symbol 1))
                            (Structure 
                              OPERATION-TYPE
                                (MEMBER SELECTING SELECTING-ABSOLUTELY)
                              CONSEQUENT-ACTION
                                (OR (OR (MEMBER LIFT-TO-TOP DROP-TO-BOTTOM GO-TO-REFERENCED-ITEM 
                                                CLONE-AS-TREND-CHART TABLE EDIT TRANSFER MOVE CLONE 
                                                CHANGE-MIN-SIZE ALIGN-TEXT COLOR DELETE 
                                                GO-TO-MESSAGE-ORIGIN ENABLE DISABLE DESCRIBE 
                                                VIEW-CHANGE-LOG DYNAMIC-RULE-INVOCATION-DISPLAY 
                                                DESCRIBE-CONFIGURATION MARK-TO-STRIP-TEXT 
                                                MARK-TO-STRIP-TEXT-* REMOVE-STRIP-TEXT-MARK 
                                                REMOVE-STRIP-TEXT-MARK-* MARK-NOT-TO-STRIP-TEXT-* 
                                                MARK-NOT-TO-STRIP-TEXT 
                                                REMOVE-DO-NOT-STRIP-TEXT-MARK-* 
                                                REMOVE-DO-NOT-STRIP-TEXT-MARK GO-TO-SUBWORKSPACE 
                                                CREATE-INSTANCE EDIT-ICON TABLE-OF-VALUES NAME 
                                                ROTATE-REFLECT CHANGE-SIZE DYNAMIC-BACKWARD-CHAINING 
                                                DESCRIBE-CHAINING DYNAMIC-GENERIC-RULE-DISPLAY 
                                                CREATE-SUBWORKSPACE EDIT-CELL-EXPRESSION 
                                                EDIT-CELL-FORMAT OTHER-EDITS ADD-ROW ADD-COLUMN 
                                                DELETE-ROW DELETE-COLUMN HIDE-NAME)
                                        Symbol)
                                    (Structure 
                                      MOUSE-TRACKING-PROCEDURE-NAME Symbol
                                      MOUSE-TRACKING-APPLICABLE-ITEMS
                                        (Sequence Symbol 1)
                                      MOUSE-MOTION-TRACKING? BooleanTruthValue))
                              APPLICABLE-ITEMS
                                (Sequence Symbol 1))
                            (Structure 
                              OPERATION-TYPE
                                (MEMBER MOVING)
                              TYPE-OF-REGION
                                (MEMBER RECTANGLE GRID)
                              CONSTRAINED-REGION
                                (OR (Structure 
                                      LEFT-EDGE Integer
                                      RIGHT-EDGE Integer
                                      TOP-EDGE Integer
                                      BOTTOM-EDGE Integer)
                                    (Structure 
                                      X-GRID-LENGTH Integer
                                      Y-GRID-LENGTH Integer))
                              APPLICABLE-ITEMS
                                (Sequence Symbol 1)))
                        1)))
                  1))
                (Sequence 
                  (OR (Structure 
                        OPERATION-TYPE
                          (MEMBER WORKSPACE-MENU ITEM-MENU NON-MENU)
                        RESTRICTION-TYPE
                          (MEMBER INCLUDE INCLUDE-ADDITIONALLY EXCLUDE EXCLUDE-ADDITIONALLY 
                                  EXCLUDE-ABSOLUTELY)
                        MENU-CHOICES
                          (Sequence Symbol 0)
                        APPLICABLE-ITEMS
                          (Sequence Symbol 1))
                      (Structure 
                        OPERATION-TYPE
                          (MEMBER TABLE-MENU)
                        RESTRICTION-TYPE
                          (MEMBER INCLUDE INCLUDE-ADDITIONALLY EXCLUDE EXCLUDE-ADDITIONALLY 
                                  EXCLUDE-ABSOLUTELY)
                        MENU-CHOICES
                          (Sequence 
                            (MEMBER SUBTABLE DELETE-SUBTABLE CHANGE-TO-NO CHANGE-TO-YES 
                                    ADD-OPTIONAL-SUBTABLE TABLE CHOOSE-EXISTING-CLASS EDIT EDIT-ICON 
                                    TRANSFER MOVE CLONE SHOW-ATTRIBUTE-DISPLAY ADD-ANOTHER-ATTRIBUTE 
                                    DELETE-ATTRIBUTE ADD-NAME-OF-ATTRIBUTE DELETE-NAME-OF-ATTRIBUTE 
                                    HIDE-ATTRIBUTE-DISPLAY CHANGE-SIZE ENABLE DISABLE GO-TO-ORIGINAL 
                                    DELETE-ORIGINAL TRANSFER-ORIGINAL DESCRIBE-CONFIGURATION 
                                    DESCRIBE VIEW-CHANGE-LOG SHOW-TEXT SHOW-SUMMARY-OF-TEXT 
                                    ADD-SUBTABLE SUBTABLES DYNAMIC-BACKWARD-CHAINING 
                                    DESCRIBE-CHAINING DYNAMIC-GENERIC-RULE-DISPLAY HIDE DELETE 
                                    HIDE-TABLE MARK-TO-STRIP-TEXT MARK-TO-STRIP-TEXT-* 
                                    REMOVE-STRIP-TEXT-MARK REMOVE-STRIP-TEXT-MARK-* 
                                    MARK-NOT-TO-STRIP-TEXT-* MARK-NOT-TO-STRIP-TEXT 
                                    REMOVE-DO-NOT-STRIP-TEXT-MARK-* REMOVE-DO-NOT-STRIP-TEXT-MARK)
                            0))
                        APPLICABLE-ATTRIBUTES
                          (Sequence Symbol 0)
                        APPLICABLE-ITEMS
                          (Sequence Symbol 1))
                      (Structure 
                        OPERATION-TYPE
                          (MEMBER ATTRIBUTE-VISIBILITY)
                        RESTRICTION-TYPE
                          (MEMBER INCLUDE INCLUDE-ADDITIONALLY EXCLUDE EXCLUDE-ADDITIONALLY 
                                  EXCLUDE-ABSOLUTELY)
                        ATTRIBUTES
                          (Sequence Symbol 1)
                        APPLICABLE-ITEMS
                          (Sequence Symbol 1))
                      (Structure 
                        OPERATION-TYPE
                          (MEMBER PRESSING RELEASING)
                        KEY-CODE
                          (Structure 
                            MODIFIERS Integer
                            MOUSE-BUTTON
                              (MEMBER ANY))
                        CONSEQUENT-ACTION
                          (OR (OR (MEMBER LIFT-TO-TOP DROP-TO-BOTTOM GO-TO-REFERENCED-ITEM 
                                          CLONE-AS-TREND-CHART TABLE EDIT TRANSFER MOVE CLONE 
                                          CHANGE-MIN-SIZE ALIGN-TEXT COLOR DELETE 
                                          GO-TO-MESSAGE-ORIGIN ENABLE DISABLE DESCRIBE 
                                          VIEW-CHANGE-LOG DYNAMIC-RULE-INVOCATION-DISPLAY 
                                          DESCRIBE-CONFIGURATION MARK-TO-STRIP-TEXT 
                                          MARK-TO-STRIP-TEXT-* REMOVE-STRIP-TEXT-MARK 
                                          REMOVE-STRIP-TEXT-MARK-* MARK-NOT-TO-STRIP-TEXT-* 
                                          MARK-NOT-TO-STRIP-TEXT REMOVE-DO-NOT-STRIP-TEXT-MARK-* 
                                          REMOVE-DO-NOT-STRIP-TEXT-MARK GO-TO-SUBWORKSPACE 
                                          CREATE-INSTANCE EDIT-ICON TABLE-OF-VALUES NAME 
                                          ROTATE-REFLECT CHANGE-SIZE DYNAMIC-BACKWARD-CHAINING 
                                          DESCRIBE-CHAINING DYNAMIC-GENERIC-RULE-DISPLAY 
                                          CREATE-SUBWORKSPACE EDIT-CELL-EXPRESSION EDIT-CELL-FORMAT 
                                          OTHER-EDITS ADD-ROW ADD-COLUMN DELETE-ROW DELETE-COLUMN 
                                          HIDE-NAME)
                                  Symbol)
                              (Structure 
                                MOUSE-TRACKING-PROCEDURE-NAME Symbol
                                MOUSE-TRACKING-APPLICABLE-ITEMS
                                  (Sequence Symbol 1)
                                MOUSE-MOTION-TRACKING? BooleanTruthValue))
                        APPLICABLE-ITEMS
                          (Sequence Symbol 1))
                      (Structure 
                        OPERATION-TYPE
                          (MEMBER TYPING)
                        KEY-CODE
                          (Structure 
                            MODIFIERS Integer
                            KEYBOARD-SYMBOL
                              (MEMBER F1 F2 F3 F4 F5 F6 BACKSPACE TAB LINEFEED RETURN ESCAPE 0 1 2 
                                      3 4 5 6 7 8 9 : ; < = > ? A B C D E F G H I J K L M N O P Q R 
                                      S T U V W X Y Z [ ] ^ _ ` { | } SPACE ! " # $ % & ' ( ) * + , 
                                      - . / DELETE BREAK ENTER HELP INSERT REDO MENU FIND HOME BEGIN 
                                      END PAUSE SELECT PRINT EXECUTE ABORT CLEAR-SCREEN UP-ARROW 
                                      DOWN-ARROW LEFT-ARROW RIGHT-ARROW PREVIOUS-SCREEN NEXT-SCREEN))
                        CONSEQUENT-ACTION
                          (OR (OR (MEMBER LIFT-TO-TOP DROP-TO-BOTTOM GO-TO-REFERENCED-ITEM 
                                          CLONE-AS-TREND-CHART TABLE EDIT TRANSFER MOVE CLONE 
                                          CHANGE-MIN-SIZE ALIGN-TEXT COLOR DELETE 
                                          GO-TO-MESSAGE-ORIGIN ENABLE DISABLE DESCRIBE 
                                          VIEW-CHANGE-LOG DYNAMIC-RULE-INVOCATION-DISPLAY 
                                          DESCRIBE-CONFIGURATION MARK-TO-STRIP-TEXT 
                                          MARK-TO-STRIP-TEXT-* REMOVE-STRIP-TEXT-MARK 
                                          REMOVE-STRIP-TEXT-MARK-* MARK-NOT-TO-STRIP-TEXT-* 
                                          MARK-NOT-TO-STRIP-TEXT REMOVE-DO-NOT-STRIP-TEXT-MARK-* 
                                          REMOVE-DO-NOT-STRIP-TEXT-MARK GO-TO-SUBWORKSPACE 
                                          CREATE-INSTANCE EDIT-ICON TABLE-OF-VALUES NAME 
                                          ROTATE-REFLECT CHANGE-SIZE DYNAMIC-BACKWARD-CHAINING 
                                          DESCRIBE-CHAINING DYNAMIC-GENERIC-RULE-DISPLAY 
                                          CREATE-SUBWORKSPACE EDIT-CELL-EXPRESSION EDIT-CELL-FORMAT 
                                          OTHER-EDITS ADD-ROW ADD-COLUMN DELETE-ROW DELETE-COLUMN 
                                          HIDE-NAME)
                                  Symbol)
                              (Structure 
                                MOUSE-TRACKING-PROCEDURE-NAME Symbol
                                MOUSE-TRACKING-APPLICABLE-ITEMS
                                  (Sequence Symbol 1)
                                MOUSE-MOTION-TRACKING? BooleanTruthValue))
                        APPLICABLE-ITEMS
                          (Sequence Symbol 1))
                      (Structure 
                        OPERATION-TYPE
                          (MEMBER SELECTING SELECTING-ABSOLUTELY)
                        CONSEQUENT-ACTION
                          (OR (OR (MEMBER LIFT-TO-TOP DROP-TO-BOTTOM GO-TO-REFERENCED-ITEM 
                                          CLONE-AS-TREND-CHART TABLE EDIT TRANSFER MOVE CLONE 
                                          CHANGE-MIN-SIZE ALIGN-TEXT COLOR DELETE 
                                          GO-TO-MESSAGE-ORIGIN ENABLE DISABLE DESCRIBE 
                                          VIEW-CHANGE-LOG DYNAMIC-RULE-INVOCATION-DISPLAY 
                                          DESCRIBE-CONFIGURATION MARK-TO-STRIP-TEXT 
                                          MARK-TO-STRIP-TEXT-* REMOVE-STRIP-TEXT-MARK 
                                          REMOVE-STRIP-TEXT-MARK-* MARK-NOT-TO-STRIP-TEXT-* 
                                          MARK-NOT-TO-STRIP-TEXT REMOVE-DO-NOT-STRIP-TEXT-MARK-* 
                                          REMOVE-DO-NOT-STRIP-TEXT-MARK GO-TO-SUBWORKSPACE 
                                          CREATE-INSTANCE EDIT-ICON TABLE-OF-VALUES NAME 
                                          ROTATE-REFLECT CHANGE-SIZE DYNAMIC-BACKWARD-CHAINING 
                                          DESCRIBE-CHAINING DYNAMIC-GENERIC-RULE-DISPLAY 
                                          CREATE-SUBWORKSPACE EDIT-CELL-EXPRESSION EDIT-CELL-FORMAT 
                                          OTHER-EDITS ADD-ROW ADD-COLUMN DELETE-ROW DELETE-COLUMN 
                                          HIDE-NAME)
                                  Symbol)
                              (Structure 
                                MOUSE-TRACKING-PROCEDURE-NAME Symbol
                                MOUSE-TRACKING-APPLICABLE-ITEMS
                                  (Sequence Symbol 1)
                                MOUSE-MOTION-TRACKING? BooleanTruthValue))
                        APPLICABLE-ITEMS
                          (Sequence Symbol 1))
                      (Structure 
                        OPERATION-TYPE
                          (MEMBER MOVING)
                        TYPE-OF-REGION
                          (MEMBER RECTANGLE GRID)
                        CONSTRAINED-REGION
                          (OR (Structure 
                                LEFT-EDGE Integer
                                RIGHT-EDGE Integer
                                TOP-EDGE Integer
                                BOTTOM-EDGE Integer)
                              (Structure 
                                X-GRID-LENGTH Integer
                                Y-GRID-LENGTH Integer))
                        APPLICABLE-ITEMS
                          (Sequence Symbol 1)))
                  1))
                (Sequence 
                  (Structure 
                    RESTRICTION-TYPE
                      (MEMBER ALLOW PROHIBIT PROHIBIT-ABSOLUTELY)
                    ACCESS-TYPES
                      (Sequence 
                        (MEMBER EXECUTE INFORM READ WRITE)
                        1))
                    ACCESS-AGENT
                      (MEMBER ANY G2 GSI G2-AND-GSI)
                    APPLICABLE-ITEMS
                      (Sequence Symbol 1))
                  1))
                (Structure 
                  DECLARED-PROPERTIES
                    (Structure 
                      INDEPENDENT-FOR-ALL-COMPILATIONS BooleanTruthValue
                      STABLE-FOR-DEPENDENT-COMPILATIONS BooleanTruthValue
                      STABLE-HIERARCHY BooleanTruthValue
                      MANUAL-CONNECTIONS BooleanTruthValue
                      OPTIMIZABLE BooleanTruthValue
                      INLINEABLE BooleanTruthValue
                      ACTIVATABLE-SUBWORKSPACE BooleanTruthValue
                      EXTERNAL-SIMULATION BooleanTruthValue
                      SUBWORKSPACE-CONNECTION-POSTS BooleanTruthValue)
                  APPLICABLE-ITEMS
                    (Sequence Symbol 1))
                (Sequence 
                  (Structure 
                    TAG-NAME Symbol
                    ASSOCIATED-TEXT Text)
                  1))))
        1)))
   *
   */
  public com.gensym.util.Sequence getInstanceConfigurationForClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INSTANCE-CONFIGURATION
   * @param instanceConfiguration new value to conclude for INSTANCE-CONFIGURATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInstanceConfigurationForClass(com.gensym.util.Sequence instanceConfiguration) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CLASS-INHERITANCE-PATH
   * @return the value of the CLASS-INHERITANCE-PATH attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CLASS-INHERITANCE-PATH is : 
   * (OR NoItem
      (Sequence Symbol 1))
   *
   */
  public com.gensym.util.Sequence getClassInheritancePathForClass() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INHERITED-ATTRIBUTES
   * @return the value of the INHERITED-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INHERITED-ATTRIBUTES is : 
   * (OR NoItem
      (Sequence 
        (Structure 
          ATTRIBUTE-NAME Symbol
          ATTRIBUTE-TYPE-SPECIFICATION Symbol
          ATTRIBUTE-INITIAL-VALUE Value
          ATTRIBUTE-INITIAL-ITEM-CLASS Symbol
          ATTRIBUTE-INITIAL-TYPE Symbol
          ATTRIBUTE-RANGE
            (Sequence Symbol 1)
          ATTRIBUTE-IS-INDEXED BooleanTruthValue)
        1)))
   *
   */
  public com.gensym.util.Sequence getInheritedAttributesForClass() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SUPERIOR-CLASS
   * @return the value of the SUPERIOR-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Attribute SUPERIOR-CLASS has no type
   *
   */
  public java.lang.Object getSuperiorClassForClass() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CAPABILITIES-AND-RESTRICTIONS
   * @return the value of the CAPABILITIES-AND-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Attribute CAPABILITIES-AND-RESTRICTIONS has no type
   *
   */
  public java.lang.Object getCapabilitiesAndRestrictionsForClass() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ATTRIBUTES-SPECIFIC-TO-CLASS
   * @return the value of the ATTRIBUTES-SPECIFIC-TO-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Attribute ATTRIBUTES-SPECIFIC-TO-CLASS has no type
   *
   */
  public java.lang.Object getAttributesSpecificToClassForClass() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MENU-OPTION
   * @return the value of the MENU-OPTION attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Attribute MENU-OPTION has no type
   *
   */
  public java.lang.Object getMenuOptionForClass() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @return the value of the DIRECT-SUPERIOR-CLASSES attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DIRECT-SUPERIOR-CLASSES is : 
   * (OR NoItem
      (Sequence Symbol 1))
   *
   */
  public com.gensym.util.Sequence getDirectSuperiorClassesForClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @param directSuperiorClasses new value to conclude for DIRECT-SUPERIOR-CLASSES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDirectSuperiorClassesForClass(com.gensym.util.Sequence directSuperiorClasses) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CHANGE
   * @return the value of the CHANGE attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Attribute CHANGE has no type
   *
   */
  public java.lang.Object getChangeForClass() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @return the value of the ATTRIBUTE-INITIALIZATIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ATTRIBUTE-INITIALIZATIONS is : 
   * (OR NoItem
      (Sequence 
        (OR (Structure 
              USER-ATTRIBUTE-NAME Symbol
              INITIALIZATION
                (Structure 
                  INITIAL-VALUE Value
                  INITIAL-ITEM-CLASS Symbol
                  INITIAL-TYPE Symbol))
            (Structure 
              SYSTEM-ATTRIBUTE-DESIGNATION Symbol
              INITIALIZATION
                (OR (OR NoItem
                        (Sequence ItemOrValue 1))
                    (Sequence Value 1)
                    (OR NoItem
                        (Sequence (Class ITEM) 1))
                    (Sequence Quantity 1)
                    (Sequence Integer 1)
                    (Sequence Float 1)
                    (Sequence Symbol 1)
                    (Sequence Text 1)
                    (Sequence BooleanTruthValue 1)
                    Integer
                    BooleanTruthValue
                    (OR NoItem
                        Quantity)
                    (OR NoItem
                        Float)
                    (OR NoItem
                        Integer)
                    (OR NoItem
                        Symbol)
                    (OR NoItem
                        Text)
                    (OR Quantity
                        NoItem)
                    (Structure 
                      FORWARD-CHAIN BooleanTruthValue
                      BACKWARD-CHAIN
                        (MEMBER BREADTH-FIRST DEPTH-FIRST DO-NOT-BACKWARD-CHAIN DO-NOT-SEEK-DATA))
                    (Structure 
                      FORWARD-CHAIN BooleanTruthValue)
                    (OR (MEMBER SUPPLIED INDEFINITE)
                        Integer)
                    BooleanTruthValue
                    (OR (OR (MEMBER QUANTITY)
                            (OR (MEMBER FLOAT TIME-STAMP)
                                Symbol)
                            (OR (MEMBER INTEGER INTERVAL)
                                Symbol))
                        (MEMBER VALUE SYMBOL TEXT TRUTH-VALUE))
                    (OR (MEMBER INFERENCE-ENGINE G2-SIMULATOR G2-METER GFI-DATA-SERVER 
                                GSI-DATA-SERVER G2-DATA-SERVER)
                        Symbol)
                    (OR NoItem
                        (Structure 
                          MAXIMUM-NUMBER-OF-DATA-POINTS Integer
                          MAXIMUM-AGE-OF-DATA-POINTS Integer
                          MINIMUM-INTERVAL-BETWEEN-DATA-POINTS Quantity)))))
        1)))
   *
   */
  public com.gensym.util.Sequence getAttributeInitializationsForClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @param attributeInitializations new value to conclude for ATTRIBUTE-INITIALIZATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAttributeInitializationsForClass(com.gensym.util.Sequence attributeInitializations) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-DISPLAYS
   * @return the value of the ATTRIBUTE-DISPLAYS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ATTRIBUTE-DISPLAYS is : 
   * (OR NoItem
      (MEMBER INHERITED)
      (Sequence 
        (Structure 
          ATTRIBUTE-LIST
            (Sequence 
              (Structure 
                ATTRIBUTE Symbol
                QUALIFIED-CLASS Symbol
                DISPLAY-WITH-NAME BooleanTruthValue)
              1))
          POSITION
            (OR (MEMBER AT-STANDARD-POSITION)
                (Structure 
                  X-OFFSET Integer
                  Y-OFFSET Integer)))
        1)))
   *
   */
  public java.lang.Object getAttributeDisplaysForClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-DISPLAYS
   * @param attributeDisplays new value to conclude for ATTRIBUTE-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAttributeDisplaysForClass(java.lang.Object attributeDisplays) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- STUBS
   * @return the value of the STUBS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for STUBS is : 
   * (OR NoItem
      (MEMBER INHERITED)
      (Sequence 
        (Structure 
          PORTNAME Symbol
          CONNECTION-CLASS Symbol
          STUB-DIRECTION
            (MEMBER INPUT OUTPUT)
          EDGE-LOCATION
            (MEMBER TOP BOTTOM RIGHT LEFT)
          COORDINATE-LOCATION Integer
          STYLE
            (MEMBER DIAGONAL ORTHOGONAL))
        1)))
   *
   */
  public java.lang.Object getStubsForClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- STUBS
   * @param stubs new value to conclude for STUBS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStubsForClass(java.lang.Object stubs) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DEFAULT-SETTINGS
   * @return the value of the DEFAULT-SETTINGS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Attribute DEFAULT-SETTINGS has no type
   *
   */
  public java.lang.Object getDefaultSettingsForClass() throws G2AccessException;

}
