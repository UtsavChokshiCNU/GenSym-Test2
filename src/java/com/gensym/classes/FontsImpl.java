/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      FontsImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:41:59 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class FontsImpl extends com.gensym.classes.SystemTableImpl implements Fonts {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public FontsImpl() {
    super();
  }

  public FontsImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public FontsImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- FONT-FOR-ATTRIBUTE-TABLES
   * @param fontForAttributeTables new value to conclude for FONT-FOR-ATTRIBUTE-TABLES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFontForAttributeTables(com.gensym.util.Symbol fontForAttributeTables) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FONT_FOR_ATTRIBUTE_TABLES_, fontForAttributeTables);
  }

  /**
   * Generated Property Getter for attribute -- FONT-FOR-ATTRIBUTE-TABLES
   * @return the value of the FONT-FOR-ATTRIBUTE-TABLES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFontForAttributeTables() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FONT_FOR_ATTRIBUTE_TABLES_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- FONT-FOR-ATTRIBUTE-DISPLAYS
   * @param fontForAttributeDisplays new value to conclude for FONT-FOR-ATTRIBUTE-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFontForAttributeDisplays(com.gensym.util.Symbol fontForAttributeDisplays) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FONT_FOR_ATTRIBUTE_DISPLAYS_, fontForAttributeDisplays);
  }

  /**
   * Generated Property Getter for attribute -- FONT-FOR-ATTRIBUTE-DISPLAYS
   * @return the value of the FONT-FOR-ATTRIBUTE-DISPLAYS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFontForAttributeDisplays() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FONT_FOR_ATTRIBUTE_DISPLAYS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- FONT-FOR-STATEMENTS
   * @param fontForStatements new value to conclude for FONT-FOR-STATEMENTS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFontForStatements(com.gensym.util.Symbol fontForStatements) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FONT_FOR_STATEMENTS_, fontForStatements);
  }

  /**
   * Generated Property Getter for attribute -- FONT-FOR-STATEMENTS
   * @return the value of the FONT-FOR-STATEMENTS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFontForStatements() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FONT_FOR_STATEMENTS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- FONT-FOR-FREE-TEXT
   * @param fontForFreeText new value to conclude for FONT-FOR-FREE-TEXT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFontForFreeText(com.gensym.util.Symbol fontForFreeText) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FONT_FOR_FREE_TEXT_, fontForFreeText);
  }

  /**
   * Generated Property Getter for attribute -- FONT-FOR-FREE-TEXT
   * @return the value of the FONT-FOR-FREE-TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFontForFreeText() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FONT_FOR_FREE_TEXT_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- FONT-FOR-EDITING
   * @param fontForEditing new value to conclude for FONT-FOR-EDITING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFontForEditing(com.gensym.util.Symbol fontForEditing) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FONT_FOR_EDITING_, fontForEditing);
  }

  /**
   * Generated Property Getter for attribute -- FONT-FOR-EDITING
   * @return the value of the FONT-FOR-EDITING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFontForEditing() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FONT_FOR_EDITING_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- FONT-FOR-DESCRIPTIONS
   * @param fontForDescriptions new value to conclude for FONT-FOR-DESCRIPTIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFontForDescriptions(com.gensym.util.Symbol fontForDescriptions) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FONT_FOR_DESCRIPTIONS_, fontForDescriptions);
  }

  /**
   * Generated Property Getter for attribute -- FONT-FOR-DESCRIPTIONS
   * @return the value of the FONT-FOR-DESCRIPTIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFontForDescriptions() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FONT_FOR_DESCRIPTIONS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
