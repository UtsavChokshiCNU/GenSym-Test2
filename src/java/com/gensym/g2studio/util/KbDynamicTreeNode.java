/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 KbDynamicTreeNode.java
 *
 */
package com.gensym.g2studio.util;

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

import com.sun.java.swing.JFrame;
import com.sun.java.swing.tree.DefaultMutableTreeNode;

/**
  * DynamicTreeNode illustrates one of the possible ways in which dynamic
  * loading can be used in tree.  The basic premise behind this is that
  * getChildCount() will be messaged from JTreeModel before any children
  * are asked for.  So, the first time getChildCount() is issued the
  * children are loaded.<p>
  * It should be noted that isLeaf will also be messaged from the model.
  * The default behavior of TreeNode is to message getChildCount to
  * determine this. As such, isLeaf is subclassed to always return false.<p>
  * There are others ways this could be accomplished as well.  Instead of
  * subclassing TreeNode you could subclass JTreeModel and do the same
  * thing in getChildCount().  Or, if you aren't using TreeNode you could
  * write your own TreeModel implementation.
  * Another solution would be to listen for TreeNodeExpansion events and
  * the first time a node has been expanded post the appropriate insertion
  * events.  I would not recommend this approach though, the other two
  * are much simpler and cleaner (and are faster from the perspective of
  * how tree deals with it).
  *
  * NOTE: getAllowsChildren() can be messaged before getChildCount().
  *       For this example the nodes always allow children, so it isn't
  *       a problem, but if you do support true leaf nodes you may want
  *       to check for loading in getAllowsChildren too.
  *
  * @version 1.3 09/23/97
  * @author Scott Violet
  */

public class KbDynamicTreeNode extends DefaultMutableTreeNode {

  private TwAccess cxn;
  private JFrame frame;

  /** Have the children of this node been loaded yet? */
  protected boolean hasLoaded;

  private static final Symbol KBWORKSPACE_ = Symbol.intern("KB-WORKSPACE");

  /**
   * Constructs a new KbDynamicTreeNode instance with o as the user
   * object.
   */
  public KbDynamicTreeNode(JFrame frame, TwAccess cxn, Object obj) {
    super(obj);
    this.cxn = cxn;
    this.frame = frame;
  }
  
  public boolean isLeaf() {
    return false;
  }
  
  /**
   * If hasLoaded is false, meaning the children have not yet been
   * loaded, loadChildren is messaged and super is messaged for
   * the return value.
   */
  public int getChildCount() {
    //System.out.println("KbDynamicTreeNode.getChildCount()");
    if(!hasLoaded)
      loadChildren();
    return super.getChildCount();
  }

  public void setConnection(TwAccess connection) {
    //System.out.println("KbDynamicTreeNode.setConnection");
    cxn = connection;
  }

  /**
   * Messaged the first time getChildCount is messaged.  Creates
   * children with random names from names.
   */
  protected void loadChildren() {
    //System.out.println("KbDynamicTreeNode.loadChildren: "+this);

    KbData data = (KbData)getUserObject();
    int dataType = data.getDataType();

    if (dataType == KbData.THE_INVISIBLE_ROOT) {
      //System.out.println("dataType is THE_INVISIBLE_ROOT");
      insert(new KbDynamicTreeNode(frame, cxn, new KbData(KbData.G2_PROJECT)), 0);
      hasLoaded = true;
    }

    else if (dataType == KbData.G2_PROJECT) {
      //System.out.println("dataType is G2_PROJECT, cxn: "+cxn);
      if (cxn != null)
	loadProjectModules();
    }

    else if (dataType == KbData.G2_MODULE) {
      try {
	loadModuleChildren(data.getModule());
      } catch (G2AccessException gae) {
	System.out.println(gae);
      }
    } 

    else if (dataType == KbData.G2_KB_WORKSPACE) {
      System.out.println("dataType is G2_KB_WORKSPACE");
    } 

    else if (dataType == KbData.G2_CLASS_DEFINITION) {
      //System.out.println("dataType is G2_CLASS_DEFINITION");
      try {
	loadSubClasses(data.getClassDefinition());
      } catch (G2AccessException gae) {
	System.out.println(gae);
      }
    } 

    else if (dataType == KbData.MODULE_CLASSES) {
      //System.out.println("dataType is MODULE_CLASSES");
      KbDynamicTreeNode parent = (KbDynamicTreeNode)getParent();
      KbData parentData = (KbData)parent.getUserObject();
      try {
	loadModuleClasses(parentData.getModule());
      } catch (G2AccessException gae) {
	System.out.println(gae);
      }
    } 

    else if (dataType == KbData.MODULE_WORKSPACES) {
      //System.out.println("dataType is MODULE_WORKSPACES");
      KbDynamicTreeNode parent = (KbDynamicTreeNode)getParent();
      KbData parentData = (KbData)parent.getUserObject();
      try {
	loadModuleWorkspaces(parentData.getModule());
      } catch (G2AccessException gae) {
	System.out.println(gae);
      }
    }

    else if (dataType == KbData.MODULE_MODULES) {
      KbDynamicTreeNode parent = (KbDynamicTreeNode)getParent();
      KbData parentData = (KbData)parent.getUserObject();
      try {
	loadModuleModules(parentData.getModule());
      } catch (G2AccessException gae) {
	System.out.println(gae);
      }
    }

    else if (dataType == KbData.MODULE_SYSTEM_TABLES) {
      KbDynamicTreeNode parent = (KbDynamicTreeNode)getParent();
      KbData parentData = (KbData)parent.getUserObject();
      try {
	loadModuleSystemTables(parentData.getModule());
      } catch (G2AccessException gae) {
	System.out.println(gae);
      }
    }
  }

