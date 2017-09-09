/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ConnectionDefinition.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:37:29 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface ConnectionDefinition extends com.gensym.classes.ClassDefinition {

  public static final Symbol CONNECTION_DEFINITION_ = com.gensym.util.symbol.G2ClassSymbols.CONNECTION_DEFINITION_;
  static final Symbol g2ClassName = CONNECTION_DEFINITION_;
  static final Symbol[] classInheritancePath = new Symbol[] {CONNECTION_DEFINITION_, CLASS_DEFINITION_, DEFINITION_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- CROSS-SECTION-PATTERN
   * @return the value of the CROSS-SECTION-PATTERN attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CROSS-SECTION-PATTERN is : 
   * (OR NoItem
      (Structure 
        CROSS-SECTION-REGIONS
          (Sequence 
            (Structure 
              REGION-NAME Symbol
              REGION-COLOR
                (MEMBER FOREGROUND BACKGROUND TRANSPARENT AQUAMARINE BLACK BLUE BROWN CADET-BLUE 
                        CORAL CYAN DARK-GRAY DARK-SLATE-BLUE DIM-GRAY FOREST-GREEN GOLD GOLDENROD 
                        GRAY GREEN GREEN-YELLOW INDIAN-RED KHAKI LIGHT-BLUE LIGHT-GRAY LIME-GREEN 
                        MAGENTA MAROON MEDIUM-AQUAMARINE MEDIUM-BLUE MEDIUM-GOLDENROD MEDIUM-ORCHID 
                        ORANGE PALE-GREEN PINK PLUM PURPLE RED SALMON SIENNA SKY-BLUE SLATE-BLUE TAN 
                        THISTLE TURQUOISE VIOLET VIOLET-RED WHEAT WHITE YELLOW SMOKE FLORAL-WHITE 
                        LINEN ANTIQUE-WHITE IVORY AZURE LAVENDER LIGHT-STEEL-BLUE POWDER-BLUE 
                        PALE-TURQUOISE LIGHT-CYAN PALE-GOLDENROD LIGHT-GOLDENROD-YELLOW LIGHT-YELLOW 
                        LIGHT-GOLDENROD BEIGE LIGHT-PINK EXTRA-LIGHT-GRAY))
            1))
        CROSS-SECTION-STRIPES
          (Sequence 
            (Structure 
              REGION-NAME Symbol
              REGION-SIZE Integer)
            1))))
   *
   */
  public com.gensym.util.Structure getCrossSectionPattern() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CROSS-SECTION-PATTERN
   * @param crossSectionPattern new value to conclude for CROSS-SECTION-PATTERN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setCrossSectionPattern(com.gensym.util.Structure crossSectionPattern) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- STUB-LENGTH
   * @return the value of the STUB-LENGTH attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for STUB-LENGTH is : 
   * (OR Symbol
      Quantity)
   *
   */
  public java.lang.Object getStubLength() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- STUB-LENGTH
   * @param stubLength new value to conclude for STUB-LENGTH
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStubLength(java.lang.Object stubLength) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JUNCTION-BLOCK
   * @return the value of the JUNCTION-BLOCK attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JUNCTION-BLOCK is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getJunctionBlock() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- JUNCTION-BLOCK
   * @param junctionBlock new value to conclude for JUNCTION-BLOCK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setJunctionBlock(com.gensym.util.Symbol junctionBlock) throws G2AccessException;

}
