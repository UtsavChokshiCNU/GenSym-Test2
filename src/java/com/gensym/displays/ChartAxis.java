/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ChartAxis.java
 *
 *  Description:
 *               Axis information
 *
 *	 Author:
 *		Robert Penny		Aug/97
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.displays;

import java.awt.*;
import java.util.*;
import java.io.Serializable;

import com.gensym.ntw.util.G2ColorMap;
import com.gensym.util.*;
import com.gensym.util.Set;
import com.gensym.message.*;

// OPTIMIZATIONS:
// 1. Store transformation information and have it invalidated
//    when the data-window moves or is resized, rather than always
//    calculating it.

/** An axis against which to draw a Plot.
 * <p>
 * NOTE: You must use one of <code>ChartAxis.HORIZONTAL</code> or
 * <code>ChartAxis.VERTICAL</code>.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 *@see com.gensym.displays.Plot */

public class ChartAxis implements Serializable, ChartElement{
  private static Resource i18n =
  Trace.getBundle("com.gensym.displays.Messages");
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.TraceMessages");
  private static MessageKey traceKey = 
  Trace.registerMessageKey("com.gensym.displays", ChartAxis.class);
  // There seems to be a problem with intern() on Netscape.
  public static final String HORIZONTAL =
  //"HORIZONTAL";
  (new String("HORIZONTAL")).intern();
  public static final String VERTICAL =
  //"VERTICAL";
  "VERTICAL".intern();

  Color gridLineColor;
  Boolean gridLinesVisible;
  Color labelColor;
  Boolean labelsVisible;
  Set names = new Set();

  private double maximum = Double.MAX_VALUE;
  private double minimum = - Double.MAX_VALUE;
  private Object orientation;
  private boolean valid = false;
  boolean horizontal;
  private double dataOrigin;

  protected DataWindow dataWindow;

  public ChartAxis(Object chartElementUid) {
    this.chartElementUid = chartElementUid;
  }

  private Object chartElementUid;
  @Override
  public Object getChartElementUid() {
    return chartElementUid;
  }

  public ChartAxis(DataWindow dataWindow, Object orientation) {
    setOrientation(orientation);    
    this.dataWindow = dataWindow;
  }

  @Override
  public void configure(Chart chart) {
    if (dataWindow == null)
      dataWindow = chart.getDataWindow();
  }

  @Override
  public void dispose() {
  }

  protected void setOrientation(Object orientation) {
    if(!(HORIZONTAL.equals(orientation) || VERTICAL.equals(orientation)))
      throw new IllegalArgumentException();
    this.orientation = orientation;
    horizontal = (HORIZONTAL.equals(orientation));
  }

  public boolean getHorizontal() {
    return horizontal;
  }

  public void setDataOrigin(double newOrigin) {
    dataOrigin = newOrigin;
  }

  /** This is the data value for the device co-ordinate 0. */
  public double getDataOrigin() {
    return dataOrigin;
  }
  
  private double visibleDataMinimum;
  private double visibleDataMaximum;
  private double visibleDataRange;
  private double scale;

  public double getVisibleDataMinimum() {
    return visibleDataMinimum;
  }

  public double getVisibleDataMaximum() {
    return visibleDataMaximum;
  }

  public synchronized void setVisibleDataRange(double visibleDataMinimum,
					       double visibleDataMaximum)
  {
    this.visibleDataMinimum = visibleDataMinimum;
    this.visibleDataMaximum = visibleDataMaximum;
    rescale();
  }

  /** Returns what the new scale would be for the
   * <code>trialDeviceRange</code>.
   */
  protected double makeScale(int trialDeviceRange) {
    return ((double)trialDeviceRange)/visibleDataRange;
  }

  /** This must be called whenever the visible data bounds of the axis changes
   * or the device size of the DataWindow changes */
  public synchronized double rescale() {
    visibleDataRange = visibleDataMaximum - visibleDataMinimum;
    Rectangle bounds = dataWindow.getBounds();
    int deviceRange = (horizontal ?
		       bounds.width : bounds.height);
    scale = ((double)deviceRange)/visibleDataRange;
    //Thread.dumpStack();
    Trace.send(10, traceKey, i18nTrace, "caRescale",
	       new Double(visibleDataMinimum),
	       new Double(visibleDataMaximum),
	       bounds,
	       new Double(scale));
    return scale;
  }

