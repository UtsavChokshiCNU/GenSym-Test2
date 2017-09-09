/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ColorPendingListener.java
 *
 */
package com.gensym.editor.color;

/** 
 * An interface for listening for when a color is in a
 * pending state in G2StandardColorsCanvas (mouse hovering
 * over a color block)
 */
public interface G2ColorPendingListener {

  /**
   * This method is called whenever a color is in a pending
   * state in G2ColorsCanvas.
   * All listeners received a G2ColorPendingEvent.
   * @param event A G2ColorPendingEvent.
   */
  public void g2ColorPending(G2ColorPendingEvent event);

}
