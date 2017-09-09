/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      MenuParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:19 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class MenuParametersImpl extends com.gensym.classes.SystemTableImpl implements MenuParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public MenuParametersImpl() {
    super();
  }

  public MenuParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public MenuParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- ALIGNMENT-FOR-MENU-CHOICES
   * @param alignmentForMenuChoices new value to conclude for ALIGNMENT-FOR-MENU-CHOICES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAlignmentForMenuChoices(com.gensym.util.Symbol alignmentForMenuChoices) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ALIGNMENT_FOR_MENU_CHOICES_, alignmentForMenuChoices);
  }

  /**
   * Generated Property Getter for attribute -- ALIGNMENT-FOR-MENU-CHOICES
   * @return the value of the ALIGNMENT-FOR-MENU-CHOICES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getAlignmentForMenuChoices() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ALIGNMENT_FOR_MENU_CHOICES_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- WHEN-TO-ALLOW-MULTIPLE-MENUS
   * @param whenToAllowMultipleMenus new value to conclude for WHEN-TO-ALLOW-MULTIPLE-MENUS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setWhenToAllowMultipleMenus(com.gensym.util.Symbol whenToAllowMultipleMenus) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.WHEN_TO_ALLOW_MULTIPLE_MENUS_, whenToAllowMultipleMenus);
  }

  /**
   * Generated Property Getter for attribute -- WHEN-TO-ALLOW-MULTIPLE-MENUS
   * @return the value of the WHEN-TO-ALLOW-MULTIPLE-MENUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getWhenToAllowMultipleMenus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.WHEN_TO_ALLOW_MULTIPLE_MENUS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- WALKING-MENUS?
   * @param walkingMenus new value to conclude for WALKING-MENUS?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setWalkingMenus(boolean walkingMenus) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.WALKING_MENUSQ_, new Boolean (walkingMenus));
  }

  /**
   * Generated Property Getter for attribute -- WALKING-MENUS?
   * @return the value of the WALKING-MENUS? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getWalkingMenus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.WALKING_MENUSQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR
   * @param automaticallyShowDeveloperMenuBar new value to conclude for AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAutomaticallyShowDeveloperMenuBar(com.gensym.util.Structure automaticallyShowDeveloperMenuBar) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.AUTOMATICALLY_SHOW_DEVELOPER_MENU_BAR_, automaticallyShowDeveloperMenuBar);
  }

  /**
   * Generated Property Getter for attribute -- AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR
   * @return the value of the AUTOMATICALLY-SHOW-DEVELOPER-MENU-BAR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getAutomaticallyShowDeveloperMenuBar() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.AUTOMATICALLY_SHOW_DEVELOPER_MENU_BAR_);
    return (com.gensym.util.Structure)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
