/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      DrawingParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:40:35 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface DrawingParameters extends com.gensym.classes.SystemTable {

  public static final Symbol DRAWING_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.DRAWING_PARAMETERS_;
  static final Symbol g2ClassName = DRAWING_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {DRAWING_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- ALLOW-SCHEDULED-DRAWING?
   * @return the value of the ALLOW-SCHEDULED-DRAWING? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ALLOW-SCHEDULED-DRAWING? is : 
   * BooleanTruthValue
   *
   */
  public boolean getAllowScheduledDrawing() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ALLOW-SCHEDULED-DRAWING?
   * @param allowScheduledDrawing new value to conclude for ALLOW-SCHEDULED-DRAWING?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAllowScheduledDrawing(boolean allowScheduledDrawing) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PAINT-MODE?
   * @return the value of the PAINT-MODE? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PAINT-MODE? is : 
   * BooleanTruthValue
   *
   */
  public boolean getPaintMode() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PAINT-MODE?
   * @param paintMode new value to conclude for PAINT-MODE?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPaintMode(boolean paintMode) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- IMAGE-PALETTE
   * @return the value of the IMAGE-PALETTE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for IMAGE-PALETTE is : 
   * (OR (MEMBER BLACK-AND-WHITE STANDARD-GRAYS STANDARD-COLORS EXTENDED-GRAYS EXTENDED-COLORS)
      (Structure 
        PALETTE-NAME
          (MEMBER CUSTOM-GRAYS CUSTOM-COLORS)
        IMAGE-NAME Symbol))
   *
   */
  public java.lang.Object getImagePalette() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- IMAGE-PALETTE
   * @param imagePalette new value to conclude for IMAGE-PALETTE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setImagePalette(java.lang.Object imagePalette) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SHOW-SELECTION-HANDLES
   * @return the value of the SHOW-SELECTION-HANDLES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SHOW-SELECTION-HANDLES is : 
   * BooleanTruthValue
   *
   */
  public boolean getShowSelectionHandles() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SHOW-SELECTION-HANDLES
   * @param showSelectionHandles new value to conclude for SHOW-SELECTION-HANDLES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setShowSelectionHandles(boolean showSelectionHandles) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PRIMARY-SELECTION-COLOR
   * @return the value of the PRIMARY-SELECTION-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PRIMARY-SELECTION-COLOR is : 
   * (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
          DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW 
          INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON MEDIUM-AQUAMARINE 
          MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON 
          SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE YELLOW 
          SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE 
          PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW 
          LIGHT-GOLDENROD BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
   *
   */
  public com.gensym.util.Symbol getPrimarySelectionColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PRIMARY-SELECTION-COLOR
   * @param primarySelectionColor new value to conclude for PRIMARY-SELECTION-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPrimarySelectionColor(com.gensym.util.Symbol primarySelectionColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SECONDARY-SELECTION-COLOR
   * @return the value of the SECONDARY-SELECTION-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SECONDARY-SELECTION-COLOR is : 
   * (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL CYAN 
          DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN GREEN-YELLOW 
          INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON MEDIUM-AQUAMARINE 
          MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON 
          SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE YELLOW 
          SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE 
          PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW 
          LIGHT-GOLDENROD BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY)
   *
   */
  public com.gensym.util.Symbol getSecondarySelectionColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SECONDARY-SELECTION-COLOR
   * @param secondarySelectionColor new value to conclude for SECONDARY-SELECTION-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSecondarySelectionColor(com.gensym.util.Symbol secondarySelectionColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ALIGNMENT-GRID
   * @return the value of the ALIGNMENT-GRID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ALIGNMENT-GRID is : 
   * (Structure 
    SPACING
      (OR Integer
          (Sequence Integer 2 3))
    LINE-COLOR Symbol
    LINE-PATTERN
      (MEMBER SOLID DASH DOT LONG-DASH SHORT-DASH COARSE-DOT FINE-DOT)
    SNAP-TO
      (OR Integer
          (Sequence Integer 2 3)))
   *
   */
  public com.gensym.util.Structure getAlignmentGrid() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ALIGNMENT-GRID
   * @param alignmentGrid new value to conclude for ALIGNMENT-GRID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAlignmentGrid(com.gensym.util.Structure alignmentGrid) throws G2AccessException;

}
