/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      MenuParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:18 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface MenuParameters extends com.gensym.classes.SystemTable {

  public static final Symbol MENU_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.MENU_PARAMETERS_;
  static final Symbol g2ClassName = MENU_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {MENU_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- ALIGNMENT-FOR-MENU-CHOICES
   * @return the value of the ALIGNMENT-FOR-MENU-CHOICES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ALIGNMENT-FOR-MENU-CHOICES is : 
   * (MEMBER LEFT CENTER RIGHT)
   *
   */
  public com.gensym.util.Symbol getAlignmentForMenuChoices() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ALIGNMENT-FOR-MENU-CHOICES
   * @param alignmentForMenuChoices new value to conclude for ALIGNMENT-FOR-MENU-CHOICES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAlignmentForMenuChoices(com.gensym.util.Symbol alignmentForMenuChoices) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- WHEN-TO-ALLOW-MULTIPLE-MENUS
   * @return the value of the WHEN-TO-ALLOW-MULTIPLE-MENUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for WHEN-TO-ALLOW-MULTIPLE-MENUS is : 
   * (MEMBER NEVER ALWAYS FOR-DIFFERENT-SELECTIONS)
   *
   */
  public com.gensym.util.Symbol getWhenToAllowMultipleMenus() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- WHEN-TO-ALLOW-MULTIPLE-MENUS
   * @param whenToAllowMultipleMenus new value to conclude for WHEN-TO-ALLOW-MULTIPLE-MENUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setWhenToAllowMultipleMenus(com.gensym.util.Symbol whenToAllowMultipleMenus) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- WALKING-MENUS?
   * @return the value of the WALKING-MENUS? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for WALKING-MENUS? is : 
   * BooleanTruthValue
   *
   */
  public boolean getWalkingMenus() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- WALKING-MENUS?
   * @param walkingMenus new value to conclude for WALKING-MENUS?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setWalkingMenus(boolean walkingMenus) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR
   * @return the value of the AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR is : 
   * (Structure 
    EVENTS
      (Sequence Symbol)
    MODES
      (Sequence Symbol))
   *
   */
  public com.gensym.util.Structure getAutomaticallyShowDeveloperMenuBar() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR
   * @param automaticallyShowDeveloperMenuBar new value to conclude for AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAutomaticallyShowDeveloperMenuBar(com.gensym.util.Structure automaticallyShowDeveloperMenuBar) throws G2AccessException;

}
