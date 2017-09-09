/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ClassInstanceDynamicTreeNode.java
 *
 */
package com.gensym.uitools.browsers;

import java.util.Vector;

import com.gensym.classes.ClassDefinition;
import com.gensym.classes.Entity;
import com.gensym.classes.G2Definition;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.classes.SystemTable;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.WorkspaceAdapter;
import com.gensym.util.WorkspaceEvent;

import com.sun.java.swing.event.TreeExpansionEvent;
import com.sun.java.swing.event.TreeExpansionListener;
import com.sun.java.swing.tree.DefaultMutableTreeNode;


public class ClassInstanceDynamicTreeNode extends DefaultMutableTreeNode implements BrowserSymbols, TreeExpansionListener {

  private TwAccess cxn;
  private TreeNodeWorkspaceAdapter wkspAdapter;

  /** Have the children of this node been loaded yet? */
  protected boolean hasLoaded;

  /**
   * Constructs a new ClassInstanceDynamicTreeNode instance with obj as the user object.
   */
  public ClassInstanceDynamicTreeNode(TwAccess cxn, Object obj) {
    super(obj);
    this.cxn = cxn;
  }
  
  public boolean isLeaf() {
    return false;
  }
  
  /**
   * If hasLoaded is false, meaning the children have not yet been loaded, 
   * loadChildren is messaged and super is messaged for the return value.
   */
  public int getChildCount() {
    if(!hasLoaded)
      loadChildren();
    return super.getChildCount();
  }

  public void setConnection(TwAccess connection) {
    cxn = connection;
  }

  public void treeCollapsed(TreeExpansionEvent e) {
    //System.out.println("ClassInstanceDynamicTreeNode.treeCollapsed");
    ClassInstanceData data = (ClassInstanceData)getUserObject();
    if (data.getDataType() == ClassInstanceData.G2_KB_WORKSPACE) {
      KbWorkspace wksp = data.getKbWorkspace();
      if (wksp != null) {
	try {
	  wksp.removeWorkspaceListener(wkspAdapter);
	} catch (G2AccessException gae) {
	  Trace.exception(gae);
	}
      }
    }
  }
  public void treeExpanded(TreeExpansionEvent e) {
    //System.out.println("ClassInstanceDynamicTreeNode.treeExpanded");
    ClassInstanceData data = (ClassInstanceData)getUserObject();
    if (data.getDataType() == ClassInstanceData.G2_KB_WORKSPACE) {
      KbWorkspace wksp = data.getKbWorkspace();
      if (wksp != null) {
	try { 
	  wksp.addWorkspaceListener(wkspAdapter);
	  loadSubworkspaces(wksp, data);
	} catch (G2AccessException gae) {
	  Trace.exception(gae);
	}
      }
    }
  }

  /**
   * Messaged the first time getChildCount is messaged.  Creates
   * children with random names from names.
   */
  protected void loadChildren() {
    System.out.println("ClassInstanceDynamicTreeNode.loadChildren: "+this);

    if (cxn == null) return;

    ClassInstanceData data = (ClassInstanceData)getUserObject();
    int dataType = data.getDataType();

    System.out.println("dataType: "+dataType);

    if (dataType == ClassInstanceData.MODULE_HIERARCHY) {
      loadModuleHierarchy(data);
    }

    else if (dataType == ClassInstanceData.WORKSPACE_HIERARCHY) {
      try{
	loadWorkspaceHierarchy(data);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	System.out.println(gae);
      }
    }

    else if (dataType == ClassInstanceData.CLASS_HIERARCHY) {
      try {
	loadClassHierarchy(data);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	System.out.println(gae);
      }
    }

    else if (dataType == ClassInstanceData.KNOWLEDGE_BASE) {
      try {
	loadSubworkspaces(data);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	System.out.println(gae);
      }
    }

    else if (dataType == ClassInstanceData.G2_MODULE) {
      try {
	loadRequiredModules(data);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	System.out.println(gae);
      }
    } 

    else if (dataType == ClassInstanceData.G2_KB_WORKSPACE) {
      try {
	loadSubworkspaces(data);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	System.out.println(gae);
      }
    } 

    else if (dataType == ClassInstanceData.G2_DEFINITION) {
      try {
	loadSubclasses(data);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	System.out.println(gae);
      }
    }

    else if (dataType == ClassInstanceData.G2_CLASS_DEFINITION) {
      System.out.println("loadChildren >> dataType is G2_CLASS_DEFINITION");
    } 

    else {
      System.out.println("ClassInstanceDynamicTreeNode: unhandle case in loadChildren");
    }
  }

