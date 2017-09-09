/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2glParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:51:31 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2glParameters extends com.gensym.classes.SystemTable {

  public static final Symbol G2GL_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.G2GL_PARAMETERS_;
  static final Symbol g2ClassName = G2GL_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2GL_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- BREAK-ON-ALL-EXECUTION-FAULTS
   * @return the value of the BREAK-ON-ALL-EXECUTION-FAULTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for BREAK-ON-ALL-EXECUTION-FAULTS is : 
   * BooleanTruthValue
   *
   */
  public boolean getBreakOnAllExecutionFaults() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- BREAK-ON-ALL-EXECUTION-FAULTS
   * @param breakOnAllExecutionFaults new value to conclude for BREAK-ON-ALL-EXECUTION-FAULTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setBreakOnAllExecutionFaults(boolean breakOnAllExecutionFaults) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SUPPRESS-UNSPECIFIED-PARTNER-LINK-VARIABLE-TYPE-FAULTS
   * @return the value of the SUPPRESS-UNSPECIFIED-PARTNER-LINK-VARIABLE-TYPE-FAULTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SUPPRESS-UNSPECIFIED-PARTNER-LINK-VARIABLE-TYPE-FAULTS is : 
   * BooleanTruthValue
   *
   */
  public boolean getSuppressUnspecifiedPartnerLinkVariableTypeFaults() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SUPPRESS-UNSPECIFIED-PARTNER-LINK-VARIABLE-TYPE-FAULTS
   * @param suppressUnspecifiedPartnerLinkVariableTypeFaults new value to conclude for SUPPRESS-UNSPECIFIED-PARTNER-LINK-VARIABLE-TYPE-FAULTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSuppressUnspecifiedPartnerLinkVariableTypeFaults(boolean suppressUnspecifiedPartnerLinkVariableTypeFaults) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- COMPILE-TEXT-ELEMENTS-IN-SOURCE-FOR-EXECUTION-DISPLAYS
   * @return the value of the COMPILE-TEXT-ELEMENTS-IN-SOURCE-FOR-EXECUTION-DISPLAYS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for COMPILE-TEXT-ELEMENTS-IN-SOURCE-FOR-EXECUTION-DISPLAYS is : 
   * BooleanTruthValue
   *
   */
  public boolean getCompileTextElementsInSourceForExecutionDisplays() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- COMPILE-TEXT-ELEMENTS-IN-SOURCE-FOR-EXECUTION-DISPLAYS
   * @param compileTextElementsInSourceForExecutionDisplays new value to conclude for COMPILE-TEXT-ELEMENTS-IN-SOURCE-FOR-EXECUTION-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setCompileTextElementsInSourceForExecutionDisplays(boolean compileTextElementsInSourceForExecutionDisplays) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DEFAULT-THREAD-TOKEN-COLOR
   * @return the value of the DEFAULT-THREAD-TOKEN-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DEFAULT-THREAD-TOKEN-COLOR is : 
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
  public com.gensym.util.Symbol getDefaultThreadTokenColor() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DEFAULT-THREAD-TOKEN-COLOR
   * @param defaultThreadTokenColor new value to conclude for DEFAULT-THREAD-TOKEN-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDefaultThreadTokenColor(com.gensym.util.Symbol defaultThreadTokenColor) throws G2AccessException;

}
