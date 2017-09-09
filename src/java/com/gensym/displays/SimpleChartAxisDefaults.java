/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      SimpleChartAxisDefaults.java
 *
 * Description:
 *               One set of information to draw and how to draw it
 *
 *
 */
package com.gensym.displays;

import com.gensym.ntw.util.G2FontMap;
import com.gensym.ntw.util.G2ColorMap;
import com.gensym.util.*;
import com.gensym.message.*;
import java.util.*;
import java.awt.*;


/** Corresponds to the "axis defaults of a Chart in G2.
 * being a default axis.
 * @author Robert Penny
 * @version 1.0 December 1997
 * @undocumented
 */
class SimpleChartAxisDefaults extends SimpleChartAxis {

  static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.displays.chart",
			   SimpleChartAxisDefaults.class);
  static Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.TraceMessages");

  static final Integer index = null;

  SimpleChartAxisDefaults(SimpleChart chart) {
    super(chart);
  }

  //
  // G2 Slots
  //
  @Override
  Color getLineColor(){
    Color color = null;
    if (annotations != null) {
      color = G2ColorMap.get(annotations, LINE_COLOR_, null);
    }
    if (color == null)
      color = chart.getLineColor();
    return color;
  }

  @Override
  Color getTextColor() {
    Color color = null;
    if (annotations != null) {
      color = G2ColorMap.get(annotations, TEXT_COLOR_, null);
    }
    if (color == null)
      color = chart.getTextColor();
    return color;
  }

  @Override
  Color getGridColor(){
    Color color = null;
    if (annotations != null) {
      color = G2ColorMap.get(annotations, GRID_COLOR_, null);
    }
    if (color == null)
      color = chart.getGridColor();
    return color;
  }

  @Override
  Boolean getGridVisible(){
    Boolean visible = null;
    if (annotations != null) {
      visible = (Boolean)annotations.getAttributeValue(GRID_VISIBLE_, null);
    }
    if (visible == null)
      return chart.getGridVisible() ? Boolean.TRUE : Boolean.FALSE;
    else
      return visible;
  }

  @Override
  Font getDeclaredFont() {
    Font font = null;
    if (annotations != null) {
      font =
 	G2FontMap.get(annotations, TEXT_SIZE_, null);
    }
    if (font == null)
      font = chart.getDeclaredFont();
     return font;
  }



  @Override
  Number getDeclaredAxisCrossover() {
    Number crossover = null;
    if (annotations != null) {
      crossover =
	(Number)annotations.getAttributeValue(AXIS_CROSSOVER_, null);
    }
    return crossover;
  }

  @Override
  Number getDeclaredAxisMinimum() {
    return (annotations == null ?
	    null :
	    (Number)annotations.getAttributeValue(AXIS_MINIMUM_, null));
  }

  @Override
  Number getDeclaredAxisMaximum() {
    return (annotations == null ?
	    null :
	    (Number)annotations.getAttributeValue(AXIS_MAXIMUM_, null));
  }

  @Override
  Number getDeclaredNumberOfTickmarks() {
    return
      (annotations == null ?
       null :
       (Number)annotations.getAttributeValue(NUMBER_OF_TICKMARKS_, null));
  }

  @Override
  Number getDeclaredTickmarkInterval() {
    return
      (annotations == null ?
       null :
       (Number)annotations.getAttributeValue(TICKMARK_INTERVAL_, null));
  }

  @Override
  int getVisibleLength() {
    return -1;
  }

  @Override
  int getOffset() {
    return 0;
  }

  //
  // drawing support
  //

  @Override
  void drawTickmarksOrGrid(Graphics g, double tickmarkInterval, double scale,
			   boolean doGrid){}
  @Override
  void drawLabels(Graphics g, double tickmarkInterval, double scale){}
  @Override
  void drawAxis(Graphics g){}

  void drawAxisFeatures(Graphics g) {};  
}
