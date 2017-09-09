/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 HelpCommands.java
 *
 */
package com.gensym.demos.g2studiosample.commands;

import java.awt.Frame;
import java.awt.TextArea;
import java.awt.event.ActionEvent;
import com.gensym.core.ProductManager;
import com.gensym.dlg.AboutDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.message.Resource;

public final class HelpCommands extends AbstractCommand implements 
StandardDialogClient {
  private AboutDialog aboutDialog;

  /** Command to display About dialog */
  public static final String ABOUT = "About";

  private static final String shortResource = "HelpCommandShortResource";
  private static final String longResource = "HelpCommandLongResource";
  private static final String mnemonicRsource = "MnemonicResource";
  private Resource shortBundle = Resource.getBundle("com/gensym/demos/g2studiosample/commands/HelpCommandShortResource");
  
  private Frame appFrame;

  public HelpCommands(Frame frame){
    super(new CommandInformation[]{
      new CommandInformation(ABOUT, true, shortResource, longResource,
			     "about.gif", null, 
			     null, false, mnemonicRsource, null)});
    this.appFrame = frame;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (cmdKey.equals(ABOUT))
      handleAbout();
  }

  private void handleAbout() {
    com.gensym.demos.g2studiosample.Shell.showSplashScreen();
  }

  @Override
  public void dialogDismissed (StandardDialog dlg, int code) {
  }
}











