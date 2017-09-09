/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CPopupMenu.java
 *
 */

package com.gensym.ui.menu;

import java.util.Hashtable;
import java.util.Vector;
import java.util.Enumeration;
import javax.swing.JMenuItem;
import javax.swing.JPopupMenu;
import com.gensym.ui.Command;
import com.gensym.ui.CommandEvent;
import com.gensym.ui.KeyInformation;
import com.gensym.ui.StructuredCommand;
import com.gensym.ui.SubCommand;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.CommandUtilities;
import com.gensym.message.Resource;

/**
 * CPopupMenu is a "command-aware" menu container. It provides API for adding
 * Commands.
 *<p>
 * In general, when a Command is added to a CPopupMenu, the CPopupMenu:
 * <LI>Creates and adds a menu item for each command key.  A command with state
 * generates a checkbox menu item.
 * <LI>Applies the default or specified RepresentationConstraints
 * <LI>Ensures that the initial availability and state of the menu item is in sync
 * with the current availability and state of the command.
 * <LI>Registers the Command as an ActionListener with each menu item and registers
 * a CommandListener with the Command to respond appropriately to changes in the
 * Command.
 *</p><p>
 * The actionCommand of the ActionEvent dispatched from the generated menu items
 * is the command key.
 *</p>
 * @see com.gensym.ui.Command
 * @see com.gensym.ui.StructuredCommand
 * @see com.gensym.ui.RepresentationConstraints
 */

public class CPopupMenu extends JPopupMenu{
  private static final RepresentationConstraints defaultConstraints =
    new RepresentationConstraints(RepresentationConstraints.LEFT,
				  RepresentationConstraints.CENTER,
				  RepresentationConstraints.RIGHT,
				  RepresentationConstraints.CENTER);
  private static Resource i18n = Resource.getBundle("com/gensym/ui/menu/Errors");
  private CMenuCommandAdapter cmdAdapter;
  private boolean topLevelSubMenusNormalized = false;

  private Hashtable commandToAdapterTable;

  public CPopupMenu () {
    super ();
  }


  public CPopupMenu (String title) {
    super (title);
  }

  /**
   * Adds menu items for each command key in cmd. The short description of the
   * command is used as the label for the menu item.  If the command is a
   * StructuredCommand, then the hierachical structure of the command is represented
   * via submenus and groupings are separated by separators.  Commands with state
   * are represented by checkbox menu items.
   *
   * @see com.gensym.ui.Command#getDescription
   */
  public void add(Command cmd){
    add(cmd, defaultConstraints);
  }


  /**
   * Adds the command and applies the specified constraints to each generated menu
   * item. If specified in the constraints, the short description of the Command
   * is used for the menu item's label and the small icon of the Command is used
   * for the menu item's icon.
   *
   * @see com.gensym.ui.Command#getDescription
   * @see com.gensym.ui.Command#getIcon
   */
  public void add(Command cmd, RepresentationConstraints constraints){
    if (cmd == null)
      throw new IllegalArgumentException(i18n.getString("CommandCanNotBeNull"));
    CMenuCommandAdapter menuCmdAdapter = new CMenuCommandAdapter(cmd, constraints, null, this, true);
    updateTable(cmd, menuCmdAdapter);
    add(cmd, menuCmdAdapter, constraints, null);
  }

  void add(Command cmd, CMenuCommandAdapter cmdAdapter,
	   RepresentationConstraints constraints, KeyInformation[] mnemonicAndShortcutOverrides){
    KeyMap mnemonicMap = new KeyMap(CMenu.NULL_MARKER);
    KeyMap shortcutMap = new KeyMap(CMenu.NULL_MARKER);
    CMenu.fillKeyMaps(mnemonicMap, shortcutMap, mnemonicAndShortcutOverrides);
    if (cmd instanceof StructuredCommand){
      Vector structuredKeys = ((StructuredCommand)cmd).getStructuredKeys();
      createMenu(this, structuredKeys, cmd, cmdAdapter, false, constraints, mnemonicMap, shortcutMap, true);
    }
    else{
      String[] keys = cmd.getKeys();
      if (!(keys == null))
	for (int i=0; i<keys.length; i++)
	  add(cmd, keys[i], cmdAdapter, constraints, mnemonicMap, shortcutMap);
    }
  }

  /**
   * Adds a menu item for a single action of the command, or, in the case of a
   * StructuredCommand, it may add a single sub-menu.  The short description of the
   * command is used for the label of the menu item or menu. If the command has state,
   * then a checkbox menu item is generated.
   *
   * @see com.gensym.ui.Command#getDescription
   */
  public void add(Command cmd, String cmdKey){
    add(cmd, cmdKey, defaultConstraints);
  }


  /**
   * Adds a menu item for a single action of the command, or, in the case of a
   * StructuredCommand, it may add a single sub-menu.
   * If specified in the constraints, the short description of the
   * Command is used for the menu item's label and the small icon of the Command is
   * used for the menu item's icon.
   *
   * @see com.gensym.ui.Command#getDescription
   * @see com.gensym.ui.Command#getIcon
   */
  public void add(Command cmd, String cmdKey, RepresentationConstraints constraints){
    add(cmd, cmdKey, constraints, null);
  }

