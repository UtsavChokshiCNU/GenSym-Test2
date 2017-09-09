/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ObjectDynamicTreeNode.java
 *
 */
package com.gensym.uitools.browsers;

import java.util.Vector;

import com.gensym.classes.ClassDefinition;
import com.gensym.classes.DefaultJunction;
import com.gensym.classes.Entity;
import com.gensym.classes.Item;
import com.gensym.classes.Kb;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.classes.NameBox;
import com.gensym.classes.Procedure;
import com.gensym.classes.TableItem;
import com.gensym.classes.TextBox;
import com.gensym.dlg.ErrorDialog;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.WorkspaceAdapter;
import com.gensym.util.WorkspaceEvent;

import javax.swing.event.TreeExpansionEvent;
import javax.swing.event.TreeExpansionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import java.awt.Container;
import com.gensym.ntw.util.BasicTreeNode;
import com.gensym.ntw.util.BasicDynamicTreeNode;
import com.gensym.ntw.util.BrowserSymbols;
import com.gensym.ntw.util.BrowserScrollPane;
import com.gensym.ntw.util.InstanceData;


public class ObjectDynamicTreeNode extends BasicDynamicTreeNode implements BrowserSymbols {

  private static Resource i18n = Resource.getBundle("com/gensym/uitools/browsers/Messages");
 
  private ObjectBrowserScrollPane parent = null;
  private Symbol moduleScope = ALL_;

  /**
   * Constructs a new ObjectDynamicTreeNode instance with obj as the user object.
   * @param cxn The current context
   * @param obj The InstanceData user object associated with the tree node
   * @param pane The container for the JTree which hosts this tree node
   */
  public ObjectDynamicTreeNode(TwAccess cxn, InstanceData obj, ObjectBrowserScrollPane pane) {
    super(cxn, obj);
    parent = pane;
    moduleScope = parent.getModuleScope(); // use for filtering loadChildren, either ALL_ or module name
    
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
    //System.out.println("ObjectDynamicTreeNode.loadChildren: "+this);

    if (cxn == null) return;

    InstanceData data = (InstanceData)getUserObject();
    Symbol dataType = data.getDataType();

    //System.out.println("loadChildren cont. dataType>> "+dataType);

    if (dataType.equals(OBJECT_HIERARCHY_)) {
      try {
	loadObjectHiearchy();
      } catch (G2AccessException gae) {
	Trace.exception(gae);
 	new ErrorDialog(null, i18n.getString("G2AccessException"), true, 
			gae.getMessage(), null).setVisible(true);
      }
    }

    else if (dataType.equals(MODULE_)) {
      try {
	loadTopLevelWorkspacesForModule(data);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    else if (dataType.equals(KB_WORKSPACE_)) {
      try {
	loadItemsOnWorkspace((KbWorkspace)data.getItem());
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }
    
    else if ((dataType.equals(ENTITY_))) {
      Entity entity = (Entity)data.getItem();
      try {
	if (parent.getShowNodesForSubWorkspace(entity))
	  loadSubworkspace(entity);
	else 
	  loadItemsOnWorkspace(entity.getSubworkspace());
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    else {
      System.out.println("ObjectDynamicTreeNode: unhandle case in loadChildren");
    }
  }

  private void loadObjectHiearchy() throws G2AccessException {
    //System.out.println("loadObjectHierarchy");

    /*
     * NYI: check moduleScope to determine whether to show entire KB hierarchy, or module specific
     */

    Kb kb = cxn.getKb();
    Module module = kb.getTopLevelModule();
    if (module != null && module.getName() != null) {
      InstanceData newData = parent.getInstanceDataFactory().createInstanceData(module);
      insert(new ObjectDynamicTreeNode(cxn, newData, parent), 0);
      hasLoaded = true;  
    } else {
      Module[] allModules = kb.getModules();
      for (int i=0; i<allModules.length; i++) {
	Module mod = allModules[i];
	//System.out.println("mod: "+mod);
	InstanceData newData = parent.getInstanceDataFactory().createInstanceData(mod);
	//System.out.println("newData.getModule(): "+newData.getModule());
	ObjectDynamicTreeNode newNode =
	  new ObjectDynamicTreeNode(cxn, newData, parent);
	insert(newNode, 0);
      }
      hasLoaded = true;
    }
  }

  private void loadTopLevelWorkspacesForModule(InstanceData data) throws G2AccessException {
    //System.out.println("loadTopLevelWorkspacesForModule: "+data.toString());
    Module module = data.getModule();
    //System.out.println("module: "+module.getName());
    if (module != null) {
      KbWorkspace[] topLevelWorkspaces = module.getTopLevelKbWorkspaces();
      for (int i=0; i<topLevelWorkspaces.length; i++) {
	KbWorkspace wksp = topLevelWorkspaces[i];
	wksp.addItemListener(parent);
	InstanceData newData = parent.getInstanceDataFactory().createInstanceData(wksp);
	ObjectDynamicTreeNode newNode =
	  new ObjectDynamicTreeNode(cxn, newData, parent);
	insert(newNode, 0);
      } 
      hasLoaded = true;
    } 
  }

  private void loadItemsOnWorkspace(KbWorkspace wksp) throws G2AccessException {
    //System.out.println("loadItemsOnWorkspace");
    WorkspaceAdapter wkspAdapter;
    wksp.addWorkspaceListener(wkspAdapter = new WorkspaceAdapter() {
      @Override
      public void workspaceItemAdded (WorkspaceEvent event) {}
      @Override
      public void workspaceItemRemoved (WorkspaceEvent event) {}
      @Override
      public void receivedInitialDownload(WorkspaceEvent event) {}
      @Override
      public void workspaceItemAttributesChanged(WorkspaceEvent evt) {}
    });
    Item[] items = wksp.getItems();
    if (items != null) {
      int cnt = 0;
      Vector classFilter = parent.getClassFilter();
      for (int i=0; i<items.length; i++) {
	Item item = items[i];
	if (!(classFilter.contains(item.getG2ClassName()))) {
	  item.addItemListener(parent);
	  InstanceData newData = parent.getInstanceDataFactory().createInstanceData(item);
	  if (item instanceof Entity) {
	    KbWorkspace subWS = ((Entity)item).getSubworkspace();
	    if (subWS == null)
	      insert(new BasicTreeNode(cxn, newData), cnt++);
	    else {
	      ObjectDynamicTreeNode newNode =
		new ObjectDynamicTreeNode(cxn, newData, parent);
	      insert(newNode, cnt++);	      
	    }
	  } else {
	    insert(new BasicTreeNode(cxn, newData), cnt++);
	  }
	}
      }
      hasLoaded = true;
    }
    wksp.removeWorkspaceListener(wkspAdapter);
  }

  private void loadSubworkspace(Entity entity) throws G2AccessException {
    KbWorkspace subWS = entity.getSubworkspace();
    subWS.addItemListener(parent);
    InstanceData newData = parent.getInstanceDataFactory().createInstanceData(subWS);
    ObjectDynamicTreeNode newNode =
      new ObjectDynamicTreeNode(cxn, newData, parent);
    insert(newNode, 0);
    hasLoaded = true;
  }
}


