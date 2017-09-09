/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ObjectFactory.java
 *
 */

package com.gensym.ui;

public interface ObjectFactory{

  /**
   * Returns an object for the "item" specified by key.
   */
  public Object createObject(String key);

}
