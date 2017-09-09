/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PaletteDropEvent.java
 *
 */

package com.gensym.ui.palette;

import java.util.EventObject;

/**
 *  A PaletteDropEvent is delivered whenever an item is created (dropped) 
 *  from a palette.
 */
public class PaletteDropEvent extends EventObject{

  private boolean dropOccurred;

  public PaletteDropEvent (PaletteDropTarget source, boolean dropOccurred) {
    super(source);
    this.dropOccurred = dropOccurred;
  }

  public boolean getDropOccurred () {
    return dropOccurred;
  }

}
