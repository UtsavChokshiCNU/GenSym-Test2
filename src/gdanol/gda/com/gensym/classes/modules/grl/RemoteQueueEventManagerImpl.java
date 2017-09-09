/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      RemoteQueueEventManagerImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Tue Jun 13 11:46:02 EDT 2000
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

public class RemoteQueueEventManagerImpl extends com.gensym.classes.modules.gqs.GqsViewManagerImpl implements RemoteQueueEventManager {


  static final long serialVersionUID = 2L;
  private static final Symbol _GRL_MONITORED_ATTRIBUTES_ = Symbol.intern ("_GRL-MONITORED-ATTRIBUTES");
  private static final Symbol _GRL_IS_ACTIVE_MONITORING_ = Symbol.intern ("_GRL-IS-ACTIVE-MONITORING");
  private static final Symbol _EVENT_LISTENERS_ = Symbol.intern ("_EVENT-LISTENERS");

  /* Generated constructors */

  public RemoteQueueEventManagerImpl() {
    super();
  }

  public RemoteQueueEventManagerImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- _GRL-MONITORED-ATTRIBUTES
   * @param _grlMonitoredAttributes new value to conclude for _GRL-MONITORED-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_grlMonitoredAttributes(com.gensym.classes.SymbolList _grlMonitoredAttributes) throws G2AccessException {
    setAttributeValue (_GRL_MONITORED_ATTRIBUTES_, _grlMonitoredAttributes);
  }

