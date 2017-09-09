/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      LanguageParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:00:27 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface LanguageParameters extends com.gensym.classes.SystemTable {

  public static final Symbol LANGUAGE_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.LANGUAGE_PARAMETERS_;
  static final Symbol g2ClassName = LANGUAGE_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {LANGUAGE_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- CURRENT-LANGUAGE
   * @return the value of the CURRENT-LANGUAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CURRENT-LANGUAGE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getCurrentLanguage() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CURRENT-LANGUAGE
   * @param currentLanguage new value to conclude for CURRENT-LANGUAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setCurrentLanguage(com.gensym.util.Symbol currentLanguage) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TEXT-CONVERSION-STYLE
   * @return the value of the TEXT-CONVERSION-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TEXT-CONVERSION-STYLE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getTextConversionStyle() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TEXT-CONVERSION-STYLE
   * @param textConversionStyle new value to conclude for TEXT-CONVERSION-STYLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTextConversionStyle(com.gensym.util.Symbol textConversionStyle) throws G2AccessException;

}
