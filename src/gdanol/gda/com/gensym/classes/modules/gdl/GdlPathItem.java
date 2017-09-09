/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlPathItem.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Thu Jun 29 19:17:48 EDT 2000
 *
 */


package com.gensym.classes.modules.gdl;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GdlPathItem extends com.gensym.classes.modules.gdl.GdlObject {

  public static final Symbol GDL_PATH_ITEM_ = Symbol.intern ("GDL-PATH-ITEM");
  static final Symbol g2ClassName = GDL_PATH_ITEM_;
  static final Symbol[] classInheritancePath = new Symbol[] {GDL_PATH_ITEM_, GDL_OBJECT_, GFR_OBJECT_WITH_UUID_, OBJECT_, GFR_ITEM_WITH_UUID_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- NEXT-BLOCKS
   * @return the value of the NEXT-BLOCKS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NEXT-BLOCKS is : 
   * (Class GDL-PERMANENT-ITEM-ARRAY)
   *
   */
  public com.gensym.classes.modules.gdl.GdlPermanentItemArray getNextBlocks() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NEXT-BLOCKS
   * @param nextBlocks new value to conclude for NEXT-BLOCKS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNextBlocks(com.gensym.classes.modules.gdl.GdlPermanentItemArray nextBlocks) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-REMOTE-BLOCKS
   * @return the value of the NUMBER-OF-REMOTE-BLOCKS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NUMBER-OF-REMOTE-BLOCKS is : 
   * Integer
   *
   */
  public int getNumberOfRemoteBlocks() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-REMOTE-BLOCKS
   * @param numberOfRemoteBlocks new value to conclude for NUMBER-OF-REMOTE-BLOCKS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNumberOfRemoteBlocks(int numberOfRemoteBlocks) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NEXT-VORPS
   * @return the value of the NEXT-VORPS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NEXT-VORPS is : 
   * (Class ITEM-LIST)
   *
   */
  public com.gensym.classes.ItemList getNextVorps() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NEXT-VORPS
   * @param nextVorps new value to conclude for NEXT-VORPS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNextVorps(com.gensym.classes.ItemList nextVorps) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM::GDL-INITIALIZE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlInitialize(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM::GDL-RESET
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReset(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
}
