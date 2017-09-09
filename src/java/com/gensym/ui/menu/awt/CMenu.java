/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CMenu.java
 *
 */

package com.gensym.ui.menu.awt;

import java.awt.Menu;
import java.awt.MenuItem;
import java.awt.event.ActionListener;
import java.util.Vector;
import com.gensym.ui.Command;
import com.gensym.ui.SubCommand;
import com.gensym.ui.StructuredCommand;
import com.gensym.ui.CommandUtilities;
import com.gensym.message.Resource;

/**
 * CMenu is a "command-aware" menu container. It provides API for adding Commands.
 *<p>
 * In general, when a Command is added to a CMenu, the CMenu:
 * <LI>Creates and adds a menu item for each command key.  A command with state 
 * generates a checkbox menu item. 
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
 */

public class CMenu extends Menu{
  private static Resource i18n = Resource.getBundle("com/gensym/ui/menu/awt/Errors");
  private String key;
  private CMenuCommandAdapter cmdAdapter;

  /**
   * Creates a CMenu with the specified label.
   */
  public CMenu (String label){
    super(label);
  }

  /*
   * Creates a CMenu whose label is the short description of command.
   * The CMenu is disabled if command is unavailable.  cmdAdapter is
   * a CommandListener of command.
   */
  CMenu(Command command, String cmdKey, CMenuCommandAdapter cmdAdapter){
    super(command.getDescription(cmdKey, Command.SHORT_DESCRIPTION));
    key = cmdKey;
    this.cmdAdapter = cmdAdapter;
    cmdAdapter.add(this);
    if (!command.isAvailable(cmdKey)) setEnabled(false);
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
  public final void add(Command cmd){
    if (cmd == null) 
      throw new IllegalArgumentException(i18n.getString("CommandCanNotBeNull"));
    CMenuCommandAdapter cmdAdapter = new CMenuCommandAdapter(cmd, this, true);
    add(cmd, cmdAdapter);
  }

  void add(Command cmd, CMenuCommandAdapter cmdAdapter){
    if (cmd instanceof StructuredCommand){
      Vector structuredKeys = ((StructuredCommand)cmd).getStructuredKeys();
      createMenu(this, structuredKeys, cmd, cmdAdapter, false);
    }
    else{
      String[] keys = cmd.getKeys();
      if (!(keys == null))
	for (int i=0; i<keys.length; i++)
	  add(cmd, keys[i], cmdAdapter);
    }
  }

  /**
   * Adds a menu item for the specified cmdKey.  The short description of the
   * command is used for the label of the menu item.  If the command has state,
   * then a checkbox menu item is generated.  If the command is a StructuredCommand
   * and the cmdKey represents a SubCommand, then a sub-menu is added.
   * Single actions of StructuredCommands
   * will ignore to STRUCTURE_CHANGED CommandEvents.
   *
   * @see com.gensym.ui.Command#getDescription
   */
  public final void add(Command cmd, String cmdKey){
    if (cmd == null) 
      throw new IllegalArgumentException(i18n.getString("CommandCanNotBeNull"));
    CMenuCommandAdapter cmdAdapter = new CMenuCommandAdapter(cmd, this, false);
    if (cmd instanceof StructuredCommand){
      Object commandElement = 
	CommandUtilities.getElementForKey((StructuredCommand)cmd, cmdKey);
      if (commandElement instanceof String){
	add(cmd, cmdKey, cmdAdapter);
      }
      else if (commandElement instanceof SubCommand){
	SubCommand subCommand = (SubCommand)commandElement;
	String subCmdKey = subCommand.getKey();
	CMenu newMenu = new CMenu(cmd, subCmdKey, cmdAdapter);
	add(newMenu);
	createMenu(newMenu, subCommand.getStructure(), cmd, cmdAdapter, false);	
      }
      //else throw exception??
    }
    else
      add(cmd, cmdKey, cmdAdapter);
  }

  void add(Command cmd, String cmdKey, CMenuCommandAdapter cmdAdapter){
    Object state = cmd.getState(cmdKey);
    if (state == null)
      add(new CMenuItem(cmd, cmdKey, cmdAdapter));
    else
      add(new CCheckboxMenuItem(cmd, cmdKey, cmdAdapter, 
				((Boolean)state).booleanValue()));
  }


  void createMenu(CMenu menu, Vector structure, Command cmd,
			  CMenuCommandAdapter cmdAdapter, boolean addSeparator){
    if (structure == null) return;
    if (addSeparator) {
      menu.addSeparator();
    }
    for (int i=0; i<structure.size(); i++){
      Object element = structure.elementAt(i);
      if (element instanceof String){
	menu.add(cmd, (String)element, cmdAdapter);
      }
      else if (element instanceof Vector){
	if ((!addSeparator)&&(i == 0))
	  createMenu(menu, (Vector)element, cmd, cmdAdapter, false);
	else createMenu(menu, (Vector)element, cmd, cmdAdapter, true);
      }
      else if (element instanceof SubCommand){
	SubCommand subCommand = (SubCommand)element;
	String subCmdKey = subCommand.getKey();
	CMenu newMenu = new CMenu(cmd, subCmdKey, cmdAdapter);
	menu.add(newMenu);
	createMenu(newMenu, subCommand.getStructure(), cmd, cmdAdapter, false);
      }
    }
  }      

  String getKey(){
    return key;
  }
 
  CMenuCommandAdapter getCommandAdapter(){
    return cmdAdapter;
  }

}
