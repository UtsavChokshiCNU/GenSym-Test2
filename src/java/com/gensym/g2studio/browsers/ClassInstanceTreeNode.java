/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassInstanceTreeNode.java
 *
 */
package com.gensym.uitools.browsers;

import com.gensym.ntw.TwAccess;
import com.sun.java.swing.tree.DefaultMutableTreeNode;

public class ClassInstanceTreeNode extends DefaultMutableTreeNode {

  private TwAccess cxn;

  /**
   * Constructs a new ClassInstanceTreeNode instance with obj as the user object.
   */
  public ClassInstanceTreeNode(TwAccess cxn, Object obj) {
    super(obj);
    this.cxn = cxn;
  }
  
  public boolean isLeaf() {
    return true;
  }
}
