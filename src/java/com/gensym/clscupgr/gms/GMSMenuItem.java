package com.gensym.clscupgr.gms;

import java.awt.MenuItem;

public class GMSMenuItem extends MenuItem implements GMSItem {

  private int index;
  private Object key;

  public GMSMenuItem (int index, Object key) {
    super();
    initialize(index, key);
  }
 
  public GMSMenuItem (String label, int index, Object key) {
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

  // tie in methods to GMS API
}
