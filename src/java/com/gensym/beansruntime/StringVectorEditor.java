package com.gensym.beansruntime;

import java.awt.*;
import java.awt.event.*;
import java.beans.*;

import java.util.Vector;

public class StringVectorEditor extends  VectorEditor
{
  
  public StringVectorEditor() {
    super(true,String.class);
  }  
  
  @Override
  protected Object getNewElement() {
    return "NEW-ENTRY";
  }
  
  @Override
  protected Vector getNewVector() {
    return new StringVector();
  }
  
  @Override
  public boolean treatElementAsProperty(Object obj) {
    return true;
  }

  @Override
  public String getJavaInitializationString()
  {
    StringBuffer buffer = 
      new StringBuffer("new com.gensym.beansruntime.StringVector(new String[]{");
    StringVector vector = (StringVector) super.getValue();
    int i,size = vector.size();
    for (i=0; i<size ; i++)
      if (i == 0)
	buffer.append("\""+vector.elementAt(i)+"\"");
      else
	buffer.append(", \""+vector.elementAt(i)+"\"");
    buffer.append("})");
    return buffer.toString();
  }
}
