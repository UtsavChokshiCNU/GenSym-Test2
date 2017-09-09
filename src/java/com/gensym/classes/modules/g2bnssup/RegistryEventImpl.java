/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      RegistryEventImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 0 (H15)
 *
 *          Date: Tue Dec 01 13:37:04 EST 1998
 *
 */


package com.gensym.classes.modules.g2bnssup;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class RegistryEventImpl extends com.gensym.classes.modules.g2evliss.G2EventObjectImpl implements RegistryEvent {


  static final long serialVersionUID = 2L;
  private static final Symbol CLASS_DATA_ = Symbol.intern ("CLASS-DATA");

  /* Generated constructors */

  public RegistryEventImpl() {
    super();
  }

  public RegistryEventImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- CLASS-DATA
   * @param classData new value to conclude for CLASS-DATA
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setClassData(java.lang.Object classData) throws G2AccessException {
    setAttributeValue (CLASS_DATA_, classData);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-DATA
   * @return the value of the CLASS-DATA attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getClassData() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (CLASS_DATA_);
    return (java.lang.Object)retnValue;
  }

  /* com.gensym.classes.G2_EventObject support */
  @Override
  public Class getExternalEventClass() {
    return com.gensym.classes.modules.g2bnssup.G2_RegistryEvent.class;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
