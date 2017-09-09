/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ItemReferenceParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 6.0 Alpha 0 (BL14)
 *
 *          Date: Mon Dec 20 16:30:56 EST 1999
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class ItemReferenceParametersImpl extends com.gensym.classes.SystemTableImpl implements ItemReferenceParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public ItemReferenceParametersImpl() {
    super();
  }

  public ItemReferenceParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }

  public ItemReferenceParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }

  /**
   * Generated Property Setter for attribute -- SHOW-UUIDS-IN-ATTRIBUTE-TABLES
   * @param showUuidsInAttributeTables new value to conclude for SHOW-UUIDS-IN-ATTRIBUTE-TABLES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setShowUuidsInAttributeTables(boolean showUuidsInAttributeTables) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.SHOW_UUIDS_IN_ATTRIBUTE_TABLES_, new Boolean (showUuidsInAttributeTables));
  }

  /**
   * Generated Property Getter for attribute -- SHOW-UUIDS-IN-ATTRIBUTE-TABLES
   * @return the value of the SHOW-UUIDS-IN-ATTRIBUTE-TABLES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getShowUuidsInAttributeTables() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.SHOW_UUIDS_IN_ATTRIBUTE_TABLES_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
