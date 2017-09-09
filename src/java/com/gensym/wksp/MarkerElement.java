
package com.gensym.wksp;

import java.awt.Dimension;
import com.gensym.draw.*;
import java.awt.Color;

class MarkerElement extends RectElement {

  private static final int[] markerFreedom = {3, 2, 3, 1, 3, 2, 3, 1};
  private static final int HORIZONTALLY_EXTENSIBLE = 1, VERTICALLY_EXTENSIBLE = 2;
  private static final Color fillColor, outlineColor;
  private static int markerHalfWidth;
  int location;

  static {
    fillColor = Color.getColor ("com.gensym.wksp.marker.color.fill", Color.white);
    outlineColor = Color.getColor ("com.gensym.wksp.marker.color.outline", Color.black);
    markerHalfWidth = Integer.getInteger ("com.gensym.wksp.marker.halfwidth", 3).intValue ();
  }

  MarkerElement (int locn, int x, int y) {
    super (fillColor, x - markerHalfWidth, y - markerHalfWidth, 2*markerHalfWidth, 2*markerHalfWidth);
    location = locn;
  }

  MarkerElement (int locn, int x, int y, int width, int height) {
    super(fillColor, x, y, width, height);
    location = locn;
  }

  boolean isHorizontallyExtensible () {
    return ((markerFreedom[location] & HORIZONTALLY_EXTENSIBLE) != 0);
  }

  boolean isVerticallyExtensible () {
    return ((markerFreedom[location] & VERTICALLY_EXTENSIBLE) != 0);
  }

  @Override
  public void paint (java.awt.Graphics g) {
    super.paint (g);
    g.setColor (outlineColor);
    Dimension d = getSize();
    g.drawRect (0, 0, d.width - 1, d.height - 1);
  }

  protected static Color getFillColor(){
    return fillColor;
  }

  protected static Color getOutlineColor(){
    return outlineColor;
  }

  protected static int getMarkerHalfWidth(){
    return markerHalfWidth;
  }
}
