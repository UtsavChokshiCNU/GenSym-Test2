/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ChartPath.java
 *
 *  Description:
 *               A collection of the straight lines that make up
 *               the (line) drawing of a set of chart data.
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
import com.gensym.draw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.ChartHistoryBuffer;

/** A collection of points in both real and display units. A purely visual
 * representation.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */
public class ChartPath extends BasicDrawElement {

  public static boolean traceOn = false;
  private static Resource i18n =
  Trace.getBundle("com.gensym.displays.Messages");
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.TraceMessages");
  private static MessageKey traceKey = 
  Trace.registerMessageKey("com.gensym.displays", ChartPath.class);
  // data kept in device units 

  private Color color = Color.black;
  private int width; // in pixels!!!

  private TrendChart chart;
  TrendChartPlot plot;

  int[] xbuf, ybuf;

  ChartPath(TrendChartPlot plot) {
    this.plot = plot;
    chart = (TrendChart)plot.getTrendChart();
    setVisible(true);
    chart.dataWindow.add(this, 0);
  }

  public void setLineColor(Color newColor) {
    if(newColor.equals(color))
      return;

    color = newColor;
    invalidate();
  }

  @Override
  public void invalidate() {
    super.invalidate();
  }

  /** 
   * @param newWidth width in pixels */
  public void setLineWidth(int newWidth) {
    width = newWidth;
  }

  // hack! should only need two extra points (for connector
  // shading targets), but sometimes the elementCount is off
  // by one, resulting in the need for two extra points
  private static final int BUFFER_FUDGE = 4;

  private double[] markerValues;

  /** Configures the device buffers to be of an appropriate size,
   * according to the specified start and end times.
   * If the plot is showing "current value" as a plot marker, then
   * make one additional buffer that will hold the actual
   * values, since otherwise the relationship between the visible point
   * and the value at that point are hidden within the ChartHistoryBuffer
   * and not easily accessible at paint time.
   * Making additional buffers for this is not terribly expensive,
   * because if there are too many points, "current value" is
   * a pretty useless plot marker.
   * @returns the indexFactor: the number of indices that will
   * be needed for a single data point.
   */
  int configureBuffers(long startTime, long endTime,
		       boolean collectMarkerValues,
		       int markerFrequency) {
    int elementCount = plot.getHistory().elementCount(startTime, endTime);
    int bufferFactor = plot.connectorFormat.getBufferSizeFactor();
    int bufferSize = elementCount*bufferFactor + BUFFER_FUDGE;
    if (collectMarkerValues) {
      int markerBufferSize =
	elementCount/markerFrequency + BUFFER_FUDGE;
      markerValues = new double[markerBufferSize];
    } else
      markerValues = null;
      
    if (traceOn) {
      Trace.send(10, traceKey, i18nTrace, "tcp_configureBuffers",
		 new Integer(elementCount), new Integer(bufferFactor),
		 new Long(startTime), new Long(endTime));
    }

    if (xbuf == null || xbuf.length < bufferSize) {
      xbuf = new int[bufferSize];
      ybuf = new int[bufferSize];
    }
    return bufferFactor;
  }

  @Override
  public void paint(Graphics g) {
    Trace.send(5, traceKey, i18nTrace, "cpPaint", g, getBounds(),
	       chart.dataWindow.getBounds(), chart.dataWindow.getBounds());
    Trace.send(10, traceKey, i18nTrace, "boundsClip",
	       this, g.getClipBounds(), getBounds());

    // fix this: 1. review the locking (need to lock markers too?
    // or better to designate a more central lock object);
    synchronized(plot) {
      synchronized (plot.connectorFormat) {
	ConnectorFormat connectorFormat = plot.connectorFormat;
	boolean connectorsVisible =
	  connectorFormat.getConnectorsVisible();

	MarkerFormat markerFormat = plot.markerFormat;
	boolean markersVisible = markerFormat.getMarkersVisible();
	int markerFrequency = markerFormat.getMarkerFrequency();

	if (!connectorsVisible && !markersVisible)
	  return;
	
	TimeAxis timeAxis = chart.timeAxis;
	ChartAxis valueAxis = plot.valueAxis;
	DataWindow dataWindow = chart.dataWindow;
	Point windowLocation = dataWindow.getLocation();
	long timeOffset = (long)timeAxis.getDataOrigin();
	double timeScale = timeAxis.getScale();
	
	double valueOffset = valueAxis.getDataOrigin();
	double valueScale = valueAxis.getScale();
	int windowLeft = windowLocation.x;
	int windowTop = windowLocation.y;

	Rectangle clip = g.getClipBounds();
	int startX = clip.x;
	int endX = startX + clip.width;
	long startTime =
	  (long)MathUtils.floor(startX - windowLeft, timeScale) + timeOffset;
 	long endTime =
 	  (long)MathUtils.floor(endX - windowLeft, timeScale) + timeOffset;
	if (traceOn) {
	  Trace.send(20, traceKey, i18nTrace, "cpTimeScales",
		     clip, windowLocation, new Long(timeOffset),
		     new Double(timeScale));
	  Trace.send(20, traceKey, i18nTrace, "cpTranslatedTime",
		     new Integer(startX), new Integer(endX),
		     new Long(startTime), new Long(endTime));
	}
	ChartHistoryBuffer history = plot.getHistory();
	if (history == null)
	  return;
	int indexFactor = connectorFormat.getIndexFactor();
	int count, start;
 	boolean collectMarkerValues =
 	  (markersVisible && markerFormat.isShowingCurrentValue());

	Point point;
	synchronized (history) {
	  configureBuffers(startTime, endTime, collectMarkerValues,
			   markerFrequency);
	  point = history.transform(startTime, endTime,
				    indexFactor,
				    xbuf, timeScale, timeOffset, windowLeft,
				    ybuf, valueScale, valueOffset, windowTop,
				    markerFrequency, markerValues);
	}

	if (point == null)
	  return;

	count = point.x;
	start = point.y;

	boolean extendPlot =
	  timeAxis.isEndTimeCurrent() &&
	  (connectorFormat.getConnectorInterpolation() !=
	   ConnectorFormat.LINEAR);

 	if(extendPlot) {
 	  xbuf[count] = 
	    (int)Math.floor((chart.getCurrentTime() - timeOffset) *
			    timeScale) + windowLeft;
	  //chart.getCurrentTime()*timeScale + timeOffset;
	  ybuf[count] = ybuf[count - 1];
	  count++;

	  if (traceOn) {
	    System.out.println("clipEndTime=" + endTime +
			       ";chart=" + chart.getCurrentTime());
	  }
	}

	// hack: fix this: in cases where fill, or thick lines are being
	// drawn, care must be taken no to re-use the xbuf and ybuf
	// from here. For now, we are drawing the plot markers *behind*
	// the connectors, to simplify.
	if (markersVisible)
	  plot.getMarkerFormat().drawMarkers(g, indexFactor, count, start,
					     xbuf, ybuf, markerValues);
	if (connectorsVisible)
	  connectorFormat.drawConnectors(g, plot, history, count, xbuf, ybuf);
      }
    }
  }
}
    
