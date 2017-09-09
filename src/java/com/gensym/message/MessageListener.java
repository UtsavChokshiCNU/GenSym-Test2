/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MessageListener.java
 *
 *  Description:
 *              Object must implement this interface to receive MessageEvents.
 *
 *	 Author:
 *		Robert Penny		Jul/97
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.message;

import java.util.EventListener;
/* Object must implement this interface to receive MessageEvents. */
public interface MessageListener extends EventListener {
  /** Once a Listener is registered with the Message class, it will receive
   * message events via this method.
   */
  public void processMessageEvent(MessageEvent event);

}
