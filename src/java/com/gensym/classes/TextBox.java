/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      TextBox.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:13:53 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface TextBox extends com.gensym.classes.Block {

  public static final Symbol TEXT_BOX_ = com.gensym.util.symbol.G2ClassSymbols.TEXT_BOX_;
  static final Symbol g2ClassName = TEXT_BOX_;
  static final Symbol[] classInheritancePath = new Symbol[] {TEXT_BOX_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};

  static final Symbol DEFAULT_TEXT_BOX_FORMAT_NAME_ = Symbol.intern ("DEFAULT-TEXT-BOX-FORMAT-NAME");

  static final Symbol[] staticAttributes = new Symbol[] {DEFAULT_TEXT_BOX_FORMAT_NAME_};


  /**
   * Generated Property Getter for attribute -- TEXT
   * @return the value of the TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Attribute TEXT has no type
   *
   */
  public java.lang.String getText() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TEXT
   * @param text new value to conclude for TEXT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setText(java.lang.String text) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TEXT-Y-MAGNIFICATION
   * @return the value of the TEXT-Y-MAGNIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TEXT-Y-MAGNIFICATION is : 
   * Quantity
   *
   */
  public java.lang.Number getTextYMagnification() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TEXT-X-MAGNIFICATION
   * @return the value of the TEXT-X-MAGNIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TEXT-X-MAGNIFICATION is : 
   * Quantity
   *
   */
  public java.lang.Number getTextXMagnification() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TEXT-FONT
   * @return the value of the TEXT-FONT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TEXT-FONT is : 
   * (Structure 
    FONT-SIZE
      (MEMBER SMALL LARGE EXTRA-LARGE)
    X-MAGNIFICATION Float
    Y-MAGNIFICATION Float)
   *
   */
  public com.gensym.util.Structure getTextFont() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TEXT-FONT
   * @param textFont new value to conclude for TEXT-FONT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTextFont(com.gensym.util.Structure textFont) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TEXT-ALIGNMENT
   * @return the value of the TEXT-ALIGNMENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TEXT-ALIGNMENT is : 
   * (MEMBER LEFT CENTER RIGHT)
   *
   */
  public com.gensym.util.Symbol getTextAlignment() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TEXT-ALIGNMENT
   * @param textAlignment new value to conclude for TEXT-ALIGNMENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTextAlignment(com.gensym.util.Symbol textAlignment) throws G2AccessException;

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
   * Generated Property Getter for attribute -- FORMAT-TYPE
   * @return the value of the FORMAT-TYPE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FORMAT-TYPE is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getFormatType() throws G2AccessException;

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
   * Generated Property Getter for attribute -- DEFAULT-TEXT-BOX-FORMAT-NAME
   * @return the value of the DEFAULT-TEXT-BOX-FORMAT-NAME attribute of this class
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DEFAULT-TEXT-BOX-FORMAT-NAME is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getDefaultTextBoxFormatNameForClass() throws G2AccessException;

}