  public void add(Command cmd, String cmdKey, RepresentationConstraints constraints,
		  KeyInformation[] mnemonicAndShortcutOverrides){
    if (cmd == null)
      throw new IllegalArgumentException(i18n.getString("CommandCanNotBeNull"));
    CMenuCommandAdapter menuCmdAdapter = new CMenuCommandAdapter(cmd, constraints, mnemonicAndShortcutOverrides,
							     this, false);
    updateTable(cmd, menuCmdAdapter);
    if (cmdKey == null)
      add(cmd, menuCmdAdapter, constraints, mnemonicAndShortcutOverrides);
    else{
      KeyMap mnemonicMap = new KeyMap(CMenu.NULL_MARKER);
      KeyMap shortcutMap = new KeyMap(CMenu.NULL_MARKER);
      CMenu.fillKeyMaps(mnemonicMap, shortcutMap, mnemonicAndShortcutOverrides);
      if (cmd instanceof StructuredCommand){
	Object commandElement =
	  CommandUtilities.getElementForKey((StructuredCommand)cmd, cmdKey);
	if (commandElement instanceof String){
	  add(cmd, cmdKey, menuCmdAdapter, constraints, mnemonicMap, shortcutMap);
	}
	else if (commandElement instanceof SubCommand){
	  SubCommand subCommand = (SubCommand)commandElement;
          addSubCommandMenu(subCommand, cmd, menuCmdAdapter, constraints, mnemonicMap, shortcutMap);
	}
      }
      else
	add(cmd, cmdKey, menuCmdAdapter, constraints, mnemonicMap, shortcutMap);
    }
  }

  private void updateTable(Command cmd, CMenuCommandAdapter cmdAdapter){
    if (commandToAdapterTable == null)
      commandToAdapterTable = new Hashtable();
    Vector adapters = (Vector)commandToAdapterTable.get(cmd);
    if (adapters == null){
      adapters = new Vector(1); //adding a command to a menu more than once should be rare
      commandToAdapterTable.put(cmd, adapters);
    }
    adapters.addElement(cmdAdapter);
  }

  private void add(Command cmd, String cmdKey, CMenuCommandAdapter cmdAdapter,
		   RepresentationConstraints constraints, KeyMap mnemonicMap, KeyMap shortcutMap){
    add(cmd, false, cmdKey, cmdAdapter, constraints, null, null);
  }

  private JMenuItem add(Command cmd, boolean isSubMenu, String cmdKey, CMenuCommandAdapter cmdAdapter,
			   RepresentationConstraints constraints, KeyMap mnemonicMap, KeyMap shortcutMap){
   if (isSubMenu)
      return add(newSubMenu(cmd, cmdKey, cmdAdapter, constraints,
			   CMenu.getMnemonic(cmd, cmdKey, mnemonicMap)));
    else{
      Object state = cmd.getState(cmdKey);
      if (state == null)
	return add(new CMenuItem(cmd, cmdKey, cmdAdapter, constraints,
				 CMenu.getMnemonic(cmd, cmdKey, mnemonicMap),
				 CMenu.getShortcut(cmd, cmdKey, shortcutMap)));
      else
	return add(new CCheckboxMenuItem(cmd, cmdKey, cmdAdapter,
				  ((Boolean)state).booleanValue(), constraints,
					 CMenu.getMnemonic(cmd, cmdKey, mnemonicMap),
					 CMenu.getShortcut(cmd, cmdKey, shortcutMap)));
    }
  }

  private void createMenu(CPopupMenu menu, Vector structure, Command cmd,
			  CMenuCommandAdapter cmdAdapter, boolean addSeparator,
			  RepresentationConstraints constraints,
			  KeyMap mnemonicMap, KeyMap shortcutMap, boolean topLevel){
    if (structure == null){
    	return;
    }
    if (addSeparator) {
      menu.addSeparator();
    }
    for (int i=0; i<structure.size(); i++){
      Object element = structure.elementAt(i);
      if (element instanceof String){
	menu.add(cmd, (String)element, cmdAdapter, constraints, mnemonicMap, shortcutMap);
      }
      else if (element instanceof Vector){
	if ((!addSeparator)&&(i == 0))
	  createMenu(menu, (Vector)element, cmd, cmdAdapter, false, constraints, mnemonicMap, shortcutMap, topLevel);
	else createMenu(menu, (Vector)element, cmd, cmdAdapter, true, constraints, mnemonicMap, shortcutMap, topLevel);
      }
      else if (element instanceof SubCommand){
	SubCommand subCommand = (SubCommand)element;
        if (topLevel && topLevelSubMenusNormalized)
          createMenu(menu, subCommand.getStructure(), cmd, cmdAdapter, addSeparator, constraints, mnemonicMap, shortcutMap, false);
        else
          addSubCommandMenu(subCommand, cmd, cmdAdapter, constraints, mnemonicMap, shortcutMap);
      }
    }
  }

