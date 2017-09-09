package com.gensym.uitools.utils;

public interface ComponentVisibilityEventSource {
  public void addComponentVisibilityListener(ComponentVisibilityListener listener);
  public void removeComponentVisibilityListener(ComponentVisibilityListener listener);
}
