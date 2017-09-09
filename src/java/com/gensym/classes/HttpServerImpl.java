/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      HttpServerImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JJ12)
 *
 *          Date: Fri Oct 12 14:11:38 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class HttpServerImpl extends com.gensym.classes.ObjectImpl implements HttpServer {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public HttpServerImpl() {
    super();
  }

  public HttpServerImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public HttpServerImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Getter for attribute -- HTTP-SERVER-PORT
   * @return the value of the HTTP-SERVER-PORT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Integer getHttpServerPort() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.HTTP_SERVER_PORT_);
    return (java.lang.Integer)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- HTTP-SERVER-DISPATCH
   * @param httpServerDispatch new value to conclude for HTTP-SERVER-DISPATCH
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setHttpServerDispatch(com.gensym.util.Symbol httpServerDispatch) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.HTTP_SERVER_DISPATCH_, httpServerDispatch);
  }

  /**
   * Generated Property Getter for attribute -- HTTP-SERVER-DISPATCH
   * @return the value of the HTTP-SERVER-DISPATCH attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getHttpServerDispatch() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.HTTP_SERVER_DISPATCH_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
