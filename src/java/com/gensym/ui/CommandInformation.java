/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CommandInformation.java
 *
 */

package com.gensym.ui;

import java.awt.Image;
import javax.swing.KeyStroke;
import com.gensym.message.Resource;
/** 
 *  A class that encapsulates information about a single command.  This
 *  information includes
 *  its initial availability, initial state, and the resources needed to
 *  represent the command in the UI.
 *
 * @see com.gensym.ui.AbstractCommand
 */

public class CommandInformation extends StructuredCommandInformation{

  boolean available;
  String longResourceName;
  String shortResourceName;
  String smallImageName;
  String largeImageName;
  Boolean state;
  boolean immediate;
  Resource shortBundle;
  Resource longBundle;
  String shortDescription;
  String longDescription;
  Image smallImage;
  Image largeImage;

  String mnemonicResourceName;
  Resource mnemonicBundle;
  Character mnemonic;
  KeyStroke shortcut;

  /**
   * @deprecated As of version 1.1, 
   * replaced by CommandInformation(String, boolean, String, String, String, String, Boolean, boolean, String, KeyStroke)
   */
  public CommandInformation(String key, boolean initialAvailability, 
			    String shortResourceName, String longResourceName, 
			    String smallImageName, String largeImageName, 
			    Boolean initialState, boolean immediate){
    this(key, initialAvailability, shortResourceName, longResourceName,
	 smallImageName, largeImageName, initialState, immediate, null, null,
	 null, null, null, null, null);
  }

  /**
   * @param key the command key
   * @param initialAvailability true if initially available
   * @param shortResouceName the name of the properties file used for translating 
   *  the command's short description
   * @param longResourceName the name of the properties file used for translating
   *  the command's long description
   * @param smallImageName the name of the image file used for the command's small 
   *  icon
   * @param largeImageName the name of the image file used for the command's large
   *  icon
   * @param initialState true if the initial state of the command is "selected" or 
   *  "on"; false if the intial state is not "selected" or "off", null if the command
   *  does not support state
   * @param immediate true if the command is executed without any user interaction
   * @param mnemonicResourceName the name of the properties file used for translating
   *  the command's mnemonic
   * @param shortcut the key sequence to be assigned as an accelerator for the command
   */
  public CommandInformation(String key, boolean initialAvailability, 
			    String shortResourceName, String longResourceName, 
			    String smallImageName, String largeImageName, 
			    Boolean initialState, boolean immediate,
			    String mnemonicResourceName, KeyStroke shortcut){
    this(key, initialAvailability, shortResourceName, longResourceName, smallImageName, largeImageName,
	 initialState, immediate, null, null, null, null, mnemonicResourceName, null, shortcut);
  }

  /**
   * @deprecated As of version 1.1,
   * replaced by CommandInformation(String, boolean, String, String, String, String, Boolean, boolean, String, String, Image, Image, String, Character, KeyStroke)
   */
  public CommandInformation(String key, boolean initialAvailability, 
			    String shortResourceName, String longResourceName, 
			    String smallImageName, String largeImageName, 
			    Boolean initialState, boolean immediate,
			    String shortDescription, String longDescription, 
			    Image smallImage, Image largeImage){
    this(key, initialAvailability, shortResourceName, longResourceName, smallImageName, largeImageName,
	 initialState, immediate, shortDescription, longDescription, smallImage, largeImage, null, null, null);
  }

  /**
   * This constructor is usually used for commands that are created dynamically.
   * @param key the command key
   * @param initialAvailability true if initially available
   * @param shortResouceName the name of the properties file used for translating 
   *  the command's short description or null if the description is not translated
   * @param longResourceName the name of the properties file used for translating
   *  the command's long description or null if the description is not translated
   * @param smallImageName the name of the image file used for the command's small 
   *  icon or null if the image is not obtained from a file
   * @param largeImageName the name of the image file used for the command's large
   *  icon or null if the image is not obtained from a file
   * @param initialState true if the initial state of the command is "selected" or 
   *  "on"; false if the intial state is not "selected" or "off", null if the command
   *  does not support state
   * @param immeditae true if the command is executed without any user interaction
   * @param shortDescription the short description of the command; this takes 
   *  precedence over translation through the shortResourceName
   * @param longDescription the long description of the command; this takes 
   *  precedence over translation through the longResourceName
   * @param smallImage the small icon used for the command; this takes
   *  precedence over smallImageName 
   * @param largeImage the large icon used for the command; this takes
   *  precedence over largeImageName
   * @param mnemonicResourceName the name of the properties file used for translating
   *  the command's mnemonic
   * @param shortcut the key sequence to be assigned as an accelerator for the command
   */
  public CommandInformation(String key, boolean initialAvailability, 
			    String shortResourceName, String longResourceName, 
			    String smallImageName, String largeImageName, 
			    Boolean initialState, boolean immediate,
			    String shortDescription, String longDescription, 
			    Image smallImage, Image largeImage,
			    String mnemonicResourceName, Character mnemonic, KeyStroke shortcut){
    super(key);
    this.available = initialAvailability;
    this.shortResourceName = shortResourceName;
    this.longResourceName = longResourceName;
    this.smallImageName = smallImageName;
    this.largeImageName = largeImageName;
    this.state = initialState;
    this.immediate = immediate;
    this.shortDescription = shortDescription;
    this.longDescription = longDescription;
    this.smallImage = smallImage;
    this.largeImage = largeImage;
    this.mnemonicResourceName = mnemonicResourceName;
    this.mnemonic = mnemonic;
    this.shortcut = shortcut;
  }

  /** Returns the key for the command. */
  @Override
  public String getKey(){
    return key;
  }

  /** Returns true if the command is available and false otherwise. */
  public boolean getAvailable(){
    return available;
  }

  /** Returns the name of the resource used for the command's short description. */
  public String getShortResourceName(){
    return shortResourceName;
  }

  /** Returns the name of the resource used for the command's long description. */
  public String getLongResourceName(){
    return longResourceName;
  }

  /** Returns the name of the image file used for the command's small icon. */
  public String getSmallImageName(){
    return smallImageName;
  }

  /** Retruns the name of the image file used for the command's large icon. */
  public String getLargeImageName(){
    return largeImageName;
  }


  /** Returns the command's short description. */
  public String getShortDescription(){
    return shortDescription;
  }

  /** Returns the command's long description. */
  public String getLongDescription(){
    return longDescription;
  }

  /** Returns the image  used for the command's small icon. */
  public Image getSmallImage(){
    return smallImage;
  }

  /** Retruns the image used for the command's large icon. */
  public Image getLargeImage(){
    return largeImage;
  }

  /** Returns the initial state of the command. If a <code>Command</code>
   *  does not support state, null is returned.
   */
  public Boolean getState(){
    return state;
  }

  /** Returns true if the command executes without user interaction and false
   *  otherwise. */
  public boolean isImmediate(){
    return immediate;
  }

  /** Returns the name of the resource used to translated mnemonics. */
  public String getMnemonicResourceName(){
    return mnemonicResourceName;
  }

  /** Returns the character to be used as a mnemonic for the command. */
  public Character getMnemonic(){
    return mnemonic;
  }

  /** Returns the accelerator key sequence for the command. */
  public KeyStroke getShortcut(){
    return shortcut;
  }

}
  
