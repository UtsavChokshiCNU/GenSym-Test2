/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 KbTreeNode.java
 *
 */
package com.gensym.g2studio.util;

import com.gensym.ntw.TwAccess;
import com.sun.java.swing.tree.DefaultMutableTreeNode;

public class KbTreeNode extends DefaultMutableTreeNode {

  private TwAccess cxn;

  /**
   * Constructs a new KbTreeNode instance with obj as the user
   * object.
   */
  public KbTreeNode(TwAccess cxn, Object obj) {
    super(obj);
    this.cxn = cxn;
  }
  
  public boolean isLeaf() {
    return true;
  }
}
