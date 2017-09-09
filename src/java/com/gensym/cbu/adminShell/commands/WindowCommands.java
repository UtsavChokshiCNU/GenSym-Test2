/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WindowCommands.java
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

public final class WindowCommands extends AbstractCommand 
{
  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("denali/developer/commands/Errors");

  Frame frame;

  public WindowCommands(Frame frame)
  {
    super(new CommandInformation[]{
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
  }
}


