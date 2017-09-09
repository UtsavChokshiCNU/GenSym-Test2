/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      SystemItem.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:25:44 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface SystemItem extends com.gensym.classes.Root {

  public static final Symbol SYSTEM_ITEM_ = com.gensym.util.symbol.G2ClassSymbols.SYSTEM_ITEM_;
  static final Symbol g2ClassName = SYSTEM_ITEM_;
  static final Symbol[] classInheritancePath = new Symbol[] {SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- UUID
   * @return the value of the UUID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for UUID is : 
   * Text
   *
   */
  public java.lang.String getUuid() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- UUID
   * @param uuid new value to conclude for UUID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setUuid(java.lang.String uuid) throws G2AccessException;

}
