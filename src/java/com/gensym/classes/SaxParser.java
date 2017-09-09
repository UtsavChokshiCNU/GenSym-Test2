/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      SaxParser.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JJ11)
 *
 *          Date: Thu Oct 11 15:37:18 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface SaxParser extends com.gensym.classes.Object {

  public static final Symbol SAX_PARSER_ = com.gensym.util.symbol.G2ClassSymbols.SAX_PARSER_;
  static final Symbol g2ClassName = SAX_PARSER_;
  static final Symbol[] classInheritancePath = new Symbol[] {SAX_PARSER_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for AUTHORS is : 
   * (OR NoItem
      (Structure 
        TIMESTAMP
          (Structure 
            YEAR Integer
            MONTH Integer
            DATE Integer
            HOURS Integer
            MINUTES Integer)
        AUTHORS
          (Sequence Symbol 0)))
   *
   */
  public com.gensym.util.Structure getAuthors() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAuthors(com.gensym.util.Structure authors) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CHANGE-LOG is : 
   * (OR (Sequence)
      NoItem)
   *
   */
  public com.gensym.util.Sequence getChangeLog() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-PENDING-CALLBACKS
   * @return the value of the NUMBER-OF-PENDING-CALLBACKS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NUMBER-OF-PENDING-CALLBACKS is : 
   * Integer
   *
   */
  public int getNumberOfPendingCallbacks() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- START-DOCUMENT-PROCEDURE
   * @return the value of the START-DOCUMENT-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for START-DOCUMENT-PROCEDURE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getStartDocumentProcedure() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- START-DOCUMENT-PROCEDURE
   * @param startDocumentProcedure new value to conclude for START-DOCUMENT-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStartDocumentProcedure(com.gensym.util.Symbol startDocumentProcedure) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- END-DOCUMENT-PROCEDURE
   * @return the value of the END-DOCUMENT-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for END-DOCUMENT-PROCEDURE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getEndDocumentProcedure() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- END-DOCUMENT-PROCEDURE
   * @param endDocumentProcedure new value to conclude for END-DOCUMENT-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEndDocumentProcedure(com.gensym.util.Symbol endDocumentProcedure) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- START-ELEMENT-PROCEDURE
   * @return the value of the START-ELEMENT-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for START-ELEMENT-PROCEDURE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getStartElementProcedure() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- START-ELEMENT-PROCEDURE
   * @param startElementProcedure new value to conclude for START-ELEMENT-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStartElementProcedure(com.gensym.util.Symbol startElementProcedure) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- END-ELEMENT-PROCEDURE
   * @return the value of the END-ELEMENT-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for END-ELEMENT-PROCEDURE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getEndElementProcedure() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- END-ELEMENT-PROCEDURE
   * @param endElementProcedure new value to conclude for END-ELEMENT-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEndElementProcedure(com.gensym.util.Symbol endElementProcedure) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CHARACTERS-PROCEDURE
   * @return the value of the CHARACTERS-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CHARACTERS-PROCEDURE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getCharactersProcedure() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CHARACTERS-PROCEDURE
   * @param charactersProcedure new value to conclude for CHARACTERS-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setCharactersProcedure(com.gensym.util.Symbol charactersProcedure) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- COMMENT-PROCEDURE
   * @return the value of the COMMENT-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for COMMENT-PROCEDURE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getCommentProcedure() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- COMMENT-PROCEDURE
   * @param commentProcedure new value to conclude for COMMENT-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setCommentProcedure(com.gensym.util.Symbol commentProcedure) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- WARNING-PROCEDURE
   * @return the value of the WARNING-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for WARNING-PROCEDURE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getWarningProcedure() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- WARNING-PROCEDURE
   * @param warningProcedure new value to conclude for WARNING-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setWarningProcedure(com.gensym.util.Symbol warningProcedure) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ERROR-PROCEDURE
   * @return the value of the ERROR-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ERROR-PROCEDURE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getErrorProcedure() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ERROR-PROCEDURE
   * @param errorProcedure new value to conclude for ERROR-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setErrorProcedure(com.gensym.util.Symbol errorProcedure) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FATAL-ERROR-PROCEDURE
   * @return the value of the FATAL-ERROR-PROCEDURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FATAL-ERROR-PROCEDURE is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getFatalErrorProcedure() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FATAL-ERROR-PROCEDURE
   * @param fatalErrorProcedure new value to conclude for FATAL-ERROR-PROCEDURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFatalErrorProcedure(com.gensym.util.Symbol fatalErrorProcedure) throws G2AccessException;

}
