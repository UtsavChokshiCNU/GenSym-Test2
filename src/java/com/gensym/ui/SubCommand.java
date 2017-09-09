/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SubCommand.java
 *
 */

package com.gensym.ui;

import java.util.Vector;

/**
 * A class that in defines a "step" in the hierachical structure of a
 * <code>StructuredCommand</code>.
 * A <code>SubCommand</code> is a (key, vector) pair.  The key defines the parent 
 * node and the 
 * vector defines its children. The vector of a <code>SubCommand</code> may contain 
 * <code>Vectors</code>,
 * <code>SubCommands</code>, and/or <code>Strings</code>.  When added to a 
 * "command-aware" menu, a <code>SubCommand </code>
 * may be represented by a pull-right menu.  When added to a "command-aware" menu 
 * bar, a <code>SubCommand<code> may be represented by a menu.
 *
 * @see com.gensym.ui.StructuredCommand
 * @see com.gensym.ui.AbstractStructuredCommand
 * @see com.gensym.ui.menu.CMenu
 * @com.gensym.ui.menu.CMenuBar
 * @see com.gensym.ui.menu.awt.CMenu
 * @see com.gensym.ui.menu.awt.CMenuBar
 */
public class SubCommand{
  private String key;
  private Vector structure;

  /** Creates a <code>SubCommand</code> from the specified <code>key and 
   * <code>Vector</code>. */
  public SubCommand(String key, Vector structure){
    this.key = key;
    this.structure = structure;
  }

  /** Returns the key for this <code>SubCommand</code>. */
  public String getKey(){
    return key;
  }

  /** 
   * Returns a <code>Vector</code> that represents the hierachical structure of this 
   * <code>SubCommand</code>. The Vector may contain <code>Vectors</code>, 
   * <code>Strings</code>, or <code>SubCommands</code>.
   */
  public Vector getStructure(){
    return structure;
  }

  @Override
  public String toString(){
    return "com.gensym.ui.SubCommand["+key+", "+structure.toString()+"]";
  }
}
