/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 StructuredObjectCreator.java
 *
 */

package com.gensym.ui;

import java.util.Vector;

/**
 * A StructuredObjectCreator is an interface that defines ObjectCreators with one 
 * or more of these characteristics:
 *    (a) logical groupings of items,
 *    (b) a hierarchical structure of items,
 *    (c) a dynamic number of items.
 *<p>
 * The tree-like structure of a <code>StructuredObjectCreator</code> is defined as 
 * follows:
 *<p>
 *  - Each <code>String[]</code> is a logical grouping of items.  When added to a
 *    palette, each grouping may be visually separated.  
 * </p><p>
 *  - Each <code>Object[]</code> defines a step in the hierarchy.  
 *    When added to a palette, a button with a "sub-palette" may be added.
 * </p><p>
 *  - Each <code>String</code> is a key that represents an item.  The leaves of 
 *    the tree are always <code>Strings</code>.
 *</p></p><p>
 * Clients may add themselves as listeners to get notification of changes in the
 * structure of a <code>StructuredObjectCreator</code>.
 *</p>
 */
public interface StructuredObjectCreator extends ObjectCreator{

  /**
   * Returns an Object[] that defines the structure of the StructuredObjectCreator.
   */
  public Object[] getStructuredKeys();

  /** 
   * Adds a StucturedObjectCreatorListener. 
   */
  public void addStructuredObjectCreatorListener(StructuredObjectCreatorListener listener);

  /** 
   * Removes a StructuredObjectCreatorListener. 
   */
  public void removeStructuredObjectCreatorListener(StructuredObjectCreatorListener listener);
}
