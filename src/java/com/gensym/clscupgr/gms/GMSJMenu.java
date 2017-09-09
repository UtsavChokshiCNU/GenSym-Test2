package com.gensym.clscupgr.gms;

import javax.swing.JMenu;

public class GMSJMenu extends JMenu implements GMSItem {

  private int index;
  private Object key;
 
  public GMSJMenu (String label, int index, Object key) {
    super(label);
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
