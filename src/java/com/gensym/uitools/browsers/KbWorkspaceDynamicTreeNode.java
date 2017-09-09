/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 KbWorkspaceDynamicTreeNode.java
 *
 */
package com.gensym.uitools.browsers;

import java.util.Vector;

import com.gensym.classes.Entity;
import com.gensym.classes.Item;
import com.gensym.classes.Kb;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Symbol;
import com.gensym.util.WorkspaceAdapter;
import com.gensym.util.WorkspaceEvent;
import java.awt.Container;
import com.gensym.ntw.util.BasicTreeNode;
import com.gensym.ntw.util.BasicDynamicTreeNode;
import com.gensym.ntw.util.BrowserSymbols;
import com.gensym.ntw.util.BrowserScrollPane;
import com.gensym.ntw.util.InstanceData;

public class KbWorkspaceDynamicTreeNode extends BasicDynamicTreeNode implements BrowserSymbols {

  private WorkspaceBrowserScrollPane parent = null;
  private Symbol moduleScope = ALL_;
  private Symbol baseClass = ROOT_;

  private TreeNodeWorkspaceAdapter workspaceAdapter;

  /**
   * Constructs a new KbWorkspaceDynamicTreeNode instance with obj as the user object.
   * @param cxn The current context
   * @param obj The ObjectInstanceData user object associated with the tree node
   * @param pane The container for the JTree which hosts this tree node
   */
  public KbWorkspaceDynamicTreeNode(TwAccess cxn, InstanceData obj, WorkspaceBrowserScrollPane pane) {
    super(cxn, obj);
    parent = pane;
    moduleScope = parent.getModuleScope(); // use for filtering loadChildren, either ALL_ or module name
    baseClass = parent.getBaseClass();     // use for determining where to start the root of the tree
    workspaceAdapter = new TreeNodeWorkspaceAdapter();
  }
  
  @Override
  protected Container getParentWindow()
  {
    return parent;
  }

  /**
   * Messaged the first time getChildCount is messaged.
   */
  @Override
  protected void loadChildren() {
    //System.out.println("KbWorkspaceDynamicTreeNode.loadChildren: "+this);

    if (cxn == null) return;

    InstanceData data = (InstanceData)getUserObject();
    Symbol dataType = data.getDataType();

    //System.out.println("KbWorkspaceDynamicTreeNode.loadChildren, dataType: "+dataType);

    if (dataType.equals(KB_WORKSPACE_)) {
      try {
	loadSubworkspaces(data);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	//System.out.println(gae);
      }
    } 

    else if (dataType.equals(WORKSPACE_HIERARCHY_)) {
      try{
	loadWorkspaceHierarchy(data);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	//System.out.println(gae);
      }
    } 

    else if (dataType.equals(KNOWLEDGE_BASE_)) {
      try {
	loadSubworkspaces(data);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	//System.out.println(gae);
      }
    }

    else {
      //System.out.println("KbWorkspaceDynamicTreeNode: unhandle case in loadChildren");
    }
  }

  // loads the sub-workspaces for a given workspace
  private void loadSubworkspaces(InstanceData nodeData) throws G2AccessException {
    //System.out.println("loadSubworkspaces");
    KbWorkspace wksp = (KbWorkspace)nodeData.getItem();
    if (wksp == null) {
      // case of KNOWLEDGE_BASE
      Vector topWS = new Vector();
      gatherTopLevelWorkspaces(KB_WORKSPACE_, topWS);
      //System.out.println("back from gatherTopLevelWorkspaces, number: "+topWS.size());

      // all top-level workspaces have been gathered an placed in topWS
      InstanceData data;
      for (int i=0; i<topWS.size(); i++) {
	wksp = (KbWorkspace)topWS.elementAt(i);
	data = parent.getInstanceDataFactory().createInstanceData(wksp);
	//if (workspaceItemsWithSubworkspacesExist(wksp))
	  insert(new KbWorkspaceDynamicTreeNode(cxn, data, parent), i);
	  //else
	  //insert(new BasicTreeNode(cxn, data), i);
      }
    } else {
      //System.out.println("case of KB_WORKSPACE");
      loadSubworkspaces(wksp, nodeData);
    }

    hasLoaded = true;
  }

