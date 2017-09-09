/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GqsSubscriptionImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 13 11:46:01 EDT 2000
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

public class GqsSubscriptionImpl extends com.gensym.classes.modules.gfr.GfrObjectWithUuidImpl implements GqsSubscription {


  static final long serialVersionUID = 2L;
  private static final Symbol GQS_SEND_ALREADY_COLLECTED_ITEMS_ = Symbol.intern ("GQS-SEND-ALREADY-COLLECTED-ITEMS");
  private static final Symbol _GQS_FILTER_ID_ = Symbol.intern ("_GQS-FILTER-ID");
  private static final Symbol _GQS_SUBSCRIBER_ID_ = Symbol.intern ("_GQS-SUBSCRIBER-ID");
  private static final Symbol _GQS_PROVIDER_ID_ = Symbol.intern ("_GQS-PROVIDER-ID");

  /* Generated constructors */

  public GqsSubscriptionImpl() {
    super();
  }

  public GqsSubscriptionImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- GQS-SEND-ALREADY-COLLECTED-ITEMS
   * @param gqsSendAlreadyCollectedItems new value to conclude for GQS-SEND-ALREADY-COLLECTED-ITEMS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGqsSendAlreadyCollectedItems(boolean gqsSendAlreadyCollectedItems) throws G2AccessException {
    setAttributeValue (GQS_SEND_ALREADY_COLLECTED_ITEMS_, new Boolean (gqsSendAlreadyCollectedItems));
  }

  /**
   * Generated Property Getter for attribute -- GQS-SEND-ALREADY-COLLECTED-ITEMS
   * @return the value of the GQS-SEND-ALREADY-COLLECTED-ITEMS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getGqsSendAlreadyCollectedItems() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GQS_SEND_ALREADY_COLLECTED_ITEMS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- _GQS-FILTER-ID
   * @param _gqsFilterId new value to conclude for _GQS-FILTER-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gqsFilterId(java.lang.String _gqsFilterId) throws G2AccessException {
    setAttributeValue (_GQS_FILTER_ID_, _gqsFilterId);
  }

  /**
   * Generated Property Getter for attribute -- _GQS-FILTER-ID
   * @return the value of the _GQS-FILTER-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String get_gqsFilterId() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_GQS_FILTER_ID_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- _GQS-SUBSCRIBER-ID
   * @param _gqsSubscriberId new value to conclude for _GQS-SUBSCRIBER-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gqsSubscriberId(java.lang.String _gqsSubscriberId) throws G2AccessException {
    setAttributeValue (_GQS_SUBSCRIBER_ID_, _gqsSubscriberId);
  }

  /**
   * Generated Property Getter for attribute -- _GQS-SUBSCRIBER-ID
   * @return the value of the _GQS-SUBSCRIBER-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String get_gqsSubscriberId() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_GQS_SUBSCRIBER_ID_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- _GQS-PROVIDER-ID
   * @param _gqsProviderId new value to conclude for _GQS-PROVIDER-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_gqsProviderId(java.lang.String _gqsProviderId) throws G2AccessException {
    setAttributeValue (_GQS_PROVIDER_ID_, _gqsProviderId);
  }

  /**
   * Generated Property Getter for attribute -- _GQS-PROVIDER-ID
   * @return the value of the _GQS-PROVIDER-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String get_gqsProviderId() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_GQS_PROVIDER_ID_);
    return (java.lang.String)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_GQS_SUBSCRIBE_ = Symbol.intern ("GQS-SUBSCRIBE");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * GQS-SUBSCRIPTION::GQS-SUBSCRIBE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GQS-SUBSCRIPTION,arg1:CLASS GQS-QUEUE,arg2:CLASS GQS-QUEUE,arg3:CLASS OBJECT) = ()
   */
  public  void gqsSubscribe(com.gensym.classes.modules.gqs.GqsQueue arg1,com.gensym.classes.modules.gqs.GqsQueue arg2,com.gensym.classes.Object arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
      result = (java.lang.Object)callRPC(MethodName_GQS_SUBSCRIBE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
