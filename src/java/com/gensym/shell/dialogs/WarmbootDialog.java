/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WarmbootDialog.java
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

public class WarmbootDialog extends StandardDialog {

  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");

  private Frame frame;
  private ConnectionManager connectionManager;

  private Component openPanelOrTabbedPane;

  private String g2Path;
  private URLFile urlFile;

  private Boolean RUN_IN_CATCH_UP_MODE = Boolean.FALSE;

  public WarmbootDialog (Frame frame, String title, boolean isModal,
			 ConnectionManager connectionManager, StandardDialogClient client) {
    this (frame, title, isModal, false, connectionManager, client);
  }

  public WarmbootDialog (Frame frame, String title, boolean isModal, boolean withOptions,
			 ConnectionManager connectionManager, StandardDialogClient client) {
    super (frame, title, isModal,
	   new String[] {OK_LABEL, CANCEL_LABEL},
	   new int[] {OK, CANCEL},
	   new WarmbootPanel(frame, connectionManager, withOptions), client);

    this.frame = frame;
    this.connectionManager = connectionManager;
    openPanelOrTabbedPane =  getDialogComponent();
    pack ();
  }

  public void setRunInCatchUpMode(Boolean catchUp) {
    RUN_IN_CATCH_UP_MODE = catchUp;
  }

  public Boolean getRunInCatchUpMode() {
    return RUN_IN_CATCH_UP_MODE;
  }

  public URLFile getURLFile() {
    return urlFile;
  }

  public void setURLFile(URLFile urlFile) {
    this.urlFile = urlFile;
  }

  public String getG2FileSpecification() {
    this.g2Path = ((WarmbootPanel)getDialogComponent()).kbTextField.getText();
    return g2Path;
  }

  public void setG2FileSpecification(String path) {
    this.g2Path = path;
    ((WarmbootPanel)getDialogComponent()).kbTextField.setText(this.g2Path);
  }
}

class WarmbootPanel extends JPanel {

  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");

  Frame frame;
  ConnectionManager connectionManager;

  DialogIcons icons = new DialogIcons();

  JFileChooser fileDlg;

  JButton    chooseButton;
  JLabel     promptLabel;
  JTextField kbTextField;

  public WarmbootPanel(Frame f, ConnectionManager cxnMgr, boolean withOptions) {
    frame = f;
    connectionManager = cxnMgr;

    if (withOptions) {
      executeBuildWarmbootTabbedPane();
    } else {
      executeBuildWarmbootPanel(null);
    }
  }

  private void executeBuildWarmbootPanel(JPanel thePanel) {

    GridBagConstraints gridC = new GridBagConstraints();
    GridBagLayout gridBagLayout = new GridBagLayout();
    if (thePanel != null)
      thePanel.setLayout (gridBagLayout);
    else
      setLayout (gridBagLayout);

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
	//JFileChooser fileDlg;
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
	fileDlg.setApproveButtonText(i18n.getString("WarmbootButtonLabel"));

        if (g2File.isFile())
  	  fileDlg.setSelectedFile(g2File);

	int dialogStatus = fileDlg.showDialog(frame, i18n.getString("WarmbootDialogTitle"));

	URLFile result = (URLFile)fileDlg.getSelectedFile();

	if (dialogStatus == JFileChooser.APPROVE_OPTION) {
	  String path = LoadSaveKBTools.getG2FileSpecificationFromURL(connectionManager.getCurrentConnection(), result);

	  kbTextField.setText(path);
	}
      }
    });
  }

  private void executeBuildWarmbootTabbedPane() {
    JPanel openPanel = new JPanel();
    executeBuildWarmbootPanel(openPanel);
    JPanel optionsPanel = new WarmbootOptionsPanel();

    JTabbedPane tabbedPane = new JTabbedPane();
    tabbedPane.addTab("Snapshot", icons.openIcon, openPanel);
    tabbedPane.addTab("Options", null, optionsPanel);
    tabbedPane.setSelectedIndex(0);
    add(tabbedPane);
  }
}

class WarmbootOptionsPanel extends JPanel {

  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");

  JCheckBox catchUpButton;

  public WarmbootOptionsPanel() {

    GridBagConstraints gridC = new GridBagConstraints();
    GridBagLayout gridBagLayout = new GridBagLayout();
    setLayout (gridBagLayout);

    gridC.insets = new Insets (5, 5, 0, 5);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 1.0;
    gridC.gridwidth = GridBagConstraints.REMAINDER; // end row

    catchUpButton = new JCheckBox(i18n.getString("RunInCatchUpMode"), true);
    catchUpButton.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
	Component parent = getParent();
	while ((parent != null) && (!(parent instanceof WarmbootDialog))) {
	  parent = parent.getParent();
	}
	((WarmbootDialog)parent).setRunInCatchUpMode(new Boolean(catchUpButton.isSelected()));
      }
    });
    gridBagLayout.setConstraints(catchUpButton, gridC);
    add(catchUpButton);
  }
}
