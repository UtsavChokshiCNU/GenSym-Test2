/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      T2beansRegistryImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Feb 08 00:44:42 EST 1999
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

public class T2beansRegistryImpl extends com.gensym.classes.modules.g2evliss.G2EventListenerSupportImpl implements T2beansRegistry {


  static final long serialVersionUID = 2L;
  private static final Symbol BEAN_CLASSES_ = Symbol.intern ("BEAN-CLASSES");

  /* Generated constructors */

  public T2beansRegistryImpl() {
    super();
  }

  public T2beansRegistryImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- BEAN-CLASSES
   * @param beanClasses new value to conclude for BEAN-CLASSES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setBeanClasses(com.gensym.util.Sequence beanClasses) throws G2AccessException {
    setAttributeValue (BEAN_CLASSES_, beanClasses);
  }

  /**
   * Generated Property Getter for attribute -- BEAN-CLASSES
   * @return the value of the BEAN-CLASSES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getBeanClasses() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (BEAN_CLASSES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_ADD_REGISTRY_LISTENER_ = Symbol.intern ("ADD-REGISTRY-LISTENER");
  private static final Symbol MethodName_REMOVE_REGISTRY_LISTENER_ = Symbol.intern ("REMOVE-REGISTRY-LISTENER");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * T2BEANS-REGISTRY::ADD-REGISTRY-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS T2BEANS-REGISTRY,arg1:CLASS REGISTRY-LISTENER) = ()
   */
  @Override
  public  void addRegistryListener(com.gensym.classes.modules.t2beans.RegistryListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_ADD_REGISTRY_LISTENER_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * T2BEANS-REGISTRY::ADD-REGISTRY-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS T2BEANS-REGISTRY,arg1:CLASS REGISTRY-LISTENER) = ()
   */
  @Override
  public  void addG2_RegistryListener(G2_RegistryListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      G2JavaStubController.getG2JavaStubController().addJavaListenerToG2EventSource(this,
                MethodName_ADD_REGISTRY_LISTENER_,
                "com.gensym.classes.modules.t2beans.RegistryListener",
                Symbol.intern("REGISTRY-LISTENER"),
                arg1);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * T2BEANS-REGISTRY::REMOVE-REGISTRY-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS T2BEANS-REGISTRY,arg1:CLASS REGISTRY-LISTENER) = ()
   */
  @Override
  public  void removeRegistryListener(com.gensym.classes.modules.t2beans.RegistryListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_REMOVE_REGISTRY_LISTENER_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * T2BEANS-REGISTRY::REMOVE-REGISTRY-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS T2BEANS-REGISTRY,arg1:CLASS REGISTRY-LISTENER) = ()
   */
  @Override
  public  void removeG2_RegistryListener(G2_RegistryListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      G2JavaStubController.getG2JavaStubController().removeJavaListenerFromG2EventSource(this,
                MethodName_REMOVE_REGISTRY_LISTENER_,
                "com.gensym.classes.modules.t2beans.RegistryListener",
                Symbol.intern("REGISTRY-LISTENER"),
                arg1);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
