/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ColorParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:37:19 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface ColorParameters extends com.gensym.classes.SystemTable {

  public static final Symbol COLOR_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.COLOR_PARAMETERS_;
  static final Symbol g2ClassName = COLOR_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {COLOR_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- COLOR-MENU-ORDERING
   * @return the value of the COLOR-MENU-ORDERING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for COLOR-MENU-ORDERING is : 
   * (MEMBER INTENSITY ALPHABETIC HUE)
   *
   */
  public com.gensym.util.Symbol getColorMenuOrdering() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- COLOR-MENU-ORDERING
   * @param colorMenuOrdering new value to conclude for COLOR-MENU-ORDERING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setColorMenuOrdering(com.gensym.util.Symbol colorMenuOrdering) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- COLORS-ON-1ST-LEVEL-COLOR-MENU
   * @return the value of the COLORS-ON-1ST-LEVEL-COLOR-MENU attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for COLORS-ON-1ST-LEVEL-COLOR-MENU is : 
   * (OR (MEMBER ALL NONE STANDARD-SET)
      (Sequence 
        (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
                DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN 
                GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK 
                PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET 
                VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE 
                LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD 
                LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD BEIGE LIGHT-PINK 
                EXTRA-LIGHT-GRAY)
        1)))
   *
   */
  public java.lang.Object getColorsOn1stLevelColorMenu() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- COLORS-ON-1ST-LEVEL-COLOR-MENU
   * @param colorsOn1stLevelColorMenu new value to conclude for COLORS-ON-1ST-LEVEL-COLOR-MENU
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setColorsOn1stLevelColorMenu(java.lang.Object colorsOn1stLevelColorMenu) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- COLORS-ON-2ND-LEVEL-COLOR-MENU
   * @return the value of the COLORS-ON-2ND-LEVEL-COLOR-MENU attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for COLORS-ON-2ND-LEVEL-COLOR-MENU is : 
   * (OR (MEMBER ALL NONE STANDARD-SET)
      (Sequence 
        (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
                DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN 
                GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK 
                PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET 
                VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE 
                LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD 
                LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD BEIGE LIGHT-PINK 
                EXTRA-LIGHT-GRAY)
        1)))
   *
   */
  public java.lang.Object getColorsOn2ndLevelColorMenu() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- COLORS-ON-2ND-LEVEL-COLOR-MENU
   * @param colorsOn2ndLevelColorMenu new value to conclude for COLORS-ON-2ND-LEVEL-COLOR-MENU
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setColorsOn2ndLevelColorMenu(java.lang.Object colorsOn2ndLevelColorMenu) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-COLUMNS-FOR-1ST-LEVEL-COLOR-MENU
   * @return the value of the NUMBER-OF-COLUMNS-FOR-1ST-LEVEL-COLOR-MENU attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NUMBER-OF-COLUMNS-FOR-1ST-LEVEL-COLOR-MENU is : 
   * (MEMBER 1 2 3 4 5 6 7)
   *
   */
  public com.gensym.util.Symbol getNumberOfColumnsFor1stLevelColorMenu() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-COLUMNS-FOR-1ST-LEVEL-COLOR-MENU
   * @param numberOfColumnsFor1stLevelColorMenu new value to conclude for NUMBER-OF-COLUMNS-FOR-1ST-LEVEL-COLOR-MENU
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNumberOfColumnsFor1stLevelColorMenu(com.gensym.util.Symbol numberOfColumnsFor1stLevelColorMenu) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-COLUMNS-FOR-2ND-LEVEL-COLOR-MENU
   * @return the value of the NUMBER-OF-COLUMNS-FOR-2ND-LEVEL-COLOR-MENU attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NUMBER-OF-COLUMNS-FOR-2ND-LEVEL-COLOR-MENU is : 
   * (MEMBER 1 2 3 4 5 6 7)
   *
   */
  public com.gensym.util.Symbol getNumberOfColumnsFor2ndLevelColorMenu() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-COLUMNS-FOR-2ND-LEVEL-COLOR-MENU
   * @param numberOfColumnsFor2ndLevelColorMenu new value to conclude for NUMBER-OF-COLUMNS-FOR-2ND-LEVEL-COLOR-MENU
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNumberOfColumnsFor2ndLevelColorMenu(com.gensym.util.Symbol numberOfColumnsFor2ndLevelColorMenu) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DISMISS-COLOR-MENU-AFTER-CHOOSING?
   * @return the value of the DISMISS-COLOR-MENU-AFTER-CHOOSING? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DISMISS-COLOR-MENU-AFTER-CHOOSING? is : 
   * BooleanTruthValue
   *
   */
  public boolean getDismissColorMenuAfterChoosing() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DISMISS-COLOR-MENU-AFTER-CHOOSING?
   * @param dismissColorMenuAfterChoosing new value to conclude for DISMISS-COLOR-MENU-AFTER-CHOOSING?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDismissColorMenuAfterChoosing(boolean dismissColorMenuAfterChoosing) throws G2AccessException;

}
