/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlPathItemEventImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon May 15 13:58:18 GMT+04:00 2000
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

public class GdlPathItemEventImpl extends com.gensym.classes.modules.g2evliss.G2EventObjectImpl implements GdlPathItemEvent {


  static final long serialVersionUID = 2L;
  private static final Symbol GDL_PATH_DATA_VALUES_ = Symbol.intern ("GDL-PATH-DATA-VALUES");

  /* Generated constructors */

  public GdlPathItemEventImpl() {
    super();
  }

  public GdlPathItemEventImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- GDL-PATH-DATA-VALUES
   * @param gdlPathDataValues new value to conclude for GDL-PATH-DATA-VALUES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setGdlPathDataValues(com.gensym.util.Sequence gdlPathDataValues) throws G2AccessException {
    setAttributeValue (GDL_PATH_DATA_VALUES_, gdlPathDataValues);
  }

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
   * Generated Property Setter for attribute -- ATTRIBUTE-DISPLAYS
   * @param attributeDisplays new value to conclude for ATTRIBUTE-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAttributeDisplaysForClass(java.lang.Object attributeDisplays) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_DISPLAYS_, attributeDisplays);
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-DISPLAYS
   * @return the value of the ATTRIBUTE-DISPLAYS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getAttributeDisplaysForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_DISPLAYS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- STUBS
   * @param stubs new value to conclude for STUBS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setStubsForClass(java.lang.Object stubs) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.STUBS_, stubs);
  }

  /**
   * Generated Property Getter for attribute -- STUBS
   * @return the value of the STUBS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getStubsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.STUBS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-SETTINGS
   * @return the value of the DEFAULT-SETTINGS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getDefaultSettingsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.DEFAULT_SETTINGS_);
    return (java.lang.Object)retnValue;
  }

  /* com.gensym.classes.G2_EventObject support */
  public Class getExternalEventClass() {
    return com.gensym.classes.modules.gdluisup.G2_GdlPathItemEvent.class;
  }

  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
}
