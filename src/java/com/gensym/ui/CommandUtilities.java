/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CommandUtilities.java
 *
 */

package com.gensym.ui;

import java.util.Vector;

/**
 *  This class contains convenience methods for Commands.
 */
public class CommandUtilities{

  /**
   *  Traverses the structure of the StructuredCommand and returns
   *  the first command key (String) that equals the
   *  specified key or SubCommand whose key equals the specified key.
   *  If no match is found, null is returned.
   */
  public static Object getElementForKey(StructuredCommand command, String key){
    Vector structure = command.getStructuredKeys();
    return getElementForKey(structure, key);
  }
  
  private static Object getElementForKey(Vector structure, String key){
    Object commandElement = null;
    for (int i=0; i<structure.size(); i++){
      Object element = structure.elementAt(i);
      if (element instanceof String){
	if (element.equals(key)){
		commandElement = element;
	}
      }
      else if (element instanceof Vector){
	commandElement = getElementForKey((Vector)element, key);
      }
      else if (element instanceof SubCommand){
	SubCommand subCommand = (SubCommand)element;
	String subCmdKey = subCommand.getKey();
	if (subCmdKey.equals(key)){
		commandElement = subCommand;
	}
	else commandElement = getElementForKey(subCommand.getStructure(), key);
      }
      if (commandElement != null){
    	  break;
      }
    }
    return commandElement;
  }

}
