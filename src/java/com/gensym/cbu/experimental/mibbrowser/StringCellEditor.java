package com.gensym.cbu.experimental.mibbrowser;

import java.awt.Component;                   
import java.util.EventObject;

import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.table.TableCellEditor;
import javax.swing.DefaultCellEditor;
import javax.swing.event.CellEditorListener;


public class StringCellEditor implements TableCellEditor {
  JTextField tField = new JTextField();
  JTextArea tArea = new JTextArea();
  JScrollPane pane = new JScrollPane(tArea);
  Object cellValue = null;
  boolean useTextArea = false;

  public StringCellEditor() {
    tArea.setEditable(false);
    tArea.setLineWrap(true);
    tArea.setWrapStyleWord(true);
    tField.setEditable(false);
  }

  @Override
  public Component getTableCellEditorComponent(JTable table, Object value,
    boolean isSelected,int row,int col) {
    int strWidth = table.getFontMetrics(table.getFont()).
      stringWidth(value.toString() + 5);
    int cellWidth = table.getCellRect(row,col,false).width;
    cellValue = value;
    if (strWidth > cellWidth) {
      useTextArea = true;
      tArea.setText(value.toString());
      return pane;
    }
    else {
      useTextArea = false;
      tField.setText(value.toString());
      return tField;
    }

  }

  @Override
  public void cancelCellEditing() {
    if (useTextArea)
      tArea.transferFocus();
  }
  
  @Override
  public Object getCellEditorValue() {
    return cellValue;
  }

  @Override
  public boolean isCellEditable(EventObject eo) {

    return true;
  }

  @Override
  public boolean shouldSelectCell(EventObject eo) {
    return false;
  }

  public boolean stopEditing() {
    return true;
  }

  @Override
  public boolean stopCellEditing() {
    return true;
  }

  @Override
  public void removeCellEditorListener(CellEditorListener l) {};
  @Override
  public void addCellEditorListener(CellEditorListener l) {};

}
