/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MDIListener.java
 *
 */

package com.gensym.mdi;

import java.util.EventListener;

/** An interface for listening to documents being added to a MDIManager. */
public interface MDIListener extends EventListener{

  /**  This method gets called whenever a document is added to a MDIManager. */
  public void documentAdded(MDIEvent event);
}
