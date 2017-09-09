/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CCheckboxMenuItem.java
 *
 */

package com.gensym.ui.menu.awt;

import java.awt.CheckboxMenuItem;
import java.awt.event.*;
import java.util.Vector;
import java.util.Enumeration;
import com.gensym.ui.Command;

/** CCheckboxMenuItems are typically created by adding Commands that have state to   
 *  a CMenu. A CCheckboxMenuItem has a unique key that is used as the actionCommand 
 *  property of the ActionEvent dispatched on selection.  CCheckboxMenuItems 
 *  support cloning.
 */
class CCheckboxMenuItem extends CheckboxMenuItem implements ItemListener {
  private String key;
  private CMenuCommandAdapter cmdAdapter;
  private Vector listeners = new Vector();

  public CCheckboxMenuItem(String label){
    super(label);
  }

  CCheckboxMenuItem(Command command, String cmdKey, 
			   CMenuCommandAdapter cmdAdapter){
    this(command, cmdKey, cmdAdapter, 
	 ((Boolean)command.getState(cmdKey)).booleanValue());
  }

  CCheckboxMenuItem(Command command, String cmdKey, 
			   CMenuCommandAdapter cmdAdapter, boolean state){
    super();
    setState(state);
    if (command.isImmediate(cmdKey))
      setLabel(command.getDescription(cmdKey, Command.SHORT_DESCRIPTION));
    else
      setLabel(command.getDescription(cmdKey, Command.SHORT_DESCRIPTION)+"...");
    this.key = cmdKey;
    this.cmdAdapter = cmdAdapter;
    cmdAdapter.add(this);
    this.addActionListener(command);
    if (!command.isAvailable(key)) this.setEnabled(false);
    addItemListener(this);
  }

  @Override
  public void addActionListener(ActionListener l){
    listeners.addElement(l);
  }

  @Override
  public void removeActionListener(ActionListener l){
    listeners.removeElement(l);
  }

  @Override
  public void itemStateChanged(ItemEvent e){
    //workaround for AWT bug:
    //CheckboxMenuItems do not fire ActionEvents only ItemEvents
    ActionEvent evt = new ActionEvent(this, ActionEvent.ACTION_PERFORMED, key);
    Vector l;
    synchronized(this) {l = (Vector)listeners.clone();}
    Enumeration dispatchList = l.elements();
    while (dispatchList.hasMoreElements()){
      ActionListener listener = ((ActionListener)dispatchList.nextElement());
      listener.actionPerformed(evt);
    }
  }

  /** Returns the key */
  public String getKey(){
    return key;
  }

  CMenuCommandAdapter getCommandAdapter(){
    return cmdAdapter;
  }
}



