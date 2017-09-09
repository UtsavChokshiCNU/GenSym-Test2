/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CMenuBar.java
 *
 */

package com.gensym.ui.menu;

import java.util.Hashtable;
import java.util.Vector;
import java.util.Enumeration;
import javax.swing.JMenuBar;
import com.gensym.ui.Command;
import com.gensym.ui.KeyInformation;
import com.gensym.ui.StructuredCommand;
import com.gensym.ui.SubCommand;
import com.gensym.ui.RepresentationConstraints;
import com.gensym.ui.CommandUtilities;
import com.gensym.message.Resource;

/** CMenuBar is a "command-aware" menu container. It provides API for adding Commands.
 * <p>
 * Typically, a StructuredCommand consisting of a single SubCommand is added to
 * a CMenuBar.  When the command is added to a CMenuBar, the CMenuBar:
 * <LI>Creates and adds a CMenu that represents the entire SubCommand. The generated
 * CMenu may contain menu items, checkbox menu items, or menus to represent the
 * structure of the SubCommand.
 * <LI>Applies the default or specified RepresentationConstraints
 * <LI>Ensures that the initial availability and state of the menu items is in sync
 * with the current availability and state of the command.
 * <LI>Registers the Command as an ActionListener with each menu item and registers
 * a CommandListener with the Command to respond appropriately to changes in the
 * Command.
 *</p><p>
 * The actionCommand of the ActionEvent dispatched from the generated menu items
 * is the command key.
 *</p>
 * @see com.gensym.ui.CMenu
 * @see com.gensym.ui.StructuredCommand
 * @see com.gensym.ui.SubCommand
 * @see com.gensym.ui.RepresentationConstraints
 */
public class CMenuBar extends JMenuBar {
  private static final RepresentationConstraints defaultConstraints =
    new RepresentationConstraints(RepresentationConstraints.LEFT,
				  RepresentationConstraints.CENTER,
				  RepresentationConstraints.RIGHT,
				  RepresentationConstraints.CENTER);
  private static Resource i18n = Resource.getBundle("com/gensym/ui/menu/Errors");

  private Hashtable commandToAdapterTable;

  public CMenuBar(){
  }

  /**
   * Adds menus and menu items to represent the command.  Typically, a
   * StruturedCommand consisting of a single SubCommand is added. The short
   * description of the Command is used for the label of the menu or menu items.
   *
   * @see com.gensym.ui.Command#getDescription
   */
  public void add(Command cmd){
    add(cmd, defaultConstraints);
  }

  /**
   * Adds the command and applies the specified constraints for representing
   * the command. If specified in the constraints, the short description of the
   * Command is used for the menu or menu item's label and the small icon of the
   * Command is used for the menu or menu item's icon.
   *
   * @see com.gensym.ui.Command#getDescription
   * @see com.gensym.ui.Command#getIcon
   */
  public void add(Command cmd, RepresentationConstraints constraints){
    if (cmd == null)
      throw new IllegalArgumentException(i18n.getString("CommandCanNotBeNull"));
    CMenuCommandAdapter cmdAdapter =
      new CMenuCommandAdapter(cmd, constraints, null, this, true);
    updateTable(cmd, cmdAdapter);
    add(cmd, cmdAdapter, constraints, null);
  }

  void add(Command cmd, CMenuCommandAdapter cmdAdapter,
	   RepresentationConstraints constraints, KeyInformation[] mnemonicAndShortcutOverrides){
    if (cmd instanceof StructuredCommand){
      KeyMap mnemonicMap = new KeyMap(CMenu.NULL_MARKER);
      KeyMap shortcutMap = new KeyMap(CMenu.NULL_MARKER);
      CMenu.fillKeyMaps(mnemonicMap, shortcutMap, mnemonicAndShortcutOverrides);
      Vector structuredKeys = ((StructuredCommand)cmd).getStructuredKeys();
      createMenu(this, structuredKeys, cmd, cmdAdapter, constraints, mnemonicMap, shortcutMap);
    }
    else{
      throw new IllegalArgumentException(i18n.getString("CanOnlyAddSubCommands"));
    }
  }

