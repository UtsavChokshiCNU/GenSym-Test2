/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CommandListener.java
 *
 */

package com.gensym.ui;

/**
 * An interface for listening to changes in Commands.
 */
public interface CommandListener {

  /**
   * This method gets called whenever the availability of a
   * Command changes.
   * @see com.gensym.ui.Command#isAvailable
   */
  public void commandAvailabilityChanged(CommandEvent e);

  /**
   * This method gets called whenever the state of a Command changes.
   * @see com.gensym.ui.Command#getState
   */
  public void commandStateChanged(CommandEvent e);

  /**
   * This method gets called whenever the short or long description of
   * Command changes.

   * @see com.gensym.ui.Command#getDescription
   */
  public void commandDescriptionChanged(CommandEvent e);

  /**
   * This method gets called whenever the small or large icon of
   * Command changes.

   * @see com.gensym.ui.Command#getIcon
   */
  public void commandIconChanged(CommandEvent e);

}
