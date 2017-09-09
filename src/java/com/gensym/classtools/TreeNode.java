package com.gensym.classtools;

import java.util.Vector;
import java.util.Enumeration;

abstract class TreeNode {

  Vector children = new Vector(10);
  
  protected TreeNode parent;
  
  public boolean hasChildren() {
    return !children.isEmpty();
  }
  
  /**
   * Deliberately vague in returning an Enumeration
   *  the types of children are not important here.
   */
  public Enumeration getChildren() {
    return children.elements();
  }
  
  public TreeNode getParent() {
    return parent;
  }
  
  protected void addChild(TreeNode o) {
    children.addElement(o);
    o.setParent(this);
  }
  
  protected void setChild(TreeNode o, int index) throws IndexOutOfBoundsException {
    children.setElementAt(o,index);
  }
  
  public void setParent(TreeNode o) {
    parent = o;
  }
}
