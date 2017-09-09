/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 KbTreeModel.java
 *
 */
package com.gensym.g2studio.util;

import com.sun.java.swing.tree.DefaultMutableTreeNode;
import com.sun.java.swing.tree.DefaultTreeModel;
import com.sun.java.swing.tree.TreeNode;
import com.sun.java.swing.tree.TreePath;

public class KbTreeModel extends DefaultTreeModel {
  /**
   * Creates a new instance of KbTreeModel with newRoot set
   * to the root of this model.
   */
  public KbTreeModel(TreeNode newRoot) {
    super(newRoot);
  }

  /**
   * Subclassed to message setString() to the changed path item.
   */
  public void valueForPathChanged(TreePath path, Object newValue) {
    System.out.println("KbTreeModel.valueForPathChanged");

    /* Update the user object. */
    DefaultMutableTreeNode aNode = (DefaultMutableTreeNode)path.getLastPathComponent();
    KbData kbData = (KbData)aNode.getUserObject();

    kbData.setString((String)newValue);
    /* UUUhhhhh, pretty colors. */
    //sampleData.setColor(Color.green);
    
    /* Since we've changed how the data is to be displayed, message nodeChanged. */
    nodeChanged(aNode);
  }
}
