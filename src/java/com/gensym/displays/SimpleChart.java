/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      SimpleChart.java
 *
 *
 */
package com.gensym.displays;

import java.util.*;
import java.awt.*;

import com.gensym.ntw.util.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.BufferedContainer;
import com.gensym.jgi.G2AccessException;

/** Corresponds to a Chart in G2. Given the nested "defaulting" behaviour
 * of all Chart parts, and given that a chart is not a "dynamic" object,
 * no attempt is made to "configure" the chart when new Annotations (or other
 * attribute changes) come in, but rather, all data necessary for painting
 * is extracted from the Chart item when the object is painted.
 * Is completely dependent on Structures and sequences for providing
 * configuration information.
 * @author Robert Penny
 * @version 1.0 December 1997
 * @undocumented
 */
public class SimpleChart extends BufferedContainer
implements com.gensym.util.symbol.ChartSymbols {

  static private MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.displays.chart", SimpleChart.class);
  static private Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.TraceMessages");

  private static final Integer
  HORIZONTAL_INDEX = new Integer(1),
    VERTICAL_INDEX = new Integer(2);

  static private final int DEFAULT_LEFT_MARGIN = 8,
    DEFAULT_TOP_MARGIN = 8,
    DEFAULT_RIGHT_MARGIN = 8,
    DEFAULT_BOTTOM_MARGIN = 8;

  static final Structure NULL_STRUCT = new Structure();

  private int leftMargin = DEFAULT_LEFT_MARGIN,
    topMargin = DEFAULT_TOP_MARGIN,
    rightMargin = DEFAULT_RIGHT_MARGIN,
    bottomMargin = DEFAULT_BOTTOM_MARGIN;

  SimpleChartHorizontalAxis horizontalAxis;
  SimpleChartVerticalAxis verticalAxis;
  SimpleChartAxisDefaults axisDefaults;
  com.gensym.classes.Chart g2Chart;
  SimpleChartDataSeries seriesDefaults;
  Vector chartDataSeries;

  SimpleChartStyle style;
  //
  // G2 attributes
  //
  Structure annotations;
  Symbol chartStyle;
  Structure defaultFeatures;
  Structure dataPointFeatures = new Structure();
  Structure seriesDefaultAnnotations;

  //
  // "computed" attributes
  //
  
  // if no data...
  boolean emptyChart = false;

  //
  // defaults (taken from charts1.lisp)
  //

  public SimpleChart(com.gensym.classes.Chart g2Chart)
  throws G2AccessException, NoSuchAttributeException {
    this.g2Chart = g2Chart;
    axisDefaults = new SimpleChartAxisDefaults(this);
    horizontalAxis = new SimpleChartHorizontalAxis(this, axisDefaults);
    verticalAxis = new SimpleChartVerticalAxis(this, axisDefaults);
    seriesDefaults = new SimpleChartDataSeries(this);
    configure();
  }

  private void configure() throws G2AccessException, NoSuchAttributeException {
    annotations = g2Chart.getAnnotations();
    if (annotations == null) {
      annotations = NULL_STRUCT;
    }
    defaultFeatures =
      (Structure)annotations.getAttributeValue(DEFAULT_FEATURES_, null);
    if (defaultFeatures == null) {
      defaultFeatures = NULL_STRUCT;
    }
    chartStyle = g2Chart.getChartStyle();
    style = new SimpleChartStyle(chartStyle);
    // fix this: don't really need to make new data series just because
    // the annotations change.
    Sequence chartDataSeriesData = g2Chart.getChartDataSeries();
    if (chartDataSeriesData == null) {
      emptyChart = true;
      return;
    } else {
      emptyChart = false;
      makeDataSeries(chartDataSeriesData);
    }
    // fix this: only really need to reconfigure data series on a data
    // change if there are new data series that haven't been configured.
    configureDataSeries();
    configureDataPoints();
    Trace.send(10, traceKey, i18nTrace, "scconfigure", annotations,
	       defaultFeatures, style, chartDataSeries);
    configureAxes();
    //computeAxisExtrema();
  }

  void configureDataPoints() {
    Sequence features =
      (Sequence)annotations.getAttributeValue(DATA_POINT_FEATURES_, null);
    if (features == null) {
      return;
    } else {
      Structure struct = (Structure)features.firstElement();
      features = (Sequence)struct.getAttributeValue(ANNOTATIONS_, null);
      if (features == null)
	return;
      Structure usefulAnnotations =
	findUsefulAnnotations(features);
      if (usefulAnnotations != null)
	dataPointFeatures = usefulAnnotations;
    }
  }

  /** See configureDataSeries for a discussion of indexing. data series
   * are given 1-based indices in this method. */
  private void makeDataSeries(Sequence chartDataSeriesData)
  throws NoSuchAttributeException {
    seriesDefaults = new SimpleChartDataSeries(this);
    int count = chartDataSeriesData.size();
    chartDataSeries = new Vector(count);
    int i = 1;

    // make them, with their initial data
    for (Enumeration en = chartDataSeriesData.elements();
	 en.hasMoreElements();) {
      Structure data = (Structure)en.nextElement();
      chartDataSeries.
	addElement(new SimpleChartDataSeries(this, data, new Integer(i++)));
    }
  }

  /** Right now, this method assumes that the data series are newly made.
   * If data series are ever reused, then care will have to be taken
   * to clear the annotations of existing data series in case old annotations
   * for a specific data series have been removed.
   * NOTE: the DATA-SERIES-FEATURES information from G2 comes with
   * index information that is "1 based" rather than "zero based".
   * The CHART-DATA-SERIES information that is associated with it
   * is just a sequence with no explicit "INDEX" tags.
   * As a result, care is needed to make sure things line up correctly
   * between the two.
   * The current implementation tries to hide all the associated rigamarole
   * in configureDataSeries.
   */
  private void configureDataSeries() {
    Sequence dataFeatures =
      (Sequence)annotations.getAttributeValue(DATA_SERIES_FEATURES_, null);
    if (dataFeatures == null) {
      setupDataSeriesColorPath();
      return;
    }
    int size = chartDataSeries.size();

    for (Enumeration en = dataFeatures.elements(); en.hasMoreElements();) {
      Structure annotations = (Structure)en.nextElement();
      Integer index = (Integer)annotations.getAttributeValue(INDEX_, null);
      SimpleChartDataSeries target = null;
      if (index == null) {
	target = seriesDefaults;
	seriesDefaultAnnotations = annotations;
      } else {
	int i = index.intValue();
	if (i <= size) {
	  target = (SimpleChartDataSeries)chartDataSeries.elementAt(i - 1);
	} else {
	  Message.
	    send(new MessageEvent(0, traceKey, i18nTrace,
				  "scirrelevantDataSeriesAnnotations",
				  new Object[]
				  {index, new Integer(size), annotations}));
	}
      }
      if (target != null){ // NOTE warning of irrelevant annotations sent above
	// fix this: should we continue if one of the data series has
	// a bad attribute? right now we will.
	try {
	  target.setAnnotations(annotations);
	} catch (NoSuchAttributeException nsae) {
	  Message.send(new MessageEvent(0, traceKey, i18nTrace,
					"scbadAnnotationsForDataSeries",
					new Object[]
					{this, index, annotations}));
	}
      }
    }
    setupDataSeriesColorPath();
  }
  
  private void setupDataSeriesColorPath() {
    int size = chartDataSeries.size();
    for (int i = 0; i < size; i++) {
      SimpleChartDataSeries target =
	(SimpleChartDataSeries)chartDataSeries.elementAt(i);
      target.setUpDataColorAnnotationPath();
    }
  }

  private void configureAxes() throws G2AccessException,
  NoSuchAttributeException {
    configureAxesAnnotations();
    configureAxesComputedDetails();
  }

  private static final Symbol AXIS_1_ = Symbol.intern ("AXIS-1");
  private static final Symbol AXIS_2_ = Symbol.intern ("AXIS-2");

  private void configureAxesComputedDetails() throws G2AccessException,
  NoSuchAttributeException {
    Structure computedAxisDetails = g2Chart.getChartAxisComputedDetails();
    if (computedAxisDetails != null) {
      horizontalAxis.setComputedDetails((Structure)computedAxisDetails.
					getAttributeValue(AXIS_1_));
      verticalAxis.setComputedDetails((Structure)computedAxisDetails.
				      getAttributeValue(AXIS_2_));
    }
  }    

  private void configureAxesAnnotations() {
    // clear all attributes first
    horizontalAxis.setAnnotations(null);
    verticalAxis.setAnnotations(null);
    axisDefaults.setAnnotations(null);
    
    Sequence axisFeatures =
      (Sequence)annotations.getAttributeValue(AXIS_FEATURES_, null);
    if (axisFeatures == null)
      return;

    SimpleChartAxis targetAxis = null;

    for (Enumeration en = axisFeatures.elements(); en.hasMoreElements();) {
      Structure features = (Structure)en.nextElement();
      Object index = features.getAttributeValue(INDEX_, null);
      if(index == null) {
	targetAxis = axisDefaults;
      } else if (index.equals(HORIZONTAL_INDEX)) {
	  targetAxis = horizontalAxis;
      } else if (index.equals(VERTICAL_INDEX)) {
	  targetAxis = verticalAxis;
      }
      if (targetAxis != null) {
	Sequence axisAnnotations =
	  (Sequence)features.getAttributeValue(ANNOTATIONS_, null);
	Structure axisAttributes = findUsefulAnnotations(axisAnnotations);
	Trace.send(5, traceKey, i18nTrace, "scconfigureAxes", index,
		   axisAnnotations, axisAttributes);
	targetAxis.setAnnotations(axisAttributes);
      }
    }
  }

  /** This is most applicable to AXIS-FEATURES, where any features structure
   * that includes a path is meaningless. */
  private Structure findUsefulAnnotations(Sequence sequence) {
    Trace.send(10, traceKey, i18nTrace, "scfindUsefulAnnotations", sequence);
    for (Enumeration en = sequence.elements(); en.hasMoreElements();) {
      Structure struct = (Structure)en.nextElement();
      if (struct.getAttributeValue(PATH_, null) == null)
	return (Structure)struct.getAttributeValue(ATTRIBUTES_, null);
    }
    return null;
  }

  private static final Object NOT_DOWNLOADED = new Object();

  /** This is the more general and correct way to abstract the means
   * of looking up an annotation. It makes the SimpleChartAxisDefaults
   * class and the this.seriesDefaults field superfluous.
   */
  static Object getDeclaredValueOfPart(Symbol name, Vector annotationPath,
				       Object defaultValue) {
    int size = annotationPath.size();

    for (int i = 0; i < size; i++) {
      Structure struct = (Structure)annotationPath.elementAt(i);
      Object value = struct.getAttributeValue(name, NOT_DOWNLOADED);
      if (value != NOT_DOWNLOADED)
	return value;
    }

    return defaultValue;
  }    

  Object getDeclaredValueOfPart(Symbol name, Structure sourceAnnotations,
				Structure defaultAnnotations){
    Trace.send(10, traceKey, i18nTrace, "scgetDeclaredValueOfPart",
	       name, sourceAnnotations, defaultAnnotations);
    Object returnValue = null;
    if (sourceAnnotations != null){
      Trace.send(10, traceKey, i18nTrace, "scgetDeclaredAnnotations",
		 "object", sourceAnnotations);
      if ((returnValue =
	   sourceAnnotations.getAttributeValue(name, null)) != null) {
	Trace.send(10, traceKey, i18nTrace, "scgetDeclaredReturnValue",
		 "object", returnValue);
	return returnValue;
      }
    }

    if (defaultAnnotations != null) {
      Trace.send(10, traceKey, i18nTrace, "scgetDeclaredAnnotations",
		 "default", defaultAnnotations);
      if ((returnValue =
	   defaultAnnotations.getAttributeValue(name, null)) != null) {
	Trace.send(10, traceKey, i18nTrace, "scgetDeclaredReturnValue",
		 "default", returnValue);
	return returnValue;
      }
    }
    
    if (defaultFeatures != null) {
      Trace.send(10, traceKey, i18nTrace, "scgetDeclaredAnnotations",
		 "default", defaultFeatures);
      return defaultFeatures.getAttributeValue(name, null);
    }

    return null;
  }

  Font getDeclaredFont() {
    return
      (defaultFeatures == null ?
       G2FontMap.HM14 :
       G2FontMap.get(defaultFeatures, TEXT_SIZE_, G2FontMap.HM14));
  }

  Color getLineColor(){
    if (defaultFeatures != null) {
      return G2ColorMap.get(defaultFeatures, LINE_COLOR_, Color.black);
    }
    return Color.black;
  }

  Color getTextColor() {
    if (defaultFeatures != null) {
      return G2ColorMap.get(defaultFeatures, TEXT_COLOR_, Color.black);
    }
    return Color.black;
  }

  Color getBackgroundColor() {
    return
      (defaultFeatures == null ?
       null :
       G2ColorMap.get(defaultFeatures, BACKGROUND_COLOR_, null));
  }

  Color getBorderColor() {
    return
      (defaultFeatures == null ?
       Color.black :
       G2ColorMap.get(defaultFeatures, BORDER_COLOR_, Color.black));
  }

  Color getGridColor() {
    return
      (defaultFeatures == null ?
       Color.black :
       G2ColorMap.get(defaultFeatures, GRID_COLOR_, Color.black));
  }

  boolean getGridVisible() {
    if (defaultFeatures != null) {
      Boolean value =
	(Boolean)defaultFeatures.getAttributeValue(GRID_VISIBLE_, null);
      if (value == null)
	return false;
      else
	return value.booleanValue();
    } else
      return false;
  }

  public void acknowledgeSlotChange(ItemEvent e)
  throws G2AccessException, NoSuchAttributeException {
    configure();
    repaintAll();
  }

  //
  // computed slots
  //

  private void computeMargins() {
  }

  int getTopMargin() {
    return topMargin;
  }

  int getBottomMargin() {
    return bottomMargin;
  }

  int getLeftMargin() {
    return leftMargin;
  }

  int getRightMargin() {
    return rightMargin;
  }

  //
  // computed slots
  //

  int hAxisVerticalPos, vAxisHorizontalPos;
  void computeAxisLocations() {
    int hAxisLeftAdjust = horizontalAxis.getLeftAdjust(),
      hAxisRightAdjust = horizontalAxis.getRightAdjust(),
      vAxisTopAdjust = verticalAxis.getTopAdjust(),
      vAxisBottomAdjust = verticalAxis.getBottomAdjust();
    
    double hAxisCrossover = horizontalAxis.getAxisCrossover(),
      hAxisMinimum = horizontalAxis.getAxisMinimum(),
      hAxisMaximum = horizontalAxis.getAxisMaximum(),
      vAxisCrossover = verticalAxis.getAxisCrossover(),
      vAxisMinimum = verticalAxis.getAxisMinimum(),
      vAxisMaximum = verticalAxis.getAxisMaximum();

    Dimension size = getSize();
    horizontalAxis.left = hAxisLeftAdjust + leftMargin;
    horizontalAxis.right = size.width - (hAxisRightAdjust + rightMargin);
    int hLeft = horizontalAxis.left;
    int hRight = horizontalAxis.right;

    verticalAxis.top = vAxisTopAdjust + topMargin;
    verticalAxis.bottom = size.height - (vAxisBottomAdjust + bottomMargin);
    int vTop = verticalAxis.top;
    int vBottom = verticalAxis.bottom;

    double vScale = (vBottom - vTop)/(vAxisMinimum - vAxisMaximum);
    int vOffset = vTop - (int)(vScale * vAxisMaximum);
    int horizontalAxisNeededLabelSpace =
      horizontalAxis.getNeededVerticalLabelSpace();
    int horizontalAxisY = vOffset + (int)(hAxisCrossover * vScale);

    if (size.height < horizontalAxisNeededLabelSpace)
      topMargin = bottomMargin = 0;

    if (horizontalAxisY > size.height -  horizontalAxisNeededLabelSpace &&
	!(vAxisMaximum - hAxisCrossover == 0.0 ||
	  size.height < horizontalAxisNeededLabelSpace)) {
      horizontalAxisY =
	size.height - (horizontalAxisNeededLabelSpace + bottomMargin);
      double newVBottom =
	(double)horizontalAxisY +
	(double)(vAxisMinimum - hAxisCrossover)*
	((double)(hRight - horizontalAxisY)/(vAxisMaximum - hAxisCrossover));
      verticalAxis.bottom = (int)newVBottom;
    }
    
    horizontalAxis.y = horizontalAxisY;
    //horizontalAxis.y = vBottom +
    //  (int)((vAxisMaximum - vAxisCrossover) * vScale);

    //horizontalAxis.setComputedValues(hLeft, hRight, y);
                       
    double hScale = (hRight - hLeft)/(hAxisMaximum - hAxisMinimum);
    int hOffset = hLeft - (int)(hScale * hAxisMinimum);
    int verticalAxisX = hOffset + (int)(vAxisCrossover * hScale);
    int verticalAxisMaxLabelWidth = verticalAxis.getMaxLabelWidth();
    if (size.width < verticalAxisMaxLabelWidth)
      rightMargin = leftMargin = 0;

    if (verticalAxisX < verticalAxisMaxLabelWidth &&
	!(hAxisMaximum - vAxisCrossover == 0.0 ||
	   size.width < verticalAxisMaxLabelWidth)) {
      verticalAxisX = verticalAxisMaxLabelWidth + leftMargin;
      double newHLeft =
	(double)verticalAxisX -
	(double)(vAxisCrossover - hAxisMinimum)*
	((double)(hRight - verticalAxisX)/(hAxisMaximum - vAxisCrossover));
      horizontalAxis.left = (int)newHLeft;
    }

    verticalAxis.x = verticalAxisX;

    Trace.send(5, traceKey, i18nTrace, "sccomputeHorizontal",
	       new Double(vAxisCrossover), new Double(hAxisMinimum),
	       new Double(hAxisMaximum), new Double(hScale));

    Trace.send(5, traceKey, i18nTrace, "sccomputeVertical",
	       new Double(hAxisCrossover), new Double(vAxisMinimum),
	       new Double(vAxisMaximum), new Double(vScale));

  }

  FontMetrics getFontMetrics() {
    // fix this: is it worth re-using a FontMetrics where possible?
    return getFontMetrics(getDeclaredFont());
  }

  SimpleChartStyle getStyle() {
    return style;
  }

  //
  // paint methods
  //

  private void drawEmptyChart(Graphics g) {
    Dimension size = getSize();
    g.setColor(getLineColor());
    int width = size.width;
    int height = size.height;

    int x = width/8;
    int xLength = width - x*2;
    int y = height - height/8;
    int yLength = height - y*2;

    g.drawLine(x, y, x, y + yLength);
    g.drawLine(x, y, x + xLength, y);
  }

  private boolean axesIncomplete() {
    return (verticalAxis.computedDetails == null ||
	    horizontalAxis.computedDetails == null);
  }

  @Override
  protected void localPaint(Graphics g) {
    Dimension size = getSize();
    Color backgroundColor = getBackgroundColor();
    if(backgroundColor != null){
      g.setColor(backgroundColor);
    } else {
      g.setColor(Color.white);
    }
    g.fillRect(0, 0, size.width, size.height);

    Color borderColor = getBorderColor();
    if(borderColor != null){
      g.setColor(borderColor);
      g.drawRect(0, 0, size.width - 1, size.height - 1);
    }

    if (emptyChart || axesIncomplete()) {
      drawEmptyChart(g);
      return;
    }

    computeAxisLocations();
    Trace.send(10, traceKey, i18nTrace, "sclocalPaint", g.getClipBounds(),
	       getBounds(), backgroundColor, borderColor);
    g.setColor(getLineColor());

    double horizontalTickInterval = horizontalAxis.getRealTickmarkInterval();
    double horizontalScale = horizontalAxis.getScale();
    double verticalTickInterval = verticalAxis.getRealTickmarkInterval();
    double verticalScale = verticalAxis.getScale();

    horizontalAxis.drawGrid(g, horizontalTickInterval, horizontalScale);
    verticalAxis.drawGrid(g, verticalTickInterval, verticalScale);
      
    if (chartDataSeries != null) {
      for (Enumeration en = chartDataSeries.elements(); en.hasMoreElements();){
	((SimpleChartDataSeries)en.nextElement()).draw(g);
      }
    }
    horizontalAxis.drawAxis(g);
    horizontalAxis.drawTickmarks(g, horizontalTickInterval, horizontalScale);
    horizontalAxis.drawLabels(g, horizontalTickInterval, horizontalScale);
    verticalAxis.drawAxis(g);
    verticalAxis.drawTickmarks(g, verticalTickInterval, verticalScale);
    verticalAxis.drawLabels(g, verticalTickInterval, verticalScale);
    g.setColor(getLineColor());
    containerPaint(g);
  }

}
