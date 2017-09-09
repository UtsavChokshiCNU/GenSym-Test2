/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   SpinEvent.java 
 * 
 * 
 */ 

package com.gensym.widgets;

import java.util.EventObject;

public class SpinEvent extends EventObject {

  boolean up;

  public SpinEvent(Object source, boolean isUp) {
    super(source);
    up = isUp;
  }

  public boolean isUp() {
    return up;
  }
}
