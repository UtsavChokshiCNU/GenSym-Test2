/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 WorkspaceBrowserPanel.java
 *
 */
package com.gensym.demos.multiplecxnsdiapp;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.net.MalformedURLException;

import com.gensym.classes.KbWorkspace;
import com.gensym.dlgruntime.DialogManager;
import com.gensym.dlgruntime.ResourceInstantiationException;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.ntw.TwAccess;
import com.gensym.shell.util.ConnectionManager;
import com.gensym.shell.util.ContextChangedEvent;
import com.gensym.shell.util.ContextChangedListener;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

import javax.swing.JFrame;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.JPopupMenu;
import javax.swing.JScrollPane;
import javax.swing.JTree;
import javax.swing.ToolTipManager;
import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.TreePath;

public class WorkspaceBrowserPanel extends JPanel implements ActionListener {

  private JFrame frame;
  private WorkspaceDynamicTreeNode rootNode;
  private WorkspaceTreeModel treeModel;
  private JTree tree;
  private JScrollPane scrollPane;
 
  private JPopupMenu kbWorkspaceMenu;

  private static final String PROPERTIES_ = "Properties...";
  private static final String SHOW_ = "Show";
  
  private ConnectionManager connectionManager;
  private TwAccess currentConnection;

  private static ContextChangedListener contextChangedListener;

  public WorkspaceBrowserPanel(JFrame frame, ConnectionManager connectionManager) {
    this(connectionManager.getCurrentConnection());
    contextChangedListener = new ContextChangedAdapter();
    connectionManager.addContextChangedListener(contextChangedListener);
    this.frame = frame;
    this.connectionManager = connectionManager;
  }

  public WorkspaceBrowserPanel(JFrame frame, TwAccess connection) {
    this(connection);
    this.frame = frame;
  }

  private WorkspaceBrowserPanel(TwAccess connection) {
    super(new BorderLayout());
    add(scrollPane = new JScrollPane(), BorderLayout.CENTER);
    setCurrentConnection(connection);
  }

  private void buildWorkspaceTree(TwAccess connection) {
    rootNode = createNewNode();
    treeModel = new WorkspaceTreeModel(rootNode);
    tree = new JTree(treeModel);

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

    createKbWorkspacePopupMenu();

    /* Enable tool tips for the tree, without this tool tips will not be picked up. */
    ToolTipManager.sharedInstance().registerComponent(tree);

    /* Make the tree use an instance of SampleTreeCellRenderer for drawing. */
    tree.setCellRenderer(new WorkspaceTreeCellRenderer());

    /* Make tree ask for the height of each row. */
    tree.setRowHeight(-1);
  }

  private boolean isPopupTrigger(MouseEvent e) {
    return (e.getModifiers() == MouseEvent.BUTTON3_MASK);
  }

  public void setCurrentConnection(TwAccess connection) {
    if (currentConnection != null && tree != null) {
      // get rid of current tree before building new one
      scrollPane.getViewport().remove(tree);
    }

    currentConnection = connection;

    buildWorkspaceTree(currentConnection);
    scrollPane.getViewport().add(tree);
    if (currentConnection == null)
      rootNode.setAllowsChildren(false);
    else 
      rootNode.setAllowsChildren(true);

    // make sure that the scrollPane is up-to-date and visible, nothing works so far
    update(getGraphics());
    invalidate(); 
    
    //paint(getGraphics());
    //scrollPane.getViewport().repaint();
   
  }

  private WorkspaceDynamicTreeNode createNewNode() {
    String cxnName = "";
    if (currentConnection != null)
      cxnName = currentConnection.toShortString();
    return new WorkspaceDynamicTreeNode(frame, currentConnection, 
					new WorkspaceData(WorkspaceData.KB_WORKSPACES, cxnName));
  }

  private void showPopupMenuForDataType(DefaultMutableTreeNode node, int x, int y) {
    WorkspaceData data = (WorkspaceData)node.getUserObject();
    int dataType = data.getDataType();
    
    if (dataType == WorkspaceData.G2_KB_WORKSPACE)
      kbWorkspaceMenu.show(tree, x, y);
  }

  private void createKbWorkspacePopupMenu() {
    kbWorkspaceMenu = new JPopupMenu();
    JMenuItem menuItem;
    menuItem = new JMenuItem(SHOW_);
    kbWorkspaceMenu.add(menuItem);
    menuItem.addActionListener(this);
    menuItem = new JMenuItem(PROPERTIES_);
    kbWorkspaceMenu.add(menuItem);
    menuItem.addActionListener(this);
    kbWorkspaceMenu.setInvoker(tree);
  }

  class ContextChangedAdapter implements ContextChangedListener{
    @Override
    public void currentConnectionChanged(ContextChangedEvent e){
      TwAccess newCurrentConnection = e.getConnection();
      setCurrentConnection(newCurrentConnection);
    } 
  }

  @Override
  public void actionPerformed(ActionEvent e) {
    String actionCommand = e.getActionCommand();
    JMenuItem menuItem = (JMenuItem)e.getSource();
    JPopupMenu menu = (JPopupMenu)menuItem.getParent();
    JTree invoker = (JTree)menu.getInvoker();
    TreePath path = invoker.getLeadSelectionPath();
    DefaultMutableTreeNode node = (DefaultMutableTreeNode)path.getLastPathComponent();

    try {
      if (menu == kbWorkspaceMenu) {
	handleKbWorkspacePopupMenu(node, actionCommand);
      }
    } catch (G2AccessException gae) {
      System.out.println(gae);
      Trace.exception(gae);
    }
  }

  private void handleKbWorkspacePopupMenu(DefaultMutableTreeNode node, String actionCommand) throws G2AccessException {
    WorkspaceData data = (WorkspaceData)node.getUserObject();
    if (data.getDataType() == WorkspaceData.G2_KB_WORKSPACE) {
      Structure particulars = new Structure();
      KbWorkspace wksp = data.getKbWorkspace();
      if (actionCommand.equals(SHOW_)) {
	  wksp.show(particulars);
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

}
