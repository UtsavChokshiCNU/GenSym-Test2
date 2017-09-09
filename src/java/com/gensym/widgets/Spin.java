/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   Spin.java 
 * 
 * 
 */ 

package com.gensym.widgets;

import java.awt.Component;
import java.awt.Container;
import java.awt.Button;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.GridBagLayout;
import java.awt.BorderLayout;
import java.awt.GridBagConstraints;
import java.awt.TextArea;
import java.awt.TextComponent;
import java.awt.TextField;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Dimension;
import java.util.Vector;
import java.io.Serializable;
import javax.swing.JTextField;

// REQUIREMENTS
// 1. Allow for float or integer display, increment, and value.
// 2. allow typing new value
// 3. do key-repeat
// 4. wrap


public class Spin extends Container implements ActionListener {

  static final long serialVersionUID = 2L;

  private Container buttons;
  private SpinButton downButton, upButton;
  private Component textWidget;

  private static GridBagConstraints buttonConstraints =
  new GridBagConstraints();

  static {
    buttonConstraints.weighty = 1.0;
    buttonConstraints.gridwidth = GridBagConstraints.REMAINDER;
    buttonConstraints.fill = GridBagConstraints.VERTICAL;
  }

  private SpinController spinController = new SpinController();

  public SpinController getSpinController(){
      return spinController;
  }

  public void setSpinController(SpinController spinController){
    this.spinController = spinController;
  }

  public Spin() {
    this(new JTextField(0));
  }

  public Spin(Component textWidget) {
    setLayout(new BorderLayout());
    addSpinButtons();
    addTextComponent(textWidget);
    spinController.setTextWidget(textWidget);
    addSpinListener(spinController);
  }

  @Override
  public void setEnabled(boolean yes) {
    downButton.setEnabled(yes);
    upButton.setEnabled(yes);
    textWidget.setEnabled(yes);
    super.setEnabled(yes);
  }

  public void putValue(double value) {
    spinController.putValue(value);
  }

  public void putValue(long value) {
    spinController.putValue(value);
  }

  public boolean getWrap(){
      return spinController.getWrap();
  }

  public void setWrap(boolean wrap){
    spinController.setWrap(wrap);
  }

  public double getIncrement(){
      return spinController.getIncrement();
  }

  public void setIncrement(double increment){
    spinController.setIncrement(increment);
  }

  public double getMinValue(){
      return spinController.getMinValue();
  }

  public void setMinValue(double minValue){
    spinController.setMinValue(minValue);
  }

  public double getMaxValue(){
      return spinController.getMaxValue();
  }

  public void setMaxValue(double maxValue){
    spinController.setMaxValue(maxValue);
  }

  public Component getTextWidget(){
    return textWidget;
  }

  private Vector listeners = new Vector();

  public void addSpinListener(SpinListener l) {
    synchronized (listeners) {
      listeners.addElement(l);
    }
  }

  public void removeSpinListener(SpinListener l) {
    synchronized (listeners) {
      listeners.removeElement(l);
    }
  }

  @Override
  public void actionPerformed(ActionEvent e) {
    dispatchSpinEvent(e.getSource() == upButton);
  }

  private void dispatchSpinEvent(boolean up) {
    Vector dispatchList = null;

    synchronized (listeners) {
      if (!listeners.isEmpty()) {
	dispatchList = (Vector)listeners.clone();
      }
    }

    if (dispatchList != null) {
      SpinEvent event = new SpinEvent(this, up);
      int size = dispatchList.size();
      for (int i = 0; i < size; i++) {
	SpinListener l = (SpinListener)dispatchList.elementAt(i);
	if (up)
	  l.spinUp(event);
	else
	  l.spinDown(event);
      }
    }
  }

  private void addTextComponent(Component textWidget) {
    this.textWidget = textWidget;
    add(textWidget, BorderLayout.CENTER);
    
    //add(new TextArea("", 1, 1, TextArea.SCROLLBARS_NONE), BorderLayout.CENTER);
  }

  int arrowWidth = 7, arrowHeight = 4;

  private void addSpinButtons() {
    upButton = new SpinButton(true, arrowWidth, arrowHeight);
    downButton = new SpinButton(false, arrowWidth, arrowHeight);
    buttons = new SpinButtons(upButton, downButton, buttonConstraints);
    downButton.addActionListener(this);
    upButton.addActionListener(this);
    buttons.setVisible(true);
    add(buttons, BorderLayout.EAST);
  }
}
