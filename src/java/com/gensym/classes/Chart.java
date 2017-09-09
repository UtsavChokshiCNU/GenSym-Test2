/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Chart.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:36:58 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Chart extends com.gensym.classes.Item, com.gensym.classes.Block {

  public static final Symbol CHART_ = com.gensym.util.symbol.G2ClassSymbols.CHART_;
  static final Symbol g2ClassName = CHART_;
  static final Symbol[] classInheritancePath = new Symbol[] {CHART_, ITEM_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- CHART-STYLE
   * @return the value of the CHART-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CHART-STYLE is : 
   * (MEMBER LINE-CHART-STYLE COLUMN-CHART-STYLE SCATTER-CHART-STYLE)
   *
   */
  public com.gensym.util.Symbol getChartStyle() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CHART-STYLE
   * @param chartStyle new value to conclude for CHART-STYLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setChartStyle(com.gensym.util.Symbol chartStyle) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DATA-SERIES
   * @return the value of the DATA-SERIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DATA-SERIES is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getDataSeries() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DATA-SERIES
   * @param dataSeries new value to conclude for DATA-SERIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDataSeries(java.lang.String dataSeries) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ANNOTATIONS
   * @return the value of the ANNOTATIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ANNOTATIONS is : 
   * (OR NoItem
      (Structure 
        DEFAULT-FEATURES
          (Structure 
            LINE-COLOR
              (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE 
                      CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY 
                      GREEN GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA 
                      MAROON MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE 
                      PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE 
                      TURQUOISE VIOLET VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN 
                      ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE 
                      LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                      BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
            TEXT-COLOR
              (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE 
                      CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY 
                      GREEN GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA 
                      MAROON MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE 
                      PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE 
                      TURQUOISE VIOLET VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN 
                      ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE 
                      LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                      BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
            BACKGROUND-COLOR
              (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE 
                      CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY 
                      GREEN GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA 
                      MAROON MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE 
                      PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE 
                      TURQUOISE VIOLET VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN 
                      ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE 
                      LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                      BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
            BORDER-COLOR
              (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE 
                      CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY 
                      GREEN GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA 
                      MAROON MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE 
                      PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE 
                      TURQUOISE VIOLET VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN 
                      ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE 
                      LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                      BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
            GRID-COLOR
              (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE 
                      CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY 
                      GREEN GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA 
                      MAROON MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE 
                      PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE 
                      TURQUOISE VIOLET VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN 
                      ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE 
                      LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                      BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
            GRID-VISIBLE BooleanTruthValue
            TEXT-ALIGNMENT Symbol
            TEXT-SIZE Symbol
            WIDTH Quantity
            HEIGHT Quantity
            INDICATOR Symbol
            INDICATOR-VISIBLE BooleanTruthValue
            CONNECTION-LINE-VISIBLE BooleanTruthValue
            LINE-FROM-LAST-TO-FIRST-POINT-VISIBLE BooleanTruthValue
            AXIS-MINIMUM Quantity
            AXIS-MAXIMUM Quantity
            AXIS-CROSSOVER Quantity
            NUMBER-OF-TICKMARKS Quantity
            TICKMARK-INTERVAL Quantity
            NUMBER-OF-SIGNIFICANT-DIGITS Quantity)
        DATA-POINT-FEATURES
          (Sequence 
            (Structure 
              ANNOTATIONS
                (Sequence 
                  (Structure 
                    ATTRIBUTES
                      (Structure 
                        LINE-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        TEXT-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        BACKGROUND-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        BORDER-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        GRID-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        GRID-VISIBLE BooleanTruthValue
                        TEXT-ALIGNMENT Symbol
                        TEXT-SIZE Symbol
                        WIDTH Quantity
                        HEIGHT Quantity
                        INDICATOR Symbol
                        INDICATOR-VISIBLE BooleanTruthValue
                        CONNECTION-LINE-VISIBLE BooleanTruthValue
                        LINE-FROM-LAST-TO-FIRST-POINT-VISIBLE BooleanTruthValue
                        AXIS-MINIMUM Quantity
                        AXIS-MAXIMUM Quantity
                        AXIS-CROSSOVER Quantity
                        NUMBER-OF-TICKMARKS Quantity
                        TICKMARK-INTERVAL Quantity
                        NUMBER-OF-SIGNIFICANT-DIGITS Quantity)
                    PATH
                      (Sequence 
                        (Structure 
                          PART-NAME
                            (OR (MEMBER CHART-DATA-POINT DATA-SERIES AXIS)
                                Symbol)
                          PART-INDEX Quantity)
                        1)))
                  1)))
            1))
        DATA-SERIES-FEATURES
          (Sequence 
            (Structure 
              INDEX Integer
              ANNOTATIONS
                (Sequence 
                  (Structure 
                    ATTRIBUTES
                      (Structure 
                        LINE-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        TEXT-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        BACKGROUND-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        BORDER-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        GRID-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        GRID-VISIBLE BooleanTruthValue
                        TEXT-ALIGNMENT Symbol
                        TEXT-SIZE Symbol
                        WIDTH Quantity
                        HEIGHT Quantity
                        INDICATOR Symbol
                        INDICATOR-VISIBLE BooleanTruthValue
                        CONNECTION-LINE-VISIBLE BooleanTruthValue
                        LINE-FROM-LAST-TO-FIRST-POINT-VISIBLE BooleanTruthValue
                        AXIS-MINIMUM Quantity
                        AXIS-MAXIMUM Quantity
                        AXIS-CROSSOVER Quantity
                        NUMBER-OF-TICKMARKS Quantity
                        TICKMARK-INTERVAL Quantity
                        NUMBER-OF-SIGNIFICANT-DIGITS Quantity)
                    PATH
                      (Sequence 
                        (Structure 
                          PART-NAME
                            (OR (MEMBER CHART-DATA-POINT DATA-SERIES AXIS)
                                Symbol)
                          PART-INDEX Quantity)
                        1)))
                  1)))
            1))
        AXIS-FEATURES
          (Sequence 
            (Structure 
              INDEX Integer
              ANNOTATIONS
                (Sequence 
                  (Structure 
                    ATTRIBUTES
                      (Structure 
                        LINE-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        TEXT-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        BACKGROUND-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        BORDER-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        GRID-COLOR
                          (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                                  CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY 
                                  FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED 
                                  KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                                  MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                                  ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE 
                                  SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE 
                                  YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER 
                                  LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                                  PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                                  BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
                        GRID-VISIBLE BooleanTruthValue
                        TEXT-ALIGNMENT Symbol
                        TEXT-SIZE Symbol
                        WIDTH Quantity
                        HEIGHT Quantity
                        INDICATOR Symbol
                        INDICATOR-VISIBLE BooleanTruthValue
                        CONNECTION-LINE-VISIBLE BooleanTruthValue
                        LINE-FROM-LAST-TO-FIRST-POINT-VISIBLE BooleanTruthValue
                        AXIS-MINIMUM Quantity
                        AXIS-MAXIMUM Quantity
                        AXIS-CROSSOVER Quantity
                        NUMBER-OF-TICKMARKS Quantity
                        TICKMARK-INTERVAL Quantity
                        NUMBER-OF-SIGNIFICANT-DIGITS Quantity)
                    PATH
                      (Sequence 
                        (Structure 
                          PART-NAME
                            (OR (MEMBER CHART-DATA-POINT DATA-SERIES AXIS)
                                Symbol)
                          PART-INDEX Quantity)
                        1)))
                  1)))
            1))))
   *
   */
  public com.gensym.util.Structure getAnnotations() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ANNOTATIONS
   * @param annotations new value to conclude for ANNOTATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAnnotations(com.gensym.util.Structure annotations) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CHART-DATA-SERIES
   * @return the value of the CHART-DATA-SERIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CHART-DATA-SERIES is : 
   * (OR NoItem
      (Sequence 
        (Structure 
          DATA-SERIES-CACHE-1
            (Sequence Float 0)
          DATA-SERIES-CACHE-2
            (Sequence Float 0)
          DATA-SERIES-SOURCE-KIND
            (MEMBER AXIS-DATA-SERIES MALFORMED-DATA-SERIES FLOAT-AND-FLOAT-FROM-DATA-CACHES))
        0)))
   *
   */
  public com.gensym.util.Sequence getChartDataSeries() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CHART-AXIS-COMPUTED-DETAILS
   * @return the value of the CHART-AXIS-COMPUTED-DETAILS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CHART-AXIS-COMPUTED-DETAILS is : 
   * (OR NoItem
      (Structure 
        AXIS-1
          (Structure 
            AXIS-IS-DISCRETE BooleanTruthValue
            MAX-DIGITS-IN-EXPONENT Integer
            MAX-DIGITS-BEFORE-POINT Integer
            MAX-DIGITS-AFTER-POINT Integer
            AXIS-HEADING Symbol
            AXIS-CROSSOVER Float
            MINIMUM Float
            MAXIMUM Float)
        AXIS-2
          (Structure 
            AXIS-IS-DISCRETE BooleanTruthValue
            MAX-DIGITS-IN-EXPONENT Integer
            MAX-DIGITS-BEFORE-POINT Integer
            MAX-DIGITS-AFTER-POINT Integer
            AXIS-HEADING Symbol
            AXIS-CROSSOVER Float
            MINIMUM Float
            MAXIMUM Float)))
   *
   */
  public com.gensym.util.Structure getChartAxisComputedDetails() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- EVALUATION-ATTRIBUTES
   * @return the value of the EVALUATION-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for EVALUATION-ATTRIBUTES is : 
   * (OR NoItem
      (Structure 
        MAY-REFER-TO-INACTIVE-ITEMS BooleanTruthValue
        MAY-RUN-WHILE-INACTIVE BooleanTruthValue))
   *
   */
  public com.gensym.util.Structure getEvaluationAttributes() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- EVALUATION-ATTRIBUTES
   * @param evaluationAttributes new value to conclude for EVALUATION-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEvaluationAttributes(com.gensym.util.Structure evaluationAttributes) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SIZE-IN-WORKSPACE
   * @return the value of the SIZE-IN-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SIZE-IN-WORKSPACE is : 
   * (OR NoItem
      (Structure 
        WIDTH Quantity
        HEIGHT Quantity))
   *
   */
  public com.gensym.util.Structure getSizeInWorkspace() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SIZE-IN-WORKSPACE
   * @param sizeInWorkspace new value to conclude for SIZE-IN-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSizeInWorkspace(com.gensym.util.Structure sizeInWorkspace) throws G2AccessException;

}
