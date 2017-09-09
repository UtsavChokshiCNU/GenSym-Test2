/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      PrinterSetupImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:04:55 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class PrinterSetupImpl extends com.gensym.classes.SystemTableImpl implements PrinterSetup {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public PrinterSetupImpl() {
    super();
  }

  public PrinterSetupImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public PrinterSetupImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- PRINTING-DETAILS
   * @param printingDetails new value to conclude for PRINTING-DETAILS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPrintingDetails(com.gensym.util.Structure printingDetails) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PRINTING_DETAILS_, printingDetails);
  }

  /**
   * Generated Property Getter for attribute -- PRINTING-DETAILS
   * @return the value of the PRINTING-DETAILS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getPrintingDetails() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PRINTING_DETAILS_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- PAGE-LAYOUT
   * @param pageLayout new value to conclude for PAGE-LAYOUT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPageLayout(com.gensym.util.Structure pageLayout) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PAGE_LAYOUT_, pageLayout);
  }

  /**
   * Generated Property Getter for attribute -- PAGE-LAYOUT
   * @return the value of the PAGE-LAYOUT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getPageLayout() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PAGE_LAYOUT_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- PRINT-SPOOLING
   * @param printSpooling new value to conclude for PRINT-SPOOLING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPrintSpooling(com.gensym.util.Structure printSpooling) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PRINT_SPOOLING_, printSpooling);
  }

  /**
   * Generated Property Getter for attribute -- PRINT-SPOOLING
   * @return the value of the PRINT-SPOOLING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getPrintSpooling() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PRINT_SPOOLING_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- PRINTING-PRIORITY
   * @param printingPriority new value to conclude for PRINTING-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPrintingPriority(com.gensym.util.Symbol printingPriority) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PRINTING_PRIORITY_, printingPriority);
  }

  /**
   * Generated Property Getter for attribute -- PRINTING-PRIORITY
   * @return the value of the PRINTING-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getPrintingPriority() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PRINTING_PRIORITY_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- PRINTING-FILE-FORMAT
   * @param printingFileFormat new value to conclude for PRINTING-FILE-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPrintingFileFormat(com.gensym.util.Symbol printingFileFormat) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PRINTING_FILE_FORMAT_, printingFileFormat);
  }

  /**
   * Generated Property Getter for attribute -- PRINTING-FILE-FORMAT
   * @return the value of the PRINTING-FILE-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getPrintingFileFormat() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PRINTING_FILE_FORMAT_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- PAGE-ECONOMY-MODE
   * @param pageEconomyMode new value to conclude for PAGE-ECONOMY-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPageEconomyMode(boolean pageEconomyMode) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PAGE_ECONOMY_MODE_, new Boolean (pageEconomyMode));
  }

  /**
   * Generated Property Getter for attribute -- PAGE-ECONOMY-MODE
   * @return the value of the PAGE-ECONOMY-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getPageEconomyMode() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PAGE_ECONOMY_MODE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
