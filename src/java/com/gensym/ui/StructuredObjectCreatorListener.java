/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 StructuredObjectCreatorListener.java
 *
 */

package com.gensym.ui;

/** 
 * An interface for listening to changes in StructuredObjectCreators.
 */
public interface StructuredObjectCreatorListener extends ObjectCreatorListener{

  /**
   * This method gets invoked whenever the structure of a StructuredObjectCreator 
   * changes
   */
  public void structureChanged(ObjectCreatorEvent event);

}
