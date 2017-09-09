package com.gensym.cbu.experimental.mibbrowser;

import javax.swing.*;
import javax.swing.table.*;


public class AttributeTable
{

  JTable table = new JTable(new DefaultTableModel(new String[] {"Attribute", "Value"}, 0));
//{
//    public boolean isCellEditable(int row,int column) { return false; };
//  });

  public AttributeTable () {
    table.setDefaultRenderer(Object.class,new StringCellRenderer());
    table.setDefaultEditor (Object.class, new StringCellEditor());

  }

  public JTable getTable()
    {
      return table;
    }

  public void removeRows()
    {
      while(table.getModel().getRowCount() > 0)
        ((DefaultTableModel)table.getModel()).removeRow(0);
    }

  public void showObject(MibFileObjectTableObject o)
    {
      //removeRows();

      int rows = o.getRowCount();
      for (int i = 0; i < rows; i++)
	      ((DefaultTableModel)table.getModel()).addRow(
          new String[] {o.getAttribute(i), o.getValue(i)});
    }
}
