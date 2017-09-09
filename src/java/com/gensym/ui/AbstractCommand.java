/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 AbstractCommand.java
 *
 */

package com.gensym.ui;

import java.util.Vector;
import java.util.Enumeration;
import java.util.Hashtable;
import java.awt.Toolkit;
import java.awt.Image;
import java.awt.event.ActionEvent;
import javax.swing.KeyStroke;
import com.gensym.message.Resource;

/** 
 * A default implementation of the <code>Command</code> interface.
 *<p>
 *  An <code>AbstractCommand<code> is created from one or more 
 *  <code>CommandInformation<code> objects.  Each 
 *  <code>CommandInformation<code> object represents an action that the 
 *  <code>Command<code> can perform.
 *</p><p>
 *  A command's description and mnemonic is translated only once at the time of the first
 *  request for the description.  A command's icon is created only once at the
 *  time of the first request for the icon.
 *</p><p>
 *  Subclasses of this abstract class may need only define 
 *  <code>actionPerformed<code>.  Subclasses of this class may use the 
 *  <code>setAvailable<code>, <code>setState<code>, <code>setDescription<code>,
 *  and <code>setIcon<code> methods for changing a commands availability,
 *  state, description, or icon, respectively.
 *  If the new value is different from the old value, the appropriate 
 *  <code>CommandEvent<code> is dispatched to all <code>CommandListeners<code>.
 *</p><p>
 * @see com.gensym.ui.CommandInformation
 */

public abstract class AbstractCommand implements Command, KeyableCommand{

  private static Resource i18n = Resource.getBundle("com/gensym/ui/Errors");

  Vector listeners = new Vector();

  private Class commandClass;
  Hashtable commandTable;
  String[] orderedKeys;

  /**
   * Creates an AbstractCommand from a list of CommandInformation objects.
   * Each CommandInformation object describes a single action.
   * The command's descriptions are translated by key using the default
   * Locale in the specified resource.  
   * If a resource (translation resource or image file) is not specified by an
   * absolute name, then it is assumed to be relative to the Command class file.
   */
  protected AbstractCommand(CommandInformation[] commandInformationList){
    if (commandInformationList == null) 
      throw new IllegalArgumentException(i18n.getString("IllegalCommandInformationList"));
    commandClass = this.getClass();
    int length = commandInformationList.length;	// ch -> 0 keys allowed?
    commandTable = new Hashtable(11); //11 seems like a reasonable size 
    orderedKeys = new String[length];
    for (int i =0; i<length; i++){
      CommandInformation commandInfo = commandInformationList[i];
      checkForDuplicateKey(commandInfo.getKey());
      commandTable.put(commandInfo.getKey(), commandInfo);
      orderedKeys[i] = commandInfo.getKey();
    }
  }

  AbstractCommand(){
    commandClass = this.getClass();
  }

  void checkForDuplicateKey(String key){
    if (commandTable.get(key) != null)
      throw new IllegalArgumentException(i18n.format("DuplicateKey", key));
  }

  @Override
  public abstract void actionPerformed (ActionEvent e);

  /**
   * Returns a boolean indicating whether this Command
   * is currently available.
   */
  @Override
  public boolean isAvailable (String cmdKey){
    CommandInformation commandInfo = (CommandInformation)lookupKey(cmdKey);
    return commandInfo.available;
  }
  
  /**
   * Sets the availability of this Command.  If the availability has changed,
   * notification is dispatched to listeners.
   */
  protected void setAvailable (String cmdKey, boolean available){
    CommandInformation commandInfo = (CommandInformation)lookupKey(cmdKey);
    setAvailable(commandInfo, available);
  }

  void setAvailable(CommandInformation commandInfo, boolean available){
    if (commandInfo.available != available){
      commandInfo.available = available;
      CommandEvent e = new CommandEvent(this, CommandEvent.AVAILABILITY_CHANGED, 
					commandInfo.key);
      notifyCommandChanged(e);
    }
  }

