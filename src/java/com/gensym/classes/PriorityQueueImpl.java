/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      PriorityQueueImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:04:57 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public class PriorityQueueImpl extends com.gensym.classes.ObjectImpl implements PriorityQueue {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public PriorityQueueImpl() {
    super();
  }

  public PriorityQueueImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public PriorityQueueImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Getter for attribute -- G2-PRIORITY-QUEUE-SEQUENCE
   * @return the value of the G2-PRIORITY-QUEUE-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getG2PriorityQueueSequence() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_PRIORITY_QUEUE_SEQUENCE_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- G2-PRIORITY-QUEUE-NUMBER-OF-ENTRIES
   * @return the value of the G2-PRIORITY-QUEUE-NUMBER-OF-ENTRIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getG2PriorityQueueNumberOfEntries() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SystemAttributeSymbols.G2_PRIORITY_QUEUE_NUMBER_OF_ENTRIES_);
    return ((Integer)retnValue).intValue ();
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
