/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Fonts.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:41:58 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Fonts extends com.gensym.classes.SystemTable {

  public static final Symbol FONTS_ = com.gensym.util.symbol.G2ClassSymbols.FONTS_;
  static final Symbol g2ClassName = FONTS_;
  static final Symbol[] classInheritancePath = new Symbol[] {FONTS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- FONT-FOR-ATTRIBUTE-TABLES
   * @return the value of the FONT-FOR-ATTRIBUTE-TABLES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FONT-FOR-ATTRIBUTE-TABLES is : 
   * (MEMBER SMALL LARGE EXTRA-LARGE)
   *
   */
  public com.gensym.util.Symbol getFontForAttributeTables() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FONT-FOR-ATTRIBUTE-TABLES
   * @param fontForAttributeTables new value to conclude for FONT-FOR-ATTRIBUTE-TABLES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFontForAttributeTables(com.gensym.util.Symbol fontForAttributeTables) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FONT-FOR-ATTRIBUTE-DISPLAYS
   * @return the value of the FONT-FOR-ATTRIBUTE-DISPLAYS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FONT-FOR-ATTRIBUTE-DISPLAYS is : 
   * (MEMBER SMALL LARGE EXTRA-LARGE)
   *
   */
  public com.gensym.util.Symbol getFontForAttributeDisplays() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FONT-FOR-ATTRIBUTE-DISPLAYS
   * @param fontForAttributeDisplays new value to conclude for FONT-FOR-ATTRIBUTE-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFontForAttributeDisplays(com.gensym.util.Symbol fontForAttributeDisplays) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FONT-FOR-STATEMENTS
   * @return the value of the FONT-FOR-STATEMENTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FONT-FOR-STATEMENTS is : 
   * (MEMBER SMALL LARGE EXTRA-LARGE)
   *
   */
  public com.gensym.util.Symbol getFontForStatements() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FONT-FOR-STATEMENTS
   * @param fontForStatements new value to conclude for FONT-FOR-STATEMENTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFontForStatements(com.gensym.util.Symbol fontForStatements) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FONT-FOR-FREE-TEXT
   * @return the value of the FONT-FOR-FREE-TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FONT-FOR-FREE-TEXT is : 
   * (MEMBER SMALL LARGE EXTRA-LARGE)
   *
   */
  public com.gensym.util.Symbol getFontForFreeText() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FONT-FOR-FREE-TEXT
   * @param fontForFreeText new value to conclude for FONT-FOR-FREE-TEXT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFontForFreeText(com.gensym.util.Symbol fontForFreeText) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FONT-FOR-EDITING
   * @return the value of the FONT-FOR-EDITING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FONT-FOR-EDITING is : 
   * (MEMBER SMALL LARGE EXTRA-LARGE)
   *
   */
  public com.gensym.util.Symbol getFontForEditing() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FONT-FOR-EDITING
   * @param fontForEditing new value to conclude for FONT-FOR-EDITING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFontForEditing(com.gensym.util.Symbol fontForEditing) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FONT-FOR-DESCRIPTIONS
   * @return the value of the FONT-FOR-DESCRIPTIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FONT-FOR-DESCRIPTIONS is : 
   * (MEMBER SMALL LARGE EXTRA-LARGE)
   *
   */
  public com.gensym.util.Symbol getFontForDescriptions() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FONT-FOR-DESCRIPTIONS
   * @param fontForDescriptions new value to conclude for FONT-FOR-DESCRIPTIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFontForDescriptions(com.gensym.util.Symbol fontForDescriptions) throws G2AccessException;

}
