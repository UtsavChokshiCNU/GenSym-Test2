/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BasicSaveOptionsPanel.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import javax.swing.JCheckBox;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.border.EmptyBorder;
import com.gensym.message.Resource;
import com.gensym.ntw.TwAccess;

public class BasicSaveOptionsPanel extends JPanel {
  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");  
  private JCheckBox showProgressButton;
  private JCheckBox saveWorkspaceLayoutButton;
  private JCheckBox saveRequiredModulesButton;
  
  public BasicSaveOptionsPanel() {
    setName("Options");    
    GridBagConstraints gridC = new GridBagConstraints();
    GridBagLayout gridBagLayout = new GridBagLayout();
    setLayout (gridBagLayout);
    
    gridC.insets = new Insets (5, 5, 0, 5);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 1.0;
    gridC.gridwidth = GridBagConstraints.REMAINDER; // end row

    showProgressButton =
      new JCheckBox(i18n.getString("ShowProgressDisplay"), true);
    gridBagLayout.setConstraints(showProgressButton, gridC);
    add(showProgressButton);

    saveWorkspaceLayoutButton =
      new JCheckBox(i18n.getString("SaveWorkspaceLayout"), true);
    gridBagLayout.setConstraints(saveWorkspaceLayoutButton, gridC);
    add(saveWorkspaceLayoutButton);

    saveRequiredModulesButton =
      new JCheckBox(i18n.getString("SaveRequiredModules"), false);
    gridBagLayout.setConstraints(saveRequiredModulesButton, gridC);
    add(saveRequiredModulesButton);
  }

  public void setShowProgress(boolean showProgress) {
    showProgressButton.setSelected(showProgress);
  }
  
  public boolean getShowProgress() {
    return showProgressButton.isSelected();
  }
  
  public void setSaveWorkspaceLayout(boolean saveWorkspaceLayout) {
    saveWorkspaceLayoutButton.setSelected(saveWorkspaceLayout);
  }

  public boolean getSaveWorkspaceLayout() {
    return saveWorkspaceLayoutButton.isSelected();
  }

  public void setSaveRequiredModules(boolean saveRequiredModules) {
    saveRequiredModulesButton.setSelected(saveRequiredModules);
  }

  public boolean getSaveRequiredModules() {
    return saveRequiredModulesButton.isSelected();
  }
}
