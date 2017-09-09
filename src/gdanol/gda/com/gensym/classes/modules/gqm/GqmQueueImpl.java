/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GqmQueueImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 13 11:46:12 EDT 2000
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

public class GqmQueueImpl extends com.gensym.classes.modules.gqs.GqsQueueImpl implements GqmQueue {


  static final long serialVersionUID = 2L;
  private static final Symbol GQM_ENTRY_CLASS_ = Symbol.intern ("GQM-ENTRY-CLASS");
  private static final Symbol GQM_DEFAULT_PRIORITY_ = Symbol.intern ("GQM-DEFAULT-PRIORITY");
  private static final Symbol GQM_ENTRY_LIMIT_ = Symbol.intern ("GQM-ENTRY-LIMIT");
  private static final Symbol GQM_ENTRY_LIMIT_TRIM_CRITERION_ = Symbol.intern ("GQM-ENTRY-LIMIT-TRIM-CRITERION");
  private static final Symbol GQM_DISPLAY_MESSAGES_ = Symbol.intern ("GQM-DISPLAY-MESSAGES");
  private static final Symbol GQM_BEEP_FOR_NEW_ENTRY_ = Symbol.intern ("GQM-BEEP-FOR-NEW-ENTRY");
  private static final Symbol GQM_CONFIRM_DELETIONS_ = Symbol.intern ("GQM-CONFIRM-DELETIONS");
  private static final Symbol GQM_ENTRY_LIFETIME_ = Symbol.intern ("GQM-ENTRY-LIFETIME");

  /* Generated constructors */

  public GqmQueueImpl() {
    super();
  }

  public GqmQueueImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- GQM-ENTRY-CLASS
   * @param gqmEntryClass new value to conclude for GQM-ENTRY-CLASS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmEntryClass(com.gensym.util.Symbol gqmEntryClass) throws G2AccessException {
    setAttributeValue (GQM_ENTRY_CLASS_, gqmEntryClass);
  }

