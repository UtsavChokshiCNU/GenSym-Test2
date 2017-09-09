/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      FreeText.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:43:49 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface FreeText extends com.gensym.classes.Item, com.gensym.classes.TextBox {

  public static final Symbol FREE_TEXT_ = com.gensym.util.symbol.G2ClassSymbols.FREE_TEXT_;
  static final Symbol g2ClassName = FREE_TEXT_;
  static final Symbol[] classInheritancePath = new Symbol[] {FREE_TEXT_, ITEM_, TEXT_BOX_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- MINIMUM-SIZE-IN-WORKSPACE
   * @return the value of the MINIMUM-SIZE-IN-WORKSPACE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MINIMUM-SIZE-IN-WORKSPACE is : 
   * (OR NoItem
      (Structure 
        WIDTH
          (OR Integer
              (MEMBER NONE))
        HEIGHT
          (OR Integer
              (MEMBER NONE))))
   *
   */
  public com.gensym.util.Structure getMinimumSizeInWorkspace() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MINIMUM-SIZE-IN-WORKSPACE
   * @param minimumSizeInWorkspace new value to conclude for MINIMUM-SIZE-IN-WORKSPACE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMinimumSizeInWorkspace(com.gensym.util.Structure minimumSizeInWorkspace) throws G2AccessException;

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

  /**
   * Generated Property Getter for attribute -- CURRENT-ATTRIBUTE-DISPLAYS
   * @return the value of the CURRENT-ATTRIBUTE-DISPLAYS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CURRENT-ATTRIBUTE-DISPLAYS is : 
   * (OR NoItem
      (Sequence 
        (Structure 
          ATTRIBUTE-LIST
            (Sequence 
              (Structure 
                ATTRIBUTE Symbol
                QUALIFIED-CLASS Symbol
                DISPLAY-WITH-NAME BooleanTruthValue
                DISPLAY-FORMAT
                  (MEMBER INTERVAL DEFAULT TIME-STAMP FREE-TEXT)
                ATTRIBUTE-IS-HIDDEN BooleanTruthValue
                ATTRIBUTE-IS-IN-VALUE-FORMAT BooleanTruthValue
                ATTRIBUTE-IS-IN-SUMMARY-FORMAT BooleanTruthValue)
              1))
          TEXT-COLOR
            (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE CORAL 
                    CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY GREEN 
                    GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA MAROON 
                    MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN 
                    PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE 
                    VIOLET VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE 
                    IVORY AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE LIGHT-CYAN 
                    PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD BEIGE 
                    LIGHT-PINK EXTRA-LIGHT-GRAY)
          POSITION
            (OR (MEMBER AT-STANDARD-POSITION)
                (Structure 
                  X-OFFSET Integer
                  Y-OFFSET Integer)))
        1)))
   *
   */
  public com.gensym.util.Sequence getCurrentAttributeDisplays() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CURRENT-ATTRIBUTE-DISPLAYS
   * @param currentAttributeDisplays new value to conclude for CURRENT-ATTRIBUTE-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setCurrentAttributeDisplays(com.gensym.util.Sequence currentAttributeDisplays) throws G2AccessException;

}
