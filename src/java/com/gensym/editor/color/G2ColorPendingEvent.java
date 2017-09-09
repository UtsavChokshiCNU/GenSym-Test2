/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 G2ColorPendingEvent.java
 *
 */
package com.gensym.editor.color;

import java.awt.Color;
import java.util.EventObject;
import com.gensym.util.Symbol;

/**
 * G2ColorPendingEvent are dispatched whenever a color is in a
 * pending state in G2ColorsCanvas. In order to receive 
 * G2ColorPendingEvents, components must be a G2ColorPendingListener.
 */
public class G2ColorPendingEvent extends EventObject {
  private String colorString_;
  private Symbol colorSymbol_;
  private Color  color_;

  /**
   * @param source An Object component that is the source of 
   * the event
   * @param colorString_ A String containing the G2 standard color 
   * name of the pending color.
   * @param color_ A Color component for the pending G2 
   * standard color.
   * @param colorRGB An integer array containing the RGB values 
   * of the pending G2 standard color.
   */
  public G2ColorPendingEvent(Object source,
			     String colorString_,
			     Symbol colorSymbol_,
			     Color color_){
    super(source);
    this.colorString_ = colorString_;
    this.colorSymbol_ = colorSymbol_;
    this.color_       = color_;
    //this.colorRGB_    = colorRGB;
  }

  /**
   * Gets the String representation of the pending G2 standard color.
   * @return String A String containing the name of the 
   * pending G2 standard color
   */
  public String getColorString() {
    return colorString_;
  }

  /**
   * Gets the G2 symbol name of the pending G2 standard color.
   * @return Symbol A Symbol containing the G2 symbol name of the 
   * pending G2 standard color
   */
  public Symbol getColorSymbol() {
    return colorSymbol_;
  }

  /**
   * Gets the Color of the pending G2 standard color.
   * @return Color A Color component for the pending G2 
   * standard color.
   */
  public Color getColor() {
    return color_;
  }
}
