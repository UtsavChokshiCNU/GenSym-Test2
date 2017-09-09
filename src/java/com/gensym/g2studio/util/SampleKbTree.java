package com.gensym.g2studio.util;

import com.gensym.classes.Item;
import com.gensym.classes.Module;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.LoginRequest;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwGateway;

import com.sun.java.swing.*;
import com.sun.java.swing.event.*;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import com.sun.java.swing.tree.*;

public class SampleKbTree {
  protected JFrame frame;  
  protected TwAccess connection;
  protected JTree tree;
  protected KbTreeModel treeModel;

  public SampleKbTree(TwAccess connection) {
    this.connection = connection;
    try {
      Module topLevelModule = connection.getKb().getTopLevelModule();

      JMenuBar menuBar = constructMenuBar();
      JPanel panel = new JPanel(true);
      
      frame = new JFrame("SampleKbTree");
      frame.getContentPane().add("Center", panel);
      frame.setJMenuBar(menuBar);
      frame.setBackground(Color.lightGray);
      
      /* Create the JTreeModel. */
      //DefaultMutableTreeNode root = createNewNode(topLevelModule);
      DefaultMutableTreeNode root = createNewNode();
      treeModel = new KbTreeModel(root);
      
      /* Create the tree. */
      tree = new JTree(treeModel);
      tree.setRootVisible(true);
      
      /* Enable tool tips for the tree, without this tool tips will not be picked up. */
      ToolTipManager.sharedInstance().registerComponent(tree);
      
      /* Make the tree use an instance of SampleTreeCellRenderer for drawing. */
      tree.setCellRenderer(new KbTreeCellRenderer());
      
      /* Make tree ask for the height of each row. */
      tree.setRowHeight(-1);
      
      /* Put the Tree in a scroller. */
      JScrollPane        sp = new JScrollPane();
      sp.setPreferredSize(new Dimension(300, 300));
      sp.getViewport().add(tree);
      
      /* And show it. */
      panel.setLayout(new BorderLayout());
      panel.add("Center", sp);
      
      frame.addWindowListener( new WindowAdapter() {
	@Override
	public void windowClosing(WindowEvent e) {System.exit(0);}});
      
      frame.pack();
      frame.show();
    } catch (G2AccessException gae) {
      System.out.println(gae);
    }
  }

  /** Construct a menu. */
  private JMenuBar constructMenuBar() {
    JMenu            menu;
    JMenuBar         menuBar = new JMenuBar();
    JMenuItem        menuItem;

    /* Good ol exit. */
    menu = new JMenu("File");
    menuBar.add(menu);

    menuItem = menu.add(new JMenuItem("Exit"));
    menuItem.addActionListener(new ActionListener() {
      @Override
      public void actionPerformed(ActionEvent e) {
	System.exit(0);
      }});

    /* Tree related stuff. */
    menu = new JMenu("Tree");
    menuBar.add(menu);

    menuItem = menu.add(new JMenuItem("Add"));
    menuItem.addActionListener(new AddAction());
    
    menuItem = menu.add(new JMenuItem("Insert"));
    menuItem.addActionListener(new InsertAction());
    
    menuItem = menu.add(new JMenuItem("Reload"));
    menuItem.addActionListener(new ReloadAction());
    
    menuItem = menu.add(new JMenuItem("Remove"));
    menuItem.addActionListener(new RemoveAction());
    
    return menuBar;
    }
  
  /**
   * Returns the TreeNode instance that is selected in the tree.
   * If nothing is selected, null is returned.
   */
  protected DefaultMutableTreeNode getSelectedNode() {
    TreePath   selPath = tree.getSelectionPath();
    
    if(selPath != null)
      return (DefaultMutableTreeNode)selPath.getLastPathComponent();
    return null;
  }

  protected DefaultMutableTreeNode createNewNode() {
    return new KbDynamicTreeNode(frame, connection, new KbData(KbData.G2_PROJECT));
  }

  protected DefaultMutableTreeNode createNewNode(Module module) {
    return new KbDynamicTreeNode(frame, connection, new KbData(module));
  }
  
  /**
   * AddAction is used to add a new item after the selected item.
   */
  class AddAction extends Object implements ActionListener
  {
    /** Number of nodes that have been added. */
    public int               addCount;
    
