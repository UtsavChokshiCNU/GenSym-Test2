/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceDynamicTreeNode.java
 *
 */
package com.gensym.demos.multiplecxnsdiapp;

import java.awt.Cursor;
import java.util.Vector;

import com.gensym.classes.ClassDefinition;
import com.gensym.classes.G2Definition;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.classes.SystemTable;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.G2ClassSymbols;

import javax.swing.JFrame;
import javax.swing.tree.DefaultMutableTreeNode;

public class WorkspaceDynamicTreeNode extends DefaultMutableTreeNode {

  private TwAccess cxn;
  private JFrame frame;

  /** Have the children of this node been loaded yet? */
  protected boolean hasLoaded;

  private static final Symbol KBWORKSPACE_ = Symbol.intern("KB-WORKSPACE");

  /**
   * Constructs a new WorkspaceDynamicTreeNode instance with obj as the user
   * object.
   */
  public WorkspaceDynamicTreeNode(JFrame frame, TwAccess cxn, Object obj) {
    super(obj);
    this.cxn = cxn;
    this.frame = frame;
  }
  
  @Override
  public boolean isLeaf() {
    return false;
  }
  
  /**
   * If hasLoaded is false, meaning the children have not yet been
   * loaded, loadChildren is messaged and super is messaged for
   * the return value.
   */
  @Override
  public int getChildCount() {
    if(!hasLoaded)
      loadChildren();
    return super.getChildCount();
  }

  public void setConnection(TwAccess connection) {
    cxn = connection;
  }

  /**
   * Messaged the first time getChildCount is messaged.  Creates
   * children with random names from names.
   */
  protected void loadChildren() {
    WorkspaceData data = (WorkspaceData)getUserObject();
    int dataType = data.getDataType();

    if (dataType == WorkspaceData.KB_WORKSPACES) {
      if (cxn != null) {
	try {
	  loadKbWorkspaces();
	  hasLoaded = true;
	} catch (G2AccessException gae) {
	  System.out.println(gae);
	}
      }
    }

    else if (dataType == WorkspaceData.G2_KB_WORKSPACE) {
      try {
	loadSubWorkspaces(data.getKbWorkspace());
      } catch (G2AccessException gae) {
	System.out.println(gae);
      }
    } 
  }

  private void loadKbWorkspaces() throws G2AccessException {
    WorkspaceData data;
    WorkspaceTreeNode newNode;
    Sequence wksps = cxn.getNamedWorkspaces();

    KbWorkspace wksp;
    int counter = 0;
    for (int i=0; i<wksps.size(); i++) {
      wksp = (KbWorkspace)cxn.getUniqueNamedItem(KBWORKSPACE_, (Symbol)wksps.elementAt(i));
      data = new WorkspaceData(wksp, (Symbol)wksps.elementAt(i));
      newNode = new WorkspaceTreeNode(cxn, data);
      insert(newNode, counter++);
    }

    hasLoaded = true;
  }

  private void loadSubWorkspaces(KbWorkspace workspace) throws G2AccessException {
  }
}
