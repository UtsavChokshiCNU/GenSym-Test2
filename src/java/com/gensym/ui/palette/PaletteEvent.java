/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 PaletteEvent.java
 *
 */

package com.gensym.ui.palette;

import java.util.EventObject;
import javax.swing.JToggleButton;
import com.gensym.ui.ObjectCreator;

/** 
 *  A PaletteEvent is delivered to PaletteListeners whenever a Palette is created 
 *  and to PaletteDropTargets whenever a toggle button on a Palette is selected. 
 */
public class PaletteEvent extends EventObject{

  private PaletteButton button;
  private String key;

  /**
   * Creates a PaletteEvent with the specified source object.
   */
  public PaletteEvent(Object source){
    this(source, null, null);
  }

  /**
   * Creates a PaletteEvent with the specified source object,  toggle button,
   * and key.
   */ 
  public PaletteEvent(Object source, PaletteButton paletteButton, String key){
        super(source);
        button = paletteButton;
	this.key = key;
  }

  /**
   * If the PaletteEvent is a result of a toggle button being toggled, then the 
   * palette button that was toggled is returned; otherwise null is returned.
   */
  public PaletteButton getButton(){
    return button;
  }

  /**
   * If the PaletteEvent is a result of a toggle button being toggled, then the 
   * key associated with the selected toggle button is returned; otherwise
   * null is returned.
   */
  public String getKey(){
    return key;
  }

}
