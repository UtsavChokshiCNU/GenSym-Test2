/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CMenuCommandAdapter.java
 *
 */

package com.gensym.ui.menu;

import java.util.Enumeration;
import java.util.Vector;
import java.util.Hashtable;
import java.awt.Component;
import java.awt.Container;
import java.awt.Image;
import javax.swing.JComponent;
import javax.swing.JMenuItem;
import javax.swing.ImageIcon;
import com.gensym.ui.Command;
import com.gensym.ui.CommandUtilities;
import com.gensym.ui.KeyInformation;
import com.gensym.ui.StructuredCommand;
import com.gensym.ui.StructuredCommandListener;
import com.gensym.ui.SubCommand;
import com.gensym.ui.CommandEvent;
import com.gensym.ui.RepresentationConstraints;


/* This class is an adapter between Commands and CMenuItems. */
public class CMenuCommandAdapter implements StructuredCommandListener{
  private Command command;
  private RepresentationConstraints constraints;
  private KeyInformation[] keyInfo;
  private Hashtable menuItemTable;
  private volatile JComponent parent;
  private boolean entireCommandAdded;

  CMenuCommandAdapter(Command cmd, RepresentationConstraints constraints, KeyInformation[] keyInfo,
		      JComponent parent, boolean entireCommandAdded){
    this.command = cmd;
    this.constraints = constraints;
    this.keyInfo = keyInfo;
    this.parent = parent;
    this.entireCommandAdded = entireCommandAdded;
    menuItemTable = new Hashtable();
    if (cmd instanceof StructuredCommand)
      ((StructuredCommand)cmd).addStructuredCommandListener(this);
    else
      cmd.addCommandListener(this);
  }

  void add(CMenu menu){
    menuItemTable.put(menu.getKey(), menu);
  }

  void add(CMenuItem mi){
    menuItemTable.put(mi.getKey(), mi);
  }

  void add(CCheckboxMenuItem mi){
    menuItemTable.put(mi.getKey(), mi);
  }


  Command getCommand(){
    return command;
  }

  @Override
  public void commandAvailabilityChanged(CommandEvent e){
    String key = e.getKey();
    Command cmd = (Command)e.getSource();
    boolean available = cmd.isAvailable(key);
    JMenuItem mi = (JMenuItem)menuItemTable.get(key);
    if (mi != null)
      mi.setEnabled(available);
  }

  @Override
  public void commandStateChanged(CommandEvent e){
    String key = e.getKey();
    Command cmd = (Command)e.getSource();
    boolean state = ((Boolean)cmd.getState(key)).booleanValue();
    JMenuItem mi = (JMenuItem)menuItemTable.get(key);
    if (mi instanceof CCheckboxMenuItem){
    	((CCheckboxMenuItem)mi).setState(state);
    }
  }

  @Override
  public void commandDescriptionChanged(CommandEvent e){
    int type = constraints.getRepresentationType();
    if ((type == constraints.TEXT_ONLY) || (type == constraints.TEXT_AND_ICON)){
      String key = e.getKey();
      Command cmd = (Command)e.getSource();
      String label = cmd.getDescription(key, Command.SHORT_DESCRIPTION);
      JMenuItem mi = (JMenuItem)menuItemTable.get(key);
      if (mi != null){
	if (cmd.isImmediate(key))
	  mi.setText(label);
	else
	  mi.setText(label+"...");
	mi.setMnemonic(mi.getMnemonic());
      }
    }
  }

  @Override
  public void commandIconChanged(CommandEvent e){
    int type = constraints.getRepresentationType();
    if ((type == constraints.ICON_ONLY) || (type == constraints.TEXT_AND_ICON)) {
      String key = e.getKey();
      Command cmd = (Command)e.getSource();
      Image icon = cmd.getIcon(key, Command.SMALL_ICON);
      if (icon != null){
	ImageIcon img = new ImageIcon(icon);
	JMenuItem mi = (JMenuItem)menuItemTable.get(key);
	if (mi != null){
		mi.setIcon(img);
	}
      }
    }
  }

  @Override
  public synchronized void commandStructureChanged(CommandEvent e){
    if (!entireCommandAdded){
    	return; //exception??
    }
    if (parent instanceof CMenu)
      doStructureChangedForCMenu((CMenu)parent, (Command)e.getSource());
    else if (parent instanceof CMenuBar)
      doStructureChangedForCMenuBar((CMenuBar)parent, (Command)e.getSource());
    else
      doStructureChangedForCPopupMenu((CPopupMenu)parent, (Command)e.getSource());
  }
  
  private void doStructureChangedForCMenu(CMenu parentMenu, Command command){
    int count = parentMenu.getMenuComponentCount();
    //pop menu items
    Vector poppedList = new Vector();
    boolean found = false;
    boolean previousItemWasSeparator = false;
    for (int i=count-1; i>=0; i--){
      java.awt.Component c = parentMenu.getMenuComponent(i);
      parentMenu.remove(i);
      if (c instanceof javax.swing.JSeparator){
	previousItemWasSeparator = true;
	if (!found){
		poppedList.addElement(c);
	}
      }
      else{
	JMenuItem mi = (JMenuItem)c;
	//contained=is this a menuItem managed by this cmdAdapter?
	//found=was the first menuItem in the group found?
	boolean contained = menuItemTable.contains(mi);
	if ((!found)&&(!contained)){
		poppedList.addElement(mi);
	}
	else if ((!found)&&(contained)){//first menuItem in group found
	  found = true;
	  menuItemTable.remove(mi);
	  mi.removeActionListener(command);
	}
	else if ((found)&&(!contained)){//left group
	  parentMenu.add(mi);
	  if (previousItemWasSeparator){
		  parentMenu.addSeparator();
	  }
	  break;
	}
	else{
	  menuItemTable.remove(mi);
	  mi.removeActionListener(command);
	}
	previousItemWasSeparator = false;
      }
    }	 
    //build new menu
    parentMenu.add(command, this, this.constraints, this.keyInfo);
    //push menu items
    int size = poppedList.size();
    for (int i=size-1; i>=0; i--){
      parentMenu.add((java.awt.Component)poppedList.elementAt(i));
    }
  }
  
