/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GqsSubscription.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Jun 26 18:45:02 EDT 2000
 *
 */


package com.gensym.classes.modules.gqs;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GqsSubscription extends com.gensym.classes.modules.gfr.GfrObjectWithUuid {

  public static final Symbol GQS_SUBSCRIPTION_ = Symbol.intern ("GQS-SUBSCRIPTION");
  static final Symbol g2ClassName = GQS_SUBSCRIPTION_;
  static final Symbol[] classInheritancePath = new Symbol[] {GQS_SUBSCRIPTION_, GFR_OBJECT_WITH_UUID_, OBJECT_, GFR_ITEM_WITH_UUID_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- GQS-SEND-ALREADY-COLLECTED-ITEMS
   * @return the value of the GQS-SEND-ALREADY-COLLECTED-ITEMS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for GQS-SEND-ALREADY-COLLECTED-ITEMS is : 
   * BooleanTruthValue
   *
   */
  public boolean getGqsSendAlreadyCollectedItems() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- GQS-SEND-ALREADY-COLLECTED-ITEMS
   * @param gqsSendAlreadyCollectedItems new value to conclude for GQS-SEND-ALREADY-COLLECTED-ITEMS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqsSendAlreadyCollectedItems(boolean gqsSendAlreadyCollectedItems) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _GQS-FILTER-ID
   * @return the value of the _GQS-FILTER-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _GQS-FILTER-ID is : 
   * Text
   *
   */
  public java.lang.String get_gqsFilterId() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _GQS-FILTER-ID
   * @param _gqsFilterId new value to conclude for _GQS-FILTER-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gqsFilterId(java.lang.String _gqsFilterId) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _GQS-SUBSCRIBER-ID
   * @return the value of the _GQS-SUBSCRIBER-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _GQS-SUBSCRIBER-ID is : 
   * Text
   *
   */
  public java.lang.String get_gqsSubscriberId() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _GQS-SUBSCRIBER-ID
   * @param _gqsSubscriberId new value to conclude for _GQS-SUBSCRIBER-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gqsSubscriberId(java.lang.String _gqsSubscriberId) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _GQS-PROVIDER-ID
   * @return the value of the _GQS-PROVIDER-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _GQS-PROVIDER-ID is : 
   * Text
   *
   */
  public java.lang.String get_gqsProviderId() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _GQS-PROVIDER-ID
   * @param _gqsProviderId new value to conclude for _GQS-PROVIDER-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gqsProviderId(java.lang.String _gqsProviderId) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * GQS-SUBSCRIPTION::GQS-SUBSCRIBE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQS-SUBSCRIPTION,arg1:CLASS GQS-QUEUE,arg2:CLASS GQS-QUEUE,arg3:CLASS OBJECT) = ()
   */
  public  void gqsSubscribe(com.gensym.classes.modules.gqs.GqsQueue arg1,com.gensym.classes.modules.gqs.GqsQueue arg2,com.gensym.classes.Object arg3) throws G2AccessException;
  
}
