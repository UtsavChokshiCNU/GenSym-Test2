/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2Socket.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JJ12)
 *
 *          Date: Fri Oct 12 14:15:08 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface G2Socket extends com.gensym.classes.Item, com.gensym.classes.Entity {

  public static final Symbol G2_SOCKET_ = com.gensym.util.symbol.G2ClassSymbols.G2_SOCKET_;
  static final Symbol g2ClassName = G2_SOCKET_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2_SOCKET_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- G2-SOCKET-PORT
   * @return the value of the G2-SOCKET-PORT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-SOCKET-PORT is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text
      (Sequence)
      (Structure))
   *
   */
  public java.lang.Object getG2SocketPort() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-SOCKET-STATUS
   * @return the value of the G2-SOCKET-STATUS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-SOCKET-STATUS is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text
      (Sequence)
      (Structure))
   *
   */
  public java.lang.Object getG2SocketStatus() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-SOCKET-REMOTE-HOST
   * @return the value of the G2-SOCKET-REMOTE-HOST attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-SOCKET-REMOTE-HOST is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text
      (Sequence)
      (Structure))
   *
   */
  public java.lang.Object getG2SocketRemoteHost() throws G2AccessException;

}
