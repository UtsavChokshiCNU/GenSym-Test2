/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PaletteDropTarget.java
 *
 */

package com.gensym.ui.palette;

/** 
 *  An interface for the drop targets of items that are created off of a Palette. 
 */
public interface PaletteDropTarget{

  /** This method gets called whenever a toggle button on a Palette gets toggled. */
  public void paletteButtonStateChanged(PaletteEvent event);

}
