/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdaAlarmQueue.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Jun 26 13:41:50 EDT 2000
 *
 */


package com.gensym.classes.modules.gda;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GdaAlarmQueue extends com.gensym.classes.modules.gqm.GqmQueue {

  public static final Symbol GDA_ALARM_QUEUE_ = Symbol.intern ("GDA-ALARM-QUEUE");
  static final Symbol g2ClassName = GDA_ALARM_QUEUE_;
  static final Symbol[] classInheritancePath = new Symbol[] {GDA_ALARM_QUEUE_, GQM_QUEUE_, GQS_QUEUE_, GFR_OBJECT_WITH_UUID_, OBJECT_, GFR_ITEM_WITH_UUID_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- GDA-AUTOGENERATE-EXPLANATION
   * @return the value of the GDA-AUTOGENERATE-EXPLANATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GDA-AUTOGENERATE-EXPLANATION is : 
   * BooleanTruthValue
   *
   */
  public boolean getGdaAutogenerateExplanation() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GDA-AUTOGENERATE-EXPLANATION
   * @param gdaAutogenerateExplanation new value to conclude for GDA-AUTOGENERATE-EXPLANATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdaAutogenerateExplanation(boolean gdaAutogenerateExplanation) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- GDA-RECURRING-ENTRY-CLASS
   * @return the value of the GDA-RECURRING-ENTRY-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GDA-RECURRING-ENTRY-CLASS is : 
   * Symbol
   *
   */
  public com.gensym.util.Symbol getGdaRecurringEntryClass() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GDA-RECURRING-ENTRY-CLASS
   * @param gdaRecurringEntryClass new value to conclude for GDA-RECURRING-ENTRY-CLASS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdaRecurringEntryClass(com.gensym.util.Symbol gdaRecurringEntryClass) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-QUEUE::GQS-REMOVE-ITEMS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-QUEUE,arg1:CLASS ITEM-LIST,arg2:CLASS OBJECT) = ()
   */
  public  void gqsRemoveItems(com.gensym.classes.ItemList arg1,com.gensym.classes.Object arg2) throws G2AccessException;
  
}
