package com.gensym.clscupgr.gms;

import java.awt.MenuBar;

public class GMSMenuBar extends MenuBar implements GMSItem {

  private int index;
  private Object key;
 
  public GMSMenuBar (int index, Object key) {
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
