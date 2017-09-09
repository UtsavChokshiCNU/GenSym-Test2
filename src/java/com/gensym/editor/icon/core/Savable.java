package com.gensym.editor.icon.core;

public interface Savable {
  public boolean save(Object object);
  public Savable getLastLocation();
  public String getLastLocationTitle();
  public void addObjectChangedListener(ObjectChangedListener objectChangedListener);
  public void removeObjectChangedListener(ObjectChangedListener objectChangedListener);
  public IconFormat getIconFormat();
}
