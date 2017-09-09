/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      RemoteQueueEventManager.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Jun 26 18:45:00 EDT 2000
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

public interface RemoteQueueEventManager extends com.gensym.classes.modules.gqs.GqsViewManager, com.gensym.classes.modules.g2evliss.G2EventListenerSupport {

  public static final Symbol REMOTE_QUEUE_EVENT_MANAGER_ = Symbol.intern ("REMOTE-QUEUE-EVENT-MANAGER");
  static final Symbol g2ClassName = REMOTE_QUEUE_EVENT_MANAGER_;
  static final Symbol[] classInheritancePath = new Symbol[] {REMOTE_QUEUE_EVENT_MANAGER_, GQS_VIEW_MANAGER_, G2_EVENT_LISTENER_SUPPORT_, OBJECT_, ITEM_, ENTITY_, BLOCK_, KB_FRAME_, SYSTEM_ITEM_, ROOT_};


  static final Symbol[] staticAttributes = new Symbol[] {};


  /**
   * Generated Property Getter for attribute -- _GRL-MONITORED-ATTRIBUTES
   * @return the value of the _GRL-MONITORED-ATTRIBUTES attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _GRL-MONITORED-ATTRIBUTES is : 
   * (Class SYMBOL-LIST)
   *
   */
  public com.gensym.classes.SymbolList get_grlMonitoredAttributes() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _GRL-MONITORED-ATTRIBUTES
   * @param _grlMonitoredAttributes new value to conclude for _GRL-MONITORED-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_grlMonitoredAttributes(com.gensym.classes.SymbolList _grlMonitoredAttributes) throws G2AccessException;

  /**
   * Generated Property Getter for attribute -- _GRL-IS-ACTIVE-MONITORING
   * @return the value of the _GRL-IS-ACTIVE-MONITORING attribute of this item
   * @exception G2AccessException if there are any communication problems
   *
   * Type Specification for _GRL-IS-ACTIVE-MONITORING is : 
   * BooleanTruthValue
   *
   */
  public boolean get_grlIsActiveMonitoring() throws G2AccessException;

  /**
   * Generated Property Setter for attribute -- _GRL-IS-ACTIVE-MONITORING
   * @param _grlIsActiveMonitoring new value to conclude for _GRL-IS-ACTIVE-MONITORING
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  public void set_grlIsActiveMonitoring(boolean _grlIsActiveMonitoring) throws G2AccessException;

  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::GQS-UPDATE-VIEW-PER-DELETE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS GQS-QUEUE,arg2:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gqsUpdateViewPerDelete(com.gensym.classes.modules.gqs.GqsQueue arg1,com.gensym.classes.UiClientItem arg2) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::GQS-UPDATE-VIEW-PER-ATTRIBUTE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS GQS-QUEUE,arg2:CLASS ITEM,arg3:SYMBOL) = ()
   */
  public  void gqsUpdateViewPerAttribute(com.gensym.classes.modules.gqs.GqsQueue arg1,com.gensym.classes.Item arg2,com.gensym.util.Symbol arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::GQS-UPDATE-VIEW-PER-REMOVAL
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS GQS-QUEUE,arg2:CLASS ITEM-LIST,arg3:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gqsUpdateViewPerRemoval(com.gensym.classes.modules.gqs.GqsQueue arg1,com.gensym.classes.ItemList arg2,com.gensym.classes.UiClientItem arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::GQS-UPDATE-VIEW-PER-ADDITION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS GQS-QUEUE,arg2:CLASS ITEM-LIST,arg3:CLASS UI-CLIENT-ITEM) = ()
   */
  public  void gqsUpdateViewPerAddition(com.gensym.classes.modules.gqs.GqsQueue arg1,com.gensym.classes.ItemList arg2,com.gensym.classes.UiClientItem arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::GRL-BATCH-UPDATE-VIEW-PER-ATTRIBUTE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS GQS-QUEUE,arg2:SEQUENCE,arg3:SYMBOL) = ()
   */
  public  void grlBatchUpdateViewPerAttribute(com.gensym.classes.modules.gqs.GqsQueue arg1,com.gensym.util.Sequence arg2,com.gensym.util.Symbol arg3) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::ADD-REMOTE-QUEUE-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS REMOTE-QUEUE-EVENT-LISTENER) = ()
   */
  public  void addRemoteQueueEventListener(com.gensym.classes.modules.grl.RemoteQueueEventListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::ADD-REMOTE-QUEUE-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS REMOTE-QUEUE-EVENT-LISTENER) = ()
   */
  public  void addG2_RemoteQueueEventListener(G2_RemoteQueueEventListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::REMOVE-REMOTE-QUEUE-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS REMOTE-QUEUE-EVENT-LISTENER) = ()
   */
  public  void removeRemoteQueueEventListener(com.gensym.classes.modules.grl.RemoteQueueEventListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::REMOVE-REMOTE-QUEUE-EVENT-LISTENER
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:CLASS REMOTE-QUEUE-EVENT-LISTENER) = ()
   */
  public  void removeG2_RemoteQueueEventListener(G2_RemoteQueueEventListener arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::REMOVE-ITEMS-FROM-QUEUE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:SEQUENCE) = ()
   */
  public  void removeItemsFromQueue(com.gensym.util.Sequence arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-MANAGER::REGISTER-ATTRIBUTES-FOR-MONITOR-ON-QUEUE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-MANAGER,arg1:SEQUENCE) = ()
   */
  public  void registerAttributesForMonitorOnQueue(com.gensym.util.Sequence arg1) throws G2AccessException;
  
}
