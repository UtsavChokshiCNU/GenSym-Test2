/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UilCheckBox.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Oct 22 11:05:52 EDT 2007
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

public interface UilCheckBox extends com.gensym.classes.modules.uilroot.UilSelectionBox {

  public static final Symbol UIL_CHECK_BOX_ = Symbol.intern ("UIL-CHECK-BOX");
  static final Symbol g2ClassName = UIL_CHECK_BOX_;
  static final Symbol[] classInheritancePath = new Symbol[] {UIL_CHECK_BOX_, UIL_SELECTION_BOX_, UIL_GROBJ_, UIL_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Auto Generated method for G2 Method
   * UIL-CHECK-BOX::UPP-EXTRACT-VALUE-FROM-ITEM
   * @return the return from calling UPP-EXTRACT-VALUE-FROM-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-CHECK-BOX) = (VALUE,TRUTH-VALUE)
   */
  public  com.gensym.util.Sequence uppExtractValueFromItem() throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * UIL-CHECK-BOX::UPP-EXTRACT-VALUES-FROM-ITEM
   * @return the return from calling UPP-EXTRACT-VALUES-FROM-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS UIL-CHECK-BOX) = (ITEM-OR-VALUE)
   */
  public  java.lang.Object uppExtractValuesFromItem() throws G2AccessException;
  
}
