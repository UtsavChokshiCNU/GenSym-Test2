package com.gensym.tracebeans;

import java.util.Vector;
import com.gensym.beansruntime.VectorEditor;
 
public class TraceElementVectorEditor extends VectorEditor {
  
  public TraceElementVectorEditor() {
    super(false,TraceElement.class);
  }
  
  @Override
  protected Object getNewElement() {
    return new TraceElement("com.gensym.util","java.lang.Object",1);
  }
  
  @Override
  protected Vector getNewVector() {
    return new TraceElementVector();
  }
  
  @Override
  protected boolean treatElementAsProperty(Object element) {
    return false;
  }
}

