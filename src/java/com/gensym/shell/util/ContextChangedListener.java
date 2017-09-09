/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ContextChangedListener.java
 *
 */

package com.gensym.shell.util;

/** An interface for listening to changes in the current context. */
public interface ContextChangedListener {

  /** This method gets called whenever the current connection is changed. If
  * the last connection managed by the ConnectionManager is closed, this method
  * will be called with e.getConnection() == null. */
  public void currentConnectionChanged(ContextChangedEvent e);

}

