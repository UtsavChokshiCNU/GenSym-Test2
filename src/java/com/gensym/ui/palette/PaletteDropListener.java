/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PaletteDropListener.java
 *
 */

package com.gensym.ui.palette;

/** 
 * An interface for notification of an item being created (dropped) from a palette. 
 */
public interface PaletteDropListener{

  /**
   * This method is called whenever an item is created (dropped) from a palette.
   */
  public void dropOccurred (PaletteDropEvent paletteDropEvent);

  /**
   * This method is called whenever creation from a palette is cancelled.
   */
  public void dropCancelled (PaletteDropEvent paletteDropEvent);



}
