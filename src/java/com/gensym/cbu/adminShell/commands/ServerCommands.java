/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ServerCommands.java
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

public final class ServerCommands extends AbstractCommand 
  implements WindowListener, StandardDialogClient
{
  /** Command to exit application */
  public static final String CONNECT = "Connect";
  public static final String DISCONNECT = "Disconnect";
  public static final String EXIT = "ExitDeveloperShell";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("denali/developer/commands/Errors");
  private String[] workspaceNames;
  private String workspaceName;
  Frame frame;

  public ServerCommands(Frame frame)
  {
    super(new CommandInformation[]{
      new CommandInformation(CONNECT, true, shortResource, longResource, null, 
			     null, null, true),
      new CommandInformation(DISCONNECT, true, shortResource, longResource, null, 
			     null, null, true),
      new CommandInformation(EXIT, true, shortResource, longResource, "exit_tw.gif", 
			     null, null, true)});
    this.frame = frame;
    frame.addWindowListener((WindowListener)this);
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)){
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", 
						  cmdKey));
    }
    
    if (cmdKey.equals(EXIT))
      exitApp();
    else if (cmdKey.equals(CONNECT))
      connectSelected();
    else if (cmdKey.equals(DISCONNECT))
      disconnectSelected();
  }

  @Override
  public void windowClosing(WindowEvent e) {
    exitApp();
  }

  @Override
  public void windowActivated(WindowEvent e) {}
  @Override
  public void windowDeactivated(WindowEvent e) {}
  @Override
  public void windowOpened(WindowEvent e) {}
  @Override
  public void windowClosed(WindowEvent e) {}
  @Override
  public void windowIconified(WindowEvent e) {}
  @Override
  public void windowDeiconified(WindowEvent e) {}

  private void exitApp()
  {
    System.exit(0);
  }

  @Override
  public synchronized void dialogDismissed (StandardDialog dlg, int cmdCode) {
    if (dlg.wasCancelled ())
      workspaceName = null;
    else
      {
	int chosenIndex = ((SelectionDialog)dlg).getResult();
	dlg.setVisible (false);
	workspaceName = workspaceNames[chosenIndex];
      }
  }

  private void connectSelected()
  {
    System.out.println("Hey! Somebody needs to implement connect");
  }

  private void disconnectSelected()
  {
    System.out.println("Hey! Somebody needs to implement disconnect");
  }
}


