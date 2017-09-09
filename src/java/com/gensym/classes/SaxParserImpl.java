/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      SaxParserImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JJ11)
 *
 *          Date: Thu Oct 11 15:37:30 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class SaxParserImpl extends com.gensym.classes.ObjectImpl implements SaxParser {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public SaxParserImpl() {
    super();
  }

  public SaxParserImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public SaxParserImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
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
   * Generated Property Getter for attribute -- NUMBER-OF-PENDING-CALLBACKS
   * @return the value of the NUMBER-OF-PENDING-CALLBACKS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getNumberOfPendingCallbacks() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.NUMBER_OF_PENDING_CALLBACKS_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- START-DOCUMENT-PROCEDURE
   * @param startDocumentProcedure new value to conclude for START-DOCUMENT-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setStartDocumentProcedure(com.gensym.util.Symbol startDocumentProcedure) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.START_DOCUMENT_PROCEDURE_, startDocumentProcedure);
  }

  /**
   * Generated Property Getter for attribute -- START-DOCUMENT-PROCEDURE
   * @return the value of the START-DOCUMENT-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getStartDocumentProcedure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.START_DOCUMENT_PROCEDURE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- END-DOCUMENT-PROCEDURE
   * @param endDocumentProcedure new value to conclude for END-DOCUMENT-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setEndDocumentProcedure(com.gensym.util.Symbol endDocumentProcedure) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.END_DOCUMENT_PROCEDURE_, endDocumentProcedure);
  }

  /**
   * Generated Property Getter for attribute -- END-DOCUMENT-PROCEDURE
   * @return the value of the END-DOCUMENT-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getEndDocumentProcedure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.END_DOCUMENT_PROCEDURE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- START-ELEMENT-PROCEDURE
   * @param startElementProcedure new value to conclude for START-ELEMENT-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setStartElementProcedure(com.gensym.util.Symbol startElementProcedure) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.START_ELEMENT_PROCEDURE_, startElementProcedure);
  }

  /**
   * Generated Property Getter for attribute -- START-ELEMENT-PROCEDURE
   * @return the value of the START-ELEMENT-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getStartElementProcedure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.START_ELEMENT_PROCEDURE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- END-ELEMENT-PROCEDURE
   * @param endElementProcedure new value to conclude for END-ELEMENT-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setEndElementProcedure(com.gensym.util.Symbol endElementProcedure) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.END_ELEMENT_PROCEDURE_, endElementProcedure);
  }

  /**
   * Generated Property Getter for attribute -- END-ELEMENT-PROCEDURE
   * @return the value of the END-ELEMENT-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getEndElementProcedure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.END_ELEMENT_PROCEDURE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CHARACTERS-PROCEDURE
   * @param charactersProcedure new value to conclude for CHARACTERS-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setCharactersProcedure(com.gensym.util.Symbol charactersProcedure) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.CHARACTERS_PROCEDURE_, charactersProcedure);
  }

  /**
   * Generated Property Getter for attribute -- CHARACTERS-PROCEDURE
   * @return the value of the CHARACTERS-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getCharactersProcedure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.CHARACTERS_PROCEDURE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- COMMENT-PROCEDURE
   * @param commentProcedure new value to conclude for COMMENT-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setCommentProcedure(com.gensym.util.Symbol commentProcedure) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.COMMENT_PROCEDURE_, commentProcedure);
  }

  /**
   * Generated Property Getter for attribute -- COMMENT-PROCEDURE
   * @return the value of the COMMENT-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getCommentProcedure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.COMMENT_PROCEDURE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- WARNING-PROCEDURE
   * @param warningProcedure new value to conclude for WARNING-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setWarningProcedure(com.gensym.util.Symbol warningProcedure) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.WARNING_PROCEDURE_, warningProcedure);
  }

  /**
   * Generated Property Getter for attribute -- WARNING-PROCEDURE
   * @return the value of the WARNING-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getWarningProcedure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.WARNING_PROCEDURE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ERROR-PROCEDURE
   * @param errorProcedure new value to conclude for ERROR-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setErrorProcedure(com.gensym.util.Symbol errorProcedure) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.ERROR_PROCEDURE_, errorProcedure);
  }

  /**
   * Generated Property Getter for attribute -- ERROR-PROCEDURE
   * @return the value of the ERROR-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getErrorProcedure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.ERROR_PROCEDURE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- FATAL-ERROR-PROCEDURE
   * @param fatalErrorProcedure new value to conclude for FATAL-ERROR-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setFatalErrorProcedure(com.gensym.util.Symbol fatalErrorProcedure) throws G2AccessException {
    setAttributeValue (SystemAttributeSymbols.FATAL_ERROR_PROCEDURE_, fatalErrorProcedure);
  }

  /**
   * Generated Property Getter for attribute -- FATAL-ERROR-PROCEDURE
   * @return the value of the FATAL-ERROR-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getFatalErrorProcedure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.FATAL_ERROR_PROCEDURE_);
    return (com.gensym.util.Symbol)retnValue;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
