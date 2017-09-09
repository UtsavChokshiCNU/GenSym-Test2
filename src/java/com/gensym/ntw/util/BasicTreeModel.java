/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BasicTreeModel.java
 *
 */
package com.gensym.ntw.util;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;

public class BasicTreeModel extends DefaultTreeModel {

  /**
   * Creates a new instance of BasicTreeModel with newRoot set to the root of this model.
   */
  public BasicTreeModel(TreeNode newRoot) {
    super(newRoot);
  }

  /**
   * Subclassed to message setString() to the changed path item.
   */
  @Override
  public void valueForPathChanged(TreePath path, Object newValue) {
    //System.out.println("BasicTreeModel.valueForPathChanged");

    /* Update the user object. */
    DefaultMutableTreeNode aNode = (DefaultMutableTreeNode)path.getLastPathComponent();
    BasicObjectDataRenderer data = (BasicObjectDataRenderer)aNode.getUserObject();

    data.setTextRepresentation((String)newValue);
    
    /* Since we've changed how the data is to be displayed, message nodeChanged. */
    nodeChanged(aNode);
  }
}







