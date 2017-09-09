/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PaletteListener.java
 *
 */

package com.gensym.ui.palette;

/** An interface for notification of palettes being created. */

public interface PaletteListener{

  /** This method gets called whenever a new palette is created. */
  public void paletteCreated(PaletteEvent event);

}