  /**
   * Returns an array of command keys.  Each key represents an action that the
   * Command can perform.
   */
  @Override
  public synchronized String[] getKeys(){
    if (commandTable.isEmpty()){
    	return null;
    }
    int len = orderedKeys.length;
    String[] keys = new String[len];
    for (int i=0; i<len; i++)
      keys[i] = orderedKeys[i];
    return keys;
  }

  /**
   * Returns a textual description for this Command.
   * The key should be either SHORT_DESCRIPTION or
   * LONG_DESCRIPTION.
   */
  @Override
  public String getDescription (String cmdKey, String type){
    CommandInformation commandInfo = (CommandInformation)lookupKey(cmdKey);
    if (Command.SHORT_DESCRIPTION.equals(type))
      return getShortDescription(commandInfo);
    else 
      return getLongDescription(commandInfo);
  }

  /**
   * Sets the description of this Command.  If the description has changed,
   * notification is dispatched to all listeners.
   */
  protected void setDescription(String cmdKey, String type, String newDescription){
    CommandInformation commandInfo = (CommandInformation)lookupKey(cmdKey);
    setDescription(commandInfo, type, newDescription);
  } 

  void setDescription(CommandInformation commandInfo, String type, String description){
    boolean fireEvent = false;
    if (Command.SHORT_DESCRIPTION.equals(type)){
      if (((description == null) && (commandInfo.shortDescription != null)) ||
       ((description != null) && (!description.equals(commandInfo.shortDescription)))){
	fireEvent = true;
	commandInfo.shortDescription = description;
      }
    }
    else{ 
      if (((description == null) && (commandInfo.longDescription != null)) ||
        ((description != null) && (!description.equals(commandInfo.longDescription)))){
	fireEvent = true;
	commandInfo.longDescription = description;
      }
      if (fireEvent){
	CommandEvent e = new CommandEvent(this, CommandEvent.DESCRIPTION_CHANGED, 
					  commandInfo.key);
	notifyCommandChanged(e);
      }
    }
  }
    
  /**
   * Returns an image of the size indicated by size.  The size should either
   * be SMALL_ICON or LARGE_ICON.
   */
  @Override
  public Image getIcon (String cmdKey, String size){
    CommandInformation commandInfo = (CommandInformation)lookupKey(cmdKey);
    if (Command.SMALL_ICON.equals(size))
      return getSmallImage(commandInfo);
    else 
      return getLargeImage(commandInfo);
  }

  /**
   * Sets the image of the size indicated by size.  The size should either
   * be SMALL_ICON or LARGE_ICON.
   */
  public void setIcon (String cmdKey, String size, Image icon){
    CommandInformation commandInfo = (CommandInformation)lookupKey(cmdKey);
    setIcon(commandInfo, size, icon);
  } 

  void setIcon(CommandInformation commandInfo, String size, Image icon){
    boolean fireEvent = false;
    if (Command.SMALL_ICON.equals(size)){
      if (((icon == null) && (commandInfo.smallImage != null)) ||
       ((icon != null) && (!icon.equals(commandInfo.smallImage)))){
	fireEvent = true;
	commandInfo.smallImage = icon;
      }
    }
    else{ 
      if (((icon == null) && (commandInfo.largeImage != null)) ||
        ((icon != null) && (!icon.equals(commandInfo.largeImage)))){
	fireEvent = true;
	commandInfo.largeImage = icon;
      }
    }
    if (fireEvent){
      CommandEvent e = new CommandEvent(this, CommandEvent.ICON_CHANGED, 
					commandInfo.key);
      notifyCommandChanged(e);
    }
  }


  /**
   * Returns the state for this Command. No state is indicated by null.
   * "Selected" or "on" is indicated by Boolean.True and "unselected" or "off"
   * is indicated by Boolean.False.
   */
  @Override
  public Boolean getState(String cmdKey){
    CommandInformation commandInfo = (CommandInformation)lookupKey(cmdKey);
    return commandInfo.state;
  }

