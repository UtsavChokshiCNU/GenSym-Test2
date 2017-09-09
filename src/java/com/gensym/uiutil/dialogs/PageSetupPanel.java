/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PageSetupPanel.java
 *
 */

package com.gensym.uiutil.dialogs;

import java.awt.Component;
import java.awt.Graphics;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.TextField;
import java.awt.event.FocusListener;
import java.awt.event.FocusEvent;
import java.awt.event.ItemListener;
import java.awt.event.ItemEvent;
import java.awt.event.KeyListener;
import javax.swing.ButtonGroup;
import javax.swing.JPanel;
import javax.swing.border.TitledBorder;
import javax.swing.border.EtchedBorder;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.GridLayout;
import javax.swing.JTabbedPane;
import javax.swing.JButton;
import javax.swing.JRadioButton;
import java.awt.event.KeyEvent;
import java.awt.BorderLayout;
import javax.swing.BorderFactory;

import java.awt.Insets;
import javax.swing.JTextField;
import javax.swing.JLabel;
import javax.swing.border.EmptyBorder;
import javax.swing.ImageIcon;
import java.net.URL;
import java.awt.print.PageFormat;
import java.awt.print.Paper;
import java.text.DecimalFormat;
import java.text.ParseException;

import com.gensym.message.Resource;
import com.gensym.widgets.Spin;
import com.gensym.widgets.SpinListener;
import com.gensym.widgets.SpinEvent;
import com.gensym.widgets.TextWidget;


public class PageSetupPanel extends JPanel implements ActionListener, SpinListener {
  private static Resource i18nMsgs = Resource.getBundle("com.gensym.uiutil.dialogs.Messages");
  private static Resource i18nErrors = Resource.getBundle("com.gensym.uiutil.dialogs.Errors");

  public static final double ZOOM_TO_FIT = 0.0;  

  private JTabbedPane tabbedPane;
  private JRadioButton portraitButton, landscapeButton;
  private Spin leftSpinner,  rightSpinner, topSpinner, bottomSpinner;
  private ZoomPanel zoomPanel;
  private PageFormat format;
  JTextField[] marginTextControls;

  private JTextField rightField;
  private JTextField topField;
  private JTextField leftField;
  private JTextField bottomField;


  public PageSetupPanel(PageFormat format){
    this.format = format;
    tabbedPane = new JTabbedPane();
    Component pagePanel = makePagePanel();
    tabbedPane.addTab(i18nMsgs.getString("pageTab"), null, pagePanel, i18nMsgs.getString("pageTabTooltip"));
    tabbedPane.setSelectedIndex(0);
    Component marginsPanel = makeMarginsPanel();
    tabbedPane.addTab(i18nMsgs.getString("marginTab"), null, marginsPanel, i18nMsgs.getString("marginTabTooltip"));
    setLayout(new GridLayout(1, 1)); 
    add(tabbedPane);
  }

  private Component makePagePanel() {
    JPanel pagePanel = new JPanel();
    pagePanel.setLayout(new GridLayout(2, 0)); 

    URL url = this.getClass().getResource("portrait.gif");
    ImageIcon portraitIcon = new ImageIcon(url);
    url = this.getClass().getResource("landscape.gif");
    ImageIcon landscapeIcon = new ImageIcon(url);



    JPanel orientationPanel = new JPanel(); 

    orientationPanel.setBorder(new TitledBorder(new EtchedBorder(), i18nMsgs.getString("Orientation")));
    orientationPanel.setLayout(new GridLayout(1, 3));

    portraitButton = new JRadioButton(i18nMsgs.getString("portraitLabel"));
    portraitButton.setMnemonic(KeyEvent.VK_T);
    portraitButton.addActionListener(this);

    landscapeButton = new JRadioButton(i18nMsgs.getString("landscapeLabel"));
    landscapeButton.setMnemonic(KeyEvent.VK_L);
    landscapeButton.addActionListener(this);

    if(format.getOrientation() == PageFormat.LANDSCAPE) {
      landscapeButton.setSelected(true);
    } else { 
      portraitButton.setSelected(true);
    }
		
    ButtonGroup group = new ButtonGroup();
    group.add(portraitButton);
    group.add(landscapeButton);

    orientationPanel.add(new JLabel(portraitIcon));
    orientationPanel.add(portraitButton);
    orientationPanel.add(new JLabel(landscapeIcon));
    orientationPanel.add(landscapeButton);
    pagePanel.add(orientationPanel);

    zoomPanel = new ZoomPanel(new double[0], 
			      new String[0], 
			      true, 
			      true, 
			      1, 
			      1, 
			      ZOOM_TO_FIT);
    pagePanel.add(zoomPanel);

    return pagePanel;
  }

