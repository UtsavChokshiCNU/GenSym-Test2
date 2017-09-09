/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceTreeNode.java
 *
 */
package com.gensym.demos.multiplecxnsdiapp;

import com.gensym.ntw.TwAccess;
import javax.swing.tree.DefaultMutableTreeNode;

public class WorkspaceTreeNode extends DefaultMutableTreeNode {

  private TwAccess cxn;

  /**
   * Constructs a new WorkspaceTreeNode instance with obj as the user
   * object.
   */
  public WorkspaceTreeNode(TwAccess cxn, Object obj) {
    super(obj);
    this.cxn = cxn;
  }
  
  @Override
  public boolean isLeaf() {
    return true;
  }
}
