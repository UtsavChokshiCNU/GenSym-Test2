/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      TrendChartPlot.java
 *
 * Description:
 *               One set of information to draw and how to draw it
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

import com.gensym.util.*;
import com.gensym.util.Set;
import com.gensym.message.*;
import com.gensym.ntw.util.ChartHistoryBuffer;

/** Corresponds to a plot in a G2 trend chart. */
public class TrendChartPlot implements Serializable, ChartElement {

  static Resource i18n =
  Resource.getBundle("com.gensym.displays.Messages");

  public static boolean traceOn = false;
  static Resource i18nTrace =
  Resource.getBundle("com.gensym.displays.TraceMessages");
  static MessageKey traceKey = 
  Trace.registerMessageKey("com.gensym.displays", TrendChartPlot.class);

  static final Symbol
  UPDATE_INTERVAL_ = Symbol.intern("UPDATE-INTERVAL"),
    GRANULARITY_ = Symbol.intern("GRANULARITY");

  Boolean includeInLegend;
  Structure tracingAndBreakpoints;
  boolean useSimulator;
  boolean mayRequestEventUpdates;
  boolean mayRequestDataSeeking;
  int updatePriority;
  Number waitInterval;
  Structure updateInterval;
  Object connectorFormatNameOrNumber;
  Object pointFormatNameOrNumber;
  Object valueAxisNameOrNumber;
  boolean useLocalHistory;
  Set names = new Set();
  Object expression;

  // ChartPath will be used to enable things such as clicking on the graph
  // to get details of the graph at that point. However, ChartPath
  // will only be necessary if Graphics2D is not ready in time,
  // as hitPath() will do the trick nicely.
  private TrendChartPlot defaultTrendChartPlot;
  private ChartPath chartPath;
  private TrendChartLegend trendChartLegend;

  ConnectorFormat connectorFormat;
  MarkerFormat markerFormat;
  ValueAxis valueAxis;
  TimeAxis timeAxis;
  TrendChart chart;
  DataAndLabelWindow dataAndLabelWindow;

  private int lastIndexPainted;
  private boolean configured = false;

  private Dimension size;
  DataWindow dataWindow;
  com.gensym.classes.TrendChart g2TrendChart;

  public TrendChartPlot(TrendChart chart,
			com.gensym.classes.TrendChart g2TrendChart,
			Object chartElementUid) {
    super();
    this.g2TrendChart = g2TrendChart;
    this.chart = chart;
    this.chartElementUid = chartElementUid;
    trendChartLegend = new TrendChartLegend(this, chart);
    chart.addLegend(trendChartLegend);
  }

  private Object chartElementUid;
  @Override
  public Object getChartElementUid() {
    return chartElementUid;
  }

  void configureValueAxes() {
    Object valueAxisIdentifier = getValueAxisNameOrNumber();
    Trace.send(10, traceKey, i18nTrace, "tcpconfigureValueAxes1",
	       valueAxisIdentifier);
    valueAxis = chart.getValueAxis(valueAxisIdentifier);
    Trace.send(10, traceKey, i18nTrace, "tcpconfigureValueAxes2",
	       valueAxis);
  }

  @Override
  public void configure(Chart genericChart) {
    Trace.send(5, traceKey, i18nTrace, "tcpConfigure", this, genericChart,
	       valueAxisNameOrNumber);
    defaultTrendChartPlot = chart.getDefaultTrendChartPlot();
    // chart = (TrendChart)genericChart;
    timeAxis = chart.getTimeAxis();

    configureValueAxes();

    connectorFormat =
      chart.getConnectorFormat(getConnectorFormatNameOrNumber());

    markerFormat =
      chart.getMarkerFormat(getPointFormatNameOrNumber());

    dataWindow = chart.getDataWindow();
    chartPath = new ChartPath(this);
    dataAndLabelWindow = chart.dataAndLabelWindow;
    configured = true;
  }

  public void reconfigure() {
    boolean needFullRedraw = false;

    ValueAxis newValueAxis = chart.getValueAxis(getValueAxisNameOrNumber());

    if (!newValueAxis.equals(valueAxis)) {
      valueAxis = newValueAxis;
      needFullRedraw = true;
    }

    ConnectorFormat newConnectorFormat =
      chart.getConnectorFormat(getConnectorFormatNameOrNumber());

    if (!newConnectorFormat.equals(connectorFormat)) {
      connectorFormat = newConnectorFormat;
      needFullRedraw = true;
    }
    MarkerFormat newMarkerFormat =
      chart.getMarkerFormat(getPointFormatNameOrNumber());

    if (!newMarkerFormat.equals(markerFormat)) {
      markerFormat = newMarkerFormat;
      needFullRedraw = true;
    }

    if (needFullRedraw)
      chart.repaintDataAndLabelWindow();
  }      

    