    /**
     * Messaged when the user clicks on the Add menu item.
     * Determines the selection from the Tree and adds an item
     * after that.  If nothing is selected, an item is added to
     * the root.
     */
    @Override
    public void actionPerformed(ActionEvent e) {
      int newIndex;
      DefaultMutableTreeNode lastItem = getSelectedNode();
      DefaultMutableTreeNode parent;
      
      /* Determine where to create the new node. */
      if(lastItem != null)
	parent = (DefaultMutableTreeNode)lastItem.getParent();
      else
	parent = (DefaultMutableTreeNode)treeModel.getRoot();
      if(lastItem == null)
	newIndex = treeModel.getChildCount(parent);
      else
	newIndex = parent.getIndex(lastItem) + 1;
      
      /* Let the treemodel know. */
      //treeModel.insertNodeInto(createNewNode("Added " + Integer.toString(addCount++)), parent, newIndex);
    }
  } // End of SampleTree.AddAction
  
  
  /**
   * InsertAction is used to insert a new item before the selected item.
   */
  class InsertAction extends Object implements ActionListener
  {
    /** Number of nodes that have been added. */
    public int               insertCount;
    
    /**
     * Messaged when the user clicks on the Insert menu item.
     * Determines the selection from the Tree and inserts an item
     * after that.  If nothing is selected, an item is added to
     * the root.
     */
    @Override
    public void actionPerformed(ActionEvent e) {
      int               newIndex;
      DefaultMutableTreeNode          lastItem = getSelectedNode();
      DefaultMutableTreeNode          parent;
      
      /* Determine where to create the new node. */
      if(lastItem != null)
	parent = (DefaultMutableTreeNode)lastItem.getParent();
      else
	parent = (DefaultMutableTreeNode)treeModel.getRoot();
      if(lastItem == null)
	newIndex = treeModel.getChildCount(parent);
      else
	newIndex = parent.getIndex(lastItem);
      
      /* Let the treemodel know. */
      //treeModel.insertNodeInto(createNewNode("Inserted " + Integer.toString(insertCount++)), parent, newIndex);
    }
  } // End of SampleTree.InsertAction
  
  
  /**
   * ReloadAction is used to reload from the selected node.  If nothing
   * is selected, reload is not issued.
   */
  class ReloadAction extends Object implements ActionListener
  {
    /**
     * Messaged when the user clicks on the Reload menu item.
     * Determines the selection from the Tree and asks the treemodel
     * to reload from that node.
     */
    @Override
    public void actionPerformed(ActionEvent e) {
      DefaultMutableTreeNode          lastItem = getSelectedNode();
      
      if(lastItem != null)
	treeModel.reload(lastItem);
    }
  } // End of SampleTree.ReloadAction
  
  /**
   * RemoveAction removes the selected node from the tree.  If
   * The root or nothing is selected nothing is removed.
   */
  class RemoveAction extends Object implements ActionListener
  {
    /**
     * Removes the selected item as long as it isn't root.
     */
    @Override
    public void actionPerformed(ActionEvent e) {
      DefaultMutableTreeNode          lastItem = getSelectedNode();
      
      if(lastItem != null && lastItem != (DefaultMutableTreeNode)treeModel.getRoot()) {
	treeModel.removeNodeFromParent(lastItem);
      }
    }
  } // End of SampleTree.RemoveAction
  

  /**
   * ShowHandlesChangeListener implements the ChangeListener interface
   * to toggle the state of showing the handles in the tree.
   */
  class ShowHandlesChangeListener extends Object implements ChangeListener
  {
    public void stateChanged(ChangeEvent e) {
      tree.setShowsRootHandles(((JCheckBox)e.getSource()).isSelected());
    }
    
  } // End of class SampleTree.ShowHandlesChangeListener
  
  
  /**
   * ShowRootChangeListener implements the ChangeListener interface
   * to toggle the state of showing the root node in the tree.
   */
  class ShowRootChangeListener extends Object implements ChangeListener
  {
    public void stateChanged(ChangeEvent e) {
      tree.setRootVisible(((JCheckBox)e.getSource()).isSelected());
    }
    
  } // End of class SampleTree.ShowRootChangeListener
  
  
  /**
   * TreeEditableChangeListener implements the ChangeListener interface
   * to toggle between allowing editing and now allowing editing in
   * the tree.
   */
  class TreeEditableChangeListener extends Object implements ChangeListener
  {
    public void stateChanged(ChangeEvent e) {
      tree.setEditable(((JCheckBox)e.getSource()).isSelected());
    }
    
  } // End of class SampleTree.TreeEditableChangeListener
  
  
  static public void main(String args[]) {
    // Force SampleTree to come up in the Cross Platform L&F
    try {
      UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
    } catch (Exception exc) {
      System.err.println("Error loading L&F: " + exc);
    }

    try {
      TwAccess connection = TwGateway.openConnection("localhost", "1111");
      connection.login(new LoginRequest());
      new SampleKbTree(connection);
    } catch (G2AccessException gae) {
      System.out.println(gae);
    }
  } 
}
