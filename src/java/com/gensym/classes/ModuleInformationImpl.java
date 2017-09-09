/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ModuleInformationImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:01:58 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class ModuleInformationImpl extends com.gensym.classes.SystemTableImpl implements ModuleInformation {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public ModuleInformationImpl() {
    super();
  }

  public ModuleInformationImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public ModuleInformationImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- MODULE-FILE-NAME
   * @param moduleFileName new value to conclude for MODULE-FILE-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setModuleFileName(java.lang.Object moduleFileName) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MODULE_FILE_NAME_, moduleFileName);
  }

  /**
   * Generated Property Getter for attribute -- MODULE-FILE-NAME
   * @return the value of the MODULE-FILE-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getModuleFileName() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MODULE_FILE_NAME_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TOP-LEVEL-MODULE
   * @param topLevelModule new value to conclude for TOP-LEVEL-MODULE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTopLevelModule(com.gensym.util.Symbol topLevelModule) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TOP_LEVEL_MODULE_, topLevelModule);
  }

  /**
   * Generated Property Getter for attribute -- TOP-LEVEL-MODULE
   * @return the value of the TOP-LEVEL-MODULE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getTopLevelModule() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TOP_LEVEL_MODULE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DIRECTLY-REQUIRED-MODULES
   * @param directlyRequiredModules new value to conclude for DIRECTLY-REQUIRED-MODULES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDirectlyRequiredModules(com.gensym.util.Sequence directlyRequiredModules) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.DIRECTLY_REQUIRED_MODULES_, directlyRequiredModules);
  }

  /**
   * Generated Property Getter for attribute -- DIRECTLY-REQUIRED-MODULES
   * @return the value of the DIRECTLY-REQUIRED-MODULES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getDirectlyRequiredModules() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.DIRECTLY_REQUIRED_MODULES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- MODULE-ANNOTATIONS
   * @param moduleAnnotations new value to conclude for MODULE-ANNOTATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setModuleAnnotations(com.gensym.util.Sequence moduleAnnotations) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.MODULE_ANNOTATIONS_, moduleAnnotations);
  }

  /**
   * Generated Property Getter for attribute -- MODULE-ANNOTATIONS
   * @return the value of the MODULE-ANNOTATIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getModuleAnnotations() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.MODULE_ANNOTATIONS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
