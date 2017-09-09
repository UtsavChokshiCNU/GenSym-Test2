/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2_GdlPathItemEvent.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon May 15 14:06:27 GMT+04:00 2000
 *
 */


package com.gensym.classes.modules.gdluisup;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class G2_GdlPathItemEvent extends com.gensym.classes.G2_ExternalEventObjectRoot {


  
  private static Sequence userAttributeList;
  

  static final long serialVersionUID = 2L;
  private static final Symbol GDL_PATH_DATA_VALUES_ = Symbol.intern ("GDL-PATH-DATA-VALUES");


  /* Generated constructor */

  public G2_GdlPathItemEvent(java.lang.Object source, Item g2EventObject) {
    super(source, g2EventObject);
  };

  /**
   * Generated Property Getter for attribute -- GDL-PATH-DATA-VALUES
   * @return the value of the GDL-PATH-DATA-VALUES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getGdlPathDataValues() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (GDL_PATH_DATA_VALUES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  
  /**
  * Return the attributes that this External event will "preload" from
  * G2 at creation.
  */
  public static Sequence getAttributeList() {

    if (userAttributeList == null) {
      userAttributeList = new Sequence(5);
      userAttributeList.addElement(SOURCE_);
      userAttributeList.addElement(GDL_PATH_DATA_VALUES_);
    }
    return userAttributeList;
  }
  
}
