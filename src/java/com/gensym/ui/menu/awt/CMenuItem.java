/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CMenuItem.java
 *
 */

package com.gensym.ui.menu.awt;

import java.awt.MenuItem;
import java.awt.event.ActionListener;
import com.gensym.ui.Command;

/** CMenuItems are typically created by adding Commands to a CMenu.  
 *  A CMenuItem has a unique key that is used as the actionCommand property
 *  of the ActionEvent dispatched on selection.  CMenuItems
 *  support cloning.
 */
class CMenuItem extends MenuItem {
  private String key;
  private CMenuCommandAdapter cmdAdapter;

  public CMenuItem(String label){
    super(label);
  }

  CMenuItem(Command command, String cmdKey, CMenuCommandAdapter cmdAdapter){
    super();
    if (command.isImmediate(cmdKey))
      setLabel(command.getDescription(cmdKey, Command.SHORT_DESCRIPTION));
    else
      setLabel(command.getDescription(cmdKey, Command.SHORT_DESCRIPTION)+"...");
    this.key = cmdKey;
    this.cmdAdapter = cmdAdapter;
    cmdAdapter.add(this);
    this.addActionListener(command);
    if (!command.isAvailable(key)) this.setEnabled(false);
  }

  @Override
  public String getActionCommand(){
    return this.key;
  }

  /** Returns the key of the menu item */
  public String getKey(){
    return key;
  }

  CMenuCommandAdapter getCommandAdapter(){
    return cmdAdapter;
  }
}
