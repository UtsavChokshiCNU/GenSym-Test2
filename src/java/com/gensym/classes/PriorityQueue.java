/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      PriorityQueue.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 8.4 Rev 0 (JI21)
 *
 *          Date: Fri Sep 21 13:04:56 EDT 2007
 *
 */


package com.gensym.classes;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;

public interface PriorityQueue extends com.gensym.classes.Object {

  public static final Symbol PRIORITY_QUEUE_ = com.gensym.util.symbol.G2ClassSymbols.PRIORITY_QUEUE_;
  static final Symbol g2ClassName = PRIORITY_QUEUE_;
  static final Symbol[] classInheritancePath = new Symbol[] {PRIORITY_QUEUE_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- G2-PRIORITY-QUEUE-SEQUENCE
   * @return the value of the G2-PRIORITY-QUEUE-SEQUENCE attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-PRIORITY-QUEUE-SEQUENCE is : 
   * (OR NoItem
      (Sequence))
   *
   */
  public com.gensym.util.Sequence getG2PriorityQueueSequence() throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- G2-PRIORITY-QUEUE-NUMBER-OF-ENTRIES
   * @return the value of the G2-PRIORITY-QUEUE-NUMBER-OF-ENTRIES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for G2-PRIORITY-QUEUE-NUMBER-OF-ENTRIES is : 
   * Integer
   *
   */
  public int getG2PriorityQueueNumberOfEntries() throws G2AccessException;

}
