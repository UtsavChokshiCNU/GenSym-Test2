/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GfiDataServiceImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:56:50 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class GfiDataServiceImpl extends com.gensym.classes.VariableImpl implements GfiDataService {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public GfiDataServiceImpl() {
    super();
  }

  public GfiDataServiceImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public GfiDataServiceImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- GFI-INPUT-INTERFACE-OBJECT
   * @param gfiInputInterfaceObject new value to conclude for GFI-INPUT-INTERFACE-OBJECT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGfiInputInterfaceObject(java.lang.String gfiInputInterfaceObject) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GFI_INPUT_INTERFACE_OBJECT_, gfiInputInterfaceObject);
  }

  /**
   * Generated Property Getter for attribute -- GFI-INPUT-INTERFACE-OBJECT
   * @return the value of the GFI-INPUT-INTERFACE-OBJECT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getGfiInputInterfaceObject() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GFI_INPUT_INTERFACE_OBJECT_);
    return (java.lang.String)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
