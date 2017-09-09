
/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassChooserTabPaneDialog.java
 *
 *
 */
package com.gensym.ntw.util;

import java.awt.Frame;
import java.awt.Component;

import java.util.Vector;

import javax.swing.JRadioButton;
import javax.swing.JTabbedPane;

import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.message.Resource;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;

public class ClassChooserTabPaneDialog extends StandardDialog {

  private static final Resource i18n = Resource.getBundle("com.gensym.ntw.util.Messages");

  public ClassChooserTabPaneDialog(Frame frame, boolean modal, TwAccess connection, String[] tabNames,
                                   Component[] tabComponents, StandardDialogClient client, int selectedTab,
                                   Vector iconSizes, Vector buttonStyles) {
    super(frame, i18n.getString("ClassChooserTitle"), modal,
	  new String[]{OK_LABEL, CANCEL_LABEL, APPLY_LABEL}, new int[]{OK, CANCEL, APPLY},
          new ClassChooserTabControlPanel(connection, tabNames, tabComponents, selectedTab, iconSizes, buttonStyles), client);
    setDefaultButton(OK);
    setCancelButton(CANCEL);
  }

  public Symbol[] getSelection(int tabIndex){
    return ((ClassChooserTabControlPanel)getDialogComponent()).getSelection(tabIndex);
  }

  public JTabbedPane getClassChooserTabPane () {
    return ((ClassChooserTabControlPanel)getDialogComponent()).getTabbedPane();
  }

  public void disableRadioButtons(){
    JRadioButton[] radButtons = ((ClassChooserTabControlPanel)getDialogComponent()).getRadioButtons();
    for (int i=0; i<radButtons.length; i++)
      radButtons[i].setEnabled(false);
  }
  
  @Override
  protected int getButtonAlignment(){
    return CENTER;
  }

  public Vector getIconSizes() {
    return ((ClassChooserTabControlPanel)getDialogComponent()).getIconSizes();
  }

  public Vector getButtonStyles() {
    return ((ClassChooserTabControlPanel)getDialogComponent()).getButtonStyles();
  }
}