  @Override
  public void dispose() {
    chart.removeTrendChartPlot(this);
    dataWindow.remove(chartPath);
  }

  private static final long NO_PRIOR_END_TIME_MARKER = -1L;
  private long priorEndTime = NO_PRIOR_END_TIME_MARKER;

  public void acknowledgeNewData(long newEndTime) {
    if (priorEndTime != NO_PRIOR_END_TIME_MARKER)
      chart.acknowledgeNewData(priorEndTime, newEndTime);

    priorEndTime = newEndTime;
  }

  public void setIncludeInLegend(boolean includeInLegend) {
    this.includeInLegend = new Boolean(includeInLegend);
    chart.acknowledgeLayoutChange();
  }

  public boolean getIncludeInLegend() {
    if (includeInLegend == null) {
      return defaultTrendChartPlot.getIncludeInLegend();
    } else {
      return includeInLegend.booleanValue();
    }
  }

  // It could be more intelligent about it
  // and only reset those that have changed, based on whether
  // the ChartElement affects the plot in question (i.e., is either
  // the MarkerFormat or the ConnectorFormat for that plot.
  // the "element" argument is the hook that makes such intelligence
  // possible.
  void resetLegendText(ChartElement element) {
      resetLegendText();
  }

  private void resetLegendText() {
    if (configured && getIncludeInLegend())
      trendChartLegend.resetLegendText();
  }
  

  /** adaptor method for G2 */
  public void setTracingAndBreakpoints(Symbol tracingAndBreakpoints) {
  }
  
  /** adaptor method for G2 */
  public void setTracingAndBreakpoints(Structure tracingAndBreakpoints) {
    this.tracingAndBreakpoints = tracingAndBreakpoints;
  }

  public Structure getTracingAndBreakpoints() {
    return tracingAndBreakpoints;
  }

  public void setUseSimulator(boolean useSimulator) {
    this.useSimulator = useSimulator;
  }

  public boolean getUseSimulator() {
    return useSimulator;
  }

  public void setMayRequestEventUpdates(boolean mayRequestEventUpdates) {
    this.mayRequestEventUpdates = mayRequestEventUpdates;
  }

  public boolean getMayRequestEventUpdates() {
    return mayRequestEventUpdates;
  }

  public void setMayRequestDataSeeking(boolean mayRequestDataSeeking) {
    this.mayRequestDataSeeking = mayRequestDataSeeking;
  }

  public boolean getMayRequestDataSeeking() {
    return mayRequestDataSeeking;
  }

  public void setUpdatePriority(int updatePriority) {
    this.updatePriority = updatePriority;
  }

  public int getUpdatePriority() {
    return updatePriority;
  }

  public void setWaitInterval(Number waitInterval) {
    this.waitInterval = waitInterval;
  }

  public Number getWaitInterval() {
    return waitInterval;
  }

  /** Adaptor method for G2 */
  public void setUpdateInterval(Structure updateInterval)
  throws NoSuchAttributeException {
    this.updateInterval = updateInterval;
  }

  public Structure getUpdateInterval() {
    if (updateInterval == null)
      return defaultTrendChartPlot.getUpdateInterval();
    return updateInterval;
  }

  /** @returns the minimum number of milliseconds between data points.
   */
  long getGranularity() {
    Structure updateInterval = getUpdateInterval();
    Number intervalNum = null;
    try {
      intervalNum =
	((Number)updateInterval.getAttributeValue(UPDATE_INTERVAL_));
    } catch (NoSuchAttributeException nsae) {
      throw new CorruptionException(nsae);
    }
    long interval = (long)(intervalNum.doubleValue() * 1000);

    Number granularityNum =
      (Number)updateInterval.getAttributeValue(GRANULARITY_, null);
    
    if (granularityNum == null)
      return interval;
    
    long granularity = (long)(granularityNum.doubleValue() * 1000);

    if (traceOn) {
      Trace.send(20, traceKey, i18nTrace, "tcp_getGranularity",
		 new Long(interval), new Long(granularity));
    }
    
    return Math.min(interval, granularity);
  }

  public void setConnectorFormatNameOrNumber(Object connectorFormatNameOrNumber) {
    this.connectorFormatNameOrNumber = connectorFormatNameOrNumber;
    ConnectorFormat newConnectorFormat =
      chart.getConnectorFormat(getConnectorFormatNameOrNumber());
    if (!newConnectorFormat.equals(connectorFormat)) {
      connectorFormat = newConnectorFormat;
      resetLegendText();
      chart.repaintDataAndLabelWindow();
    }
  }

