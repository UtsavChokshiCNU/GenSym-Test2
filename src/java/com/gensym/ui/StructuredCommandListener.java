/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 StructuredCommandListener.java
 *
 */

package com.gensym.ui;

/**
 * An interface for listening to changes in StructuredCommands.
 */
public interface StructuredCommandListener extends CommandListener{

  /**
   * This method gets called whenever of the structure of a StructuredCommand
   * changes.
   * @see com.gensym.ui.StructuredCommand#getStructuredKeys
   */
  public void commandStructureChanged(CommandEvent e);
}
