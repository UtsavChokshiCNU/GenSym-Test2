/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CMenuBar.java
 *
 */

package com.gensym.ui.menu.awt;

import java.awt.MenuBar;
import java.util.Vector;
import com.gensym.ui.Command;
import com.gensym.ui.StructuredCommand;
import com.gensym.ui.SubCommand;
import com.gensym.ui.CommandUtilities;
import com.gensym.message.Resource;

/** 
 * CMenuBar is a "command-aware" menu container. It provides API for adding Commands.
 *<p>
 * Typically, a StructuredCommand consisting of a single SubCommand is added to 
 * a CMenuBar.  When the command is added to a CMenuBar, the CMenuBar:
 * <LI>Creates and adds a CMenu that represents the entire SubCommand. The generated
 * CMenu may contain menu items, checkbox menu items, or menus to represent the 
 * structure of the SubCommand.
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
 */
public class CMenuBar extends MenuBar  {
  private static Resource i18n = Resource.getBundle("com/gensym/ui/menu/awt/Errors"); 
  public CMenuBar () {
  }

  /**
   * Adds menus and menu items to represent the command.  Typically, a 
   * StruturedCommand consisting of a single SubCommand is added. The short
   * description of the Command is used for the label of the menu or menu items.
   *
   * @see com.gensym.ui.Command#getDescription
   */
  public void add(Command cmd){
    if (cmd == null) 
      throw new IllegalArgumentException(i18n.getString("CommandCanNotBeNull"));
    CMenuCommandAdapter cmdAdapter = new CMenuCommandAdapter(cmd, this, true);
    add(cmd, cmdAdapter);
  }

  void add(Command cmd, CMenuCommandAdapter cmdAdapter){
    if (cmd instanceof StructuredCommand){
      Vector structuredKeys = ((StructuredCommand)cmd).getStructuredKeys();
      createMenu(this, structuredKeys, cmd, cmdAdapter);
    }
    else throw new IllegalArgumentException(i18n.getString("CanOnlyAddSubCommands"));
  }

  /**
   * Adds a menu for the specified cmdKey.  The command should be a StructuredCommand
   * and the cmdKey should represent a SubCommand.  The short description of the
   * command is used for the label of the menu item(s). The menu created will
   * ignore STRUCTURE_CHANGED CommandEvents.
   *
   * @see com.gensym.ui.Command#getDescription
   */
  public void add(Command cmd, String cmdKey){
    if (cmd == null) 
      throw new IllegalArgumentException(i18n.getString("CommandCanNotBeNull"));
    CMenuCommandAdapter cmdAdapter = new CMenuCommandAdapter(cmd, this, false);
    if (cmd instanceof StructuredCommand){
      Object commandElement = 
	CommandUtilities.getElementForKey((StructuredCommand)cmd, cmdKey);
      if (commandElement instanceof String){
	throw new IllegalArgumentException(i18n.getString("CanOnlyAddSubCommands"));
      }
      else if (commandElement instanceof SubCommand){
	SubCommand subCommand = (SubCommand)commandElement;
	String subCmdKey = subCommand.getKey();
	CMenu newMenu = new CMenu(cmd, subCmdKey, cmdAdapter);
	add(newMenu);
	newMenu.createMenu(newMenu,subCommand.getStructure(), cmd, cmdAdapter,false);
      }
      else throw new IllegalArgumentException(i18n.getString("CanOnlyAddSubCommands"));
    }
    else throw new IllegalArgumentException(i18n.getString("CanOnlyAddSubCommands"));
  }

  private void createMenu(CMenuBar menuBar, Vector structure, Command cmd,
			  CMenuCommandAdapter cmdAdapter){
    if (structure == null) return;
    for (int i=0; i<structure.size(); i++){
      Object element = structure.elementAt(i);
      if (element instanceof String){
	throw new IllegalArgumentException(i18n.getString("CanOnlyAddSubCommands"));
      }
      else if (element instanceof Vector)
	createMenu(menuBar, (Vector)element, cmd, cmdAdapter);
      else if (element instanceof SubCommand){
	SubCommand subCommand = (SubCommand)element;
	String subCmdKey = subCommand.getKey();
	CMenu newMenu = new CMenu(cmd, subCmdKey, cmdAdapter);
	menuBar.add(newMenu);
	newMenu.createMenu(newMenu, subCommand.getStructure(), cmd, cmdAdapter, false);
      }
    }
  } 

}
