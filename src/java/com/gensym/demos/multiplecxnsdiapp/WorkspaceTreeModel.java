/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceTreeModel.java
 *
 */
package com.gensym.demos.multiplecxnsdiapp;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;

public class WorkspaceTreeModel extends DefaultTreeModel {
  /**
   * Creates a new instance of WorkspaceTreeModel with newRoot set
   * to the root of this model.
   */
  public WorkspaceTreeModel(TreeNode newRoot) {
    super(newRoot);
  }

  /**
   * Subclassed to message setString() to the changed path item.
   */
  @Override
  public void valueForPathChanged(TreePath path, Object newValue) {
    DefaultMutableTreeNode node = (DefaultMutableTreeNode)path.getLastPathComponent();
    WorkspaceData data = (WorkspaceData)node.getUserObject();
    data.setString((String)newValue);
    nodeChanged(node);
  }
}