  /**
   * Adds menus and menu items to represent the command.
   * Typically, the cmdKey represents a SubCommand. The short
   * description of the Command is used for the label of the menu or menu items.
   * SubCommands added with this method will ignore STRUCTURE_CHANGED CommandEvents.
   * @see com.gensym.ui.Command#getDescription
   */
  public void add(Command cmd, String cmdKey){
    add(cmd, cmdKey, defaultConstraints);
  }

  /**
   * Adds menus and menu items to represent the command.
   * Typically, the cmdKey represents a SubCommand. If specified in the
   * RepresentationConstraints, the short description of the Command is
   * used for the label of the menu or menu items.  If specified in the
   * RepresentationConstraints, the small icon of the Command is used the
   * icon of the menu item.
   * SubCommands added with this method will ignore STRUCTURE_CHANGED CommandEvents.
   *
   * @see com.gensym.ui.Command#getDescription
   */
  public void add(Command cmd, String cmdKey, RepresentationConstraints constraints){
    add(cmd, cmdKey, constraints, null);
  }

  public void add(Command cmd, String cmdKey, RepresentationConstraints constraints,
		  KeyInformation[] mnemonicAndShortcutOverrides){
    if (cmd == null)
      throw new IllegalArgumentException(i18n.getString("CommandCanNotBeNull"));
    CMenuCommandAdapter cmdAdapter = new CMenuCommandAdapter(cmd, constraints, mnemonicAndShortcutOverrides,
							     this, false);
    updateTable(cmd, cmdAdapter);
   if (cmdKey == null)
     add(cmd, cmdAdapter, constraints, mnemonicAndShortcutOverrides);
   else{
     KeyMap mnemonicMap = new KeyMap(CMenu.NULL_MARKER);
     KeyMap shortcutMap = new KeyMap(CMenu.NULL_MARKER);
     CMenu.fillKeyMaps(mnemonicMap, shortcutMap, mnemonicAndShortcutOverrides);
     if (cmd instanceof StructuredCommand){
       Object commandElement =
	 CommandUtilities.getElementForKey((StructuredCommand)cmd, cmdKey);
       if (commandElement instanceof String){
	 throw new IllegalArgumentException(i18n.getString("CanOnlyAddSubCommands"));
       }
       else if (commandElement instanceof SubCommand){
         SubCommand subCommand = (SubCommand)commandElement;
         addSubCommandMenu(subCommand, cmd, cmdAdapter, constraints, mnemonicMap, shortcutMap);
       }
     }
     else
       throw new IllegalArgumentException(i18n.getString("CanOnlyAddSubCommands"));
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


  private void createMenu(CMenuBar menuBar, Vector structure, Command cmd,
			  CMenuCommandAdapter cmdAdapter,
			  RepresentationConstraints constraints,
			  KeyMap mnemonicMap, KeyMap shortcutMap){
    if (structure == null){
    	return;
    }
    for (int i=0; i<structure.size(); i++){
      Object element = structure.elementAt(i);
      if (element instanceof String){
	throw new IllegalArgumentException(i18n.getString("CanOnlyAddSubCommands"));
      }
      else if (element instanceof Vector)
	createMenu(menuBar, (Vector)element, cmd, cmdAdapter, constraints, mnemonicMap, shortcutMap);
      else if (element instanceof SubCommand){
        addSubCommandMenu((SubCommand)element, cmd, cmdAdapter, constraints, mnemonicMap, shortcutMap);
      }
    }
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
    CMenu newMenu = createSubMenu(cmd, subCommandElement.getKey(), cmdAdapter, constraints, CMenu.getMnemonic(cmd, subCommandElement.getKey(), mnemonicMap));
    boolean addSeparator = (newMenu.getItemCount() > 0);
    newMenu.createMenu(newMenu, subCommandElement.getStructure(), cmd, cmdAdapter,
                      addSeparator, constraints, mnemonicMap, shortcutMap);
  }

  /**
   * @undocumented
   */
  protected CMenu createSubMenu(Command command, String cmdKey,
        CMenuCommandAdapter cmdAdapter,	RepresentationConstraints constraints,
        Character mnemonic)
  {
    CMenu newMenu = newSubMenu(command, cmdKey, cmdAdapter, constraints, mnemonic);
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
}



