/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      EventSourceClassImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Fri Sep 21 13:50:16 EDT 2007
 *
 */


package com.gensym.classes.modules.jgidemo;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class EventSourceClassImpl extends com.gensym.classes.modules.jgidemo.GenericREmployeeImpl implements EventSourceClass {


  static final long serialVersionUID = 2L;
  private static final Symbol _EVENT_LISTENERS_ = Symbol.intern ("_EVENT-LISTENERS");

  /* Generated constructors */

  public EventSourceClassImpl() {
    super();
  }

  public EventSourceClassImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  public EventSourceClassImpl(G2Access context, int handle, int handleVersion, G2__BaseImpl wrap, Structure attributes) {
    super (context, handle, handleVersion, wrap, attributes);
  }


  /**
   * Generated Property Setter for attribute -- _EVENT-LISTENERS
   * @param _eventListeners new value to conclude for _EVENT-LISTENERS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void set_eventListeners(com.gensym.classes.modules.g2evliss._g2lissupListenerList _eventListeners) throws G2AccessException {
    setAttributeValue (_EVENT_LISTENERS_, _eventListeners);
  }

  /**
   * Generated Property Getter for attribute -- _EVENT-LISTENERS
   * @return the value of the _EVENT-LISTENERS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.modules.g2evliss._g2lissupListenerList get_eventListeners() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_EVENT_LISTENERS_);
    return (com.gensym.classes.modules.g2evliss._g2lissupListenerList)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAuthorsForClass(com.gensym.util.Structure authors) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.AUTHORS_, authors);
  }

  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getAuthorsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.AUTHORS_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getChangeLogForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_LOG_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-NAME
   * @param className new value to conclude for CLASS-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setClassNameForClass(com.gensym.util.Symbol className) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.CLASS_NAME_, className);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-NAME
   * @return the value of the CLASS-NAME attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getClassNameForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @param directSuperiorClasses new value to conclude for DIRECT-SUPERIOR-CLASSES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDirectSuperiorClassesForClass(com.gensym.util.Sequence directSuperiorClasses) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_, directSuperiorClasses);
  }

  /**
   * Generated Property Getter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @return the value of the DIRECT-SUPERIOR-CLASSES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getDirectSuperiorClassesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @param classSpecificAttributes new value to conclude for CLASS-SPECIFIC-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setClassSpecificAttributesForClass(com.gensym.util.Sequence classSpecificAttributes) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_, classSpecificAttributes);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @return the value of the CLASS-SPECIFIC-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getClassSpecificAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CLASS-RESTRICTIONS
   * @return the value of the CLASS-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
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
  @Override
  public void setInstanceConfigurationForClass(com.gensym.util.Sequence instanceConfiguration) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.INSTANCE_CONFIGURATION_, instanceConfiguration);
  }

  /**
   * Generated Property Getter for attribute -- INSTANCE-CONFIGURATION
   * @return the value of the INSTANCE-CONFIGURATION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getInstanceConfigurationForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INSTANCE_CONFIGURATION_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE
   * @return the value of the CHANGE attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getChangeForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CLASS-INHERITANCE-PATH
   * @return the value of the CLASS-INHERITANCE-PATH attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getClassInheritancePathForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_INHERITANCE_PATH_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INHERITED-ATTRIBUTES
   * @return the value of the INHERITED-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getInheritedAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INHERITED_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INITIALIZABLE-SYSTEM-ATTRIBUTES
   * @return the value of the INITIALIZABLE-SYSTEM-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getInitializableSystemAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INITIALIZABLE_SYSTEM_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @param attributeInitializations new value to conclude for ATTRIBUTE-INITIALIZATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAttributeInitializationsForClass(com.gensym.util.Sequence attributeInitializations) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_, attributeInitializations);
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @return the value of the ATTRIBUTE-INITIALIZATIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getAttributeInitializationsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- SUPERIOR-CLASS
   * @return the value of the SUPERIOR-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getSuperiorClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.SUPERIOR_CLASS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CAPABILITIES-AND-RESTRICTIONS
   * @return the value of the CAPABILITIES-AND-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getCapabilitiesAndRestrictionsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CAPABILITIES_AND_RESTRICTIONS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTES-SPECIFIC-TO-CLASS
   * @return the value of the ATTRIBUTES-SPECIFIC-TO-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getAttributesSpecificToClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTES_SPECIFIC_TO_CLASS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- MENU-OPTION
   * @return the value of the MENU-OPTION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getMenuOptionForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.MENU_OPTION_);
    return (java.lang.Object)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_ADD_EVENT_SOURCE_LISTENER_ = Symbol.intern ("ADD-EVENT-SOURCE-LISTENER");
  private static final Symbol MethodName_REMOVE_EVENT_SOURCE_LISTENER_ = Symbol.intern ("REMOVE-EVENT-SOURCE-LISTENER");
  private static final Symbol MethodName_FIRE_AN_EVENT_ = Symbol.intern ("FIRE-AN-EVENT");
  private static final Symbol MethodName_ADD_G2_EVENT_LISTENER$G2_EVENT_LISTENER_SUPPORT_ = Symbol.intern ("G2-EVENT-LISTENER-SUPPORT::ADD-G2-EVENT-LISTENER");
  private static final Symbol MethodName_REMOVE_G2_EVENT_LISTENER$G2_EVENT_LISTENER_SUPPORT_ = Symbol.intern ("G2-EVENT-LISTENER-SUPPORT::REMOVE-G2-EVENT-LISTENER");
  private static final Symbol MethodName_GET_EVENT_LISTENER_LIST$G2_EVENT_LISTENER_SUPPORT_ = Symbol.intern ("G2-EVENT-LISTENER-SUPPORT::GET-EVENT-LISTENER-LIST");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * EVENT-SOURCE-CLASS::ADD-EVENT-SOURCE-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS EVENT-SOURCE-CLASS,arg1:CLASS EVENT-SOURCE-LISTENER) = ()
   */
  @Override
  public  void addEventSourceListener(com.gensym.classes.modules.jgidemo.EventSourceListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_ADD_EVENT_SOURCE_LISTENER_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * EVENT-SOURCE-CLASS::ADD-EVENT-SOURCE-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS EVENT-SOURCE-CLASS,arg1:CLASS EVENT-SOURCE-LISTENER) = ()
   */
  @Override
  public  void addG2_EventSourceListener(G2_EventSourceListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      G2JavaStubController.getG2JavaStubController().addJavaListenerToG2EventSource(this,
                MethodName_ADD_EVENT_SOURCE_LISTENER_,
                "com.gensym.classes.modules.jgidemo.EventSourceListener",
                Symbol.intern("EVENT-SOURCE-LISTENER"),
                arg1);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * EVENT-SOURCE-CLASS::REMOVE-EVENT-SOURCE-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS EVENT-SOURCE-CLASS,arg1:CLASS EVENT-SOURCE-LISTENER) = ()
   */
  @Override
  public  void removeEventSourceListener(com.gensym.classes.modules.jgidemo.EventSourceListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_REMOVE_EVENT_SOURCE_LISTENER_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * EVENT-SOURCE-CLASS::REMOVE-EVENT-SOURCE-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS EVENT-SOURCE-CLASS,arg1:CLASS EVENT-SOURCE-LISTENER) = ()
   */
  @Override
  public  void removeG2_EventSourceListener(G2_EventSourceListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      G2JavaStubController.getG2JavaStubController().removeJavaListenerFromG2EventSource(this,
                MethodName_REMOVE_EVENT_SOURCE_LISTENER_,
                "com.gensym.classes.modules.jgidemo.EventSourceListener",
                Symbol.intern("EVENT-SOURCE-LISTENER"),
                arg1);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * EVENT-SOURCE-CLASS::FIRE-AN-EVENT
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS EVENT-SOURCE-CLASS,arg1:TEXT) = ()
   */
  @Override
  public  void fireAnEvent(java.lang.String arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_FIRE_AN_EVENT_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2-EVENT-LISTENER-SUPPORT::ADD-G2-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2-EVENT-LISTENER-SUPPORT,arg1:CLASS G2-EVENT-LISTENER) = ()
   */
  @Override
  public  void addG2EventListener(com.gensym.classes.modules.g2evliss.G2EventListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_ADD_G2_EVENT_LISTENER$G2_EVENT_LISTENER_SUPPORT_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2-EVENT-LISTENER-SUPPORT::REMOVE-G2-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2-EVENT-LISTENER-SUPPORT,arg1:CLASS G2-EVENT-LISTENER) = ()
   */
  @Override
  public  void removeG2EventListener(com.gensym.classes.modules.g2evliss.G2EventListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_REMOVE_G2_EVENT_LISTENER$G2_EVENT_LISTENER_SUPPORT_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * G2-EVENT-LISTENER-SUPPORT::GET-EVENT-LISTENER-LIST
   * @return the return from calling GET-EVENT-LISTENER-LIST
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS G2-EVENT-LISTENER-SUPPORT) = (CLASS ITEM-LIST)
   */
  @Override
  public  com.gensym.classes.ItemList getEventListenerList() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_GET_EVENT_LISTENER_LIST$G2_EVENT_LISTENER_SUPPORT_, args);
      return (com.gensym.classes.ItemList)result;
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
