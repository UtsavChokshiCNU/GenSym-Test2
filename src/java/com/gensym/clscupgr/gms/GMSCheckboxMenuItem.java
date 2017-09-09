package com.gensym.clscupgr.gms;

import java.awt.CheckboxMenuItem;

public class GMSCheckboxMenuItem extends CheckboxMenuItem implements GMSItem {

  private int index;
  private Object key;

  public GMSCheckboxMenuItem (int index, Object key) {
    super();
    initialize(index, key);
  }
 
  public GMSCheckboxMenuItem (String label, int index, Object key) {
    super(label);
    initialize(index, key);
  }  

  public GMSCheckboxMenuItem (String label, boolean state, int index, Object key) {
    super(label, state);
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
