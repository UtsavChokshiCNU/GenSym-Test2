/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      RegistryListenerImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Feb 08 00:44:39 EST 1999
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

public class RegistryListenerImpl extends com.gensym.classes.modules.g2evliss.G2EventListenerImpl implements RegistryListener {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public RegistryListenerImpl() {
    super();
  }

  public RegistryListenerImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  // Method Name Constants
  private static final Symbol MethodName_HANDLE_REGISTRY_INITIAL_VALUES_ = Symbol.intern ("HANDLE-REGISTRY-INITIAL-VALUES");
  private static final Symbol MethodName_BEAN_ADDED_ = Symbol.intern ("BEAN-ADDED");
  private static final Symbol MethodName_BEAN_REMOVED_ = Symbol.intern ("BEAN-REMOVED");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * REGISTRY-LISTENER::HANDLE-REGISTRY-INITIAL-VALUES
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REGISTRY-LISTENER,arg1:CLASS REGISTRY-EVENT) = ()
   */
  @Override
  public  void handleRegistryInitialValues(com.gensym.classes.modules.t2beans.RegistryEvent arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_HANDLE_REGISTRY_INITIAL_VALUES_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REGISTRY-LISTENER::BEAN-ADDED
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REGISTRY-LISTENER,arg1:CLASS REGISTRY-EVENT) = ()
   */
  @Override
  public  void beanAdded(com.gensym.classes.modules.t2beans.RegistryEvent arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_BEAN_ADDED_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REGISTRY-LISTENER::BEAN-REMOVED
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REGISTRY-LISTENER,arg1:CLASS REGISTRY-EVENT) = ()
   */
  @Override
  public  void beanRemoved(com.gensym.classes.modules.t2beans.RegistryEvent arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_BEAN_REMOVED_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
