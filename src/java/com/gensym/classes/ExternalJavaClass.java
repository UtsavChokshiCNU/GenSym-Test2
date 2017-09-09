/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ExternalJavaClass.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:41:03 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface ExternalJavaClass extends com.gensym.classes.Item, com.gensym.classes.Entity {

  public static final Symbol EXTERNAL_JAVA_CLASS_ = com.gensym.util.symbol.G2ClassSymbols.EXTERNAL_JAVA_CLASS_;
  static final Symbol g2ClassName = EXTERNAL_JAVA_CLASS_;
  static final Symbol[] classInheritancePath = new Symbol[] {EXTERNAL_JAVA_CLASS_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- DERIVE-NAMES-AUTOMATICALLY?
   * @return the value of the DERIVE-NAMES-AUTOMATICALLY? attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DERIVE-NAMES-AUTOMATICALLY? is : 
   * BooleanTruthValue
   *
   */
  public boolean getDeriveNamesAutomatically() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DERIVE-NAMES-AUTOMATICALLY?
   * @param deriveNamesAutomatically new value to conclude for DERIVE-NAMES-AUTOMATICALLY?
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDeriveNamesAutomatically(boolean deriveNamesAutomatically) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JAVA-CLASS-AND-INTERFACE-NAMES
   * @return the value of the JAVA-CLASS-AND-INTERFACE-NAMES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JAVA-CLASS-AND-INTERFACE-NAMES is : 
   * (Sequence Text 0)
   *
   */
  public com.gensym.util.Sequence getJavaClassAndInterfaceNames() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- JAVA-SYNTAX-VERSION
   * @return the value of the JAVA-SYNTAX-VERSION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for JAVA-SYNTAX-VERSION is : 
   * (OR NoItem
      Symbol
      BooleanTruthValue
      Quantity
      Text
      (Sequence)
      (Structure))
   *
   */
  public java.lang.Object getJavaSyntaxVersion() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- PACKAGE-DECLARATION
   * @return the value of the PACKAGE-DECLARATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for PACKAGE-DECLARATION is : 
   * (Sequence Text 0)
   *
   */
  public com.gensym.util.Sequence getPackageDeclaration() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- IMPORT-DECLARATIONS
   * @return the value of the IMPORT-DECLARATIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for IMPORT-DECLARATIONS is : 
   * (Sequence 
    (Sequence Text 0)
    0))
   *
   */
  public com.gensym.util.Sequence getImportDeclarations() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TEXT
   * @return the value of the TEXT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TEXT is : 
   * Text
   *
   */
  public java.lang.String getText() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TEXT
   * @param text new value to conclude for TEXT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setText(java.lang.String text) throws G2AccessException;

}
