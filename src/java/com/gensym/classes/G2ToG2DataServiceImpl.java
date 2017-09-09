/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2ToG2DataServiceImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:47:29 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2ToG2DataServiceImpl extends com.gensym.classes.VariableImpl implements G2ToG2DataService {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2ToG2DataServiceImpl() {
    super();
  }

  public G2ToG2DataServiceImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2ToG2DataServiceImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- G2-TO-G2-INTERFACE-NAME
   * @param g2ToG2InterfaceName new value to conclude for G2-TO-G2-INTERFACE-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setG2ToG2InterfaceName(com.gensym.util.Symbol g2ToG2InterfaceName) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.G2_TO_G2_INTERFACE_NAME_, g2ToG2InterfaceName);
  }

  /**
   * Generated Property Getter for attribute -- G2-TO-G2-INTERFACE-NAME
   * @return the value of the G2-TO-G2-INTERFACE-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getG2ToG2InterfaceName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_TO_G2_INTERFACE_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- REMOTE-G2-EXPRESSION
   * @param remoteG2Expression new value to conclude for REMOTE-G2-EXPRESSION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setRemoteG2Expression(java.lang.String remoteG2Expression) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.REMOTE_G2_EXPRESSION_, remoteG2Expression);
  }

  /**
   * Generated Property Getter for attribute -- REMOTE-G2-EXPRESSION
   * @return the value of the REMOTE-G2-EXPRESSION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getRemoteG2Expression() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.REMOTE_G2_EXPRESSION_);
    return (java.lang.String)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
