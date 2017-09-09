/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ModuleBrowserScrollPane.java
 *
 */
package com.gensym.ntw.util;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.Enumeration;
import java.util.Vector;

import com.gensym.classes.Item;
import com.gensym.classes.Kb;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.classes.ModuleInformation;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwGateway;
import com.gensym.ntw.util.KbEvent;
import com.gensym.ntw.util.KbModuleListener;
import com.gensym.ntw.util.uitools.ModuleKBTools;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

import javax.swing.JFrame;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.ToolTipManager;
import javax.swing.event.TreeModelEvent;

import javax.swing.event.TreeModelListener;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.TreePath;

public class ModuleBrowserScrollPane extends BrowserScrollPane
{
  private Symbol moduleScope = ALL_;  // NYI: a module filter for loading children, ALL_ or module name
  private Symbol baseClass = ROOT_;   // baseClass for workspace browser, ROOT_ or workspace class name

  public ModuleBrowserScrollPane (TwAccess cxn, Symbol moduleScope, Symbol baseClass) {
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
    InstanceData data
      = getInstanceDataFactory().createInstanceData(MODULE_HIERARCHY_);
    return new ModuleDynamicTreeNode(getConnection(), data, this);
  }

  @Override
  public void moduleCreated (KbEvent e) {
    //  insert module into tree
    Module module = e.getModule();
    //System.out.println("ModuleBrowserScrollPane.moduleCreated: "+module);
       
    try {
      if (!ModuleKBTools.isModularized(getConnection())) {
	verifyUnrequiredModulesUpToDate();
      } 
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
    
    /*
     * now check for the case where the module that was just created already existed in
     * the hierarchy (i.e. it's already listed as a dependent module by some module)
     */
    try {
      Vector requiringMods_ = new Vector();
      ModuleKBTools.getRequiringModules(getConnection(), module.getName(), requiringMods_);
      //System.out.println("requiringMods_: "+requiringMods_);
      if (requiringMods_.size() > 0) {
	Kb kb = getConnection().getKb();
	for (int i=0; i<requiringMods_.size(); i++) {
	  Vector nodes = new Vector();
	  executeFindNodesForModule(kb.getModule((Symbol)requiringMods_.elementAt(i)), rootNode, nodes);
	  for (int j=0; j<nodes.size(); j++) {
	    verifyModuleNodeUpToDate((BasicTreeNode)nodes.elementAt(j), module);
	  }
	}
      }
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }
  @Override
  public void moduleDeleted (KbEvent e) {
    // remove module from tree
    Module module = e.getModule();
    //System.out.println("ModuleBrowserScrollPane.moduleDeleted: "+module);

    Vector moduleNodes = new Vector();
    executeFindNodesForModule(module, rootNode, moduleNodes);

    for (int i=0; i<moduleNodes.size(); i++) { 
      BasicTreeNode node = (BasicTreeNode)moduleNodes.elementAt(i);
      BasicTreeNode parent = (BasicTreeNode)node.getParent();
      treeModel.removeNodeFromParent(node);
      treeModel.reload(parent);
    }

    try {
      verifyUnrequiredModulesUpToDate();
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }
  @Override
  public void moduleNameChanged (KbEvent e) {
    // locate all nodes for module and setTextRepresentation() & nodeChanged()
    Module module = e.getModule();
    //System.out.println("ModuleBrowserScrollPane.moduleNameChanged: "+module.getName());

    Vector moduleNodes = new Vector();
    executeFindNodesForModule(module, rootNode, moduleNodes);

    //System.out.println("number of matching nodes: "+moduleNodes.size());

    try {
      for (int i=0; i<moduleNodes.size(); i++)
	executeModuleNameChanged((BasicTreeNode)moduleNodes.elementAt(i));
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }
  @Override
  public void moduleDependencyChanged (KbEvent e) {
    // locate all nodes for module and fix the dependency
    Module module = e.getModule();
    Sequence dependentModules = (Sequence)e.getData();
    //System.out.println("ModuleBrowserScrollPane.moduleDependencyChanged: "+module+"  depMods: "+dependentModules);
  }
  @Override
  public void kbCleared (KbEvent e) {
    //System.out.println("ModuleBrowserScrollPane.executeKbCleared");
    Vector kids = new Vector();
    for (int i=0; i<rootNode.getChildCount(); i++) 
      kids.addElement(rootNode.getChildAt(i));
    
    for (int j=0; j<kids.size(); j++) {
      BasicTreeNode kid = (BasicTreeNode)kids.elementAt(j);
      BasicTreeNode parent = (BasicTreeNode)kid.getParent();
      treeModel.removeNodeFromParent(kid);
      treeModel.reload(parent);
    }

    treeModel.reload();
  }

  private void executeFindNodesForModule(Module module, BasicTreeNode root, Vector moduleNodes) {
    //System.out.println("ModuleBrowserScrollPane.executeFindNodesForModule: "+module.getName());
    if (!root.isLeaf && ((BasicDynamicTreeNode)root).hasLoaded) {
      int numKids = root.getChildCount();
      //System.out.println("numKids: "+numKids);
      for (int i=0; i<numKids; i++) {
	BasicTreeNode kid = (BasicTreeNode)root.getChildAt(i);
	InstanceData data = (InstanceData)kid.getUserObject();
	Module mod = data.getModule();
	if (mod != null && mod.equals(module))
	  moduleNodes.addElement(kid);
    
	if (!kid.isLeaf && ((BasicDynamicTreeNode)kid).hasLoaded) 
	  executeFindNodesForModule(module, kid, moduleNodes);
      }
    }
  }

  private void executeModuleNameChanged(BasicTreeNode node) throws G2AccessException {
    /*
     * Two special cases: 
     * 1) top-level-module becomes "unname" i.e. UNSPECIFIED
     * 2) top-level-module becomes named => no longer "unrequired"
     */

    ObjectInstanceData data = (ObjectInstanceData)node.getUserObject();
    String currentText = data.getTextRepresentation();
    String newText = data.determineStringValueForDataType(data.getDataType());
    
    //System.out.println("currentText: "+currentText+"  newText: "+newText);

    if (currentText.equals(UNSPECIFIED)) {
      // CASE: unnamed top-level-module is getting named
      //System.out.println("top-level-module is getting named");
      data.setTextRepresentation(newText);
      treeModel.nodeChanged(node);

      ModuleInformation modInfo = data.getModule().getModuleInformation();
      Sequence drm = modInfo.getDirectlyRequiredModules();

      if (drm == null || drm.size() == 0)
	treeModel.insertNodeInto(new BasicTreeNode(getConnection(), data), rootNode, 0);
      else
	treeModel.insertNodeInto(new ModuleDynamicTreeNode(getConnection(), data, this), rootNode, 0);

      treeModel.nodeStructureChanged(rootNode);

      verifyUnrequiredModulesUpToDate();
    } else if (newText.equals(UNSPECIFIED)) {
      // CASE: top-level-module is becoming unnamed, and therefore "unrequired"
      //System.out.println("top-level-module is becoming unnamed");
      data.setTextRepresentation(newText);
      treeModel.nodeChanged(node);

      verifyUnrequiredModulesUpToDate();
      treeModel.removeNodeFromParent(node);
    } else {
      data.setTextRepresentation(newText);
      treeModel.nodeChanged(node);
    }
  }

  private void verifyModuleNodeUpToDate(BasicTreeNode node, Module module) {
    /*
     * If "node" doesn't have a child node for "module", then add it
     */
    if (!node.isLeaf && ((BasicDynamicTreeNode)node).hasLoaded) {
      boolean FOUND_IT = false;
      for (int i=0; i<node.getChildCount(); i++) {
	InstanceData data = (InstanceData)node.getUserObject();
	Module mod = data.getModule();
	if (module != null && mod.equals(module))
	  FOUND_IT = true;
      }

      if (!FOUND_IT) {
	InstanceData newData = getInstanceDataFactory().createInstanceData(module);
	treeModel.insertNodeInto(new ModuleDynamicTreeNode(getConnection(), newData, this), node, 0);
      }
    }
  }

  private void verifyUnrequiredModulesUpToDate() throws G2AccessException {
    //System.out.println("verifyUnrequiredModulesUpToDate, rootNode: "+rootNode);
    ModuleDynamicTreeNode unreqNode
      = ((ModuleDynamicTreeNode)rootNode).getUnrequiredModulesNode();

    if (ModuleKBTools.isModularized(getConnection()) && unreqNode != null && unreqNode.hasLoaded) {
      //System.out.println("KB IS modularized");
      treeModel.removeNodeFromParent(unreqNode);
    }
    else {
      //System.out.println("if unreqNode is null, create it: "+unreqNode);
      if (unreqNode == null) {
	InstanceData newData = getInstanceDataFactory().createInstanceData(UNREQUIRED_MODULES_);
	treeModel.insertNodeInto(unreqNode = new ModuleDynamicTreeNode(getConnection(), newData, this), rootNode, 0);
      }

      if (unreqNode.hasLoaded) {
	//System.out.println("KB is NOT modularized");
	Vector nodesToRemove = new Vector();
	Vector unrequiredModules = new Vector();
	ModuleKBTools.getUnrequiredModules(getConnection(), unrequiredModules);
	//System.out.println("unrequiredModules: "+unrequiredModules);
	for (int i=0; i<unreqNode.getChildCount(); i++) {
	  BasicTreeNode kid = (BasicTreeNode)unreqNode.getChildAt(i);
	  InstanceData data = (InstanceData)kid.getUserObject();
	  Symbol name_ = data.getModule().getName();
	  name_ = (name_ != null ? name_ : UNSPECIFIED_);
	  if (unrequiredModules.contains(name_))
	    unrequiredModules.removeElement(name_);
	  else
	    nodesToRemove.addElement(kid);
	}

	//System.out.println("Done walking through kids, num nodes to remove: "+nodesToRemove.size()+"  nodes to add: "+unrequiredModules);

	for (int j=0; j<nodesToRemove.size(); j++) 
	  treeModel.removeNodeFromParent((BasicTreeNode)nodesToRemove.elementAt(j));

	//System.out.println("add new unrequired modules: "+unrequiredModules.size());

	if (unrequiredModules.size() > 0) {
	  Kb kb = getConnection().getKb();
	  Module module;
	  for (int k=0; k<unrequiredModules.size(); k++) {
	    Symbol name_ = (Symbol)unrequiredModules.elementAt(k);
	    //System.out.println("["+k+"]: "+name_);
	    if (name_ != null && (!name_.equals(UNSPECIFIED_)))
	      module = kb.getModule(name_);
	    else
	      module = kb.getTopLevelModule();
	    if (module != null) {
	      InstanceData newData =
		getInstanceDataFactory().createInstanceData(module);
	      treeModel.insertNodeInto(new ModuleDynamicTreeNode(getConnection(),
								 newData, this),
				       unreqNode, 0);
	    }
	  }
	}
      }
    }
    //System.out.println("leaving verifyUnrequiredModulesUpToDate");
  }
  // END:: support for KbModuleListener


  public static void main(String[] args){
    try{
      TwAccess connection = TwGateway.openConnection("localhost", "1111");
      connection.loginSession();
      
      JFrame frame = new JFrame();
      ModuleBrowserScrollPane pane = new ModuleBrowserScrollPane(connection, ALL_, ROOT_);
      frame.getContentPane().add(pane, "Center");
      frame.pack();
      frame.setVisible(true);
    }
    catch(Exception ex){
      System.out.println(ex);
    }
  }

}


