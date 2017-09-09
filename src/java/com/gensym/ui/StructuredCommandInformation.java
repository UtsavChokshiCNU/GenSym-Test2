/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 StructuredCommandInformation.java
 *
 */

package com.gensym.ui;

public abstract class StructuredCommandInformation{

  String key;

  protected StructuredCommandInformation(String key){
    this.key = key;
  }

  /** Returns the key for the command. */
  public String getKey(){
    return key;
  }

}
  
