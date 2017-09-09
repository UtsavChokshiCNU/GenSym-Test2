/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      MarkerFormat.java
 *
 * Description:
 *
 *      Author:
 *
 * Modifications:
 *
 */
package com.gensym.displays;

import java.awt.*;
import java.util.Locale;
import java.util.Enumeration;
import java.io.Serializable;
import java.text.NumberFormat;
import com.gensym.ntw.util.G2ColorMap;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.classes.G2Definition;
import com.gensym.jgi.G2AccessException;
import com.gensym.icons.IconDescription;
import com.gensym.util.ScientificDecimalFormat;
import com.gensym.irm.IconRendering;

/** Corresponds to the point-format of a G2 trend chart.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */

public class MarkerFormat implements Serializable, ChartElement,
com.gensym.util.symbol.TrendChartSymbols{

  static final int DEFAULT_MARKER_FREQUENCY = 1;
  static final Integer DEFAULT_MARKER_FREQUENCY_OBJ =
  new Integer(DEFAULT_MARKER_FREQUENCY);

  public static boolean traceOn = false;
  static Resource i18n =
  Trace.getBundle("com.gensym.displays.Messages");
  static Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.TraceMessages");
  static MessageKey traceKey = 
  Trace.registerMessageKey("com.gensym.displays", MarkerFormat.class);
  Integer markerFrequency;
  Structure markerStyle;
  Color markerColor;
  Symbol markerColorName;
  Boolean markersVisible;
  Set names = new Set();
  private TrendChart chart;
  DefaultMarkerFormat defaultMarkerFormat;

  public MarkerFormat(TrendChart chart,
		      com.gensym.classes.TrendChart g2TrendChart,
		      Object chartElementUid) {
    super();
    this.chartElementUid = chartElementUid;
    this.chart = chart;
    defaultMarkerFormat = chart.getDefaultMarkerFormat();
  }

  private Object chartElementUid;
  @Override
  public Object getChartElementUid() {
    return chartElementUid;
  }

  @Override
  public void configure(Chart chart) {
  }

  @Override
  public void dispose() {
    chart.removeMarkerFormat(this);
  }
  
  /** This is an "adapter" method for compatibility with G2 */
  public void setMarkerFrequency(Structure markerFrequency) {
    this.markerFrequency =
      (Integer)markerFrequency.getAttributeValue(POINTS_PER_MARKER_, null);
  }

  public void setMarkerFrequency(int markerFrequency) {
    this.markerFrequency = new Integer(markerFrequency);
  }

  public int getMarkerFrequency() {
    if (markerFrequency == null) {
      return defaultMarkerFormat.getMarkerFrequency();
    } else {
    return markerFrequency.intValue();
    }
  }

  public void setMarkerStyle(Structure markerStyle) {
    this.markerStyle = markerStyle;
    chart.resetLegendText(this);
    invalidateIcon();
  }

  public Structure getMarkerStyle() {
    if (markerStyle == null) {
      return defaultMarkerFormat.getMarkerStyle();
    } else {
      return markerStyle;
    }
  }

  Symbol getMarkerShapeSym() {
    Structure style = getMarkerStyle();
    if (style == null)
      return null;

    Symbol shape = (Symbol)style.getAttributeValue(STANDARD_SHAPE_, null);
    if (shape == null) {
      shape = (Symbol)style.getAttributeValue(ICON_OF_CLASS_, null);
    }
    return shape;
  }


  String getMarkerShape() {
    Symbol shape = getMarkerShapeSym();

    if (shape != null) {
      return shape.getPrintValue().toLowerCase();
    }
    return null;
  }

  Symbol getMarkerType() {
    Structure style = getMarkerStyle();
    Enumeration en = style.getAttributeNames();
    if (en.hasMoreElements())
      return (Symbol)en.nextElement();
    return null;
  }

  /** This string is used for displaying the marker shape to the
   * users, not for progromatic purposes.
   */
  String makeMarkerString() {
    if (!getMarkersVisible())
      return null;

    String markerShape = getMarkerShape();
    Symbol markerType = getMarkerType();

    if (STANDARD_SHAPE_.equals(markerType)) {
      return i18n.format("mfStandardMarkerType", markerShape);
    } else if (ICON_OF_CLASS_.equals(markerType)) {
      return i18n.format("mfIconMarkerType", markerShape);
    } else
      return null;
  }      
    
  public void setMarkerColor(Symbol markerColorName) {
    this.markerColorName = markerColorName;
    markerColor = G2ColorMap.get(markerColorName);
    changeIconColor(markerColor);
    chart.resetLegendText(this);
  }

  public Color getMarkerColor() {
    Symbol colorName = getMarkerColorName();
    return (colorName == null ? Color.black : G2ColorMap.get(colorName));
  }

  Symbol getMarkerColorName() {
    if (markerColorName == null) {
      return defaultMarkerFormat.getMarkerColorName();
    } else {
      return markerColorName;
    }
  }

  public void setMarkersVisible(boolean markersVisible) {
    this.markersVisible = new Boolean(markersVisible);
    chart.resetLegendText(this);
  }

  public boolean getMarkersVisible() {
    if (markersVisible == null) {
      return defaultMarkerFormat.getMarkersVisible();
    } else {
      return markersVisible.booleanValue();
    }
  }

  public void setNames(Set names) {
    this.names = names;
  }

  @Override
  public Enumeration getNames() {
    return names.elements();
  }

  /** This is an "adapter" method for compatibility with G2 */
  public void setNames(Symbol name) {
    names.add(name);
  }

  /** This is an "adapter" method for compatibility with G2 */
  public void setNames(Sequence names) {
   for(Enumeration en = names.elements(); en.hasMoreElements();)
     this.names.add(en.nextElement());
  }

  boolean isShowingCurrentValue() {
    return CURRENT_VALUE_.equals(getMarkerShapeSym());
  }

  private final int calculateStartIndex(int markerFrequency, int indexFactor,
					int historyStartIndex) {
    int mod = (historyStartIndex % markerFrequency);
    if (traceOn) {
      Trace.send(10, traceKey, i18nTrace, "mfcalculateStartIndex",
		 new Integer(markerFrequency), new Integer(indexFactor),
		 new Integer(historyStartIndex),
		 new Integer(mod));
    }
    return mod == 0 ? 0 : (markerFrequency - mod)*indexFactor;
  }    

  /** @param indexFactor reflects how many buffer indices reflect
   * the same underlying data point (the xbuf and ybuf are currently
   * shared with the ConnectorFormat, which places its own special
   * requirements on these buffers).
   * @param historyStartIndex a number used for modulo arithmetic to get
   * markers to paint on the same point they would in G2.
   */
  void drawMarkers(Graphics g, int indexFactor, int count,
		   int historyStartIndex,
		   int[] xbuf, int[] ybuf,
		   double[] markerValues) {
    if(!getMarkersVisible())
      return;
    g.setColor(getMarkerColor());
    int frequency = getMarkerFrequency() * indexFactor;
    int startIndex =
      calculateStartIndex(getMarkerFrequency(), indexFactor, historyStartIndex);
    int width = 10;
    int height = 10;
    int wLeft = width/2;
    int wRight = width - wLeft;
    int hTop = height/2;
    int hBottom = height - hTop;
    Symbol indicator = getMarkerShapeSym();

    if (SQUARE_.equals(indicator)) {
      drawSquares(g, frequency, count, startIndex,
		  xbuf, ybuf, wLeft, width, hTop, height);
    } else if (PLUS_SIGN_.equals(indicator)) {
      drawPlusSigns(g, frequency, count, startIndex,
		  xbuf, ybuf, wLeft, width,
		    hTop, height);
    } else if (TRIANGLE_.equals(indicator)) {
      drawTriangles(g, frequency, count, startIndex,
		  xbuf, ybuf, wLeft, wRight, hTop, hBottom);
    } else if (CURRENT_VALUE_.equals(indicator)) {
      drawCurrentValues(g, frequency, count, startIndex,
			xbuf, ybuf, markerValues);
    } else if (ICON_OF_CLASS_.equals(getMarkerType())) {
      drawIcons(g, frequency, count, startIndex,
		  xbuf, ybuf);
    } else {
      System.out.println("Unknown marker format: " + indicator);
    }
  }

  private static int PLUS_SIGN_WEIGHT = 3;

  void drawPlusSigns(Graphics g, int frequency, int count, int startIndex,
		     int[] xbuf, int[] ybuf,
		     int wLeft, int width, int hTop, int height) {
    for (int i = startIndex; ; i+= frequency) {
      if (i >= count)
	return;
      int adjust = PLUS_SIGN_WEIGHT/2;
      int x = xbuf[i], y = ybuf[i];
      g.fillRect(x - wLeft, y - adjust , width, PLUS_SIGN_WEIGHT);
      g.fillRect(x - adjust, y - hTop, PLUS_SIGN_WEIGHT, height);
    }
  }

  private NumberFormat numberFormat;
  
  private NumberFormat getNumberFormat() {
    if (numberFormat == null)
      numberFormat = new ScientificDecimalFormat();
    return numberFormat;
  }

  void drawCurrentValues(Graphics g, int frequency, int count, int startIndex,
			 int[] xbuf, int[] ybuf, double[] markerValues) {
    NumberFormat numberFormat = getNumberFormat();
    int valueIndex = 0;
    numberFormat = getNumberFormat();
    FontMetrics metrics = g.getFontMetrics(g.getFont());
    int heightAdjustment = metrics.getHeight()/2;
    for (int i = startIndex; ; i+= frequency) {
      if (i >= count)
	return;
      double value = markerValues[valueIndex];
      String valueString = numberFormat.format(value);
      int width = metrics.stringWidth(valueString);
      int x = xbuf[i] - width/2;
      int y = ybuf[i] + heightAdjustment;
      g.drawString(valueString, x, y);
      valueIndex++;
    }      
  }

  private int imageHorizontalOffset, imageVerticalOffset;
  private IconDescription iconDescription;

  /** returns a new IconDescription and sets values for
   * imageHorizontalOffset and imageVerticalOffset.
   */
  private IconDescription getIconDescription() {
    if (iconDescription != null)
      return iconDescription;
    try {
      Symbol className = getMarkerShapeSym();
      Structure iconDescStruct = chart.getIcon(className);

      iconDescription = new IconDescription(iconDescStruct);
      // Polychrome icons don't draw at all in G2, so we might
      // as well draw them correctly here, since we have the
      // chance to do so easily
      iconDescription.setLayerColors(getMarkerColor(), true);
      imageHorizontalOffset = iconDescription.getWidth()/2;
      imageVerticalOffset = iconDescription.getHeight()/2;
      return iconDescription;
    } catch (G2AccessException g2ae) {
      throw new UnexpectedException(g2ae);
    }
  }

  private void changeIconColor(Color color) {
    if (iconDescription != null) {
      // this will cause a new IconRendering to be made the
      // next time one is needed.
      storedRendering = null;  
      iconDescription.setLayerColors(color, true);
    }
  }

  private void invalidateIcon() {
    iconDescription = null;
    storedRendering = null;
  }

  private IconRendering storedRendering;
  private IconRendering getIconRendering() {
    if (storedRendering != null)
      return storedRendering;
    
    IconDescription desc = getIconDescription();
    storedRendering =
      new MarkerFormatIconRendering(desc);
    return storedRendering;
  }    
  
  void drawIcons(Graphics g, int frequency, int count, int startIndex,
		 int[] xbuf, int[] ybuf) {
    int leftOffset = imageHorizontalOffset;
    int topOffset = imageVerticalOffset;
    IconRendering rendering = getIconRendering();
    for (int i = startIndex; ; i+= frequency) {
      if (i >= count)
	return;
      rendering.Draw(g, xbuf[i] - imageHorizontalOffset,
		     ybuf[i] - imageVerticalOffset);
    }
  }

  void drawSquares(Graphics g, int frequency, int count,  int startIndex,
		   int[] xbuf, int[] ybuf,
		   int wLeft, int width, int hTop, int height) {
    int length = xbuf.length;
    for (int i = startIndex; ; i+= frequency) {
      if (i >= count)
	return;
      g.fillRect(xbuf[i] - wLeft, ybuf[i] - hTop,
		 width, height);
    }
  }

  int triangleX[] = new int[3];
  int triangleY[] = new int[3];

  void drawTriangles(Graphics g, int frequency, int count, int startIndex,
		     int[] xbuf, int[] ybuf,
		     int wLeft, int wRight, int hTop, int hBottom){
    Trace.send(30, traceKey, i18nTrace, "mfdrawTriangles", this,
	       new Integer(frequency), markerFrequency);
    //    System.out.println("Marker Frequency: " + frequency);
    int length = xbuf.length;
    for (int i = startIndex; ; i+= frequency) {
      if (i >= count)
	return;
      int x = xbuf[i];
      int y = ybuf[i];

      triangleX[0] = x - wLeft;
      triangleX[1] = x;
      triangleX[2] = x + wRight;

      triangleY[0] = y + hBottom;
      triangleY[1] = y - hTop;
      triangleY[2] = y + hBottom;

      g.fillPolygon(triangleX, triangleY, 3);
    }
  }
}
