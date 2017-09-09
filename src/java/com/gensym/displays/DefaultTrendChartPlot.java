/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DefaultTrendChartPlot.java
 *
 *     
 *   Modifications:
 *
 */
package com.gensym.displays;

import com.gensym.util.Structure;
import com.gensym.util.Symbol;

/** A pre-initialized version that acts as the default version
 * in a chart. All important slots are initialized to be non-null;
 */
class DefaultTrendChartPlot extends TrendChartPlot {

  static final Structure DEFAULT_UPDATE_INTERVAL =
  new Structure(new Symbol[] {UPDATE_INTERVAL_},
                new Object[] {new Long(2)},        // in seconds, not millis
		1);

  int DEFAULT_NAME_OR_NUMBER = 1;
  Integer DEFAULT_NAME_OR_NUMBER_OBJ = new Integer(DEFAULT_NAME_OR_NUMBER);
  
  public DefaultTrendChartPlot(TrendChart chart) {
    super(chart, null, DEFAULT_);
    includeInLegend = Boolean.TRUE;
    connectorFormat = chart.getDefaultConnectorFormat();
    markerFormat = chart.getDefaultMarkerFormat();
    valueAxis = chart.getDefaultValueAxis();
    valueAxisNameOrNumber = DEFAULT_NAME_OR_NUMBER_OBJ;
    pointFormatNameOrNumber = DEFAULT_NAME_OR_NUMBER_OBJ;
    connectorFormatNameOrNumber = DEFAULT_NAME_OR_NUMBER_OBJ;
    updateInterval = DEFAULT_UPDATE_INTERVAL;
  }

  @Override
  public void configure(Chart genericChart) {
  }
}
