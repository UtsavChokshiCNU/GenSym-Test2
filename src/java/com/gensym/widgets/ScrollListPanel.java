/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ScrollListPanel.java
 *
 */
package com.gensym.widgets;

// import swing and java packages

import java.awt.*;
import java.awt.event.*;
import javax.swing.JPanel;
import javax.swing.JTextField;
import javax.swing.JTable;
import javax.swing.JFrame;
import java.util.Vector;

// for the DiscoveryDialogPanel
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;
import javax.swing.event.*;

public class ScrollListPanel extends JPanel implements
ActionListener, ListSelectionListener, KeyListener {
  
  private JButton addButton, removeButton;
  private JList list;
  private DefaultListModel listModel;
  private JTextField inputField;

  //selection mode
  public static final int SINGLE = ListSelectionModel.SINGLE_SELECTION;
  public static final int SINGLE_INTERVAL = ListSelectionModel.SINGLE_INTERVAL_SELECTION;
  public static final int MULTIPLE = ListSelectionModel.MULTIPLE_INTERVAL_SELECTION;

  public ScrollListPanel(Vector feeder, int numRowsVisible,
			 String addLabel, String removeLabel,
			 int selection) { 
    super(new BorderLayout());
    listModel = new DefaultListModel();
    if(feeder.size() > 0) { // if data is to be fed, do so
      for(int looper = 0; looper < feeder.size(); looper++) {
	listModel.addElement((String)feeder.elementAt(looper));
      }
    }
    list = new JList(listModel);
    list.setVisibleRowCount(numRowsVisible);
    if((selection != SINGLE) & (selection != SINGLE_INTERVAL)
       & (selection != MULTIPLE))
      selection = SINGLE_INTERVAL;
    list.setSelectionMode(selection);
    list.addListSelectionListener(this);
    JScrollPane spane = new JScrollPane(list);
    spane.setBorder(BorderFactory.createLoweredBevelBorder());

    if(addLabel != null && removeLabel != null){
      addButton = new JButton(addLabel);
      addButton.addActionListener(this);
      addButton.setDefaultCapable(true);
      removeButton = new JButton(removeLabel);
      removeButton.addActionListener(this);
      removeButton.setEnabled(false);
      removeButton.setDefaultCapable(false);
      inputField = new JTextField(15);
      inputField.addKeyListener(this);
      
      JPanel control = new JPanel();
      control.setBorder(new EmptyBorder(10, 0, 5, 0));
      control.setLayout(new BorderLayout());
      control.add(inputField, BorderLayout.CENTER);
      
      JPanel buttons = new JPanel();
      buttons.setLayout(new FlowLayout(FlowLayout.RIGHT, 5, 0));
      buttons.add(addButton);
      buttons.add(removeButton);
      control.add(buttons, BorderLayout.EAST);
    
    
      add(control, BorderLayout.SOUTH);
    }
    add(spane, BorderLayout.CENTER);

  }
  
  @Override
  public void actionPerformed(ActionEvent ae) {
    if(ae.getSource() == addButton) {
      add();
    } else if(ae.getSource() == removeButton) {
      int index = list.getSelectedIndex();
      if(index < 0) return;
      listModel.remove(index);
      inputField.setText("");
    }
  }

  @Override
  public void valueChanged(ListSelectionEvent e) {
    if (e.getValueIsAdjusting() == false) {
      if (list.getSelectedIndex() == -1) {
	if(removeButton != null){
	  // no selection, disable remove  button.
	  removeButton.setEnabled(false);
	  inputField.setText("");	
	} else {
	  // selection, update text field.
	  removeButton.setEnabled(true);
	  String address = list.getSelectedValue().toString();
	  inputField.setText(address);
	}
      }
    }
  }
    
  @Override
  public void keyTyped(KeyEvent ke) {}

  @Override
  public void keyReleased(KeyEvent ke) {
    if(ke.getKeyCode() == KeyEvent.VK_ENTER) {
      add();
    }
  }

  @Override
  public void keyPressed(KeyEvent ke) {}

  private void add() {
    //check if field is empty
    if (inputField.getText().equals("")) {
      Toolkit.getDefaultToolkit().beep();
      return;
    }
    listModel.addElement(inputField.getText());
    inputField.setText("");
  }

  public ListModel getListModel() {
    return listModel;
  }

  public JList getList(){
    return list;
  }

  public void setListModel(Vector feeder){
    if(feeder.size() > 0) { // if data is to be fed, do so
      listModel.clear();
      for(int looper = 0; looper < feeder.size(); looper++) {
	listModel.addElement((String)feeder.elementAt(looper));
      }
    }
  }
    
  public Vector getResult() {
    int size = listModel.getSize();
    Vector v = new Vector(size);
    for(int index = 0; index < size; index++) {
      v.addElement((String)listModel.elementAt(index));
    }
    return v;
  }

  public Vector getSelectedResult(){
    Vector result = new Vector(0);
    Object[] selection = list.getSelectedValues();
    int size = selection.length;
    if(size >0){
      for(int counter=0; counter<size; counter++){
	result.addElement(selection[counter]);
      }
    }
    return result;
  }
    
}