  /**
   * Generated Property Getter for attribute -- GQM-ENTRY-CLASS
   * @return the value of the GQM-ENTRY-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getGqmEntryClass() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQM_ENTRY_CLASS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GQM-DEFAULT-PRIORITY
   * @param gqmDefaultPriority new value to conclude for GQM-DEFAULT-PRIORITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmDefaultPriority(int gqmDefaultPriority) throws G2AccessException {
    setAttributeValue (GQM_DEFAULT_PRIORITY_, new Integer (gqmDefaultPriority));
  }

  /**
   * Generated Property Getter for attribute -- GQM-DEFAULT-PRIORITY
   * @return the value of the GQM-DEFAULT-PRIORITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getGqmDefaultPriority() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQM_DEFAULT_PRIORITY_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- GQM-ENTRY-LIMIT
   * @param gqmEntryLimit new value to conclude for GQM-ENTRY-LIMIT
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmEntryLimit(int gqmEntryLimit) throws G2AccessException {
    setAttributeValue (GQM_ENTRY_LIMIT_, new Integer (gqmEntryLimit));
  }

  /**
   * Generated Property Getter for attribute -- GQM-ENTRY-LIMIT
   * @return the value of the GQM-ENTRY-LIMIT attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getGqmEntryLimit() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQM_ENTRY_LIMIT_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- GQM-ENTRY-LIMIT-TRIM-CRITERION
   * @param gqmEntryLimitTrimCriterion new value to conclude for GQM-ENTRY-LIMIT-TRIM-CRITERION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmEntryLimitTrimCriterion(com.gensym.util.Symbol gqmEntryLimitTrimCriterion) throws G2AccessException {
    setAttributeValue (GQM_ENTRY_LIMIT_TRIM_CRITERION_, gqmEntryLimitTrimCriterion);
  }

  /**
   * Generated Property Getter for attribute -- GQM-ENTRY-LIMIT-TRIM-CRITERION
   * @return the value of the GQM-ENTRY-LIMIT-TRIM-CRITERION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getGqmEntryLimitTrimCriterion() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQM_ENTRY_LIMIT_TRIM_CRITERION_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- GQM-DISPLAY-MESSAGES
   * @param gqmDisplayMessages new value to conclude for GQM-DISPLAY-MESSAGES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmDisplayMessages(boolean gqmDisplayMessages) throws G2AccessException {
    setAttributeValue (GQM_DISPLAY_MESSAGES_, new Boolean (gqmDisplayMessages));
  }

  /**
   * Generated Property Getter for attribute -- GQM-DISPLAY-MESSAGES
   * @return the value of the GQM-DISPLAY-MESSAGES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getGqmDisplayMessages() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQM_DISPLAY_MESSAGES_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- GQM-BEEP-FOR-NEW-ENTRY
   * @param gqmBeepForNewEntry new value to conclude for GQM-BEEP-FOR-NEW-ENTRY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmBeepForNewEntry(boolean gqmBeepForNewEntry) throws G2AccessException {
    setAttributeValue (GQM_BEEP_FOR_NEW_ENTRY_, new Boolean (gqmBeepForNewEntry));
  }

  /**
   * Generated Property Getter for attribute -- GQM-BEEP-FOR-NEW-ENTRY
   * @return the value of the GQM-BEEP-FOR-NEW-ENTRY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getGqmBeepForNewEntry() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQM_BEEP_FOR_NEW_ENTRY_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- GQM-CONFIRM-DELETIONS
   * @param gqmConfirmDeletions new value to conclude for GQM-CONFIRM-DELETIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmConfirmDeletions(boolean gqmConfirmDeletions) throws G2AccessException {
    setAttributeValue (GQM_CONFIRM_DELETIONS_, new Boolean (gqmConfirmDeletions));
  }

  /**
   * Generated Property Getter for attribute -- GQM-CONFIRM-DELETIONS
   * @return the value of the GQM-CONFIRM-DELETIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getGqmConfirmDeletions() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQM_CONFIRM_DELETIONS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- GQM-ENTRY-LIFETIME
   * @param gqmEntryLifetime new value to conclude for GQM-ENTRY-LIFETIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqmEntryLifetime(double gqmEntryLifetime) throws G2AccessException {
    setAttributeValue (GQM_ENTRY_LIFETIME_, new Double (gqmEntryLifetime));
  }

  /**
   * Generated Property Getter for attribute -- GQM-ENTRY-LIFETIME
   * @return the value of the GQM-ENTRY-LIFETIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public double getGqmEntryLifetime() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQM_ENTRY_LIFETIME_);
    return ((Double)retnValue).doubleValue ();
  }

  // Method Name Constants
  private static final Symbol MethodName_GQM_POST_ENTRY_ = Symbol.intern ("GQM-POST-ENTRY");
  private static final Symbol MethodName_GQS_SEND_ITEMS_ = Symbol.intern ("GQS-SEND-ITEMS");
  private static final Symbol MethodName_GQS_REMOVE_ITEMS_ = Symbol.intern ("GQS-REMOVE-ITEMS");
  private static final Symbol MethodName_GQS_RECEIVE_ITEMS_ = Symbol.intern ("GQS-RECEIVE-ITEMS");
  private static final Symbol MethodName_GQS_RECEIVE_SINGLE_ITEM_ = Symbol.intern ("GQS-RECEIVE-SINGLE-ITEM");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * GQM-QUEUE::GQM-POST-ENTRY
   * @return the return from calling GQM-POST-ENTRY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-QUEUE,arg1:STRUCTURE,arg2:CLASS OBJECT) = (CLASS GQM-ENTRY)
   */
  public  com.gensym.classes.modules.gqm.GqmEntry gqmPostEntry(com.gensym.util.Structure arg1,com.gensym.classes.Object arg2) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
      result = (java.lang.Object)callRPC(MethodName_GQM_POST_ENTRY_, args);
      return (com.gensym.classes.modules.gqm.GqmEntry)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GQM-QUEUE::GQS-SEND-ITEMS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-QUEUE,arg1:CLASS GQS-QUEUE,arg2:CLASS ITEM-LIST,arg3:CLASS OBJECT) = ()
   */
  public  void gqsSendItems(com.gensym.classes.modules.gqs.GqsQueue arg1,com.gensym.classes.ItemList arg2,com.gensym.classes.Object arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
      result = (java.lang.Object)callRPC(MethodName_GQS_SEND_ITEMS_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GQM-QUEUE::GQS-REMOVE-ITEMS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-QUEUE,arg1:CLASS ITEM-LIST,arg2:CLASS OBJECT) = ()
   */
  public  void gqsRemoveItems(com.gensym.classes.ItemList arg1,com.gensym.classes.Object arg2) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
      result = (java.lang.Object)callRPC(MethodName_GQS_REMOVE_ITEMS_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GQM-QUEUE::GQS-RECEIVE-ITEMS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-QUEUE,arg1:ITEM-OR-VALUE,arg2:CLASS ITEM-LIST,arg3:CLASS OBJECT) = ()
   */
  public  void gqsReceiveItems(java.lang.Object arg1,com.gensym.classes.ItemList arg2,com.gensym.classes.Object arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
      result = (java.lang.Object)callRPC(MethodName_GQS_RECEIVE_ITEMS_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GQM-QUEUE::GQS-RECEIVE-SINGLE-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQM-QUEUE,arg1:CLASS ITEM,arg2:CLASS OBJECT) = ()
   */
  public  void gqsReceiveSingleItem(com.gensym.classes.Item arg1,com.gensym.classes.Object arg2) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
      result = (java.lang.Object)callRPC(MethodName_GQS_RECEIVE_SINGLE_ITEM_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
