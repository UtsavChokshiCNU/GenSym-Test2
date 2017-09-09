/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      NewTable.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:04:15 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface NewTable extends com.gensym.classes.Block {

  public static final Symbol NEW_TABLE_ = com.gensym.util.symbol.G2ClassSymbols.NEW_TABLE_;
  static final Symbol g2ClassName = NEW_TABLE_;
  static final Symbol[] classInheritancePath = new Symbol[] {NEW_TABLE_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- DEFAULT-CELL-FORMAT
   * @return the value of the DEFAULT-CELL-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DEFAULT-CELL-FORMAT is : 
   * (OR NoItem
      (Structure 
        BACKGROUND-COLOR
          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL 
                  CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN 
                  GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN 
                  PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE 
                  VIOLET VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY 
                  AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD BEIGE 
                  LIGHT-PINK EXTRA-LIGHT-GRAY)
        LINE-COLOR
          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL 
                  CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN 
                  GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN 
                  PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE 
                  VIOLET VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY 
                  AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD BEIGE 
                  LIGHT-PINK EXTRA-LIGHT-GRAY)
        BORDER-COLOR
          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL 
                  CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN 
                  GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN 
                  PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE 
                  VIOLET VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY 
                  AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD BEIGE 
                  LIGHT-PINK EXTRA-LIGHT-GRAY)
        TEXT-COLOR
          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL 
                  CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN 
                  GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN 
                  PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE 
                  VIOLET VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY 
                  AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD BEIGE 
                  LIGHT-PINK EXTRA-LIGHT-GRAY)
        TEXT-ALIGNMENT
          (MEMBER LEFT CENTER RIGHT)
        TEXT-SIZE
          (MEMBER SMALL LARGE EXTRA-LARGE)
        WIDTH Integer
        HEIGHT Integer))
   *
   */
  public com.gensym.util.Structure getDefaultCellFormat() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DEFAULT-CELL-FORMAT
   * @param defaultCellFormat new value to conclude for DEFAULT-CELL-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDefaultCellFormat(com.gensym.util.Structure defaultCellFormat) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DEFAULT-EVALUATION-SETTING
   * @return the value of the DEFAULT-EVALUATION-SETTING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DEFAULT-EVALUATION-SETTING is : 
   * (OR NoItem
      (Structure 
        PRIORITY
          (MEMBER 1 2 3 4 5 6 7 8 9 10)
        SCAN-INTERVAL Quantity
        INITIAL-SCAN-WAIT-INTERVAL Quantity
        VALUE-DOMAIN
          (MEMBER INFERENCE-ENGINE G2-SIMULATOR)
        UPDATE-ONLY-WHEN-SHOWN BooleanTruthValue
        TRACE-MESSAGE-LEVEL
          (MEMBER 0 1 2 3)
        WARNING-MESSAGE-LEVEL
          (MEMBER 0 1 2 3)
        BREAK-MESSAGE-LEVEL
          (MEMBER 0 1 2 3)
        TIME-OUT-WHEN-REQUESTING-DATA-SEEKING Integer
        MAY-REQUEST-EVENT-UPDATES BooleanTruthValue
        MAY-REQUEST-DATA-SEEKING BooleanTruthValue
        MAY-PROVIDE-DATA-ON-REQUEST BooleanTruthValue
        MAY-PROVIDE-EVENT-UPDATES BooleanTruthValue))
   *
   */
  public com.gensym.util.Structure getDefaultEvaluationSetting() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DEFAULT-EVALUATION-SETTING
   * @param defaultEvaluationSetting new value to conclude for DEFAULT-EVALUATION-SETTING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDefaultEvaluationSetting(com.gensym.util.Structure defaultEvaluationSetting) throws G2AccessException;

}
