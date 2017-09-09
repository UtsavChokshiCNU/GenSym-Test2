/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 SaveSnapshotDialog.java
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

import com.gensym.classes.Kb;
import com.gensym.classes.Module;
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

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.JTextField;
import javax.swing.JFileChooser;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;

public class SaveSnapshotDialog extends StandardDialog {

  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");

  private Frame frame;
  private ConnectionManager connectionManager;

  private Component savePanelOrTabbedPane;

  private String g2Path;
  private URLFile urlFile;

  private Boolean SHOW_PROGRESS = Boolean.FALSE;
  private Boolean SAVE_WORKSPACE_LAYOUT = Boolean.TRUE;

  public SaveSnapshotDialog (Frame frame, String title, boolean isModal,
			     ConnectionManager connectionManager, StandardDialogClient client) {
    this (frame, title, isModal, false, connectionManager, client);
  }

  public SaveSnapshotDialog (Frame frame, String title, boolean isModal, boolean withOptions,
			     ConnectionManager connectionManager, StandardDialogClient client) {
    super (frame, title, isModal,
	   new String[] {OK_LABEL, CANCEL_LABEL},
	   new int[] {OK, CANCEL},
	   new SaveSnapshotPanel(frame, connectionManager, withOptions), client);

    this.frame = frame;
    this.connectionManager = connectionManager;
    savePanelOrTabbedPane =  getDialogComponent();
    pack ();
  }

  public URLFile getURLFile() {
    return urlFile;
  }

  public void setURLFile(URLFile urlFile) {
    this.urlFile = urlFile;
  }

  public String getG2FileSpecification() {
    this.g2Path = ((SaveSnapshotPanel)getDialogComponent()).kbTextField.getText();
    return g2Path;
  }

  public void setG2FileSpecification(String path) {
    this.g2Path = path;
    ((SaveSnapshotPanel)getDialogComponent()).kbTextField.setText(this.g2Path);
  }

  public void setShowProgress(Boolean showProgress) {
    SHOW_PROGRESS = showProgress;
  }

  public Boolean getShowProgress() {
    return SHOW_PROGRESS;
  }

  public void setSaveWorkspaceLayout(Boolean saveWorkspaceLayout) {
    SAVE_WORKSPACE_LAYOUT = saveWorkspaceLayout;
  }

  public Boolean getSaveWorkspaceLayout() {
    return SAVE_WORKSPACE_LAYOUT;
  }
}

class SaveSnapshotPanel extends JPanel {

  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");

  Frame frame;
  ConnectionManager connectionManager;

  DialogIcons icons = new DialogIcons();

  JFileChooser fileDlg;

  JButton    chooseButton;
  JLabel     promptLabel;
  public JTextField kbTextField;

  public SaveSnapshotPanel(Frame f, ConnectionManager cxnMgr, boolean withOptions) {
    frame = f;
    connectionManager = cxnMgr;

    if (withOptions) {
      executeBuildSaveSnapshotTabbedPane();
    } else {
      executeBuildSaveSnapshotPanel(null);
    }
  }

