/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      JmsInterface.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Wed Dec 18 18:33:17 EST 2002
 *
 */


package com.gensym.classes.modules.g2jms;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface JmsInterface extends com.gensym.classes.GsiInterface {

  public static final Symbol JMS_INTERFACE_ = Symbol.intern ("JMS-INTERFACE");
  static final Symbol g2ClassName = JMS_INTERFACE_;
  static final Symbol[] classInheritancePath = new Symbol[] {JMS_INTERFACE_, GSI_INTERFACE_, NETWORK_INTERFACE_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};

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
   * Generated Property Getter for attribute -- JMS-DESTINATION-TYPE
   * @return the value of the JMS-DESTINATION-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-DESTINATION-TYPE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getJmsDestinationType() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-DESTINATION-TYPE
   * @param jmsDestinationType new value to conclude for JMS-DESTINATION-TYPE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsDestinationType(com.gensym.util.Symbol jmsDestinationType) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JMS-INPUT-DESTINATION-NAME
   * @return the value of the JMS-INPUT-DESTINATION-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-INPUT-DESTINATION-NAME is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getJmsInputDestinationName() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-INPUT-DESTINATION-NAME
   * @param jmsInputDestinationName new value to conclude for JMS-INPUT-DESTINATION-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsInputDestinationName(com.gensym.util.Symbol jmsInputDestinationName) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JMS-INPUT-DESTINATION-SELECTOR
   * @return the value of the JMS-INPUT-DESTINATION-SELECTOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-INPUT-DESTINATION-SELECTOR is : 
   * Text
   *
   */
  public java.lang.String getJmsInputDestinationSelector() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-INPUT-DESTINATION-SELECTOR
   * @param jmsInputDestinationSelector new value to conclude for JMS-INPUT-DESTINATION-SELECTOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsInputDestinationSelector(java.lang.String jmsInputDestinationSelector) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JMS-DURABLE-TOPIC-SUBSCRIPTION
   * @return the value of the JMS-DURABLE-TOPIC-SUBSCRIPTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-DURABLE-TOPIC-SUBSCRIPTION is : 
   * BooleanTruthValue
   *
   */
  public boolean getJmsDurableTopicSubscription() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-DURABLE-TOPIC-SUBSCRIPTION
   * @param jmsDurableTopicSubscription new value to conclude for JMS-DURABLE-TOPIC-SUBSCRIPTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsDurableTopicSubscription(boolean jmsDurableTopicSubscription) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JMS-INPUT-MESSAGES
   * @return the value of the JMS-INPUT-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-INPUT-MESSAGES is : 
   * (Sequence)
   *
   */
  public com.gensym.util.Sequence getJmsInputMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-INPUT-MESSAGES
   * @param jmsInputMessages new value to conclude for JMS-INPUT-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsInputMessages(com.gensym.util.Sequence jmsInputMessages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JMS-INPUT-MESSAGE-PROCEDURE-CALLBACK
   * @return the value of the JMS-INPUT-MESSAGE-PROCEDURE-CALLBACK attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-INPUT-MESSAGE-PROCEDURE-CALLBACK is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getJmsInputMessageProcedureCallback() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-INPUT-MESSAGE-PROCEDURE-CALLBACK
   * @param jmsInputMessageProcedureCallback new value to conclude for JMS-INPUT-MESSAGE-PROCEDURE-CALLBACK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsInputMessageProcedureCallback(com.gensym.util.Symbol jmsInputMessageProcedureCallback) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JMS-OUTPUT-DESTINATION-NAME
   * @return the value of the JMS-OUTPUT-DESTINATION-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-OUTPUT-DESTINATION-NAME is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getJmsOutputDestinationName() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-OUTPUT-DESTINATION-NAME
   * @param jmsOutputDestinationName new value to conclude for JMS-OUTPUT-DESTINATION-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsOutputDestinationName(com.gensym.util.Symbol jmsOutputDestinationName) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JMS-OUTPUT-TOPIC-LOCAL-COPY
   * @return the value of the JMS-OUTPUT-TOPIC-LOCAL-COPY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-OUTPUT-TOPIC-LOCAL-COPY is : 
   * BooleanTruthValue
   *
   */
  public boolean getJmsOutputTopicLocalCopy() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-OUTPUT-TOPIC-LOCAL-COPY
   * @param jmsOutputTopicLocalCopy new value to conclude for JMS-OUTPUT-TOPIC-LOCAL-COPY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsOutputTopicLocalCopy(boolean jmsOutputTopicLocalCopy) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JMS-TRANSACTED-DELIVERY
   * @return the value of the JMS-TRANSACTED-DELIVERY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-TRANSACTED-DELIVERY is : 
   * BooleanTruthValue
   *
   */
  public boolean getJmsTransactedDelivery() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-TRANSACTED-DELIVERY
   * @param jmsTransactedDelivery new value to conclude for JMS-TRANSACTED-DELIVERY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsTransactedDelivery(boolean jmsTransactedDelivery) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JMS-SYNCHRONOUS-DELIVERY
   * @return the value of the JMS-SYNCHRONOUS-DELIVERY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-SYNCHRONOUS-DELIVERY is : 
   * BooleanTruthValue
   *
   */
  public boolean getJmsSynchronousDelivery() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-SYNCHRONOUS-DELIVERY
   * @param jmsSynchronousDelivery new value to conclude for JMS-SYNCHRONOUS-DELIVERY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsSynchronousDelivery(boolean jmsSynchronousDelivery) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JMS-PERSISTENT-DELIVERY
   * @return the value of the JMS-PERSISTENT-DELIVERY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-PERSISTENT-DELIVERY is : 
   * BooleanTruthValue
   *
   */
  public boolean getJmsPersistentDelivery() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-PERSISTENT-DELIVERY
   * @param jmsPersistentDelivery new value to conclude for JMS-PERSISTENT-DELIVERY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsPersistentDelivery(boolean jmsPersistentDelivery) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JMS-MESSAGE-PRIORITY
   * @return the value of the JMS-MESSAGE-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-MESSAGE-PRIORITY is : 
   * Integer
   *
   */
  public int getJmsMessagePriority() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-MESSAGE-PRIORITY
   * @param jmsMessagePriority new value to conclude for JMS-MESSAGE-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsMessagePriority(int jmsMessagePriority) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JMS-MESSAGE-ALIVE-TIME
   * @return the value of the JMS-MESSAGE-ALIVE-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-MESSAGE-ALIVE-TIME is : 
   * Integer
   *
   */
  public int getJmsMessageAliveTime() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-MESSAGE-ALIVE-TIME
   * @param jmsMessageAliveTime new value to conclude for JMS-MESSAGE-ALIVE-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsMessageAliveTime(int jmsMessageAliveTime) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JMS-USERNAME
   * @return the value of the JMS-USERNAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-USERNAME is : 
   * Text
   *
   */
  public java.lang.String getJmsUsername() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-USERNAME
   * @param jmsUsername new value to conclude for JMS-USERNAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsUsername(java.lang.String jmsUsername) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JMS-PASSWORD
   * @return the value of the JMS-PASSWORD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JMS-PASSWORD is : 
   * Text
   *
   */
  public java.lang.String getJmsPassword() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JMS-PASSWORD
   * @param jmsPassword new value to conclude for JMS-PASSWORD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJmsPassword(java.lang.String jmsPassword) throws G2AccessException;

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
          (Sequence Symbol 0)))
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
          ATTRIBUTE-INITIAL-ITEM-CLASS-RESTRICTED-TO-VARIABLE-OR-PARAMETER BooleanTruthValue
          ATTRIBUTE-INITIAL-TYPE Symbol
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
                                          SHOW-SUBTABLE-OF-UNSAVED-ATTRIBUTES ADD-OPTIONAL-SUBTABLE 
                                          TABLE CHOOSE-EXISTING-CLASS EDIT EDIT-ICON TRANSFER MOVE 
                                          CLONE SHOW-ATTRIBUTE-DISPLAY ADD-ANOTHER-ATTRIBUTE 
                                          DELETE-ATTRIBUTE ADD-NAME-OF-ATTRIBUTE 
                                          DELETE-NAME-OF-ATTRIBUTE HIDE-ATTRIBUTE-DISPLAY 
                                          CHANGE-SIZE ENABLE DISABLE GO-TO-ORIGINAL DELETE-ORIGINAL 
                                          TRANSFER-ORIGINAL DESCRIBE-CONFIGURATION DESCRIBE 
                                          VIEW-CHANGE-LOG SHOW-VALUE SHOW-TEXT SHOW-SUMMARY-OF-TEXT 
                                          ADD-SUBTABLE SUBTABLES DYNAMIC-BACKWARD-CHAINING 
                                          DESCRIBE-CHAINING DYNAMIC-GENERIC-RULE-DISPLAY HIDE DELETE 
                                          HIDE-TABLE MARK-TO-STRIP-TEXT MARK-TO-STRIP-TEXT-* 
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
                                (Sequence Symbol 0)
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
                                                CHANGE-MIN-SIZE ALIGN-TEXT SHOW-UNSAVED-ATTRIBUTES 
                                                TABLE-OF-HIDDEN-ATTRIBUTES COLOR DELETE 
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
                                                CHANGE-MIN-SIZE ALIGN-TEXT SHOW-UNSAVED-ATTRIBUTES 
                                                TABLE-OF-HIDDEN-ATTRIBUTES COLOR DELETE 
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
                                                CHANGE-MIN-SIZE ALIGN-TEXT SHOW-UNSAVED-ATTRIBUTES 
                                                TABLE-OF-HIDDEN-ATTRIBUTES COLOR DELETE 
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
                                    SHOW-SUBTABLE-OF-UNSAVED-ATTRIBUTES ADD-OPTIONAL-SUBTABLE TABLE 
                                    CHOOSE-EXISTING-CLASS EDIT EDIT-ICON TRANSFER MOVE CLONE 
                                    SHOW-ATTRIBUTE-DISPLAY ADD-ANOTHER-ATTRIBUTE DELETE-ATTRIBUTE 
                                    ADD-NAME-OF-ATTRIBUTE DELETE-NAME-OF-ATTRIBUTE 
                                    HIDE-ATTRIBUTE-DISPLAY CHANGE-SIZE ENABLE DISABLE GO-TO-ORIGINAL 
                                    DELETE-ORIGINAL TRANSFER-ORIGINAL DESCRIBE-CONFIGURATION 
                                    DESCRIBE VIEW-CHANGE-LOG SHOW-VALUE SHOW-TEXT 
                                    SHOW-SUMMARY-OF-TEXT ADD-SUBTABLE SUBTABLES 
                                    DYNAMIC-BACKWARD-CHAINING DESCRIBE-CHAINING 
                                    DYNAMIC-GENERIC-RULE-DISPLAY HIDE DELETE HIDE-TABLE 
                                    MARK-TO-STRIP-TEXT MARK-TO-STRIP-TEXT-* REMOVE-STRIP-TEXT-MARK 
                                    REMOVE-STRIP-TEXT-MARK-* MARK-NOT-TO-STRIP-TEXT-* 
                                    MARK-NOT-TO-STRIP-TEXT REMOVE-DO-NOT-STRIP-TEXT-MARK-* 
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
                          (Sequence Symbol 0)
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
                                          CHANGE-MIN-SIZE ALIGN-TEXT SHOW-UNSAVED-ATTRIBUTES 
                                          TABLE-OF-HIDDEN-ATTRIBUTES COLOR DELETE 
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
                                          CHANGE-MIN-SIZE ALIGN-TEXT SHOW-UNSAVED-ATTRIBUTES 
                                          TABLE-OF-HIDDEN-ATTRIBUTES COLOR DELETE 
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
                                          CHANGE-MIN-SIZE ALIGN-TEXT SHOW-UNSAVED-ATTRIBUTES 
                                          TABLE-OF-HIDDEN-ATTRIBUTES COLOR DELETE 
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
                        (MEMBER EXECUTE CONNECT INFORM READ WRITE)
                        1))
                    ACCESS-AGENT
                      (MEMBER ANY G2 GSI G2-AND-GSI G2-AND-TELEWINDOWS G2-AND-TELEWINDOWS-AND-GSI 
                              TELEWINDOWS-AND-GSI)
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
                        (Sequence ItemOrValue 1)
                        (Structure 
                          VALUES
                            (Sequence 
                              (OR ItemOrValue
                                  NoItem)
                              1))
                          ITEMS
                            (Sequence 
                              (OR Value
                                  NoItem)
                              1))))
                    (Sequence Value 1)
                    (OR NoItem
                        (Sequence (Class ITEM) 1)
                        (Sequence Value 1))
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
                        (MEMBER BREADTH-FIRST DEPTH-FIRST DO-NOT-BACKWARD-CHAIN DO-NOT-SEEK-DATA)
                      EXPLANATION-DATA BooleanTruthValue)
                    (Structure 
                      FORWARD-CHAIN BooleanTruthValue
                      EXPLANATION-DATA BooleanTruthValue)
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
                          MINIMUM-INTERVAL-BETWEEN-DATA-POINTS Quantity))))))))
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
            (MEMBER DIAGONAL ORTHOGONAL)
          LINE-PATTERN
            (OR NoItem
                (MEMBER SOLID DASH DOT LONG-DASH SHORT-DASH COARSE-DOT FINE-DOT)
                (Sequence Symbol 1)
                (Sequence Integer 1)
                (Structure 
                  PATTERN
                    (Sequence Integer 1)
                  NOT-SCALED-BY-LINE-WIDTH BooleanTruthValue)))
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

  /**
   * Auto Generated method for G2 Method
   * JMS-INTERFACE::JMS-SEND-TEXT-MESSAGE
   * @return the return from calling JMS-SEND-TEXT-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS JMS-INTERFACE,arg1:TEXT,arg2:STRUCTURE,arg3:CLASS G2-WINDOW) = (INTEGER)
   */
  public  int jmsSendTextMessage(java.lang.String arg1,com.gensym.util.Structure arg2,com.gensym.classes.G2Window arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * JMS-INTERFACE::JMS-SEND-MAP-MESSAGE
   * @return the return from calling JMS-SEND-MAP-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS JMS-INTERFACE,arg1:STRUCTURE,arg2:STRUCTURE,arg3:CLASS G2-WINDOW) = (INTEGER)
   */
  public  int jmsSendMapMessage(com.gensym.util.Structure arg1,com.gensym.util.Structure arg2,com.gensym.classes.G2Window arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * JMS-INTERFACE::JMS-SEND-MAP-MESSAGE
   * @return the return from calling JMS-SEND-MAP-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS JMS-INTERFACE,arg1:SEQUENCE,arg2:SEQUENCE,arg3:STRUCTURE,arg4:CLASS G2-WINDOW) = (INTEGER)
   */
  public  int jmsSendMapMessage(com.gensym.util.Sequence arg1,com.gensym.util.Sequence arg2,com.gensym.util.Structure arg3,com.gensym.classes.G2Window arg4) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * JMS-INTERFACE::JMS-PUBLISH-TEXT-MESSAGE
   * @return the return from calling JMS-PUBLISH-TEXT-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS JMS-INTERFACE,arg1:TEXT,arg2:STRUCTURE,arg3:CLASS G2-WINDOW) = (INTEGER)
   */
  public  int jmsPublishTextMessage(java.lang.String arg1,com.gensym.util.Structure arg2,com.gensym.classes.G2Window arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * JMS-INTERFACE::JMS-PUBLISH-MAP-MESSAGE
   * @return the return from calling JMS-PUBLISH-MAP-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS JMS-INTERFACE,arg1:STRUCTURE,arg2:STRUCTURE,arg3:CLASS G2-WINDOW) = (INTEGER)
   */
  public  int jmsPublishMapMessage(com.gensym.util.Structure arg1,com.gensym.util.Structure arg2,com.gensym.classes.G2Window arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * JMS-INTERFACE::JMS-PUBLISH-MAP-MESSAGE
   * @return the return from calling JMS-PUBLISH-MAP-MESSAGE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS JMS-INTERFACE,arg1:SEQUENCE,arg2:SEQUENCE,arg3:STRUCTURE,arg4:CLASS G2-WINDOW) = (INTEGER)
   */
  public  int jmsPublishMapMessage(com.gensym.util.Sequence arg1,com.gensym.util.Sequence arg2,com.gensym.util.Structure arg3,com.gensym.classes.G2Window arg4) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * JMS-INTERFACE::JMS-REMOVE-ALL-MESSAGES
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS JMS-INTERFACE,arg1:CLASS G2-WINDOW) = ()
   */
  public  void jmsRemoveAllMessages(com.gensym.classes.G2Window arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * JMS-INTERFACE::JMS-CONNECT
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS JMS-INTERFACE,arg1:CLASS G2-WINDOW) = ()
   */
  public  void jmsConnect(com.gensym.classes.G2Window arg1) throws G2AccessException;
  
}
