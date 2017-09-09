/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      KbRestrictions.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:00:02 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface KbRestrictions extends com.gensym.classes.SystemTable {

  public static final Symbol KB_RESTRICTIONS_ = com.gensym.util.symbol.G2ClassSymbols.KB_RESTRICTIONS_;
  static final Symbol g2ClassName = KB_RESTRICTIONS_;
  static final Symbol[] classInheritancePath = new Symbol[] {KB_RESTRICTIONS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- MAIN-MENU-USER-RESTRICTIONS
   * @return the value of the MAIN-MENU-USER-RESTRICTIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MAIN-MENU-USER-RESTRICTIONS is : 
   * (OR NoItem
      (Sequence 
        (Structure 
          APPLICABLE-USER-MODES
            (Structure 
              NEGATIVE BooleanTruthValue
              MODES
                (Sequence Symbol 1))
          STATEMENTS
            (Sequence 
              (Structure 
                RESTRICTION-TYPE
                  (MEMBER INCLUDE INCLUDE-ADDITIONALLY EXCLUDE EXCLUDE-ADDITIONALLY 
                          EXCLUDE-ABSOLUTELY)
                MENU-CHOICES
                  (Sequence 
                    (OR (MEMBER START PAUSE RESUME RESET RESTART NEW-WORKSPACE GET-WORKSPACE 
                                INSPECT LOAD-MERGE-SAVE LOAD-KB MERGE-KB SAVE-KB SYSTEM-TABLES 
                                RUN-OPTIONS CHANGE-MODE MISCELLANY LONG-MENUS SHORT-MENUS 
                                CREATE-NEW-MODULE DELETE-MODULE NEW-TITLE-BLOCK NEATLY-STACK-WINDOWS 
                                NETWORK-INFO CLOSE-TELEWINDOWS-CONNECTION LOG-OUT CHANGE-PASSWORD 
                                REINSTALL-AUTHORIZED-USERS CONNECT-TO-FOREIGN-IMAGE 
                                DISCONNECT-FROM-FOREIGN-IMAGE LOAD-ATTRIBUTE-FILE WRITE-G2-STATS 
                                CLEAR-KB SHUT-DOWN-G2 TURN-ON-ALL-EXPLANATION-CACHING 
                                TURN-OFF-ALL-EXPLANATION-CACHING ENTER-PACKAGE-PREPARATION-MODE 
                                LEAVE-PACKAGE-PREPARATION-MODE STRIP-TEXTS-NOW 
                                MAKE-WORKSPACES-PROPRIETARY-NOW FLUSH-CHANGE-LOG-FOR-ENTIRE-KB 
                                ENTER-SIMULATE-PROPRIETARY-MODE LEAVE-SIMULATE-PROPRIETARY-MODE 
                                DO-NOT-HIGHLIGHT-INVOKED-RULES HIGHLIGHT-INVOKED-RULES 
                                ENABLE-ALL-ITEMS REMOVE-TRACING-AND-BREAKPOINTS LAUNCH-ONLINE-HELP 
                                PRINT-WINDOW)
                        Symbol)
                    1)))
              1)))
        1)))
   *
   */
  public com.gensym.util.Sequence getMainMenuUserRestrictions() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MAIN-MENU-USER-RESTRICTIONS
   * @param mainMenuUserRestrictions new value to conclude for MAIN-MENU-USER-RESTRICTIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMainMenuUserRestrictions(com.gensym.util.Sequence mainMenuUserRestrictions) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- KEYBOARD-COMMAND-RESTRICTIONS
   * @return the value of the KEYBOARD-COMMAND-RESTRICTIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for KEYBOARD-COMMAND-RESTRICTIONS is : 
   * (OR NoItem
      (Sequence 
        (Structure 
          APPLICABLE-USER-MODES
            (Structure 
              NEGATIVE BooleanTruthValue
              MODES
                (Sequence Symbol 1))
          STATEMENTS
            (Sequence 
              (Structure 
                RESTRICTION-TYPE
                  (MEMBER INCLUDE INCLUDE-ADDITIONALLY EXCLUDE EXCLUDE-ADDITIONALLY 
                          EXCLUDE-ABSOLUTELY)
                COMMAND-CHOICES
                  (Sequence 
                    (MEMBER PAUSE REFRESH HELP FULL-SCALE NORMALIZED-FULL-SCALE LIFT-TO-TOP 
                            DROP-TO-BOTTOM CIRCULATE-UP CIRCULATE-DOWN SHIFT-LEFT-TEN-PERCENT 
                            SHIFT-UP-TEN-PERCENT SHIFT-RIGHT-TEN-PERCENT SHIFT-DOWN-TEN-PERCENT 
                            SHIFT-LEFT-ONE-PERCENT SHIFT-UP-ONE-PERCENT SHIFT-RIGHT-ONE-PERCENT 
                            SHIFT-DOWN-ONE-PERCENT CENTER-ORIGIN SCALE-TO-FIT MAXIMUM-SCALE-TO-FIT 
                            TWENTY-PERCENT-SMALLER TWENTY-PERCENT-BIGGER TWENTY-PERCENT-NARROWER 
                            TWENTY-PERCENT-WIDER ONE-QUARTER-THE-SCALE FOUR-TIMES-THE-SCALE 
                            TOGGLE-VISIBLE-GRID)
                    1)))
              1)))
        1)))
   *
   */
  public com.gensym.util.Sequence getKeyboardCommandRestrictions() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- KEYBOARD-COMMAND-RESTRICTIONS
   * @param keyboardCommandRestrictions new value to conclude for KEYBOARD-COMMAND-RESTRICTIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setKeyboardCommandRestrictions(com.gensym.util.Sequence keyboardCommandRestrictions) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INITIAL-G2-USER-MODE-FOR-THIS-KB
   * @return the value of the INITIAL-G2-USER-MODE-FOR-THIS-KB attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INITIAL-G2-USER-MODE-FOR-THIS-KB is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getInitialG2UserModeForThisKb() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- AUTHORIZED-OPTIONAL-MODULES
   * @return the value of the AUTHORIZED-OPTIONAL-MODULES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for AUTHORIZED-OPTIONAL-MODULES is : 
   * (Sequence Symbol 1)
   *
   */
  public com.gensym.util.Sequence getAuthorizedOptionalModules() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SIMULATED-OPTIONAL-MODULES
   * @return the value of the SIMULATED-OPTIONAL-MODULES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SIMULATED-OPTIONAL-MODULES is : 
   * (OR NoItem
      Symbol
      (Sequence Symbol 1))
   *
   */
  public java.lang.Object getSimulatedOptionalModules() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SIMULATED-OPTIONAL-MODULES
   * @param simulatedOptionalModules new value to conclude for SIMULATED-OPTIONAL-MODULES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSimulatedOptionalModules(java.lang.Object simulatedOptionalModules) throws G2AccessException;

}
