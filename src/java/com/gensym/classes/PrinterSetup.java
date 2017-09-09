/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      PrinterSetup.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:04:50 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface PrinterSetup extends com.gensym.classes.SystemTable {

  public static final Symbol PRINTER_SETUP_ = com.gensym.util.symbol.G2ClassSymbols.PRINTER_SETUP_;
  static final Symbol g2ClassName = PRINTER_SETUP_;
  static final Symbol[] classInheritancePath = new Symbol[] {PRINTER_SETUP_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- PRINTING-DETAILS
   * @return the value of the PRINTING-DETAILS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PRINTING-DETAILS is : 
   * (Structure 
    WORKSPACE-SCALING
      (OR (MEMBER SCALE-TO-FIT-SINGLE-PAGE)
          (Structure 
            NUMBER Quantity
            UNITS
              (MEMBER INCH INCHES CENTIMETER CENTIMETERS CM FOOT FEET MILLIMETER MILLIMETERS MM)))
    COLOR-CONVERSION
      (MEMBER BLACK-AND-WHITE GRAYS FULL-COLOR))
   *
   */
  public com.gensym.util.Structure getPrintingDetails() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PRINTING-DETAILS
   * @param printingDetails new value to conclude for PRINTING-DETAILS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPrintingDetails(com.gensym.util.Structure printingDetails) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PAGE-LAYOUT
   * @return the value of the PAGE-LAYOUT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PAGE-LAYOUT is : 
   * (Structure 
    PAPER-SIZE
      (OR (MEMBER LETTER LEGAL LEDGER A0 A1 A2 A3 A4 A5 B0 B1 B2 B3 B4 B5)
          (Structure 
            WIDTH
              (Structure 
                NUMBER Quantity
                UNITS
                  (MEMBER INCH INCHES CENTIMETER CENTIMETERS CM FOOT FEET MILLIMETER MILLIMETERS MM))
            HEIGHT
              (Structure 
                NUMBER Quantity
                UNITS
                  (MEMBER INCH INCHES CENTIMETER CENTIMETERS CM FOOT FEET MILLIMETER MILLIMETERS MM))))
    PAPER-ORIENTATION
      (MEMBER PORTRAIT LANDSCAPE)
    LEFT-MARGIN
      (Structure 
        NUMBER Quantity
        UNITS
          (MEMBER INCH INCHES CENTIMETER CENTIMETERS CM FOOT FEET MILLIMETER MILLIMETERS MM))
    TOP-MARGIN
      (Structure 
        NUMBER Quantity
        UNITS
          (MEMBER INCH INCHES CENTIMETER CENTIMETERS CM FOOT FEET MILLIMETER MILLIMETERS MM))
    RIGHT-MARGIN
      (Structure 
        NUMBER Quantity
        UNITS
          (MEMBER INCH INCHES CENTIMETER CENTIMETERS CM FOOT FEET MILLIMETER MILLIMETERS MM))
    BOTTOM-MARGIN
      (Structure 
        NUMBER Quantity
        UNITS
          (MEMBER INCH INCHES CENTIMETER CENTIMETERS CM FOOT FEET MILLIMETER MILLIMETERS MM)))
   *
   */
  public com.gensym.util.Structure getPageLayout() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PAGE-LAYOUT
   * @param pageLayout new value to conclude for PAGE-LAYOUT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPageLayout(com.gensym.util.Structure pageLayout) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PRINT-SPOOLING
   * @return the value of the PRINT-SPOOLING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PRINT-SPOOLING is : 
   * (Structure 
    SPOOLED-FILENAME-TEMPLATE Text
    SPOOL-FILE-TO-PRINTER BooleanTruthValue
    PRINTER-IDENTIFICATION Text)
   *
   */
  public com.gensym.util.Structure getPrintSpooling() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PRINT-SPOOLING
   * @param printSpooling new value to conclude for PRINT-SPOOLING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPrintSpooling(com.gensym.util.Structure printSpooling) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PRINTING-PRIORITY
   * @return the value of the PRINTING-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PRINTING-PRIORITY is : 
   * (MEMBER 1 2 3 4 5 6 7 8 9 10)
   *
   */
  public com.gensym.util.Symbol getPrintingPriority() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PRINTING-PRIORITY
   * @param printingPriority new value to conclude for PRINTING-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPrintingPriority(com.gensym.util.Symbol printingPriority) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PRINTING-FILE-FORMAT
   * @return the value of the PRINTING-FILE-FORMAT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PRINTING-FILE-FORMAT is : 
   * (MEMBER ENCAPSULATED-POSTSCRIPT POSTSCRIPT)
   *
   */
  public com.gensym.util.Symbol getPrintingFileFormat() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PRINTING-FILE-FORMAT
   * @param printingFileFormat new value to conclude for PRINTING-FILE-FORMAT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPrintingFileFormat(com.gensym.util.Symbol printingFileFormat) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PAGE-ECONOMY-MODE
   * @return the value of the PAGE-ECONOMY-MODE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PAGE-ECONOMY-MODE is : 
   * BooleanTruthValue
   *
   */
  public boolean getPageEconomyMode() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PAGE-ECONOMY-MODE
   * @param pageEconomyMode new value to conclude for PAGE-ECONOMY-MODE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPageEconomyMode(boolean pageEconomyMode) throws G2AccessException;

}
