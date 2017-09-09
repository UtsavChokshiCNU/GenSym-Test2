/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ColorParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:37:23 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class ColorParametersImpl extends com.gensym.classes.SystemTableImpl implements ColorParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public ColorParametersImpl() {
    super();
  }

  public ColorParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public ColorParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- COLOR-MENU-ORDERING
   * @param colorMenuOrdering new value to conclude for COLOR-MENU-ORDERING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setColorMenuOrdering(com.gensym.util.Symbol colorMenuOrdering) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.COLOR_MENU_ORDERING_, colorMenuOrdering);
  }

  /**
   * Generated Property Getter for attribute -- COLOR-MENU-ORDERING
   * @return the value of the COLOR-MENU-ORDERING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getColorMenuOrdering() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.COLOR_MENU_ORDERING_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- COLORS-ON-1ST-LEVEL-COLOR-MENU
   * @param colorsOn1stLevelColorMenu new value to conclude for COLORS-ON-1ST-LEVEL-COLOR-MENU
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setColorsOn1stLevelColorMenu(java.lang.Object colorsOn1stLevelColorMenu) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.COLORS_ON_1ST_LEVEL_COLOR_MENU_, colorsOn1stLevelColorMenu);
  }

  /**
   * Generated Property Getter for attribute -- COLORS-ON-1ST-LEVEL-COLOR-MENU
   * @return the value of the COLORS-ON-1ST-LEVEL-COLOR-MENU attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getColorsOn1stLevelColorMenu() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.COLORS_ON_1ST_LEVEL_COLOR_MENU_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- COLORS-ON-2ND-LEVEL-COLOR-MENU
   * @param colorsOn2ndLevelColorMenu new value to conclude for COLORS-ON-2ND-LEVEL-COLOR-MENU
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setColorsOn2ndLevelColorMenu(java.lang.Object colorsOn2ndLevelColorMenu) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.COLORS_ON_2ND_LEVEL_COLOR_MENU_, colorsOn2ndLevelColorMenu);
  }

  /**
   * Generated Property Getter for attribute -- COLORS-ON-2ND-LEVEL-COLOR-MENU
   * @return the value of the COLORS-ON-2ND-LEVEL-COLOR-MENU attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getColorsOn2ndLevelColorMenu() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.COLORS_ON_2ND_LEVEL_COLOR_MENU_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-COLUMNS-FOR-1ST-LEVEL-COLOR-MENU
   * @param numberOfColumnsFor1stLevelColorMenu new value to conclude for NUMBER-OF-COLUMNS-FOR-1ST-LEVEL-COLOR-MENU
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setNumberOfColumnsFor1stLevelColorMenu(com.gensym.util.Symbol numberOfColumnsFor1stLevelColorMenu) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.NUMBER_OF_COLUMNS_FOR_1ST_LEVEL_COLOR_MENU_, numberOfColumnsFor1stLevelColorMenu);
  }

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-COLUMNS-FOR-1ST-LEVEL-COLOR-MENU
   * @return the value of the NUMBER-OF-COLUMNS-FOR-1ST-LEVEL-COLOR-MENU attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getNumberOfColumnsFor1stLevelColorMenu() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.NUMBER_OF_COLUMNS_FOR_1ST_LEVEL_COLOR_MENU_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-COLUMNS-FOR-2ND-LEVEL-COLOR-MENU
   * @param numberOfColumnsFor2ndLevelColorMenu new value to conclude for NUMBER-OF-COLUMNS-FOR-2ND-LEVEL-COLOR-MENU
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setNumberOfColumnsFor2ndLevelColorMenu(com.gensym.util.Symbol numberOfColumnsFor2ndLevelColorMenu) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.NUMBER_OF_COLUMNS_FOR_2ND_LEVEL_COLOR_MENU_, numberOfColumnsFor2ndLevelColorMenu);
  }

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-COLUMNS-FOR-2ND-LEVEL-COLOR-MENU
   * @return the value of the NUMBER-OF-COLUMNS-FOR-2ND-LEVEL-COLOR-MENU attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getNumberOfColumnsFor2ndLevelColorMenu() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.NUMBER_OF_COLUMNS_FOR_2ND_LEVEL_COLOR_MENU_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DISMISS-COLOR-MENU-AFTER-CHOOSING?
   * @param dismissColorMenuAfterChoosing new value to conclude for DISMISS-COLOR-MENU-AFTER-CHOOSING?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDismissColorMenuAfterChoosing(boolean dismissColorMenuAfterChoosing) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DISMISS_COLOR_MENU_AFTER_CHOOSINGQ_, new Boolean (dismissColorMenuAfterChoosing));
  }

  /**
   * Generated Property Getter for attribute -- DISMISS-COLOR-MENU-AFTER-CHOOSING?
   * @return the value of the DISMISS-COLOR-MENU-AFTER-CHOOSING? attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getDismissColorMenuAfterChoosing() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DISMISS_COLOR_MENU_AFTER_CHOOSINGQ_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
