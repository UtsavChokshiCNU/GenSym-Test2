/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 StructuredCommand.java
 *
 */

package com.gensym.ui;

import java.util.Vector;

/**
 * An interface that defines Commands with one or more of these
 *  characteristics:
 *    (a) logical groupings of actions,
 *    (b) a hierarchical structure of actions,
 *    (c) a dynamic number of actions.
 *<p>
 * The tree-like structure of a <code>StructuredCommand</code> is defined as follows:
 *<p>
 *  - Each <code>Vector</code> is a logical grouping of actions.  When added to a
 *    "command-aware" container, each grouping may be visually separated.  
 *    For example, a "command-aware" menu may place a separator between groups.  
 *    Each <code>Vector</code> may contain <code>Vectors</code>, 
 *    <code>SubCommands</code>, and/or <code>Strings</code>.
 * </p><p>
 *  - Each <code>SubCommand</code> defines a step in the hierarchy.  
 *    A <code>SubCommand</code> is simply
 *    a (key, vector) pair.  The key defines the parent node and the vector defines
 *    its children.  The vector of a <code>SubComman</code>d may contain 
 *    <code>Vectors</code>, <code>SubCommands</code>, 
 *    and/or <code>Strings</code>.  When added to a "command-aware" menu, each 
 *    <code>SubCommand</code> may be
 *    represented by a pull-right menu.
 * </p><p>
 *  - Each <code>String</code> is a command key and defines an action.  The leaves of 
 *    the tree
 *    are always <code>Strings</code>.
 *</p></p><p>
 * Clients may add themselves as listeners to get notification of changes in the
 * structure of a <code>StructuredCommand</code>.
 *</p>
 * @see com.gensym.ui.menu.CMenu
 * @see com.gensym.ui.menu.CMenuBar
 * @see com.gensym.ui.menu.awt.CMenu
 * @see com.gensym.ui.menu.awt.CMenuBar
 * @see com.gensym.ui.SubCommand
 */
public interface StructuredCommand extends Command{

  /**
   * Returns a <code>Vector</code> that contains the hierarchical structure 
   * and/or logical grouping of the <code>StructuredCommand</code>.
   */
  public Vector getStructuredKeys();

  
  /**
   * Adds a <code>StructuredCommandListener</code>.
   */
  public void addStructuredCommandListener (StructuredCommandListener listener);

  /**
   * Removes a <code>StructuredCommandListener</code>.
   */
  public void removeStructuredCommandListener(StructuredCommandListener listener);

}
