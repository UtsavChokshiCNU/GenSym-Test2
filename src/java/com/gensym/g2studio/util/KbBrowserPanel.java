/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 KbBrowserPanel.java
 *
 */
package com.gensym.g2studio.util;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.net.MalformedURLException;

import com.gensym.classes.ClassDefinition;
import com.gensym.classes.Item;
import com.gensym.classes.KbWorkspace;
import com.gensym.classes.Module;
import com.gensym.classes.ModuleInformation;
import com.gensym.classes.SystemTable;
import com.gensym.dlg.StandardDialog;
import com.gensym.dlg.StandardDialogClient;
import com.gensym.dlgruntime.DialogManager;
import com.gensym.dlgruntime.ResourceInstantiationException;
import com.gensym.g2studio.dialogs.ClassEditorDialog;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

import com.sun.java.swing.JFrame;
import com.sun.java.swing.JMenuItem;
import com.sun.java.swing.JPanel;
import com.sun.java.swing.JPopupMenu;
import com.sun.java.swing.JScrollPane;
import com.sun.java.swing.JTree;
import com.sun.java.swing.ToolTipManager;
import com.sun.java.swing.tree.DefaultMutableTreeNode;
import com.sun.java.swing.tree.TreePath;

public class KbBrowserPanel extends JPanel implements ActionListener {

  private JFrame frame;
  private KbDynamicTreeNode rootNode;
  private KbTreeModel treeModel;
  private JTree tree;
  private JScrollPane scrollPane;

  private JPopupMenu projectMenu;

  private JPopupMenu projectModuleMenu;
  private JPopupMenu moduleMenu;
 
  private JPopupMenu projectWkspMenu;
  private JPopupMenu kbWorkspaceMenu;

  private JPopupMenu projectClassMenu;
  private JPopupMenu classDefinitionMenu;

  private JPopupMenu systemTableMenu;

  private static final String CLONE_ = "Clone...";
  private static final String CREATE_ = "Create";
  private static final String DELETE_ = "Delete";
  private static final String EDIT_ = "Edit...";
  private static final String GO_TO_ = "Go To";
  private static final String NEW_ = "New...";
  private static final String PROPERTIES_ = "Properties...";
  private static final String RENAME_ = "Rename...";
  private static final String SHOW_ = "Show";
  private static final String SHOW_SUBWORKSPACE_ = "Show Subworkspace";
  private static final String SUBCLASS_ = "Subclass...";

  private static final Symbol ITEM_ = Symbol.intern ("ITEM");
  private static final Symbol GO_TO_ITEM_ = Symbol.intern ("GO-TO-ITEM");
  private static final Symbol CLASS_DEFINITION_ = Symbol.intern("CLASS-DEFINITION");
  
  private ConnectionManager connectionManager;
  private TwAccess currentConnection;

  private static ContextChangedListener contextChangedListener;

  public KbBrowserPanel(JFrame frame, ConnectionManager connectionManager) {
    this(connectionManager.getCurrentConnection());
    contextChangedListener = new ContextChangedAdapter();
    connectionManager.addContextChangedListener(contextChangedListener);
    this.frame = frame;
    this.connectionManager = connectionManager;
  }

  public KbBrowserPanel(JFrame frame, TwAccess connection) {
    this(connection);
    this.frame = frame;
  }

  private KbBrowserPanel(TwAccess connection) {
    setLayout(new BorderLayout()); 
    add(scrollPane = new JScrollPane(), BorderLayout.CENTER);
    setCurrentConnection(connection);
  }

