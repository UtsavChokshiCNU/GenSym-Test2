/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 FontDialog.java
 *
 */
package com.gensym.g2studio.dialogs;

import java.awt.Font;
import java.awt.Frame;
import java.awt.Insets;
import java.awt.Panel;
import com.gensym.shell.dialogs.FontPanel;
import com.gensym.dlg.CommandConstants;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;

public class FontDialog extends StandardDialog implements CommandConstants {

  private FontPanel fontPanel = null;
  private boolean wasCancelled = false;
 
  public FontDialog (Frame parent, String title, boolean isModal, String[] buttonNames, int[] buttonCodes, StandardDialogClient client) {
    super (parent, title, isModal,buttonNames, buttonCodes,
	   new FontPanel(FontPanel.NO_BUTTONS),
	   //new FontPanel(FontPanel.OK+FontPanel.APPLY+FontPanel.CANCEL+FontPanel.DISMISS),
	   client);

    fontPanel = (FontPanel)getDialogComponent();
  }

  @Override
  public Insets getInsets () {
    //return new Insets (15, 20, 15, 20);
    return new Insets (20, 10, 0, 10);
  }

  public FontPanel getFontPanel(){
    return fontPanel;
  }
}
