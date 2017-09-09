/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 EditCommands.java
 *
 */
package com.gensym.cbu.adminShell.commands;

import java.awt.Frame;
import java.awt.event.WindowListener;
import java.awt.event.WindowEvent;
import java.awt.event.ActionEvent;
import com.gensym.denali.developer.*;
import com.gensym.denali.simpleclient.*;
import com.gensym.mdi.*;
import com.gensym.core.GensymApplication;
import com.gensym.message.Resource;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.dlg.*;

public final class EditCommands extends AbstractCommand 
{
  public static final String UNDO = "Undo";
  public static final String CUT = "CutSelection";
  public static final String COPY = "CopySelection";
  public static final String PASTE = "PasteSelection";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("denali/developer/commands/Errors");
  Frame frame;

  public EditCommands(Frame frame)
  {
    super(new CommandInformation[]{
      new CommandInformation(UNDO, true, shortResource, longResource, null, 
			     null, null, true),
      new CommandInformation(CUT, true, shortResource, longResource, null, 
			     null, null, true),
      new CommandInformation(COPY, true, shortResource, longResource, null, 
			     null, null, true),
      new CommandInformation(PASTE, true, shortResource, longResource, null, 
			     null, null, true)
	});
    this.frame = frame;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)){
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", 
						  cmdKey));
    }
    
    if (cmdKey.equals(UNDO))
      undoSelected();
    else if (cmdKey.equals(CUT))
      cutSelected();
    else if (cmdKey.equals(COPY))
      copySelected();
    else if (cmdKey.equals(PASTE))
      pasteSelected();
  }


  private void undoSelected()
  {
    System.out.println("Hey! Somebody needs to implement Undo");
  }

  private void cutSelected()
  {
    System.out.println("Hey! Somebody needs to implement Cut");
  }

  private void copySelected()
  {
    System.out.println("Hey! Somebody needs to implement Copy");
  }

  private void pasteSelected()
  {
    System.out.println("Hey! Somebody needs to implement Paste");
  }
}


