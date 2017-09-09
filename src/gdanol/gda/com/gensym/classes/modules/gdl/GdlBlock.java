/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlBlock.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Jun 26 18:45:44 EDT 2000
 *
 */


package com.gensym.classes.modules.gdl;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public interface GdlBlock extends com.gensym.classes.modules.gdl.GdlTask, com.gensym.classes.modules.gdl.GdlObjectWithSseId {

  public static final Symbol GDL_BLOCK_ = Symbol.intern ("GDL-BLOCK");
  static final Symbol g2ClassName = GDL_BLOCK_;
  static final Symbol[] classInheritancePath = new Symbol[] {GDL_BLOCK_, GDL_TASK_, GDL_TASK_OR_EVENT_, GDL_OBJECT_, GFR_OBJECT_WITH_UUID_, GDL_OBJECT_WITH_SSE_ID_, OBJECT_, GFR_ITEM_WITH_UUID_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- DISCOVERY-TIME
   * @return the value of the DISCOVERY-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for DISCOVERY-TIME is : 
   * Integer
   *
   */
  public int getDiscoveryTime() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- DISCOVERY-TIME
   * @param discoveryTime new value to conclude for DISCOVERY-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDiscoveryTime(int discoveryTime) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- FINISHING-TIME
   * @return the value of the FINISHING-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for FINISHING-TIME is : 
   * Integer
   *
   */
  public int getFinishingTime() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- FINISHING-TIME
   * @param finishingTime new value to conclude for FINISHING-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFinishingTime(int finishingTime) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- ALLOW-INVOCATIONS
   * @return the value of the ALLOW-INVOCATIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for ALLOW-INVOCATIONS is : 
   * BooleanTruthValue
   *
   */
  public boolean getAllowInvocations() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- ALLOW-INVOCATIONS
   * @param allowInvocations new value to conclude for ALLOW-INVOCATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAllowInvocations(boolean allowInvocations) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-INITIALIZE-CLASS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS OBJECT-DEFINITION) = ()
   */
  public  void gdlInitializeClass(com.gensym.classes.ObjectDefinition arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-REINITIALIZE-CLASS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS OBJECT-DEFINITION,arg2:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReinitializeClass(com.gensym.classes.ObjectDefinition arg1,com.gensym.classes.UiClientItem arg2) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GFR-CREATE-INSTANCE-FROM-PALETTE-ITEM
   * @return the return from calling GFR-CREATE-INSTANCE-FROM-PALETTE-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS UI-CLIENT-ITEM) = (CLASS GDL-BLOCK)
   */
  public  com.gensym.classes.modules.gdl.GdlBlock gfrCreateInstanceFromPaletteItem(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-VALIDATE-CONNECTION
   * @return the return from calling GDL-VALIDATE-CONNECTION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS CONNECTION,arg2:CLASS UI-CLIENT-ITEM,arg3:SYMBOL) = (TRUTH-VALUE)
   */
  public  boolean gdlValidateConnection(com.gensym.classes.Connection arg1,com.gensym.classes.UiClientItem arg2,com.gensym.util.Symbol arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-VALIDATE-STUB-DELETION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlValidateStubDeletion(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GFR-INITIALIZE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS OBJECT) = ()
   */
  public  void gfrInitialize(com.gensym.classes.Object arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-RESET
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReset(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-DISABLE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlDisable(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-ENABLE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlEnable(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-CLEAR-ERROR
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK) = ()
   */
  public  void gdlClearError() throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-REANIMATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReanimate(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-INITIALIZE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlInitialize(com.gensym.classes.UiClientItem arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-POST-ERROR
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:SYMBOL,arg2:TEXT,arg3:INTEGER,arg4:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlPostError(com.gensym.util.Symbol arg1,java.lang.String arg2,int arg3,com.gensym.classes.UiClientItem arg4) throws G2AccessException;
  
}
