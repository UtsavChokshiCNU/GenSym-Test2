/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      MessageDefinitionImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:38 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class MessageDefinitionImpl extends com.gensym.classes.ClassDefinitionImpl implements MessageDefinition {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public MessageDefinitionImpl() {
    super();
  }

  public MessageDefinitionImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public MessageDefinitionImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- DEFAULT-MESSAGE-PROPERTIES
   * @param defaultMessageProperties new value to conclude for DEFAULT-MESSAGE-PROPERTIES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDefaultMessageProperties(com.gensym.util.Structure defaultMessageProperties) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DEFAULT_MESSAGE_PROPERTIES_, defaultMessageProperties);
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-MESSAGE-PROPERTIES
   * @return the value of the DEFAULT-MESSAGE-PROPERTIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getDefaultMessageProperties() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DEFAULT_MESSAGE_PROPERTIES_);
    return (com.gensym.util.Structure)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
