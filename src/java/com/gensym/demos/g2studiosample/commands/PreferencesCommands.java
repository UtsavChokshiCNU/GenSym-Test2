/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PreferencesCommands.java
 *
 */
package com.gensym.demos.g2studiosample.commands;

import java.awt.Frame;
import java.awt.TextArea;
import java.awt.event.ActionEvent;
import com.gensym.core.ProductManager;
import com.gensym.uitools.utils.Preferences;
import com.gensym.dlg.AboutDialog;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.ui.AbstractCommand;
import com.gensym.ui.CommandInformation;
import com.gensym.message.Resource;
import com.gensym.demos.g2studiosample.Shell;
import com.gensym.demos.g2studiosample.util.PreferencesPanel;

public final class PreferencesCommands extends AbstractCommand {
  public static final String PREFERENCES = "Preferences";
  private static final String shortResource = "PreferencesCommandShortResource";
  private static final String longResource = "PreferencesCommandShortResource";
  private static final String mnemonicRsource = "MnemonicResource";
  private static Resource shortBundle =
  Resource.getBundle("com/gensym/demos/g2studiosample/commands/PreferencesCommandShortResource");
  private Shell shell;

  public PreferencesCommands(Shell shell) {
    super(new CommandInformation[]{
      new CommandInformation(PREFERENCES, true, shortResource, longResource,
			     null,//gif
			     null, 
			     null, false, mnemonicRsource, null)});
    this.shell = shell;
  }

  @Override
  public void actionPerformed(ActionEvent e){
    String cmdKey = e.getActionCommand();
    if (cmdKey == null) return;
    if (cmdKey.equals(PREFERENCES))
      handlePreferences();
  }

  private void handlePreferences() {
    Preferences preferences = shell.getPreferences();        
    PreferencesPanel panel = new PreferencesPanel(preferences);
    PreferencesDialog preferencesDialog = new PreferencesDialog(panel, shell.getCurrentFrame());
    preferencesDialog.setVisible(true);
    if (!preferencesDialog.wasCancelled()) {
      panel.save();//saves to the preferences
      preferences.save();//saves to the preference file; maybe only do when close the shell
    }
  }

  class PreferencesDialog extends StandardDialog {
    PreferencesDialog(PreferencesPanel panel, Frame frame) {
      super(frame,
	    shortBundle.getString(PREFERENCES),
	    true,
	    new String[] {OK_LABEL, CANCEL_LABEL},	    
	    new int[] {OK, CANCEL},
	    panel,
	    null);
    }
  }
}











