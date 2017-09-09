/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ColumnDefinition.java
 *
 */

package com.gensym.ntw.util;

class ColumnDefinition{

  private String name;
  private Class type;
  private boolean editable;

  public ColumnDefinition(String name, Class type, boolean editable){
    this.name = name;
    this.type = type;
    this.editable = editable;
  }

  public String getName(){
    return name;
  }

  public Class getType(){
    return type;
  }

  public boolean isEditable(){
    return editable;
  }
}
