/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      LanguageParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:00:28 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class LanguageParametersImpl extends com.gensym.classes.SystemTableImpl implements LanguageParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public LanguageParametersImpl() {
    super();
  }

  public LanguageParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public LanguageParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- CURRENT-LANGUAGE
   * @param currentLanguage new value to conclude for CURRENT-LANGUAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setCurrentLanguage(com.gensym.util.Symbol currentLanguage) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.CURRENT_LANGUAGE_, currentLanguage);
  }

  /**
   * Generated Property Getter for attribute -- CURRENT-LANGUAGE
   * @return the value of the CURRENT-LANGUAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getCurrentLanguage() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CURRENT_LANGUAGE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TEXT-CONVERSION-STYLE
   * @param textConversionStyle new value to conclude for TEXT-CONVERSION-STYLE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTextConversionStyle(com.gensym.util.Symbol textConversionStyle) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TEXT_CONVERSION_STYLE_, textConversionStyle);
  }

  /**
   * Generated Property Getter for attribute -- TEXT-CONVERSION-STYLE
   * @return the value of the TEXT-CONVERSION-STYLE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getTextConversionStyle() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TEXT_CONVERSION_STYLE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
