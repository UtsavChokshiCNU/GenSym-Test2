/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      MessageBoardParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:26:09 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class MessageBoardParametersImpl extends com.gensym.classes.SystemTableImpl implements MessageBoardParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public MessageBoardParametersImpl() {
    super();
  }

  public MessageBoardParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public MessageBoardParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- INITIAL-WIDTH-OF-MESSAGE-BOARD
   * @param initialWidthOfMessageBoard new value to conclude for INITIAL-WIDTH-OF-MESSAGE-BOARD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setInitialWidthOfMessageBoard(int initialWidthOfMessageBoard) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.INITIAL_WIDTH_OF_MESSAGE_BOARD_, initialWidthOfMessageBoard);
  }

  /**
   * Generated Property Getter for attribute -- INITIAL-WIDTH-OF-MESSAGE-BOARD
   * @return the value of the INITIAL-WIDTH-OF-MESSAGE-BOARD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getInitialWidthOfMessageBoard() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INITIAL_WIDTH_OF_MESSAGE_BOARD_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- INITIAL-HEIGHT-OF-MESSAGE-BOARD
   * @param initialHeightOfMessageBoard new value to conclude for INITIAL-HEIGHT-OF-MESSAGE-BOARD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setInitialHeightOfMessageBoard(int initialHeightOfMessageBoard) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.INITIAL_HEIGHT_OF_MESSAGE_BOARD_, initialHeightOfMessageBoard);
  }

  /**
   * Generated Property Getter for attribute -- INITIAL-HEIGHT-OF-MESSAGE-BOARD
   * @return the value of the INITIAL-HEIGHT-OF-MESSAGE-BOARD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getInitialHeightOfMessageBoard() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INITIAL_HEIGHT_OF_MESSAGE_BOARD_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- SPACING-BETWEEN-ENTRIES
   * @param spacingBetweenEntries new value to conclude for SPACING-BETWEEN-ENTRIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSpacingBetweenEntries(int spacingBetweenEntries) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SPACING_BETWEEN_ENTRIES_, spacingBetweenEntries);
  }

  /**
   * Generated Property Getter for attribute -- SPACING-BETWEEN-ENTRIES
   * @return the value of the SPACING-BETWEEN-ENTRIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getSpacingBetweenEntries() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SPACING_BETWEEN_ENTRIES_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-ENTRIES
   * @param maximumNumberOfEntries new value to conclude for MAXIMUM-NUMBER-OF-ENTRIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMaximumNumberOfEntries(int maximumNumberOfEntries) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_ENTRIES_, maximumNumberOfEntries);
  }

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-ENTRIES
   * @return the value of the MAXIMUM-NUMBER-OF-ENTRIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getMaximumNumberOfEntries() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_ENTRIES_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- HIGHLIGHT-NEW-MESSAGES
   * @param highlightNewMessages new value to conclude for HIGHLIGHT-NEW-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setHighlightNewMessages(boolean highlightNewMessages) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.HIGHLIGHT_NEW_MESSAGES_, highlightNewMessages);
  }

  /**
   * Generated Property Getter for attribute -- HIGHLIGHT-NEW-MESSAGES
   * @return the value of the HIGHLIGHT-NEW-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getHighlightNewMessages() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.HIGHLIGHT_NEW_MESSAGES_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- MINIMUM-DISPLAY-INTERVAL
   * @param minimumDisplayInterval new value to conclude for MINIMUM-DISPLAY-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMinimumDisplayInterval(java.lang.Object minimumDisplayInterval) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MINIMUM_DISPLAY_INTERVAL_, minimumDisplayInterval);
  }

  /**
   * Generated Property Getter for attribute -- MINIMUM-DISPLAY-INTERVAL
   * @return the value of the MINIMUM-DISPLAY-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getMinimumDisplayInterval() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MINIMUM_DISPLAY_INTERVAL_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- PREFER-NATIVE-MESSAGE-BOARD
   * @param preferNativeMessageBoard new value to conclude for PREFER-NATIVE-MESSAGE-BOARD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPreferNativeMessageBoard(boolean preferNativeMessageBoard) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PREFER_NATIVE_MESSAGE_BOARD_, preferNativeMessageBoard);
  }

  /**
   * Generated Property Getter for attribute -- PREFER-NATIVE-MESSAGE-BOARD
   * @return the value of the PREFER-NATIVE-MESSAGE-BOARD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getPreferNativeMessageBoard() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PREFER_NATIVE_MESSAGE_BOARD_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- INCLUDE-DATE-IN-MESSAGES
   * @param includeDateInMessages new value to conclude for INCLUDE-DATE-IN-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setIncludeDateInMessages(boolean includeDateInMessages) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.INCLUDE_DATE_IN_MESSAGES_, includeDateInMessages);
  }

  /**
   * Generated Property Getter for attribute -- INCLUDE-DATE-IN-MESSAGES
   * @return the value of the INCLUDE-DATE-IN-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getIncludeDateInMessages() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INCLUDE_DATE_IN_MESSAGES_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
