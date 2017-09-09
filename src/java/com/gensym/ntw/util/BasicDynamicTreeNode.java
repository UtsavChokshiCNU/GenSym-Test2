/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BasicDynamicTreeNode.java
 *
 */
package com.gensym.ntw.util;

import com.gensym.ntw.TwAccess;
import java.awt.Container;
import java.awt.Cursor;

public abstract class BasicDynamicTreeNode extends BasicTreeNode {
  
  protected boolean hasLoaded;

  /**
   * Constructs a new BasicDynamicTreeNode instance with obj as the user object.
   */
  public BasicDynamicTreeNode(TwAccess cxn, InstanceData obj) {
    super(cxn, obj, false);
  }

  @Override
  public int getChildCount() {
    if(!hasLoaded) {
      Container parent = getParentWindow();
      Container prevParent = parent;
      while(parent != null && !(prevParent instanceof java.awt.Window)) {
	prevParent = parent;
	parent = parent.getParent();
      }
      parent = prevParent;
      if (parent != null) 
	parent.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));     
      loadChildren();
      if (parent != null) 
	parent.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
    }
    return super.getChildCount();
  }

  protected abstract Container getParentWindow();
  
  protected abstract void loadChildren();

  // what about stuff for: moduleScope, factory (see ObjectDynamicTreeNode parent references)

  @Override
  public void removeAllChildren() {
    super.removeAllChildren();
    hasLoaded = false;
  }
  
}
