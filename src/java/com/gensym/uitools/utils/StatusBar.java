/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 StatusBar.java
 *
 */

package com.gensym.uitools.utils;

import java.awt.Graphics;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Color;
import java.awt.Dimension;
import javax.swing.JPanel;
import javax.swing.JTextField;
import java.awt.BorderLayout;
import java.awt.Image;
import javax.swing.ImageIcon;
import javax.swing.border.BevelBorder;
import java.awt.GridLayout;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;

public class StatusBar extends JPanel implements StatusDisplay {
  private static final Font stdFont = new Font ("SansSerif", Font.PLAIN, 11);
  private JTextField[] textFields;
  private GridBagLayout gbl;
  private TemporaryIndicator tempIndicator;

  public StatusBar(int columnCount){
    setColumnCount(columnCount);
    setBackground(Color.lightGray);
  }

  @Override
  public void setBackground(Color bg) {
    super.setBackground(bg);
    if (textFields != null) {
      for (int i=0;i<textFields.length;i++)
	textFields[i].setBackground(bg);
    }
  }

  @Override
  public void setForeground(Color bg) {
    super.setForeground(bg);
    if (textFields != null) {    
      for (int i=0;i<textFields.length;i++)
	textFields[i].setForeground(bg);
    }
  }  
  
  public StatusBar(int columnCount, boolean useTempInd) {
    this(columnCount);
    if (useTempInd) {
      tempIndicator = new TemporaryIndicator(textFields, Color.lightGray);
      tempIndicator.setRunning(true);
      tempIndicator.start();
    }
  }
    
  public void setConstraints(int column, GridBagConstraints gbc) {
    gbl.setConstraints(textFields[column],gbc);
  }

  public JTextField getTextField(int index) {
    return textFields[index];
  }
  
  public void setColumnCount(int columnCount) {
    removeAll();
    gbl = new GridBagLayout();
    setLayout(gbl);
    GridBagConstraints gbc = new GridBagConstraints ();
    
    gbc.gridwidth = columnCount;
    gbc.weightx = 0.2;
    gbc.fill = GridBagConstraints.HORIZONTAL;//NONE;
    gbc.anchor = GridBagConstraints.WEST;

    textFields = new JTextField[columnCount];
    for (int i=0;i<columnCount;i++) {
      JTextField textField = new JTextField();
      textField.setBorder(new BevelBorder(BevelBorder.LOWERED));
      textField.setMargin(new java.awt.Insets(0,10,0,10));
      //textField.setHorizontalAlignment(textField.CENTER);
      textField.setFont(stdFont);
      textField.setEditable(false);
      textFields[i]= textField;
      textField.setBackground(Color.lightGray);
      gbl.setConstraints(textField, gbc);      
      add(textField);
    }
  }

  private static final long indicatorTime = 400;

  public void flashColor() {
    if (tempIndicator != null)
      tempIndicator.indicate(Color.green, indicatorTime);
  }
  
  @Override
  public void setStatus(String msg, int regionIndex){
    textFields[regionIndex].setText(msg);
    repaint();
  }


}
