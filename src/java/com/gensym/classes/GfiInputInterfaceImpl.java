/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GfiInputInterfaceImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:56:53 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class GfiInputInterfaceImpl extends com.gensym.classes.ObjectImpl implements GfiInputInterface {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public GfiInputInterfaceImpl() {
    super();
  }

  public GfiInputInterfaceImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public GfiInputInterfaceImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Getter for attribute -- FILE-SYSTEM
   * @return the value of the FILE-SYSTEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getFileSystem() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FILE_SYSTEM_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- FILE-STATUS
   * @return the value of the FILE-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getFileStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FILE_STATUS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- IGNORE-GFI-INPUT-BASE-TIME
   * @param ignoreGfiInputBaseTime new value to conclude for IGNORE-GFI-INPUT-BASE-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setIgnoreGfiInputBaseTime(boolean ignoreGfiInputBaseTime) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.IGNORE_GFI_INPUT_BASE_TIME_, new Boolean (ignoreGfiInputBaseTime));
  }

  /**
   * Generated Property Getter for attribute -- IGNORE-GFI-INPUT-BASE-TIME
   * @return the value of the IGNORE-GFI-INPUT-BASE-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getIgnoreGfiInputBaseTime() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.IGNORE_GFI_INPUT_BASE_TIME_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- GFI-INPUT-VARIABLES-UPDATE-MODE
   * @param gfiInputVariablesUpdateMode new value to conclude for GFI-INPUT-VARIABLES-UPDATE-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfiInputVariablesUpdateMode(com.gensym.util.Symbol gfiInputVariablesUpdateMode) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GFI_INPUT_VARIABLES_UPDATE_MODE_, gfiInputVariablesUpdateMode);
  }

  /**
   * Generated Property Getter for attribute -- GFI-INPUT-VARIABLES-UPDATE-MODE
   * @return the value of the GFI-INPUT-VARIABLES-UPDATE-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getGfiInputVariablesUpdateMode() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GFI_INPUT_VARIABLES_UPDATE_MODE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GFI-INPUT-TIME-STAMP-FORMAT
   * @param gfiInputTimeStampFormat new value to conclude for GFI-INPUT-TIME-STAMP-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfiInputTimeStampFormat(com.gensym.util.Symbol gfiInputTimeStampFormat) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GFI_INPUT_TIME_STAMP_FORMAT_, gfiInputTimeStampFormat);
  }

  /**
   * Generated Property Getter for attribute -- GFI-INPUT-TIME-STAMP-FORMAT
   * @return the value of the GFI-INPUT-TIME-STAMP-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getGfiInputTimeStampFormat() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GFI_INPUT_TIME_STAMP_FORMAT_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GFI-INPUT-FILE-FORMAT
   * @param gfiInputFileFormat new value to conclude for GFI-INPUT-FILE-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfiInputFileFormat(com.gensym.util.Symbol gfiInputFileFormat) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GFI_INPUT_FILE_FORMAT_, gfiInputFileFormat);
  }

  /**
   * Generated Property Getter for attribute -- GFI-INPUT-FILE-FORMAT
   * @return the value of the GFI-INPUT-FILE-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getGfiInputFileFormat() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GFI_INPUT_FILE_FORMAT_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GFI-INPUT-FILE-PATHNAME
   * @param gfiInputFilePathname new value to conclude for GFI-INPUT-FILE-PATHNAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfiInputFilePathname(java.lang.String gfiInputFilePathname) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GFI_INPUT_FILE_PATHNAME_, gfiInputFilePathname);
  }

  /**
   * Generated Property Getter for attribute -- GFI-INPUT-FILE-PATHNAME
   * @return the value of the GFI-INPUT-FILE-PATHNAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getGfiInputFilePathname() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GFI_INPUT_FILE_PATHNAME_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GFI-INPUT-WHEN-ACTIVE
   * @param gfiInputWhenActive new value to conclude for GFI-INPUT-WHEN-ACTIVE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfiInputWhenActive(boolean gfiInputWhenActive) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GFI_INPUT_WHEN_ACTIVE_, new Boolean (gfiInputWhenActive));
  }

  /**
   * Generated Property Getter for attribute -- GFI-INPUT-WHEN-ACTIVE
   * @return the value of the GFI-INPUT-WHEN-ACTIVE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getGfiInputWhenActive() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GFI_INPUT_WHEN_ACTIVE_);
    return ((Boolean)retnValue).booleanValue ();
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
