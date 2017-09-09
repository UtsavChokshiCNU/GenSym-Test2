/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      UserMenuChoice.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:14:03 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.util.Symbol;
import com.gensym.jgi.*;

public interface UserMenuChoice extends com.gensym.classes.Item, com.gensym.classes.Entity {

  public static final Symbol USER_MENU_CHOICE_ = com.gensym.util.symbol.G2ClassSymbols.USER_MENU_CHOICE_;
  static final Symbol g2ClassName = USER_MENU_CHOICE_;
  static final Symbol[] classInheritancePath = new Symbol[] {USER_MENU_CHOICE_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


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
   * Generated Property Getter for attribute -- LABEL
   * @return the value of the LABEL attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for LABEL is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getLabel() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- LABEL
   * @param label new value to conclude for LABEL
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setLabel(com.gensym.util.Symbol label) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- APPLICABLE-CLASS
   * @return the value of the APPLICABLE-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for APPLICABLE-CLASS is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getApplicableClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- APPLICABLE-CLASS
   * @param applicableClass new value to conclude for APPLICABLE-CLASS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setApplicableClass(com.gensym.util.Symbol applicableClass) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- CONDITION
   * @return the value of the CONDITION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for CONDITION is : 
   * (OR Text
      NoItem)
   *
   */
  public java.lang.String getCondition() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- CONDITION
   * @param condition new value to conclude for CONDITION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setCondition(java.lang.String condition) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ACTION
   * @return the value of the ACTION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ACTION is : 
   * Text
   *
   */
  public java.lang.String getAction() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ACTION
   * @param action new value to conclude for ACTION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAction(java.lang.String action) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ACTION-PRIORITY
   * @return the value of the ACTION-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ACTION-PRIORITY is : 
   * (MEMBER 1 2 3 4 5 6 7 8 9 10)
   *
   */
  public com.gensym.util.Symbol getActionPriority() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ACTION-PRIORITY
   * @param actionPriority new value to conclude for ACTION-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setActionPriority(com.gensym.util.Symbol actionPriority) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- EVALUATION-ATTRIBUTES
   * @return the value of the EVALUATION-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for EVALUATION-ATTRIBUTES is : 
   * (OR NoItem
      (Structure 
        MAY-REFER-TO-INACTIVE-ITEMS BooleanTruthValue
        MAY-RUN-WHILE-INACTIVE BooleanTruthValue))
   *
   */
  public com.gensym.util.Structure getEvaluationAttributes() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- EVALUATION-ATTRIBUTES
   * @param evaluationAttributes new value to conclude for EVALUATION-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setEvaluationAttributes(com.gensym.util.Structure evaluationAttributes) throws G2AccessException;

  /* Overriden method - INVOKE */
  /**
   * @param item the Item on which to invoke this UserMenuChoice
   * @return true if successful
   * @exception G2AccessException if there are any communication problems
   *   or exceptions within the remote method call
   */
  public boolean invoke(Item item)
       throws G2AccessException;

}
