/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilDialogTitleImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:07:45 EDT 2007
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

public class UilDialogTitleImpl extends com.gensym.classes.modules.uilroot.UilTextImpl implements UilDialogTitle {


  static final long serialVersionUID = 2L;
  private static final Symbol UIL_JUSTIFICATION_ = Symbol.intern ("UIL-JUSTIFICATION");
  private static final Symbol UIL_TITLE_BUTTON_BEHAVIOUR_ENABLED_ = Symbol.intern ("UIL-TITLE-BUTTON-BEHAVIOUR-ENABLED");
  private static final Symbol UIL_TITLE_BUTTON_CALLBACK_ = Symbol.intern ("UIL-TITLE-BUTTON-CALLBACK");
  private static final Symbol _UIL_MOVEMENT_IN_PROGRESS_ = Symbol.intern ("_UIL-MOVEMENT-IN-PROGRESS");
  private static final Symbol _UIL_X_ARCHIVE_ = Symbol.intern ("_UIL-X-ARCHIVE");
  private static final Symbol _UIL_Y_ARCHIVE_ = Symbol.intern ("_UIL-Y-ARCHIVE");

  /* Generated constructors */

  public UilDialogTitleImpl() {
    super();
  }

  public UilDialogTitleImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public UilDialogTitleImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UIL-JUSTIFICATION
   * @param uilJustification new value to conclude for UIL-JUSTIFICATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilJustification(java.lang.Object uilJustification) throws G2AccessException {
    setAttributeValue (UIL_JUSTIFICATION_, uilJustification);
  }

  /**
   * Generated Property Getter for attribute -- UIL-JUSTIFICATION
   * @return the value of the UIL-JUSTIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilJustification() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_JUSTIFICATION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-TITLE-BUTTON-BEHAVIOUR-ENABLED
   * @param uilTitleButtonBehaviourEnabled new value to conclude for UIL-TITLE-BUTTON-BEHAVIOUR-ENABLED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilTitleButtonBehaviourEnabled(java.lang.Object uilTitleButtonBehaviourEnabled) throws G2AccessException {
    setAttributeValue (UIL_TITLE_BUTTON_BEHAVIOUR_ENABLED_, uilTitleButtonBehaviourEnabled);
  }

  /**
   * Generated Property Getter for attribute -- UIL-TITLE-BUTTON-BEHAVIOUR-ENABLED
   * @return the value of the UIL-TITLE-BUTTON-BEHAVIOUR-ENABLED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilTitleButtonBehaviourEnabled() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_TITLE_BUTTON_BEHAVIOUR_ENABLED_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- UIL-TITLE-BUTTON-CALLBACK
   * @param uilTitleButtonCallback new value to conclude for UIL-TITLE-BUTTON-CALLBACK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUilTitleButtonCallback(java.lang.Object uilTitleButtonCallback) throws G2AccessException {
    setAttributeValue (UIL_TITLE_BUTTON_CALLBACK_, uilTitleButtonCallback);
  }

  /**
   * Generated Property Getter for attribute -- UIL-TITLE-BUTTON-CALLBACK
   * @return the value of the UIL-TITLE-BUTTON-CALLBACK attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getUilTitleButtonCallback() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (UIL_TITLE_BUTTON_CALLBACK_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- _UIL-MOVEMENT-IN-PROGRESS
   * @param _uilMovementInProgress new value to conclude for _UIL-MOVEMENT-IN-PROGRESS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void set_uilMovementInProgress(boolean _uilMovementInProgress) throws G2AccessException {
    setAttributeValue (_UIL_MOVEMENT_IN_PROGRESS_, new Boolean (_uilMovementInProgress));
  }

  /**
   * Generated Property Getter for attribute -- _UIL-MOVEMENT-IN-PROGRESS
   * @return the value of the _UIL-MOVEMENT-IN-PROGRESS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean get_uilMovementInProgress() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_UIL_MOVEMENT_IN_PROGRESS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- _UIL-X-ARCHIVE
   * @param _uilXArchive new value to conclude for _UIL-X-ARCHIVE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void set_uilXArchive(int _uilXArchive) throws G2AccessException {
    setAttributeValue (_UIL_X_ARCHIVE_, new Integer (_uilXArchive));
  }

  /**
   * Generated Property Getter for attribute -- _UIL-X-ARCHIVE
   * @return the value of the _UIL-X-ARCHIVE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int get_uilXArchive() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_UIL_X_ARCHIVE_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- _UIL-Y-ARCHIVE
   * @param _uilYArchive new value to conclude for _UIL-Y-ARCHIVE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void set_uilYArchive(int _uilYArchive) throws G2AccessException {
    setAttributeValue (_UIL_Y_ARCHIVE_, new Integer (_uilYArchive));
  }

  /**
   * Generated Property Getter for attribute -- _UIL-Y-ARCHIVE
   * @return the value of the _UIL-Y-ARCHIVE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int get_uilYArchive() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_UIL_Y_ARCHIVE_);
    return ((Integer)retnValue).intValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
