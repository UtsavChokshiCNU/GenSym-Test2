/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilDialogTitle.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:44 EDT 2007
 *
 */


package com.gensym.classes.modules.uillib;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface UilDialogTitle extends com.gensym.classes.modules.uilroot.UilText {

  public static final Symbol UIL_DIALOG_TITLE_ = Symbol.intern ("UIL-DIALOG-TITLE");
  static final Symbol g2ClassName = UIL_DIALOG_TITLE_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_DIALOG_TITLE_, UIL_TEXT_, UIL_GRMES_, UIL_MESSAGE_, MESSAGE_, ITEM_, TEXT_BOX_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-JUSTIFICATION
   * @return the value of the UIL-JUSTIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-JUSTIFICATION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilJustification() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-JUSTIFICATION
   * @param uilJustification new value to conclude for UIL-JUSTIFICATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilJustification(java.lang.Object uilJustification) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-TITLE-BUTTON-BEHAVIOUR-ENABLED
   * @return the value of the UIL-TITLE-BUTTON-BEHAVIOUR-ENABLED attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-TITLE-BUTTON-BEHAVIOUR-ENABLED is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilTitleButtonBehaviourEnabled() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-TITLE-BUTTON-BEHAVIOUR-ENABLED
   * @param uilTitleButtonBehaviourEnabled new value to conclude for UIL-TITLE-BUTTON-BEHAVIOUR-ENABLED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilTitleButtonBehaviourEnabled(java.lang.Object uilTitleButtonBehaviourEnabled) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- UIL-TITLE-BUTTON-CALLBACK
   * @return the value of the UIL-TITLE-BUTTON-CALLBACK attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-TITLE-BUTTON-CALLBACK is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilTitleButtonCallback() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-TITLE-BUTTON-CALLBACK
   * @param uilTitleButtonCallback new value to conclude for UIL-TITLE-BUTTON-CALLBACK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilTitleButtonCallback(java.lang.Object uilTitleButtonCallback) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _UIL-MOVEMENT-IN-PROGRESS
   * @return the value of the _UIL-MOVEMENT-IN-PROGRESS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _UIL-MOVEMENT-IN-PROGRESS is : 
   * BooleanTruthValue
   *
   */
  public boolean get_uilMovementInProgress() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _UIL-MOVEMENT-IN-PROGRESS
   * @param _uilMovementInProgress new value to conclude for _UIL-MOVEMENT-IN-PROGRESS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_uilMovementInProgress(boolean _uilMovementInProgress) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _UIL-X-ARCHIVE
   * @return the value of the _UIL-X-ARCHIVE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _UIL-X-ARCHIVE is : 
   * Integer
   *
   */
  public int get_uilXArchive() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _UIL-X-ARCHIVE
   * @param _uilXArchive new value to conclude for _UIL-X-ARCHIVE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_uilXArchive(int _uilXArchive) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _UIL-Y-ARCHIVE
   * @return the value of the _UIL-Y-ARCHIVE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _UIL-Y-ARCHIVE is : 
   * Integer
   *
   */
  public int get_uilYArchive() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _UIL-Y-ARCHIVE
   * @param _uilYArchive new value to conclude for _UIL-Y-ARCHIVE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_uilYArchive(int _uilYArchive) throws G2AccessException;

}
