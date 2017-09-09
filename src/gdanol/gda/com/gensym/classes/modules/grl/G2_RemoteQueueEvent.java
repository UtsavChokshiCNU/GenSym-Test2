/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2_RemoteQueueEvent.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Jun 26 18:44:54 EDT 2000
 *
 */


package com.gensym.classes.modules.grl;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class G2_RemoteQueueEvent extends com.gensym.classes.G2_ExternalEventObjectRoot {


  
  private static Sequence userAttributeList;
  

  static final long serialVersionUID = 2L;
  private static final Symbol REMOTE_QUEUE_EVENT_DATA_ = Symbol.intern ("REMOTE-QUEUE-EVENT-DATA");


  /* Generated constructor */

  public G2_RemoteQueueEvent(java.lang.Object source, Item g2EventObject) {
    super(source, g2EventObject);
  };

  /**
   * Generated Property Getter for attribute -- REMOTE-QUEUE-EVENT-DATA
   * @return the value of the REMOTE-QUEUE-EVENT-DATA attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Structure getRemoteQueueEventData() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (REMOTE_QUEUE_EVENT_DATA_);
    return (com.gensym.util.Structure)retnValue;
  }

  
  /**
  * Return the attributes that this External event will "preload" from
  * G2 at creation.
  */
  public static Sequence getAttributeList() {

    if (userAttributeList == null) {
      userAttributeList = new Sequence(5);
      userAttributeList.addElement(SOURCE_);
      userAttributeList.addElement(REMOTE_QUEUE_EVENT_DATA_);
    }
    return userAttributeList;
  }
  
}
