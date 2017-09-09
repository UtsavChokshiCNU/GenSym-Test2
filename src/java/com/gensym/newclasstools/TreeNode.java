package com.gensym.newclasstools;

import java.util.Vector;
import java.util.Enumeration;

abstract class TreeNode {

  Vector children = new Vector(10);
  
  public boolean hasChildren() {
    return children.size() > 0;
  }
  
  /**
   * Deliberately vague in returning an Enumeration
   *  the types of children are not important here.
   */
  public Enumeration getChildren() {
    return children.elements();
  }
  
  protected void addChild(TreeNode o) {
    children.addElement(o);
  }
  
  protected void setChild(TreeNode o, int index) throws IndexOutOfBoundsException {
    children.setElementAt(o,index);
  }
  
}
