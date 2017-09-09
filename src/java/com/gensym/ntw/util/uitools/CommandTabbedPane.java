
/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 CommandTabbedPane.java
 *
 */
package com.gensym.ntw.util.uitools;

import java.awt.BorderLayout;
import java.awt.Component;
import java.awt.FlowLayout;

import com.gensym.ui.Command;
import com.gensym.ui.toolbar.ToolBar;

import javax.swing.ImageIcon;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;

public class CommandTabbedPane extends JTabbedPane {

  private JTabbedPane tabbedPane;

  public CommandTabbedPane(Command[] commandHandlers) {
    //setLayout(new BorderLayout());

    ToolBar toolbar;
    JPanel tbPanel;
    Component[] components;
    String[] keys;
    ImageIcon icon;
    for (int i=0; i<commandHandlers.length; i++) {
      toolbar = new ToolBar();
      toolbar.add(commandHandlers[i]);
      components = toolbar.getComponents();
      tbPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
      for (int j=0; j<components.length; j++) {
	tbPanel.add(components[j]);
      }

      keys = commandHandlers[i].getKeys();
      icon = new ImageIcon(commandHandlers[i].getIcon(keys[0], Command.SMALL_ICON));
      
      addTab(null, icon, tbPanel);
    }
  }
}






