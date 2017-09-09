package com.gensym.editor.icon.core;

public interface LayerListener
{
  public void layerAdded(Layer layer);
  public void layerRemoved(Layer layer);
  public void layerSelected(Layer layer);
  public void layerUnSelected(Layer layer);  
  public void layersResized();
}
