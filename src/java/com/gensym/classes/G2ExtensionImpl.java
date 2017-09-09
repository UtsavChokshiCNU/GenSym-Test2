/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2ExtensionImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:47:39 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class G2ExtensionImpl extends com.gensym.classes.ObjectImpl implements G2Extension {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public G2ExtensionImpl() {
    super();
  }

  public G2ExtensionImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public G2ExtensionImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Getter for attribute -- G2-USER-NAME
   * @return the value of the G2-USER-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2UserName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_USER_NAME_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2-CONNECTION-STATUS
   * @return the value of the G2-CONNECTION-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2ConnectionStatus() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_CONNECTION_STATUS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2-ROUTING-INFORMATION
   * @return the value of the G2-ROUTING-INFORMATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getG2RoutingInformation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_ROUTING_INFORMATION_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
