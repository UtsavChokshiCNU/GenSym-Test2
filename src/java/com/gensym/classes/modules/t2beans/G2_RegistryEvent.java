/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2_RegistryEvent.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Feb 08 00:43:42 EST 1999
 *
 */


package com.gensym.classes.modules.t2beans;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class G2_RegistryEvent extends com.gensym.classes.G2_ExternalEventObjectRoot {


  
  private static Sequence userAttributeList;
  

  static final long serialVersionUID = 2L;
  private static final Symbol CLASS_DATA_ = Symbol.intern ("CLASS-DATA");


  /* Generated constructor */

  public G2_RegistryEvent(java.lang.Object source, Item g2EventObject) {
    super(source, g2EventObject);
  };

  /**
   * Generated Property Getter for attribute -- CLASS-DATA
   * @return the value of the CLASS-DATA attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getClassData() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (CLASS_DATA_);
    return (java.lang.Object)retnValue;
  }

  
  /**
  * Return the attributes that this External event will "preload" from
  * G2 at creation.
  */
  public static Sequence getAttributeList() {

    if (userAttributeList == null) {
      userAttributeList = new Sequence(5);
      userAttributeList.addElement(SOURCE_);
      userAttributeList.addElement(CLASS_DATA_);
    }
    return userAttributeList;
  }
  
}
