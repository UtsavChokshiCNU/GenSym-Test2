/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CommandGroupInformation.java
 *
 */

package com.gensym.ui;

/** 
 *  This class indicated a group of commands.
 *
 * @see com.gensym.ui.AbstractCommand
 */


public class CommandGroupInformation extends StructuredCommandInformation{

  private CommandInformation[] structure;

  /**
   * @param key the key for this group
   * @param structure the commands that make up this group
   */
  public CommandGroupInformation(String key, CommandInformation[] structure){
    super(key);
    this.structure = structure;
  }

  /**
   * Returns the commands that make up this group
   */
  public CommandInformation[] getStructure(){
    return structure;
  }
}
  