  private void loadProjectModules() {
    Vector modules = new Vector();
    try {
      Module topLevelModule = cxn.getKb().getTopLevelModule();

      frame.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

      if (topLevelModule.getRequiredModules().size() == 0)
	modules.addElement(new ModuleNode(topLevelModule, false));
      else
	modules.addElement(new ModuleNode(topLevelModule, true));

      getRequiredModules(topLevelModule, modules);

      ModuleNode node;
      for (int i=0; i<modules.size(); i++) {
	node = (ModuleNode)modules.elementAt(i);
	insert(new KbDynamicTreeNode(frame, cxn, new KbData(node.module)), i);
      }

      hasLoaded = true;
    } catch (G2AccessException gae) {
      System.out.println(gae);
    }

    frame.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));
  }

  private void getRequiredModules(Module module, Vector modules) {
    Symbol moduleName;
    Module tmpModule;
    ModuleNode moduleNode;
    boolean hasRequiredModules = false;

    try {
      Sequence requiredModules = module.getRequiredModules();
      for (int i =0; i<requiredModules.size(); i++) {
	moduleName = (Symbol)requiredModules.elementAt(i);
	tmpModule = cxn.getKb().getModule(moduleName);
	Sequence moreModules = tmpModule.getRequiredModules();

	if (moreModules.size() == 0)
	  hasRequiredModules = false;
	else 
	  hasRequiredModules = true;

	// make sure modules is not already in the Vector of modules
	Symbol tmpName;
	boolean found = false;
	for (int j=0; j<modules.size(); j++) {
	  tmpName = ((ModuleNode)modules.elementAt(j)).module.getName();
	  if (moduleName.equals(tmpName))
	      found = true;
	}
	if (!found) 
	  modules.addElement(new ModuleNode(tmpModule, hasRequiredModules));
	
	if (hasRequiredModules)
	  getRequiredModules(tmpModule, modules);
      }  
    } catch (G2AccessException gae) {
      System.out.println(gae);
    }
  }

  private void loadModuleChildren(Module module) throws G2AccessException { 
    /*
     * 1. add SYSTEM_TABLES node
     * 2. add CLASSES node
     * 3. add WORKSPACES node
     * 4. add MODULES node
     */
    KbData data;
    KbDynamicTreeNode newNode;
    int counter = 0;

    data = new KbData(KbData.MODULE_SYSTEM_TABLES);
    newNode = new KbDynamicTreeNode(frame, cxn, data);
    insert(newNode, counter++);

    data = new KbData(KbData.MODULE_CLASSES);
    newNode = new KbDynamicTreeNode(frame, cxn, data);
    insert(newNode, counter++);

    data = new KbData(KbData.MODULE_WORKSPACES);
    newNode = new KbDynamicTreeNode(frame, cxn, data);
    insert(newNode, counter++);

    data = new KbData(KbData.MODULE_MODULES);
    newNode = new KbDynamicTreeNode(frame, cxn, data);
    insert(newNode, counter++);
 
    hasLoaded = true;
  }

  private void loadModuleWorkspaces(Module module) throws G2AccessException {
    Symbol moduleName = module.getName();
    KbData data;
    KbTreeNode newNode;
    Sequence wksps = cxn.getNamedWorkspaces();

    KbWorkspace wksp;
    int counter = 0;
    for (int i=0; i<wksps.size(); i++) {
      wksp = (KbWorkspace)cxn.getUniqueNamedItem(KBWORKSPACE_, (Symbol)wksps.elementAt(i));
      if (moduleName.equals(wksp.getContainingModule())) {
	data = new KbData(wksp, (Symbol)wksps.elementAt(i));
	newNode = new KbTreeNode(cxn, data);
	insert(newNode, counter++);
      }
    }

    hasLoaded = true;
  }

  private void loadModuleModules(Module module) throws G2AccessException { 
    KbData data;
    KbDynamicTreeNode newNode;
    Sequence modules = module.getRequiredModules();
    Module mod;
    for (int i=0; i<modules.size(); i++) {
      mod = cxn.getKb().getModule((Symbol)modules.elementAt(i));
      data = new KbData(mod);
      newNode = new KbDynamicTreeNode(frame, cxn, data);
      // dont use add() here, add calls insert(newNode, getChildCount()),
      // so if you want to use add, just be sure to set hasLoaded = true first
      insert(newNode, i);
    }

    hasLoaded = true;
  }

  private void loadSubClasses(ClassDefinition def) throws G2AccessException {
    Symbol tmpName;
    Vector rootNodes = new Vector();
    boolean hasSubclasses;

    Sequence subClasses = cxn.getDirectSubclasses(def.getClassName());
    for (int i=0; i<subClasses.size(); i++) {
      tmpName = (Symbol)subClasses.elementAt(i);
      Sequence userSubClasses = cxn.getDirectSubclasses(tmpName);
      if (userSubClasses.size() == 0)
	hasSubclasses = false;
      else hasSubclasses = true;   
      rootNodes.addElement(new ClassDefNode((ClassDefinition)cxn.getDefinition(tmpName), hasSubclasses));
    }

    /*
     * Add KbDynamicTreeNodes for nodes with leaves, otherwise add KbTreeNode
     */
    KbData data;
    KbTreeNode newLeafNode;
    KbDynamicTreeNode newNode;
    ClassDefNode node;
    for (int i=0; i<rootNodes.size(); i++) {
      node = (ClassDefNode)rootNodes.elementAt(i);
      data = new KbData(node.classDef);
      if (node.hasLeaves) {
	newNode = new KbDynamicTreeNode(frame, cxn, data);
	insert(newNode, i);
      } else {
	newLeafNode = new KbTreeNode(cxn, data);
	insert(newLeafNode, i);
      }
    }

    hasLoaded = true;
  }

  private void loadModuleSystemTables(Module module) throws G2AccessException {
    Sequence systemTables = module.getSystemTables();
    if (systemTables != null && systemTables.size() > 0) {
      SystemTable table;
      KbData data;
      KbTreeNode node;
      for (int i=0; i<systemTables.size(); i++) {
	table = (SystemTable)systemTables.elementAt(i);
	data = new KbData(table);
	node = new KbTreeNode(cxn, data);
	insert(node, i);
      }
    }

    hasLoaded = true;
  }

  private void loadModuleClasses(Module module) throws G2AccessException {
    Vector rootNodes = new Vector();
    Symbol startingClass = G2ClassSymbols.ITEM_;

    frame.setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

    getSubClasses(startingClass, module.getName(), rootNodes);

    /*
     * Add KbDynamicTreeNodes for nodes with leaves, otherwise add KbTreeNode
     */
    KbData data;
    KbTreeNode newLeafNode;
    KbDynamicTreeNode newNode;
    ClassDefNode node;
    for (int i=0; i<rootNodes.size(); i++) {
      node = (ClassDefNode)rootNodes.elementAt(i);
      data = new KbData(node.classDef);
      if (node.hasLeaves) {
	newNode = new KbDynamicTreeNode(frame, cxn, data);
	insert(newNode, i);
      } else {
	newLeafNode = new KbTreeNode(cxn, data);
	insert(newLeafNode, i);
      }
    }

    frame.setCursor(Cursor.getPredefinedCursor(Cursor.DEFAULT_CURSOR));

    hasLoaded = true;
  }

  private void getSubClasses(Symbol className, Symbol moduleName, Vector userRoots) {
    Symbol userClass;
    G2Definition g2Def;
    boolean hasSubclasses = false;

    try {
      Sequence subClasses = cxn.getDirectSubclasses(className);
      for (int i =0; i<subClasses.size(); i++) {
	try {
	  userClass = (Symbol)subClasses.elementAt(i);
	  g2Def = cxn.getDefinition(userClass);

	  if (g2Def instanceof ClassDefinition) {
	    if (moduleName.equals(((ClassDefinition)g2Def).getContainingModule())) {
	      Sequence userSubClasses = cxn.getDirectSubclasses(g2Def.getClassName());
	      if (userSubClasses.size() == 0)
		hasSubclasses = false;
	      else hasSubclasses = true;
	      userRoots.addElement(new ClassDefNode((ClassDefinition)g2Def, hasSubclasses));
	    }
	  } else {
	    getSubClasses((Symbol)subClasses.elementAt(i), moduleName, userRoots);
	  }
	} catch (G2AccessException gae) {
	  System.out.println(gae);
	}
      }
    } catch (G2AccessException gae) {
      System.out.println(gae);
    }
  }

  class ClassDefNode {
    ClassDefinition classDef;
    boolean hasLeaves;

    public ClassDefNode(ClassDefinition def, boolean hasLeaves) {
      this.classDef = def;
      this.hasLeaves = hasLeaves;
    }
  }

  class ModuleNode {
    Module module;
    boolean hasRequiredModules;

    public ModuleNode(Module module, boolean hasRequiredModules) {
      this.module = module;
      this.hasRequiredModules = hasRequiredModules;
    }
  }
}
