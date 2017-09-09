/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2_GdlPathItemEventListener.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon May 15 14:06:36 GMT+04:00 2000
 *
 */


package com.gensym.classes.modules.gdluisup;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface G2_GdlPathItemEventListener extends java.util.EventListener {

  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM-EVENT-LISTENER::PATH-DATA-UPDATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM-EVENT-LISTENER,arg1:CLASS GDL-PATH-ITEM-EVENT) = ()
   */
  public  void pathDataUpdate(com.gensym.classes.modules.gdluisup.G2_GdlPathItemEvent arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM-EVENT-LISTENER::TERMINATE-PATH-ITEM-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM-EVENT-LISTENER,arg1:CLASS GDL-PATH-ITEM-EVENT) = ()
   */
  public  void terminatePathItemEventListener(com.gensym.classes.modules.gdluisup.G2_GdlPathItemEvent arg1) throws G2AccessException;
  
}
