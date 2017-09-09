/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2_EventSourceListener.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Sep 21 13:49:53 EDT 2007
 *
 */


package com.gensym.classes.modules.jgidemo;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface G2_EventSourceListener extends java.util.EventListener {

  /**
   * Auto Generated method for G2 Method
   * EVENT-SOURCE-LISTENER::AN-EVENT
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS EVENT-SOURCE-LISTENER,arg1:CLASS EVENT-SOURCE-EVENT) = ()
   */
  public  void anEvent(com.gensym.classes.modules.jgidemo.G2_EventSourceEvent arg1) throws G2AccessException;
  
}
