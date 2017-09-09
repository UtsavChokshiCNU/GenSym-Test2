/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      SimpleChartAxis.java
 *
 * Description:
 *               One set of information to draw and how to draw it
 *
 *
 */
package com.gensym.displays;

import com.gensym.ntw.util.*;
import com.gensym.util.*;
import com.gensym.message.*;
import java.util.*;
import java.awt.*;
import java.text.NumberFormat;


/** Corresponds to an axis of a Chart in G2.
 * @author Robert Penny
 * @version 1.0 December 1997
 * @undocumented
 */
abstract class SimpleChartAxis implements com.gensym.util.symbol.ChartSymbols {

  static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.displays.chart", SimpleChartAxis.class);
  static Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.TraceMessages");
  static final Symbol TEXT_SIZE_ = Symbol.intern ("TEXT-SIZE");
  static final Symbol AXIS_IS_DISCRETE_ = Symbol.intern ("AXIS-IS-DISCRETE");
  static final Symbol MAX_DIGITS_AFTER_POINT_ = Symbol.intern ("MAX-DIGITS-AFTER-POINT");
  static final Symbol MAX_DIGITS_BEFORE_POINT_ = Symbol.intern ("MAX-DIGITS-BEFORE-POINT");

  SimpleChart chart;
  SimpleChartAxis axisDefaults;

  //
  // Computed slots
  //
  double computedMaximum, computedMinimum;
  
  SimpleChartAxis(SimpleChart chart) {
    this.chart = chart;
  }

  SimpleChartAxis(SimpleChart chart,
		  SimpleChartAxis axisDefaults) {
    this(chart);
    this.axisDefaults = axisDefaults;
  }

  //
  // G2 Slots
  //
  Structure annotations;
  Structure computedDetails;

  void setAnnotations(Structure annotations) {
    this.annotations = annotations;
  }

  void setComputedDetails(Structure computedDetails) {
    this.computedDetails = computedDetails;
    computedMinimum = getComputedMinimum();
    computedMaximum = getComputedMaximum();

    Number digitsAfterPoint =
      (Number)computedDetails.getAttributeValue(MAX_DIGITS_AFTER_POINT_,
						null);
    if (digitsAfterPoint != null) {
      numberFormat.setMaximumFractionDigits(digitsAfterPoint.intValue());
      numberFormat.setMinimumFractionDigits(digitsAfterPoint.intValue());
    }

    Number digitsBeforePoint =
      (Number)computedDetails.getAttributeValue(MAX_DIGITS_BEFORE_POINT_,
						null);
    if (digitsBeforePoint != null) {
      numberFormat.setMaximumIntegerDigits(digitsBeforePoint.intValue());
    }

  }

  Color getLineColor(){
    Color color = null;
    if (annotations != null) {
      color = G2ColorMap.get(annotations, LINE_COLOR_, null);
    }
    if (color == null)
      color = axisDefaults.getLineColor();
    return color;
  }

  Color getTextColor() {
    Color color = null;
    if (annotations != null) {
      color = G2ColorMap.get(annotations, TEXT_COLOR_, null);
    }
    if (color == null)
      color = axisDefaults.getTextColor();
    return color;
  }

  Color getGridColor(){
    Color color = null;
    if (annotations != null) {
      color = G2ColorMap.get(annotations, GRID_COLOR_, null);
    }
    if (color == null)
      color = axisDefaults.getGridColor();
    return color;
  }

  Boolean getGridVisible(){
    Boolean visible = null;
    if (annotations != null) {
      visible = (Boolean)annotations.getAttributeValue(GRID_VISIBLE_, null);
    }
    if (visible == null)
      visible = axisDefaults.getGridVisible();
    return visible;
  }

  Number getDeclaredAxisMinimum() {
    Number min = null;
    if (annotations != null) {
      min = (Number)annotations.getAttributeValue(AXIS_MINIMUM_, null);
    }
    if (min == null)
      min = axisDefaults.getDeclaredAxisMinimum();
     return min;
  }

  void setComputedMinimum(double minimum) {
    computedMinimum = minimum;
  }

  double getComputedMinimum() {
    try {
      return ((Number)computedDetails.getAttributeValue(AXIS_MINIMUM_)).
	     doubleValue();
    } catch (NoSuchAttributeException nsae) {
      throw new UnexpectedException(nsae);
    }
  }
    
  double getComputedMaximum() {
    try {
      return ((Number)computedDetails.getAttributeValue(AXIS_MAXIMUM_)).
	     doubleValue();
    } catch (NoSuchAttributeException nsae) {
      throw new UnexpectedException(nsae);
    }
  }

  double getAxisMinimum() {
    return getComputedMinimum();
  }

  Number getDeclaredAxisMaximum() {
    Number max = null;
    if (annotations != null) {
      max = (Number)annotations.getAttributeValue(AXIS_MAXIMUM_, null);
    }
    if (max == null)
      max = axisDefaults.getDeclaredAxisMaximum();
     return max;
  }

  void setComputedMaximum(double maximum) {
    computedMaximum = maximum;
  }

  double getAxisMaximum() {
    return getComputedMaximum();
  }

