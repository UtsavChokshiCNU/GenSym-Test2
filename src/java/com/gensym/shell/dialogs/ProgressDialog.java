/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ProgressDialog.java
 *
 */
package com.gensym.shell.dialogs;

import java.awt.Dialog;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Insets;
import java.awt.Point;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JProgressBar;

public class ProgressDialog extends Dialog {
  private JProgressBar progressBar;
  private JLabel progressLabel;

  public ProgressDialog(Frame frame, String title, String message){
    super(frame, title, false);
    progressBar = new JProgressBar();
    JPanel progressPanel = new JPanel(){
      @Override
      public Insets getInsets() {

	return new Insets(40,30,20,30);
      }
    };
    progressPanel.setLayout(new BoxLayout(progressPanel, BoxLayout.Y_AXIS));
    add(progressPanel, java.awt.BorderLayout.CENTER);
    Dimension d = new Dimension(400, 20);
    progressLabel = new JLabel(message);
    progressLabel.setMaximumSize(d);
    progressLabel.setPreferredSize(d);
    progressLabel.setLabelFor(progressBar);
    progressPanel.add(progressLabel);
    progressPanel.add(Box.createRigidArea(new Dimension(1,20)));
    progressPanel.add(progressBar);
    pack();
  }

  public JProgressBar getProgressBar(){
    return progressBar;
  }

  public JLabel getProgressLabel(){
    return progressLabel;
  }

  @Override
  public void setVisible (boolean showQ) {  // Fixes bug under Win95
    if (showQ) {
      Dimension frameSize = getParent().getSize();
      Point     frameLoc  = getParent().getLocation();
      Dimension mySize    = getSize();
      int       x,y;
      
      x = Math.max(0, frameLoc.x + (frameSize.width/2) -(mySize.width/2));
      y = Math.max(0,frameLoc.y + (frameSize.height/2)-(mySize.height/2));
     
      setBounds (x, y, mySize.width, mySize.height);
    }
    super.setVisible (showQ);
  }
}
