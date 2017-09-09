/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 HelpCommands.java
 *
 */
package com.gensym.demos.sequoia.course;

import java.awt.Frame;
import java.awt.TextArea;
import java.awt.event.ActionEvent;
import com.gensym.dlg.AboutDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.message.Resource;

public class HelpCommands extends AbstractCommand implements StandardDialogClient {


  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("com/gensym/shell/commands/Errors");
  private Resource shortBundle = Resource.getBundle("com/gensym/demos/sequoia/course/CommandShortResource");

  private static final String CONTENTS = "Contents";
  private static final String ABOUT = "About";

  private Frame frame;
  private AboutDialog aboutDialog;

  public HelpCommands(Frame frame) {
    super(new CommandInformation[]{
      new CommandInformation(CONTENTS, true, shortResource, longResource, null,
			     null, null, false),
      new CommandInformation(ABOUT, true, shortResource, longResource, null,
			     null, null, false)});
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

    if (cmdKey.equals(CONTENTS))
      handleContentsCommand();
    else if (cmdKey.equals(ABOUT))
      handleAboutCommand();
  }

  private void handleContentsCommand() {
    System.out.println("NYI: handleContentsCommand");
  }

  /*
   * This method handles the action of the About command,
   * which simply creates an AboutDialog, using the specified
   * title, message, scroll bars, etc.
   */
  private void handleAboutCommand(){
    if (aboutDialog == null) {
      String title = shortBundle.getString("AboutDemoTitle");
      String msg = shortBundle.getString("AboutDemoMessage");   
      boolean isModal = true;
      int numRows = 16;
      int numColumns = 50;
      int scrollbarVisibility = TextArea.SCROLLBARS_VERTICAL_ONLY;
      aboutDialog = new AboutDialog(frame, title, isModal, msg, 
				    numRows, numColumns, scrollbarVisibility,
				    (StandardDialogClient) this);
    }

    aboutDialog.setVisible (true);
  }

  @Override
  public void dialogDismissed (StandardDialog dlg, int code) {
  }
}











