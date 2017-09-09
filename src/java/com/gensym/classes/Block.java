/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Block.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:25:49 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Block extends com.gensym.classes.KbFrame, com.gensym.classes.SystemItem {

  public static final Symbol BLOCK_ = com.gensym.util.symbol.G2ClassSymbols.BLOCK_;
  static final Symbol g2ClassName = BLOCK_;
  static final Symbol[] classInheritancePath = new Symbol[] {BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};

  static final Symbol INSTANTIATE_ = Symbol.intern ("INSTANTIATE");
  static final Symbol INCLUDE_IN_MENUS_ = Symbol.intern ("INCLUDE-IN-MENUS");
  static final Symbol SYSTEM_MENU_CHOICES_ = Symbol.intern ("SYSTEM-MENU-CHOICES");

  static final Symbol[] staticAttributes = new Symbol[] {INSTANTIATE_, INCLUDE_IN_MENUS_, SYSTEM_MENU_CHOICES_};


  /**
   * Generated Property Getter for attribute -- ITEM-CONFIGURATION
   * @return the value of the ITEM-CONFIGURATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ITEM-CONFIGURATION is : 
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
                                          CHANGE-TO SHOW-SUBTABLE-OF-UNSAVED-ATTRIBUTES 
                                          ADD-OPTIONAL-SUBTABLE TABLE CHOOSE-EXISTING-CLASS EDIT 
                                          EDIT-ICON TRANSFER MOVE CLONE SHOW-ATTRIBUTE-DISPLAY 
                                          ADD-ANOTHER-ATTRIBUTE DELETE-ATTRIBUTE 
                                          ADD-NAME-OF-ATTRIBUTE DELETE-NAME-OF-ATTRIBUTE 
                                          HIDE-ATTRIBUTE-DISPLAY CHANGE-SIZE ENABLE DISABLE 
                                          GO-TO-ORIGINAL DELETE-ORIGINAL TRANSFER-ORIGINAL 
                                          DESCRIBE-CONFIGURATION DESCRIBE VIEW-CHANGE-LOG SHOW-VALUE 
                                          SHOW-TEXT SHOW-SUMMARY-OF-TEXT ADD-SUBTABLE SUBTABLES 
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
                                (Sequence Symbol 0)
                              APPLICABLE-ITEMS
                                (Sequence Symbol 1))
                            (Structure 
                              OPERATION-TYPE
                                (MEMBER PRESSING RELEASING CLICKING)
                              KEY-CODE
                                (Structure 
                                  MODIFIERS Integer
                                  MOUSE-BUTTON
                                    (MEMBER ANY LEFT MIDDLE RIGHT))
                              CONSEQUENT-ACTION
                                (OR (OR (MEMBER LIFT-TO-TOP DROP-TO-BOTTOM GO-TO-REFERENCED-ITEM 
                                                CLONE-AS-TREND-CHART TABLE EDIT TRANSFER MOVE CLONE 
                                                CHANGE-MIN-SIZE ALIGN-TEXT FONT 
                                                SHOW-UNSAVED-ATTRIBUTES TABLE-OF-HIDDEN-ATTRIBUTES 
                                                COLOR DELETE GO-TO-MESSAGE-ORIGIN ENABLE DISABLE 
                                                DESCRIBE VIEW-CHANGE-LOG COMPILE-G2GL-PROCESS 
                                                CLEAN-UP-G2GL-COMPILATION-POSTINGS-ON-PROCESS 
                                                EXECUTE-G2GL-PROCESS DYNAMIC-RULE-INVOCATION-DISPLAY 
                                                DESCRIBE-CONFIGURATION MARK-TO-STRIP-TEXT 
                                                MARK-TO-STRIP-TEXT-* REMOVE-STRIP-TEXT-MARK 
                                                REMOVE-STRIP-TEXT-MARK-* MARK-NOT-TO-STRIP-TEXT-* 
                                                MARK-NOT-TO-STRIP-TEXT 
                                                REMOVE-DO-NOT-STRIP-TEXT-MARK-* 
                                                REMOVE-DO-NOT-STRIP-TEXT-MARK GO-TO-SUBWORKSPACE 
                                                CREATE-INSTANCE SET-TEMPORARY-BREAKPOINT 
                                                REMOVE-TEMPORARY-BREAKPOINT 
                                                ADD-STUB-FOR-LOCAL-HANDLER EDIT-ICON TABLE-OF-VALUES 
                                                NAME ROTATE-REFLECT CHANGE-SIZE 
                                                RESTORE-TO-NORMAL-SIZE DYNAMIC-BACKWARD-CHAINING 
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
                                (MEMBER TYPING HOVERING)
                              KEY-CODE
                                (Structure 
                                  MODIFIERS Integer
                                  KEYBOARD-SYMBOL
                                    (MEMBER F1 F2 F3 F4 F5 F6 F7 F8 F9 F10 F11 F12 BACKSPACE TAB 
                                            LINEFEED RETURN ESCAPE 0 1 2 3 4 5 6 7 8 9 : ; < = > ? A 
                                            B C D E F G H I J K L M N O P Q R S T U V W X Y Z [ ] ^ 
                                            _ ` { | } SPACE ! " # $ % & ' ( ) * + , - . / DELETE 
                                            MOUSE-WHEEL-FORWARD MOUSE-WHEEL-BACKWARD MOUSE-HOVER 
                                            BREAK ENTER HELP INSERT REDO MENU FIND HOME BEGIN END 
                                            PAUSE SELECT PRINT EXECUTE ABORT CLEAR-SCREEN UP-ARROW 
                                            DOWN-ARROW LEFT-ARROW RIGHT-ARROW PREVIOUS-SCREEN 
                                            NEXT-SCREEN))
                              CONSEQUENT-ACTION
                                (OR (OR (MEMBER LIFT-TO-TOP DROP-TO-BOTTOM GO-TO-REFERENCED-ITEM 
                                                CLONE-AS-TREND-CHART TABLE EDIT TRANSFER MOVE CLONE 
                                                CHANGE-MIN-SIZE ALIGN-TEXT FONT 
                                                SHOW-UNSAVED-ATTRIBUTES TABLE-OF-HIDDEN-ATTRIBUTES 
                                                COLOR DELETE GO-TO-MESSAGE-ORIGIN ENABLE DISABLE 
                                                DESCRIBE VIEW-CHANGE-LOG COMPILE-G2GL-PROCESS 
                                                CLEAN-UP-G2GL-COMPILATION-POSTINGS-ON-PROCESS 
                                                EXECUTE-G2GL-PROCESS DYNAMIC-RULE-INVOCATION-DISPLAY 
                                                DESCRIBE-CONFIGURATION MARK-TO-STRIP-TEXT 
                                                MARK-TO-STRIP-TEXT-* REMOVE-STRIP-TEXT-MARK 
                                                REMOVE-STRIP-TEXT-MARK-* MARK-NOT-TO-STRIP-TEXT-* 
                                                MARK-NOT-TO-STRIP-TEXT 
                                                REMOVE-DO-NOT-STRIP-TEXT-MARK-* 
                                                REMOVE-DO-NOT-STRIP-TEXT-MARK GO-TO-SUBWORKSPACE 
                                                CREATE-INSTANCE SET-TEMPORARY-BREAKPOINT 
                                                REMOVE-TEMPORARY-BREAKPOINT 
                                                ADD-STUB-FOR-LOCAL-HANDLER EDIT-ICON TABLE-OF-VALUES 
                                                NAME ROTATE-REFLECT CHANGE-SIZE 
                                                RESTORE-TO-NORMAL-SIZE DYNAMIC-BACKWARD-CHAINING 
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
                                                CHANGE-MIN-SIZE ALIGN-TEXT FONT 
                                                SHOW-UNSAVED-ATTRIBUTES TABLE-OF-HIDDEN-ATTRIBUTES 
                                                COLOR DELETE GO-TO-MESSAGE-ORIGIN ENABLE DISABLE 
                                                DESCRIBE VIEW-CHANGE-LOG COMPILE-G2GL-PROCESS 
                                                CLEAN-UP-G2GL-COMPILATION-POSTINGS-ON-PROCESS 
                                                EXECUTE-G2GL-PROCESS DYNAMIC-RULE-INVOCATION-DISPLAY 
                                                DESCRIBE-CONFIGURATION MARK-TO-STRIP-TEXT 
                                                MARK-TO-STRIP-TEXT-* REMOVE-STRIP-TEXT-MARK 
                                                REMOVE-STRIP-TEXT-MARK-* MARK-NOT-TO-STRIP-TEXT-* 
                                                MARK-NOT-TO-STRIP-TEXT 
                                                REMOVE-DO-NOT-STRIP-TEXT-MARK-* 
                                                REMOVE-DO-NOT-STRIP-TEXT-MARK GO-TO-SUBWORKSPACE 
                                                CREATE-INSTANCE SET-TEMPORARY-BREAKPOINT 
                                                REMOVE-TEMPORARY-BREAKPOINT 
                                                ADD-STUB-FOR-LOCAL-HANDLER EDIT-ICON TABLE-OF-VALUES 
                                                NAME ROTATE-REFLECT CHANGE-SIZE 
                                                RESTORE-TO-NORMAL-SIZE DYNAMIC-BACKWARD-CHAINING 
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
                            (MEMBER SUBTABLE DELETE-SUBTABLE CHANGE-TO-NO CHANGE-TO-YES CHANGE-TO 
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
                          (MEMBER PRESSING RELEASING CLICKING)
                        KEY-CODE
                          (Structure 
                            MODIFIERS Integer
                            MOUSE-BUTTON
                              (MEMBER ANY LEFT MIDDLE RIGHT))
                        CONSEQUENT-ACTION
                          (OR (OR (MEMBER LIFT-TO-TOP DROP-TO-BOTTOM GO-TO-REFERENCED-ITEM 
                                          CLONE-AS-TREND-CHART TABLE EDIT TRANSFER MOVE CLONE 
                                          CHANGE-MIN-SIZE ALIGN-TEXT FONT SHOW-UNSAVED-ATTRIBUTES 
                                          TABLE-OF-HIDDEN-ATTRIBUTES COLOR DELETE 
                                          GO-TO-MESSAGE-ORIGIN ENABLE DISABLE DESCRIBE 
                                          VIEW-CHANGE-LOG COMPILE-G2GL-PROCESS 
                                          CLEAN-UP-G2GL-COMPILATION-POSTINGS-ON-PROCESS 
                                          EXECUTE-G2GL-PROCESS DYNAMIC-RULE-INVOCATION-DISPLAY 
                                          DESCRIBE-CONFIGURATION MARK-TO-STRIP-TEXT 
                                          MARK-TO-STRIP-TEXT-* REMOVE-STRIP-TEXT-MARK 
                                          REMOVE-STRIP-TEXT-MARK-* MARK-NOT-TO-STRIP-TEXT-* 
                                          MARK-NOT-TO-STRIP-TEXT REMOVE-DO-NOT-STRIP-TEXT-MARK-* 
                                          REMOVE-DO-NOT-STRIP-TEXT-MARK GO-TO-SUBWORKSPACE 
                                          CREATE-INSTANCE SET-TEMPORARY-BREAKPOINT 
                                          REMOVE-TEMPORARY-BREAKPOINT ADD-STUB-FOR-LOCAL-HANDLER 
                                          EDIT-ICON TABLE-OF-VALUES NAME ROTATE-REFLECT CHANGE-SIZE 
                                          RESTORE-TO-NORMAL-SIZE DYNAMIC-BACKWARD-CHAINING 
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
                          (MEMBER TYPING HOVERING)
                        KEY-CODE
                          (Structure 
                            MODIFIERS Integer
                            KEYBOARD-SYMBOL
                              (MEMBER F1 F2 F3 F4 F5 F6 F7 F8 F9 F10 F11 F12 BACKSPACE TAB LINEFEED 
                                      RETURN ESCAPE 0 1 2 3 4 5 6 7 8 9 : ; < = > ? A B C D E F G H 
                                      I J K L M N O P Q R S T U V W X Y Z [ ] ^ _ ` { | } SPACE ! " 
                                      # $ % & ' ( ) * + , - . / DELETE MOUSE-WHEEL-FORWARD 
                                      MOUSE-WHEEL-BACKWARD MOUSE-HOVER BREAK ENTER HELP INSERT REDO 
                                      MENU FIND HOME BEGIN END PAUSE SELECT PRINT EXECUTE ABORT 
                                      CLEAR-SCREEN UP-ARROW DOWN-ARROW LEFT-ARROW RIGHT-ARROW 
                                      PREVIOUS-SCREEN NEXT-SCREEN))
                        CONSEQUENT-ACTION
                          (OR (OR (MEMBER LIFT-TO-TOP DROP-TO-BOTTOM GO-TO-REFERENCED-ITEM 
                                          CLONE-AS-TREND-CHART TABLE EDIT TRANSFER MOVE CLONE 
                                          CHANGE-MIN-SIZE ALIGN-TEXT FONT SHOW-UNSAVED-ATTRIBUTES 
                                          TABLE-OF-HIDDEN-ATTRIBUTES COLOR DELETE 
                                          GO-TO-MESSAGE-ORIGIN ENABLE DISABLE DESCRIBE 
                                          VIEW-CHANGE-LOG COMPILE-G2GL-PROCESS 
                                          CLEAN-UP-G2GL-COMPILATION-POSTINGS-ON-PROCESS 
                                          EXECUTE-G2GL-PROCESS DYNAMIC-RULE-INVOCATION-DISPLAY 
                                          DESCRIBE-CONFIGURATION MARK-TO-STRIP-TEXT 
                                          MARK-TO-STRIP-TEXT-* REMOVE-STRIP-TEXT-MARK 
                                          REMOVE-STRIP-TEXT-MARK-* MARK-NOT-TO-STRIP-TEXT-* 
                                          MARK-NOT-TO-STRIP-TEXT REMOVE-DO-NOT-STRIP-TEXT-MARK-* 
                                          REMOVE-DO-NOT-STRIP-TEXT-MARK GO-TO-SUBWORKSPACE 
                                          CREATE-INSTANCE SET-TEMPORARY-BREAKPOINT 
                                          REMOVE-TEMPORARY-BREAKPOINT ADD-STUB-FOR-LOCAL-HANDLER 
                                          EDIT-ICON TABLE-OF-VALUES NAME ROTATE-REFLECT CHANGE-SIZE 
                                          RESTORE-TO-NORMAL-SIZE DYNAMIC-BACKWARD-CHAINING 
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
                                          CHANGE-MIN-SIZE ALIGN-TEXT FONT SHOW-UNSAVED-ATTRIBUTES 
                                          TABLE-OF-HIDDEN-ATTRIBUTES COLOR DELETE 
                                          GO-TO-MESSAGE-ORIGIN ENABLE DISABLE DESCRIBE 
                                          VIEW-CHANGE-LOG COMPILE-G2GL-PROCESS 
                                          CLEAN-UP-G2GL-COMPILATION-POSTINGS-ON-PROCESS 
                                          EXECUTE-G2GL-PROCESS DYNAMIC-RULE-INVOCATION-DISPLAY 
                                          DESCRIBE-CONFIGURATION MARK-TO-STRIP-TEXT 
                                          MARK-TO-STRIP-TEXT-* REMOVE-STRIP-TEXT-MARK 
                                          REMOVE-STRIP-TEXT-MARK-* MARK-NOT-TO-STRIP-TEXT-* 
                                          MARK-NOT-TO-STRIP-TEXT REMOVE-DO-NOT-STRIP-TEXT-MARK-* 
                                          REMOVE-DO-NOT-STRIP-TEXT-MARK GO-TO-SUBWORKSPACE 
                                          CREATE-INSTANCE SET-TEMPORARY-BREAKPOINT 
                                          REMOVE-TEMPORARY-BREAKPOINT ADD-STUB-FOR-LOCAL-HANDLER 
                                          EDIT-ICON TABLE-OF-VALUES NAME ROTATE-REFLECT CHANGE-SIZE 
                                          RESTORE-TO-NORMAL-SIZE DYNAMIC-BACKWARD-CHAINING 
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
  public com.gensym.util.Sequence getItemConfiguration() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ITEM-CONFIGURATION
   * @param itemConfiguration new value to conclude for ITEM-CONFIGURATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setItemConfiguration(com.gensym.util.Sequence itemConfiguration) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NAMES
   * @return the value of the NAMES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NAMES is : 
   * (OR Symbol
      (Sequence Symbol 0)
      NoItem)
   *
   */
  public java.lang.Object getNames() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NAMES
   * @param names new value to conclude for NAMES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNames(java.lang.Object names) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- LAYER-POSITION
   * @return the value of the LAYER-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LAYER-POSITION is : 
   * Integer
   *
   */
  public int getLayerPosition() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FOLLOWING-ITEM-IN-WORKSPACE-LAYERING
   * @return the value of the FOLLOWING-ITEM-IN-WORKSPACE-LAYERING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FOLLOWING-ITEM-IN-WORKSPACE-LAYERING is : 
   * (OR NoItem
      (Class BLOCK))
   *
   */
  public com.gensym.classes.Block getFollowingItemInWorkspaceLayering() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FOLLOWING-ITEM-IN-WORKSPACE-LAYERING
   * @param followingItemInWorkspaceLayering new value to conclude for FOLLOWING-ITEM-IN-WORKSPACE-LAYERING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFollowingItemInWorkspaceLayering(com.gensym.classes.Block followingItemInWorkspaceLayering) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- POSITION-IN-WORKSPACE
   * @return the value of the POSITION-IN-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for POSITION-IN-WORKSPACE is : 
   * (OR NoItem
      (Structure 
        X Integer
        Y Integer
        SUPERIOR (Class KB-WORKSPACE)))
   *
   */
  public com.gensym.util.Structure getPositionInWorkspace() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- POSITION-IN-WORKSPACE
   * @param positionInWorkspace new value to conclude for POSITION-IN-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPositionInWorkspace(com.gensym.util.Structure positionInWorkspace) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- RELATIONSHIPS
   * @return the value of the RELATIONSHIPS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for RELATIONSHIPS is : 
   * (OR NoItem
      (Sequence 
        (Structure 
          RELATION-NAME-REFERENCE Symbol
          RELATION-IS-INVERTED BooleanTruthValue
          RELATED-ITEMS
            (Sequence (Class ITEM) 1)))))
   *
   */
  public com.gensym.util.Sequence getRelationships() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- RELATIONSHIPS
   * @param relationships new value to conclude for RELATIONSHIPS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRelationships(com.gensym.util.Sequence relationships) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ITEM-NOTES
   * @return the value of the ITEM-NOTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ITEM-NOTES is : 
   * (OR (Sequence Text)
      NoItem)
   *
   */
  public com.gensym.util.Sequence getItemNotes() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CONTAINING-MODULE
   * @return the value of the CONTAINING-MODULE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CONTAINING-MODULE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getContainingModule() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ITEM-ACTIVE
   * @return the value of the ITEM-ACTIVE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ITEM-ACTIVE is : 
   * BooleanTruthValue
   *
   */
  public boolean getItemActive() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ITEM-STATUS
   * @return the value of the ITEM-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ITEM-STATUS is : 
   * (MEMBER OK INCOMPLETE BAD)
   *
   */
  public com.gensym.util.Symbol getItemStatus() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INSTANTIATE
   * @return the value of the INSTANTIATE attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INSTANTIATE is : 
   * BooleanTruthValue
   *
   */
  public boolean getInstantiateForClass() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INCLUDE-IN-MENUS
   * @return the value of the INCLUDE-IN-MENUS attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INCLUDE-IN-MENUS is : 
   * BooleanTruthValue
   *
   */
  public boolean getIncludeInMenusForClass() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SYSTEM-MENU-CHOICES
   * @return the value of the SYSTEM-MENU-CHOICES attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SYSTEM-MENU-CHOICES is : 
   * (OR (Sequence Symbol 0)
      ItemOrValue)
   *
   */
  public java.lang.Object getSystemMenuChoicesForClass() throws G2AccessException;

}