  public Object getConnectorFormatNameOrNumber() {
    if (connectorFormatNameOrNumber != null)
      return connectorFormatNameOrNumber;
    else
      return defaultTrendChartPlot.getConnectorFormatNameOrNumber();
  }

  public void setPointFormatNameOrNumber(Object pointFormatNameOrNumber) {
    this.pointFormatNameOrNumber = pointFormatNameOrNumber;
    MarkerFormat newMarkerFormat =
      chart.getMarkerFormat(getPointFormatNameOrNumber());
    if (!newMarkerFormat.equals(markerFormat)) {
      markerFormat = newMarkerFormat;
      resetLegendText();
      chart.repaintDataAndLabelWindow();
    }
  }

  public Object getPointFormatNameOrNumber() {
    if (pointFormatNameOrNumber != null)
      return pointFormatNameOrNumber;
    else
      return defaultTrendChartPlot.getPointFormatNameOrNumber();
  }

  /** Adaptor method for G2 */
  public void setValueAxisNameOrNumber(Object valueAxisNameOrNumber) {
    Trace.send(5, traceKey, i18nTrace, "tcpsetValueAxisNameOrNumber", this,
	       valueAxisNameOrNumber);
    this.valueAxisNameOrNumber = valueAxisNameOrNumber;
    configureValueAxes();
  }

  public Object getValueAxisNameOrNumber() {
    if (valueAxisNameOrNumber != null)
      return valueAxisNameOrNumber;
    else
      return defaultTrendChartPlot.getValueAxisNameOrNumber();
  }

  public void setUseLocalHistory(boolean useLocalHistory) {
    this.useLocalHistory = useLocalHistory;
  }

  public boolean getUseLocalHistory() {
    return useLocalHistory;
  }

  /** Adaptor method for G2 */
  public void setNames(Object names) {
    if (names instanceof Symbol)
      setName((Symbol)names);
    else if (names instanceof Sequence)
      setNames((Sequence)names);
    else if (names == null) {
      this.names.clear();
      resetLegendText();
    } else
      throw new IllegalArgumentException();
  }

  private void setName(Symbol name) {
    names.clear();
    names.add(name);
    resetLegendText();
  }

  private void setNames(Sequence names) {
    this.names = new ChartSet(names);
    resetLegendText();
  }

  @Override
  public Enumeration getNames() {
    return names.elements();
  }

  public String getName() {
    if (names.size() >0) {
      return ((Symbol)(names.firstElement())).getPrintValue();
    } else
      return null;
  }
    

  public Object getExpression() {
    return expression;
  }

  public void setExpression(Object expression) {
    this.expression = expression;
    resetLegendText();
    chart.acknowledgeLayoutChange();
  }

  TrendChart getTrendChart() {
    return chart;
  }

  TrendChartLegend getTrendChartLegend() {
    return trendChartLegend;
  }

  void setTrendChartLegend(TrendChartLegend trendChartLegend) {
    this.trendChartLegend = trendChartLegend;
  }

  MarkerFormat getMarkerFormat() {
    if (markerFormat == null) {
      return defaultTrendChartPlot.getMarkerFormat();
    } else {
    return markerFormat;
    }
  }

  ConnectorFormat getConnectorFormat() {
    if (connectorFormat == null) {
      return defaultTrendChartPlot.getConnectorFormat();
    } else {
    return connectorFormat;
    }
  }

  ValueAxis getValueAxis() {
    if (valueAxis == null)
      return defaultTrendChartPlot.getValueAxis();
    else
      return valueAxis;
  }

  Color getMostVisibleColor() {
    ConnectorFormat connectors = getConnectorFormat();
    if (connectors.getConnectorsVisible())
      return connectors.getConnectorLineColor();
    else {
      MarkerFormat markers = getMarkerFormat();
      if (markers.getMarkersVisible()) {
	return markers.getMarkerColor();
      }
    }
    return null;
  }

  Symbol getMostVisibleColorName() {
    ConnectorFormat connectors = getConnectorFormat();
    if (connectors.getConnectorsVisible())
      return connectors.getConnectorLineColorName();
    else {
      MarkerFormat markers = getMarkerFormat();
      if (markers.getMarkersVisible()) {
	return markers.getMarkerColorName();
      }
    }
    return null;
  }
    

  private TrendChartPlot getDefault() {
    return defaultTrendChartPlot;
  }

  private boolean isDefault() {
    return (this == defaultTrendChartPlot);
  }

  ChartHistoryBuffer getHistory() {
    return (ChartHistoryBuffer)g2TrendChart.getHistory(chartElementUid);
  }
}
