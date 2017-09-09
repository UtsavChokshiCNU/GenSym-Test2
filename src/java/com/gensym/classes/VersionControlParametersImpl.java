/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      VersionControlParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JJ11)
 *
 *          Date: Thu Oct 11 15:46:08 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class VersionControlParametersImpl extends com.gensym.classes.SystemTableImpl implements VersionControlParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public VersionControlParametersImpl() {
    super();
  }

  public VersionControlParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public VersionControlParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- ENABLE-KB-CHANGE-LOGGING
   * @param enableKbChangeLogging new value to conclude for ENABLE-KB-CHANGE-LOGGING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setEnableKbChangeLogging(boolean enableKbChangeLogging) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ENABLE_KB_CHANGE_LOGGING_, new Boolean (enableKbChangeLogging));
  }

  /**
   * Generated Property Getter for attribute -- ENABLE-KB-CHANGE-LOGGING
   * @return the value of the ENABLE-KB-CHANGE-LOGGING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getEnableKbChangeLogging() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ENABLE_KB_CHANGE_LOGGING_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
