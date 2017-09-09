/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      RemoteProcedureDeclarationImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:07:42 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class RemoteProcedureDeclarationImpl extends com.gensym.classes.StatementImpl implements RemoteProcedureDeclaration {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public RemoteProcedureDeclarationImpl() {
    super();
  }

  public RemoteProcedureDeclarationImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public RemoteProcedureDeclarationImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
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
   * Generated Property Setter for attribute -- NAME-IN-REMOTE-SYSTEM
   * @param nameInRemoteSystem new value to conclude for NAME-IN-REMOTE-SYSTEM
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setNameInRemoteSystem(java.lang.String nameInRemoteSystem) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.NAME_IN_REMOTE_SYSTEM_, nameInRemoteSystem);
  }

  /**
   * Generated Property Getter for attribute -- NAME-IN-REMOTE-SYSTEM
   * @return the value of the NAME-IN-REMOTE-SYSTEM attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.String getNameInRemoteSystem() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.NAME_IN_REMOTE_SYSTEM_);
    return (java.lang.String)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
