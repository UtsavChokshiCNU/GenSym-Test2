package com.gensym.widgets;

import java.awt.event.ActionEvent;
import javax.swing.JTable;
import javax.swing.table.TableModel;

public class ScrollTableWithAddEvent extends ActionEvent {
  private JTable table;
  private TableModel tableModel;

  public ScrollTableWithAddEvent(JTable table, TableModel tableModel, ActionEvent ae){
    super(ae.getSource(), ae.getID(), ae.getActionCommand());
    this.table = table;
    this.tableModel = tableModel;
  }

  public JTable getTable(){
    return table;
  }

  public TableModel getTableModel(){
    return tableModel;
  }
}
