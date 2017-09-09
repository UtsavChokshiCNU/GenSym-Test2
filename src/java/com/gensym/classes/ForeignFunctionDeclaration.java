/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      ForeignFunctionDeclaration.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 12:42:04 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface ForeignFunctionDeclaration extends com.gensym.classes.Statement {

  public static final Symbol FOREIGN_FUNCTION_DECLARATION_ = com.gensym.util.symbol.G2ClassSymbols.FOREIGN_FUNCTION_DECLARATION_;
  static final Symbol g2ClassName = FOREIGN_FUNCTION_DECLARATION_;
  static final Symbol[] classInheritancePath = new Symbol[] {FOREIGN_FUNCTION_DECLARATION_, STATEMENT_, ITEM_, STATEMENT_OR_PROCEDURE_STEP_, TEXT_BOX_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


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
   * Generated Property Getter for attribute -- NAME-IN-FOREIGN-IMAGE
   * @return the value of the NAME-IN-FOREIGN-IMAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for NAME-IN-FOREIGN-IMAGE is : 
   * (OR NoItem
      Text)
   *
   */
  public java.lang.String getNameInForeignImage() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- NAME-IN-FOREIGN-IMAGE
   * @param nameInForeignImage new value to conclude for NAME-IN-FOREIGN-IMAGE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setNameInForeignImage(java.lang.String nameInForeignImage) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TIMEOUT-INTERVAL
   * @return the value of the TIMEOUT-INTERVAL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TIMEOUT-INTERVAL is : 
   * (OR (MEMBER USE-DEFAULT)
      Integer)
   *
   */
  public java.lang.Object getTimeoutInterval() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TIMEOUT-INTERVAL
   * @param timeoutInterval new value to conclude for TIMEOUT-INTERVAL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTimeoutInterval(java.lang.Object timeoutInterval) throws G2AccessException;

}
