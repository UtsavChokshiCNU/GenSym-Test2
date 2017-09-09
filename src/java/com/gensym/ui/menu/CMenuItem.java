/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CMenuItem.java
 *
 */

package com.gensym.ui.menu;

import javax.swing.JMenuItem;
import javax.swing.ImageIcon;
import javax.swing.Icon;
import javax.swing.KeyStroke;
import java.awt.Image;
import java.awt.event.ActionListener;
import com.gensym.ui.Command;
import com.gensym.ui.KeyableCommand;
import com.gensym.ui.RepresentationConstraints;

/* CMenuItems are created by adding Commands to a CMenu.
 * A CMenuItem has a unique key that is used as the actionCommand property
 * of the ActionEvent dispatched on selection.
 */
class CMenuItem extends JMenuItem{
  private String key;
  private CMenuCommandAdapter cmdAdapter;

  CMenuItem(Command command, String cmdKey, CMenuCommandAdapter cmdAdapter,
	    RepresentationConstraints constraints, Character mnemonic, KeyStroke shortcut){
    super();
    int type = constraints.getRepresentationType();
    if ((type == constraints.TEXT_ONLY) || (type == constraints.TEXT_AND_ICON)){
      if (command.isImmediate(cmdKey))
	setText(command.getDescription(cmdKey, Command.SHORT_DESCRIPTION));
      else
	setText(command.getDescription(cmdKey, Command.SHORT_DESCRIPTION)+"...");
    }
    if ((type == constraints.ICON_ONLY) || (type == constraints.TEXT_AND_ICON)) {
      Image icon = command.getIcon(cmdKey, Command.SMALL_ICON);
      if (icon != null){
	ImageIcon img = new ImageIcon(icon);
	this.setIcon(img);
      }
      else
	this.setIcon(CMenu.defaultIcon);
    }

    setHorizontalAlignment(constraints.getHorizontalAlignment());
    setVerticalAlignment(constraints.getVerticalAlignment());
    setHorizontalTextPosition(constraints.getHorizontalTextPosition());
    setVerticalTextPosition(constraints.getVerticalTextPosition());

    this.key = cmdKey;
    this.cmdAdapter = cmdAdapter;
    cmdAdapter.add(this);
    this.addActionListener(command);

    if (!command.isAvailable(key)){
    	this.setEnabled(false);
    }
    if (mnemonic != null){
      if (getText().indexOf(mnemonic.charValue()) == -1)
	setText(getText()+" ("+mnemonic+")");
      setMnemonic(mnemonic.charValue());
    }
    //shortcut can be null
    setAccelerator(shortcut);
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


