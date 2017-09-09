/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CMenuCommandAdapter.java
 *
 */

package com.gensym.ui.menu.awt;

import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;
import java.awt.Menu;
import java.awt.MenuContainer;
import java.awt.MenuItem;
import java.awt.MenuComponent;
import com.gensym.ui.Command;
import com.gensym.ui.StructuredCommandListener;
import com.gensym.ui.StructuredCommand;
import com.gensym.ui.CommandEvent;


/* This class is an adapter between Commands and CMenuItems. */
class CMenuCommandAdapter implements StructuredCommandListener{
  private Command command;
  protected Hashtable menuItems;
  private MenuComponent parent;
  private boolean entireCommandAdded;

  CMenuCommandAdapter(Command cmd, MenuComponent parent, boolean entireCommandAdded){
    this.command = cmd;
    menuItems = new Hashtable();
    this.entireCommandAdded = entireCommandAdded;
    this.parent = parent;
    if (cmd instanceof StructuredCommand)
      ((StructuredCommand)cmd).addStructuredCommandListener(this);
    else
      cmd.addCommandListener(this);
  }

  void add(CMenu menu){
    menuItems.put(menu.getKey(), menu);
  }

  void add(CMenuItem mi){
    menuItems.put(mi.getKey(), mi);
  }

  void add(CCheckboxMenuItem mi){
    menuItems.put(mi.getKey(), mi);
  }

  Command getCommand(){
    return command;
  }

  @Override
  public void commandAvailabilityChanged(CommandEvent e){
    String key = e.getKey();
    Command command = (Command)e.getSource();
    boolean available = command.isAvailable(key);
    MenuItem mi = (MenuItem)menuItems.get(key);
    if (mi != null)  mi.setEnabled(available);
  }

  @Override
  public void commandStateChanged(CommandEvent e){
    String key = e.getKey();
    Command command = (Command)e.getSource();
    boolean state = ((Boolean)command.getState(key)).booleanValue();
    MenuItem mi = (MenuItem)menuItems.get(key);
    if (mi instanceof CCheckboxMenuItem) ((CCheckboxMenuItem)mi).setState(state);
  }

  @Override
  public void commandDescriptionChanged(CommandEvent e){
    String key = e.getKey();
    Command command = (Command)e.getSource();
    String label = command.getDescription(key, Command.SHORT_DESCRIPTION);
    MenuItem mi = (MenuItem)menuItems.get(key);
    if (mi != null){
      if (command.isImmediate(key))
	mi.setLabel(label);
      else
	mi.setLabel(label+"...");
    }
  }

  @Override
  public void commandIconChanged(CommandEvent e){}

  @Override
  public synchronized void commandStructureChanged(CommandEvent e){
    if (!entireCommandAdded) return; //exception??
    if (parent instanceof CMenu)
      doStructureChangedForMenu((Menu)parent, (Command)e.getSource());
    else if (parent instanceof CMenuBar)
      doStructureChangedForCMenuBar((CMenuBar)parent, (Command)e.getSource());
    else 
      doStructureChangedForMenu((Menu)parent, (Command)e.getSource());
  }

  private void doStructureChangedForMenu(Menu parentMenu, Command command){
    int count = parentMenu.getItemCount();
    //pop menu items
    MenuItem mi;
    Vector poppedList = new Vector();
    boolean found = false;
    //found means entered group
    boolean previousItemWasSeparator = false;
    for (int i=count-1; i>=0; i--){
      mi = parentMenu.getItem(i);
      parentMenu.remove(i);
      if (mi.getLabel().equals("-")){
	previousItemWasSeparator = true;
	if (!found) poppedList.addElement(mi);
      }
      else{
	boolean contained = menuItems.contains(mi);
	//contained means still in group
	if ((!found)&&(!contained)) poppedList.addElement(mi);
	else if ((!found)&&(contained)){
	  found = true;
	  menuItems.remove(mi);
	  mi.removeActionListener(command);
	}
	else if ((found)&&(!contained)){
	  parentMenu.add(mi);
	  if (previousItemWasSeparator) parentMenu.addSeparator();
	  break;
	}
	else{
	  menuItems.remove(mi);
	  mi.removeActionListener(command);
	}
	previousItemWasSeparator = false;
      }
    }	 
    //build new menu
    if (parentMenu instanceof CMenu)
      ((CMenu)parentMenu).add(command, this);
    else
      ((CPopupMenu)parentMenu).add(command, this);
    //push menu items
    int size = poppedList.size();
    for (int i=size-1; i>=0; i--)
      parentMenu.add((MenuItem)poppedList.elementAt(i));
  }

  private void doStructureChangedForCMenuBar(CMenuBar menuBar, Command command){
    int count = menuBar.getMenuCount();
    //pop menu items
    Vector poppedList = new Vector();
    boolean found = false;
    for (int i=count-1; i>=0; i--){
      Menu menu = menuBar.getMenu(i);
      menuBar.remove(i);
      //contained=is this a menuItem managed by this cmdAdapter?
      //found=was the first menuItem in the group found?
      boolean contained = menuItems.contains(menu);
      if ((!found)&&(!contained)) 
	poppedList.addElement(menu);
      else if ((!found)&&(contained)){//first menuItem in group found
	found = true;
	menuItems.remove(menu);
	menu.removeActionListener(command);
      }
      else if ((found)&&(!contained)){//left group
	menuBar.add(menu);
	break;
      }
      else{
	menuItems.remove(menu);//still in group  (found)&&(contained)
	menu.removeActionListener(command);
      }
    }	 
    //build new menu
    menuBar.add(command, this);
    //push menu items
    int size = poppedList.size();
    for (int i=size-1; i>=0; i--){
      menuBar.add((Menu)poppedList.elementAt(i));
    }
    //menuBar.validate();
  }


}






