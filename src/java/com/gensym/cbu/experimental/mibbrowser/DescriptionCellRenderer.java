package com.gensym.cbu.experimental.mibbrowser;

import java.awt.Component;
import java.awt.Color;

import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;

public class DescriptionCellRenderer extends DefaultTableCellRenderer {

  @Override
  public Component getTableCellRendererComponent(JTable table, Object value,
    boolean isSelected,boolean hasFocus,int row,int col) {

    int strWidth = table.getFontMetrics(table.getFont()).
      stringWidth(value.toString() + 5);
    int cellWidth = table.getCellRect(row,col,false).width;
//    if (col > 0 && table.getValueAt(row,col - 1).equals("Description")) {
    if (strWidth > cellWidth) {
      JTextArea tArea = new JTextArea(value.toString());
      tArea.setLineWrap(true);
      JScrollPane pane = new JScrollPane(tArea);
      return pane;
    }
    else
      return super.getTableCellRendererComponent(table,value,isSelected,hasFocus,
        row,col);
  }
}