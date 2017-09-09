package com.gensym.beaneditor;

import java.awt.Dialog;
import java.awt.Frame;
import java.awt.Dimension;
import java.awt.Insets;
import java.awt.Point;
import javax.swing.JProgressBar;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.BoxLayout;
import javax.swing.Box;

class ProgressFrame extends Dialog{
  private JProgressBar progressBar;
  private JLabel progressLabel;

  ProgressFrame(Frame frame, String message){
    super(frame, "Component Editor", false);
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
  }

  JProgressBar getProgressBar(){
    return progressBar;
  }

  JLabel getLabel(){
    return progressLabel;
  }
}
