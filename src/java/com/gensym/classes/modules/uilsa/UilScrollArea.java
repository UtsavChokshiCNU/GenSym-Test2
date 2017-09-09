/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilScrollArea.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:06:20 EDT 2007
 *
 */


package com.gensym.classes.modules.uilsa;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface UilScrollArea extends com.gensym.classes.modules.uilsa.UilScrollObject {

  public static final Symbol UIL_SCROLL_AREA_ = Symbol.intern ("UIL-SCROLL-AREA");
  static final Symbol g2ClassName = UIL_SCROLL_AREA_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_SCROLL_AREA_, UIL_SCROLL_OBJECT_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- MESSAGE-CLASS-NAME
   * @return the value of the MESSAGE-CLASS-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MESSAGE-CLASS-NAME is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getMessageClassName() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MESSAGE-CLASS-NAME
   * @param messageClassName new value to conclude for MESSAGE-CLASS-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMessageClassName(java.lang.Object messageClassName) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SCROLL-AREA-CLASS-NAME
   * @return the value of the UIL-SCROLL-AREA-CLASS-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SCROLL-AREA-CLASS-NAME is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilScrollAreaClassName() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SCROLL-AREA-CLASS-NAME
   * @param uilScrollAreaClassName new value to conclude for UIL-SCROLL-AREA-CLASS-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilScrollAreaClassName(java.lang.Object uilScrollAreaClassName) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SCROLL-BAR-CLASS-NAME
   * @return the value of the UIL-SCROLL-BAR-CLASS-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SCROLL-BAR-CLASS-NAME is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilScrollBarClassName() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SCROLL-BAR-CLASS-NAME
   * @param uilScrollBarClassName new value to conclude for UIL-SCROLL-BAR-CLASS-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilScrollBarClassName(java.lang.Object uilScrollBarClassName) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ORDERING-METHOD
   * @return the value of the ORDERING-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ORDERING-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getOrderingMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ORDERING-METHOD
   * @param orderingMethod new value to conclude for ORDERING-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setOrderingMethod(java.lang.Object orderingMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MAXIMUM-ALLOWED-MESSAGES
   * @return the value of the MAXIMUM-ALLOWED-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MAXIMUM-ALLOWED-MESSAGES is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getMaximumAllowedMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MAXIMUM-ALLOWED-MESSAGES
   * @param maximumAllowedMessages new value to conclude for MAXIMUM-ALLOWED-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMaximumAllowedMessages(java.lang.Object maximumAllowedMessages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SIZE
   * @return the value of the SIZE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SIZE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getSize() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SIZE
   * @param size new value to conclude for SIZE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSize(java.lang.Object size) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-FONT-SIZE-FOR-MESSAGES
   * @return the value of the UIL-FONT-SIZE-FOR-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-FONT-SIZE-FOR-MESSAGES is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilFontSizeForMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-FONT-SIZE-FOR-MESSAGES
   * @param uilFontSizeForMessages new value to conclude for UIL-FONT-SIZE-FOR-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilFontSizeForMessages(java.lang.Object uilFontSizeForMessages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-MESSAGE-SELECTION-METHOD
   * @return the value of the UIL-MESSAGE-SELECTION-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-MESSAGE-SELECTION-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilMessageSelectionMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-MESSAGE-SELECTION-METHOD
   * @param uilMessageSelectionMethod new value to conclude for UIL-MESSAGE-SELECTION-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilMessageSelectionMethod(java.lang.Object uilMessageSelectionMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-MESSAGE-UNSELECTION-METHOD
   * @return the value of the UIL-MESSAGE-UNSELECTION-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-MESSAGE-UNSELECTION-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilMessageUnselectionMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-MESSAGE-UNSELECTION-METHOD
   * @param uilMessageUnselectionMethod new value to conclude for UIL-MESSAGE-UNSELECTION-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilMessageUnselectionMethod(java.lang.Object uilMessageUnselectionMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SCROLL-INCREMENT-METHOD
   * @return the value of the UIL-SCROLL-INCREMENT-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SCROLL-INCREMENT-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilScrollIncrementMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SCROLL-INCREMENT-METHOD
   * @param uilScrollIncrementMethod new value to conclude for UIL-SCROLL-INCREMENT-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilScrollIncrementMethod(java.lang.Object uilScrollIncrementMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SCROLL-DECREMENT-METHOD
   * @return the value of the UIL-SCROLL-DECREMENT-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SCROLL-DECREMENT-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilScrollDecrementMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SCROLL-DECREMENT-METHOD
   * @param uilScrollDecrementMethod new value to conclude for UIL-SCROLL-DECREMENT-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilScrollDecrementMethod(java.lang.Object uilScrollDecrementMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SCROLL-INCREMENT-LINE-METHOD
   * @return the value of the UIL-SCROLL-INCREMENT-LINE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SCROLL-INCREMENT-LINE-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilScrollIncrementLineMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SCROLL-INCREMENT-LINE-METHOD
   * @param uilScrollIncrementLineMethod new value to conclude for UIL-SCROLL-INCREMENT-LINE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilScrollIncrementLineMethod(java.lang.Object uilScrollIncrementLineMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SCROLL-DECREMENT-LINE-METHOD
   * @return the value of the UIL-SCROLL-DECREMENT-LINE-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SCROLL-DECREMENT-LINE-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilScrollDecrementLineMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SCROLL-DECREMENT-LINE-METHOD
   * @param uilScrollDecrementLineMethod new value to conclude for UIL-SCROLL-DECREMENT-LINE-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilScrollDecrementLineMethod(java.lang.Object uilScrollDecrementLineMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SCROLL-TO-POSITION-METHOD
   * @return the value of the UIL-SCROLL-TO-POSITION-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SCROLL-TO-POSITION-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilScrollToPositionMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SCROLL-TO-POSITION-METHOD
   * @param uilScrollToPositionMethod new value to conclude for UIL-SCROLL-TO-POSITION-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilScrollToPositionMethod(java.lang.Object uilScrollToPositionMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ALLOW-MULTIPLE-SIMULTANEOUS-SELECTIONS
   * @return the value of the ALLOW-MULTIPLE-SIMULTANEOUS-SELECTIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ALLOW-MULTIPLE-SIMULTANEOUS-SELECTIONS is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getAllowMultipleSimultaneousSelections() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ALLOW-MULTIPLE-SIMULTANEOUS-SELECTIONS
   * @param allowMultipleSimultaneousSelections new value to conclude for ALLOW-MULTIPLE-SIMULTANEOUS-SELECTIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAllowMultipleSimultaneousSelections(java.lang.Object allowMultipleSimultaneousSelections) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ALLOW-UNSELECT-ON-SELECTED-MESSAGE
   * @return the value of the ALLOW-UNSELECT-ON-SELECTED-MESSAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ALLOW-UNSELECT-ON-SELECTED-MESSAGE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getAllowUnselectOnSelectedMessage() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ALLOW-UNSELECT-ON-SELECTED-MESSAGE
   * @param allowUnselectOnSelectedMessage new value to conclude for ALLOW-UNSELECT-ON-SELECTED-MESSAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAllowUnselectOnSelectedMessage(java.lang.Object allowUnselectOnSelectedMessage) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-UPDATE-STYLE
   * @return the value of the UIL-UPDATE-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-UPDATE-STYLE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilUpdateStyle() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-UPDATE-STYLE
   * @param uilUpdateStyle new value to conclude for UIL-UPDATE-STYLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilUpdateStyle(java.lang.Object uilUpdateStyle) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-CONCLUDE-STYLE
   * @return the value of the UIL-CONCLUDE-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-CONCLUDE-STYLE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilConcludeStyle() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-CONCLUDE-STYLE
   * @param uilConcludeStyle new value to conclude for UIL-CONCLUDE-STYLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilConcludeStyle(java.lang.Object uilConcludeStyle) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-MAXIMUM-CHARACTERS-TO-DISPLAY
   * @return the value of the UIL-MAXIMUM-CHARACTERS-TO-DISPLAY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-MAXIMUM-CHARACTERS-TO-DISPLAY is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilMaximumCharactersToDisplay() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-MAXIMUM-CHARACTERS-TO-DISPLAY
   * @param uilMaximumCharactersToDisplay new value to conclude for UIL-MAXIMUM-CHARACTERS-TO-DISPLAY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilMaximumCharactersToDisplay(java.lang.Object uilMaximumCharactersToDisplay) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ALLOW-MULTIPLE-LINES
   * @return the value of the UIL-ALLOW-MULTIPLE-LINES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ALLOW-MULTIPLE-LINES is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilAllowMultipleLines() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ALLOW-MULTIPLE-LINES
   * @param uilAllowMultipleLines new value to conclude for UIL-ALLOW-MULTIPLE-LINES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilAllowMultipleLines(java.lang.Object uilAllowMultipleLines) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ALLOW-MANUAL-MESSAGE-MOVE
   * @return the value of the UIL-ALLOW-MANUAL-MESSAGE-MOVE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ALLOW-MANUAL-MESSAGE-MOVE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilAllowManualMessageMove() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ALLOW-MANUAL-MESSAGE-MOVE
   * @param uilAllowManualMessageMove new value to conclude for UIL-ALLOW-MANUAL-MESSAGE-MOVE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilAllowManualMessageMove(java.lang.Object uilAllowManualMessageMove) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-FORMAT-SPECIFICATION
   * @return the value of the UIL-FORMAT-SPECIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-FORMAT-SPECIFICATION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilFormatSpecification() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-FORMAT-SPECIFICATION
   * @param uilFormatSpecification new value to conclude for UIL-FORMAT-SPECIFICATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilFormatSpecification(java.lang.Object uilFormatSpecification) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-DISPLAY-DISABLED-MESSAGES
   * @return the value of the UIL-DISPLAY-DISABLED-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-DISPLAY-DISABLED-MESSAGES is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilDisplayDisabledMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-DISPLAY-DISABLED-MESSAGES
   * @param uilDisplayDisabledMessages new value to conclude for UIL-DISPLAY-DISABLED-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilDisplayDisabledMessages(java.lang.Object uilDisplayDisabledMessages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SPACE-FOR-MESSAGES
   * @return the value of the SPACE-FOR-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SPACE-FOR-MESSAGES is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getSpaceForMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SPACE-FOR-MESSAGES
   * @param spaceForMessages new value to conclude for SPACE-FOR-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSpaceForMessages(java.lang.Object spaceForMessages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TOP-MESSAGE-VISIBLE
   * @return the value of the TOP-MESSAGE-VISIBLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TOP-MESSAGE-VISIBLE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getTopMessageVisible() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TOP-MESSAGE-VISIBLE
   * @param topMessageVisible new value to conclude for TOP-MESSAGE-VISIBLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTopMessageVisible(java.lang.Object topMessageVisible) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-VISIBLE-MESSAGES
   * @return the value of the NUMBER-OF-VISIBLE-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NUMBER-OF-VISIBLE-MESSAGES is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getNumberOfVisibleMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-VISIBLE-MESSAGES
   * @param numberOfVisibleMessages new value to conclude for NUMBER-OF-VISIBLE-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNumberOfVisibleMessages(java.lang.Object numberOfVisibleMessages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CURRENT-MESSAGE-POINTER
   * @return the value of the CURRENT-MESSAGE-POINTER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CURRENT-MESSAGE-POINTER is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getCurrentMessagePointer() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CURRENT-MESSAGE-POINTER
   * @param currentMessagePointer new value to conclude for CURRENT-MESSAGE-POINTER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setCurrentMessagePointer(java.lang.Object currentMessagePointer) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-MESSAGES
   * @return the value of the NUMBER-OF-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NUMBER-OF-MESSAGES is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getNumberOfMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-MESSAGES
   * @param numberOfMessages new value to conclude for NUMBER-OF-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNumberOfMessages(java.lang.Object numberOfMessages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MESSAGE-LIST
   * @return the value of the MESSAGE-LIST attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MESSAGE-LIST is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getMessageList() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MESSAGE-LIST
   * @param messageList new value to conclude for MESSAGE-LIST
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMessageList(java.lang.Object messageList) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MEMBERS
   * @return the value of the MEMBERS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MEMBERS is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getMembers() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MEMBERS
   * @param members new value to conclude for MEMBERS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMembers(java.lang.Object members) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MEMBERS-INDEX
   * @return the value of the MEMBERS-INDEX attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MEMBERS-INDEX is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getMembersIndex() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MEMBERS-INDEX
   * @param membersIndex new value to conclude for MEMBERS-INDEX
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMembersIndex(java.lang.Object membersIndex) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MOST-RECENTLY-ADDED-POINTER
   * @return the value of the MOST-RECENTLY-ADDED-POINTER attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MOST-RECENTLY-ADDED-POINTER is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getMostRecentlyAddedPointer() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MOST-RECENTLY-ADDED-POINTER
   * @param mostRecentlyAddedPointer new value to conclude for MOST-RECENTLY-ADDED-POINTER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMostRecentlyAddedPointer(java.lang.Object mostRecentlyAddedPointer) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ORIENTATION
   * @return the value of the ORIENTATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ORIENTATION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getOrientation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ORIENTATION
   * @param orientation new value to conclude for ORIENTATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setOrientation(java.lang.Object orientation) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- STATE
   * @return the value of the STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for STATE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getState() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- STATE
   * @param state new value to conclude for STATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setState(java.lang.Object state) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-ACTIVATION-STATE
   * @return the value of the UIL-ACTIVATION-STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-ACTIVATION-STATE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilActivationState() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-ACTIVATION-STATE
   * @param uilActivationState new value to conclude for UIL-ACTIVATION-STATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilActivationState(java.lang.Object uilActivationState) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CORNER-STATE
   * @return the value of the CORNER-STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CORNER-STATE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getCornerState() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CORNER-STATE
   * @param cornerState new value to conclude for CORNER-STATE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setCornerState(java.lang.Object cornerState) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TOP-OF-DISPLAY-AREA-X
   * @return the value of the TOP-OF-DISPLAY-AREA-X attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TOP-OF-DISPLAY-AREA-X is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getTopOfDisplayAreaX() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TOP-OF-DISPLAY-AREA-X
   * @param topOfDisplayAreaX new value to conclude for TOP-OF-DISPLAY-AREA-X
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTopOfDisplayAreaX(java.lang.Object topOfDisplayAreaX) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TOP-OF-DISPLAY-AREA-Y
   * @return the value of the TOP-OF-DISPLAY-AREA-Y attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TOP-OF-DISPLAY-AREA-Y is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getTopOfDisplayAreaY() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TOP-OF-DISPLAY-AREA-Y
   * @param topOfDisplayAreaY new value to conclude for TOP-OF-DISPLAY-AREA-Y
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTopOfDisplayAreaY(java.lang.Object topOfDisplayAreaY) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- BOTTOM-OF-DISPLAY-AREA-Y
   * @return the value of the BOTTOM-OF-DISPLAY-AREA-Y attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for BOTTOM-OF-DISPLAY-AREA-Y is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getBottomOfDisplayAreaY() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- BOTTOM-OF-DISPLAY-AREA-Y
   * @param bottomOfDisplayAreaY new value to conclude for BOTTOM-OF-DISPLAY-AREA-Y
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setBottomOfDisplayAreaY(java.lang.Object bottomOfDisplayAreaY) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UPDATE-DISPLAY
   * @return the value of the UPDATE-DISPLAY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UPDATE-DISPLAY is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUpdateDisplay() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UPDATE-DISPLAY
   * @param updateDisplay new value to conclude for UPDATE-DISPLAY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUpdateDisplay(java.lang.Object updateDisplay) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-SCROLL-THUMB-ADJUSTMENT-METHOD
   * @return the value of the UIL-SCROLL-THUMB-ADJUSTMENT-METHOD attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-SCROLL-THUMB-ADJUSTMENT-METHOD is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilScrollThumbAdjustmentMethod() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-SCROLL-THUMB-ADJUSTMENT-METHOD
   * @param uilScrollThumbAdjustmentMethod new value to conclude for UIL-SCROLL-THUMB-ADJUSTMENT-METHOD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilScrollThumbAdjustmentMethod(java.lang.Object uilScrollThumbAdjustmentMethod) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SAVED-SCROLL-AREA-KEY
   * @return the value of the SAVED-SCROLL-AREA-KEY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SAVED-SCROLL-AREA-KEY is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getSavedScrollAreaKey() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SAVED-SCROLL-AREA-KEY
   * @param savedScrollAreaKey new value to conclude for SAVED-SCROLL-AREA-KEY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSavedScrollAreaKey(java.lang.Object savedScrollAreaKey) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SAVED-MESSAGES-ARE-STABLE
   * @return the value of the SAVED-MESSAGES-ARE-STABLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SAVED-MESSAGES-ARE-STABLE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getSavedMessagesAreStable() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SAVED-MESSAGES-ARE-STABLE
   * @param savedMessagesAreStable new value to conclude for SAVED-MESSAGES-ARE-STABLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSavedMessagesAreStable(java.lang.Object savedMessagesAreStable) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-UPDATE-VALUE
   * @return the value of the UIL-UPDATE-VALUE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-UPDATE-VALUE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilUpdateValue() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-UPDATE-VALUE
   * @param uilUpdateValue new value to conclude for UIL-UPDATE-VALUE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilUpdateValue(java.lang.Object uilUpdateValue) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-LAST-ENABLED-MESSAGE
   * @return the value of the UIL-LAST-ENABLED-MESSAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-LAST-ENABLED-MESSAGE is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilLastEnabledMessage() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-LAST-ENABLED-MESSAGE
   * @param uilLastEnabledMessage new value to conclude for UIL-LAST-ENABLED-MESSAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilLastEnabledMessage(java.lang.Object uilLastEnabledMessage) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * UIL-SCROLL-AREA::UPP-EXTRACT-VALUE-FROM-ITEM
   * @return the return from calling UPP-EXTRACT-VALUE-FROM-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-SCROLL-AREA) = (VALUE,TRUTH-VALUE)
   */
  public  com.gensym.util.Sequence uppExtractValueFromItem() throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * UIL-SCROLL-AREA::UPP-EXTRACT-VALUES-FROM-ITEM
   * @return the return from calling UPP-EXTRACT-VALUES-FROM-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-SCROLL-AREA) = (ITEM-OR-VALUE)
   */
  public  java.lang.Object uppExtractValuesFromItem() throws G2AccessException;
  
}