  /**
   * Sets the state of this Command.  If the state has changed, notification is
   * dispatched to listeners.
   */
  protected void setState(String cmdKey, Boolean state){
    CommandInformation commandInfo = (CommandInformation)lookupKey(cmdKey);
    setState(commandInfo, state);
  }

  void setState(CommandInformation commandInfo, Boolean state){
    if (!commandInfo.state.equals(state)){
      commandInfo.state = state;
      CommandEvent e = new CommandEvent(this, CommandEvent.STATE_CHANGED, commandInfo.key);
      notifyCommandChanged(e);
    }
  }

  
  /**
   * Returns true is this Command is executed without user interaction and
   * false otherwise.
   */
  @Override
  public boolean isImmediate(String cmdKey){
    CommandInformation commandInfo = (CommandInformation)lookupKey(cmdKey);
    return commandInfo.immediate;
  }

  /**
   *  Sets whether this Command executes immediately.
   */
  protected void setImmediate(String cmdKey, boolean immediate){
    CommandInformation commandInfo = (CommandInformation)lookupKey(cmdKey);
    setImmediate(commandInfo, immediate);
  }

  void setImmediate(CommandInformation commandInfo, boolean immediate){
      commandInfo.immediate = immediate;
  }

  /**
   * Checks if the argument is one of the valid keys for this
   * Command. A key is valid if and only if it was included
   * in the CommandInformation data passed to the Constructor.
   * Subclasses can use this to check the validity
   * of any key passed to it as an argument. If the key is
   * not valid, an IllegalArgumentException is thrown.
   * @param cmdKey the String key to check
   */
  protected void checkKey (String cmdKey) {
    CommandInformation commandInfo = (CommandInformation)commandTable.get(cmdKey); 
    if (commandInfo == null){
    	notifyUnknownKey(cmdKey);
    }
  }
  
  CommandInformation lookupKey(String cmdKey){
    CommandInformation commandInfo = (CommandInformation)commandTable.get(cmdKey); 
    if (commandInfo == null){
    	notifyUnknownKey(cmdKey);
    }
    return commandInfo;
  }

  private void notifyUnknownKey(String key){
    IllegalArgumentException ex = new IllegalArgumentException(
       i18n.format("unknownCommandKey", key));
    throw ex;
  }

  /**
   * Adds a CommandListener.
   */
  @Override
  public void addCommandListener(CommandListener listener){
    listeners.addElement(listener);
  }

  /**
   * Removes a CommandListener.
   */
  @Override
  public void removeCommandListener(CommandListener listener){
    listeners.removeElement(listener);
  }

  /**
   * Dispatches a CommandEvent event to listeners.
   */
  protected void notifyCommandChanged(CommandEvent e){
    Vector l;
    synchronized(this) {
    	l = (Vector)listeners.clone();
    }
    Enumeration dispatchList = l.elements();
    while (dispatchList.hasMoreElements()){
      CommandListener listener = ((CommandListener)dispatchList.nextElement());
      int id = e.getId();
      switch (id){
	case CommandEvent.AVAILABILITY_CHANGED:
	  listener.commandAvailabilityChanged(e);
	  break;
	case CommandEvent.STATE_CHANGED:
	  listener.commandStateChanged(e);
	  break;
        case CommandEvent.DESCRIPTION_CHANGED:
	  listener.commandDescriptionChanged(e);
	  break;
      case CommandEvent.ICON_CHANGED:
	listener.commandIconChanged(e);
	break;
	  default:
      }
    }  
  }

  @Override
  public synchronized  String toString(){
    int len = orderedKeys.length;
    String name = getClass().getName();
    if (len == 0) {
    	return name+"[no keys]";
    }
    String cmdString = name+"[keys=";
    for (int i=0; i<len-1; i++)
      cmdString = cmdString+orderedKeys[i]+",";
    return cmdString+orderedKeys[len-1]+"]";
  }

