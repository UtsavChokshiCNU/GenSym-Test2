/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SaveModuleDialog.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.Frame;
import java.awt.Component;
import com.gensym.util.Symbol;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.ntw.util.ModuleSelectionPanel;
import com.gensym.ntw.TwAccess;

public class SaveModuleDialog extends SaveProjectDialog {
  private ModuleSelectionPanel moduleSelectionPanel;
  
  public SaveModuleDialog (Frame frame, String title, boolean isModal,
			   ConnectionManager connectionManager, StandardDialogClient client) { 
    this (frame, title, isModal, false, connectionManager, client);
  }

  public SaveModuleDialog (Frame frame, String title, boolean isModal, boolean withOptions,
			   ConnectionManager connectionManager, StandardDialogClient client) {  
    super (frame, title, isModal, withOptions,
	   connectionManager.getCurrentConnection(),
	   client);
  }

  @Override
  protected void createOptionsPanels(TwAccess cxn) {
    moduleSelectionPanel = new ModuleSelectionPanel(cxn);
    chooser.addOptionsPanel(moduleSelectionPanel, null);    
    super.createOptionsPanels(cxn);    
  }
  
  public Symbol getSelectedModule() {
    return moduleSelectionPanel.getSelectedModule();
  }

  public void setSelectedModule(Symbol moduleName) {
    moduleSelectionPanel.setSelectedModule(moduleName);
  }

}