  private void gatherTopLevelWorkspaces(Symbol baseClass, Vector topWS) throws G2AccessException {
    //System.out.println("running gatherTopLevelWorkspaces, baseClass: "+baseClass);
    Kb kb = cxn.getKb();
    Module mod = kb.getTopLevelModule();
    Module[] modules = kb.getModules();

    for (int p=0; p<modules.length; p++) {
      //System.out.println("["+p+"]: modname? "+modules[p].getName());
      KbWorkspace[] workspaces = modules[p].getTopLevelKbWorkspaces();
      //System.out.println("num workspaces: "+workspaces.length);
      for (int i=0; i<workspaces.length; i++) {
	topWS.addElement(workspaces[i]);
      }
    }
  }

  private void loadSubworkspaces(KbWorkspace wksp, InstanceData data) throws G2AccessException {
    //System.out.println("loadSubworkspaces for wksp");
    if (workspaceAdapter == null)
      workspaceAdapter = new TreeNodeWorkspaceAdapter();

    wksp.addWorkspaceListener(workspaceAdapter);

    Item[] items = wksp.getItems();
    //System.out.println("items: "+items);
    if (items != null && items.length > 0) {
      for (int i=0; i<items.length; i++) {
	if (items[i] instanceof Entity) {
	  KbWorkspace subWS = ((Entity)items[i]).getSubworkspace();
	  if (subWS != null) {
	    InstanceData newData = parent.getInstanceDataFactory().createInstanceData(subWS);
	    //if (workspaceItemsWithSubworkspacesExist(subWS))
	      insert(new KbWorkspaceDynamicTreeNode(cxn, newData, parent), 0);
	      //else
	      //  insert(new BasicTreeNode(cxn, newData), 0);
	  } 
	}
      }
    }

    wksp.removeWorkspaceListener(workspaceAdapter);
  }
 
  // BEGIN: case of WORKSPACE_HIERARCHY_
  private void loadWorkspaceHierarchy(InstanceData nodeData) throws G2AccessException {
    //System.out.println("running loadWorkspaceHierarchy");
    if (baseClass.equals(ROOT_)) {
      //System.out.println("case of ROOT_");
      InstanceData data = parent.getInstanceDataFactory().createInstanceData(KNOWLEDGE_BASE_);
      insert(new KbWorkspaceDynamicTreeNode(cxn, data, parent), 0);
    }
    else {
      KbWorkspace wksp = (KbWorkspace)nodeData.getItem();
      InstanceData data = parent.getInstanceDataFactory().createInstanceData(wksp);
      //if (workspaceItemsWithSubworkspacesExist(wksp))
	insert(new KbWorkspaceDynamicTreeNode(cxn, data, parent), 0);
	//else
	//insert(new BasicTreeNode(cxn, data), 0);
    }

    hasLoaded = true;
  }

  private boolean workspaceItemsWithSubworkspacesExist(KbWorkspace wksp) {
    TreeNodeWorkspaceAdapter wsAdapter = new TreeNodeWorkspaceAdapter();
    try {
      wksp.addWorkspaceListener(wsAdapter);
      Item[] items = wksp.getItems();
      if (items != null && items.length > 0) {
	for (int i=0; i<items.length; i++) {
	  if (items[i] instanceof Entity) {
	    if (((Entity)items[i]).getSubworkspace() != null) {
	      wksp.removeWorkspaceListener(wsAdapter);
	      return true;
	    }
	  }
	}
      }
      wksp.removeWorkspaceListener(wsAdapter);
    } catch (G2AccessException gae) {
      try {
	wksp.removeWorkspaceListener(wsAdapter);
	Trace.exception(gae);
	//System.out.println(gae);
      } catch (G2AccessException gae2) {
	Trace.exception(gae2);
      }
    }
    return false;
  }
  // END: case of WORKSPACE_HIERARCY_

  class TreeNodeWorkspaceAdapter extends WorkspaceAdapter {
    @Override
    public void workspaceItemAdded (WorkspaceEvent event) {}
    @Override
    public void workspaceItemRemoved (WorkspaceEvent event) {}
    @Override
    public void receivedInitialDownload(WorkspaceEvent event) {}
    @Override
    public void workspaceItemAttributesChanged(WorkspaceEvent evt) {}
  }
  // END:: WorkspaceAdapter
}
