package com.gensym.clscupgr.gms;

import javax.accessibility.Accessible;
import javax.accessibility.AccessibleContext;

import javax.swing.JComponent;
import javax.swing.JMenuBar;

public class GMSJMenuBar extends JMenuBar implements GMSItem {

  private int index;
  private Object key;
 
  public GMSJMenuBar (int index, Object key) {
    super();
    initialize(index, key);
  }  

  private void initialize(int index, Object key) {
    this.index = index;
    this.key = key;
  }

  @Override
  public int getIndex() {
    return index;
  }

  @Override
  public Object getKey() {
    return key;
  }
}
