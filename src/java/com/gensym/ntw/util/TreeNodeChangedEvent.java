/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TreeNodeChangedEvent.java
 *
 */

package com.gensym.ntw.util;

import java.util.EventObject;
 
public class TreeNodeChangedEvent extends EventObject {
 
  InstanceData userObject;
  String newStringValue;

  public TreeNodeChangedEvent(Object source,
			      InstanceData data,
			      String newValue){
    super(source);
    userObject = data;
    newStringValue = newValue;
  }
 
  public InstanceData getUserObject(){
    return userObject;
  }

  public String getNewValue() {
    return newStringValue;
  }
}
