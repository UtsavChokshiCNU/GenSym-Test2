/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 HelpCommands.java
 *
 */
package com.gensym.demos.multiplecxnsdiapp;

import java.awt.Frame;
import java.awt.TextArea;
import java.awt.event.ActionEvent;
import com.gensym.dlg.AboutDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.message.Resource;

public final class HelpCommands extends AbstractCommand implements 
StandardDialogClient {

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");
  private Resource shortBundle = Resource.getBundle("com/gensym/demos/multiplecxnsdiapp/CommandShortResource");

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
      String title = shortBundle.getString("AboutTitle");
      String msg = shortBundle.getString("AboutMessage");   
      boolean isModal = true;
      int numRows = 16;
      int numColumns = 90;
      int scrollbarVisibility = TextArea.SCROLLBARS_VERTICAL_ONLY;
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











