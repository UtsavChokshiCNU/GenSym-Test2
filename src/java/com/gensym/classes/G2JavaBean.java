/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2JavaBean.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:44:56 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import java.io.*;
import java.util.Vector;
import com.gensym.message.Trace;
import com.gensym.util.*;
import com.gensym.jgi.G2AccessException;

public interface G2JavaBean extends com.gensym.classes.G2ForeignObject {

  public static final Symbol G2_JAVA_BEAN_ = com.gensym.util.symbol.G2ClassSymbols.G2_JAVA_BEAN_;
  static final Symbol g2ClassName = G2_JAVA_BEAN_;
  static final Symbol[] classInheritancePath = new Symbol[] {G2_JAVA_BEAN_, G2_FOREIGN_OBJECT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- INTERNAL-MEDIA-BIN
   * @return the value of the INTERNAL-MEDIA-BIN attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INTERNAL-MEDIA-BIN is : 
   * (OR NoItem
      (Class MEDIA-BIN))
   *
   */
  public com.gensym.classes.MediaBin getInternalMediaBin() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- LATENT-LISTENERS
   * @return the value of the LATENT-LISTENERS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LATENT-LISTENERS is : 
   * (OR NoItem
      (Structure))
   *
   */
  public com.gensym.util.Structure getLatentListeners() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LATENT-LISTENERS
   * @param latentListeners new value to conclude for LATENT-LISTENERS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLatentListeners(com.gensym.util.Structure latentListeners) throws G2AccessException;

  /* Overriden method - SAVE-OBJECT */
  /**
   * Save a template object
   * @param obj the template object to be serialized
   * exception G2AccessException If an error occurs during communication with G2.
   */
  public void saveObject (java.lang.Object obj) throws G2AccessException;

  /* Overriden method - RETRIEVE-OBJECT */
  /**
   * Retrieve a serialized template object from the bean
   * @return The cached Object
   * @exception G2AccessException If an error occurs during communication with G2.
   */
  public java.lang.Object retrieveObject () throws G2AccessException;

}
