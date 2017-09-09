/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 AbstractStructuredCommand.java
 *
 */

package com.gensym.ui;

import java.awt.Image;
import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;

/**
 *  A default implementation for the <code>StructuredCommand</code>
 *  interface.  Subclasses of this class need only define the command's
 *  structure by calling setStructuredKeys and define the 
 *  <code>actionPerformed</code> method.<p>
 *
 *  Subclasses of this class may use <code>setStructureKeys</code> to change the 
 *  command's structure and the appropriate <code>CommandEvent</code> will be 
 *  dispatched to all <code>StructuredCommandListeners</code>.
 *
 *  @see com.gensym.ui.SubCommand
 *  @see com.gensym.ui.menu.CMenu
 *  @see com.gensym.ui.menu.CMenuBar
 *  @see com.gensym.ui.menu.awt.CMenu
 *  @see com.gensym.ui.menu.awt.CMenuBar
 */
public abstract class AbstractStructuredCommand extends AbstractCommand 
implements StructuredCommand{
  private StructuredCommandInformation[] structure;
  private Vector structuredKeys;
  private Hashtable pendingTable;
  private Integer id = 0;

  /**
   * Creates a <code>AbstractStructuredCommand</code> from a list of 
   * <code>CommandInformation</code> objects.  Each <code>CommandInformation</code>
   * describes either a single action, a subcommand, or a group of commands.  
   * The command's
   * descriptions are translated by key using the default <code>Locale</code> in
   * the specified resource.  If a resource (translation resource or image file)
   * if not specified by absolute name, then it is assume to be relative to the
   * <code>Command</code> class file.  
   */
  protected AbstractStructuredCommand(StructuredCommandInformation[] structure){
    super();
    commandTable = new Hashtable(11); //11 seems like a reasonable size
    pendingTable = new Hashtable(11);
    structuredKeys = new Vector();
    setStructuredKeys(structure);
  }

  /** 
   *  Sets the structure for the command.  Notification of <code>STRUCTURE_CHANGED
   *  </code> for the command key indicated by key is dispatched to all 
   * <code>StructuredCommandListeners</code>. 
   */
  
  protected void setStructuredKeys(StructuredCommandInformation[] structure){
    Integer currentId;
    synchronized(this) {
      id = id.intValue() + 1;
      currentId = id;
      this.structure = structure;
      java.util.Enumeration e = commandTable.keys();
      while (e.hasMoreElements()){
	Object key = e.nextElement();
	PendingInfo info = (PendingInfo)pendingTable.get(key);
	if (info == null){
	  info = new PendingInfo((CommandInformation)commandTable.get(key));
	  pendingTable.put(key, info);
	}
	info.ids.addElement(id);
      }
      commandTable.clear();
      Vector keys = new Vector();
      flattenStructure(this.structure, keys, id);
      orderedKeys = new String[keys.size()];
      for (int i=0; i<keys.size(); i++)
	orderedKeys[i] = (String)keys.elementAt(i);
      structuredKeys.removeAllElements();
    }
    notifyCommandChanged(new CommandEvent(this, CommandEvent.STRUCTURE_CHANGED, null), currentId);  
  }

  private void flattenStructure(StructuredCommandInformation[] structure, 
				Vector keys, Integer id){
    if (structure == null) 
      throw new IllegalArgumentException("StructureCanNotBeNull");
    for (int i =0; i<structure.length; i++){
      StructuredCommandInformation commandInfo = structure[i];
      if (commandInfo != null){
	String key = commandInfo.getKey();
	PendingInfo info = (PendingInfo)pendingTable.get(key);
	if (info != null){
	  if (info.ids.contains(id)){
	    info.ids.removeElement(id);
	    if (info.ids.isEmpty()){
	      pendingTable.remove(key);
	    }  
	  }
	}
	if (commandInfo instanceof CommandGroupInformation){
	  flattenStructure(((CommandGroupInformation)commandInfo).getStructure(), keys, id);
	}
	else if (commandInfo instanceof SubCommandInformation){
	  checkForDuplicateKey(key);
	  commandTable.put(key, commandInfo);
	  keys.addElement(key);
	  flattenStructure(((SubCommandInformation)commandInfo).getStructure(), keys, id);
	}
	else if (commandInfo instanceof CommandInformation){
	  checkForDuplicateKey(key);
	  commandTable.put(key, commandInfo);
	  keys.addElement(key);
	}
      }    
    }
  }

  /**
   * Returns a <code>Vector</code> that contains the hierarchical structure of the
   * <code>Command</code>.  The <code>Vector</code> may contain <code>Vectors</code>,
   * <code>Strings</code>, or <code>SubCommands</code>.  Each <code>Vector</code> is
   * a logical grouping of commands.  Each <codeString</code> represents a command
   * key.  A <code>SubCommand</code> indicates a new level in the hierarchy.
   */
  @Override
  public Vector getStructuredKeys(){
    Vector keys, keysCopy;
    if (structuredKeys.isEmpty()){
      StructuredCommandInformation[] structureCopy;
      synchronized(this){
	structureCopy = (StructuredCommandInformation[])structure.clone();
      }
      keysCopy = new Vector();
      convertStructure(structureCopy, keysCopy);
      structuredKeys = keysCopy;
    }
    synchronized(this){
      keys = (Vector)structuredKeys.clone();
    }
    return keys;
  }

  private void convertStructure(StructuredCommandInformation[] structure, 
				Vector newStructure){
    StructuredCommandInformation commandInfo = null;
    for (int i=0; i<structure.length; i++){
      commandInfo = structure[i];
      if (commandInfo != null){
	if (commandInfo instanceof SubCommandInformation){
	  SubCommandInformation subCmdInfo = (SubCommandInformation)commandInfo;
	  Vector subCmdStructure = new Vector();
	  convertStructure(subCmdInfo.getStructure(), subCmdStructure);
	  SubCommand subCmd = new SubCommand(subCmdInfo.getKey(), subCmdStructure);
	  newStructure.addElement(subCmd);
	}
	else if (commandInfo instanceof CommandGroupInformation){
	  Vector group = new Vector();
	  convertStructure(((CommandGroupInformation)commandInfo).getStructure(), group);
	  newStructure.addElement(group);
	}
	else
	  newStructure.addElement(commandInfo.getKey());
      }
    }
  }

  @Override
  public boolean isAvailable (String cmdKey){
    PendingInfo info = (PendingInfo)pendingTable.get(cmdKey);    
    CommandInformation commandInfo = null;
    if (info != null)
      commandInfo = info.info;
    if (commandInfo != null){
      //System.out.println("isAvailable("+cmdKey+"): retrieving from the pendingTable");
      return commandInfo.available;
    }
    else 
      return super.isAvailable (cmdKey);
  }
  
  @Override
  public String getDescription (String cmdKey, String type){
    PendingInfo info = (PendingInfo)pendingTable.get(cmdKey);    
    CommandInformation commandInfo = null;
    if (info != null)
      commandInfo = info.info;
    if (commandInfo != null){
      //System.out.println("getDescription("+cmdKey+"): retrieving from the pendingTable");
      if (Command.SHORT_DESCRIPTION.equals(type))
	return getShortDescription(commandInfo);
      else 
	return getLongDescription(commandInfo);
    }
    else 
      return super.getDescription (cmdKey, type);
  }
  
  @Override
  public Image getIcon(String cmdKey, String type){
    PendingInfo info = (PendingInfo)pendingTable.get(cmdKey);    
    CommandInformation commandInfo = null;
    if (info != null)
      commandInfo = info.info;
    if (commandInfo != null){
      //System.out.println("getIcon("+cmdKey+"): retrieving from the pendingTable");
      if (Command.SMALL_ICON.equals(type))
	return getSmallImage(commandInfo);
      else 
	return getLargeImage(commandInfo);
    }
    else 
      return super.getIcon(cmdKey, type);
  }
  
  @Override
  public Boolean getState(String cmdKey){
    PendingInfo info = (PendingInfo)pendingTable.get(cmdKey);    
    CommandInformation commandInfo = null;
    if (info != null)
      commandInfo = info.info;
    if (commandInfo != null){
      //System.out.println("getState("+cmdKey+"): retrieving from the pendingTable");
      return commandInfo.state;
    }
    else 
      return super.getState(cmdKey);
  }
  
  @Override
  public boolean isImmediate(String cmdKey){
    PendingInfo info = (PendingInfo)pendingTable.get(cmdKey);    
    CommandInformation commandInfo = null;
    if (info != null)
      commandInfo = info.info;
    if (commandInfo != null){
      //System.out.println("isImmediate("+cmdKey+"): retrieving from the pendingTable");
      return commandInfo.immediate;
    }
    else 
      return super.isImmediate (cmdKey);
  }
  
  /**
   * Adds a <code>StructuredCommandListener</code>.
   */
  @Override
  public void addStructuredCommandListener (StructuredCommandListener listener){
    listeners.addElement(listener);
  }

  /**
   * Removes a <code>StructuredCommandAvailabilityListener</code>.
   */
  @Override
  public void removeStructuredCommandListener(StructuredCommandListener listener){
    listeners.removeElement(listener);
  }


  /**
   * Dispatches a <code>CommandEvent</code> event to listeners.
   */
  private void notifyCommandChanged(CommandEvent e, Integer id){
    if (e.getId() == e.STRUCTURE_CHANGED){
      Vector l;
      synchronized(this) {
    	  l = (Vector)listeners.clone();
      }
      Enumeration dispatchList = l.elements();
      while (dispatchList.hasMoreElements()){
	CommandListener listener = 
	  ((CommandListener)dispatchList.nextElement());
	if (listener instanceof StructuredCommandListener)
	  ((StructuredCommandListener)listener).commandStructureChanged(e);
      }
      java.util.Enumeration keys = pendingTable.keys();
      while (keys.hasMoreElements()){
	Object key = keys.nextElement();
	PendingInfo info = (PendingInfo)pendingTable.get(key);
	if (info != null){
	  info.ids.removeElement(id);
	  if (info.ids.isEmpty()){
	    pendingTable.remove(key);
	  }
	}
      }
    }
    else super.notifyCommandChanged(e);
  }

  class PendingInfo{
    CommandInformation info;
    Vector ids;

    PendingInfo(CommandInformation info){
      this.info = info;
      ids = new Vector();
    }

    @Override
    public String toString () {
      return "Pending: Info = " + info + ", IDs = " + ids;
    }
  }

  /**
   * @undocumented
   */
  protected StructuredCommandInformation[] getStructure()
  {
    return structure;
  }

}

