/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      DataServerParametersImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:37:38 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class DataServerParametersImpl extends com.gensym.classes.SystemTableImpl implements DataServerParameters {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public DataServerParametersImpl() {
    super();
  }

  public DataServerParametersImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public DataServerParametersImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- PRIORITY-OF-DATA-SERVICE
   * @param priorityOfDataService new value to conclude for PRIORITY-OF-DATA-SERVICE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setPriorityOfDataService(com.gensym.util.Symbol priorityOfDataService) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.PRIORITY_OF_DATA_SERVICE_, priorityOfDataService);
  }

  /**
   * Generated Property Getter for attribute -- PRIORITY-OF-DATA-SERVICE
   * @return the value of the PRIORITY-OF-DATA-SERVICE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getPriorityOfDataService() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.PRIORITY_OF_DATA_SERVICE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- G2-METER-DATA-SERVICE-ON
   * @param g2MeterDataServiceOn new value to conclude for G2-METER-DATA-SERVICE-ON
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setG2MeterDataServiceOn(boolean g2MeterDataServiceOn) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.G2_METER_DATA_SERVICE_ON_, new Boolean (g2MeterDataServiceOn));
  }

  /**
   * Generated Property Getter for attribute -- G2-METER-DATA-SERVICE-ON
   * @return the value of the G2-METER-DATA-SERVICE-ON attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getG2MeterDataServiceOn() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_METER_DATA_SERVICE_ON_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
