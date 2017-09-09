/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2_EventSourceEvent.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Sep 21 13:49:52 EDT 2007
 *
 */


package com.gensym.classes.modules.jgidemo;

import com.gensym.classes.*;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.jgi.*;

public class G2_EventSourceEvent extends com.gensym.classes.G2_ExternalEventObjectRoot {


  
  private static Sequence userAttributeList;
  

  static final long serialVersionUID = 2L;
  private static final Symbol MESSAGE_ = Symbol.intern ("MESSAGE");


  /* Generated constructor */

  public G2_EventSourceEvent(java.lang.Object source, Item g2EventObject) {
    super(source, g2EventObject);
  }

  /**
   * Generated Property Getter for attribute -- MESSAGE
   * @return the value of the MESSAGE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String getMessage() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (MESSAGE_);
    return (java.lang.String)retnValue;
  }

  
  /**
  * Return the attributes that this External event will "preload" from
  * G2 at creation.
  */
  public static synchronized Sequence getAttributeList() {

    if (userAttributeList == null) {
      userAttributeList = new Sequence(5);
      userAttributeList.addElement(SOURCE_);
      userAttributeList.addElement(MESSAGE_);
    }
    return userAttributeList;
  }
  
}
