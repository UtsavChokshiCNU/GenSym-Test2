/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 KbMessageListener.java
 *
 */

package com.gensym.ntw.util;

/**
 * Interface for listening to KB messages.  For example, LogBook and
 * Message Board messages.
 */
public interface KbMessageListener extends java.util.EventListener {

  /**
   * Listener is called when the subscription is added
   */
  public void receivedInitialContents (KbEvent event);

  /**
   * Invoked when a new kb message is added.
   */
  public void kbMessageAdded(KbEvent event);

  /**
   * Invokes when a kb message is deleted.
   */
  public void kbMessageDeleted(KbEvent event);
}
