/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlPathItemEventManagerImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue May 16 14:12:39 GMT+04:00 2000
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

public class GdlPathItemEventManagerImpl extends com.gensym.classes.modules.g2evliss.G2EventListenerSupportImpl implements GdlPathItemEventManager {


  static final long serialVersionUID = 2L;

  /* Generated constructors */

  public GdlPathItemEventManagerImpl() {
    super();
  }

  public GdlPathItemEventManagerImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
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

  // Method Name Constants
  private static final Symbol MethodName_GDL_UPDATE_DISPLAY_ = Symbol.intern ("GDL-UPDATE-DISPLAY");
  private static final Symbol MethodName_ADD_GDL_PATH_ITEM_EVENT_LISTENER_ = Symbol.intern ("ADD-GDL-PATH-ITEM-EVENT-LISTENER");
  private static final Symbol MethodName_REMOVE_GDL_PATH_ITEM_EVENT_LISTENER_ = Symbol.intern ("REMOVE-GDL-PATH-ITEM-EVENT-LISTENER");
  private static final Symbol MethodName_GDL_HIDE_DISPLAY_ = Symbol.intern ("GDL-HIDE-DISPLAY");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM-EVENT-MANAGER::GDL-UPDATE-DISPLAY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM-EVENT-MANAGER,arg1:CLASS GDL-PATH-ITEM) = ()
   */
  public  void gdlUpdateDisplay(com.gensym.classes.modules.gdl.GdlPathItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_UPDATE_DISPLAY_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM-EVENT-MANAGER::ADD-GDL-PATH-ITEM-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM-EVENT-MANAGER,arg1:CLASS GDL-PATH-ITEM-EVENT-LISTENER) = ()
   */
  public  void addGdlPathItemEventListener(com.gensym.classes.modules.gdluisup.GdlPathItemEventListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_ADD_GDL_PATH_ITEM_EVENT_LISTENER_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM-EVENT-MANAGER::ADD-GDL-PATH-ITEM-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM-EVENT-MANAGER,arg1:CLASS GDL-PATH-ITEM-EVENT-LISTENER) = ()
   */
  public  void addG2_GdlPathItemEventListener(G2_GdlPathItemEventListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      G2JavaStubController.getG2JavaStubController().addJavaListenerToG2EventSource(this,
                MethodName_ADD_GDL_PATH_ITEM_EVENT_LISTENER_,
                "com.gensym.classes.modules.gdluisup.GdlPathItemEventListener",
                Symbol.intern("GDL-PATH-ITEM-EVENT-LISTENER"),
                arg1);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM-EVENT-MANAGER::REMOVE-GDL-PATH-ITEM-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM-EVENT-MANAGER,arg1:CLASS GDL-PATH-ITEM-EVENT-LISTENER) = ()
   */
  public  void removeGdlPathItemEventListener(com.gensym.classes.modules.gdluisup.GdlPathItemEventListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_REMOVE_GDL_PATH_ITEM_EVENT_LISTENER_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM-EVENT-MANAGER::REMOVE-GDL-PATH-ITEM-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM-EVENT-MANAGER,arg1:CLASS GDL-PATH-ITEM-EVENT-LISTENER) = ()
   */
  public  void removeG2_GdlPathItemEventListener(G2_GdlPathItemEventListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      G2JavaStubController.getG2JavaStubController().removeJavaListenerFromG2EventSource(this,
                MethodName_REMOVE_GDL_PATH_ITEM_EVENT_LISTENER_,
                "com.gensym.classes.modules.gdluisup.GdlPathItemEventListener",
                Symbol.intern("GDL-PATH-ITEM-EVENT-LISTENER"),
                arg1);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-PATH-ITEM-EVENT-MANAGER::GDL-HIDE-DISPLAY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-PATH-ITEM-EVENT-MANAGER,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlHideDisplay(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_HIDE_DISPLAY_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
