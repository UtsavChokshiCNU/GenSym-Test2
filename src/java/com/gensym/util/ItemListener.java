/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ItemListener.java
 *
 *   Description: 
 *     
 *
 *	 Author:
 *		Robert Penny		May/97
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.util;

/** 
 * Interface for receiving events regarding changes to Items.
 * Only changes to subscribable attributes on an item are sent to
 * ItemListeners.
 * <p>
 * NOTE: The value of a variable or parameter is not a
 * "subscribable attribute". To receive events regarding the value of a
 * variable or parameter, the VariableValueListener interface must be
 * implemented.
 * @see com.gensym.util.VariableValueListener
 */

public interface ItemListener extends java.util.EventListener {

  /**
   * Invoked when the listener is added. It is called within the
   * context of the addItemListener method.
   */
  public void receivedInitialValues (ItemEvent e);

  /**
   * Invoked when the denotation that the listener is interested
   * in changes.
   */
  public void itemModified (ItemEvent e);

  /**
   * Invoked when the denotation that the listener is interested
   * in is no longer reachable.
   */
  public void itemDeleted (ItemEvent e);

}
