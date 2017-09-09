/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GfiOutputInterface.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:56:54 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface GfiOutputInterface extends com.gensym.classes.Object {

  public static final Symbol GFI_OUTPUT_INTERFACE_ = com.gensym.util.symbol.G2ClassSymbols.GFI_OUTPUT_INTERFACE_;
  static final Symbol g2ClassName = GFI_OUTPUT_INTERFACE_;
  static final Symbol[] classInheritancePath = new Symbol[] {GFI_OUTPUT_INTERFACE_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- FILE-SYSTEM
   * @return the value of the FILE-SYSTEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FILE-SYSTEM is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text)
   *
   */
  public java.lang.Object getFileSystem() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FILE-STATUS
   * @return the value of the FILE-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FILE-STATUS is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text)
   *
   */
  public java.lang.Object getFileStatus() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-OUTPUT-LINES
   * @return the value of the MAXIMUM-NUMBER-OF-OUTPUT-LINES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MAXIMUM-NUMBER-OF-OUTPUT-LINES is : 
   * (OR NoItem
      Integer)
   *
   */
  public java.lang.Integer getMaximumNumberOfOutputLines() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-OUTPUT-LINES
   * @param maximumNumberOfOutputLines new value to conclude for MAXIMUM-NUMBER-OF-OUTPUT-LINES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMaximumNumberOfOutputLines(java.lang.Integer maximumNumberOfOutputLines) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GFI-OUTPUT-VALUES
   * @return the value of the GFI-OUTPUT-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GFI-OUTPUT-VALUES is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getGfiOutputValues() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GFI-OUTPUT-VALUES
   * @param gfiOutputValues new value to conclude for GFI-OUTPUT-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGfiOutputValues(java.lang.String gfiOutputValues) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GFI-OUTPUT-FILE-UPDATE-FREQUENCY
   * @return the value of the GFI-OUTPUT-FILE-UPDATE-FREQUENCY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GFI-OUTPUT-FILE-UPDATE-FREQUENCY is : 
   * (OR NoItem
      Integer
      (MEMBER WHEN-VARIABLES-RECEIVE-VALUES WHEN-ACTIVATED WHEN-ACTIVATED-WITHOUT-INTERRUPTION))
   *
   */
  public java.lang.Object getGfiOutputFileUpdateFrequency() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GFI-OUTPUT-FILE-UPDATE-FREQUENCY
   * @param gfiOutputFileUpdateFrequency new value to conclude for GFI-OUTPUT-FILE-UPDATE-FREQUENCY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGfiOutputFileUpdateFrequency(java.lang.Object gfiOutputFileUpdateFrequency) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GFI-OUTPUT-TIME-STAMP-FORMAT
   * @return the value of the GFI-OUTPUT-TIME-STAMP-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GFI-OUTPUT-TIME-STAMP-FORMAT is : 
   * (MEMBER EXPLICIT-TIME-STAMP RELATIVE-TIME-STAMP)
   *
   */
  public com.gensym.util.Symbol getGfiOutputTimeStampFormat() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GFI-OUTPUT-TIME-STAMP-FORMAT
   * @param gfiOutputTimeStampFormat new value to conclude for GFI-OUTPUT-TIME-STAMP-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGfiOutputTimeStampFormat(com.gensym.util.Symbol gfiOutputTimeStampFormat) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GFI-OUTPUT-FILE-FORMAT
   * @return the value of the GFI-OUTPUT-FILE-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GFI-OUTPUT-FILE-FORMAT is : 
   * (OR NoItem
      (MEMBER EVENT-LOG SPREADSHEET))
   *
   */
  public com.gensym.util.Symbol getGfiOutputFileFormat() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GFI-OUTPUT-FILE-FORMAT
   * @param gfiOutputFileFormat new value to conclude for GFI-OUTPUT-FILE-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGfiOutputFileFormat(com.gensym.util.Symbol gfiOutputFileFormat) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- RENAMED-GFI-OUTPUT-FILE-PATHNAME
   * @return the value of the RENAMED-GFI-OUTPUT-FILE-PATHNAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for RENAMED-GFI-OUTPUT-FILE-PATHNAME is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getRenamedGfiOutputFilePathname() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- RENAMED-GFI-OUTPUT-FILE-PATHNAME
   * @param renamedGfiOutputFilePathname new value to conclude for RENAMED-GFI-OUTPUT-FILE-PATHNAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRenamedGfiOutputFilePathname(java.lang.String renamedGfiOutputFilePathname) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GFI-OUTPUT-FILE-PATHNAME
   * @return the value of the GFI-OUTPUT-FILE-PATHNAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GFI-OUTPUT-FILE-PATHNAME is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getGfiOutputFilePathname() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GFI-OUTPUT-FILE-PATHNAME
   * @param gfiOutputFilePathname new value to conclude for GFI-OUTPUT-FILE-PATHNAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGfiOutputFilePathname(java.lang.String gfiOutputFilePathname) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GFI-OUTPUT-WHEN-ACTIVE
   * @return the value of the GFI-OUTPUT-WHEN-ACTIVE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GFI-OUTPUT-WHEN-ACTIVE is : 
   * BooleanTruthValue
   *
   */
  public boolean getGfiOutputWhenActive() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GFI-OUTPUT-WHEN-ACTIVE
   * @param gfiOutputWhenActive new value to conclude for GFI-OUTPUT-WHEN-ACTIVE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGfiOutputWhenActive(boolean gfiOutputWhenActive) throws G2AccessException;

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
