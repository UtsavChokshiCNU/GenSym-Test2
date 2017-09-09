/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Entity.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:25:50 EDT 2007
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

public interface Entity extends com.gensym.classes.Block {

  public static final Symbol ENTITY_ = com.gensym.util.symbol.G2ClassSymbols.ENTITY_;
  static final Symbol g2ClassName = ENTITY_;
  static final Symbol[] classInheritancePath = new Symbol[] {ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};

  static final Symbol ICON_DESCRIPTION_ = Symbol.intern ("ICON-DESCRIPTION");

  static final Symbol[] staticAttributes = new Symbol[] {ICON_DESCRIPTION_};


  /* Overriden Property - SUBWORKSPACE */
  /**
   * @return this Item's subworkspace, if one exists.
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public KbWorkspace getSubworkspace()
       throws G2AccessException;
  /**
   * @param workspace the KbWorkspace to attempt to set as
   * this Item's subworkspace.  
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call, such as when
   * this Item already has a subworkspace.
   */
  public void setSubworkspace(KbWorkspace workspace)
       throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-DISPLAY-ITEMS
   * @return the value of the ATTRIBUTE-DISPLAY-ITEMS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ATTRIBUTE-DISPLAY-ITEMS is : 
   * (OR (Sequence)
      NoItem)
   *
   */
  public com.gensym.util.Sequence getAttributeDisplayItems() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NAME-BOX-ITEM
   * @return the value of the NAME-BOX-ITEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NAME-BOX-ITEM is : 
   * (OR Value
      NoItem)
   *
   */
  public java.lang.Object getNameBoxItem() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ICON-VARIABLES
   * @return the value of the ICON-VARIABLES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ICON-VARIABLES is : 
   * (OR (Structure)
      NoItem)
   *
   */
  public com.gensym.util.Structure getIconVariables() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ICON-VARIABLES
   * @param iconVariables new value to conclude for ICON-VARIABLES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIconVariables(com.gensym.util.Structure iconVariables) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ICON-COLOR
   * @return the value of the ICON-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ICON-COLOR is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getIconColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ICON-COLOR
   * @param iconColor new value to conclude for ICON-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIconColor(com.gensym.util.Symbol iconColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ICON-REFLECTION
   * @return the value of the ICON-REFLECTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ICON-REFLECTION is : 
   * (OR Symbol
      NoItem)
   *
   */
  public com.gensym.util.Symbol getIconReflection() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ICON-REFLECTION
   * @param iconReflection new value to conclude for ICON-REFLECTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIconReflection(com.gensym.util.Symbol iconReflection) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ICON-HEADING
   * @return the value of the ICON-HEADING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ICON-HEADING is : 
   * Integer
   *
   */
  public int getIconHeading() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ICON-HEADING
   * @param iconHeading new value to conclude for ICON-HEADING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIconHeading(int iconHeading) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ITEM-COLOR-PATTERN
   * @return the value of the ITEM-COLOR-PATTERN attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ITEM-COLOR-PATTERN is : 
   * (Structure)
   *
   */
  public com.gensym.util.Structure getItemColorPattern() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ITEM-COLOR-PATTERN
   * @param itemColorPattern new value to conclude for ITEM-COLOR-PATTERN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setItemColorPattern(com.gensym.util.Structure itemColorPattern) throws G2AccessException;

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

  /**
   * Generated Property Getter for attribute -- NAME-BOX
   * @return the value of the NAME-BOX attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NAME-BOX is : 
   * (OR NoItem
      (Structure 
        COLOR
          (Structure 
            BACKGROUND-COLOR Symbol
            TEXT-COLOR Symbol)
        POSITION
          (OR (MEMBER AT-STANDARD-POSITION)
              (Structure 
                X-OFFSET Integer
                Y-OFFSET Integer))))
   *
   */
  public com.gensym.util.Structure getNameBox() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NAME-BOX
   * @param nameBox new value to conclude for NAME-BOX
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNameBox(com.gensym.util.Structure nameBox) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- STRIPE-COLOR
   * @return the value of the STRIPE-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for STRIPE-COLOR is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getStripeColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- STRIPE-COLOR
   * @param stripeColor new value to conclude for STRIPE-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStripeColor(com.gensym.util.Symbol stripeColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- BORDER-COLOR
   * @return the value of the BORDER-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for BORDER-COLOR is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getBorderColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- BORDER-COLOR
   * @param borderColor new value to conclude for BORDER-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setBorderColor(com.gensym.util.Symbol borderColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TEXT-COLOR
   * @return the value of the TEXT-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TEXT-COLOR is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getTextColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TEXT-COLOR
   * @param textColor new value to conclude for TEXT-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTextColor(com.gensym.util.Symbol textColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FOREGROUND-COLOR
   * @return the value of the FOREGROUND-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FOREGROUND-COLOR is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getForegroundColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FOREGROUND-COLOR
   * @param foregroundColor new value to conclude for FOREGROUND-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setForegroundColor(com.gensym.util.Symbol foregroundColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- BACKGROUND-COLOR
   * @return the value of the BACKGROUND-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for BACKGROUND-COLOR is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getBackgroundColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- BACKGROUND-COLOR
   * @param backgroundColor new value to conclude for BACKGROUND-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setBackgroundColor(com.gensym.util.Symbol backgroundColor) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ICON-DESCRIPTION
   * @return the value of the ICON-DESCRIPTION attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ICON-DESCRIPTION is : 
   * (OR NoItem
      (Structure 
        WIDTH Integer
        HEIGHT Integer
        REGIONS
          (OR NoItem
              (Sequence 
                (Structure 
                  REGION-NAME Symbol
                  COLOR-NAME
                    (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN 
                            CADET-BLUE CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN 
                            GOLD GOLDENROD GRAY GREEN GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE 
                            LIGHT-GRAY LIME-GREEN MAGENTA MAROON MEDIUM-AQUAMARINE MEDIUM-BLUE 
                            MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE PALE-GREEN PINK PLUM PURPLE RED 
                            SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE TURQUOISE VIOLET 
                            VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN ANTIQUE-WHITE 
                            IVORY AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE 
                            LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW 
                            LIGHT-GOLDENROD BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY))
                1)))
        VARIABLES
          (Sequence 
            (Structure 
              VARIABLE-NAME Symbol
              INITIAL-VALUE
                (OR Integer
                    Symbol
                    Text))
            1))
        ICON-BACKGROUND-LAYER
          (OR (Structure 
                TYPE
                  (MEMBER IMAGE)
                IMAGE-NAME Symbol
                POINT
                  (Structure 
                    X Integer
                    Y Integer))
              (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE 
                      CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD GRAY 
                      GREEN GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN MAGENTA 
                      MAROON MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID ORANGE 
                      PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN THISTLE 
                      TURQUOISE VIOLET VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE LINEN 
                      ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE PALE-TURQUOISE 
                      LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW LIGHT-GOLDENROD 
                      BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY))
        STIPPLE
          (MEMBER LIGHT-STIPPLE MEDIUM-STIPPLE DARK-STIPPLE)
        LAYERS
          (Sequence 
            (Structure 
              REGION-OR-COLOR
                (OR NoItem
                    Symbol)
              LINE-DRAWING-ELEMENTS
                (Sequence 
                  (OR (Structure 
                        TYPE
                          (MEMBER TEXT)
                        LABEL
                          (OR Symbol
                              Text)
                        POINT
                          (Structure 
                            X
                              (OR (OR Integer
                                      Symbol)
                                  Text)
                            Y
                              (OR (OR Integer
                                      Symbol)
                                  Text))
                        FONT-SIZE
                          (OR (MEMBER SMALL LARGE EXTRA-LARGE)
                              Symbol))
                      (Structure 
                        TYPE
                          (MEMBER IMAGE)
                        IMAGE-NAME Symbol
                        POINT
                          (Structure 
                            X
                              (OR (OR Integer
                                      Symbol)
                                  Text)
                            Y
                              (OR (OR Integer
                                      Symbol)
                                  Text)))
                      (Structure 
                        TYPE
                          (MEMBER POINT)
                        POINTS
                          (Structure 
                            X
                              (OR (OR Integer
                                      Symbol)
                                  Text)
                            Y
                              (OR (OR Integer
                                      Symbol)
                                  Text)))
                      (Structure 
                        TYPE
                          (MEMBER CIRCLE)
                        POINTS
                          (Sequence 
                            (Structure 
                              X
                                (OR (OR Integer
                                        Symbol)
                                    Text)
                              Y
                                (OR (OR Integer
                                        Symbol)
                                    Text))
                            1)))
                      (Structure 
                        TYPE
                          (MEMBER FILLED-RECTANGLE)
                        POINTS
                          (Sequence 
                            (Structure 
                              X
                                (OR (OR Integer
                                        Symbol)
                                    Text)
                              Y
                                (OR (OR Integer
                                        Symbol)
                                    Text))
                            1)))
                      (Structure 
                        TYPE
                          (MEMBER FILLED-CIRCLE)
                        POINTS
                          (Sequence 
                            (Structure 
                              X
                                (OR (OR Integer
                                        Symbol)
                                    Text)
                              Y
                                (OR (OR Integer
                                        Symbol)
                                    Text))
                            1)))
                      (Structure 
                        TYPE
                          (MEMBER LINES)
                        POINTS
                          (Sequence 
                            (Structure 
                              ARC BooleanTruthValue
                              X
                                (OR (OR Integer
                                        Symbol)
                                    Text)
                              Y
                                (OR (OR Integer
                                        Symbol)
                                    Text))
                            2)))
                      (Structure 
                        TYPE
                          (MEMBER OUTLINE)
                        POINTS
                          (Sequence 
                            (Structure 
                              ARC BooleanTruthValue
                              X
                                (OR (OR Integer
                                        Symbol)
                                    Text)
                              Y
                                (OR (OR Integer
                                        Symbol)
                                    Text))
                            2)))
                      (Structure 
                        TYPE
                          (MEMBER FILLED-POLYGON)
                        POINTS
                          (Sequence 
                            (Structure 
                              X
                                (OR (OR Integer
                                        Symbol)
                                    Text)
                              Y
                                (OR (OR Integer
                                        Symbol)
                                    Text))
                            3)))
                      (Structure 
                        TYPE
                          (MEMBER STIPPLED-AREA)
                        STIPPLE
                          (MEMBER LIGHT-STIPPLE MEDIUM-STIPPLE DARK-STIPPLE)
                        POINTS
                          (Sequence 
                            (Structure 
                              X
                                (OR (OR Integer
                                        Symbol)
                                    Text)
                              Y
                                (OR (OR Integer
                                        Symbol)
                                    Text))
                            1))))
                  1)))
            1))))
   *
   */
  public com.gensym.util.Structure getIconDescriptionForClass() throws G2AccessException;

  /* Overriden method - REFLECT-VERTICALLY */
  /**
   * Reflects this Item vertically, across the X-axis
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public Symbol reflectVertically() throws G2AccessException;

  /* Overriden method - REFLECT-HORIZONTALLY */
  /**
   * Reflects this Item horizontally, across the Y-axis
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public Symbol reflectHorizontally() throws G2AccessException;

}
