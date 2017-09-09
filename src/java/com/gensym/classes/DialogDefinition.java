/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      DialogDefinition.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:37:53 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface DialogDefinition extends com.gensym.classes.Item, com.gensym.classes.Entity {

  public static final Symbol DIALOG_DEFINITION_ = com.gensym.util.symbol.G2ClassSymbols.DIALOG_DEFINITION_;
  static final Symbol g2ClassName = DIALOG_DEFINITION_;
  static final Symbol[] classInheritancePath = new Symbol[] {DIALOG_DEFINITION_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this item
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
  public com.gensym.util.Structure getAuthors() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAuthors(com.gensym.util.Structure authors) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CHANGE-LOG is : 
   * (OR (Sequence)
      NoItem)
   *
   */
  public com.gensym.util.Sequence getChangeLog() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DIALOG-TITLE
   * @return the value of the DIALOG-TITLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DIALOG-TITLE is : 
   * (OR NoItem
      Text)
   *
   */
  public java.lang.String getDialogTitle() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DIALOG-TITLE
   * @param dialogTitle new value to conclude for DIALOG-TITLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDialogTitle(java.lang.String dialogTitle) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DIALOG-WIDTH
   * @return the value of the DIALOG-WIDTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DIALOG-WIDTH is : 
   * Integer
   *
   */
  public int getDialogWidth() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DIALOG-WIDTH
   * @param dialogWidth new value to conclude for DIALOG-WIDTH
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDialogWidth(int dialogWidth) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DIALOG-HEIGHT
   * @return the value of the DIALOG-HEIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DIALOG-HEIGHT is : 
   * Integer
   *
   */
  public int getDialogHeight() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DIALOG-HEIGHT
   * @param dialogHeight new value to conclude for DIALOG-HEIGHT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDialogHeight(int dialogHeight) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DIALOG-X-POSITION
   * @return the value of the DIALOG-X-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DIALOG-X-POSITION is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getDialogXPosition() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DIALOG-X-POSITION
   * @param dialogXPosition new value to conclude for DIALOG-X-POSITION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDialogXPosition(com.gensym.util.Symbol dialogXPosition) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DIALOG-Y-POSITION
   * @return the value of the DIALOG-Y-POSITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DIALOG-Y-POSITION is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getDialogYPosition() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DIALOG-Y-POSITION
   * @param dialogYPosition new value to conclude for DIALOG-Y-POSITION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDialogYPosition(com.gensym.util.Symbol dialogYPosition) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DIALOG-TYPE
   * @return the value of the DIALOG-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DIALOG-TYPE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getDialogType() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DIALOG-TYPE
   * @param dialogType new value to conclude for DIALOG-TYPE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDialogType(com.gensym.util.Symbol dialogType) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UPDATE-CALLBACK
   * @return the value of the UPDATE-CALLBACK attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UPDATE-CALLBACK is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getUpdateCallback() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UPDATE-CALLBACK
   * @param updateCallback new value to conclude for UPDATE-CALLBACK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUpdateCallback(com.gensym.util.Symbol updateCallback) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DISMISSED-CALLBACK
   * @return the value of the DISMISSED-CALLBACK attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DISMISSED-CALLBACK is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getDismissedCallback() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DISMISSED-CALLBACK
   * @param dismissedCallback new value to conclude for DISMISSED-CALLBACK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDismissedCallback(com.gensym.util.Symbol dismissedCallback) throws G2AccessException;

}
