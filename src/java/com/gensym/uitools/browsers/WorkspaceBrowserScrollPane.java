/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceBrowserScrollPane.java
 *
 */
package com.gensym.uitools.browsers;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Enumeration;
import java.util.Vector;

import com.gensym.ntw.util.*;
import com.gensym.classes.Item;
import com.gensym.classes.Kb;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.KbEvent;
import com.gensym.ntw.util.KbModuleListener;
import com.gensym.util.ItemEvent;
import com.gensym.util.ItemListener;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.ToolTipManager;
import javax.swing.event.TreeModelEvent;
import javax.swing.event.TreeModelListener;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.TreePath;
import com.gensym.ntw.util.BasicDynamicTreeNode;
import com.gensym.ntw.util.BrowserSymbols;
import com.gensym.ntw.util.BrowserScrollPane;
import com.gensym.ntw.util.InstanceDataFactory;
import com.gensym.ntw.util.InstancePopupMenuFactory;
import com.gensym.ntw.util.DefaultObjectInstancePopupMenuFactory;
import com.gensym.ntw.util.InstanceData;

public class WorkspaceBrowserScrollPane extends BrowserScrollPane
{

  private Symbol moduleScope, baseClass;
  
  public WorkspaceBrowserScrollPane(TwAccess cxn,
				    Symbol moduleScope,
				    Symbol baseClass)
  {
    super(cxn);
    this.moduleScope = moduleScope;
    this.baseClass   = baseClass;
    initTree();
  }

  public Symbol getModuleScope() {
    return moduleScope;
  }

  public Symbol getBaseClass() {
    return baseClass;
  }

  @Override
  protected InstanceDataFactory createInstanceDataFactory()
  {
    return new DefaultClassInstanceDataFactory();
  }

  @Override
  protected InstancePopupMenuFactory createInstancePopupMenuFactory()
  {
    return new DefaultObjectInstancePopupMenuFactory();
  }
  
  @Override
  protected BasicDynamicTreeNode createRootNode() {
    InstanceData data = getInstanceDataFactory().createInstanceData(WORKSPACE_HIERARCHY_);
    return new KbWorkspaceDynamicTreeNode(getConnection(), data, this);
  }

}