  CMenuCommandAdapter getCommandAdapter(){
    return cmdAdapter;
  }

  /**
   * @undocumented
   */
  protected void addSubCommandMenu(SubCommand subCommandElement,
                          Command cmd,
			  CMenuCommandAdapter cmdAdapter,
			  RepresentationConstraints constraints,
			  KeyMap mnemonicMap, KeyMap shortcutMap)
  {
    CMenu newMenu = createSubMenu(cmd, subCommandElement.getKey(), cmdAdapter,
                                         constraints, mnemonicMap, shortcutMap);
    boolean addSeparator = (newMenu.getItemCount() > 0);
    newMenu.createMenu(newMenu, subCommandElement.getStructure(), cmd, cmdAdapter,
                      addSeparator, constraints, mnemonicMap, shortcutMap);
  }

  /**
   * @undocumented
   */
  protected CMenu createSubMenu(Command command, String cmdKey,
        CMenuCommandAdapter cmdAdapter,	RepresentationConstraints constraints,
        KeyMap mnemonicMap, KeyMap shortcutMap)
  {
    CMenu newMenu = (CMenu)add(command, true, cmdKey, cmdAdapter, constraints, mnemonicMap, shortcutMap);
    add(newMenu);
    return newMenu;
  }

  /**
   * @undocumented
   */
  protected CMenu newSubMenu(Command cmd, String cmdKey, CMenuCommandAdapter cmdAdapter,
    RepresentationConstraints constraints, Character mnemonic)
  {
    return new CMenu(cmd, cmdKey, cmdAdapter, constraints, mnemonic);
  }

  public final void remove(Command cmd){
    remove(cmd, null);
  }

  public final void remove(Command cmd, String cmdKey){
    if (commandToAdapterTable == null)
      return;
    Vector adapters = (Vector)commandToAdapterTable.get(cmd);
    if (adapters != null){
      for (int i=adapters.size()-1; i>=0; i--){
	CMenuCommandAdapter adapter = (CMenuCommandAdapter)adapters.elementAt(i);
	boolean removed = adapter.remove(cmdKey);
	if (removed)
	  adapters.removeElement(adapter);
      }
      if (adapters.isEmpty())
	commandToAdapterTable.remove(cmd);
    }
  }

  @Override
  public final void removeAll()
  {
    if (commandToAdapterTable != null) {
      Enumeration e = commandToAdapterTable.keys();
      while (e.hasMoreElements()) {
        Command cmd = (Command)e.nextElement();
        remove(cmd);
      }
    }
  }

/**
 * Returns whether the top level sub menu's are normalized within this popup menu.
 * @see setTopLevelSubMenusNormalized
 */
  public boolean isTopLevelSubMenusNormalized()
  {
    return topLevelSubMenusNormalized;
  }

/**
 * Sets whether the top level sub menus are normalized within this popup menu.
 * If this is false (as it is by default), commands that are added which have a
 * 'MenuBar friendly' structure will appear in the menu in a similar fashion to
 * they would in the MenuBar.
 *
 * e.g for a Command structure with two major groups File and Edit, and sub-items
 * File|Open, File|Save, Edit|Cut, Edit|Copy they would appear like this:
 *
 *   +-------+
 *   |File > +-----+
 *   |Edit > |Cut  |
 *   +-------|Copy |
 *           +-----+  (with Edit selected)
 *
 * If TopLevelSubMenusNormalized is set to true, the top level groupings are
 * ignored and the example structure would look like this:
 *
 *   +-------+
 *   |Open   |
 *   |Save   |
 *   |-------|
 *   |Cut    |
 *   |Copy   |
 *   +-------+
 *
 * However, Further sub menu structure would still be preserved.
 */
  public void setTopLevelSubMenusNormalized(boolean newValue)
  {
    if (newValue != topLevelSubMenusNormalized) {
      topLevelSubMenusNormalized = newValue;
      if (commandToAdapterTable != null) {
        // rebuild the menu
        Enumeration e = commandToAdapterTable.elements();
        while (e.hasMoreElements()) {
          CMenuCommandAdapter adapter = (CMenuCommandAdapter)e.nextElement();
          if (adapter != null)
            adapter.commandStructureChanged(new CommandEvent(adapter.getCommand(), 0, ""));
        }
      }
    }
  }

  /** workaround to Swing bug: 4189244: Swing Popup menu is not being refreshed
   * (cleared) under a Dialog
   * http://developer.java.sun.com/developer/bugParade/bugs/4189244.html
   *
   * repaints the first JComponent it finds when the menu hidden
   */
  @Override
  public void setVisible(boolean vis) {
    super.setVisible(vis);
    if (!vis) {
      java.awt.Component c = getInvoker();
      if (c instanceof javax.swing.JComponent) {
	java.awt.Container parent = (java.awt.Container) c;
	while (!(parent instanceof javax.swing.JComponent)) {
	  c = parent;
	  parent = c.getParent();
	}
	javax.swing.JComponent jc = (javax.swing.JComponent)c;
	jc.paintImmediately(0, 0, jc.getWidth(), jc.getHeight());
      }
    }
  }
}
