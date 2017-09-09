/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      LogbookParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:25:53 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface LogbookParameters extends com.gensym.classes.SystemTable {

  public static final Symbol LOGBOOK_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.LOGBOOK_PARAMETERS_;
  static final Symbol g2ClassName = LOGBOOK_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {LOGBOOK_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- WIDTH-FOR-PAGES
   * @return the value of the WIDTH-FOR-PAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for WIDTH-FOR-PAGES is : 
   * Integer
   *
   */
  public int getWidthForPages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- WIDTH-FOR-PAGES
   * @param widthForPages new value to conclude for WIDTH-FOR-PAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setWidthForPages(int widthForPages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- HEIGHT-FOR-PAGES
   * @return the value of the HEIGHT-FOR-PAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for HEIGHT-FOR-PAGES is : 
   * Integer
   *
   */
  public int getHeightForPages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- HEIGHT-FOR-PAGES
   * @param heightForPages new value to conclude for HEIGHT-FOR-PAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setHeightForPages(int heightForPages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MARGIN-FOR-PAGES
   * @return the value of the MARGIN-FOR-PAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MARGIN-FOR-PAGES is : 
   * Integer
   *
   */
  public int getMarginForPages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MARGIN-FOR-PAGES
   * @param marginForPages new value to conclude for MARGIN-FOR-PAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMarginForPages(int marginForPages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- X-OFFSET-FOR-NEXT-PAGE
   * @return the value of the X-OFFSET-FOR-NEXT-PAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for X-OFFSET-FOR-NEXT-PAGE is : 
   * Integer
   *
   */
  public int getXOffsetForNextPage() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- X-OFFSET-FOR-NEXT-PAGE
   * @param xOffsetForNextPage new value to conclude for X-OFFSET-FOR-NEXT-PAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setXOffsetForNextPage(int xOffsetForNextPage) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- Y-OFFSET-FOR-NEXT-PAGE
   * @return the value of the Y-OFFSET-FOR-NEXT-PAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for Y-OFFSET-FOR-NEXT-PAGE is : 
   * Integer
   *
   */
  public int getYOffsetForNextPage() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- Y-OFFSET-FOR-NEXT-PAGE
   * @param yOffsetForNextPage new value to conclude for Y-OFFSET-FOR-NEXT-PAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setYOffsetForNextPage(int yOffsetForNextPage) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- X-OFFSET-FOR-LOGBOOK
   * @return the value of the X-OFFSET-FOR-LOGBOOK attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for X-OFFSET-FOR-LOGBOOK is : 
   * Integer
   *
   */
  public int getXOffsetForLogbook() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- X-OFFSET-FOR-LOGBOOK
   * @param xOffsetForLogbook new value to conclude for X-OFFSET-FOR-LOGBOOK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setXOffsetForLogbook(int xOffsetForLogbook) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- Y-OFFSET-FOR-LOGBOOK
   * @return the value of the Y-OFFSET-FOR-LOGBOOK attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for Y-OFFSET-FOR-LOGBOOK is : 
   * Integer
   *
   */
  public int getYOffsetForLogbook() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- Y-OFFSET-FOR-LOGBOOK
   * @param yOffsetForLogbook new value to conclude for Y-OFFSET-FOR-LOGBOOK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setYOffsetForLogbook(int yOffsetForLogbook) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-PAGES-TO-SHOW
   * @return the value of the MAXIMUM-NUMBER-OF-PAGES-TO-SHOW attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MAXIMUM-NUMBER-OF-PAGES-TO-SHOW is : 
   * Integer
   *
   */
  public int getMaximumNumberOfPagesToShow() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-PAGES-TO-SHOW
   * @param maximumNumberOfPagesToShow new value to conclude for MAXIMUM-NUMBER-OF-PAGES-TO-SHOW
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMaximumNumberOfPagesToShow(int maximumNumberOfPagesToShow) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-PAGES-TO-SHED-AT-LIMIT
   * @return the value of the NUMBER-OF-PAGES-TO-SHED-AT-LIMIT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NUMBER-OF-PAGES-TO-SHED-AT-LIMIT is : 
   * Integer
   *
   */
  public int getNumberOfPagesToShedAtLimit() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-PAGES-TO-SHED-AT-LIMIT
   * @param numberOfPagesToShedAtLimit new value to conclude for NUMBER-OF-PAGES-TO-SHED-AT-LIMIT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNumberOfPagesToShedAtLimit(int numberOfPagesToShedAtLimit) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SPACING-BETWEEN-ENTRIES
   * @return the value of the SPACING-BETWEEN-ENTRIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SPACING-BETWEEN-ENTRIES is : 
   * Integer
   *
   */
  public int getSpacingBetweenEntries() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SPACING-BETWEEN-ENTRIES
   * @param spacingBetweenEntries new value to conclude for SPACING-BETWEEN-ENTRIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSpacingBetweenEntries(int spacingBetweenEntries) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- LOG-INFORM-MESSAGES
   * @return the value of the LOG-INFORM-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LOG-INFORM-MESSAGES is : 
   * BooleanTruthValue
   *
   */
  public boolean getLogInformMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LOG-INFORM-MESSAGES
   * @param logInformMessages new value to conclude for LOG-INFORM-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLogInformMessages(boolean logInformMessages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- MAXIMUM-NUMBER-OF-PAGES-TO-KEEP-IN-MEMORY
   * @return the value of the MAXIMUM-NUMBER-OF-PAGES-TO-KEEP-IN-MEMORY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for MAXIMUM-NUMBER-OF-PAGES-TO-KEEP-IN-MEMORY is : 
   * Integer
   *
   */
  public int getMaximumNumberOfPagesToKeepInMemory() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- MAXIMUM-NUMBER-OF-PAGES-TO-KEEP-IN-MEMORY
   * @param maximumNumberOfPagesToKeepInMemory new value to conclude for MAXIMUM-NUMBER-OF-PAGES-TO-KEEP-IN-MEMORY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setMaximumNumberOfPagesToKeepInMemory(int maximumNumberOfPagesToKeepInMemory) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- LIFT-LOGBOOK-TO-TOP-WHEN-NEW-PAGES-ARE-ADDED?
   * @return the value of the LIFT-LOGBOOK-TO-TOP-WHEN-NEW-PAGES-ARE-ADDED? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LIFT-LOGBOOK-TO-TOP-WHEN-NEW-PAGES-ARE-ADDED? is : 
   * BooleanTruthValue
   *
   */
  public boolean getLiftLogbookToTopWhenNewPagesAreAdded() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LIFT-LOGBOOK-TO-TOP-WHEN-NEW-PAGES-ARE-ADDED?
   * @param liftLogbookToTopWhenNewPagesAreAdded new value to conclude for LIFT-LOGBOOK-TO-TOP-WHEN-NEW-PAGES-ARE-ADDED?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLiftLogbookToTopWhenNewPagesAreAdded(boolean liftLogbookToTopWhenNewPagesAreAdded) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PREFER-NATIVE-LOGBOOK
   * @return the value of the PREFER-NATIVE-LOGBOOK attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PREFER-NATIVE-LOGBOOK is : 
   * BooleanTruthValue
   *
   */
  public boolean getPreferNativeLogbook() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- PREFER-NATIVE-LOGBOOK
   * @param preferNativeLogbook new value to conclude for PREFER-NATIVE-LOGBOOK
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setPreferNativeLogbook(boolean preferNativeLogbook) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INCLUDE-DATE-IN-MESSAGES
   * @return the value of the INCLUDE-DATE-IN-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INCLUDE-DATE-IN-MESSAGES is : 
   * BooleanTruthValue
   *
   */
  public boolean getIncludeDateInMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INCLUDE-DATE-IN-MESSAGES
   * @param includeDateInMessages new value to conclude for INCLUDE-DATE-IN-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setIncludeDateInMessages(boolean includeDateInMessages) throws G2AccessException;

}
