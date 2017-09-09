/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2ToG2DataInterfaceImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:45:27 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2ToG2DataInterfaceImpl extends com.gensym.classes.NetworkInterfaceImpl implements G2ToG2DataInterface {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2ToG2DataInterfaceImpl() {
    super();
  }

  public G2ToG2DataInterfaceImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2ToG2DataInterfaceImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- ICP-CONNECTION-SPECIFICATION
   * @param icpConnectionSpecification new value to conclude for ICP-CONNECTION-SPECIFICATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setIcpConnectionSpecification(com.gensym.util.Structure icpConnectionSpecification) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ICP_CONNECTION_SPECIFICATION_, icpConnectionSpecification);
  }

  /**
   * Generated Property Getter for attribute -- ICP-CONNECTION-SPECIFICATION
   * @return the value of the ICP-CONNECTION-SPECIFICATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getIcpConnectionSpecification() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ICP_CONNECTION_SPECIFICATION_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INTERFACE-STATUS
   * @return the value of the INTERFACE-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getInterfaceStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INTERFACE_STATUS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INTERFACE-IS-SECURE
   * @return the value of the INTERFACE-IS-SECURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getInterfaceIsSecure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.INTERFACE_IS_SECURE_);
    return ((Boolean)retnValue).booleanValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
