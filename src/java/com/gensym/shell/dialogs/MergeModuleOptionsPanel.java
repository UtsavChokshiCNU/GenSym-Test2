/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 MergeModuleOptionsPanel.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import javax.swing.JCheckBox;
import com.gensym.message.Resource;

public class MergeModuleOptionsPanel extends OpenProjectOptionsPanel {
  private static Resource i18n = Resource.getBundle("com/gensym/shell/dialogs/Messages");  
  private JCheckBox installSystemTablesButton;
  
  @Override
  protected void createComponents(GridBagLayout gridBagLayout,
				  GridBagConstraints gridC) {
    super.createComponents(gridBagLayout, gridC);

    installSystemTablesButton = new JCheckBox(i18n.getString("InstallSystemTables"), false);    
    gridBagLayout.setConstraints(installSystemTablesButton, gridC);
    add(installSystemTablesButton);
  }

  public void setInstallSystemTables(boolean installSystemTables) {
    installSystemTablesButton.setSelected(installSystemTables);
  }

  public boolean getInstallSystemTables() {
    return installSystemTablesButton.isSelected();
  }
  
}
