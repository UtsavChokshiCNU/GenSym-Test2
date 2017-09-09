/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 RenameModuleDialog.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.Component;
import java.awt.Frame;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import java.util.Vector;

import com.gensym.classes.Module;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.ntw.util.BrowserSymbols;
import com.gensym.ntw.util.ClassInstanceData;
import com.gensym.ntw.util.ModuleBrowserScrollPane;
import com.gensym.ntw.util.TreeNodeChangedEvent;
import com.gensym.ntw.util.TreeNodeChangedListener;
import com.gensym.util.Sorter;
import com.gensym.util.Symbol;

import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.JTextField;
import com.gensym.ntw.util.ModuleSelectionPanel;
import java.awt.BorderLayout;

public class RenameModuleDialog extends StandardDialog {
  //private ClassInstanceData changedUserObject;
  private ModuleSelectionPanel moduleSelectionPanel;
  private JTextField textField;
  
  public RenameModuleDialog (Frame frame, String title, boolean isModal,
			     ConnectionManager connectionManager, StandardDialogClient client) { 
    super (frame, title, isModal,
	   new String[] {OK_LABEL, CANCEL_LABEL},
	   new int[] {OK, CANCEL},
	   null, client);
    TwAccess cxn = connectionManager.getCurrentConnection();
    textField = new JTextField();
    moduleSelectionPanel = new ModuleSelectionPanel(cxn);
    JPanel panel = new JPanel();
    panel.setLayout(new BorderLayout());
    JPanel renamePanel = new JPanel();
    renamePanel.setLayout(new BorderLayout());
    renamePanel.add(new JLabel("New Name:"), BorderLayout.WEST);
    renamePanel.add(textField);
    panel.add(renamePanel, BorderLayout.NORTH);
    panel.add(moduleSelectionPanel);
    getContentPane().add(panel);
    pack();
  }

  public Symbol getSelectedModule() {
    return moduleSelectionPanel.getSelectedModule();
  }

  public void setSelectedModule(Symbol moduleName) {
    moduleSelectionPanel.setSelectedModule(moduleName);
  }

  public String getNewValue() {
    return textField.getText().trim().toUpperCase();
  }

  /*public void setNewValue(String newValue) {
  }
  public ClassInstanceData getChangedUserObject() {
  }
  public void setChangedUserObject(ClassInstanceData data) {
  }*/
}