  private void executeBuildSaveSnapshotPanel(JPanel thePanel) {

    GridBagConstraints gridC = new GridBagConstraints();
    GridBagLayout gridBagLayout = new GridBagLayout();
    if (thePanel != null)
      thePanel.setLayout (gridBagLayout);
    else
      setLayout(gridBagLayout);

    gridC.insets = new Insets (5, 5, 0, 5);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 1.0;
    gridC.gridwidth = GridBagConstraints.REMAINDER; // end row

    promptLabel = new JLabel(i18n.getString("PathPrompt"));
    gridBagLayout.setConstraints(promptLabel, gridC);
    if (thePanel != null)
      thePanel.add(promptLabel);
    else
      add(promptLabel);

    gridC.gridwidth = GridBagConstraints.RELATIVE;

    kbTextField = new JTextField("", 25);
    kbTextField.getDocument().addDocumentListener(new DocumentListener() {
      @Override
      public void insertUpdate(DocumentEvent e) {
      }
      @Override
      public void removeUpdate(DocumentEvent e) {}
      @Override
      public void changedUpdate(DocumentEvent e) {}
    });
    gridBagLayout.setConstraints(kbTextField, gridC);
    if (thePanel != null)
      thePanel.add(kbTextField);
    else
      add(kbTextField);

    gridC.gridwidth = GridBagConstraints.REMAINDER;

    chooseButton = new JButton(i18n.getString("ChooseButtonLabel"));
    gridBagLayout.setConstraints(chooseButton, gridC);
    if (thePanel != null)
      thePanel.add(chooseButton);
    else
      add(chooseButton);
    chooseButton.addActionListener (new ActionListener (){
      @Override
      public void actionPerformed (ActionEvent event){
	String file;
	G2ConnectionInfo cxnInfo = ((G2Gateway)connectionManager.getCurrentConnection()).getG2ConnectionInfo();
	String host = cxnInfo.getHost();
	String port = cxnInfo.getPort();
        // Though a bit odd to do this the way its done but probable
        // setting defPath twice could be that at times host and port
        // information is not returned. Thus to handle such side effect
        // we have the defPath set the way it is done.
        String defPath = kbTextField.getText();
        defPath = "g2://"+host+":"+port+"/serverFileSystem/";
        G2ServerFile  g2File  = new G2ServerFile(defPath, FileType.SharedGenericFile);

	if (fileDlg == null) {
          T2URLDirectoryModel model   = new T2URLDirectoryModel(false, true, false, null, null);
          URLFileSystemView   sysView = new URLFileSystemView(model);

          // Create file chooser
          fileDlg = new JFileChooser (defPath, sysView);
        }

	String txt = i18n.getString("FileSearchString");
	fileDlg.setApproveButtonText(i18n.getString("SaveButtonLabel"));

        if (g2File.isFile())
  	  fileDlg.setSelectedFile(g2File);

	int dialogStatus = fileDlg.showDialog(frame, i18n.getString("SaveFileDialogTitle"));

	URLFile result = (URLFile)fileDlg.getSelectedFile();

	if (dialogStatus == JFileChooser.APPROVE_OPTION) {
	  String path = LoadSaveKBTools.getG2FileSpecificationFromURL(connectionManager.getCurrentConnection(), result);
	  kbTextField.setText(path);
	}
      }
    });
  }

  private void executeBuildSaveSnapshotTabbedPane() {
    JPanel savePanel = new JPanel();
    executeBuildSaveSnapshotPanel(savePanel);
    JPanel optionsPanel = new SaveSnapshotOptionsPanel();

    JTabbedPane tabbedPane = new JTabbedPane();
    tabbedPane.addTab("Path", icons.saveIcon, savePanel);
    tabbedPane.addTab("Options", null, optionsPanel);
    tabbedPane.setSelectedIndex(0);
    add(tabbedPane);
  }
}

class SaveSnapshotOptionsPanel extends JPanel {

  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");

  JCheckBox showProgressButton;
  JCheckBox saveWorkspaceLayoutButton;

  public SaveSnapshotOptionsPanel() {
    GridBagConstraints gridC = new GridBagConstraints();
    GridBagLayout gridBagLayout = new GridBagLayout();
    setLayout (gridBagLayout);

    gridC.insets = new Insets (5, 5, 0, 5);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 1.0;
    gridC.gridwidth = GridBagConstraints.REMAINDER; // end row

    showProgressButton = new JCheckBox(i18n.getString("ShowProgressDisplay"), false);
    showProgressButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
	Component parent = getParent();
	while ((parent != null) && (!(parent instanceof SaveSnapshotDialog))) {
	  parent = parent.getParent();
	}
	((SaveSnapshotDialog)parent).setShowProgress(new Boolean(showProgressButton.isSelected()));
      }
    });
    gridBagLayout.setConstraints(showProgressButton, gridC);
    add(showProgressButton);

    saveWorkspaceLayoutButton = new JCheckBox(i18n.getString("SaveWorkspaceLayout"), true);
    saveWorkspaceLayoutButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
	Component parent = getParent();
	while ((parent != null) && (!(parent instanceof SaveSnapshotDialog))) {
	  parent = parent.getParent();
	}
	((SaveSnapshotDialog)parent).setSaveWorkspaceLayout(new Boolean(saveWorkspaceLayoutButton.isSelected()));
      }
    });
    gridBagLayout.setConstraints(saveWorkspaceLayoutButton, gridC);
    add(saveWorkspaceLayoutButton);
  }
}
