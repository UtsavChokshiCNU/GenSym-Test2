/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TableView.java
 *
 */

package com.gensym.ntw.util;

import java.awt.Color;
import java.awt.Component;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.BorderLayout;
import java.util.Vector;
import javax.swing.UIManager;
import javax.swing.JTable;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JScrollBar;
import javax.swing.border.BevelBorder;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.TableColumn;
import javax.swing.table.TableColumnModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.DefaultTableCellRenderer;
import javax.swing.table.TableCellEditor;
import com.gensym.uitools.utils.StatusBar;

public class TableView extends Container{
  private JTable table; 
  private TableViewModel model;
  JScrollPane scrollpane;
  private int messageLimit = -1;//-1 means no limit
  private int messageCount = 0;
  
  public TableView(ColumnDefinition[] columns){
    model = new TableViewModel(columns);
    table = new JTable(model);
    table.setDefaultRenderer(Object.class, new TableViewCellRenderer());
    DefaultTableCellRenderer rightAlignedLabel = new TableViewCellRenderer();
    rightAlignedLabel.setHorizontalAlignment(JLabel.CENTER);
    table.setDefaultRenderer(Number.class, rightAlignedLabel);
    scrollpane = new JScrollPane(table);
    scrollpane.setBorder(new BevelBorder(BevelBorder.LOWERED));
    setLayout(new BorderLayout());
    add(scrollpane, BorderLayout.CENTER);
  }

  public void setStatusBar(StatusBar statusBar) {
    add(statusBar, BorderLayout.SOUTH);
  }
  
  /**
   * @param messageLimit an integer dictating the maximum number of messages to 
   * show at a time.  Setting a value of -1 signifies not to use any limit.
   */
  public void setMessageLimit(int messageLimit) {
    this.messageLimit = messageLimit;
  }

  public void addTableViewMessage(TableViewMessage msg) {
    messageCount++;
    if ((messageLimit != -1) && (messageCount > messageLimit))
      removeTableViewMessage(getTableViewMessage(0));
    model.addRow(msg);
    model.fireTableRowsInserted(messageCount-1, messageCount-1);
    scrollToBottom();
  }

  private void scrollToBottom() {
    JScrollBar scrollBar = scrollpane.getVerticalScrollBar();
    if (scrollBar != null)
      scrollBar.setValue(scrollBar.getMaximum());
  }

    
  public void updateTableViewMessage(TableViewMessage msg){
      model.updateRow(msg);
  }

  public void removeTableViewMessage(TableViewMessage msg){
    model.deleteRow(msg);
    messageCount--;
  }

  public TableViewMessage getTableViewMessage(int row){
      return model.getMessageForRow(row);
  }

  public void clear(){
    model.clear();
  }

  public JTable getTable(){
    return table;
  }

  class TableViewModel extends AbstractTableModel{
    private Vector data;
    private ColumnDefinition[] columns;
    
    public TableViewModel(ColumnDefinition[] columns){
      data = new Vector();
      this.columns = columns;
    }
    
    @Override
    public int getColumnCount(){
      return columns.length;
    }
    
    @Override
    public String getColumnName(int column){
      return columns[column].getName();
    }
    
    @Override
    public Class getColumnClass(int column){
      return columns[column].getType();
    }
    
    @Override
    public boolean isCellEditable(int row, int col) {
      return columns[col].isEditable();
    }
    
    @Override
    public int getRowCount(){
      return data.size();
    }
    
    @Override
    public Object getValueAt(int row, int column){
      TableViewMessage msg = null;
      synchronized(data){
	if (row >= data.size()) return null;
	msg = (TableViewMessage)data.elementAt(row);
      }
      return msg.getRowValues()[column];
      
    }  
    
    @Override
    public void setValueAt(Object aValue, int row, int column){
      TableViewMessage msg = (TableViewMessage)data.elementAt(row);
      msg.setValueAt(column, aValue);
    }
    
    void addRow(TableViewMessage msg){
      data.addElement(msg);
      fireTableRowsInserted(data.size()-1, data.size()-1);
    }

    void updateRow(TableViewMessage msg){
      int index = data.indexOf(msg);
      if (index >= 0){
	data.setElementAt(msg, index);
	fireTableRowsUpdated(index, index);
      }
    }

    void deleteRow(TableViewMessage msg){
      int index = data.indexOf(msg);
      if (index >= 0){
	table.clearSelection();
	data.removeElementAt(index);
	//fireTableRowsDeleted(index, index);
	//Can't call fireTableRowsDeleted because of repaint bug in JTable
	fireTableDataChanged();
      }
    }
    
    void clear(){
      data.removeAllElements();
      fireTableDataChanged();
    }
    
    TableViewMessage getMessageForRow(int row){
      if (row >= data.size()) return null;
      return (TableViewMessage)data.elementAt(row);
    }
  }


  class TableViewCellRenderer extends DefaultTableCellRenderer{

    @Override
    public Component getTableCellRendererComponent(JTable table, Object value,
						   boolean isSelected, 
						   boolean hasFocus, 
						   int row, int column){
      if (isSelected) {
	setForeground(table.getSelectionForeground());
	setBackground(table.getSelectionBackground());
      }
      else {
	TableViewMessage msg = model.getMessageForRow(row);
	if (msg != null){
	  setForeground(msg.getForegroundColor());
	  setBackground(msg.getBackgroundColor());
	}
      }
      
      setFont(table.getFont());
   
      if (hasFocus) {
	setBorder( UIManager.getBorder("Table.focusCellHighlightBorder") );
	if (table.isCellEditable(row, column)) {
	  setForeground( UIManager.getColor("Table.focusCellForeground") );
	  setBackground( UIManager.getColor("Table.focusCellBackground") );
	}
      } 
      else 
	setBorder(noFocusBorder);

      setValue(value); 
      
      return this;
    }
  }
}
