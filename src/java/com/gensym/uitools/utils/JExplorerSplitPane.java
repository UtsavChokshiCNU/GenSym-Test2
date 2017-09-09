package com.gensym.uitools.utils;

import java.util.Enumeration;
import java.awt.Color;
import java.awt.Font;
import java.awt.Insets;
import java.awt.Component;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.event.TreeSelectionListener;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.tree.TreePath;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.JTableHeader;
import javax.swing.JTable;
import javax.swing.JLabel;
import javax.swing.JSplitPane;
import javax.swing.JTree;
import javax.swing.JScrollPane;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;
import javax.swing.border.CompoundBorder;
import javax.swing.border.EtchedBorder;
import java.awt.Dimension;
import java.awt.BorderLayout;
import java.awt.Component;
import javax.swing.JComponent;
import javax.swing.table.TableModel;
import javax.swing.tree.TreeNode;

public class JExplorerSplitPane extends JSplitPane {
  private int viewType = JExplorer.VIEW_DETAILS;
  private static final int DEFAULT_TREE_WIDTH = 250;
  private static final String ALL_ITEMS = "All Items";
  private JExplorerTableModel tableModel;
  protected JTable table;
  protected JTree tree;

  public JExplorerSplitPane(JTree tree,
			    JExplorerTableModel tableModel,
			    JTableIconFactory tableIconFactory)
  {
    this(tree,tableModel, new ExplorerJTable(), tableIconFactory);
    this.tableModel = tableModel;
    this.tree = tree;
  }

  public void refresh(Object[] currentArguments) {
    //make this abstract???
  }

  public void setViewType(int type) {
    if (viewType == type) return;
    viewType = type;
    switch (type) {
    case JExplorer.VIEW_DETAILS:
      break;
    case JExplorer.VIEW_LIST:
      break;
    }
  }

  private JExplorerSplitPane(JTree tree,
			     TableModel tableModel,
			     JTable table,
			     JTableIconFactory tableIconFactory)   
  {
    super(HORIZONTAL_SPLIT,
	  createLeftPane(tree),
	  new WhiteBackgroundJScrollPane(table));
    //setOneTouchExpandable(true);
    setDividerSize(1);
    setDividerLocation(DEFAULT_TREE_WIDTH);
    setBorder(new CompoundBorder(new EtchedBorder(),
				 new LineBorder(Color.lightGray, 3)));
    table.setModel(tableModel);
    this.table = table;
    table.setDefaultRenderer(Object.class,
			     new JExplorerTableCellRenderer(tableIconFactory));
    tree.addTreeSelectionListener(new DefaultTreeSelectionListener());
  }

  private static Component createLeftPane(JTree tree)
  {
    JPanel panel = new JPanel();
    panel.setLayout(new BorderLayout());
    JLabel header = new JLabel(ALL_ITEMS);
    header.setFont(FontUtil.sanserifPlain11);
    header.setBackground(Color.lightGray);

    JComponent headerPanel = header;
    headerPanel.setBorder(new CompoundBorder(new EtchedBorder(),
					     new EmptyBorder(new Insets(3,10,3,3))));    
    panel.add(headerPanel, "North");    
    JScrollPane scrollpane = new JScrollPane(tree);
    panel.add(scrollpane, "Center");
    return panel;
  }

  private void doSelectionChanged(TreeSelectionEvent e) {
    TreePath path = e.getPath();
    TreeNode node = null;
    if (path != null && e.isAddedPath(path)) 
      node = (TreeNode)path.getLastPathComponent();
    tableModel.removeAll();
    if (node != null) {
      addChildrenForNode(node);
    }
    tableModel.update();
  }

  protected void addChildrenForNode(TreeNode node) {
    Enumeration e = node.children();
    while (e.hasMoreElements()) 
      tableModel.addRow((TreeNode)e.nextElement());
  }
  
  class DefaultTreeSelectionListener implements TreeSelectionListener {

    @Override
    public void valueChanged(TreeSelectionEvent e) {
      doSelectionChanged(e);
    }
  }
}

class ExplorerJTable extends JTable {
  ExplorerJTable() {
    super();
    setShowGrid(false);
    setShowHorizontalLines(false);
    setShowVerticalLines(false);
    setIntercellSpacing(new java.awt.Dimension(7,0));
    setRowHeight(19);
    sizeColumnsToFit(AUTO_RESIZE_OFF);
    setAutoResizeMode(AUTO_RESIZE_OFF);
    setBackground(Color.white);
    JTableHeader header = getTableHeader();
    header.setUpdateTableInRealTime(false);
    header.setFont(FontUtil.sanserifPlain11);
    header.setAlignmentY(0);
    header.setAlignmentX(0);
    setFont(FontUtil.sanserifPlain11);
  }
}