  private void doStructureChangedForCMenuBar(CMenuBar menuBar, Command command){
    int count = menuBar.getMenuCount();
    //pop menu items
    Vector poppedList = new Vector();
    boolean found = false;
    for (int i=count-1; i>=0; i--){
      Component c = menuBar.getComponentAtIndex(i);
      menuBar.remove(i);
      if (c instanceof JMenuItem){
	JMenuItem mi = (JMenuItem)c;
	//contained=is this a menuItem managed by this cmdAdapter?
	//found=was the first menuItem in the group found?
	boolean contained = menuItemTable.contains(mi);
	if ((!found)&&(!contained)) 
	  poppedList.addElement(mi);
	else if ((!found)&&(contained)){//first menuItem in group found
	  found = true;
	  menuItemTable.remove(mi);
	  mi.removeActionListener(command);
	}
	else if ((found)&&(!contained)){//left group
	  menuBar.add(mi);
	  break;
	}
	else{
	  menuItemTable.remove(mi);//still in group  (found)&&(contained)
	  mi.removeActionListener(command);
	}
      }
      else poppedList.addElement(c);
    }	 
    //build new menu
    menuBar.add(command, this, constraints, keyInfo);
    //push menu items
    int size = poppedList.size();
    for (int i=size-1; i>=0; i--){
      menuBar.add((java.awt.Component)poppedList.elementAt(i));
    }
    menuBar.validate();
  }

  private void doStructureChangedForCPopupMenu(CPopupMenu parentMenu, 
					       Command command){
    int count = parentMenu.getComponentCount();
    //pop menu items
    Vector poppedList = new Vector();
    boolean found = false;
    boolean previousItemWasSeparator = false;
    for (int i=count-1; i>=0; i--){
      java.awt.Component c = parentMenu.getComponentAtIndex(i);
      parentMenu.remove(i);
      if (c instanceof javax.swing.JSeparator){
	previousItemWasSeparator = true;
	if (!found) {
		poppedList.addElement(c);
	}
      }
      else{
	JMenuItem mi = (JMenuItem)c;
	//contained=is this a menuItem managed by this cmdAdapter?
	//found=was the first menuItem in the group found?
	boolean contained = menuItemTable.contains(mi);
	if ((!found)&&(!contained)){
		poppedList.addElement(mi);
	}
	else if ((!found)&&(contained)){//first menuItem in group found
	  found = true;
	  menuItemTable.remove(mi);
	  mi.removeActionListener(command);
	}
	else if ((found)&&(!contained)){//left group
	  parentMenu.add(mi);
	  if (previousItemWasSeparator){
		  parentMenu.addSeparator();
	  }
	  break;
	}
	else{
	  menuItemTable.remove(mi);
	  mi.removeActionListener(command);
	}
	previousItemWasSeparator = false;
      }
    }	 
    //build new menu
    parentMenu.add(command, this, this.constraints, keyInfo);
    //push menu items
    int size = poppedList.size();
    for (int i=size-1; i>=0; i--){
      parentMenu.add((java.awt.Component)poppedList.elementAt(i));
    }
  }

  boolean remove(String cmdKey){
    boolean removed = false;
    if (cmdKey == null){
      removed = true;
      if (entireCommandAdded){
	String[] keys = command.getKeys();
        if (keys != null)
          for (int i=0; i<keys.length; i++)
            removeItem(keys[i]);
      }
      else {
	Enumeration keys = menuItemTable.keys();
	while(keys.hasMoreElements())
	  removeItem((String)keys.nextElement());
      }
    }
    else{
      removed = removeItem(cmdKey);
      if (removed && command instanceof StructuredCommand){
	StructuredCommand structuredCommand = (StructuredCommand)command;
	Object element = CommandUtilities.getElementForKey(structuredCommand, cmdKey);
	if (element instanceof SubCommand)
	  removeChildren(((SubCommand)element).getStructure());
      }
    }
    if (menuItemTable.isEmpty())
      cleanup();
    return removed;
  }

  private boolean removeItem(String key){
    //System.out.println("removing:"+key);
    JMenuItem menuItem = (JMenuItem)menuItemTable.get(key);
    if (menuItem == null)
      return false;
    Container parentMenu = menuItem.getParent();
    if (parentMenu != null)
      parentMenu.remove(menuItem);
    if (command instanceof StructuredCommand)
      ((StructuredCommand)command).removeStructuredCommandListener(this);
    else
      command.removeCommandListener(this);
    menuItem.removeActionListener(command);
    menuItemTable.remove(key);
    return true;
  }

  private void removeChildren(Vector children){
    //System.out.println("removing children");
    for (int i=0; i<children.size(); i++){
      Object element = children.elementAt(i);
      if (element instanceof String)
	removeItem((String)element);
      else if (element instanceof Vector)
	removeChildren((Vector)element);
      else{
	SubCommand subCommand = (SubCommand)element;
	boolean removed = removeItem(subCommand.getKey());
	if (removed)
	  removeChildren(subCommand.getStructure());
      }
    }
  }

  //help gc
  private void cleanup(){
    parent = null;
    command = null;
    constraints = null;
    keyInfo = null;
    menuItemTable = null;
  }
}

