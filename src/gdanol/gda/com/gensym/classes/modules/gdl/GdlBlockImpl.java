/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      GdlBlockImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 27 07:59:18 EDT 2000
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

public class GdlBlockImpl extends com.gensym.classes.modules.gdl.GdlTaskImpl implements GdlBlock {


  static final long serialVersionUID = 2L;
  private static final Symbol DISCOVERY_TIME_ = Symbol.intern ("DISCOVERY-TIME");
  private static final Symbol FINISHING_TIME_ = Symbol.intern ("FINISHING-TIME");
  private static final Symbol ALLOW_INVOCATIONS_ = Symbol.intern ("ALLOW-INVOCATIONS");
  private static final Symbol SSE_ID_ = Symbol.intern ("SSE-ID");

  /* Generated constructors */

  public GdlBlockImpl() {
    super();
  }

  public GdlBlockImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- DISCOVERY-TIME
   * @param discoveryTime new value to conclude for DISCOVERY-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDiscoveryTime(int discoveryTime) throws G2AccessException {
    setAttributeValue (DISCOVERY_TIME_, new Integer (discoveryTime));
  }

  /**
   * Generated Property Getter for attribute -- DISCOVERY-TIME
   * @return the value of the DISCOVERY-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getDiscoveryTime() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (DISCOVERY_TIME_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- FINISHING-TIME
   * @param finishingTime new value to conclude for FINISHING-TIME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setFinishingTime(int finishingTime) throws G2AccessException {
    setAttributeValue (FINISHING_TIME_, new Integer (finishingTime));
  }

  /**
   * Generated Property Getter for attribute -- FINISHING-TIME
   * @return the value of the FINISHING-TIME attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getFinishingTime() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (FINISHING_TIME_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- ALLOW-INVOCATIONS
   * @param allowInvocations new value to conclude for ALLOW-INVOCATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAllowInvocations(boolean allowInvocations) throws G2AccessException {
    setAttributeValue (ALLOW_INVOCATIONS_, new Boolean (allowInvocations));
  }

  /**
   * Generated Property Getter for attribute -- ALLOW-INVOCATIONS
   * @return the value of the ALLOW-INVOCATIONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean getAllowInvocations() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (ALLOW_INVOCATIONS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- SSE-ID
   * @param sseId new value to conclude for SSE-ID
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setSseId(int sseId) throws G2AccessException {
    setAttributeValue (SSE_ID_, new Integer (sseId));
  }

  /**
   * Generated Property Getter for attribute -- SSE-ID
   * @return the value of the SSE-ID attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public int getSseId() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (SSE_ID_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAuthorsForClass(com.gensym.util.Structure authors) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.AUTHORS_, authors);
  }

  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Structure getAuthorsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.AUTHORS_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.String getChangeLogForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_LOG_);
    return (java.lang.String)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-NAME
   * @param className new value to conclude for CLASS-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setClassNameForClass(com.gensym.util.Symbol className) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.CLASS_NAME_, className);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-NAME
   * @return the value of the CLASS-NAME attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Symbol getClassNameForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @param classSpecificAttributes new value to conclude for CLASS-SPECIFIC-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setClassSpecificAttributesForClass(com.gensym.util.Sequence classSpecificAttributes) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_, classSpecificAttributes);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @return the value of the CLASS-SPECIFIC-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getClassSpecificAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CLASS-RESTRICTIONS
   * @return the value of the CLASS-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getClassRestrictionsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_RESTRICTIONS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- INSTANCE-CONFIGURATION
   * @param instanceConfiguration new value to conclude for INSTANCE-CONFIGURATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setInstanceConfigurationForClass(com.gensym.util.Sequence instanceConfiguration) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.INSTANCE_CONFIGURATION_, instanceConfiguration);
  }

  /**
   * Generated Property Getter for attribute -- INSTANCE-CONFIGURATION
   * @return the value of the INSTANCE-CONFIGURATION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getInstanceConfigurationForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INSTANCE_CONFIGURATION_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CLASS-INHERITANCE-PATH
   * @return the value of the CLASS-INHERITANCE-PATH attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getClassInheritancePathForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_INHERITANCE_PATH_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INHERITED-ATTRIBUTES
   * @return the value of the INHERITED-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getInheritedAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INHERITED_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- SUPERIOR-CLASS
   * @return the value of the SUPERIOR-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getSuperiorClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.SUPERIOR_CLASS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CAPABILITIES-AND-RESTRICTIONS
   * @return the value of the CAPABILITIES-AND-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getCapabilitiesAndRestrictionsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CAPABILITIES_AND_RESTRICTIONS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTES-SPECIFIC-TO-CLASS
   * @return the value of the ATTRIBUTES-SPECIFIC-TO-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getAttributesSpecificToClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTES_SPECIFIC_TO_CLASS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- MENU-OPTION
   * @return the value of the MENU-OPTION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getMenuOptionForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.MENU_OPTION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @param directSuperiorClasses new value to conclude for DIRECT-SUPERIOR-CLASSES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setDirectSuperiorClassesForClass(com.gensym.util.Sequence directSuperiorClasses) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_, directSuperiorClasses);
  }

  /**
   * Generated Property Getter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @return the value of the DIRECT-SUPERIOR-CLASSES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getDirectSuperiorClassesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE
   * @return the value of the CHANGE attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getChangeForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @param attributeInitializations new value to conclude for ATTRIBUTE-INITIALIZATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void setAttributeInitializationsForClass(com.gensym.util.Sequence attributeInitializations) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_, attributeInitializations);
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @return the value of the ATTRIBUTE-INITIALIZATIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.util.Sequence getAttributeInitializationsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_);
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

  // Method Name Constants
  private static final Symbol MethodName_GDL_INITIALIZE_CLASS_ = Symbol.intern ("GDL-INITIALIZE-CLASS");
  private static final Symbol MethodName_GDL_REINITIALIZE_CLASS_ = Symbol.intern ("GDL-REINITIALIZE-CLASS");
  private static final Symbol MethodName_GFR_CREATE_INSTANCE_FROM_PALETTE_ITEM_ = Symbol.intern ("GFR-CREATE-INSTANCE-FROM-PALETTE-ITEM");
  private static final Symbol MethodName_GDL_VALIDATE_CONNECTION_ = Symbol.intern ("GDL-VALIDATE-CONNECTION");
  private static final Symbol MethodName_GDL_VALIDATE_STUB_DELETION_ = Symbol.intern ("GDL-VALIDATE-STUB-DELETION");
  private static final Symbol MethodName_GFR_INITIALIZE_ = Symbol.intern ("GFR-INITIALIZE");
  private static final Symbol MethodName_GDL_RESET_ = Symbol.intern ("GDL-RESET");
  private static final Symbol MethodName_GDL_DISABLE_ = Symbol.intern ("GDL-DISABLE");
  private static final Symbol MethodName_GDL_ENABLE_ = Symbol.intern ("GDL-ENABLE");
  private static final Symbol MethodName_GDL_CLEAR_ERROR_ = Symbol.intern ("GDL-CLEAR-ERROR");
  private static final Symbol MethodName_GDL_REANIMATE_ = Symbol.intern ("GDL-REANIMATE");
  private static final Symbol MethodName_GDL_INITIALIZE_ = Symbol.intern ("GDL-INITIALIZE");
  private static final Symbol MethodName_GDL_POST_ERROR_ = Symbol.intern ("GDL-POST-ERROR");
  private static final Symbol MethodName_GFR_COPY$GDL_OBJECT_WITH_SSE_ID_ = Symbol.intern ("GDL-OBJECT-WITH-SSE-ID::GFR-COPY");
  private static final Symbol MethodName_GDL_SSE_PRESERVE_SPECIAL_ATTRIBUTE_VALUES$GDL_OBJECT_WITH_SSE_ID_ = Symbol.intern ("GDL-OBJECT-WITH-SSE-ID::GDL-SSE-PRESERVE-SPECIAL-ATTRIBUTE-VALUES");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-INITIALIZE-CLASS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS OBJECT-DEFINITION) = ()
   */
  public  void gdlInitializeClass(com.gensym.classes.ObjectDefinition arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_INITIALIZE_CLASS_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-REINITIALIZE-CLASS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS OBJECT-DEFINITION,arg2:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReinitializeClass(com.gensym.classes.ObjectDefinition arg1,com.gensym.classes.UiClientItem arg2) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
      result = (java.lang.Object)callRPC(MethodName_GDL_REINITIALIZE_CLASS_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GFR-CREATE-INSTANCE-FROM-PALETTE-ITEM
   * @return the return from calling GFR-CREATE-INSTANCE-FROM-PALETTE-ITEM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS UI-CLIENT-ITEM) = (CLASS GDL-BLOCK)
   */
  public  com.gensym.classes.modules.gdl.GdlBlock gfrCreateInstanceFromPaletteItem(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GFR_CREATE_INSTANCE_FROM_PALETTE_ITEM_, args);
      return (com.gensym.classes.modules.gdl.GdlBlock)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-VALIDATE-CONNECTION
   * @return the return from calling GDL-VALIDATE-CONNECTION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS CONNECTION,arg2:CLASS UI-CLIENT-ITEM,arg3:SYMBOL) = (TRUTH-VALUE)
   */
  public  boolean gdlValidateConnection(com.gensym.classes.Connection arg1,com.gensym.classes.UiClientItem arg2,com.gensym.util.Symbol arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
      result = (java.lang.Object)callRPC(MethodName_GDL_VALIDATE_CONNECTION_, args);
      return ((Boolean)result).booleanValue ();
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-VALIDATE-STUB-DELETION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlValidateStubDeletion(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_VALIDATE_STUB_DELETION_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GFR-INITIALIZE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS OBJECT) = ()
   */
  public  void gfrInitialize(com.gensym.classes.Object arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GFR_INITIALIZE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-RESET
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReset(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_RESET_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-DISABLE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlDisable(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_DISABLE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-ENABLE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlEnable(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_ENABLE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-CLEAR-ERROR
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK) = ()
   */
  public  void gdlClearError() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_GDL_CLEAR_ERROR_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-REANIMATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlReanimate(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_REANIMATE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-INITIALIZE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlInitialize(com.gensym.classes.UiClientItem arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_INITIALIZE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-BLOCK::GDL-POST-ERROR
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-BLOCK,arg1:SYMBOL,arg2:TEXT,arg3:INTEGER,arg4:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gdlPostError(com.gensym.util.Symbol arg1,java.lang.String arg2,int arg3,com.gensym.classes.UiClientItem arg4) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,new Integer (arg3),arg4};
      result = (java.lang.Object)callRPC(MethodName_GDL_POST_ERROR_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-OBJECT-WITH-SSE-ID::GFR-COPY
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT-WITH-SSE-ID,arg1:CLASS GDL-OBJECT-WITH-SSE-ID) = ()
   */
  public  void gfrCopy(com.gensym.classes.modules.gdl.GdlObjectWithSseId arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GFR_COPY$GDL_OBJECT_WITH_SSE_ID_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * GDL-OBJECT-WITH-SSE-ID::GDL-SSE-PRESERVE-SPECIAL-ATTRIBUTE-VALUES
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS GDL-OBJECT-WITH-SSE-ID,arg1:CLASS GDL-OBJECT-WITH-SSE-ID) = ()
   */
  public  void gdlSsePreserveSpecialAttributeValues(com.gensym.classes.modules.gdl.GdlObjectWithSseId arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_GDL_SSE_PRESERVE_SPECIAL_ATTRIBUTE_VALUES$GDL_OBJECT_WITH_SSE_ID_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