  // loads the workspace hierarchy for either the entire KB or from a specified workspace
  private boolean toplevelWSExist = false;
  private void loadWorkspaceHierarchy(ClassInstanceData nodeData) throws G2AccessException {
    ClassInstanceData data;
    Symbol moduleScope = nodeData.getModuleScope();
    Symbol baseClass   = nodeData.getBaseClass();

    if (baseClass.equals(ROOT_)) {
      data = new ClassInstanceData(KNOWLEDGE_BASE_, baseClass, moduleScope);

      toplevelWSExist = false;
      toplevelWorkspacesExist(KB_WORKSPACE_);
      if (toplevelWSExist)
	insert(new ClassInstanceDynamicTreeNode(cxn, data), 0);
      else
	insert(new ClassInstanceTreeNode(cxn, data), 0);
    }
    else {
      KbWorkspace wksp = nodeData.getKbWorkspace();
      data = new ClassInstanceData(wksp, baseClass, moduleScope);
      if (workspaceItemsWithSubworkspacesExist(wksp))
	insert(new ClassInstanceDynamicTreeNode(cxn, data), 0);
      else
	insert(new ClassInstanceTreeNode(cxn, data), 0);
    }

    hasLoaded = true;
  }

  // loads the sub-workspaces for a given workspace
  private void loadSubworkspaces(ClassInstanceData nodeData) throws G2AccessException {
    KbWorkspace wksp = nodeData.getKbWorkspace();
    if (wksp == null) {
      // case of KNOWLEDGE_BASE
      Vector topWS = new Vector();
      loadTopLevelWorkspaces(KB_WORKSPACE_, topWS);

      // all top-level workspaces have been gathered an placed in topWS
      ClassInstanceData data;
      for (int i=0; i<topWS.size(); i++) {
	wksp = (KbWorkspace)topWS.elementAt(i);
	data = new ClassInstanceData(wksp, nodeData.getBaseClass(), nodeData.getModuleScope());
	if (workspaceItemsWithSubworkspacesExist(wksp))
	  insert(new ClassInstanceDynamicTreeNode(cxn, data), i);
	else
	  insert(new ClassInstanceTreeNode(cxn, data), i);
      }
    } else {
      loadSubworkspaces(wksp, nodeData);
    }

    hasLoaded = true;
  }

  private void loadTopLevelWorkspaces(Symbol baseClass, Vector topWS) throws G2AccessException {
    KbWorkspace wksp;
    Sequence containmentHierarchy;

    Sequence allWorkspaces = cxn.getStrictInstancesOfClass(baseClass);
    if (allWorkspaces != null) {
      for (int i=0; i<allWorkspaces.size(); i++) {
	wksp = (KbWorkspace)allWorkspaces.elementAt(i);
	containmentHierarchy = wksp.getContainmentHierarchy();
	if (containmentHierarchy == null || containmentHierarchy.size() == 0)
	  topWS.addElement(wksp);
      }
    }

    Sequence subClasses = cxn.getDirectSubclasses(baseClass);
    for (int j=0; j<subClasses.size(); j++) {
      loadTopLevelWorkspaces((Symbol)subClasses.elementAt(j), topWS);
    }
  }

  private void loadSubworkspaces(KbWorkspace wksp, ClassInstanceData data) throws G2AccessException {
    //System.out.println("loadSubworkspaces for wksp");
    if (wkspAdapter == null) {
      //System.out.println("create a wkspAdapter for this node");
      wkspAdapter = new TreeNodeWorkspaceAdapter();
    }

    Item[] items = wksp.getItems();
    if (items != null && items.length > 0) {
      ClassInstanceData newData;
      KbWorkspace subWS;
      int cnt = 0;
      for (int i=0; i<items.length; i++) {
	if (items[i] instanceof Entity) {
	  subWS = ((Entity)items[i]).getSubworkspace();
	  if (subWS != null) {
	    newData = new ClassInstanceData(subWS, data.getBaseClass(), data.getModuleScope());
	    if (workspaceItemsWithSubworkspacesExist(subWS))
	      insert(new ClassInstanceDynamicTreeNode(cxn, newData), cnt++);
	    else
	      insert(new ClassInstanceTreeNode(cxn, newData), cnt++);
	  } 
	}
      }
    }
  }

