package com.gensym.controls;

import com.gensym.dlgevent.*;
import com.gensym.util.Symbol;

public interface AttributeEditor extends ObjectUpdateListener
{
  public Symbol getAttribute();

  public void setAttribute(Symbol symbol);

  public void addObjectChangeListener (ObjectChangeListener listener);

  public void removeObjectChangeListener(ObjectChangeListener listener);
  
}
