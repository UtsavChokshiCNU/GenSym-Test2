/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DeleteModuleDialog.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import com.gensym.message.Resource;
import javax.swing.JCheckBox;
import javax.swing.JPanel;

public class DeleteModuleOptionsPanel extends JPanel {
  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");
  private JCheckBox deleteAssociatedButton;

  public DeleteModuleOptionsPanel() {
    GridBagConstraints gridC = new GridBagConstraints();
    GridBagLayout gridBagLayout = new GridBagLayout();
    setLayout (gridBagLayout);
    gridC.insets = new Insets (5, 5, 0, 5);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 1.0;
    gridC.gridwidth = GridBagConstraints.REMAINDER; // end row
    deleteAssociatedButton = new JCheckBox(i18n.getString("DeleteAssociatedWorkspaces"), true);
    gridBagLayout.setConstraints(deleteAssociatedButton, gridC);
    add(deleteAssociatedButton);
  }

  public boolean getDeleteAssociatedWorkspaces() {
    return deleteAssociatedButton.isSelected();
  }

  public void setDeleteAssociatedWorkspaces(boolean deleteThem) {
    deleteAssociatedButton.setSelected(deleteThem);
  }
  
  
}
