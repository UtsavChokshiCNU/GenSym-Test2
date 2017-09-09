/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      Relation.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:07:23 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface Relation extends com.gensym.classes.Item, com.gensym.classes.Entity {

  public static final Symbol RELATION_ = com.gensym.util.symbol.G2ClassSymbols.RELATION_;
  static final Symbol g2ClassName = RELATION_;
  static final Symbol[] classInheritancePath = new Symbol[] {RELATION_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


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
   * Generated Property Getter for attribute -- FIRST-CLASS
   * @return the value of the FIRST-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FIRST-CLASS is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getFirstClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FIRST-CLASS
   * @param firstClass new value to conclude for FIRST-CLASS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFirstClass(com.gensym.util.Symbol firstClass) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- SECOND-CLASS
   * @return the value of the SECOND-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for SECOND-CLASS is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getSecondClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- SECOND-CLASS
   * @param secondClass new value to conclude for SECOND-CLASS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSecondClass(com.gensym.util.Symbol secondClass) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- RELATION-NAME
   * @return the value of the RELATION-NAME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for RELATION-NAME is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getRelationName() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- RELATION-NAME
   * @param relationName new value to conclude for RELATION-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRelationName(com.gensym.util.Symbol relationName) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- INVERSE-OF-RELATION
   * @return the value of the INVERSE-OF-RELATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for INVERSE-OF-RELATION is : 
   * (OR NoItem
      Symbol)
   *
   */
  public com.gensym.util.Symbol getInverseOfRelation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- INVERSE-OF-RELATION
   * @param inverseOfRelation new value to conclude for INVERSE-OF-RELATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInverseOfRelation(com.gensym.util.Symbol inverseOfRelation) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- TYPE-OF-RELATION
   * @return the value of the TYPE-OF-RELATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for TYPE-OF-RELATION is : 
   * (MEMBER ONE-TO-ONE ONE-TO-MANY MANY-TO-ONE MANY-TO-MANY)
   *
   */
  public com.gensym.util.Symbol getTypeOfRelation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- TYPE-OF-RELATION
   * @param typeOfRelation new value to conclude for TYPE-OF-RELATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setTypeOfRelation(com.gensym.util.Symbol typeOfRelation) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- RELATION-IS-SYMMETRIC
   * @return the value of the RELATION-IS-SYMMETRIC attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for RELATION-IS-SYMMETRIC is : 
   * BooleanTruthValue
   *
   */
  public boolean getRelationIsSymmetric() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- RELATION-IS-SYMMETRIC
   * @param relationIsSymmetric new value to conclude for RELATION-IS-SYMMETRIC
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRelationIsSymmetric(boolean relationIsSymmetric) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- RELATION-IS-PERMANENT
   * @return the value of the RELATION-IS-PERMANENT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for RELATION-IS-PERMANENT is : 
   * BooleanTruthValue
   *
   */
  public boolean getRelationIsPermanent() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- RELATION-IS-PERMANENT
   * @param relationIsPermanent new value to conclude for RELATION-IS-PERMANENT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setRelationIsPermanent(boolean relationIsPermanent) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ITEMS-IN-THIS-RELATION
   * @return the value of the ITEMS-IN-THIS-RELATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ITEMS-IN-THIS-RELATION is : 
   * (OR NoItem
      (Sequence (Class ITEM) 1))
   *
   */
  public com.gensym.util.Sequence getItemsInThisRelation() throws G2AccessException;

}
