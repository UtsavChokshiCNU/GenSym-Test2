/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ObjectCreatorListener.java
 *
 */

package com.gensym.ui;

/** An interface for listening to changes in ObjectCreators. */
public interface ObjectCreatorListener{


  /**
   * This methods gets invoked whenever the availability of an ObjectCreator changes.
   *@see com.gensym.ui.ObjectCreator#isAvailable
   */
  public void availabilityChanged(ObjectCreatorEvent event);

  /**
   * This method gets invoked whenever the description of an ObjectCreator changes.
   * @see com.gensym.ui.ObjectCreator#getDescription
   */
  public void descriptionChanged(ObjectCreatorEvent event);

  /**
   * This method gets invoked whenever the icon of an ObjectCreator changes.
   * @see com.gensym.ui.ObjectCreator#getIcon
   */
  public void iconChanged(ObjectCreatorEvent event);

}
