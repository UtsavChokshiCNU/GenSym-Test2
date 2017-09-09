/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   SpinListener.java 
 * 
 * 
 */ 

package com.gensym.widgets;

import java.util.EventListener;

public interface SpinListener extends EventListener {

  public void spinUp(SpinEvent event);
  public void spinDown(SpinEvent event);
}
