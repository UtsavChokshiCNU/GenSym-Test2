/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      LogbookParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:26:06 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class LogbookParametersImpl extends com.gensym.classes.SystemTableImpl implements LogbookParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public LogbookParametersImpl() {
    super();
  }

  public LogbookParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public LogbookParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- WIDTH-FOR-PAGES
   * @param widthForPages new value to conclude for WIDTH-FOR-PAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setWidthForPages(int widthForPages) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.WIDTH_FOR_PAGES_, widthForPages);
  }

  /**
   * Generated Property Getter for attribute -- WIDTH-FOR-PAGES
   * @return the value of the WIDTH-FOR-PAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getWidthForPages() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.WIDTH_FOR_PAGES_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- HEIGHT-FOR-PAGES
   * @param heightForPages new value to conclude for HEIGHT-FOR-PAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setHeightForPages(int heightForPages) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.HEIGHT_FOR_PAGES_, heightForPages);
  }

  /**
   * Generated Property Getter for attribute -- HEIGHT-FOR-PAGES
   * @return the value of the HEIGHT-FOR-PAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getHeightForPages() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.HEIGHT_FOR_PAGES_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- MARGIN-FOR-PAGES
   * @param marginForPages new value to conclude for MARGIN-FOR-PAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMarginForPages(int marginForPages) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MARGIN_FOR_PAGES_, marginForPages);
  }

  /**
   * Generated Property Getter for attribute -- MARGIN-FOR-PAGES
   * @return the value of the MARGIN-FOR-PAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getMarginForPages() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MARGIN_FOR_PAGES_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- X-OFFSET-FOR-NEXT-PAGE
   * @param xOffsetForNextPage new value to conclude for X-OFFSET-FOR-NEXT-PAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setXOffsetForNextPage(int xOffsetForNextPage) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.X_OFFSET_FOR_NEXT_PAGE_, xOffsetForNextPage);
  }

  /**
   * Generated Property Getter for attribute -- X-OFFSET-FOR-NEXT-PAGE
   * @return the value of the X-OFFSET-FOR-NEXT-PAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getXOffsetForNextPage() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.X_OFFSET_FOR_NEXT_PAGE_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- Y-OFFSET-FOR-NEXT-PAGE
   * @param yOffsetForNextPage new value to conclude for Y-OFFSET-FOR-NEXT-PAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setYOffsetForNextPage(int yOffsetForNextPage) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.Y_OFFSET_FOR_NEXT_PAGE_, yOffsetForNextPage);
  }

  /**
   * Generated Property Getter for attribute -- Y-OFFSET-FOR-NEXT-PAGE
   * @return the value of the Y-OFFSET-FOR-NEXT-PAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getYOffsetForNextPage() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.Y_OFFSET_FOR_NEXT_PAGE_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- X-OFFSET-FOR-LOGBOOK
   * @param xOffsetForLogbook new value to conclude for X-OFFSET-FOR-LOGBOOK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setXOffsetForLogbook(int xOffsetForLogbook) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.X_OFFSET_FOR_LOGBOOK_, xOffsetForLogbook);
  }

  /**
   * Generated Property Getter for attribute -- X-OFFSET-FOR-LOGBOOK
   * @return the value of the X-OFFSET-FOR-LOGBOOK attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getXOffsetForLogbook() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.X_OFFSET_FOR_LOGBOOK_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- Y-OFFSET-FOR-LOGBOOK
   * @param yOffsetForLogbook new value to conclude for Y-OFFSET-FOR-LOGBOOK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setYOffsetForLogbook(int yOffsetForLogbook) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.Y_OFFSET_FOR_LOGBOOK_, yOffsetForLogbook);
  }

  /**
   * Generated Property Getter for attribute -- Y-OFFSET-FOR-LOGBOOK
   * @return the value of the Y-OFFSET-FOR-LOGBOOK attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getYOffsetForLogbook() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.Y_OFFSET_FOR_LOGBOOK_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-PAGES-TO-SHOW
   * @param maximumNumberOfPagesToShow new value to conclude for MAXIMUM-NUMBER-OF-PAGES-TO-SHOW
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMaximumNumberOfPagesToShow(int maximumNumberOfPagesToShow) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_PAGES_TO_SHOW_, maximumNumberOfPagesToShow);
  }

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-PAGES-TO-SHOW
   * @return the value of the MAXIMUM-NUMBER-OF-PAGES-TO-SHOW attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getMaximumNumberOfPagesToShow() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_PAGES_TO_SHOW_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-PAGES-TO-SHED-AT-LIMIT
   * @param numberOfPagesToShedAtLimit new value to conclude for NUMBER-OF-PAGES-TO-SHED-AT-LIMIT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setNumberOfPagesToShedAtLimit(int numberOfPagesToShedAtLimit) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.NUMBER_OF_PAGES_TO_SHED_AT_LIMIT_, numberOfPagesToShedAtLimit);
  }

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-PAGES-TO-SHED-AT-LIMIT
   * @return the value of the NUMBER-OF-PAGES-TO-SHED-AT-LIMIT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getNumberOfPagesToShedAtLimit() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.NUMBER_OF_PAGES_TO_SHED_AT_LIMIT_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- SPACING-BETWEEN-ENTRIES
   * @param spacingBetweenEntries new value to conclude for SPACING-BETWEEN-ENTRIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setSpacingBetweenEntries(int spacingBetweenEntries) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SPACING_BETWEEN_ENTRIES_, spacingBetweenEntries);
  }

  /**
   * Generated Property Getter for attribute -- SPACING-BETWEEN-ENTRIES
   * @return the value of the SPACING-BETWEEN-ENTRIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getSpacingBetweenEntries() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SPACING_BETWEEN_ENTRIES_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- LOG-INFORM-MESSAGES
   * @param logInformMessages new value to conclude for LOG-INFORM-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setLogInformMessages(boolean logInformMessages) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.LOG_INFORM_MESSAGES_, logInformMessages);
  }

  /**
   * Generated Property Getter for attribute -- LOG-INFORM-MESSAGES
   * @return the value of the LOG-INFORM-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getLogInformMessages() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.LOG_INFORM_MESSAGES_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-PAGES-TO-KEEP-IN-MEMORY
   * @param maximumNumberOfPagesToKeepInMemory new value to conclude for MAXIMUM-NUMBER-OF-PAGES-TO-KEEP-IN-MEMORY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMaximumNumberOfPagesToKeepInMemory(int maximumNumberOfPagesToKeepInMemory) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_PAGES_TO_KEEP_IN_MEMORY_, maximumNumberOfPagesToKeepInMemory);
  }

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-PAGES-TO-KEEP-IN-MEMORY
   * @return the value of the MAXIMUM-NUMBER-OF-PAGES-TO-KEEP-IN-MEMORY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getMaximumNumberOfPagesToKeepInMemory() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MAXIMUM_NUMBER_OF_PAGES_TO_KEEP_IN_MEMORY_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- LIFT-LOGBOOK-TO-TOP-WHEN-NEW-PAGES-ARE-ADDED?
   * @param liftLogbookToTopWhenNewPagesAreAdded new value to conclude for LIFT-LOGBOOK-TO-TOP-WHEN-NEW-PAGES-ARE-ADDED?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setLiftLogbookToTopWhenNewPagesAreAdded(boolean liftLogbookToTopWhenNewPagesAreAdded) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.LIFT_LOGBOOK_TO_TOP_WHEN_NEW_PAGES_ARE_ADDEDQ_, liftLogbookToTopWhenNewPagesAreAdded);
  }

  /**
   * Generated Property Getter for attribute -- LIFT-LOGBOOK-TO-TOP-WHEN-NEW-PAGES-ARE-ADDED?
   * @return the value of the LIFT-LOGBOOK-TO-TOP-WHEN-NEW-PAGES-ARE-ADDED? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getLiftLogbookToTopWhenNewPagesAreAdded() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.LIFT_LOGBOOK_TO_TOP_WHEN_NEW_PAGES_ARE_ADDEDQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- PREFER-NATIVE-LOGBOOK
   * @param preferNativeLogbook new value to conclude for PREFER-NATIVE-LOGBOOK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPreferNativeLogbook(boolean preferNativeLogbook) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PREFER_NATIVE_LOGBOOK_, preferNativeLogbook);
  }

  /**
   * Generated Property Getter for attribute -- PREFER-NATIVE-LOGBOOK
   * @return the value of the PREFER-NATIVE-LOGBOOK attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getPreferNativeLogbook() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PREFER_NATIVE_LOGBOOK_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- INCLUDE-DATE-IN-MESSAGES
   * @param includeDateInMessages new value to conclude for INCLUDE-DATE-IN-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setIncludeDateInMessages(boolean includeDateInMessages) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.INCLUDE_DATE_IN_MESSAGES_, includeDateInMessages);
  }

  /**
   * Generated Property Getter for attribute -- INCLUDE-DATE-IN-MESSAGES
   * @return the value of the INCLUDE-DATE-IN-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getIncludeDateInMessages() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INCLUDE_DATE_IN_MESSAGES_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
