/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Command.java
 *
 */

package com.gensym.ui;

import java.awt.Image;
import java.awt.event.ActionListener;

/**
 * In general, a command is an action that the user can perform through the UI.  
 * Commands are usually verbs.   A single command may be accessed through several 
 *  UI controls.  For example, "Cut" is a command that users typically
 * execute through a menu choice or a toolbar button. 
 *<p>
 * This interface defines commands (actions) that are executed through the UI.
 * It provides information regarding the command's descriptions (both textual 
 * and iconic), state, and availability.  The command's action is defined in 
 * the <code>actionPerformed</code> method.
 * A <code>Command</code> may perform one or more actions.  Each action is 
 * identified by a 
 * unique key.  For example, a single Command that handles Cut, Copy, and Paste 
 * would have 3 keys, one for Cut, Copy, and Paste respectively. 
 *</p><p>
 * Clients can add themselves as listeners to know about changes in the availability,
 * state, and descriptions of the Command. Typically, the UI representing the <code>
 * Command</code> listens for <code>CommandEvents</code>.  For example, if a toolbar 
 * button represented the Cut 
 * command, it would be disabled when the command becomes unavailable.
 *</p><p>
 * When a <code>Command</code> is added to a "Command-aware" container, the container
 * uses the <code>Command</code> interface methods to get information concerning the 
 * Command, and represents the command appropriately.  For example, adding a 
 * <code>Command</code> to a "Command-aware" 
 * menu may result in adding a menu item for each action in the <code>Command</code>
 * to the menu.
 * The label of each menu item may be the result of <code>getDescription</code>.  
 * In addition,
 * the generated menu items would keep in sync with the command's availability,
 * state, and descriptions.
 *</p>
 * @see com.gensym.ui.menu.CMenu
 * @see com.gensym.ui.menu.awt.CMenu
 * @see com.gensym.ui.toolbar.ToolBar
 */
public interface Command extends ActionListener{

  public static final String SHORT_DESCRIPTION = "ShortDescription";
  public static final String LONG_DESCRIPTION = "LongDescription";
  public static final String SMALL_ICON = "SmallIcon";
  public static final String LARGE_ICON = "LargeIcon";

  /**
   * Returns a boolean indicating whether command
   * is currently available.
   */
  public boolean isAvailable (String cmdKey);
  
  /**
   * Adds a <code>CommandListener</code>.
   */
  public void addCommandListener (CommandListener listener);

  /**
   * Removes a <code>CommandListener</code>.
   */
  public void removeCommandListener(CommandListener listener);

  /**
   * Returns an array of command keys. Each key
   * represents a particular action that can be executed
   * by the <code>Command</code>.
   */

  public String[] getKeys();

  /**
   * Returns a textual description for command.
   * The <code>key</code> should be either <code>SHORT_DESCRIPTION</code> or
   * <code>LONG_DESCRIPTION</code>.
   */
  public String getDescription (String cmdKey, String key);

  /**
   * Returns an image of the size indicated by <code>key</code>.
   * <code>Key</code> should be either <code>SMALL_ICON</code> or 
   * <code>LARGE_ICON</code>.
   * This image is suitable for display in a widget that
   * can call this <code>Command</code>, such as a toolbar or menu.
   */
  public Image getIcon (String cmdKey, String key);


  /**
   * Returns the state for the command. If the key has no
   * state (only performs an action), this method should
   * return <code>null</code>. If the key has an on/off
   * state, i.e., it can be "chosen", then this method
   * should return <code>Boolean.TRUE</code> or <code>
   * Boolean.FALSE</code>.
   */
  public Boolean getState(String cmdKey);

  /**
   * Returns true is the command is executed without user interaction and
   * false otherwise.
   */
  public boolean isImmediate(String cmdKey);
}





