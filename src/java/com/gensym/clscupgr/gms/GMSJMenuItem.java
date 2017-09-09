package com.gensym.clscupgr.gms;

import javax.swing.Icon;
import javax.swing.JMenuItem;

public class GMSJMenuItem extends JMenuItem implements GMSItem {

  private int index;
  private Object key;
  private Icon icon;

  public GMSJMenuItem (Icon icon, int index, Object key) {
    super(icon);
    initialize(icon, index, key);
  }
 
  public GMSJMenuItem (String label, int index, Object key) {
    super(label);
    icon = null;
    initialize(index, key);
  }  

  public GMSJMenuItem (String label, Icon icon, int index, Object key) {
    super(label, icon);
    initialize(icon, index, key);
  }

  private void initialize(int index, Object key) {
    this.index = index;
    this.key = key;
  }

  private void initialize(Icon icon, int index, Object key) {
    this.icon = icon;
    initialize(index, key);
  }

  @Override
  public int getIndex() {
    return index;
  }

  @Override
  public Object getKey() {
    return key;
  }

  @Override
  public Icon getIcon() {
    return icon;
  }

  // tie in enable/disable/state methods to GMS API
}