  public synchronized double getScale() {
    //return scale;
    Dimension size = dataWindow.getSize();
    double range = visibleDataMaximum - visibleDataMinimum;
    return ((horizontal ? size.width : size.height)/range);
  }    

  /** Assumes that the DataWindow bounds have been set to the new
   * bounds already. Also assumes that the viewBounds and 
   * logicalBounds of the dataWindow are identical and need no adjusting.
   * subclasses for which this is not true along their axis must deal with
   * this complication themselves.
   */
  public synchronized void adjustBounds(Rectangle oldBounds) {
    rescale();
  }
  
  public synchronized void setMinimum(double minimum) {
    this.minimum = minimum;
    valid = false;
  }

  public synchronized double getMinimum() {
    return minimum;
  }
    
  public void setMaximum(double maximum) {
    this.maximum = maximum;
    valid = false;
  }

  public double getMaximum() {
    return maximum;
  }

  public int scale(double value) {
    return (int)Math.floor(value*scale);
  }

  /** adaptor method for G2 */
  public void setNames(Symbol name) {
    names.add(name);
  }

  public void setNames(Set names) {
    names.union(names.elements());
  }

  @Override
  public Enumeration getNames() {
    return names.elements();
  }

  /** adaptor method for G2 */
  public void setGridLineColor(Symbol gridLineColor) {
    this.gridLineColor = G2ColorMap.get(gridLineColor);
  }

  /** adaptor method for G2 */
  public void setGridLineColor(Structure gridLineColor) {
    this.gridLineColor = G2ColorMap.get(gridLineColor, COLOR_, null);
  }

  public void setGridLineColor(Color gridLineColor) {
    this.gridLineColor = gridLineColor;
  }

  public Color getGridLineColor() {
    return gridLineColor;
  }

  public synchronized void setGridLinesVisible(boolean gridLinesVisible) {
    this.gridLinesVisible = new Boolean(gridLinesVisible);
  }

  public boolean getGridLinesVisible() {
    return gridLinesVisible.booleanValue();
  }

  protected static final Symbol COLOR_ = Symbol.intern ("COLOR");

  /** Adaptor Method for G2 */
  public void setLabelColor(Structure labelColor) {
    this.labelColor = G2ColorMap.get(labelColor, COLOR_, null);
  }

  /** Adaptor Method for G2 */
  public void setLabelColor(Symbol labelColor) {
    this.labelColor = G2ColorMap.get(labelColor);
  }

  public void setLabelColor(Color labelColor) {
    this.labelColor = labelColor;
  }

  public Color getLabelColor() {
    return labelColor;
  }

  public void setLabelsVisible(boolean labelsVisible) {
    if (labelsVisible)
      this.labelsVisible = Boolean.TRUE;
    else
      this.labelsVisible = Boolean.FALSE;
  }

  public boolean getLabelsVisible() {
    return labelsVisible.booleanValue();
  }

  /** Translates the abstract value into a value in device space,
  * based on the <code>dataWindow</code> */
  public synchronized int transform(double value) throws OutOfBoundsException {
    double min = visibleDataMinimum,
      max = visibleDataMaximum,
      dataRange = visibleDataRange;
    Trace.send(15, traceKey, i18n, "transform", new Double(min),
	       new Double(max), orientation, this);
    if (value < minimum) 
      throw new OutOfBoundsException(value, minimum);
    if (value > maximum)
      throw new OutOfBoundsException(value, maximum);
    
    Rectangle bounds = dataWindow.getBounds();

    //    double logicalRange = max - min;
    int deviceTranslate = (horizontal ?
			   bounds.x : bounds.y);
    // since y values start at 0 at the top
    int returnVal = (horizontal ?
		     (int)Math.floor((value - dataOrigin) * scale) +
		     deviceTranslate :
		     (int)Math.floor((dataOrigin - value) * scale) +
		     deviceTranslate);

    Trace.send(5, traceKey, i18n, "transform2",
	       new Double(value), new Integer(returnVal),
	       new Double(scale),
	       bounds);
    Trace.send(5, traceKey, i18n, "transform3",
	       new Double(dataOrigin),
	       dataWindow.getBounds());

    return returnVal;
  }

  @Override
  public String toString() {
    return super.toString() + " Uid:" + chartElementUid + " names:" + names;
  }
}
