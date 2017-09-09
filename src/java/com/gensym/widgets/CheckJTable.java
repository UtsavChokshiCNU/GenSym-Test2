package com.gensym.widgets;

import java.awt.*;
import java.util.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.border.*;
import javax.swing.table.*;

/* CheckPanel will notify all registered PropertyChangeListeners,
   which can be registered by addPropertyChangeListener method on Component*/

public class CheckJTable extends JTable{
  private CheckJTableModel tableModel;
  
  public CheckJTable(Vector names, Vector columnNames){
    super(names, columnNames);
    String columnName = (String)columnNames.elementAt(1);
    tableModel = new CheckJTableModel(names, columnName);
    setModel(tableModel);

    DefaultTableCellRenderer textRenderer = new DefaultTableCellRenderer();
    setDefaultRenderer(String.class, textRenderer);

    CheckRenderer checkRenderer = new CheckRenderer();
    setDefaultRenderer(Boolean.class, checkRenderer);

  }
  public CheckJTableModel getTableModel(){
    return tableModel;
  }

  
  class CheckRenderer extends JLabel implements TableCellRenderer{
    @Override
    public Component getTableCellRendererComponent(JTable table,
						   Object value,
						   boolean isSelected,
						   boolean hasFocus,
						   int row,
						   int col){
      if(col == 0){
	JCheckBox checkBox = new JCheckBox();
	checkBox.setHorizontalAlignment(SwingConstants.CENTER);
	checkBox.setBackground(Color.white);
	//super.setOpaque(true);
	checkBox.setSelected(((Boolean)value).booleanValue());
	return checkBox;
      }
      return null;
    }
  }

}






