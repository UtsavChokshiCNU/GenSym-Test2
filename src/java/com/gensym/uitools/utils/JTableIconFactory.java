package com.gensym.uitools.utils;

import javax.swing.Icon;
import javax.swing.JTable;

public interface JTableIconFactory {
  public Icon getIcon(int row, JTable table);
}
