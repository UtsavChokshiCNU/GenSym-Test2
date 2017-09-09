/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2_G2EventObject.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Thu Sep 27 12:31:42 EDT 2007
 *
 */


package com.gensym.classes.modules.g2evliss;

import com.gensym.classes.*;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

public class G2_G2EventObject extends com.gensym.classes.G2_ExternalEventObjectRoot {


  
  private static Sequence userAttributeList;
  

  static final long serialVersionUID = 2L;
  private static final Symbol SOURCE_ = Symbol.intern ("SOURCE");


  /* Generated constructor */

  public G2_G2EventObject(java.lang.Object source, Item g2EventObject) {
    super(source, g2EventObject);
  }

  
  /**
  * Return the attributes that this External event will "preload" from
  * G2 at creation.
  */
  public static synchronized Sequence getAttributeList() {

    if (userAttributeList == null) {
      userAttributeList = new Sequence(5);
      userAttributeList.addElement(SOURCE_);
    }
    return userAttributeList;
  }
  
}
