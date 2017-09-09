/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2DefinitionDynamicTreeNode.java
 *
 */
package com.gensym.ntw.util;

import java.util.Vector;

import com.gensym.classes.Definition;
import com.gensym.classes.G2Definition;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Sequence;
import com.gensym.util.Sorter;
import com.gensym.util.Symbol;
import java.awt.Container;

public class G2DefinitionDynamicTreeNode extends BasicDynamicTreeNode implements BrowserSymbols {

  private ClassBrowserScrollPane parent = null;
  private Symbol moduleScope_ = ALL_;
  private Symbol baseClass_   = ROOT_;

  /**
   * Constructs a new G2DefinitionDynamicTreeNode instance with obj as the user object.
   * @param cxn The current context
   * @param obj The InstanceData user object associated with the tree node
   * @param pane The container for the JTree which hosts this tree node
   */
  public G2DefinitionDynamicTreeNode(TwAccess cxn, InstanceData obj, ClassBrowserScrollPane pane) {
    super(cxn, obj);
    parent = pane;
    moduleScope_ = parent.getModuleScope(); // use for filtering loadChildren, either ALL_ or module name
    baseClass_ = parent.getBaseClass();     // determines what to use as the root of this tree
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
    //System.out.println("G2DefinitionDynamicTreeNode.loadChildren: "+this);

    if (cxn == null) return;

    InstanceData data = (InstanceData)getUserObject();
    Symbol dataType = data.getDataType();

    //System.out.println("G2DefinitionDynamicTreeNode.loadChildren, dataType: "+dataType);

    if (dataType.equals(G2_DEFINITION_)) {
      try {
	loadSubclasses(data);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	//System.out.println(gae);
      }
    }

    else if (dataType.equals(CLASS_HIERARCHY_)) {
      try {
	loadClassHierarchy(data);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
	//System.out.println(gae);
      }
    }
    
    else {
      //System.out.println("G2DefinitionDynamicTreeNode: unhandle case in loadChildren");
    }
  }

  private void loadSubclasses(InstanceData data) throws G2AccessException {
    //System.out.println("G2DefinitionDynamicTreeNode.loadSubclasses: "+data);
    Sequence subClasses = cxn.getDirectSubclasses(data.getG2Definition().getClassName());
    if (subClasses != null && subClasses.size() > 0) {
      // sort class names descending, they getting added to tree in reverse order
      String[] classNames_ = new String[subClasses.size()];
      for (int i=0; i<subClasses.size(); i++)
	classNames_[i] = ((Symbol)subClasses.elementAt(i)).toString();
      Sorter.sort(classNames_, Sorter.DESCENDING);

      Vector classFilter = parent.getClassFilter();
      for (int i=0; i<classNames_.length; i++) {
	Symbol name_ = Symbol.intern(classNames_[i]);
	
	// check classFilter
	if (!(classFilter.contains(name_))) {
	  G2Definition g2Def = cxn.getDefinition(name_);
	  if (g2Def != null) {
	    if (g2Def instanceof Definition)
	      ((Definition)g2Def).addDefinitionListener(parent);
	    InstanceData newData = parent.getInstanceDataFactory().createInstanceData(g2Def);
	    insert(new G2DefinitionDynamicTreeNode(cxn, newData, parent), 0);
	  }
	}
      }
    }
    hasLoaded = true;
  }

  // BEGIN case of CLASS_HIERARCHY_
  private void loadClassHierarchy(InstanceData data) throws G2AccessException {
    //System.out.println("G2DefinitionDynamicTreeNode.loadClassHierarchy");
    
    if (baseClass_ == ROOT_) baseClass_ = ITEM_;

    //System.out.println("baseClass: "+baseClass);
    //Sequence subClasses = cxn.getDirectSubclasses(baseClass_);
    G2Definition g2Def = cxn.getDefinition(baseClass_);
    InstanceData newData = parent.getInstanceDataFactory().createInstanceData(g2Def);
    //if ((subClasses == null) || (subClasses.size() == 0))
    //insert(new BasicTreeNode(cxn, newData), 0);
    //else
      insert(new G2DefinitionDynamicTreeNode(cxn, newData, parent), 0);
    hasLoaded = true;
  }
}
