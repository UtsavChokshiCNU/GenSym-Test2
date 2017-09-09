/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GsiMessageServiceImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:57:12 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class GsiMessageServiceImpl extends com.gensym.classes.ItemImpl implements GsiMessageService {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public GsiMessageServiceImpl() {
    super();
  }

  public GsiMessageServiceImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public GsiMessageServiceImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- GSI-INTERFACE-NAME
   * @param gsiInterfaceName new value to conclude for GSI-INTERFACE-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setGsiInterfaceName(com.gensym.util.Symbol gsiInterfaceName) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.GSI_INTERFACE_NAME_, gsiInterfaceName);
  }

  /**
   * Generated Property Getter for attribute -- GSI-INTERFACE-NAME
   * @return the value of the GSI-INTERFACE-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getGsiInterfaceName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.GSI_INTERFACE_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DATA-SERVER-FOR-MESSAGES
   * @param dataServerForMessages new value to conclude for DATA-SERVER-FOR-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDataServerForMessages(com.gensym.util.Symbol dataServerForMessages) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DATA_SERVER_FOR_MESSAGES_, dataServerForMessages);
  }

  /**
   * Generated Property Getter for attribute -- DATA-SERVER-FOR-MESSAGES
   * @return the value of the DATA-SERVER-FOR-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getDataServerForMessages() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DATA_SERVER_FOR_MESSAGES_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
