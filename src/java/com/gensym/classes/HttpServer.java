/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      HttpServer.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JH28)
 *
 *          Date: Tue Aug 28 13:36:54 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface HttpServer extends com.gensym.classes.Object {

  public static final Symbol HTTP_SERVER_ = com.gensym.util.symbol.G2ClassSymbols.HTTP_SERVER_;
  static final Symbol g2ClassName = HTTP_SERVER_;
  static final Symbol[] classInheritancePath = new Symbol[] {HTTP_SERVER_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- HTTP-SERVER-PORT
   * @return the value of the HTTP-SERVER-PORT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for HTTP-SERVER-PORT is : 
   * (OR NoItem
      Integer)
   *
   */
  public java.lang.Integer getHttpServerPort() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- HTTP-SERVER-DISPATCH
   * @return the value of the HTTP-SERVER-DISPATCH attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for HTTP-SERVER-DISPATCH is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getHttpServerDispatch() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- HTTP-SERVER-DISPATCH
   * @param httpServerDispatch new value to conclude for HTTP-SERVER-DISPATCH
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setHttpServerDispatch(com.gensym.util.Symbol httpServerDispatch) throws G2AccessException;

}
