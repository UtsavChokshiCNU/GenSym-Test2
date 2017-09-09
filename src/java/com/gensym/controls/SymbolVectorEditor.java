package com.gensym.controls;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;

import java.util.Vector;

import com.gensym.util.Symbol;
import com.gensym.beansruntime.VectorEditor;

public class SymbolVectorEditor extends  VectorEditor
{
  private static final Symbol DEFAULT_ = Symbol.intern("DEFAULT");

  public SymbolVectorEditor() {
    super(true,Symbol.class);
  }
  
  @Override
  protected Object getNewElement() {
    return DEFAULT_;
  }
  
  @Override
  protected Vector getNewVector() {
    return new SymbolVector();
  }
  
  @Override
  public boolean treatElementAsProperty(Object obj) {
    return true;
  }

  @Override
  public String getJavaInitializationString()
  {
    StringBuffer buffer = 
      new StringBuffer("new com.gensym.controls.SymbolVector(new String[]{");
    SymbolVector vector = (SymbolVector) super.getValue();
    int i,size = vector.size();
    for (i=0; i<size ; i++)
      if (i == 0)
	buffer.append("\""+vector.elementAt(i).toString()+"\"");
      else
	buffer.append(", \""+vector.elementAt(i).toString()+"\"");
    buffer.append("})");
    return buffer.toString();
  }
}
