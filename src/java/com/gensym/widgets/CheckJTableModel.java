package com.gensym.widgets;

import java.awt.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import javax.swing.table.*;


public class CheckJTableModel extends AbstractTableModel{

  private Vector data;
  private Vector checks;
  private String columnName;
  
  public CheckJTableModel(Vector names, String columnName){
    super();
    data = (Vector)names.clone();
    this.columnName = columnName;
    checks = new Vector(0);
    for(int i=0;i<data.size();i++){
      checks.addElement(Boolean.FALSE);
    }
  }

  @Override
  public String getColumnName(int col){
    if(col == 0) return " ";
    return columnName;
  }
  
  @Override
  public int getRowCount(){
    return data.size();
  }
  @Override
  public int getColumnCount(){
    return 2;
  }
  public int getIndexOfValue(Object value){
    if(data.contains(value))
       return data.indexOf(value);
    return -1;
  }
  
  @Override
  public Object getValueAt(int row, int col){
    if(col==0)return checks.elementAt(row);
    return data.elementAt(row);
  }
  @Override
  public void setValueAt(Object value, int row, int col){
    if(col==0)checks.setElementAt((Boolean)value, row);
    if(col==1)data.setElementAt(value.toString(), row);
    fireTableCellUpdated(row, col);
  }
  @Override
  public boolean isCellEditable(int row, int col){
    if(col==0)return true;
    return false;
  }
  public void addRow(Boolean check, String string){
    if(! data.contains(string)){
      checks.add(0, check);
      data.add(0, string);
      fireTableRowsInserted(0,0);
    }
  }

  public void removeRow(int index){
    if(index >-1 && index<getRowCount()){
      checks.removeElementAt(index);
      data.removeElementAt(index);
      fireTableRowsDeleted(index, index);
    }
  }
      
  @Override
  public Class getColumnClass(int col){
    if(col == 0) return (new Boolean(true)).getClass();
    return (new String("")).getClass();
  }

  public Vector getCheckedValues(){
    Vector actions = new Vector(0);
    for(int counter=0; counter<checks.size(); counter++){
      if(((Boolean)getValueAt(counter, 0)).booleanValue()){
	actions.addElement((String)getValueAt(counter,1));
      }
    }
    return actions;
  }

  public boolean isEmpty(){
    if(data.isEmpty()) return true;
    return false;
  }
}
