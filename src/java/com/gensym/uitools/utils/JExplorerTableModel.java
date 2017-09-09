package com.gensym.uitools.utils;

import javax.swing.tree.TreeNode;
import javax.swing.table.TableModel;

public interface JExplorerTableModel extends TableModel {
  public void removeAll();
  public void addRow(TreeNode treeNode);
  public void update();
}
