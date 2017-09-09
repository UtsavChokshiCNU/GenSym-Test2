/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GfiOutputInterfaceImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:56:56 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class GfiOutputInterfaceImpl extends com.gensym.classes.ObjectImpl implements GfiOutputInterface {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public GfiOutputInterfaceImpl() {
    super();
  }

  public GfiOutputInterfaceImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public GfiOutputInterfaceImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
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
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-OUTPUT-LINES
   * @param maximumNumberOfOutputLines new value to conclude for MAXIMUM-NUMBER-OF-OUTPUT-LINES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMaximumNumberOfOutputLines(java.lang.Integer maximumNumberOfOutputLines) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_OUTPUT_LINES_, maximumNumberOfOutputLines);
  }

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-OUTPUT-LINES
   * @return the value of the MAXIMUM-NUMBER-OF-OUTPUT-LINES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Integer getMaximumNumberOfOutputLines() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_OUTPUT_LINES_);
    return (java.lang.Integer)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GFI-OUTPUT-VALUES
   * @param gfiOutputValues new value to conclude for GFI-OUTPUT-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfiOutputValues(java.lang.String gfiOutputValues) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GFI_OUTPUT_VALUES_, gfiOutputValues);
  }

  /**
   * Generated Property Getter for attribute -- GFI-OUTPUT-VALUES
   * @return the value of the GFI-OUTPUT-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getGfiOutputValues() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GFI_OUTPUT_VALUES_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GFI-OUTPUT-FILE-UPDATE-FREQUENCY
   * @param gfiOutputFileUpdateFrequency new value to conclude for GFI-OUTPUT-FILE-UPDATE-FREQUENCY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfiOutputFileUpdateFrequency(java.lang.Object gfiOutputFileUpdateFrequency) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GFI_OUTPUT_FILE_UPDATE_FREQUENCY_, gfiOutputFileUpdateFrequency);
  }

  /**
   * Generated Property Getter for attribute -- GFI-OUTPUT-FILE-UPDATE-FREQUENCY
   * @return the value of the GFI-OUTPUT-FILE-UPDATE-FREQUENCY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getGfiOutputFileUpdateFrequency() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GFI_OUTPUT_FILE_UPDATE_FREQUENCY_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GFI-OUTPUT-TIME-STAMP-FORMAT
   * @param gfiOutputTimeStampFormat new value to conclude for GFI-OUTPUT-TIME-STAMP-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfiOutputTimeStampFormat(com.gensym.util.Symbol gfiOutputTimeStampFormat) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GFI_OUTPUT_TIME_STAMP_FORMAT_, gfiOutputTimeStampFormat);
  }

  /**
   * Generated Property Getter for attribute -- GFI-OUTPUT-TIME-STAMP-FORMAT
   * @return the value of the GFI-OUTPUT-TIME-STAMP-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getGfiOutputTimeStampFormat() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GFI_OUTPUT_TIME_STAMP_FORMAT_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GFI-OUTPUT-FILE-FORMAT
   * @param gfiOutputFileFormat new value to conclude for GFI-OUTPUT-FILE-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfiOutputFileFormat(com.gensym.util.Symbol gfiOutputFileFormat) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GFI_OUTPUT_FILE_FORMAT_, gfiOutputFileFormat);
  }

  /**
   * Generated Property Getter for attribute -- GFI-OUTPUT-FILE-FORMAT
   * @return the value of the GFI-OUTPUT-FILE-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getGfiOutputFileFormat() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GFI_OUTPUT_FILE_FORMAT_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- RENAMED-GFI-OUTPUT-FILE-PATHNAME
   * @param renamedGfiOutputFilePathname new value to conclude for RENAMED-GFI-OUTPUT-FILE-PATHNAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRenamedGfiOutputFilePathname(java.lang.String renamedGfiOutputFilePathname) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.RENAMED_GFI_OUTPUT_FILE_PATHNAME_, renamedGfiOutputFilePathname);
  }

  /**
   * Generated Property Getter for attribute -- RENAMED-GFI-OUTPUT-FILE-PATHNAME
   * @return the value of the RENAMED-GFI-OUTPUT-FILE-PATHNAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getRenamedGfiOutputFilePathname() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.RENAMED_GFI_OUTPUT_FILE_PATHNAME_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GFI-OUTPUT-FILE-PATHNAME
   * @param gfiOutputFilePathname new value to conclude for GFI-OUTPUT-FILE-PATHNAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfiOutputFilePathname(java.lang.String gfiOutputFilePathname) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GFI_OUTPUT_FILE_PATHNAME_, gfiOutputFilePathname);
  }

  /**
   * Generated Property Getter for attribute -- GFI-OUTPUT-FILE-PATHNAME
   * @return the value of the GFI-OUTPUT-FILE-PATHNAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getGfiOutputFilePathname() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GFI_OUTPUT_FILE_PATHNAME_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GFI-OUTPUT-WHEN-ACTIVE
   * @param gfiOutputWhenActive new value to conclude for GFI-OUTPUT-WHEN-ACTIVE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfiOutputWhenActive(boolean gfiOutputWhenActive) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GFI_OUTPUT_WHEN_ACTIVE_, new Boolean (gfiOutputWhenActive));
  }

  /**
   * Generated Property Getter for attribute -- GFI-OUTPUT-WHEN-ACTIVE
   * @return the value of the GFI-OUTPUT-WHEN-ACTIVE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getGfiOutputWhenActive() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GFI_OUTPUT_WHEN_ACTIVE_);
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
