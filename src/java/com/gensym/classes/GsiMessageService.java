/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GsiMessageService.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:57:11 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface GsiMessageService extends com.gensym.classes.Item {

  public static final Symbol GSI_MESSAGE_SERVICE_ = com.gensym.util.symbol.G2ClassSymbols.GSI_MESSAGE_SERVICE_;
  static final Symbol g2ClassName = GSI_MESSAGE_SERVICE_;
  static final Symbol[] classInheritancePath = new Symbol[] {GSI_MESSAGE_SERVICE_, ITEM_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- GSI-INTERFACE-NAME
   * @return the value of the GSI-INTERFACE-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GSI-INTERFACE-NAME is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getGsiInterfaceName() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GSI-INTERFACE-NAME
   * @param gsiInterfaceName new value to conclude for GSI-INTERFACE-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGsiInterfaceName(com.gensym.util.Symbol gsiInterfaceName) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- DATA-SERVER-FOR-MESSAGES
   * @return the value of the DATA-SERVER-FOR-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DATA-SERVER-FOR-MESSAGES is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getDataServerForMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DATA-SERVER-FOR-MESSAGES
   * @param dataServerForMessages new value to conclude for DATA-SERVER-FOR-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDataServerForMessages(com.gensym.util.Symbol dataServerForMessages) throws G2AccessException;

}
