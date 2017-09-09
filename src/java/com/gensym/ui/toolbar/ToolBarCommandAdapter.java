/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MIDToolBarCommandAdapter.java
 *
 */

package com.gensym.ui.toolbar;

import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;
import java.awt.Component;
import java.awt.Image;
import javax.swing.AbstractButton;
import javax.swing.ImageIcon;
import com.gensym.ui.Command;
import com.gensym.ui.StructuredCommand;
import com.gensym.ui.StructuredCommandListener;
import com.gensym.ui.CommandEvent;
import com.gensym.ui.RepresentationConstraints;

class ToolBarCommandAdapter implements StructuredCommandListener{
  private volatile ToolBar toolBar;
  private Command command;
  private Hashtable buttons;
  private boolean entireCommandAdded;
  private RepresentationConstraints constraints;

  ToolBarCommandAdapter(Command cmd, RepresentationConstraints constraints,
			ToolBar toolBar, boolean entireCommandAdded){
    this.command = cmd;
    buttons = new Hashtable();
    this.toolBar = toolBar;
    this.entireCommandAdded = entireCommandAdded;
    this.constraints = constraints;
    if (cmd instanceof StructuredCommand)
      ((StructuredCommand)cmd).addStructuredCommandListener(this);
    else
      cmd.addCommandListener(this);
  }

  void add(ToolBarButton button){
    buttons.put(button.getKey(), button);
  }

  void add(ToolBarToggleButton button){
    buttons.put(button.getKey(), button);
  }

  Command getCommand(){
    return command;
  }

  @Override
  public void commandAvailabilityChanged(CommandEvent e){
    String key = e.getKey();
    Command cmd = (Command)e.getSource();
    AbstractButton button = (AbstractButton)buttons.get(key);
    if (button == null){
    	return;
    }
    button.setEnabled(cmd.isAvailable(key));
  }

  @Override
  public void commandStateChanged(CommandEvent e){
    String key = e.getKey();
    Command cmd = (Command)e.getSource();
    AbstractButton button = (AbstractButton)buttons.get(key);
    if (button instanceof ToolBarToggleButton){
      boolean state = cmd.getState(key).booleanValue();
      button.setSelected(state);
    }
  }

  @Override
  public void commandDescriptionChanged(CommandEvent e){
    String key = e.getKey();
    Command cmd = (Command)e.getSource();
    AbstractButton button = (AbstractButton)buttons.get(key);
    if (button == null){
    	return;
    }
    button.setToolTipText(cmd.getDescription(key, Command.LONG_DESCRIPTION));
    int type = constraints.getRepresentationType();
    if ((type == constraints.TEXT_ONLY) || (type == constraints.TEXT_AND_ICON)){
      if (cmd.isImmediate(key))
	button.setText(cmd.getDescription(key, Command.SHORT_DESCRIPTION));
      else
	button.setText(cmd.getDescription(key, Command.SHORT_DESCRIPTION)+"...");
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
	AbstractButton button = (AbstractButton)buttons.get(key);
	if (button != null){
		button.setIcon(img);
	}
      }
    }
  }

  @Override
  public synchronized void commandStructureChanged(CommandEvent e){
    //synchronized(this){
    if (!entireCommandAdded){
    	return; //exception??
    }
    Command cmd = (Command)e.getSource();
    int count = toolBar.getComponentCount();
    Component c;
    Vector poppedList = new Vector();
    boolean foundFirstCommandComp = false;
    //pop
    for (int i=count-1; i>=0; i--){
      c = toolBar.getComponent(i);
      toolBar.remove(i);
      if (c instanceof javax.swing.JToolBar.Separator){
	poppedList.addElement(c);
      }
      else{
	boolean contained = buttons.contains(c);
	if ((!contained)&&(!foundFirstCommandComp)){
		poppedList.addElement(c);
	}
	else if ((!foundFirstCommandComp)&&(contained)){
	  foundFirstCommandComp = true;
	  buttons.remove(c);
	  ((AbstractButton)c).removeActionListener(cmd);
	}
	else if ((foundFirstCommandComp)&&(!contained)){
	    toolBar.add(c);
	    break;
	}
	else{
	  buttons.remove(c);
	  ((AbstractButton)c).removeActionListener(cmd);
	}
      }
    }
    int size = poppedList.size();
    if (size >= 1){
      if (poppedList.elementAt(size-1) 
	  instanceof javax.swing.JToolBar.Separator){
	poppedList.removeElementAt(size-1);
	size--;
	toolBar.addSeparator();
      }
    }
    //re-build
    toolBar.add(cmd, this, constraints);
    //push
    for (int i=size-1; i>=0; i--){
      toolBar.add((Component)poppedList.elementAt(i));
    }
    toolBar.validate();
    //}
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
      else{
	Enumeration keys = buttons.keys();
	while(keys.hasMoreElements())
	  removeItem((String)keys.nextElement());
      }
    }
    else
      removed = removeItem(cmdKey);
    if (buttons.isEmpty())
      cleanup();
    return removed;
  }

  private boolean removeItem(String key){
    //System.out.println("removing:"+key);
    AbstractButton button = (AbstractButton)buttons.get(key);
    if (button == null)
      return false;
    toolBar.remove(button);
    if (command instanceof StructuredCommand)
      ((StructuredCommand)command).removeStructuredCommandListener(this);
    else
      command.removeCommandListener(this);
    button.removeActionListener(command);
    buttons.remove(key);
    return true;
  }

  //help gc
  private void cleanup(){
    toolBar = null;
    command = null;
    constraints = null;
    buttons = null;
  }
}
