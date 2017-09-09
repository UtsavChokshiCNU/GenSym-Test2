/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2MeterDataServiceImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:45:15 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2MeterDataServiceImpl extends com.gensym.classes.VariableImpl implements G2MeterDataService {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2MeterDataServiceImpl() {
    super();
  }

  public G2MeterDataServiceImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2MeterDataServiceImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- G2-METER-NAME
   * @param g2MeterName new value to conclude for G2-METER-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setG2MeterName(com.gensym.util.Symbol g2MeterName) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.G2_METER_NAME_, g2MeterName);
  }

  /**
   * Generated Property Getter for attribute -- G2-METER-NAME
   * @return the value of the G2-METER-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getG2MeterName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_METER_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
