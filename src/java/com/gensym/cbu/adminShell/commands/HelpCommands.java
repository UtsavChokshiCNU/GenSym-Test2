/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 HelpCommands.java
 *
 */
package com.gensym.cbu.adminShell.commands;

import java.awt.Frame;
import java.awt.TextArea;
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import com.gensym.dlg.AboutDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.message.Resource;
import com.gensym.denali.developer.GUI;
import javax.swing.*;

public final class HelpCommands extends AbstractCommand implements 
StandardDialogClient {
  private DenaliAboutDialog aboutDialog;

  //  final static ImageIcon denaliIcon = new ImageIcon(HelpCommands.class.
  //						    getResource("denali.gif").getFile());

  /** Command to display About dialog */
  public static final String CONTENTS = "Contents";
  public static final String INDEX = "Index";
  public static final String ABOUT = "AboutDeveloperShell";

  private static final String shortResource = "CommandShortResource";
  private static final String longResource = "CommandLongResource";
  private Resource i18n = Resource.getBundle("denali/developer/commands/Errors");
  private Resource shortBundle = Resource.getBundle("denali/developer/commands/CommandShortResource");

  private Frame appFrame;

  public HelpCommands(Frame frame){
    super(new CommandInformation[]{
      new CommandInformation(CONTENTS, true, shortResource, longResource, null, null, 
			     null, true),
      new CommandInformation(INDEX, true, shortResource, longResource, null, null, 
			     null, true),
      new CommandInformation(ABOUT, true, shortResource, longResource, null, null, 
			     null, false)
	});
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
    else if (cmdKey.equals(CONTENTS))
      contentsSelected();
    else if (cmdKey.equals(INDEX))
      indexSelected();
  }

  private void handleAboutTelewindows2Command(){
    if (aboutDialog == null){
      String title = "About Denali";
      // This is kludgy, but it'll probably be replaced before too long. -craig
      String msg = " Denali"+
	"                                                                "+
	"Developer Version 0.1"+
	"                                   "+
	"Gensym (c) 1999";   
      boolean isModal = true;
      int numRows = 1;
      int numColumns = 80;
      //      int scrollbarVisibility = TextArea.SCROLLBARS_VERTICAL_ONLY;
      int scrollbarVisibility = TextArea.SCROLLBARS_NONE;

      TextArea aboutDescription = 
	new TextArea (msg, numRows, numColumns, scrollbarVisibility);
      aboutDescription.setEditable(false);

      JPanel aboutPanel = new JPanel(new BorderLayout());
      //      aboutPanel.add(new JLabel(denaliIcon), GUI.CENTER);
      aboutPanel.add(aboutDescription, GUI.SOUTH);

      aboutDialog = new DenaliAboutDialog(appFrame, title, isModal, 
					  aboutPanel,
					  (StandardDialogClient) this);
    }

    aboutDialog.setVisible (true);
  }

  @Override
  public void dialogDismissed (StandardDialog dlg, int code) {
  }

  private void contentsSelected()
  {
    System.out.println("Hey! Somebody needs to implement help contents");
  }

  private void indexSelected()
  {
    System.out.println("Hey! Somebody needs to implement help index");
  }

  // Stolen from AboutDialog. -cas
  class DenaliAboutDialog extends StandardDialog
  {
    public DenaliAboutDialog (Frame parentFrame, String title,
			      boolean isModal, JPanel aboutPanel,
			      StandardDialogClient client) 
    { 
      super (parentFrame, title, isModal,
	     new String[] {OK_LABEL},
	     new int[] {OK},
	     aboutPanel, 
	     client);
      
      pack ();
    }

    @Override
    public int getButtonAlignment () {
      return CENTER;
    }
  }
}
