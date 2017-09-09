package com.gensym.clscupgr.gms;

import javax.swing.Icon;
import javax.swing.JCheckBoxMenuItem;

public class GMSJCheckBoxMenuItem extends JCheckBoxMenuItem implements GMSItem {

  private int index;
  private Object key;
  private Icon icon;

  public GMSJCheckBoxMenuItem (int index, Object key) {
    super();
    initialize(index, key);
  }

  public GMSJCheckBoxMenuItem (Icon icon, int index, Object key) {
    super(icon);
    initialize(icon, index, key);
  }
 
  public GMSJCheckBoxMenuItem (String label, int index, Object key) {
    super(label);
    icon = null;
    initialize(index, key);
  }  

  public GMSJCheckBoxMenuItem (String label, Icon icon, int index, Object key) {
    super(label, icon);
    initialize(icon, index, key);
  }

  public GMSJCheckBoxMenuItem (String label, boolean state, int index, Object key) {
    super(label, state);
    initialize(index, key);
  }

  public GMSJCheckBoxMenuItem (String label, Icon icon, boolean state, int index, Object key) {
    super(label, icon, state);
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
