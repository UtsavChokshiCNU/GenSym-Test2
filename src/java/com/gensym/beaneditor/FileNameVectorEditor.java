package com.gensym.beaneditor;

import java.util.Vector;
import com.gensym.beansruntime.VectorEditor;

public class FileNameVectorEditor extends VectorEditor
{
  
  public FileNameVectorEditor() {
    super(true, FileName.class);
  }
  
  @Override
  protected Object getNewElement() {
    return "";
  }
  
  @Override
  protected Vector getNewVector() {
    return new FileNameVector();
  }
  
  @Override
  public boolean treatElementAsProperty(Object obj) {
    return true;
  }
}
