/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ItemReferenceParameters.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 6.0 Alpha 0 (BL14)
 *
 *          Date: Mon Dec 20 16:05:34 EST 1999
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface ItemReferenceParameters extends com.gensym.classes.SystemTable {

  public static final Symbol ITEM_REFERENCE_PARAMETERS_ = com.gensym.util.symbol.G2ClassSymbols.ITEM_REFERENCE_PARAMETERS_;
  static final Symbol g2ClassName = ITEM_REFERENCE_PARAMETERS_;
  static final Symbol[] classInheritancePath = new Symbol[] {ITEM_REFERENCE_PARAMETERS_, SYSTEM_TABLE_, ITEM_, SYSTEM_FRAME_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- SHOW-UUIDS-IN-ATTRIBUTE-TABLES
   * @return the value of the SHOW-UUIDS-IN-ATTRIBUTE-TABLES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SHOW-UUIDS-IN-ATTRIBUTE-TABLES is : 
   * BooleanTruthValue
   *
   */
  public boolean getShowUuidsInAttributeTables() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SHOW-UUIDS-IN-ATTRIBUTE-TABLES
   * @param showUuidsInAttributeTables new value to conclude for SHOW-UUIDS-IN-ATTRIBUTE-TABLES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setShowUuidsInAttributeTables(boolean showUuidsInAttributeTables) throws G2AccessException;

}
