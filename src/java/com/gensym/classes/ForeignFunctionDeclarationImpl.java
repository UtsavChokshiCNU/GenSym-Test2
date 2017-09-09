/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ForeignFunctionDeclarationImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:42:09 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class ForeignFunctionDeclarationImpl extends com.gensym.classes.StatementImpl implements ForeignFunctionDeclaration {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public ForeignFunctionDeclarationImpl() {
    super();
  }

  public ForeignFunctionDeclarationImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public ForeignFunctionDeclarationImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAuthors(com.gensym.util.Structure authors) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.AUTHORS_, authors);
  }

  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getAuthors() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.AUTHORS_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getChangeLog() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CHANGE_LOG_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- NAME-IN-FOREIGN-IMAGE
   * @param nameInForeignImage new value to conclude for NAME-IN-FOREIGN-IMAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setNameInForeignImage(java.lang.String nameInForeignImage) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.NAME_IN_FOREIGN_IMAGE_, nameInForeignImage);
  }

  /**
   * Generated Property Getter for attribute -- NAME-IN-FOREIGN-IMAGE
   * @return the value of the NAME-IN-FOREIGN-IMAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getNameInForeignImage() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.NAME_IN_FOREIGN_IMAGE_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TIMEOUT-INTERVAL
   * @param timeoutInterval new value to conclude for TIMEOUT-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTimeoutInterval(java.lang.Object timeoutInterval) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.TIMEOUT_INTERVAL_, timeoutInterval);
  }

  /**
   * Generated Property Getter for attribute -- TIMEOUT-INTERVAL
   * @return the value of the TIMEOUT-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getTimeoutInterval() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.TIMEOUT_INTERVAL_);
    return (java.lang.Object)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
