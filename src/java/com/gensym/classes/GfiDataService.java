/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GfiDataService.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:56:41 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface GfiDataService extends com.gensym.classes.Variable {

  public static final Symbol GFI_DATA_SERVICE_ = com.gensym.util.symbol.G2ClassSymbols.GFI_DATA_SERVICE_;
  static final Symbol g2ClassName = GFI_DATA_SERVICE_;
  static final Symbol[] classInheritancePath = new Symbol[] {GFI_DATA_SERVICE_, VARIABLE_, VARIABLE_OR_PARAMETER_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- GFI-INPUT-INTERFACE-OBJECT
   * @return the value of the GFI-INPUT-INTERFACE-OBJECT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GFI-INPUT-INTERFACE-OBJECT is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getGfiInputInterfaceObject() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GFI-INPUT-INTERFACE-OBJECT
   * @param gfiInputInterfaceObject new value to conclude for GFI-INPUT-INTERFACE-OBJECT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGfiInputInterfaceObject(java.lang.String gfiInputInterfaceObject) throws G2AccessException;

}
