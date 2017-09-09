/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GqmQueue.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 13 11:45:45 EDT 2000
 *
 */


package com.gensym.classes.modules.gqm;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GqmQueue extends com.gensym.classes.modules.gqs.GqsQueue {

  public static final Symbol GQM_QUEUE_ = Symbol.intern ("GQM-QUEUE");
  static final Symbol g2ClassName = GQM_QUEUE_;
  static final Symbol[] classInheritancePath = new Symbol[] {GQM_QUEUE_, GQS_QUEUE_, GFR_OBJECT_WITH_UUID_, OBJECT_, GFR_ITEM_WITH_UUID_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- GQM-ENTRY-CLASS
   * @return the value of the GQM-ENTRY-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GQM-ENTRY-CLASS is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getGqmEntryClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GQM-ENTRY-CLASS
   * @param gqmEntryClass new value to conclude for GQM-ENTRY-CLASS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmEntryClass(com.gensym.util.Symbol gqmEntryClass) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GQM-DEFAULT-PRIORITY
   * @return the value of the GQM-DEFAULT-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GQM-DEFAULT-PRIORITY is : 
   * Integer
   *
   */
  public int getGqmDefaultPriority() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GQM-DEFAULT-PRIORITY
   * @param gqmDefaultPriority new value to conclude for GQM-DEFAULT-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmDefaultPriority(int gqmDefaultPriority) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GQM-ENTRY-LIMIT
   * @return the value of the GQM-ENTRY-LIMIT attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GQM-ENTRY-LIMIT is : 
   * Integer
   *
   */
  public int getGqmEntryLimit() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GQM-ENTRY-LIMIT
   * @param gqmEntryLimit new value to conclude for GQM-ENTRY-LIMIT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmEntryLimit(int gqmEntryLimit) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GQM-ENTRY-LIMIT-TRIM-CRITERION
   * @return the value of the GQM-ENTRY-LIMIT-TRIM-CRITERION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GQM-ENTRY-LIMIT-TRIM-CRITERION is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getGqmEntryLimitTrimCriterion() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GQM-ENTRY-LIMIT-TRIM-CRITERION
   * @param gqmEntryLimitTrimCriterion new value to conclude for GQM-ENTRY-LIMIT-TRIM-CRITERION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmEntryLimitTrimCriterion(com.gensym.util.Symbol gqmEntryLimitTrimCriterion) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GQM-DISPLAY-MESSAGES
   * @return the value of the GQM-DISPLAY-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GQM-DISPLAY-MESSAGES is : 
   * BooleanTruthValue
   *
   */
  public boolean getGqmDisplayMessages() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GQM-DISPLAY-MESSAGES
   * @param gqmDisplayMessages new value to conclude for GQM-DISPLAY-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmDisplayMessages(boolean gqmDisplayMessages) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GQM-BEEP-FOR-NEW-ENTRY
   * @return the value of the GQM-BEEP-FOR-NEW-ENTRY attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GQM-BEEP-FOR-NEW-ENTRY is : 
   * BooleanTruthValue
   *
   */
  public boolean getGqmBeepForNewEntry() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GQM-BEEP-FOR-NEW-ENTRY
   * @param gqmBeepForNewEntry new value to conclude for GQM-BEEP-FOR-NEW-ENTRY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmBeepForNewEntry(boolean gqmBeepForNewEntry) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GQM-CONFIRM-DELETIONS
   * @return the value of the GQM-CONFIRM-DELETIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GQM-CONFIRM-DELETIONS is : 
   * BooleanTruthValue
   *
   */
  public boolean getGqmConfirmDeletions() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GQM-CONFIRM-DELETIONS
   * @param gqmConfirmDeletions new value to conclude for GQM-CONFIRM-DELETIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmConfirmDeletions(boolean gqmConfirmDeletions) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GQM-ENTRY-LIFETIME
   * @return the value of the GQM-ENTRY-LIFETIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GQM-ENTRY-LIFETIME is : 
   * Float
   *
   */
  public double getGqmEntryLifetime() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GQM-ENTRY-LIFETIME
   * @param gqmEntryLifetime new value to conclude for GQM-ENTRY-LIFETIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmEntryLifetime(double gqmEntryLifetime) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * GQM-QUEUE::GQM-POST-ENTRY
   * @return the return from calling GQM-POST-ENTRY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-QUEUE,arg1:STRUCTURE,arg2:CLASS OBJECT) = (CLASS GQM-ENTRY)
   */
  public  com.gensym.classes.modules.gqm.GqmEntry gqmPostEntry(com.gensym.util.Structure arg1,com.gensym.classes.Object arg2) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GQM-QUEUE::GQS-SEND-ITEMS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-QUEUE,arg1:CLASS GQS-QUEUE,arg2:CLASS ITEM-LIST,arg3:CLASS OBJECT) = ()
   */
  public  void gqsSendItems(com.gensym.classes.modules.gqs.GqsQueue arg1,com.gensym.classes.ItemList arg2,com.gensym.classes.Object arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GQM-QUEUE::GQS-REMOVE-ITEMS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-QUEUE,arg1:CLASS ITEM-LIST,arg2:CLASS OBJECT) = ()
   */
  public  void gqsRemoveItems(com.gensym.classes.ItemList arg1,com.gensym.classes.Object arg2) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GQM-QUEUE::GQS-RECEIVE-ITEMS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-QUEUE,arg1:ITEM-OR-VALUE,arg2:CLASS ITEM-LIST,arg3:CLASS OBJECT) = ()
   */
  public  void gqsReceiveItems(java.lang.Object arg1,com.gensym.classes.ItemList arg2,com.gensym.classes.Object arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GQM-QUEUE::GQS-RECEIVE-SINGLE-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-QUEUE,arg1:CLASS ITEM,arg2:CLASS OBJECT) = ()
   */
  public  void gqsReceiveSingleItem(com.gensym.classes.Item arg1,com.gensym.classes.Object arg2) throws G2AccessException;
  
}
