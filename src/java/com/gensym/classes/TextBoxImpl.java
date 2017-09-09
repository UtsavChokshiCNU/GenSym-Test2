/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      TextBoxImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:13:58 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class TextBoxImpl extends com.gensym.classes.BlockImpl implements TextBox {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public TextBoxImpl() {
    super();
  }

  public TextBoxImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public TextBoxImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- TEXT
   * @param text new value to conclude for TEXT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setText(java.lang.String text) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TEXT_, text);
  }

  /**
   * Generated Property Getter for attribute -- TEXT
   * @return the value of the TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getText() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TEXT_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- TEXT-Y-MAGNIFICATION
   * @return the value of the TEXT-Y-MAGNIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Number getTextYMagnification() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TEXT_Y_MAGNIFICATION_);
    return (java.lang.Number)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- TEXT-X-MAGNIFICATION
   * @return the value of the TEXT-X-MAGNIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Number getTextXMagnification() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TEXT_X_MAGNIFICATION_);
    return (java.lang.Number)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TEXT-FONT
   * @param textFont new value to conclude for TEXT-FONT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTextFont(com.gensym.util.Structure textFont) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TEXT_FONT_, textFont);
  }

  /**
   * Generated Property Getter for attribute -- TEXT-FONT
   * @return the value of the TEXT-FONT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getTextFont() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TEXT_FONT_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TEXT-ALIGNMENT
   * @param textAlignment new value to conclude for TEXT-ALIGNMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTextAlignment(com.gensym.util.Symbol textAlignment) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TEXT_ALIGNMENT_, textAlignment);
  }

  /**
   * Generated Property Getter for attribute -- TEXT-ALIGNMENT
   * @return the value of the TEXT-ALIGNMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getTextAlignment() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TEXT_ALIGNMENT_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ITEM-COLOR-PATTERN
   * @param itemColorPattern new value to conclude for ITEM-COLOR-PATTERN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setItemColorPattern(com.gensym.util.Structure itemColorPattern) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ITEM_COLOR_PATTERN_, itemColorPattern);
  }

  /**
   * Generated Property Getter for attribute -- ITEM-COLOR-PATTERN
   * @return the value of the ITEM-COLOR-PATTERN attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getItemColorPattern() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ITEM_COLOR_PATTERN_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- FORMAT-TYPE
   * @return the value of the FORMAT-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFormatType() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FORMAT_TYPE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- BORDER-COLOR
   * @param borderColor new value to conclude for BORDER-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setBorderColor(com.gensym.util.Symbol borderColor) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.BORDER_COLOR_, borderColor);
  }

  /**
   * Generated Property Getter for attribute -- BORDER-COLOR
   * @return the value of the BORDER-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getBorderColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.BORDER_COLOR_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TEXT-COLOR
   * @param textColor new value to conclude for TEXT-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTextColor(com.gensym.util.Symbol textColor) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TEXT_COLOR_, textColor);
  }

  /**
   * Generated Property Getter for attribute -- TEXT-COLOR
   * @return the value of the TEXT-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getTextColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TEXT_COLOR_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- BACKGROUND-COLOR
   * @param backgroundColor new value to conclude for BACKGROUND-COLOR
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setBackgroundColor(com.gensym.util.Symbol backgroundColor) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.BACKGROUND_COLOR_, backgroundColor);
  }

  /**
   * Generated Property Getter for attribute -- BACKGROUND-COLOR
   * @return the value of the BACKGROUND-COLOR attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getBackgroundColor() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.BACKGROUND_COLOR_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-TEXT-BOX-FORMAT-NAME
   * @return the value of the DEFAULT-TEXT-BOX-FORMAT-NAME attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getDefaultTextBoxFormatNameForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.DEFAULT_TEXT_BOX_FORMAT_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
