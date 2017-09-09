/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      SystemItemImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:25:55 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class SystemItemImpl extends com.gensym.classes.RootImpl implements SystemItem {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public SystemItemImpl() {
    super();
  }

  public SystemItemImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public SystemItemImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- UUID
   * @param uuid new value to conclude for UUID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setUuid(java.lang.String uuid) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.UUID_, uuid);
  }

  /**
   * Generated Property Getter for attribute -- UUID
   * @return the value of the UUID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getUuid() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.UUID_);
    return (java.lang.String)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
