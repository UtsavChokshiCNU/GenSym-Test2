/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlPathItemImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Thu Jun 29 19:18:54 EDT 2000
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

public class GdlPathItemImpl extends com.gensym.classes.modules.gdl.GdlObjectImpl implements GdlPathItem {


  static final long serialVersionUID = 2L;
  private static final Symbol NEXT_BLOCKS_ = Symbol.intern ("NEXT-BLOCKS");
  private static final Symbol NUMBER_OF_REMOTE_BLOCKS_ = Symbol.intern ("NUMBER-OF-REMOTE-BLOCKS");
  private static final Symbol NEXT_VORPS_ = Symbol.intern ("NEXT-VORPS");

  /* Generated constructors */

  public GdlPathItemImpl() {
    super();
  }

  public GdlPathItemImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- NEXT-BLOCKS
   * @param nextBlocks new value to conclude for NEXT-BLOCKS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNextBlocks(com.gensym.classes.modules.gdl.GdlPermanentItemArray nextBlocks) throws G2AccessException {
    setAttributeValue (NEXT_BLOCKS_, nextBlocks);
  }

  /**
   * Generated Property Getter for attribute -- NEXT-BLOCKS
   * @return the value of the NEXT-BLOCKS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.classes.modules.gdl.GdlPermanentItemArray getNextBlocks() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (NEXT_BLOCKS_);
    return (com.gensym.classes.modules.gdl.GdlPermanentItemArray)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-REMOTE-BLOCKS
   * @param numberOfRemoteBlocks new value to conclude for NUMBER-OF-REMOTE-BLOCKS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNumberOfRemoteBlocks(int numberOfRemoteBlocks) throws G2AccessException {
    setAttributeValue (NUMBER_OF_REMOTE_BLOCKS_, new Integer (numberOfRemoteBlocks));
  }

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-REMOTE-BLOCKS
   * @return the value of the NUMBER-OF-REMOTE-BLOCKS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getNumberOfRemoteBlocks() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (NUMBER_OF_REMOTE_BLOCKS_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- NEXT-VORPS
   * @param nextVorps new value to conclude for NEXT-VORPS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNextVorps(com.gensym.classes.ItemList nextVorps) throws G2AccessException {
    setAttributeValue (NEXT_VORPS_, nextVorps);
  }

  /**
   * Generated Property Getter for attribute -- NEXT-VORPS
   * @return the value of the NEXT-VORPS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.classes.ItemList getNextVorps() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (NEXT_VORPS_);
    return (com.gensym.classes.ItemList)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_GDL_INITIALIZE_ = Symbol.intern ("GDL-INITIALIZE");
  private static final Symbol MethodName_GDL_RESET_ = Symbol.intern ("GDL-RESET");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM::GDL-INITIALIZE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlInitialize(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_INITIALIZE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM::GDL-RESET
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReset(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_RESET_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