  private void buildKbTree(TwAccess connection) {
    //System.out.println("buildKbTree, connection: "+connection);

    rootNode = createNewNode();
    treeModel = new KbTreeModel(rootNode);
    tree = new JTree(treeModel);
    //tree.setRootVisible(false);

    tree.addMouseListener(new MouseAdapter() {
      @Override
      public void mousePressed (MouseEvent e) {
	TreePath path = tree.getPathForLocation(e.getX(), e.getY());  
	if ((path != null) && (isPopupTrigger(e))) {
	  DefaultMutableTreeNode node = (DefaultMutableTreeNode)path.getLastPathComponent();
	  showPopupMenuForDataType(node, e.getX(), e.getY());
	}
      }
    });

    createPopupMenus(tree);

    /* Enable tool tips for the tree, without this tool tips will not be picked up. */
    ToolTipManager.sharedInstance().registerComponent(tree);

    /* Make the tree use an instance of SampleTreeCellRenderer for drawing. */
    tree.setCellRenderer(new KbTreeCellRenderer());

    /* Make tree ask for the height of each row. */
    tree.setRowHeight(-1);
  }

  private boolean isPopupTrigger(MouseEvent e) {
    return (e.getModifiers() == MouseEvent.BUTTON3_MASK);
  }

  public void setCurrentConnection(TwAccess connection) {
    //System.out.println("KbBrowserPanel.setCurrentConnection: "+connection);
    if (currentConnection != null && tree != null) {
      // get rid of current tree before building new one
      scrollPane.getViewport().remove(tree);
    }

    currentConnection = connection;

    buildKbTree(currentConnection);
    scrollPane.getViewport().add(tree);
    if (currentConnection == null)
      rootNode.setAllowsChildren(false);
    else 
      rootNode.setAllowsChildren(true);
    scrollPane.getViewport().repaint();
  }

  private KbDynamicTreeNode createNewNode() {
    return new KbDynamicTreeNode(frame, currentConnection, new KbData(KbData.G2_PROJECT));
  }

  private void showPopupMenuForDataType(DefaultMutableTreeNode node, int x, int y) {
    KbData data = (KbData)node.getUserObject();
    int dataType = data.getDataType();
    
    if (dataType == KbData.G2_PROJECT)
      projectMenu.show(tree, x, y);
    else if (dataType == KbData.MODULE_MODULES)
      projectModuleMenu.show(tree, x, y);
    else if (dataType == KbData.G2_MODULE)
      moduleMenu.show(tree, x, y);
    else if (dataType == KbData.MODULE_WORKSPACES)
      projectWkspMenu.show(tree, x, y);
    else if (dataType == KbData.G2_KB_WORKSPACE)
      kbWorkspaceMenu.show(tree, x, y);
    else if (dataType == KbData.MODULE_CLASSES)
      projectClassMenu.show(tree, x, y);
    else if (dataType == KbData.G2_CLASS_DEFINITION)
      classDefinitionMenu.show(tree, x, y);
    else if (dataType == KbData.G2_SYSTEM_TABLE)
      systemTableMenu.show(tree, x, y);
  }

  private void createPopupMenus(JTree tree) {
    createProjectPopupMenu();
    createProjectModulePopupMenu();
    createModulePopupMenu();
    createProjectWorkspacePopupMenu();
    createKbWorkspacePopupMenu();
    createProjectClassPopupMenu();
    createClassDefinitionPopupMenu();
    createSystemTablePopupMenu();
  }

  private void createProjectPopupMenu() {
    projectMenu = new JPopupMenu();
    JMenuItem menuItem;
    menuItem = new JMenuItem(NEW_);
    projectMenu.add(menuItem);
    menuItem.addActionListener(this);
    projectMenu.addSeparator();
    menuItem = new JMenuItem(DELETE_);
    projectMenu.add(menuItem);
    menuItem.addActionListener(this);
    projectMenu.setInvoker(tree);
  }

  private void createProjectModulePopupMenu() {
    projectModuleMenu = new JPopupMenu();
    JMenuItem menuItem;
    menuItem = new JMenuItem(NEW_);
    projectModuleMenu.add(menuItem);
    menuItem.addActionListener(this);
    projectModuleMenu.setInvoker(tree);
  }

  private void createModulePopupMenu() {
    moduleMenu = new JPopupMenu();
    JMenuItem menuItem;
    menuItem = new JMenuItem(RENAME_);
    moduleMenu.add(menuItem);
    menuItem.addActionListener(this);
    moduleMenu.addSeparator();
    menuItem = new JMenuItem(DELETE_);
    moduleMenu.add(menuItem);
    menuItem.addActionListener(this);
    moduleMenu.addSeparator();
    menuItem = new JMenuItem(PROPERTIES_);
    moduleMenu.add(menuItem);
    menuItem.addActionListener(this);
    moduleMenu.setInvoker(tree);
  }

