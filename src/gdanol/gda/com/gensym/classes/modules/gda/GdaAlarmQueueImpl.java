/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdaAlarmQueueImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Jul 14 15:17:33 EDT 2000
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

public class GdaAlarmQueueImpl extends com.gensym.classes.modules.gqm.GqmQueueImpl implements GdaAlarmQueue {


  static final long serialVersionUID = 2L;
  private static final Symbol GDA_AUTOGENERATE_EXPLANATION_ = Symbol.intern ("GDA-AUTOGENERATE-EXPLANATION");
  private static final Symbol GDA_RECURRING_ENTRY_CLASS_ = Symbol.intern ("GDA-RECURRING-ENTRY-CLASS");

  /* Generated constructors */

  public GdaAlarmQueueImpl() {
    super();
  }

  public GdaAlarmQueueImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- GDA-AUTOGENERATE-EXPLANATION
   * @param gdaAutogenerateExplanation new value to conclude for GDA-AUTOGENERATE-EXPLANATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdaAutogenerateExplanation(boolean gdaAutogenerateExplanation) throws G2AccessException {
    setAttributeValue (GDA_AUTOGENERATE_EXPLANATION_, new Boolean (gdaAutogenerateExplanation));
  }

  /**
   * Generated Property Getter for attribute -- GDA-AUTOGENERATE-EXPLANATION
   * @return the value of the GDA-AUTOGENERATE-EXPLANATION attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getGdaAutogenerateExplanation() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GDA_AUTOGENERATE_EXPLANATION_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- GDA-RECURRING-ENTRY-CLASS
   * @param gdaRecurringEntryClass new value to conclude for GDA-RECURRING-ENTRY-CLASS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdaRecurringEntryClass(com.gensym.util.Symbol gdaRecurringEntryClass) throws G2AccessException {
    setAttributeValue (GDA_RECURRING_ENTRY_CLASS_, gdaRecurringEntryClass);
  }

  /**
   * Generated Property Getter for attribute -- GDA-RECURRING-ENTRY-CLASS
   * @return the value of the GDA-RECURRING-ENTRY-CLASS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getGdaRecurringEntryClass() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GDA_RECURRING_ENTRY_CLASS_);
    return (com.gensym.util.Symbol)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_GQS_REMOVE_ITEMS_ = Symbol.intern ("GQS-REMOVE-ITEMS");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * GDA-ALARM-QUEUE::GQS-REMOVE-ITEMS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDA-ALARM-QUEUE,arg1:CLASS ITEM-LIST,arg2:CLASS OBJECT) = ()
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
  
}
