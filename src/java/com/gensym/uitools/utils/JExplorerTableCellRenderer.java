package com.gensym.uitools.utils;

import javax.swing.table.TableCellRenderer;
import java.awt.Font;
import java.awt.Color;
import java.awt.Component;
import javax.swing.JTable;
import javax.swing.JLabel;
import javax.swing.Icon;
import javax.swing.UIManager;

public class JExplorerTableCellRenderer extends JLabel
implements TableCellRenderer
{
  protected JTableIconFactory iconFactory;
  public JExplorerTableCellRenderer(JTableIconFactory iconFactory) {
    super();
    this.iconFactory = iconFactory;
    setFont(FontUtil.sanserifPlain11);
    setOpaque(true);
  }

  public void setJTableIconFactory(JTableIconFactory iconFactory) {
    this.iconFactory = iconFactory;
  }
  
  @Override
  public Component getTableCellRendererComponent(JTable table,
						 Object value,
						 boolean isSelected,
						 boolean hasFocus,
						 int row,
						 int column){
    if (isSelected && column == 0) {
      setBackground(table.getSelectionBackground());
      setForeground(table.getSelectionForeground());	
    } else {
      setBackground(table.getBackground());
      setForeground(table.getForeground());		
    }
    if (value == null)
      value = "";
    setText(value.toString());
    Icon icon = null;
    if (column == 0 && iconFactory != null)
      icon = iconFactory.getIcon(row, table);
    setIcon(icon);
    return this;
  }
  
}


