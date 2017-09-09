/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DeleteModuleDialog.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.Frame;
import javax.swing.JTabbedPane;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.message.Resource;
import com.gensym.util.Symbol;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.ModuleSelectionPanel;

public class DeleteModuleDialog extends StandardDialog {
  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");
  private static final Symbol UNSPECIFIED_ = Symbol.intern("UNSPECIFIED");  
  private DeleteModuleOptionsPanel optionsPanel;
  private ModuleSelectionPanel moduleSelectionPanel;

  public DeleteModuleDialog (Frame frame, String title, boolean isModal,
			     ConnectionManager connectionManager, StandardDialogClient client) { 
    this (frame, title, isModal, false, connectionManager, client);
  }

  public DeleteModuleDialog (Frame frame, String title, boolean isModal, boolean withOptions,
			     ConnectionManager connectionManager, StandardDialogClient client) {  
    super (frame, title, isModal,
	   new String[] {OK_LABEL, CANCEL_LABEL},
	   new int[] {OK, CANCEL},
	   null, client);    
    TwAccess cxn = connectionManager.getCurrentConnection();
    
    JTabbedPane tabbedPane = new JTabbedPane();
    moduleSelectionPanel = new ModuleSelectionPanel(cxn);
    tabbedPane.addTab(i18n.getString("ModuleSelection"),
		      DialogIcons.newIcon,
		      moduleSelectionPanel);
    if (withOptions) {
      optionsPanel = new DeleteModuleOptionsPanel();
      tabbedPane.addTab(i18n.getString("DeleteModuleOptions"), null, optionsPanel);
    }
    tabbedPane.setSelectedIndex(0);
    getContentPane().add(tabbedPane);
    pack();
  }
 
  public Symbol getSelectedModule() {
    return moduleSelectionPanel.getSelectedModule();
  }

  public void setSelectedModule(Symbol moduleName) {
    if (moduleName == null)
      moduleName = UNSPECIFIED_;
    moduleSelectionPanel.setSelectedModule(moduleName);
  }

  public boolean getDeleteAssociatedWorkspaces() {
    return optionsPanel.getDeleteAssociatedWorkspaces();
  }

  public void setDeleteAssociatedWorkspaces(boolean deleteThem) {
    optionsPanel.setDeleteAssociatedWorkspaces(deleteThem);
  }

}











