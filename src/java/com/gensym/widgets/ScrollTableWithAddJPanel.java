/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ScrollTableWithAddJPanel.java
 *
 */
package com.gensym.widgets;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.ListSelectionModel;
import javax.swing.border.EmptyBorder;
import javax.swing.border.EtchedBorder;
import javax.swing.border.TitledBorder;
import javax.swing.event.*;
import javax.swing.table.DefaultTableModel;
import java.util.Vector;
import java.util.Enumeration;

import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;
import java.awt.Insets;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

/* A very simple table. Rows are added by clicking on the Add button,
   removed by clicking on the remove button. Table selection is necessary only
   for remove. Action Listeners must be implemented separately.*/
public class ScrollTableWithAddJPanel extends JPanel implements ActionListener{

  private JButton addButton;
  private JButton removeButton;
  private JTable table;
  private DefaultTableModel tableModel;
  private Vector listeners;

  public ScrollTableWithAddJPanel(String[] columnNames, String addButtonLabel, String removeButtonLabel){

    listeners = new Vector(0);
    
    setLayout(new GridBagLayout());
    
    GridBagConstraints constraints = new GridBagConstraints();
    constraints.gridx = 0;
    constraints.gridy = 0;
    constraints.weightx = 1;
    constraints.weighty = 0;
    constraints.insets = new Insets(4, 4, 4, 4);
    constraints.fill = constraints.BOTH;

    tableModel = new DefaultTableModel(columnNames, 0); //initially 0 rows    
    table = new JTable(tableModel);
    table.setPreferredScrollableViewportSize(new Dimension(400, 100));
    table.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
    JScrollPane spane = new JScrollPane(table);
    spane.setBorder(BorderFactory.createLoweredBevelBorder());
    constraints.gridheight = 4;
    constraints.gridwidth = 2;
    constraints.weighty = 1;
    
    add(spane, constraints);
    
    JPanel control = new JPanel();
    control.setLayout(new FlowLayout(FlowLayout.RIGHT, 5, 10));
    addButton = new JButton(addButtonLabel);
    addButton.setActionCommand(addButtonLabel);
    addButton.addActionListener(this);
      
    removeButton = new JButton(removeButtonLabel);
    removeButton.setActionCommand(removeButtonLabel);
    removeButton.addActionListener(this);
    control.add(addButton); 
    control.add(removeButton);

    constraints.gridx = 0;
    constraints.gridy = 4;
    constraints.gridheight = 1;
    constraints.gridwidth = 2;
    constraints.weighty = 0;
    constraints.fill = constraints.NONE;
    constraints.anchor = constraints.EAST;
    
    add(control, constraints);

  }

  public void addSTWAListener(ScrollTableWithAddListener al){
    if(! listeners.contains(al)){
      synchronized(listeners){
	listeners.addElement(al);
      }
    }
  }
  public void removeSTWAListener(ScrollTableWithAddListener al){
    if(listeners.contains(al)){
      synchronized(listeners){
	listeners.remove(al);
      }
    }
  }
  
  public DefaultTableModel getTableModel(){
    return tableModel;
  }
  
  public void setTableModel(DefaultTableModel model){
    tableModel=model;
    table.setModel(model);
  }
  
  public JTable getTable(){
    return table;
  }

  public void updateButtons(boolean addEnable, boolean removeEnable){
    addButton.setEnabled(addEnable);
    removeButton.setEnabled(removeEnable);
  }

  @Override
  public void actionPerformed(ActionEvent ae){
    ScrollTableWithAddEvent sae = new ScrollTableWithAddEvent(table, tableModel, ae);
    Vector listenerVector = new Vector(0);
    Enumeration e;
    ScrollTableWithAddListener al;

    if(! listeners.isEmpty()){
      synchronized(listeners){
	listenerVector = (Vector)listeners.clone();
      }
      e = listenerVector.elements();
      while(e.hasMoreElements()){
	al=(ScrollTableWithAddListener)e.nextElement();
	al.actionPerformed(sae);
      }
    }
  }
	

}

