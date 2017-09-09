package com.gensym.editor.icon.core;

public class ValueChangedEvent extends java.util.EventObject {
  private Object newValue;
  
  public ValueChangedEvent(Object source, Object newValue) {
    super(source);
    this.newValue = newValue;
  }

  public Object getNewValue() {
    return newValue;
  }

}
