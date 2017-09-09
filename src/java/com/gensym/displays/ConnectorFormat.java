/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      ConnectorFormat.java
 *
 * Description:
 *               A repository of connector information that aids a
 *               ChartPath in laying out its segments.
 *
 *      Author:
 *		Robert Penny		Aug/97
 *
 * Modifications:
 *
 */
package com.gensym.displays;

import java.awt.*;
import java.util.*;
import java.io.Serializable;

import com.gensym.ntw.util.G2ColorMap;
import com.gensym.util.*;
import com.gensym.core.DebugUtil;
import com.gensym.message.*;
import com.gensym.draw.LineElement;
import com.gensym.util.Set;
import com.gensym.util.symbol.TrendChartSymbols;
import com.gensym.ntw.util.ChartHistoryBuffer;

/** Corresponds to the connector-format in a G2 trend chart. Describes the
 * attributes of connectors and how to draw them.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */

public class ConnectorFormat implements Serializable, ChartElement,
TrendChartSymbols {

  // connector interpolation
  public static final int LINEAR = 1;
  public static final int SAMPLE_AND_HOLD = 2;
  public static final int SAMPLE_AND_HOLD_WITHOUT_RISERS = 3;

  static final Integer LINEAR_OBJ =
  new Integer(LINEAR);
  static final Integer SAMPLE_AND_HOLD_OBJ =
  new Integer(SAMPLE_AND_HOLD);
  static final Integer SAMPLE_AND_HOLD_WITHOUT_RISERS_OBJ =
  new Integer(SAMPLE_AND_HOLD_WITHOUT_RISERS);

  // shading targets
  public static final int NONE = 4;
  public static final int TOP = 5;
  public static final int BOTTOM = 6;

  static final Integer NONE_OBJ = new Integer(NONE);
  static final Integer TOP_OBJ = new Integer(TOP);
  static final Integer BOTTOM_OBJ = new Integer(BOTTOM);

  public static boolean traceOn = false;
  static Resource i18n =
  Trace.getBundle("com.gensym.displays.Messages");
  static Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.TraceMessages");
  static MessageKey traceKey = 
  Trace.registerMessageKey("com.gensym.displays", ConnectorFormat.class);
  Integer connectorLineWidth;
  Integer connectorInterpolation;
  Integer connectorShadingTarget = null;
  Color connectorLineColor = null;
  Symbol connectorLineColorName;
  Boolean connectorsVisible = null;
  Set names = new Set();
  int number;

  DefaultConnectorFormat defaultConnectorFormat;

  boolean configured = false;
  Set paths = new Set();
  // change this: should be LineChart
  TrendChart chart;

  public ConnectorFormat(TrendChart chart, 
			 com.gensym.classes.TrendChart g2TrendChart,
			 Object chartElementUid) {
    this.chartElementUid = chartElementUid;
    this.chart = chart;
    defaultConnectorFormat = this.chart.getDefaultConnectorFormat();
    configured = true;
  }

  Object chartElementUid;
  @Override
  public Object getChartElementUid() {
    return chartElementUid;
  }

  @Override
  public void configure(Chart chart) {
  }

  @Override
  public void dispose() {
    chart.removeConnectorFormat(this);
  }

  /** The factor by which to multiply the number of data points
   * in order to get the size of the buffer needed to display those
   * points.
   */
  int getBufferSizeFactor() {
    int lineWidth = getConnectorLineWidth();
    int interpolation = getConnectorInterpolation();
    int factor = 1;
    if (lineWidth > 1)
      factor *= 2;
    if (!(interpolation == LINEAR))
      factor *= 2;

    return factor;
  }

  int getIndexFactor() {
    if (getConnectorInterpolation() == LINEAR)
      return 1;
    else
      return 2;
  }

  public void addChartPath(ChartPath path) {
    path.setLineColor(getConnectorLineColor());
    path.setLineWidth(getConnectorLineWidth());
    
    paths.add(path);
  }

  private int adjustPolyForShading(int count, int[] xbuf, int[] ybuf,
				   int shadingTarget, DataWindow dataWindow) {
    Dimension size = dataWindow.getSize();
    int target;

    xbuf[count] = xbuf[count - 1];
    xbuf[count + 1] = xbuf[0];

    if (BOTTOM == shadingTarget) {
      target = size.height;
    }
    else
      target = 0;

    ybuf[count] = ybuf[count + 1] = target;

    return count +2;
  }

  private int adjustPolyForLineWidth(int count,
				     int[] xbufSource, int[] xbufTarget,
				     int[] ybufSource, int[] ybufTarget,
				     int lineWidth) {
    int plus = lineWidth/2;
    int minus = lineWidth - plus;
    int newCount = count*2;
    int end = newCount - 1;
      
    for (int i = 0; i < count; i++, end-- ) {
      int yHigh = ybufSource[i] + plus;
      ybufTarget[i] = yHigh;
      ybufTarget[end] = yHigh - lineWidth;

      xbufTarget[i] = xbufTarget[end] = xbufSource[i];
    }

    return newCount;
  }

  int adjustPolyForSampleAndHold(int count,
				 int[] xbufSource, int[] xbufTarget,
				 int[] ybufSource, int[] ybufTarget) {
    for (int i = 0; i < count - 2; i += 2) {
      xbufTarget[i] = xbufSource[i];
      xbufTarget[i + 1] = xbufSource[i + 2];

      ybufTarget[i] = ybufSource[i];
      ybufTarget[i + 1] = ybufSource[i];
    }
    return count;
  }

  /** The differing connector interpolations, shading targets,
   * and line-widths are all achieved via massaging the
   * integer buffers that are passed in. Once the buffers are
   * massaged, then {draw/fill}Poly{Line/gon} is called with
   * the massaged buffers to achieve the desired paint.
   */
  void drawConnectors(Graphics g, TrendChartPlot plot,
		      ChartHistoryBuffer history,
		      int count, int[] xbuf, int[] ybuf) {
    if (!getConnectorsVisible())
      return;
    TimeAxis timeAxis = plot.timeAxis;
    ChartAxis valueAxis = plot.valueAxis;
    DataWindow dataWindow = plot.dataWindow;
    int shadingTarget = getConnectorShadingTarget();
    int lineWidth = getConnectorLineWidth();
    int interpolation = getConnectorInterpolation();

    boolean fill = false;
    g.setColor(getConnectorLineColor());

    if (traceOn) {
      Trace.send(10, traceKey, i18nTrace, "cfarraysBeforeTransformations",
		 new Integer(count),
		 DebugUtil.printArray(xbuf, 0, count +2),
		 DebugUtil.printArray(ybuf, 0, count +2));
    }

    if (!(LINEAR == interpolation)) {
      count = adjustPolyForSampleAndHold(count, xbuf, xbuf, ybuf, ybuf);
      // in the following situation, the final fillPolygon() call
      // in this method will not cause the risers to be drawn. The
      // risers are drawn here
      if (lineWidth > 1 && shadingTarget == NONE
	   && interpolation == SAMPLE_AND_HOLD)
	g.drawPolyline(xbuf, ybuf, count);
    }

    if (traceOn) {
      Trace.send(10, traceKey, i18nTrace, "cfarraysBetweenTransformations",
		 new Integer(count),
		 DebugUtil.printArray(xbuf, 0, count +2),
		 DebugUtil.printArray(ybuf, 0, count +2));
    }

    if (lineWidth == 1 &&
	interpolation == SAMPLE_AND_HOLD_WITHOUT_RISERS) {
      drawSampleAndHoldWithoutRisers(g, count, xbuf, ybuf);
      return;
    }

    // If the connectorFormat has a lineWidth > 1 and also has
    // a shadingTarget != NONE, the lineWidth is ignored.
    //
    // presumes that the buffers have been made big enough by
    // configureBuffers.
    if (shadingTarget != NONE) {
      count = adjustPolyForShading(count, xbuf, ybuf,
				   shadingTarget, dataWindow);
      fill = true;
    } else if (lineWidth > 1) {
      // the following "pre-draw" of the polyLine is just
      // in case there are steep lines: with steep lines, the
      // fillPolygon will leaves big gaps.
      if (LINEAR == interpolation)
	g.drawPolyline(xbuf, ybuf, count);
      count = adjustPolyForLineWidth(count, xbuf, xbuf, ybuf, ybuf, lineWidth);
      fill = true;
    }

    if (traceOn) {
      Trace.send(10, traceKey, i18nTrace, "cfarraysAfterTransformations",
		 new Integer(count),
		 DebugUtil.printArray(xbuf, 0, count +2),
		 DebugUtil.printArray(ybuf, 0, count +2));
      //Thread.dumpStack();
    }

    if (fill)
      g.fillPolygon(xbuf, ybuf, count);
    else
      g.drawPolyline(xbuf, ybuf, count);
  }

  void drawSampleAndHoldWithoutRisers(Graphics g, int count,
				      int[] xbuf, int[] ybuf) {
    for (int i = 0; i < count - 1; i += 2) {
      g.drawLine(xbuf[i], ybuf[i], xbuf[i + 1], ybuf[i + 1]);
    }
  }
    
  public Chart getChart() {
    return chart;
  }

  @Override
  public boolean equals(Object other) {
    if((other == null) || !(other.getClass().equals(getClass())))
      return false;

    ConnectorFormat connector = (ConnectorFormat)other;

    return (names.equals(connector.names) &&
	    number == (connector.number));
  }

  public void setConnectorLineWidth(int connectorLineWidth) {
    this.connectorLineWidth = new Integer(connectorLineWidth);
  }

  public int getConnectorLineWidth() {
    if (connectorLineWidth == null) {
      return defaultConnectorFormat.getConnectorLineWidth();
    } else {
    return connectorLineWidth.intValue();
    }
  }

  private void mapInterpolation(Symbol interpolationSym) {
    if(interpolationSym == null)
      connectorInterpolation = null;
    else if (NONE_.equals(interpolationSym))
      connectorInterpolation = NONE_OBJ;
    else if (LINEAR_.equals(interpolationSym))
      connectorInterpolation = LINEAR_OBJ;
    else if (SAMPLE_AND_HOLD_.equals(interpolationSym))
      connectorInterpolation = SAMPLE_AND_HOLD_OBJ;
    else if (SAMPLE_AND_HOLD_WITHOUT_RISERS_.equals(interpolationSym))
      connectorInterpolation = SAMPLE_AND_HOLD_WITHOUT_RISERS_OBJ;
  }

  public void setConnectorInterpolation(Symbol interpolation) {
    mapInterpolation(interpolation);
  }

  public void setConnectorInterpolation(int connectorInterpolation) {
    this.connectorInterpolation = new Integer(connectorInterpolation);
    Trace.send(5, traceKey, i18nTrace, "cfsetConnectorInterpolation",
	       this.connectorInterpolation);
  }

  public int getConnectorInterpolation() {
    if (connectorInterpolation != null) // overrides default
      return connectorInterpolation.intValue();
    else {
      return defaultConnectorFormat.getConnectorInterpolation();
    }
  }

  public void setConnectorLineColor(Symbol connectorLineColorName) {
    this.connectorLineColorName = connectorLineColorName;
    connectorLineColor = G2ColorMap.get(connectorLineColorName);
    if (configured) {
      chart.invalidateDataWindow();
      chart.resetLegendText(this);
    }
  }

  public Color getConnectorLineColor() {
    if (connectorLineColor == null) {
      return defaultConnectorFormat.getConnectorLineColor();
    }
    return connectorLineColor;
  }

  Symbol getConnectorLineColorName() {
    if (connectorLineColorName == null) {
      return defaultConnectorFormat.getConnectorLineColorName();
    } else {
      return connectorLineColorName;
    }
  }

  public void setConnectorsVisible(boolean connectorsVisible) {
    if (connectorsVisible)
      this.connectorsVisible = Boolean.TRUE;
    else
      this.connectorsVisible = Boolean.FALSE;
    chart.resetLegendText(this);
  }

  public boolean getConnectorsVisible() {
    if (connectorsVisible == null) {
      return defaultConnectorFormat.getConnectorsVisible();
    } else {
    return connectorsVisible.booleanValue();
    }
  }

  void mapTarget(Symbol target) {
    if (NONE_.equals(target))
      connectorShadingTarget = NONE_OBJ;
    else if (BOTTOM_.equals(target))
      connectorShadingTarget = BOTTOM_OBJ;
    else if (TOP_.equals(target))
      connectorShadingTarget = TOP_OBJ;
    else
      connectorShadingTarget = null;
  }

  public void setConnectorShadingTarget(Symbol target) {
    mapTarget(target);
  }

  public int getConnectorShadingTarget() {
    if (connectorShadingTarget == null) {
      return defaultConnectorFormat.getConnectorShadingTarget();
    } else {
      return connectorShadingTarget.intValue();
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
    if (name != null)
      names.add(name);
  }

  /** This is an "adapter" method for compatibility with G2 */
  public void setNames(Sequence names) {
   for(Enumeration en = names.elements(); en.hasMoreElements();)
     this.names.add(en.nextElement());
  }

  @Override
  public String toString() {
    return super.toString() + ";color=" + connectorLineColor +
      ";interpolation=" + connectorInterpolation;
  }
}
