/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BasicTreeNode.java
 *
 */
package com.gensym.ntw.util;

import java.awt.Component;

import com.gensym.ntw.TwAccess;

import javax.swing.tree.DefaultMutableTreeNode;

public class BasicTreeNode extends DefaultMutableTreeNode {

  protected TwAccess cxn;
  protected boolean isLeaf = true;
 
  /**
   * Constructs a new BasicTreeNode instance with obj as the user object.
   */
  public BasicTreeNode(TwAccess cxn, InstanceData obj) {
    super(obj);
    this.cxn = cxn;
  }

  // called by BasicDynamicTreeNode
  public BasicTreeNode(TwAccess cxn, InstanceData obj, boolean isLeaf) {
    this(cxn, obj);
    this.isLeaf = isLeaf;
  }

  @Override
  public boolean isLeaf() {
    return isLeaf;
  }

 public void setConnection(TwAccess connection) {
   //System.out.println("BasicTreeNode.setConnection: "+connection);
    cxn = connection;
  }
}