  Number getDeclaredAxisCrossover() {
    Number crossover = null;
    if (annotations != null) {
      crossover =
	(Number)annotations.getAttributeValue(AXIS_CROSSOVER_, null);
    }
    if (crossover == null)
      crossover = axisDefaults.getDeclaredAxisCrossover();
     return crossover;
  }

  double getComputedCrossover() {
    try {
      return ((Number)computedDetails.getAttributeValue(AXIS_CROSSOVER_)).
             doubleValue();
    } catch (NoSuchAttributeException nsae) {
      throw new UnexpectedException(nsae);
    }
  }

  double getAxisCrossover() {
    return getComputedCrossover();
  }

  Number getDeclaredNumberOfTickmarks() {
    Number tickCount = null;
    if (annotations != null) {
      tickCount =
	(Number)annotations.getAttributeValue(NUMBER_OF_TICKMARKS_, null);
    }
    if (tickCount == null)
      tickCount = axisDefaults.getDeclaredNumberOfTickmarks();
    return tickCount;
  }

  Number getDeclaredTickmarkInterval() {
    Number tickmarkInterval = null;
    if (annotations != null) {
      tickmarkInterval =
	(Number)annotations.getAttributeValue(TICKMARK_INTERVAL_, null);
    }
    if (tickmarkInterval == null)
      tickmarkInterval = axisDefaults.getDeclaredTickmarkInterval();
    return tickmarkInterval;
  }

  double getTickmarkInterval() {
    // In G2, interval wins over count.
    Number declaredInterval = getDeclaredTickmarkInterval();
    double actualInterval;

    if (declaredInterval != null) {
      return declaredInterval.doubleValue();
    }

    Number numberObj = getDeclaredNumberOfTickmarks();

    if (numberObj == null)
      return -1.0D; // flag that it has not been specified

    int number = (int)Math.floor(numberObj.doubleValue());

    if (number <= 2)
      number = 2;

    return (computedMaximum - computedMinimum)/(double)(number - 1);
  }
    


  /** Operates on the assumption that one end or the other is going
   * to be the number largest in print-width.
   */
  Dimension computeLabelSize(double min, double max) {
    Dimension size1 = sizeOfNumber(min);
    Dimension size2 = sizeOfNumber(max);

    return new Dimension(Math.max(size1.width, size2.width),
			 size1.height);
  }

  Font getDeclaredFont() {
    Font font = null;
    if (annotations != null) {
      font =
 	G2FontMap.get(annotations, TEXT_SIZE_, null);
    }
    if (font == null)
      font = axisDefaults.getDeclaredFont();
     return font;
  }

  static int VERTICAL_SEPARATION = 3, HORIZONTAL_SEPARATION = 5;
  
  /**
   * Takes into account separation between labels
   */
  Dimension sizeOfNumber(double number) {
    FontMetrics metrics = chart.getFontMetrics(getDeclaredFont());
    String string = formatLabel(number);
    int width = metrics.stringWidth(string) + HORIZONTAL_SEPARATION;
    int height = metrics.getHeight() + VERTICAL_SEPARATION;
    return new Dimension(width, height);
  }

  // Charts don't allow for tweaking on an instance basis except
  // in the case of doing ints along the X axis in the
  // (all-data-series-are-one-quantity-lists-p) case
  static final NumberFormat defaultNumberFormat =
  new ScientificDecimalFormat();

  // This is only the default behavior, new code should be added
  // to set this more specifically to match the G2 behaviour
  // more closely.
  static {
    defaultNumberFormat.setMaximumFractionDigits(1);
  }

  private NumberFormat numberFormat =
  (NumberFormat)defaultNumberFormat.clone();

  String formatLabel(double number) {
    // fix this: when to show as int, when as float?
    // Answer: when the horizontal axis is just showing indices
    // into arrays.
    return numberFormat.format(number);
  }

  /** This method should only be called after the axis extrema
   * have been set
   */
  double getScale() {
    double dataLength = computedMaximum - computedMinimum;
    int visibleLength = getVisibleLength();
    return visibleLength/dataLength;
  }

  /** Must be a positive number */
  abstract int getVisibleLength();

  abstract int getOffset();

  int tickLength = 6;

  double getRealTickmarkInterval() {
    double tickmarkInterval = getTickmarkInterval();
    if (tickmarkInterval < 0) // not specified
      tickmarkInterval = computedMaximum - computedMinimum;

    return tickmarkInterval;
  }

  void drawTickmarks(Graphics g, double tickmarkInterval, double scale) {
    if (!getGridVisible().booleanValue()) {
      g.setColor(getLineColor());
      drawTickmarksOrGrid(g, tickmarkInterval, scale, false);
    }
  }

  void drawGrid(Graphics g, double tickmarkInterval, double scale) {
    if (getGridVisible().booleanValue()) {
      g.setColor(getGridColor());
      drawTickmarksOrGrid(g, tickmarkInterval, scale, true);
    }
  }

  abstract void drawTickmarksOrGrid(Graphics g,
				    double tickmarkInterval,
				    double scale,
				    boolean doGrid);
  abstract void drawLabels(Graphics g, double tickmarkInterval, double scale);
  abstract void drawAxis(Graphics g);
}
