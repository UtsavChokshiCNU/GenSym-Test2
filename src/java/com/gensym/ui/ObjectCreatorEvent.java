/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ObjectCreatorEvent.java
 *
 */

package com.gensym.ui;

import java.util.EventObject;

/** A ObjectCreatorEvent is delivered whenever the availability, icon, or description
 *  of an ObjectCreator changes, and whenevener the structure of a 
 *  StructuredObjectCreator changes.
 */
public class ObjectCreatorEvent extends EventObject{

  private String key;

  /** Creates a ObjectCreatorEvent with the specified source object and
   *  reference key. */
  public ObjectCreatorEvent(Object source, String key){
    super(source);
    this.key = key;
  }

  /** Returns the reference key into the ObjectCreator that triggered the 
   *  ObjectCreatorEvent. */
  public String getKey(){
    return key;
  }

}
