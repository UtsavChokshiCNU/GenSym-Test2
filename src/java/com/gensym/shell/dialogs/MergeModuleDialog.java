/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MergeModuleDialog.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.Component;
import java.awt.Frame;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;

import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.files.*;
import com.gensym.ntw.files.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.jgi.G2ConnectionInfo;
import com.gensym.jgi.G2Gateway;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.ntw.util.LoadSaveKBTools;
import com.gensym.util.Symbol;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JTabbedPane;
import javax.swing.JFileChooser;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

public class MergeModuleDialog extends OpenProjectDialog {
  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");
  private ConnectionManager connectionManager;

  public MergeModuleDialog (Frame frame, String title, boolean isModal,
			    ConnectionManager connectionManager, StandardDialogClient client) { 
    this (frame, title, isModal, false, connectionManager, client);
  }

  public MergeModuleDialog (Frame frame, String title, boolean isModal, boolean withOptions,
			    ConnectionManager connectionManager, StandardDialogClient client) {  
    super (frame, title, isModal, withOptions, connectionManager.getCurrentConnection(),
	   client);
    chooser.setApproveButtonText(i18n.getString("MergeButtonLabel"));
    //i18n.getString("MergeModuleDialogTitle");
    this.connectionManager = connectionManager;
  }

  @Override
  protected OpenProjectOptionsPanel createOptionsPanel() {
    return new MergeModuleOptionsPanel();
  }
  
  public void setInstallSystemTables(boolean installSystemTables) {
    if (optionsPanel == null)
      throw new IllegalStateException(i18n.getString("noOptionsPanel"));
    ((MergeModuleOptionsPanel)optionsPanel).setInstallSystemTables(installSystemTables);
  }

  public boolean getInstallSystemTables() {
    if (optionsPanel == null)
      throw new IllegalStateException(i18n.getString("noOptionsPanel"));
    return ((MergeModuleOptionsPanel)optionsPanel).getInstallSystemTables();
  }  
  
}