  String getShortDescription(CommandInformation commandInfo){
    if (commandInfo.shortDescription == null){
      if (commandInfo.shortBundle == null){
	if (commandInfo.shortResourceName == null){
		return null;
	}
	commandInfo.shortBundle = 
	  Resource.getBundle(resolveResourceName(commandInfo.shortResourceName));
	commandInfo.shortDescription = commandInfo.shortBundle.getString(commandInfo.key);
      }
    }
    return commandInfo.shortDescription;
  }
    
  String getLongDescription(CommandInformation commandInfo){
    if (commandInfo.longDescription == null){
      if (commandInfo.longBundle == null){
	if (commandInfo.longResourceName == null){
		return null;
	}
	commandInfo.longBundle = 
	  Resource.getBundle(resolveResourceName(commandInfo.longResourceName));
	commandInfo.longDescription = commandInfo.longBundle.getString(commandInfo.key);
      }
    }
    return commandInfo.longDescription;
  }
  
  Image getSmallImage(CommandInformation commandInfo){

    if (commandInfo.smallImage == null){
      if (commandInfo.smallImageName == null){
	return null;
      }
      commandInfo.smallImage = 
	Toolkit.getDefaultToolkit().getImage(commandClass.getResource(commandInfo.smallImageName));
    }
    return commandInfo.smallImage;
  }
  
  Image getLargeImage(CommandInformation commandInfo){
    if (commandInfo.largeImage == null){
      if (commandInfo.largeImageName == null){
	return null;
      }
      commandInfo.largeImage = 
	Toolkit.getDefaultToolkit().getImage(commandClass.getResource(commandInfo.largeImageName));
    }
    return commandInfo.largeImage;
  }
  
  /* Add a package name prefix if the name is not package qualified.
   * Remove leading "/" if name starts with "/" (for backward compatibility)
   */
  private String resolveResourceName(final String name) {
    String resourceName = name;
	if (resourceName == null) {
      return resourceName;
    }
    if (resourceName.indexOf('.') == -1) {
      String baseName = commandClass.getName();
      int index = baseName.lastIndexOf('.');
      if (index != -1) {
	// The old code thought that these were pathnames, when they
	// are, in fact class names. The following line is kept
	// as a reference in case this same assumption bites us
	// elsewhere (to show what the old thinking was)
	//name = baseName.substring(0, index).replace('.', '/')+"/"+name;
	resourceName = baseName.substring(0, index) + "." + resourceName;
      }
    } else if (resourceName.startsWith("/"))
      resourceName = resourceName.substring(1);
    return resourceName;
  } 

  /**
   * Returns a Character to be used as the mnemonic for the command.  Return null for no mnemonic
   * @throws java.util.MissingResourceException
   */
  @Override
  public Character getMnemonic(String cmdKey){
    CommandInformation commandInfo = (CommandInformation)lookupKey(cmdKey);
    return getMnemonic(commandInfo);
  }

  private Character getMnemonic(CommandInformation commandInfo){
    if (commandInfo.mnemonic == null){
      if (commandInfo.mnemonicBundle == null){
	if (commandInfo.mnemonicResourceName == null) 
	  return null;
	else{
	  commandInfo.mnemonicBundle = 
	    Resource.getBundle(resolveResourceName(commandInfo.mnemonicResourceName));
	  String mnemonicString = commandInfo.mnemonicBundle.getString(commandInfo.key);
	  if (mnemonicString.length() >= 1)
	    commandInfo.mnemonic = Character.valueOf(mnemonicString.charAt(0));
	}
      }
    }
    return commandInfo.mnemonic;
  }

  /**
   * Returns a KeyStroke to be used as the shortcut/accelerator for the command.  Return
   * null for no shortcut.
   */
  @Override
  public KeyStroke getShortcut(String cmdKey){
    CommandInformation commandInfo = (CommandInformation)lookupKey(cmdKey);
    return commandInfo.shortcut;
  }

  protected Hashtable getCommandTable()
  {
    return commandTable;
  }

}










