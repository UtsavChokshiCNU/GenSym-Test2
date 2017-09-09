/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2WorkspacesPanel.java
 *
 *  Description:
 *
 *
 *	 Author:
 *		Todd O'Brien		Feb/98
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.g2studio.dialogs;


import java.awt.Button;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.List;
import com.gensym.classes.Module;
import com.gensym.classes.ModuleInformation;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.uiutil.StandardGridBagPanel;
import com.gensym.util.Symbol;

/**
 */
public class G2WorkspacesPanel extends StandardGridBagPanel
{
  private List list;
  private Button newButton, editButton, deleteButton, goToButton;
  private static Resource shortBundle = Resource.getBundle("com/gensym/g2studio/dialogs/CommandShortResource");

  /**
   */
  public G2WorkspacesPanel(Module module)
  {
    super();

    setLayout(gridBagLayout);
    GridBagConstraints constraints = new GridBagConstraints();
    constraints.fill = GridBagConstraints.BOTH;
    constraints.insets  = new Insets (10, 10, 10, 10);

    constraints.weightx = 1;
    constraints.weighty = 1;
    constraints.gridwidth = GridBagConstraints.RELATIVE;
    constraints.gridheight = 5;
    addComponent(list = new List(), constraints);

    constraints.weightx = 0;
    constraints.weighty = 0;
    constraints.gridwidth = GridBagConstraints.REMAINDER;
    constraints.gridheight = 1;
    constraints.insets  = new Insets (10, 0, 0, 10);

    addComponent(newButton = new Button(shortBundle.getString("G2WorkspacesPanelNewButtonLabel")), constraints);
   
    addComponent(editButton = new Button(shortBundle.getString("G2WorkspacesPanelEditButtonLabel")), constraints);
   
    addComponent(deleteButton = new Button(shortBundle.getString("G2WorkspacesPanelDeleteButtonLabel")), constraints);
   
    addComponent(goToButton = new Button(shortBundle.getString("G2WorkspacesPanelGoToButtonLabel")), constraints);
   
  }
  
}


