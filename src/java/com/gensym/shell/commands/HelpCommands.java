/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 HelpCommands.java
 *
 */
package com.gensym.shell.commands;

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
  public static final String ABOUT = "AboutTelewindows2";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private static final String mnemonicResource = "MnemonicResource";
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");
  private Resource shortBundle = Resource.getBundle("com/gensym/shell/commands/CommandShortResource");

  private Frame appFrame;

  public HelpCommands(Frame frame){
    super(new CommandInformation[]{
      new CommandInformation(ABOUT, true, shortResource, longResource,
			     "about.gif", null, 
			     null, false, mnemonicResource, null)});
    this.appFrame = frame;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)){
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", cmdKey));
    } 

    if (cmdKey.equals(ABOUT))
      handleAboutTelewindows2Command();
  }

  private void handleAboutTelewindows2Command(){
    if (aboutDialog == null){
      String title = shortBundle.getString("AboutTWTitle");
      String version = ProductManager.getProduct("sequoia").getDisplayVersion();
      String msg = "Telewindows2 Toolkit Shell\n"+version+"\n\nCopyright (C) 1986-2017 Gensym Corporation. \nAll rights reserved.";
      boolean isModal = true;
      int numRows = 6;
      int numColumns = 40;
      int scrollbarVisibility = TextArea.SCROLLBARS_NONE;
      aboutDialog = new AboutDialog(appFrame, title, isModal, msg, 
				    numRows, numColumns, scrollbarVisibility,
				    (StandardDialogClient) this);
    }

    aboutDialog.setVisible (true);
  }

  @Override
  public void dialogDismissed (StandardDialog dlg, int code) {
  }
}











