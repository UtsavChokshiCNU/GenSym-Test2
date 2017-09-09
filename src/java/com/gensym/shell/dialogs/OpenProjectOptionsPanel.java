/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 OpenProjectOptionsPanel.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;
import javax.swing.JCheckBox;
import javax.swing.JPanel;
import com.gensym.message.Resource;

public class OpenProjectOptionsPanel extends JPanel {
  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");  
  private JCheckBox conflictsButton;
  private JCheckBox formatsButton;
  
  public OpenProjectOptionsPanel() {
    setName("Options");
    GridBagConstraints gridC = new GridBagConstraints();
    GridBagLayout gridBagLayout = new GridBagLayout();
    setLayout (gridBagLayout);
    
    gridC.insets = new Insets (5, 5, 0, 5);
    gridC.fill = GridBagConstraints.BOTH;
    gridC.weightx = 1.0;
    gridC.gridwidth = GridBagConstraints.REMAINDER; // end row

    createComponents(gridBagLayout, gridC);    
  }

  protected void createComponents(GridBagLayout gridBagLayout,
				  GridBagConstraints gridC) {
    conflictsButton = new JCheckBox(i18n.getString("AutoResolveConflicts"), true);
    gridBagLayout.setConstraints(conflictsButton, gridC);
    add(conflictsButton);

    formatsButton = new JCheckBox(i18n.getString("BringFormatsUpToDate"), false);
    gridBagLayout.setConstraints(formatsButton, gridC);
    add(formatsButton);
  }
   
  public void setAutomaticallyResolveConflicts(boolean autoResolve) {
    conflictsButton.setSelected(autoResolve);
  }

  public boolean getAutomaticallyResolveConflicts() {
    return conflictsButton.isSelected();
  }

  public void setBringFormatsUpToDate(boolean bringFormatsUpToDate) {
    formatsButton.setSelected(bringFormatsUpToDate);
  }

  public boolean getBringFormatsUpToDate() {
    return formatsButton.isSelected();
  }

}
