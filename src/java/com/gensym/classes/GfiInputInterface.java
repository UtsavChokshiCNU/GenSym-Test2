/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GfiInputInterface.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:56:52 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface GfiInputInterface extends com.gensym.classes.Object {

  public static final Symbol GFI_INPUT_INTERFACE_ = com.gensym.util.symbol.G2ClassSymbols.GFI_INPUT_INTERFACE_;
  static final Symbol g2ClassName = GFI_INPUT_INTERFACE_;
  static final Symbol[] classInheritancePath = new Symbol[] {GFI_INPUT_INTERFACE_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


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
   * Generated Property Getter for attribute -- IGNORE-GFI-INPUT-BASE-TIME
   * @return the value of the IGNORE-GFI-INPUT-BASE-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for IGNORE-GFI-INPUT-BASE-TIME is : 
   * BooleanTruthValue
   *
   */
  public boolean getIgnoreGfiInputBaseTime() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- IGNORE-GFI-INPUT-BASE-TIME
   * @param ignoreGfiInputBaseTime new value to conclude for IGNORE-GFI-INPUT-BASE-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIgnoreGfiInputBaseTime(boolean ignoreGfiInputBaseTime) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GFI-INPUT-VARIABLES-UPDATE-MODE
   * @return the value of the GFI-INPUT-VARIABLES-UPDATE-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GFI-INPUT-VARIABLES-UPDATE-MODE is : 
   * (OR NoItem
      (MEMBER ASYNCHRONOUS-INPUT ASYNCHRONOUS-INPUT-IGNORING-THE-DATA-SERVER 
              INPUT-ON-REQUEST-PRESERVING-TIME-STAMPS INPUT-ON-REQUEST-SAMPLE-AND-HOLD 
              INPUT-WHEN-ACTIVATED INPUT-WHEN-ACTIVATED-WITHOUT-INTERRUPTION))
   *
   */
  public com.gensym.util.Symbol getGfiInputVariablesUpdateMode() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GFI-INPUT-VARIABLES-UPDATE-MODE
   * @param gfiInputVariablesUpdateMode new value to conclude for GFI-INPUT-VARIABLES-UPDATE-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGfiInputVariablesUpdateMode(com.gensym.util.Symbol gfiInputVariablesUpdateMode) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GFI-INPUT-TIME-STAMP-FORMAT
   * @return the value of the GFI-INPUT-TIME-STAMP-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GFI-INPUT-TIME-STAMP-FORMAT is : 
   * (MEMBER EXPLICIT-TIME-STAMP RELATIVE-TIME-STAMP)
   *
   */
  public com.gensym.util.Symbol getGfiInputTimeStampFormat() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GFI-INPUT-TIME-STAMP-FORMAT
   * @param gfiInputTimeStampFormat new value to conclude for GFI-INPUT-TIME-STAMP-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGfiInputTimeStampFormat(com.gensym.util.Symbol gfiInputTimeStampFormat) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GFI-INPUT-FILE-FORMAT
   * @return the value of the GFI-INPUT-FILE-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GFI-INPUT-FILE-FORMAT is : 
   * (OR NoItem
      (MEMBER EVENT-LOG SPREADSHEET))
   *
   */
  public com.gensym.util.Symbol getGfiInputFileFormat() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GFI-INPUT-FILE-FORMAT
   * @param gfiInputFileFormat new value to conclude for GFI-INPUT-FILE-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGfiInputFileFormat(com.gensym.util.Symbol gfiInputFileFormat) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GFI-INPUT-FILE-PATHNAME
   * @return the value of the GFI-INPUT-FILE-PATHNAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GFI-INPUT-FILE-PATHNAME is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getGfiInputFilePathname() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GFI-INPUT-FILE-PATHNAME
   * @param gfiInputFilePathname new value to conclude for GFI-INPUT-FILE-PATHNAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGfiInputFilePathname(java.lang.String gfiInputFilePathname) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GFI-INPUT-WHEN-ACTIVE
   * @return the value of the GFI-INPUT-WHEN-ACTIVE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GFI-INPUT-WHEN-ACTIVE is : 
   * BooleanTruthValue
   *
   */
  public boolean getGfiInputWhenActive() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GFI-INPUT-WHEN-ACTIVE
   * @param gfiInputWhenActive new value to conclude for GFI-INPUT-WHEN-ACTIVE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGfiInputWhenActive(boolean gfiInputWhenActive) throws G2AccessException;

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
