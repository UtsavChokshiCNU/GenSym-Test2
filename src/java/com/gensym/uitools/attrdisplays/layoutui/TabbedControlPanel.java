package com.gensym.uitools.attrdisplays.layoutui;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Insets;

public class TabbedControlPanel extends JPanel {

  protected JTabbedPane tabbedPane;

  public TabbedControlPanel(JButton[] buttons) {
    this ( null, null, buttons);
  }

  public TabbedControlPanel(Component[] tabComponents,
			    String[] tabNames,
			    JButton[] buttons)
  {
    Color bgColor = Color.lightGray;
    tabbedPane = new JTabbedPane();
    if (tabComponents != null) {
      for (int i=0;i<tabComponents.length;i++) {
	Component tabComponent = tabComponents[i];
	tabComponent.setBackground(bgColor);
	tabbedPane.addTab(tabNames[i], tabComponent);
      }
    }
    
    JPanel buttonPanel = new JPanel();
    GridBagLayout gbl = new GridBagLayout ();
    buttonPanel.setLayout(gbl);
    buttonPanel.setBackground(bgColor);
    GridBagConstraints gbc = new GridBagConstraints ();
    gbc.insets = new Insets (5, 0, 0, 0);
    gbc.gridy = GridBagConstraints.RELATIVE;
    gbc.weightx = 1.0;
    gbc.weighty = 0.5;
    gbc.gridwidth = GridBagConstraints.REMAINDER;
    gbc.fill = GridBagConstraints.HORIZONTAL;
    gbc.anchor = GridBagConstraints.WEST;

    for (int buttonCount=buttons.length;buttonCount>0;buttonCount--) {
      gbc.gridheight = (buttonCount == 1)?GridBagConstraints.REMAINDER:buttonCount;
      JButton button = buttons[buttons.length - buttonCount];
      gbl.setConstraints (button, gbc);
      buttonPanel.add(button);
    }
    
    setBackground(bgColor);
    gbl = new GridBagLayout ();
    setLayout(gbl);

    gbc = new GridBagConstraints();
    gbc.insets = new Insets (5, 10, 10, 10);
    gbc.weightx = 1.0;
    gbc.gridwidth = 2;
    gbc.fill = GridBagConstraints.BOTH;
    gbc.anchor = GridBagConstraints.NORTH;
    gbc.ipadx=5;

    gbl.setConstraints (tabbedPane, gbc);    
    add(tabbedPane);

    gbc.fill = GridBagConstraints.NONE;
    gbc.insets = new Insets (20,0,0,10);
    gbc.gridwidth = GridBagConstraints.REMAINDER;
    gbc.weightx = 0.0;
    gbc.ipadx=0;
    gbl.setConstraints (buttonPanel, gbc);
    add(buttonPanel);
  }

  public JTabbedPane getTabbedPane() {
    return tabbedPane;
  }
}

