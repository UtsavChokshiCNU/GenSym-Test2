/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2_RegistryListener.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Feb 08 00:43:56 EST 1999
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

public interface G2_RegistryListener extends java.util.EventListener {

  /**
   * Auto Generated method for G2 Method
   * REGISTRY-LISTENER::HANDLE-REGISTRY-INITIAL-VALUES
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REGISTRY-LISTENER,arg1:CLASS REGISTRY-EVENT) = ()
   */
  public  void handleRegistryInitialValues(G2_RegistryEvent arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REGISTRY-LISTENER::BEAN-ADDED
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REGISTRY-LISTENER,arg1:CLASS REGISTRY-EVENT) = ()
   */
  public  void beanAdded(G2_RegistryEvent arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REGISTRY-LISTENER::BEAN-REMOVED
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REGISTRY-LISTENER,arg1:CLASS REGISTRY-EVENT) = ()
   */
  public  void beanRemoved(G2_RegistryEvent arg1) throws G2AccessException;
  
}