  private void toplevelWorkspacesExist(Symbol baseClass) throws G2AccessException {
    KbWorkspace wksp;
    Sequence containmentHierarchy;

    Sequence allWorkspaces = cxn.getStrictInstancesOfClass(baseClass);
    if (allWorkspaces != null) {
      for (int i=0; i<allWorkspaces.size(); i++) {
	wksp = (KbWorkspace)allWorkspaces.elementAt(i);
	containmentHierarchy = wksp.getContainmentHierarchy();
	if (containmentHierarchy == null || containmentHierarchy.size() == 0)
	  toplevelWSExist = true;
      }
    }

    Sequence subClasses = cxn.getDirectSubclasses(baseClass);
    for (int j=0; j<subClasses.size(); j++) {
      toplevelWorkspacesExist((Symbol)subClasses.elementAt(j));
    }
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
	System.out.println(gae);
      } catch (G2AccessException gae2) {
	Trace.exception(gae2);
      }
    }
    return false;
  }
  
  class TreeNodeWorkspaceAdapter extends WorkspaceAdapter {
    @Override
    public void workspaceItemAdded (WorkspaceEvent event) {
      System.out.println("ClassInstanceDynamicTreeNode.workspaceItemAdded");
    }
    @Override
    public void workspaceItemRemoved (WorkspaceEvent event) {
      System.out.println("ClassInstanceDynamicTreeNode.workspaceItemRemoved");
    }
    @Override
    public void receivedInitialDownload(WorkspaceEvent event) {
      //System.out.println("ClassInstanceDynamicTreeNode.receivedInitialDownload");
    }
    @Override
    public void workspaceItemAttributesChanged(WorkspaceEvent evt) {
      //System.out.println("ClassInstanceDynamicTreeNode.workspaceItemAttributesChanged");
    }
  }

  // loads the module hierarchy for either the entire KB or from a specified module
  private void loadModuleHierarchy(ClassInstanceData data) {
    Module startingModule;
    ClassInstanceData newData;

    Symbol baseClass = data.getBaseClass();
    Symbol moduleScope = data.getModuleScope();

    try {
      //if (moduleScope.equals(ALL_))
      if (baseClass.equals(ROOT_))
	startingModule = cxn.getKb().getTopLevelModule();
      else 
	startingModule = cxn.getKb().getModule(baseClass);
	//startingModule = cxn.getKb().getModule(moduleScope);
      
      newData = new ClassInstanceData(startingModule, baseClass, moduleScope);

      if (startingModule.getRequiredModules().size() == 0)
	insert(new ClassInstanceTreeNode(cxn, newData), 0);
      else 
	insert(new ClassInstanceDynamicTreeNode(cxn, newData), 0);
 
      hasLoaded = true;
    } catch (G2AccessException gae) {
      Trace.exception(gae);
      System.out.println(gae);
      // check case of unmodularized KB
    }
  }

  // loads the required modules for the specified module
  private void loadRequiredModules(ClassInstanceData data) throws G2AccessException {
    Module module = data.getModule();
    Sequence modules = module.getRequiredModules();
    Module mod;
    Sequence requiredModules;
    ClassInstanceData newData;
    for (int i=0; i<modules.size(); i++) {
      mod = cxn.getKb().getModule((Symbol)modules.elementAt(i));
      requiredModules = mod.getRequiredModules();
      newData = new ClassInstanceData(mod, data.getBaseClass(), data.getModuleScope());
      if (requiredModules.size() == 0)
	insert(new ClassInstanceTreeNode(cxn, newData), i);
      else
	insert(new ClassInstanceDynamicTreeNode(cxn, newData), i);
    }

    hasLoaded = true;
  }

  // loads the class hiearchy for either the entire KB or for a specified module.
  Symbol CONTAINING_MODULE_;
  private void loadClassHierarchy(ClassInstanceData data) throws G2AccessException {
    //System.out.println("running loadClassHierarchy, scope: "+scope);
    Symbol moduleScope = data.getModuleScope();
    Symbol baseClass = data.getBaseClass(); // ITEM_

    if (baseClass == ROOT_) baseClass = ITEM_;

    //System.out.println("baseClass: "+baseClass);
    Sequence subClasses = cxn.getDirectSubclasses(baseClass);
    G2Definition g2Def = cxn.getDefinition(baseClass);
    ClassInstanceData newData = new ClassInstanceData(g2Def, baseClass, moduleScope);
    if ((subClasses == null) || (subClasses.size() == 0))
      insert(new ClassInstanceTreeNode(cxn, newData), 0);
    else
      insert(new ClassInstanceDynamicTreeNode(cxn, newData), 0);
    hasLoaded = true;
  }

  private void loadSubclasses(ClassInstanceData data) throws G2AccessException {
    Symbol baseClass = data.getBaseClass();
    Symbol moduleScope = data.getModuleScope();
    Sequence subClasses = cxn.getDirectSubclasses(baseClass);
    if (subClasses != null) {
      Symbol name;
      G2Definition g2Def;
      ClassInstanceData newData;
      for (int i=0; i<subClasses.size(); i++) {
	name = (Symbol)subClasses.elementAt(i);
	g2Def = cxn.getDefinition(name);
	newData = new ClassInstanceData(g2Def, name, moduleScope);
	if (cxn.getDirectSubclasses(name).size() == 0)
	  insert(new ClassInstanceTreeNode(cxn, newData), i);
	else
	  insert(new ClassInstanceDynamicTreeNode(cxn, newData), i);
      }
    }
    hasLoaded = true;
  }
}
