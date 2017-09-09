/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      SimpleChartDataSeries.java
 *
 *
 */
package com.gensym.displays;

import java.util.*;
import java.awt.*;
import com.gensym.ntw.util.G2ColorMap;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.util.symbol.G2ColorSymbols;

/** Holds the x and y values for a data series
 * @version 1.0 12/15/97
 * @author Robert Penny
 * @undocumented
 */

class SimpleChartDataSeries implements com.gensym.util.symbol.ChartSymbols{
  static private MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.displays.chart",
			   SimpleChartDataSeries.class);
  static private Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.TraceMessages");

  SimpleChart chart;
  //int[] xArray, yArray;
  Sequence xData, yData;
  // fix this: Not sure if I will use this information
  Symbol sourceKind;

  // The index is really only used here as a debugging tool
  Integer index;
  Structure attributes, dataPointAttributes;

  // This should only be used for the default. If separate subclass
  // made for defaults, then move to that class, and remove from
  // here.
  SimpleChartDataSeries(SimpleChart chart) {
    this.chart = chart;
  }

  SimpleChartDataSeries(SimpleChart chart, Structure data, Integer index)
  throws NoSuchAttributeException {
    this(chart);
    this.index = index;
    configureData(data);
    //configureAttributes(features);
  }

  void configureData (Structure data) throws NoSuchAttributeException {
    xData = (Sequence)data.getAttributeValue(DATA_SERIES_CACHE_1_);
    yData = (Sequence)data.getAttributeValue(DATA_SERIES_CACHE_2_);
    sourceKind = (Symbol)data.getAttributeValue(DATA_SERIES_SOURCE_KIND_);
  }

  private Vector dataColorAnnotationPath = new Vector();

  void setAnnotations(Structure features)
  throws NoSuchAttributeException {
    Sequence allAnnotations =
      (Sequence)features.getAttributeValue(ANNOTATIONS_);
    for (Enumeration en = allAnnotations.elements();
	 en.hasMoreElements();) {
      Structure current = (Structure)en.nextElement();
      Sequence path = (Sequence)current.getAttributeValue(PATH_, null);
      Structure attrs = (Structure)current.getAttributeValue(ATTRIBUTES_);
      if (path == null) {
	// annotations for this data series
	attributes = attrs;
	Trace.send(5, traceKey, i18nTrace, "scdsdataSeriesAttrs",
		   index, attrs);
      } else if (isDataPointPath(path)) {
	dataPointAttributes = attrs;
	Trace.send(5, traceKey, i18nTrace, "scdsdataPointAttrs",
		   index, attrs);
      } else {
	Trace.send(5, traceKey, i18nTrace, "scdsirrelevantDataAnnotations",
		   path, attrs);
      }
    }
  }

  void setUpDataColorAnnotationPath() {
    // set up the lineColor lookup path
    if (attributes != null)
      dataColorAnnotationPath.addElement(attributes);
    if (dataPointAttributes != null)
      dataColorAnnotationPath.addElement(dataPointAttributes);
    // NOTE: due to legacy code, the chart.seriesDefaults object
    // will get this structure twice. The code that looks up
    // in dataColorAnnotationPath will not be called on the
    // chart.seriesDefaults object.
    if (chart.seriesDefaultAnnotations != null)
      dataColorAnnotationPath.addElement(chart.seriesDefaultAnnotations);
    if (chart.dataPointFeatures != null)
      dataColorAnnotationPath.addElement(chart.dataPointFeatures);
    if (chart.defaultFeatures != null)
      dataColorAnnotationPath.addElement(chart.defaultFeatures);
  }

  Color getDataColor() {
    Object colorName =
      SimpleChart.getDeclaredValueOfPart(LINE_COLOR_, dataColorAnnotationPath,
					 G2ColorSymbols.BLACK_);
    return G2ColorMap.get(colorName);
  }

  /** The only meaningful <code>path</code> is one that indicates
   * that the attributes describe "any data point".
   * This predicate returns true if <code>path</code> is a sequence with
   * one structure, and the structure has one attribute, PART-NAME, with the
   * value CHART-DATA-POINT */
  private boolean isDataPointPath(Sequence path) {
    if (path.size() != 1) {
      Trace.send(10, traceKey, i18nTrace, "scdspathWrongLength",
		 new Integer(path.size()), path);
      return false;
    }
    try {
      Structure struct = (Structure)path.firstElement();
      if (struct.getAttributeCount() != 1) {
	Trace.send(10, traceKey, i18nTrace, "scdspathTooManyAttributes",
		   new Integer(struct.getAttributeCount()), struct, path);
	return false;
      }
      Symbol partName = (Symbol)struct.getAttributeValue(PART_NAME_, null);
      if (CHART_DATA_POINT_.equals(partName))
	return true;
    } catch (ClassCastException cce) {
      // this exception can happen if the structures and sequences don't
      // contain what we expect, i.e., this path is not indicating data points
      Trace.send(10, traceKey, i18nTrace, "scdspathWrongClass",
		 cce, path);
      return false;
    }
    Trace.send(10, traceKey, i18nTrace, "scdspathWrongOrMissingPartName",
	       path);
    return false;
  }

  Object getDeclaredValue(Symbol name) {
    return chart.getDeclaredValueOfPart(name, attributes,
					chart.seriesDefaults.attributes);
  }

  Color getDeclaredColor(Symbol name, Color defaultColor) {
    Symbol colorName = (Symbol)getDeclaredValue(name);
    if (colorName == null)
      colorName = (Symbol)getDeclaredPointValue(name);
    if (colorName != null)
      return G2ColorMap.get(colorName);
    
    return defaultColor;
  }

  Color getLineColor() {
    Color color = getDeclaredColor(LINE_COLOR_, null);
    if (color == null && chart.seriesDefaults != this)
      color = chart.seriesDefaults.getLineColor();
    if (color == null)
      color = chart.getLineColor();
    return color;
  }

  boolean getConnectionLineVisible() {
    Boolean visible = (Boolean)getDeclaredPointValue(CONNECTION_LINE_VISIBLE_);
    if (visible != null)
      return visible.booleanValue();

    //return true;

    return chart.getStyle().getConnectionLineVisible();
  }

  boolean getLineFromLastToFirstPointVisible() {
    Boolean visible =
      (Boolean)getDeclaredValue(LINE_FROM_LAST_TO_FIRST_POINT_VISIBLE_);
    if (visible != null)
      return visible.booleanValue();

    return false;
  }

  Object getDeclaredPointValue(Symbol name) {
    Object value =
      chart.getDeclaredValueOfPart(name, dataPointAttributes,
				   chart.seriesDefaults.dataPointAttributes);

    if (value == null)
      return chart.dataPointFeatures.getAttributeValue(name, null);
    else
      return value;
  }

  boolean getIndicatorVisible() {
    Boolean visible =
      (Boolean)getDeclaredPointValue(INDICATOR_VISIBLE_);

    if (visible != null)
      return visible.booleanValue();

    return chart.getStyle().getIndicatorVisible();
  }

  Symbol getIndicator() {
    Symbol returnValue = (Symbol)getDeclaredPointValue(INDICATOR_);
    if (returnValue == null)
      // default
      return chart.getStyle().getIndicator();
    else
      return returnValue;
  }

  Color getDataPointLineColor() {
    Symbol colorName = (Symbol)getDeclaredPointValue(LINE_COLOR_);
    if (colorName != null)
      return G2ColorMap.get(colorName);

    return getLineColor();
  }

  int getDataPointWidth() {
    Number w = (Number)getDeclaredPointValue(WIDTH_);

    if (w == null)
      return 5;
    else
      return w.intValue();
  }

  int getDataPointHeight() {
    Number h = (Number)getDeclaredPointValue(HEIGHT_);

    if (h == null)
      return 5;
    else
      return h.intValue();
  }

  int xArray[], yArray[];

  void draw(Graphics g) {
    Trace.send(10, traceKey, i18nTrace, "scdsdraw", index);
    // We have been given an invalid data series from G2, so
    // there is no point in trying to draw it.
    if (xData == null)
      return;
    double xScale = chart.horizontalAxis.getScale();
    int xOffset = chart.horizontalAxis.getOffset();
    double yScale = chart.verticalAxis.getScale() * -1.0;
    int yOffset = chart.verticalAxis.getOffset();
    setScreenLocations(xScale, xOffset, yScale, yOffset);
    g.setColor(getDataColor());
    if (getConnectionLineVisible())
      drawConnectionLine(g);

    if (getIndicatorVisible())
      drawIndicators(g);
  }

  private void setScreenLocations(double xScale, int xOffset,
				  double yScale, int yOffset) {
    int count = (int)Math.min(xData.size(), yData.size());
    xArray = new int[count];
    int i = 0;
    for (Enumeration en = xData.elements();
	 en.hasMoreElements() && i < count;) {
      double dataValue = ((Number)en.nextElement()).doubleValue();
      xArray[i++] = (int)(dataValue * xScale) + xOffset;
    }

    yArray = new int[count];
    i = 0;
    for (Enumeration en = yData.elements();
	 en.hasMoreElements() && i < count;) {
      double dataValue = ((Number)en.nextElement()).doubleValue();
      yArray[i++] = (int)(dataValue * yScale) + yOffset;
    }
  }

  void drawConnectionLine(Graphics g) {
    boolean doLoop = getLineFromLastToFirstPointVisible();
    

    if (doLoop)
      g.drawPolygon(xArray, yArray, xArray.length);
    else
      g.drawPolyline(xArray, yArray, xArray.length);
  }

  void drawIndicators(Graphics g) {
    int width = getDataPointWidth();
    int height = getDataPointHeight();
    int wLeft = width/2;
    int wRight = width - wLeft;
    int hTop = height/2;
    int hBottom = height - hTop;
    Symbol indicator = getIndicator();

    if (SQUARE_.equals(indicator)) {
      drawSquares(g, wLeft, width, hTop, height);
    } else if (RECTANGLE_.equals(indicator)) {
      drawRectangles(g, wLeft, width, hTop, height);
    } else if (CROSS_.equals(indicator)) {
      drawCrosses(g, wLeft, wRight, hTop, hBottom);
    } else if (TRIANGLE_.equals(indicator)) {
      drawTriangles(g, wLeft, wRight, hTop, hBottom);
    } else if (X_.equals(indicator)) {
      drawX(g, wLeft, wRight, hTop, hBottom);
    } else if (BAR_.equals(indicator)) {
      drawBar(g, wLeft, width, hTop, height);
    } else if (SOLID_BAR_.equals(indicator)) {
      drawSolidBar(g, wLeft, width, hTop, height);
    } else if (COLUMN_.equals(indicator)) {
      drawColumn(g, wLeft, width, hTop, height);
    } else if (SOLID_COLUMN_.equals(indicator)) {
      drawSolidColumn(g, wLeft, width, hTop, height);
    }
  }

  void drawSquares(Graphics g, int wLeft, int width, int hTop, int height) {
    for (int i = 0; i < xArray.length; i++) {
      g.fillRect(xArray[i] - wLeft, yArray[i] - hTop,
		 width, height);
    }
  }

  void drawRectangles(Graphics g, int wLeft, int width, int hTop, int height) {
    for (int i = 0; i < xArray.length; i++) {
      g.drawRect(xArray[i] - wLeft, yArray[i] - hTop,
		 width, height);
    }
  }

  void drawCrosses(Graphics g, int wLeft, int wRight, int hTop, int hBottom) {
    for (int i = 0; i < xArray.length; i++) {
      int x = xArray[i], y = yArray[i];
      g.drawLine(x - wLeft, y, x + wRight, y);
      g.drawLine(x, y - hTop, x, y + hBottom);
    }
  }

  void drawX(Graphics g, int wLeft, int wRight, int hTop, int hBottom) {
    for (int i = 0; i < xArray.length; i++) {
      int x = xArray[i], y = yArray[i];
      g.drawLine(x - wLeft, y - hTop, x + wRight, y + hBottom);
      g.drawLine(x - wLeft, y + hBottom, x + wRight, y - hTop);
    }
  }

  int triangleX[] = new int[3];
  int triangleY[] = new int[3];

  void drawTriangles(Graphics g, int wLeft, int wRight, int hTop, int hBottom){
    for (int i = 0; i < xArray.length; i++) {
      int x = xArray[i];
      int y = yArray[i];

      triangleX[0] = x - wLeft;
      triangleX[1] = x;
      triangleX[2] = x + wRight;

      triangleY[0] = y + hBottom;
      triangleY[1] = y - hTop;
      triangleY[2] = y + hBottom;

      g.drawPolygon(triangleX, triangleY, 3);
    }
  }

  void drawBar(Graphics g, int wLeft, int width, int hTop, int height) {
    int xOrigin = chart.verticalAxis.x;
    for (int i = 0; i < xArray.length; i++) {
      int x = xArray[i], y = yArray[i];
      g.drawRect(xOrigin, y - hTop, x - xOrigin, height);
    }
  }

  void drawSolidBar(Graphics g, int wLeft, int width, int hTop, int height) {
    int xOrigin = chart.verticalAxis.x;
    for (int i = 0; i < xArray.length; i++) {
      int x = xArray[i], y = yArray[i];
      g.fillRect(xOrigin, y - hTop, x - xOrigin, height);
    }
  }

  void drawColumn(Graphics g, int wLeft, int width, int hTop, int height) {
    int yOrigin = chart.horizontalAxis.y;
    for (int i = 0; i < xArray.length; i++) {
      int x = xArray[i], y = yArray[i];
      g.drawRect(x - wLeft, y, width, yOrigin - y);
    }
  }

  void drawSolidColumn(Graphics g, int wLeft, int width,
		       int hTop, int height) {
    int yOrigin = chart.horizontalAxis.y;
    for (int i = 0; i < xArray.length; i++) {
      int x = xArray[i], y = yArray[i];
      g.fillRect(x - wLeft, y , width, yOrigin - y);
    }
  }

}
