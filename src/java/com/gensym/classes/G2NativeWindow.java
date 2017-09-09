/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2NativeWindow.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:47:34 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2NativeWindow extends com.gensym.classes.Item, com.gensym.classes.Entity {

  public static final Symbol G2_NATIVE_WINDOW_ = com.gensym.util.symbol.G2ClassSymbols.G2_NATIVE_WINDOW_;
  static final Symbol g2ClassName = G2_NATIVE_WINDOW_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2_NATIVE_WINDOW_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- NATIVE-WINDOW-LEFT
   * @return the value of the NATIVE-WINDOW-LEFT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NATIVE-WINDOW-LEFT is : 
   * Integer
   *
   */
  public int getNativeWindowLeft() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NATIVE-WINDOW-TOP
   * @return the value of the NATIVE-WINDOW-TOP attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NATIVE-WINDOW-TOP is : 
   * Integer
   *
   */
  public int getNativeWindowTop() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NATIVE-WINDOW-WIDTH
   * @return the value of the NATIVE-WINDOW-WIDTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NATIVE-WINDOW-WIDTH is : 
   * Integer
   *
   */
  public int getNativeWindowWidth() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NATIVE-WINDOW-HEIGHT
   * @return the value of the NATIVE-WINDOW-HEIGHT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NATIVE-WINDOW-HEIGHT is : 
   * Integer
   *
   */
  public int getNativeWindowHeight() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NATIVE-WINDOW-STATE
   * @return the value of the NATIVE-WINDOW-STATE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NATIVE-WINDOW-STATE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getNativeWindowState() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-WINDOW-OF-VIEW
   * @return the value of the G2-WINDOW-OF-VIEW attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-WINDOW-OF-VIEW is : 
   * (OR NoItem
      (Class G2-WINDOW))
   *
   */
  public com.gensym.classes.G2Window getG2WindowOfView() throws G2AccessException;

}
