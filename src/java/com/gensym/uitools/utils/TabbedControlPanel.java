package com.gensym.uitools.utils;

import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JTabbedPane;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.Component;
import java.awt.Color;
import java.awt.GridBagLayout;

public class TabbedControlPanel extends JPanel {

  protected JTabbedPane tabbedPane;
  protected JPanel statusIndicatorAndButtonsPanel;
  public TabbedControlPanel(Component[] tabComponents,
			    String[] tabNames,
			    JButton[] buttons,
			    Component statusIndicator)
  {
    Color bgColor = Color.lightGray;
    tabbedPane = new JTabbedPane();
    for (int i=0;i<tabComponents.length;i++) {
      Component tabComponent = tabComponents[i];
      tabComponent.setBackground(bgColor);
      tabbedPane.addTab(tabNames[i], tabComponent);
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
    
    statusIndicatorAndButtonsPanel = new JPanel();
    gbl = new GridBagLayout();
    statusIndicatorAndButtonsPanel.setLayout(gbl);
    statusIndicatorAndButtonsPanel.setBackground(bgColor);
    gbc.gridheight = 2;
    gbl.setConstraints (buttonPanel, gbc);
    statusIndicatorAndButtonsPanel.add(buttonPanel);

    gbc.gridheight = gbc.REMAINDER;
    gbc.insets = new Insets (10, 0, 15, 0);
    gbc.fill = GridBagConstraints.NONE;
    gbc.anchor = GridBagConstraints.CENTER;
    gbl.setConstraints (statusIndicator, gbc);
    statusIndicatorAndButtonsPanel.add(statusIndicator);
       
    setBackground(bgColor);
    gbl = new GridBagLayout ();
    setLayout(gbl);

    gbc = new GridBagConstraints();
    gbc.insets = new Insets (5, 10, 10, 10);
    gbc.weightx = 1.0;
    gbc.gridwidth = 2;
    gbc.fill = GridBagConstraints.HORIZONTAL;
    gbc.anchor = GridBagConstraints.NORTH;
    gbc.ipadx=5;

    gbl.setConstraints (tabbedPane, gbc);    
    add(tabbedPane);

    gbc.fill = GridBagConstraints.NONE;
    gbc.insets = new Insets (20,0,0,10);
    gbc.gridwidth = GridBagConstraints.REMAINDER;
    gbc.weightx = 0.0;
    gbc.ipadx=0;
    gbl.setConstraints (statusIndicatorAndButtonsPanel, gbc);
    add(statusIndicatorAndButtonsPanel);
  }
}
