/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ModuleDynamicTreeNode.java
 *
 */
package com.gensym.ntw.util;

import java.util.Vector;

import com.gensym.classes.Kb;
import com.gensym.classes.Module;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.util.uitools.ModuleKBTools;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;

import javax.swing.JTree;
import java.awt.Container;

public class ModuleDynamicTreeNode extends BasicDynamicTreeNode implements BrowserSymbols {

  private ModuleBrowserScrollPane parent = null;
  private Symbol moduleScope_ = ALL_;
  private Symbol baseClass_   = ROOT_;

  /**
   * Constructs a new ModuleDynamicTreeNode instance with obj as the user object.
   * @param cxn The current context
   * @param obj The ObjectInstanceData user object associated with the tree node
   * @param pane The container for the JTree which hosts this tree node
   */
  public ModuleDynamicTreeNode(TwAccess cxn, InstanceData obj, ModuleBrowserScrollPane pane) {
    super(cxn, obj);
    parent = pane;
    moduleScope_ = parent.getModuleScope();  // use for filtering loadChildren, either ALL_ or module name
    baseClass_ = parent.getBaseClass();      // use for determining where to start the root of the tree
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
    //System.out.println("ModuleDynamicTreeNode.loadChildren: "+this);

    if (cxn == null) return;

    InstanceData data = (InstanceData)getUserObject();
    Symbol dataType = data.getDataType();

    //System.out.println("ModuleDynamicTreeNode.loadChildren, dataType: "+dataType);

    if (dataType.equals(MODULE_)) {
      try {
	loadRequiredModules(data);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	//System.out.println(gae);
      }
    } 
    
    else if (dataType.equals(MODULE_HIERARCHY_)) {
      loadModuleHierarchy(data);
    }

    else if (dataType.equals(UNREQUIRED_MODULES_)) {
      try {
	loadUnrequiredModules(data);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    else {
      //System.out.println("ModuleDynamicTreeNode: unhandle case in loadChildren");
    }
  }

  // BEGIN:: case of MODULE_
  // loads the required modules for the specified module
  private void loadRequiredModules(InstanceData data) throws G2AccessException {
    Module module = data.getModule();
    Sequence modules = module.getRequiredModules();

    Kb kb = cxn.getKb();
    for (int i=0; i<modules.size(); i++) {
      Symbol name_ = (Symbol)modules.elementAt(i);
      Module mod = kb.getModule(name_);
      if (mod != null) {
	Sequence requiredModules = mod.getRequiredModules();
	InstanceData newData = parent.getInstanceDataFactory().createInstanceData(mod);
	if (requiredModules == null || requiredModules.size() == 0)
	  insert(new BasicTreeNode(cxn, newData), 0);
	else
	  insert(new ModuleDynamicTreeNode(cxn, newData, parent), 0);
      }
    }

    hasLoaded = true;
  }
  // END:: case of MODULE_

  // BEGIN case of MODULE_HIERARCHY_
  private void loadModuleHierarchy(InstanceData data) {
    //System.out.println("ModuleDynamicTreeNode.loadModuleHierarchy");
    Module startingModule;
    try {
      // check for unrequired modules, if there are some, then add an additional dynamic node!
      if (!ModuleKBTools.isModularized(cxn)) {
	InstanceData newData = parent.getInstanceDataFactory().createInstanceData(UNREQUIRED_MODULES_);
	//insert(new UnrequiredModulesTreeNode(cxn, newData, parent), 0);
	insert(new ModuleDynamicTreeNode(cxn, newData, parent), 0);
      }

      Kb kb = cxn.getKb();
      if (baseClass_.equals(ROOT_)) 
	startingModule = kb.getTopLevelModule();
      else 
	startingModule = kb.getModule(baseClass_);

      // if startingModule is unnamed, then it's the top-level-module that isn't official yet
      // and will be display in the UNREQUIRED_MODULES_ branch of the tree
      if (startingModule != null) {
	if (startingModule.getName() != null) {
	  InstanceData newData = parent.getInstanceDataFactory().createInstanceData(startingModule);
	  if (startingModule.getRequiredModules().size() == 0) 
	    insert(new BasicTreeNode(cxn, newData), 0);
	  else 
	    insert(new ModuleDynamicTreeNode(cxn, newData, parent), 0);
	}
	
	hasLoaded = true;
      } // != null
    } catch (G2AccessException gae) {
      Trace.exception(gae);
      //System.out.println(gae);
    }
  }
  // END case of MODULE_HIERARCHY_

  // BEGIN case of UNREQUIRED_MODULES_
  private void loadUnrequiredModules(InstanceData data) throws G2AccessException {
    //System.out.println("running loadUnrequiredModules");
    
    Kb kb = cxn.getKb();
    Vector unreqMods = new Vector();
    //System.out.println("calling kb.getModules");
    Module[] allMods = kb.getModules();
    //System.out.println("back from kb.getModules, number of modules: "+allMods.length);
    Vector requiredModules = new Vector();
    Module topMod = kb.getTopLevelModule();
    Symbol name_ = topMod.getName();
    if (name_ != null) {
      //System.out.println("there is a named top-level-module: "+name_);
      requiredModules.addElement(topMod);
      ModuleKBTools.getLinearizedHierarchyForModule(cxn, topMod, requiredModules);
      
      // compare linearized Vector with Module array for "unrequired" modules
      for (int k=0; k<allMods.length; k++) {
	if (!(requiredModules.contains(allMods[k])))
	  unreqMods.addElement(allMods[k]);
      }
    } else {
      // completely unmodularized
      //System.out.println("completely unmodularized");
      for (int j=0; j<allMods.length; j++) {
	unreqMods.addElement(allMods[j]);
      }
    }
    
    // create nodes for each unrequired module
    if (unreqMods.size() > 0) {
      //System.out.println("number of unrequired modules: "+unreqMods.size());
      for (int i=0; i<unreqMods.size(); i++) {
	Module module = (Module)unreqMods.elementAt(i);
	//System.out.println("module: "+module.getName());
	requiredModules = module.getRequiredModules();
	InstanceData newData = parent.getInstanceDataFactory().createInstanceData(module);
	if (requiredModules.size() == 0)
	  insert(new BasicTreeNode(cxn, newData), 0);
	else
	  insert(new ModuleDynamicTreeNode(cxn, newData, parent), 0);
      }
    }
    
    hasLoaded = true;
  }
  // END case of UNREQUIRED_MODULES_

  //protected UnrequiredModulesTreeNode getUnrequiredModulesNode() {
  protected ModuleDynamicTreeNode getUnrequiredModulesNode() {
    //System.out.println("running getUnrequiredModulesNode()");
    //UnrequiredModulesTreeNode unreqNode = null;
    ModuleDynamicTreeNode unreqNode = null;

    if (((InstanceData)getUserObject()).getDataType().equals(MODULE_HIERARCHY_)) {
      int numKids = getChildCount();
      for (int i=0; i<numKids; i++) {
	BasicTreeNode node = (BasicTreeNode)getChildAt(i);
	InstanceData data = (InstanceData)node.getUserObject();
	if (data.getDataType().equals(UNREQUIRED_MODULES_))
	  //unreqNode = (UnrequiredModulesTreeNode)node;
	  unreqNode = (ModuleDynamicTreeNode)node;
      }
    }
    
    return unreqNode;
  }
  
}
