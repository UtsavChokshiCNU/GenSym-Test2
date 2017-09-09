/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ActionButton.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:37:57 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.util.Symbol;
import com.gensym.jgi.*;

public interface ActionButton extends com.gensym.classes.Item, com.gensym.classes.GenericActionButton {

  public static final Symbol ACTION_BUTTON_ = com.gensym.util.symbol.G2ClassSymbols.ACTION_BUTTON_;
  static final Symbol g2ClassName = ACTION_BUTTON_;
  static final Symbol[] classInheritancePath = new Symbol[] {ACTION_BUTTON_, ITEM_, GENERIC_ACTION_BUTTON_, BUTTON_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /* Overriden method - INVOKE */
  /**
   * @return true if successful
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public boolean invoke()
       throws G2AccessException;

}
