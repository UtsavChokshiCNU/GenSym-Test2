/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassInstanceScrollPane.java
 *
 */
package com.gensym.uitools.browsers;

import com.gensym.classes.ClassDefinition;
import com.gensym.classes.G2Definition;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;

import com.sun.java.swing.JScrollPane;
import com.sun.java.swing.JTree;
import com.sun.java.swing.ToolTipManager;
import com.sun.java.swing.event.TreeExpansionEvent;
import com.sun.java.swing.event.TreeExpansionListener;
import com.sun.java.swing.tree.TreePath;

public class ClassInstanceScrollPane extends JScrollPane implements BrowserSymbols {

  private TwAccess currentConnection;
  private Symbol className;
  private Symbol baseClass = ROOT_;
  private Symbol moduleScope = ALL_;
 
  private ClassInstanceDynamicTreeNode rootNode;
  private ClassInstanceTreeModel treeModel;
  private JTree classTree;

  public ClassInstanceScrollPane (TwAccess cxn, Symbol className, Symbol baseClass, Symbol moduleScope) {
    setupClassInstanceScrollPane(cxn, className, baseClass, moduleScope);
  }

  public ClassInstanceScrollPane (TwAccess cxn, Symbol className, Symbol baseClass) {
    setupClassInstanceScrollPane(cxn, className, baseClass, moduleScope);
  }

  private void setupClassInstanceScrollPane (TwAccess cxn, Symbol className, Symbol baseClass, Symbol moduleScope) {
    this.className = className;
    this.baseClass = baseClass;
    this.moduleScope = moduleScope;
    setConnection(cxn);
    createScrollPaneForClass();
  }

  public void setConnection(TwAccess cxn) {
    //System.out.println("ClassInstanceScrollPane.setConnection: "+cxn);
    currentConnection = cxn;
  }

  private void createScrollPaneForClass() {
    buildTreeForClass();
    getViewport().add(classTree);
  }

  private void buildTreeForClass() {
    createRootNode();
    treeModel= new ClassInstanceTreeModel(rootNode);
    classTree = new JTree(treeModel);
    ToolTipManager.sharedInstance().registerComponent(classTree);
    classTree.setCellRenderer(new ClassInstanceTreeCellRenderer());
    classTree.setRowHeight(-1); // if less than 0, the cell renderer is queried for each entry
    classTree.setEditable(true);;
    classTree.setRootVisible(false);

    // check for WORKSPACE_HIERARCHY (also check for workspace class), add TreeExpansionListener
    if (className.equals(WORKSPACE_HIERARCHY_)) {
      classTree.addTreeExpansionListener(new WorkspaceTreeExpansionAdapter());
    } 
  }

  private void createRootNode() {
    ClassInstanceData data = null;
    if ((className.equals(MODULE_HIERARCHY_)) || (className.equals(WORKSPACE_HIERARCHY_)) || 
	(className.equals(CLASS_HIERARCHY_))) {
      data = new ClassInstanceData(className, baseClass, moduleScope);
      rootNode = new ClassInstanceDynamicTreeNode(currentConnection, data);
    } else {
      try {
	G2Definition g2Def = currentConnection.getDefinition(className);
	if (g2Def instanceof ClassDefinition) {
	  data = new ClassInstanceData(g2Def, baseClass, moduleScope);
	} else {
	  data = new ClassInstanceData(g2Def, baseClass, moduleScope);
	}
	rootNode = new ClassInstanceDynamicTreeNode(currentConnection, data);
      } catch (G2AccessException gae) {
	System.out.println(gae);
      }
    }
  }

  class WorkspaceTreeExpansionAdapter implements TreeExpansionListener {
    public void treeCollapsed(TreeExpansionEvent e) {
      TreePath path = e.getPath();
      ClassInstanceDynamicTreeNode node = (ClassInstanceDynamicTreeNode)path.getLastPathComponent();
      node.treeCollapsed(e);
    }
    public void treeExpanded(TreeExpansionEvent e) {
      TreePath path = e.getPath();
      ClassInstanceDynamicTreeNode node = (ClassInstanceDynamicTreeNode)path.getLastPathComponent();
      node.treeExpanded(e);
    }
  }
}


