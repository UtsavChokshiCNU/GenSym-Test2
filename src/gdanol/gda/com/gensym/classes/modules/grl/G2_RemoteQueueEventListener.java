/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      G2_RemoteQueueEventListener.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 1
 *
 *          Date: Mon Jun 26 18:44:57 EDT 2000
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

public interface G2_RemoteQueueEventListener extends java.util.EventListener {

  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-LISTENER::QUEUE-ITEMS-ADDED
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-LISTENER,arg1:CLASS REMOTE-QUEUE-EVENT) = ()
   */
  public  void queueItemsAdded(com.gensym.classes.modules.grl.G2_RemoteQueueEvent arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-LISTENER::QUEUE-ITEMS-REMOVED
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-LISTENER,arg1:CLASS REMOTE-QUEUE-EVENT) = ()
   */
  public  void queueItemsRemoved(com.gensym.classes.modules.grl.G2_RemoteQueueEvent arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-LISTENER::QUEUE-ITEMS-ATTRIBUTE-CHANGED
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-LISTENER,arg1:CLASS REMOTE-QUEUE-EVENT) = ()
   */
  public  void queueItemsAttributeChanged(com.gensym.classes.modules.grl.G2_RemoteQueueEvent arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-LISTENER::QUEUE-RECEIVED-INITIAL-STATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-LISTENER,arg1:CLASS REMOTE-QUEUE-EVENT) = ()
   */
  public  void queueReceivedInitialState(com.gensym.classes.modules.grl.G2_RemoteQueueEvent arg1) throws G2AccessException;
  
  /**
   * Auto Generated method for G2 Method
   * REMOTE-QUEUE-EVENT-LISTENER::QUEUE-INVALIDATE-STATE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS REMOTE-QUEUE-EVENT-LISTENER,arg1:CLASS REMOTE-QUEUE-EVENT) = ()
   */
  public  void queueInvalidateState(com.gensym.classes.modules.grl.G2_RemoteQueueEvent arg1) throws G2AccessException;
  
}
