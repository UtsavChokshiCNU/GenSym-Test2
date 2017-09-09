package com.gensym.ui.menu;

import java.util.Hashtable;

public class KeyMap extends Hashtable{

  private Object nullMarker;

  KeyMap(Object nullMarker){
    this.nullMarker = nullMarker;
  }

  @Override
  public synchronized Object put(Object key, Object value){
    if (value == null)
      return super.put(key, nullMarker);
    else
      return super.put(key, value);
  }
}
