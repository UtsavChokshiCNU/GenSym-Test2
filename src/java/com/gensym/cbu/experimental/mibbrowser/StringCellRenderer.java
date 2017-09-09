package com.gensym.cbu.experimental.mibbrowser;

import java.awt.Component;
import java.awt.Dimension;

import javax.swing.JTextArea;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.DefaultTableCellRenderer;

public class StringCellRenderer extends DefaultTableCellRenderer {
  private JTextArea tArea = new JTextArea();
  private JScrollPane pane = new JScrollPane(tArea);
  private boolean useTextArea = false;

  public StringCellRenderer() {
    tArea.setLineWrap(true);
    tArea.setWrapStyleWord(true);

  }


  @Override
  public Component getTableCellRendererComponent(JTable table, Object value,
    boolean isSelected,boolean hasFocus,int row,int col) {

    int strWidth = table.getFontMetrics(table.getFont()).
      stringWidth(value.toString() + 5);
    int cellWidth = table.getCellRect(row,col,false).width;
    if (strWidth > cellWidth) {
      useTextArea = true;
      tArea.setText(value.toString());
      pane.setMinimumSize(new Dimension(62,62));
      pane.setPreferredSize(new Dimension(62,62));            
      return pane;
    }
    else {
      useTextArea = false;
      return super.getTableCellRendererComponent(table,value,isSelected,hasFocus,
        row,col);
    }
  }
}