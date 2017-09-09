/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ColorSelectedListener.java
 *
 */
package com.gensym.editor.color;

/** 
 * An interface for listening for when a color is selected in a
 * G2StandardColorsCanvas 
 */
public interface G2ColorSelectedListener {

  /**
   * This method is called whenever a color is selected in G2ColorsCanvas.
   * All listeners received a G2ColorSelectedEvent.
   * @param event A G2ColorSelectedEvent.
   */
  public void g2ColorSelected(G2ColorSelectedEvent event);

}
