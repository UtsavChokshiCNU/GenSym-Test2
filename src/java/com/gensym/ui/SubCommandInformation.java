/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SubCommandInformation.java
 *
 */

package com.gensym.ui;

import java.awt.Image;
import java.util.Vector;

/** 
 *  This class encapsulates information about a single subcommand, including
 *  its initial availability, initial state, and a list of commands.
 *
 * @see com.gensym.ui.AbstractCommand
 */
public class SubCommandInformation extends CommandInformation{
  private StructuredCommandInformation[] structure;

/**
 * @undocumented
 * @deprecated
 */
  public SubCommandInformation(String key, boolean initialAvailability, 
		    String shortResourceName, String longResourceName, 
		    String smallImageName, String largeImageName, 
		    Boolean initialState, StructuredCommandInformation[] structure){
    this(key, initialAvailability, shortResourceName, longResourceName,
	 smallImageName, largeImageName, initialState,
	 null, null, null, null, null, null, structure);
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
   * @param structure the list of commands "under" this subcommand
   */
  public SubCommandInformation(String key, boolean initialAvailability, 
		    String shortResourceName, String longResourceName, 
		    String smallImageName, String largeImageName, 
		    Boolean initialState, String mnemonicResourceName,
		    StructuredCommandInformation[] structure){
    this(key, initialAvailability, shortResourceName, longResourceName, smallImageName, largeImageName,
	 initialState, null, null, null, null, mnemonicResourceName, null, structure);
  }


  /**
   * @undocumented
   * @deprecated
   */
  public SubCommandInformation(String key, boolean initialAvailability, 
		    String shortResourceName, String longResourceName, 
		    String smallImageName, String largeImageName, 
		    Boolean initialState, String shortDescription,
		    String longDescription, Image smallImage, 
		    Image largeImage, StructuredCommandInformation[] structure){
    this(key, initialAvailability, shortResourceName, longResourceName, smallImageName, largeImageName,
	 initialState, shortDescription, longDescription, smallImage, largeImage, null, null, structure);
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
   * @param shortDescription the short description of the command; this takes 
   *  precedence over translation through the shortResourceName
   * @param longDescription the long description of the command; this takes 
   *  precedence over translation through the longResourceName
   * @param smallImage the small icon used for the command; this takes
   *  precedence over smallImageName 
   * @param largeImage the large icon used for the command; this takes
   *  precedence over largeImageName
   * @param structure the list of commands "under" this subcommand
   */
  public SubCommandInformation(String key, boolean initialAvailability, 
		    String shortResourceName, String longResourceName, 
		    String smallImageName, String largeImageName, 
		    Boolean initialState, String shortDescription,
		    String longDescription, Image smallImage, 
		    Image largeImage, String mnemonicResourceName,
		    Character mnemonic, StructuredCommandInformation[] structure){
    super(key, initialAvailability, shortResourceName, longResourceName,
	  smallImageName, largeImageName, initialState, true, shortDescription,
	  longDescription, smallImage, largeImage, mnemonicResourceName, mnemonic, null);
    this.structure = structure;
  }

  public StructuredCommandInformation[] getStructure(){
    return structure;
  }
}
