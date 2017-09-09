/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DefaultMarkerFormat.java
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.displays;

import java.awt.Color;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;

/** A pre-initialized version that acts as the default version
 * in a chart. All important slots are initialized to be non-null;
 */
class DefaultMarkerFormat extends MarkerFormat {

  private static final Structure DEFAULT_MARKER_STYLE =
  new Structure(new Symbol[] {STANDARD_SHAPE_},
                new Object[] {TRIANGLE_},
		1);

  public DefaultMarkerFormat(TrendChart chart) {
    super(chart, null, DEFAULT_);
    markerFrequency = DEFAULT_MARKER_FREQUENCY_OBJ;
    markerStyle = DEFAULT_MARKER_STYLE;
    markersVisible = Boolean.FALSE;
    markerColor = Color.black;
  }

  @Override
  public void configure(Chart genericChart) {
  }  
}