  private Component makeMarginsPanel() {
    JPanel marginsPanel = new JPanel();
    Paper p = format.getPaper();
    
    double widthLetterSize = 72 * 8.5;
    double heightLetterSize = 72 * 11.0;
    JLabel Left = new javax.swing.JLabel("Left:");
    JLabel Right = new javax.swing.JLabel ("Right:");
    JLabel Top = new javax.swing.JLabel ("Top:");
    JLabel Bottom = new javax.swing.JLabel ("Bottom:");
    
    double leftMargin = p.getImageableX() / 72 ;
    double rightMargin = (p.getWidth() - p.getImageableWidth() -  p.getImageableX()) / 72;
    double topMargin = p.getImageableY() / 72;
    double bottomMargin = (p.getHeight() - p.getImageableHeight() - p.getImageableY()) / 72;
    
    DecimalFormat formatter = new DecimalFormat("##.00");		
    leftField = new JTextField(formatter.format(leftMargin));
    rightField = new JTextField(formatter.format(rightMargin));
    topField = new JTextField(formatter.format(topMargin));
    bottomField = new JTextField(formatter.format(bottomMargin));
    
    leftSpinner = createSpinner(leftField);
    rightSpinner = createSpinner(rightField);
    topSpinner = createSpinner(topField);
    bottomSpinner = createSpinner(bottomField);
    
    GridBagLayout gridBag = new GridBagLayout();
    marginsPanel.setLayout(gridBag);
    GridBagConstraints gridBagConstraints;
    gridBagConstraints = new GridBagConstraints();
    gridBagConstraints.anchor = GridBagConstraints.NORTHWEST;
    Insets labelInsets = new Insets(10, 8, 0, 0); 
    Insets spinnerInsets = new Insets(10, 0, 0, 5); 
    gridBagConstraints.fill = GridBagConstraints.HORIZONTAL;
    gridBagConstraints.weighty = 0.0;
    
    // left label
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = 0;
    gridBagConstraints.weightx = 0.01;
    gridBagConstraints.insets = labelInsets;
    gridBag.setConstraints(Left, gridBagConstraints);
    marginsPanel.add (Left, gridBagConstraints);

    // Left spinner and text field
    gridBagConstraints.gridx = 1;
    gridBagConstraints.weightx = 0.1;
    gridBagConstraints.insets = spinnerInsets;
    gridBag.setConstraints(leftSpinner, gridBagConstraints);
    marginsPanel.add (leftSpinner, gridBagConstraints); 
	  
    // right label
    gridBagConstraints.gridx = 2;
    gridBagConstraints.weightx = 0.01;
    gridBagConstraints.insets = labelInsets;
    gridBag.setConstraints(Right, gridBagConstraints);
    marginsPanel.add (Right, gridBagConstraints);
	  
    // right spinner and text field
    gridBagConstraints.gridx = 3;
    gridBagConstraints.weightx = 0.1;
    gridBagConstraints.insets = spinnerInsets;
    gridBag.setConstraints(rightSpinner, gridBagConstraints);
    marginsPanel.add (rightSpinner, gridBagConstraints); 
	  
    // top label
    gridBagConstraints.gridx = 0;
    gridBagConstraints.gridy = 1;
    gridBagConstraints.weightx = 0.01;
    gridBagConstraints.insets = labelInsets;
    gridBag.setConstraints(Top, gridBagConstraints);
    marginsPanel.add (Top, gridBagConstraints);
	  
    // top spinner and text field
    gridBagConstraints.gridx = 1;
    gridBagConstraints.weightx = 0.1;
    gridBagConstraints.insets = spinnerInsets;
    gridBag.setConstraints(topSpinner, gridBagConstraints);
    marginsPanel.add (topSpinner, gridBagConstraints); 
	  
    // bottom label
    gridBagConstraints.gridx = 2;
    gridBagConstraints.weightx = 0.01;
    gridBagConstraints.insets = labelInsets;
    gridBag.setConstraints(Bottom, gridBagConstraints);
    marginsPanel.add (Bottom, gridBagConstraints);
	  
    // bottom spinner and text field
    gridBagConstraints.gridx = 3;
    gridBagConstraints.weightx = 0.1;
    gridBagConstraints.insets = spinnerInsets;
    gridBag.setConstraints(bottomSpinner, gridBagConstraints);
    marginsPanel.add (bottomSpinner, gridBagConstraints); 
		
    return marginsPanel;
  }

  // utility method
  private Spin createSpinner(JTextField field) {
    Spin spin = new Spin(field);
    spin.setMinValue(0);
    spin.setMaxValue(1000000);
    spin.setIncrement(0.25); // quarter-inch increment
    spin.getSpinController().setNumberFormatter(new DecimalFormat("##.##"));

    spin.addSpinListener(this);
    return spin;
  }

  // accessor
  public PageFormat getPageFormat() {
    updatePageFormat(format);
    return format;
  }

  // accessor
  public double getZoomValue() {
    return zoomPanel.getValue();
  }

  @Override
  public void actionPerformed(ActionEvent ae) {
    if(ae.getSource() == portraitButton) {
      format.setOrientation(PageFormat.PORTRAIT);
    } else if(ae.getSource() == landscapeButton) {
      format.setOrientation(PageFormat.LANDSCAPE);
    }
  }

  @Override
  public void spinUp(SpinEvent event){
  }

  @Override
  public void spinDown(SpinEvent event){
  }

  private void updatePageFormat(PageFormat f) {
    double left = getValueFromSpinner(leftSpinner) * 72;
    double right = getValueFromSpinner(rightSpinner) * 72;
    double top = getValueFromSpinner(topSpinner) * 72;
    double bottom = getValueFromSpinner(bottomSpinner) * 72;
    Paper p = f.getPaper();
    p.setImageableArea(left, top, p.getWidth()-left-right, p.getHeight()-top-bottom);
    f.setPaper(p);
  }

  private double getValueFromSpinner(Spin spinner) {
    double d = 0.0;
    Component c = spinner.getTextWidget();
    if(c instanceof JTextField) {
      try {
	String s = ((JTextField)c).getText();
	d = Double.parseDouble(s);
      } catch (NumberFormatException nfe) {
	System.err.println("error in getValue " + nfe.getMessage());
      }
    }
    return d;
  }

}

