/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ValueLabels.java
 *
 *		Robert Penny		Jan/98
 *
 */

package com.gensym.displays;

import java.awt.Container;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.Dimension;
import java.awt.Font;
import java.util.Enumeration;

import com.gensym.message.Trace;
import com.gensym.message.Message;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;

/** Is simply the container for all of the legends.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */
public class TrendChartLegends extends Container {

  private static final Resource i18nTrace =
  Resource.getBundle("com.gensym.displays.TraceMessages");

  private static final MessageKey traceKey =
  Message.registerMessageKey("com.gensym.displays", TrendChartLegends.class);

  TrendChart trendChart;

  TrendChartLegends(TrendChart trendChart) {
    this.trendChart = trendChart;
  }

  @Override
  public Component add(Component comp) {
    comp.setSize(getSize().width, 0);
    return super.add(comp);
  }

  void resetLegendTexts() {
    for(Enumeration en = trendChart.getTrendChartPlots();
	en.hasMoreElements();) {
      TrendChartPlot plot = (TrendChartPlot)en.nextElement();
      TrendChartLegend legend = plot.getTrendChartLegend();
      legend.resetLegendText();
    }
  }

  void layoutLegends (int maxHeight) {
    boolean hasVisibleLegend = false;
    Dimension size = getSize();
    int width = size.width;
    int currentHeight = 0;
    Trace.send(10, traceKey, i18nTrace, "tclslayoutLegends", size);
    for(Enumeration en = trendChart.getTrendChartPlots();
	en.hasMoreElements();) {
      TrendChartPlot plot = (TrendChartPlot)en.nextElement();
      TrendChartLegend legend = plot.getTrendChartLegend();
      if (plot.getIncludeInLegend()) {
	Trace.send(10, traceKey, i18nTrace, "tclsPlotIncluded", plot);
	if (legend == null) {
	  Trace.send(10, traceKey, i18nTrace, "tclsNullLegend", plot);
	  continue;
	} else {
	  legend.setVisible(true);
	}
	// in case width or plot description have changed
	legend.resetLegendText();
	if (legend.getLegendText() == null) {
	  Trace.send(10, traceKey, i18nTrace, "tclsNullLegendText", legend);
	  legend.setVisible(false);
	  continue;
	}
	try {
	  legend.formatShape(size, size, true);
	} catch (UnableToFormatException utfe) {
	  Trace.exception(utfe);
	}
	int legendHeight = legend.getHeight();
	if (currentHeight > maxHeight) {
	  // fix this: should do something other than silently stop adding
	  // legend lines. Should also not go on to the other legends.
	  legend.setVisible(false);
	  Trace.send(10, traceKey, i18nTrace, "tclsLegendTooHigh", legend);
	  continue;
	}
	hasVisibleLegend = true;
	legend.setVisible(true);
	legend.setBounds(0, currentHeight, width, legendHeight);
	currentHeight += legendHeight;
      } else {
	Trace.send(10, traceKey, i18nTrace, "tclsPlotNotIncluded", plot);
	if (legend != null)
	  legend.setVisible(false);
      }
    }
    setSize(width, currentHeight);
    setVisible(hasVisibleLegend);
  }
}