  private void createProjectWorkspacePopupMenu() {
    projectWkspMenu = new JPopupMenu();
    JMenuItem menuItem;
    menuItem = new JMenuItem(NEW_);
    projectWkspMenu.add(menuItem);
    menuItem.addActionListener(this);
    projectWkspMenu.setInvoker(tree);
  }

  private void createKbWorkspacePopupMenu() {
    kbWorkspaceMenu = new JPopupMenu();
    JMenuItem menuItem;
    menuItem = new JMenuItem(SHOW_);
    kbWorkspaceMenu.add(menuItem);
    menuItem.addActionListener(this);
    menuItem = new JMenuItem(CLONE_);
    kbWorkspaceMenu.add(menuItem);
    menuItem.addActionListener(this);
    menuItem = new JMenuItem(DELETE_);
    kbWorkspaceMenu.add(menuItem);
    menuItem.addActionListener(this);
    kbWorkspaceMenu.addSeparator();
    menuItem = new JMenuItem(PROPERTIES_);
    kbWorkspaceMenu.add(menuItem);
    menuItem.addActionListener(this);
    kbWorkspaceMenu.setInvoker(tree);
  }

  private void createProjectClassPopupMenu() {
    projectClassMenu = new JPopupMenu();
    JMenuItem menuItem;
    menuItem = new JMenuItem(NEW_);
    projectClassMenu.add(menuItem);
    menuItem.addActionListener(this);
    projectClassMenu.setInvoker(tree);
  }

  private void createClassDefinitionPopupMenu() {
    classDefinitionMenu = new JPopupMenu();
    JMenuItem menuItem;
    menuItem = new JMenuItem(GO_TO_);
    classDefinitionMenu.add(menuItem);
    menuItem.addActionListener(this);
    classDefinitionMenu.addSeparator();
    menuItem = new JMenuItem(CREATE_);
    classDefinitionMenu.add(menuItem);
    menuItem.addActionListener(this);
    menuItem = new JMenuItem(EDIT_);
    classDefinitionMenu.add(menuItem);
    menuItem.addActionListener(this);
    classDefinitionMenu.addSeparator();
    menuItem = new JMenuItem(SUBCLASS_);
    classDefinitionMenu.add(menuItem);
    menuItem.addActionListener(this);
    classDefinitionMenu.addSeparator();
    menuItem = new JMenuItem(DELETE_);
    classDefinitionMenu.add(menuItem);
    menuItem.addActionListener(this);
    classDefinitionMenu.addSeparator();
    menuItem = new JMenuItem(PROPERTIES_);
    classDefinitionMenu.add(menuItem);
    menuItem.addActionListener(this);
    classDefinitionMenu.setInvoker(tree);
  }

