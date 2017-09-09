/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      MessageBoardParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:26:08 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface MessageBoardParameters extends com.gensym.classes.SystemTable {

  public static final Symbol MESSAGE_BOARD_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.MESSAGE_BOARD_PARAMETERS_;
  static final Symbol g2ClassName = MESSAGE_BOARD_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {MESSAGE_BOARD_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- INITIAL-WIDTH-OF-MESSAGE-BOARD
   * @return the value of the INITIAL-WIDTH-OF-MESSAGE-BOARD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INITIAL-WIDTH-OF-MESSAGE-BOARD is : 
   * Integer
   *
   */
  public int getInitialWidthOfMessageBoard() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INITIAL-WIDTH-OF-MESSAGE-BOARD
   * @param initialWidthOfMessageBoard new value to conclude for INITIAL-WIDTH-OF-MESSAGE-BOARD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInitialWidthOfMessageBoard(int initialWidthOfMessageBoard) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INITIAL-HEIGHT-OF-MESSAGE-BOARD
   * @return the value of the INITIAL-HEIGHT-OF-MESSAGE-BOARD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INITIAL-HEIGHT-OF-MESSAGE-BOARD is : 
   * Integer
   *
   */
  public int getInitialHeightOfMessageBoard() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INITIAL-HEIGHT-OF-MESSAGE-BOARD
   * @param initialHeightOfMessageBoard new value to conclude for INITIAL-HEIGHT-OF-MESSAGE-BOARD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInitialHeightOfMessageBoard(int initialHeightOfMessageBoard) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SPACING-BETWEEN-ENTRIES
   * @return the value of the SPACING-BETWEEN-ENTRIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SPACING-BETWEEN-ENTRIES is : 
   * Integer
   *
   */
  public int getSpacingBetweenEntries() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SPACING-BETWEEN-ENTRIES
   * @param spacingBetweenEntries new value to conclude for SPACING-BETWEEN-ENTRIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSpacingBetweenEntries(int spacingBetweenEntries) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-ENTRIES
   * @return the value of the MAXIMUM-NUMBER-OF-ENTRIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MAXIMUM-NUMBER-OF-ENTRIES is : 
   * Integer
   *
   */
  public int getMaximumNumberOfEntries() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-ENTRIES
   * @param maximumNumberOfEntries new value to conclude for MAXIMUM-NUMBER-OF-ENTRIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMaximumNumberOfEntries(int maximumNumberOfEntries) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- HIGHLIGHT-NEW-MESSAGES
   * @return the value of the HIGHLIGHT-NEW-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for HIGHLIGHT-NEW-MESSAGES is : 
   * BooleanTruthValue
   *
   */
  public boolean getHighlightNewMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- HIGHLIGHT-NEW-MESSAGES
   * @param highlightNewMessages new value to conclude for HIGHLIGHT-NEW-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setHighlightNewMessages(boolean highlightNewMessages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MINIMUM-DISPLAY-INTERVAL
   * @return the value of the MINIMUM-DISPLAY-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MINIMUM-DISPLAY-INTERVAL is : 
   * (OR (MEMBER INDEFINITE SUPPLIED)
      Integer)
   *
   */
  public java.lang.Object getMinimumDisplayInterval() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MINIMUM-DISPLAY-INTERVAL
   * @param minimumDisplayInterval new value to conclude for MINIMUM-DISPLAY-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMinimumDisplayInterval(java.lang.Object minimumDisplayInterval) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PREFER-NATIVE-MESSAGE-BOARD
   * @return the value of the PREFER-NATIVE-MESSAGE-BOARD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PREFER-NATIVE-MESSAGE-BOARD is : 
   * BooleanTruthValue
   *
   */
  public boolean getPreferNativeMessageBoard() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PREFER-NATIVE-MESSAGE-BOARD
   * @param preferNativeMessageBoard new value to conclude for PREFER-NATIVE-MESSAGE-BOARD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPreferNativeMessageBoard(boolean preferNativeMessageBoard) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INCLUDE-DATE-IN-MESSAGES
   * @return the value of the INCLUDE-DATE-IN-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INCLUDE-DATE-IN-MESSAGES is : 
   * BooleanTruthValue
   *
   */
  public boolean getIncludeDateInMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INCLUDE-DATE-IN-MESSAGES
   * @param includeDateInMessages new value to conclude for INCLUDE-DATE-IN-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIncludeDateInMessages(boolean includeDateInMessages) throws G2AccessException;

}
