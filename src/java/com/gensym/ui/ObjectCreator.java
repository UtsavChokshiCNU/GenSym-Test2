/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ObjectCreator.java
 *
 */

package com.gensym.ui;

import java.awt.Image;
import java.awt.event.ActionListener;

/** 
 *  An ObjectCreator is an interface for creating instances of classes.
 *  A unique key is used to represent each "item" that may be created off the
 *  Palette.  Each key may represent a unique class, may represent a unique
 *  configuration of a class, or a combination of both.
 *  The mapping of a key to a "item" is determined by the implementation of 
 *  ObjectCreator.
 *<p>  
 *  An ObjectCreator also provides information regarding the availability,
 *  description, and icon of each "item" that it represents, as well as, providing a 
 *  method for creating the item.
 *</p><p>
 *  Clients can add themselves as ObjectCreatorListeners to receive notification
 *  of changes in availiability, descriptions, and icons.
 *</p>
 *  @see com.gensym.ui.palette.Palette
 */
public interface ObjectCreator extends ObjectFactory{

  public static final int SMALL_ICON = 0;
  public static final int LARGE_ICON = 1;
  public static final int SHORT_DESCRIPTION = 0;
  public static final int LONG_DESCRIPTION = 1;
 
 /**
   * Returns an array of String arrays.
   */
  public String[] getKeys();

  /**
   * Returns availability status for the "item" referenced by key.
   */
  public boolean isAvailable(String key);

  /**
   * Returns a textual description for the "item" specified by key, where type
   * may be either LONG_DESCRIPTION or SHORT_DESCRIPTION. 
   */
  public String getDescription (String key, int type);

  /**
   * Returns an image of the specified size for the "item" specified by key,
   * where size may be either SMALL_ICON or LARGE_ICON
   */
  public Image getIcon (String key, int size);

  /** 
   * Adds a ObjectCreatorListener. 
   */
  public void addObjectCreatorListener(ObjectCreatorListener listener);

  /** 
   * Removes a ObjectCreatorListener. 
   */
  public void removeObjectCreatorListener(ObjectCreatorListener listener);
}