  private void createSystemTablePopupMenu() {
    systemTableMenu = new JPopupMenu();
    JMenuItem menuItem;
    menuItem = new JMenuItem(SHOW_);
    systemTableMenu.add(menuItem);
    menuItem.addActionListener(this);
    systemTableMenu.setInvoker(tree);
  }

  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      //System.out.println("currentConnectionChanged: connection=> "+e.getConnection());
      TwAccess newCurrentConnection = e.getConnection();
      setCurrentConnection(newCurrentConnection);
    } 
  }

  @Override
  public void actionPerformed(ActionEvent e) {
    //System.out.println("actionPerformed: "+e+"  source: "+e.getSource());
    String actionCommand = e.getActionCommand();
    JMenuItem menuItem = (JMenuItem)e.getSource();
    JPopupMenu menu = (JPopupMenu)menuItem.getParent();
    JTree invoker = (JTree)menu.getInvoker();
    TreePath path = invoker.getLeadSelectionPath();
    DefaultMutableTreeNode node = (DefaultMutableTreeNode)path.getLastPathComponent();

    try {
      if (menu == projectMenu) {
	handleProjectPopupMenu(node, actionCommand);
      } else if (menu == projectModuleMenu){
	handleProjectModulePopupMenu(node, actionCommand);
      } else if (menu == moduleMenu) {
	handleModulePopupMenu(node, actionCommand);
      } else if (menu == projectWkspMenu) {
	handleProjectWorkspacePopupMenu(node, actionCommand);
      } else if (menu == kbWorkspaceMenu) {
	handleKbWorkspacePopupMenu(node, actionCommand);
      } else if (menu == projectClassMenu) {
	handleProjectClassPopupMenu(node, actionCommand);
      } else if (menu == classDefinitionMenu) {
	handleClassDefinitionPopupMenu(node, actionCommand);
      } else if (menu == systemTableMenu) {
	handleSystemTablePopupMenu(node, actionCommand);
      }
    } catch (G2AccessException gae) {
      System.out.println(gae);
      Trace.exception(gae);
    }
  }

  private void handleProjectPopupMenu(DefaultMutableTreeNode node, String actionCommand) throws G2AccessException {
    if (actionCommand.equals(NEW_)) {
      System.out.println("NYI: New Project");
    } else if (actionCommand.equals(DELETE_)) {
      System.out.println("NYI: Delete Project");
    } else System.out.println("handleProjectPopupMenu: "+actionCommand);
  }

  private void handleProjectModulePopupMenu(DefaultMutableTreeNode node, String actionCommand) throws G2AccessException {
    if (actionCommand.equals(NEW_)) {
      System.out.println("NYI: New Module");
    } else System.out.println("handleProjectModulePopupMenu: "+actionCommand);
  }

  private void handleModulePopupMenu(DefaultMutableTreeNode node, String actionCommand) throws G2AccessException {
    KbData data = (KbData)node.getUserObject();
    if (data.getDataType() == KbData.G2_MODULE) {
      Module module = data.getModule();

      if (actionCommand.equals(RENAME_)) {
	System.out.println("NYI: Rename Module");
      } else if (actionCommand.equals(DELETE_)) {
	System.out.println("NYI: Delete Module");
      } else if (actionCommand.equals(PROPERTIES_)) {
	ModuleInformation modInfo = module.getModuleInformation();
	DialogManager dlgManager = currentConnection.getDialogManager();
	Symbol userMode = currentConnection.getUserMode();
	try {
	  dlgManager.editItem (modInfo, userMode, java.util.Locale.getDefault());
	} 
	catch (MalformedURLException mue) {
	  Trace.exception(mue);
	}
	catch (ResourceInstantiationException rie) {
	  Trace.exception(rie);
	}
      } else System.out.println("handleModulePopupMenu: "+actionCommand);
    }
  }

  private void handleProjectWorkspacePopupMenu(DefaultMutableTreeNode node, String actionCommand) throws G2AccessException {
    if (actionCommand.equals(NEW_)) {
      System.out.println("NYI: New Workspace");
    } else System.out.println("handleProjectWorkspacePopupMenu: "+actionCommand);
  }

  private void handleKbWorkspacePopupMenu(DefaultMutableTreeNode node, String actionCommand) throws G2AccessException {
    KbData data = (KbData)node.getUserObject();
    if (data.getDataType() == KbData.G2_KB_WORKSPACE) {
      Structure particulars = new Structure();
      KbWorkspace wksp = data.getKbWorkspace();
      if (actionCommand.equals(SHOW_)) {
	  wksp.show(particulars);
      } else if (actionCommand.equals(CLONE_)) {
	System.out.println("NYI: Clone Workspace");
      } else if (actionCommand.equals(DELETE_)) {
	System.out.println("NYI: Delete Workspace");
      } else if (actionCommand.equals(PROPERTIES_)) {
	DialogManager dlgManager = currentConnection.getDialogManager();
	Symbol userMode = currentConnection.getUserMode();
	try {
	  dlgManager.editItem (wksp, userMode, java.util.Locale.getDefault());
	} 
	catch (MalformedURLException mue) {
	  Trace.exception(mue);
	}
	catch (ResourceInstantiationException rie) {
	  Trace.exception(rie);
	}
      } else System.out.println("handleKbWorkspacePopupMenu: "+actionCommand);
    }
  }

  private void handleProjectClassPopupMenu(DefaultMutableTreeNode node, String actionCommand) throws G2AccessException {
    if (actionCommand.equals(NEW_)) {
      ClassEditorDialog dlg = new ClassEditorDialog(frame, "New ClassDefinition", true,
						    connectionManager, new DialogClient());
      
      dlg.setVisible(true);
    } else System.out.println("handleProjectClassPopupMenu: "+actionCommand);
  }

  private void handleClassDefinitionPopupMenu(DefaultMutableTreeNode node, String actionCommand) throws G2AccessException {
    KbData data = (KbData)node.getUserObject();

    if (data.getDataType() == KbData.G2_CLASS_DEFINITION) {
      ClassDefinition classDef = data.getClassDefinition();
      Sequence parents = classDef.getContainmentHierarchy();
      KbWorkspace wksp = (KbWorkspace)parents.elementAt(0);

      if (actionCommand.equals(GO_TO_)) {
	Structure particulars = new Structure();
	particulars.setAttributeValue(ITEM_, classDef);
	particulars.setAttributeValue(GO_TO_ITEM_, new Boolean(true));
	wksp.show(particulars);
      } else if (actionCommand.equals(CREATE_)) {
	System.out.println("NYI: Create Instance");
      } else if (actionCommand.equals(EDIT_)) {
	ClassEditorDialog dlg = new ClassEditorDialog(frame, "Edit "+classDef.getClassName(), true,
						      connectionManager, new DialogClient());
	dlg.setClassDefinition(classDef);
	dlg.setVisible(true);
      } else if (actionCommand.equals(SUBCLASS_)) {
	ClassDefinition newClassDef = (ClassDefinition)currentConnection.createItem(CLASS_DEFINITION_);
	Sequence superiorClasses = new Sequence();
	superiorClasses.addElement(classDef.getClassName());
	newClassDef.setDirectSuperiorClasses(superiorClasses);
	ClassEditorDialog dlg = new ClassEditorDialog(frame, "New ClassDefinition", true,
						      connectionManager, new DialogClient());
	dlg.setClassDefinition(newClassDef);
	dlg.setVisible(true);
      } else if (actionCommand.equals(DELETE_)) {
	System.out.println("NYI: Delete ClassDefinition");
      } else if (actionCommand.equals(PROPERTIES_)) {
	DialogManager dlgManager = currentConnection.getDialogManager();
	Symbol userMode = currentConnection.getUserMode();
	try {
	  dlgManager.editItem (classDef, userMode, java.util.Locale.getDefault());
	} 
	catch (MalformedURLException mue) {
	  Trace.exception(mue);
	}
	catch (ResourceInstantiationException rie) {
	  Trace.exception(rie);
	}
      } else System.out.println("handleClassDefinitionPopupMenu: "+actionCommand);
    }
  }

  private void handleSystemTablePopupMenu(DefaultMutableTreeNode node, String actionCommand) throws G2AccessException {
    KbData data = (KbData)node.getUserObject();
    if (data.getDataType() == KbData.G2_SYSTEM_TABLE) {
      SystemTable systemTable = data.getSystemTable();
      if (actionCommand.equals(SHOW_)) {
	DialogManager dlgManager = currentConnection.getDialogManager();
	Symbol userMode = currentConnection.getUserMode();
	try {
	  dlgManager.editItem (systemTable, userMode, java.util.Locale.getDefault());
	} 
	catch (MalformedURLException mue) {
	  Trace.exception(mue);
	}
	catch (ResourceInstantiationException rie) {
	  Trace.exception(rie);
	}
      }
    }
  }
}

class DialogClient implements StandardDialogClient {
    @Override
    public void dialogDismissed (StandardDialog dlg, int code) {
      if (dlg.wasCancelled()) return;
      if (dlg instanceof ClassEditorDialog)
	System.out.println("ClassEditorDialog was dismissed, not cancelled");
    }
}
