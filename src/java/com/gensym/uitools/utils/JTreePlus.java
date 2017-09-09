package com.gensym.uitools.utils;

import java.awt.event.KeyEvent;
import javax.swing.JTree;
import javax.swing.tree.TreePath;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreeModel;
import java.util.Vector;
import java.util.Hashtable;

/**
 * A fancier JTree that has automatic jump to node starting 
 * with the key typed ability. The getStringRepresentation method
 * may need to be overridden, depending upon your TreeCellRenderer.
 * Also has convenience methods for expanding and collapsing all
 * the nodes at once.
 */

public class JTreePlus extends JTree {

  public JTreePlus() {
  }

  public JTreePlus(Hashtable value) {
    super(value);
  }

  public JTreePlus(TreeNode root) {
    super(root);
  }
  
  public JTreePlus(TreeNode root, boolean asksAllowsChildren) {
    super(root, asksAllowsChildren);
  }
  
  public JTreePlus(Vector value) {
    super(value);
  }
  
  public JTreePlus(TreeModel model) {
    super(model);
  }
  
  @Override
  protected void processKeyEvent(KeyEvent e) {
    if (e.getID() == KeyEvent.KEY_TYPED) 
      goToEntryStartingWith(new String(new char[]{e.getKeyChar()}).toLowerCase());
    super.processKeyEvent(e);
  }

  public void expandAll() {
    for (int i=0;i<getRowCount();i++) 
      expandRow(i);
  }

  public void collapseAll() {
    for (int i=getRowCount()-1;i>=0;i--)
      collapseRow(i);
  }

  /**
   * @return a lower cased version of this treeNode's toString
   * Override this to work with your tree cell renderer if necessary.
   * The default toString for a DefaultMutableTreeNode is to call
   * the toString method on the node's userObject.
   */
  protected String getStringRepresentation(TreeNode treeNode) {
    return treeNode.toString().toLowerCase();
  }
  
  public boolean goToEntryStartingWith(String searchString,
				       int rowStart,
				       int rowEnd) {
    for (int i=rowStart+1;i<rowEnd;i++) {
      TreePath path = getPathForRow(i);
      if (isVisible(path)) {
	Object comp = path.getLastPathComponent();
	String str = getStringRepresentation((TreeNode)comp);
	if (str.startsWith(searchString)) {
	  scrollRowToVisible(i);
	  setSelectionRow(i);
	  return true;
	}
      }
    }
    return false;
  }
						     
  public void goToEntryStartingWith(String searchString) {
    int currentLocation=getMaxSelectionRow();    
    if (goToEntryStartingWith(searchString, currentLocation, getRowCount()))
      return;
    if (currentLocation > 0)
      goToEntryStartingWith(searchString,0,currentLocation);
  }

}
