/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 BrowserScrollPane.java
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

public abstract class BrowserScrollPane extends JScrollPane
implements BrowserSymbols, TreeSelectionListener, TreeModelListener,
  ItemListener, KbModuleListener
{
  private TwAccess cxn;
  private Vector selectionListeners;
  private Vector treeNodeChangedListeners;
 
  private Vector classFilter =  new Vector();
  private Symbol[] defaultClassFilter = new Symbol[] {GFR_PUBLIC_BIN_, NAME_BOX_, DEFAULT_JUNCTION_, TABLE_ITEM_};
  protected BasicDynamicTreeNode rootNode;//private?
  protected BasicTreeModel treeModel;//private?
  private JTree tree;

  private InstanceData selectedUserObject = null;
  private BasicTreeNode selectedTreeNode = null;

  private InstanceData editedUserObject = null;
  private String newStringValue = null;

  private InstanceDataFactory dataFactory;
  private InstancePopupMenuFactory menuFactory;

  public BrowserScrollPane(TwAccess cxn)
  {
    dataFactory = createInstanceDataFactory();
    menuFactory = createInstancePopupMenuFactory();
    setConnection(cxn);    
  }

  private void setupBrowserScrollPane () {
    selectionListeners = new Vector();
    treeNodeChangedListeners = new Vector();
    for (int i=0; i<defaultClassFilter.length; i++)
      classFilter.addElement(defaultClassFilter[i]);
    createScrollPane();
  }

  protected void initTree()
  {
    setupBrowserScrollPane();
  }
  
  public TwAccess getConnection()
  {
    return cxn;
  }
  
  public void setConnection(TwAccess connection) {
    //System.out.println("BrowserScrollPane.setConnection: "+connection);
    if (cxn != null) {
      if (tree != null)
	tree.removeTreeSelectionListener(this);
      if (treeModel != null)
	treeModel.removeTreeModelListener(this);

      try {
	Kb kb = cxn.getKb();
	kb.removeKbModuleListener(this);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }

    if (connection != null && (!connection.equals(cxn))) {
      try {
	Kb kb = connection.getKb();
	kb.addKbModuleListener(this);
      } catch (G2AccessException gae) {
	Trace.exception(gae);
      }
    }
      
    cxn = connection; 
  }

  public void setInstanceDataFactory(InstanceDataFactory factory) {
    dataFactory = factory;
  }  

  public InstanceDataFactory getInstanceDataFactory() {
    return dataFactory;
  }

  public void setInstancePopupMenuFactory(InstancePopupMenuFactory factory) {
    menuFactory = factory;
  }

  public Vector getClassFilter() {
    return classFilter;
  }

  public void setClassFilter(Vector filter) {
    classFilter = filter;
  }

  /**
   * @undocumented
   * @deprecated
   */
  public Symbol[] getDefaultClassFilter() {
    return defaultClassFilter;
  }

  public JTree getTree() {
    return tree;
  }

  public boolean isTreeEditable() {
    return tree.isEditable();
  }

  public void setTreeEditable(boolean isEditable) {
    tree.setEditable(isEditable);
  }

  public InstanceData getUserObjectForSelectedTreeNode() {
    return selectedUserObject;
  }

  public BasicTreeNode getSelectedTreeNode() {
    return selectedTreeNode;
  }

  public synchronized void addTreeSelectionListener(TreeSelectionListener l) {
    if (!(selectionListeners.contains(l)))
      selectionListeners.addElement(l);
  }

  public synchronized void removeTreeSelectionListener(TreeSelectionListener l) {
    if (selectionListeners.contains(l))
      selectionListeners.removeElement(l);
  }

  public synchronized void addTreeNodeChangedListener(TreeNodeChangedListener l) {
    if (!(treeNodeChangedListeners.contains(l)))
      treeNodeChangedListeners.addElement(l);
  }

  public synchronized void removeTreeNodeChangedListener(TreeNodeChangedListener l) {
    if (treeNodeChangedListeners.contains(l))
      treeNodeChangedListeners.removeElement(l);
  }

  private void createScrollPane() {
    buildTree();
    getViewport().add(tree);
  }

  private void buildTree() {
    rootNode = createRootNode();

    treeModel= new BasicTreeModel(rootNode);
    tree = new com.gensym.uitools.utils.JTreePlus(treeModel);
  
    treeModel.addTreeModelListener(this);
    tree.addTreeSelectionListener(this);
    ToolTipManager.sharedInstance().registerComponent(tree);
    tree.setCellRenderer(new BasicTreeCellRenderer());
    tree.setRowHeight(-1); // if less than 0, the cell renderer is queried for each entry
    tree.setEditable(false);
    tree.setRootVisible(false);
    tree.addMouseListener(new MouseEventListener());
  }

  protected abstract InstanceDataFactory createInstanceDataFactory();

  protected abstract InstancePopupMenuFactory createInstancePopupMenuFactory();

  protected abstract BasicDynamicTreeNode createRootNode();

  class MouseEventListener extends MouseAdapter {
    @Override
    public void mouseReleased(MouseEvent e) {
      JTree tree = (JTree)e.getSource();
      int x = e.getX();
      int y = e.getY();
      TreePath path = tree.getPathForLocation(x, y);  
      if ((path != null) && (isPopupTrigger(e))) {
	tree.setSelectionPath(path);
	BasicTreeNode node = (BasicTreeNode)path.getLastPathComponent();
	InstanceData data = (InstanceData)node.getUserObject();
	JPopupMenu menu = ((InstancePopupMenuFactory)menuFactory).createInstancePopupMenu(cxn, data.getDataType(), tree);
	if (menu != null)
	  menu.show(tree, x+1, y+1);
      } 
    }
  }

  private boolean isPopupTrigger(MouseEvent e) {
    return (e.getModifiers() == MouseEvent.BUTTON3_MASK);
  }

  // BEGIN: support for ItemListener
  private static final Symbol NAME_  = Symbol.intern ("NAME");
  private static final Symbol NAMES_ = Symbol.intern("NAMES");
  @Override
  public void receivedInitialValues (ItemEvent e) {}
  @Override
  public void itemDeleted (ItemEvent e) {
    //System.out.println("BrowserScrollPane.itemDeleted: "+e);
    executeItemDeleted(e.getItem());
  }
  @Override
  public void itemModified (ItemEvent e) {
    //System.out.println("BrowserScrollPane.itemModified: "+e);
    Structure attr = (Structure)e.getDenotation().firstElement();
    if (NAMES_.equals(attr.getAttributeValue(NAME_, null))) {
      executeItemNameChanged(e.getItem());
    }
  }

  private void executeItemNameChanged(Item item) {
    //System.out.println("executeItemNameChanged: "+item);
  }

  private void executeItemDeleted(Item item) {
    //System.out.println("executeItemDeleted: "+item);
  }
  // END:: support for ItemListener

  // BEGIN:: support for KbModuleListener
  @Override
  public void receivedInitialModules (KbEvent e) {}
  @Override
  public void moduleCreated (KbEvent e) {
    // add module to tree if moduleScope is ALL_
    Module module = e.getModule();
    //System.out.println("BrowserScrollPane.moduleCreated ("+module.getName()+") NYI");
  }
  @Override
  public void moduleDeleted (KbEvent e) {
    // remove module node from tree
    Module module = e.getModule();
    //System.out.println("BrowserScrollPane.moduleDeleted ("+module.getName()+") NYI");
  }
  @Override
  public void moduleNameChanged (KbEvent e) {
    // find all nodes in tree containing module and setTextRepresentation & nodeChanged
    Module module = e.getModule();
    //System.out.println("BrowserScrollPane.moduleNameChanged ("+module.getName()+") NYI");
  }
  @Override
  public void moduleDependencyChanged (KbEvent e) {
    // if module is in the tree, update it's module dependency
    Module module = e.getModule();
    Sequence dependentModules = (Sequence)e.getData();
    //System.out.println("BrowserScrollPane.moduleDependencyChanged ("+module.getName()+") NYI");
  }
  @Override
  public void kbCleared (KbEvent e) {
    //System.out.println("BrowserScrollPane.executeKbCleared NYI");
  }
  @Override
  public void topLevelWorkspaceAdded(KbEvent e) {
    // if module is in the tree and hasLoaded is true, add workspace node to module node
    Module module = e.getModule();
    KbWorkspace wksp = (KbWorkspace)e.getData();
    //System.out.println("BrowserScrollPane.topLevelWorkspaceAdded for module "+module.getName()+" NYI");
  }
  @Override
  public void topLevelWorkspaceDeleted(KbEvent e) {
    // if module is in the tree and hasLoaded is true, remove workspace node from module node
    Module module = e.getModule();
    KbWorkspace wksp = (KbWorkspace)e.getData();
    //System.out.println("BrowserScrollPane.topLevelWorkspaceDeleted for module "+module.getName()+" NYI");
  }
  // END:: support for KbModuleListener

  // BEGIN: TreeSelectionListener
  @Override
  public void valueChanged(TreeSelectionEvent e) {
    //System.out.println("ClassInstanceScrollPane.valueChanged: "+e);
   
    TreePath path = e.getPath();
    if (path != null) {
      selectedTreeNode = (BasicTreeNode)path.getLastPathComponent();
      selectedUserObject = (InstanceData)selectedTreeNode.getUserObject();
    } else {
      selectedTreeNode = null;
      selectedUserObject = null;
    }

    if (selectionListeners.size() < 1) return;
    Vector l;
    synchronized(this) {l = (Vector)selectionListeners.clone();}
    Enumeration sl = l.elements();
    while (sl.hasMoreElements())
      ((TreeSelectionListener)sl.nextElement()).valueChanged(e);
  }
  // END: TreeSelectionListener

  // BEGIN: TreeModelListener
  @Override
  public void treeNodesChanged(TreeModelEvent e) {
    //System.out.println("treeNodesChanged: "+e);
    Object[] children = e.getChildren();
    newStringValue = children[0].toString().toUpperCase();
    Symbol name_ = Symbol.intern(newStringValue);
    
    TreePath path = e.getTreePath();
    BasicTreeNode node = (BasicTreeNode)path.getLastPathComponent();

    node = (BasicTreeNode)node.getChildAt((e.getChildIndices())[0]);
    editedUserObject = (InstanceData)node.getUserObject();
  
    // notify listeners
    TreeNodeChangedEvent tncEvent = new TreeNodeChangedEvent(this, editedUserObject, newStringValue);
    Vector l;
    synchronized(this) {l = (Vector)treeNodeChangedListeners.clone();}
    Enumeration tncl = l.elements();
    while (tncl.hasMoreElements())
      ((TreeNodeChangedListener)tncl.nextElement()).treeNodeChanged(tncEvent);
  }

  @Override
  public void treeNodesInserted(TreeModelEvent e) {}
  @Override
  public void treeNodesRemoved(TreeModelEvent e) {}
  @Override
  public void treeStructureChanged(TreeModelEvent e) {}
  // END: TreeModelListener
}


