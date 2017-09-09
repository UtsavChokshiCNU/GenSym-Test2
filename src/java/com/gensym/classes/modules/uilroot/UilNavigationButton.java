/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilNavigationButton.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:14:29 EDT 2007
 *
 */


package com.gensym.classes.modules.uilroot;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface UilNavigationButton extends com.gensym.classes.modules.uilroot.UilWorkspaceButton {

  public static final Symbol UIL_NAVIGATION_BUTTON_ = Symbol.intern ("UIL-NAVIGATION-BUTTON");
  static final Symbol g2ClassName = UIL_NAVIGATION_BUTTON_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_NAVIGATION_BUTTON_, UIL_WORKSPACE_BUTTON_, UIL_ICON_BUTTON_, UIL_BUTTON_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UIL-RELEASE-BUTTON-AFTER-SELECTION
   * @return the value of the UIL-RELEASE-BUTTON-AFTER-SELECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UIL-RELEASE-BUTTON-AFTER-SELECTION is : 
   * (OR ItemOrValue
      NoItem)
   *
   */
  public java.lang.Object getUilReleaseButtonAfterSelection() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UIL-RELEASE-BUTTON-AFTER-SELECTION
   * @param uilReleaseButtonAfterSelection new value to conclude for UIL-RELEASE-BUTTON-AFTER-SELECTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUilReleaseButtonAfterSelection(java.lang.Object uilReleaseButtonAfterSelection) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * UIL-NAVIGATION-BUTTON::UPP-SET-BUTTON-LABEL
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-NAVIGATION-BUTTON,arg1:TEXT) = ()
   */
  @Override
  public  void uppSetButtonLabel(java.lang.String arg1) throws G2AccessException;
  
}
