/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CCheckboxMenuItem.java
 *
 */

package com.gensym.ui.menu;
import javax.swing.JMenuItem;
import javax.swing.KeyStroke;
import javax.swing.ImageIcon;
import javax.swing.Icon;
import java.awt.Image;
import javax.swing.JCheckBoxMenuItem;
import java.awt.event.*;
import com.gensym.ui.Command;
import com.gensym.ui.KeyableCommand;
import com.gensym.ui.RepresentationConstraints;

/* CCheckboxMenuItems are created by adding Commands that have state to
 * a CMenu. A CCheckboxMenuItem has a unique key that is used as the actionCommand
 * property of the ActionEvent dispatched on selection.
 */
class CCheckboxMenuItem extends JCheckBoxMenuItem{
  private String key;
  private CMenuCommandAdapter cmdAdapter;

  CCheckboxMenuItem(Command command, String cmdKey,
		    CMenuCommandAdapter cmdAdapter,
		    RepresentationConstraints constraints, Character mnemonic, KeyStroke shortcut){
    this(command, cmdKey, cmdAdapter,
	 ((Boolean)command.getState(cmdKey)).booleanValue(), constraints, mnemonic, shortcut);
  }

  CCheckboxMenuItem(Command command, String cmdKey,
		    CMenuCommandAdapter cmdAdapter, boolean state,
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
    setState(state);
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

  /** Returns the key */
  public String getKey(){
    return key;
  }

  CMenuCommandAdapter getCommandAdapter(){
    return cmdAdapter;
  }

}



