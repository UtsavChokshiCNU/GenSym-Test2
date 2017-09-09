/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2bnssupRegistry.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 0 (H15)
 *
 *          Date: Tue Dec 01 13:37:01 EST 1998
 *
 */


package com.gensym.classes.modules.g2bnssup;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface G2bnssupRegistry extends com.gensym.classes.modules.g2evliss.G2EventListenerSupport {

  public static final Symbol G2BNSSUP_REGISTRY_ = Symbol.intern ("G2BNSSUP-REGISTRY");
  static final Symbol g2ClassName = G2BNSSUP_REGISTRY_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2BNSSUP_REGISTRY_, G2_EVENT_LISTENER_SUPPORT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- BEAN-CLASSES
   * @return the value of the BEAN-CLASSES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for BEAN-CLASSES is : 
   * (Sequence)
   *
   */
  public com.gensym.util.Sequence getBeanClasses() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- BEAN-CLASSES
   * @param beanClasses new value to conclude for BEAN-CLASSES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setBeanClasses(com.gensym.util.Sequence beanClasses) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * G2BNSSUP-REGISTRY::ADD-REGISTRY-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2BNSSUP-REGISTRY,arg1:CLASS REGISTRY-LISTENER) = ()
   */
  public  void addRegistryListener(com.gensym.classes.modules.g2bnssup.RegistryListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * G2BNSSUP-REGISTRY::ADD-REGISTRY-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2BNSSUP-REGISTRY,arg1:CLASS REGISTRY-LISTENER) = ()
   */
  public  void addG2_RegistryListener(G2_RegistryListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * G2BNSSUP-REGISTRY::REMOVE-REGISTRY-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2BNSSUP-REGISTRY,arg1:CLASS REGISTRY-LISTENER) = ()
   */
  public  void removeRegistryListener(com.gensym.classes.modules.g2bnssup.RegistryListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * G2BNSSUP-REGISTRY::REMOVE-REGISTRY-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2BNSSUP-REGISTRY,arg1:CLASS REGISTRY-LISTENER) = ()
   */
  public  void removeG2_RegistryListener(G2_RegistryListener arg1) throws G2AccessException;
  
}
