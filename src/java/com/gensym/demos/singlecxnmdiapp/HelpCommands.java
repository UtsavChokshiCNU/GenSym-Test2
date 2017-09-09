/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 HelpCommands.java
 *
 */
package com.gensym.demos.singlecxnmdiapp;

import java.awt.Frame;
import java.awt.TextArea;
import java.awt.event.ActionEvent;
import com.gensym.dlg.AboutDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.message.Resource;

public final class HelpCommands extends AbstractCommand {

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("com.gensym.shell.commands.Errors");
  private Resource i18nUI = Resource.getBundle("com.gensym.demos.singlecxnmdiapp.UiLabels");

  public static final String ABOUT = "About";

  private Frame appFrame;
  private AboutDialog aboutDialog;

  public HelpCommands(Frame frame){
    super(new CommandInformation[]{
      new CommandInformation(ABOUT, true, 
			     shortResource, longResource, 
			     null, null, null, false)});
    this.appFrame = frame;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (!isAvailable(cmdKey)){
      throw new IllegalStateException(i18n.format("CommandIsUnavailable", 
						  cmdKey));
    } 

    if (cmdKey.equals(ABOUT))
      handleAboutCommand();
  }

  private void handleAboutCommand(){
    if (aboutDialog == null){
      String title = i18nUI.getString("AboutTitle");
      String msg = i18nUI.getString("AboutMessage");   
      boolean isModal = true;
      int numRows = 10;
      int numColumns = 90;
      int scrollbarVisibility = TextArea.SCROLLBARS_VERTICAL_ONLY;
      aboutDialog = new AboutDialog(appFrame, title, isModal, msg, 
				    numRows, numColumns, scrollbarVisibility,
				    null);
    }

    aboutDialog.setVisible (true);
  }

}











