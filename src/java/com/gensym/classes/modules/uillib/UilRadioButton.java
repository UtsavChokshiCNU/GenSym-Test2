/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilRadioButton.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:05:45 EDT 2007
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

public interface UilRadioButton extends com.gensym.classes.modules.uilroot.UilSelectionButton {

  public static final Symbol UIL_RADIO_BUTTON_ = Symbol.intern ("UIL-RADIO-BUTTON");
  static final Symbol g2ClassName = UIL_RADIO_BUTTON_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_RADIO_BUTTON_, UIL_SELECTION_BUTTON_, UIL_ICON_BUTTON_, UIL_BUTTON_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Auto Generated method for G2 Method
   * UIL-RADIO-BUTTON::UPP-SET-BUTTON-LABEL
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-RADIO-BUTTON,arg1:TEXT) = ()
   */
  @Override
  public  void uppSetButtonLabel(java.lang.String arg1) throws G2AccessException;
  
}