  /**
   * Generated Property Getter for attribute -- _GRL-MONITORED-ATTRIBUTES
   * @return the value of the _GRL-MONITORED-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public com.gensym.classes.SymbolList get_grlMonitoredAttributes() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_GRL_MONITORED_ATTRIBUTES_);
    return (com.gensym.classes.SymbolList)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- _GRL-IS-ACTIVE-MONITORING
   * @param _grlIsActiveMonitoring new value to conclude for _GRL-IS-ACTIVE-MONITORING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_grlIsActiveMonitoring(boolean _grlIsActiveMonitoring) throws G2AccessException {
    setAttributeValue (_GRL_IS_ACTIVE_MONITORING_, new Boolean (_grlIsActiveMonitoring));
  }

  /**
   * Generated Property Getter for attribute -- _GRL-IS-ACTIVE-MONITORING
   * @return the value of the _GRL-IS-ACTIVE-MONITORING attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  public boolean get_grlIsActiveMonitoring() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (_GRL_IS_ACTIVE_MONITORING_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- _EVENT-LISTENERS
   * @param _eventListeners new value to conclude for _EVENT-LISTENERS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_eventListeners(com.gensym.classes.modules.g2evliss._g2lissupListenerList _eventListeners) throws G2AccessException {
    setAttributeValue (_EVENT_LISTENERS_, _eventListeners);
  }

  /**
   * Generated Property Getter for attribute -- _EVENT-LISTENERS
   * @return the value of the _EVENT-LISTENERS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
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
   * Generated Property Getter for attribute -- CHANGE
   * @return the value of the CHANGE attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  public java.lang.Object getChangeForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_);
    return (java.lang.Object)retnValue;
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
   * Generated Property Getter for attribute -- INITIALIZABLE-SYSTEM-ATTRIBUTES
   * @return the value of the INITIALIZABLE-SYSTEM-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
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

  // Method Name Constants
  private static final Symbol MethodName_GQS_UPDATE_VIEW_PER_DELETE_ = Symbol.intern ("GQS-UPDATE-VIEW-PER-DELETE");
  private static final Symbol MethodName_GQS_UPDATE_VIEW_PER_ATTRIBUTE_ = Symbol.intern ("GQS-UPDATE-VIEW-PER-ATTRIBUTE");
  private static final Symbol MethodName_GQS_UPDATE_VIEW_PER_REMOVAL_ = Symbol.intern ("GQS-UPDATE-VIEW-PER-REMOVAL");
  private static final Symbol MethodName_GQS_UPDATE_VIEW_PER_ADDITION_ = Symbol.intern ("GQS-UPDATE-VIEW-PER-ADDITION");
  private static final Symbol MethodName_GRL_BATCH_UPDATE_VIEW_PER_ATTRIBUTE_ = Symbol.intern ("GRL-BATCH-UPDATE-VIEW-PER-ATTRIBUTE");
  private static final Symbol MethodName_ADD_REMOTE_QUEUE_EVENT_LISTENER_ = Symbol.intern ("ADD-REMOTE-QUEUE-EVENT-LISTENER");
  private static final Symbol MethodName_REMOVE_REMOTE_QUEUE_EVENT_LISTENER_ = Symbol.intern ("REMOVE-REMOTE-QUEUE-EVENT-LISTENER");
  private static final Symbol MethodName_REMOVE_ITEMS_FROM_QUEUE_ = Symbol.intern ("REMOVE-ITEMS-FROM-QUEUE");
  private static final Symbol MethodName_REGISTER_ATTRIBUTES_FOR_MONITOR_ON_QUEUE_ = Symbol.intern ("REGISTER-ATTRIBUTES-FOR-MONITOR-ON-QUEUE");
  private static final Symbol MethodName_ADD_G2_EVENT_LISTENER$G2_EVENT_LISTENER_SUPPORT_ = Symbol.intern ("G2-EVENT-LISTENER-SUPPORT::ADD-G2-EVENT-LISTENER");
  private static final Symbol MethodName_REMOVE_G2_EVENT_LISTENER$G2_EVENT_LISTENER_SUPPORT_ = Symbol.intern ("G2-EVENT-LISTENER-SUPPORT::REMOVE-G2-EVENT-LISTENER");
  private static final Symbol MethodName_GET_EVENT_LISTENER_LIST$G2_EVENT_LISTENER_SUPPORT_ = Symbol.intern ("G2-EVENT-LISTENER-SUPPORT::GET-EVENT-LISTENER-LIST");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::GQS-UPDATE-VIEW-PER-DELETE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS GQS-QUEUE,arg2:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gqsUpdateViewPerDelete(com.gensym.classes.modules.gqs.GqsQueue arg1,com.gensym.classes.UiClientItem arg2) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2};
      result = (java.lang.Object)callRPC(MethodName_GQS_UPDATE_VIEW_PER_DELETE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::GQS-UPDATE-VIEW-PER-ATTRIBUTE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS GQS-QUEUE,arg2:CLASS ITEM,arg3:SYMBOL) = ()
   */
  public  void gqsUpdateViewPerAttribute(com.gensym.classes.modules.gqs.GqsQueue arg1,com.gensym.classes.Item arg2,com.gensym.util.Symbol arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
      result = (java.lang.Object)callRPC(MethodName_GQS_UPDATE_VIEW_PER_ATTRIBUTE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::GQS-UPDATE-VIEW-PER-REMOVAL
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS GQS-QUEUE,arg2:CLASS ITEM-LIST,arg3:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gqsUpdateViewPerRemoval(com.gensym.classes.modules.gqs.GqsQueue arg1,com.gensym.classes.ItemList arg2,com.gensym.classes.UiClientItem arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
      result = (java.lang.Object)callRPC(MethodName_GQS_UPDATE_VIEW_PER_REMOVAL_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::GQS-UPDATE-VIEW-PER-ADDITION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS GQS-QUEUE,arg2:CLASS ITEM-LIST,arg3:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gqsUpdateViewPerAddition(com.gensym.classes.modules.gqs.GqsQueue arg1,com.gensym.classes.ItemList arg2,com.gensym.classes.UiClientItem arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
      result = (java.lang.Object)callRPC(MethodName_GQS_UPDATE_VIEW_PER_ADDITION_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::GRL-BATCH-UPDATE-VIEW-PER-ATTRIBUTE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS GQS-QUEUE,arg2:SEQUENCE,arg3:SYMBOL) = ()
   */
  public  void grlBatchUpdateViewPerAttribute(com.gensym.classes.modules.gqs.GqsQueue arg1,com.gensym.util.Sequence arg2,com.gensym.util.Symbol arg3) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1,arg2,arg3};
      result = (java.lang.Object)callRPC(MethodName_GRL_BATCH_UPDATE_VIEW_PER_ATTRIBUTE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::ADD-REMOTE-QUEUE-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS REMOTE-QUEUE-EVENT-LISTENER) = ()
   */
  public  void addRemoteQueueEventListener(com.gensym.classes.modules.grl.RemoteQueueEventListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_ADD_REMOTE_QUEUE_EVENT_LISTENER_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::ADD-REMOTE-QUEUE-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS REMOTE-QUEUE-EVENT-LISTENER) = ()
   */
  public  void addG2_RemoteQueueEventListener(G2_RemoteQueueEventListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      G2JavaStubController.getG2JavaStubController().addJavaListenerToG2EventSource(this,
                MethodName_ADD_REMOTE_QUEUE_EVENT_LISTENER_,
                "com.gensym.classes.modules.grl.RemoteQueueEventListener",
                Symbol.intern("REMOTE-QUEUE-EVENT-LISTENER"),
                arg1);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::REMOVE-REMOTE-QUEUE-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS REMOTE-QUEUE-EVENT-LISTENER) = ()
   */
  public  void removeRemoteQueueEventListener(com.gensym.classes.modules.grl.RemoteQueueEventListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_REMOVE_REMOTE_QUEUE_EVENT_LISTENER_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::REMOVE-REMOTE-QUEUE-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS REMOTE-QUEUE-EVENT-LISTENER) = ()
   */
  public  void removeG2_RemoteQueueEventListener(G2_RemoteQueueEventListener arg1) throws G2AccessException
{
    if (isByHandle()) {
      G2JavaStubController.getG2JavaStubController().removeJavaListenerFromG2EventSource(this,
                MethodName_REMOVE_REMOTE_QUEUE_EVENT_LISTENER_,
                "com.gensym.classes.modules.grl.RemoteQueueEventListener",
                Symbol.intern("REMOTE-QUEUE-EVENT-LISTENER"),
                arg1);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::REMOVE-ITEMS-FROM-QUEUE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:SEQUENCE) = ()
   */
  public  void removeItemsFromQueue(com.gensym.util.Sequence arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_REMOVE_ITEMS_FROM_QUEUE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::REGISTER-ATTRIBUTES-FOR-MONITOR-ON-QUEUE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:SEQUENCE) = ()
   */
  public  void registerAttributesForMonitorOnQueue(com.gensym.util.Sequence arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_REGISTER_ATTRIBUTES_FOR_MONITOR_ON_QUEUE_, args);
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
