/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      SimpleChartHorizontalAxis.java
 *
 * Description:
 *               One set of information to draw and how to draw it
 *
 *
 */
package com.gensym.displays;

import com.gensym.util.*;
import com.gensym.message.*;
import java.util.*;
import java.awt.*;


/** Corresponds to an axis of a Chart in G2.
 * @author Robert Penny
 * @version 1.0 December 1997
 * @undocumented
 */
class SimpleChartHorizontalAxis extends SimpleChartAxis {

  static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.displays.chart",
			   SimpleChartHorizontalAxis.class);
  static Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.TraceMessages");

  static Integer index = new Integer(1);

  int left, right, y;

  SimpleChartHorizontalAxis(SimpleChart chart,
			    SimpleChartAxisDefaults axisDefaults) {
    super(chart, axisDefaults);
  }

  //
  // G2 Slots
  //

  // final for performance only
  private final int getLabelWidth(double value) {
    Font font = getDeclaredFont();
    FontMetrics metrics = chart.getFontMetrics(font);
    return metrics.stringWidth(formatLabel(value));
  }

  int getLeftAdjust() {
    return getLabelWidth(computedMinimum)/2;
  }

  int getRightAdjust() {
    return getLabelWidth(computedMaximum)/2;
  }

  @Override
  int getVisibleLength() {
    return right - left;
  }

  @Override
  int getOffset() {
    double scale = getScale();
    return left - (int)(scale * computedMinimum);
  }

  //
  // drawing support
  //
  int labelTopMargin = 2;

  private static int DEFAULT_LABEL_SEPARATOR = 6;

  int getNeededVerticalLabelSpace () {
    Font font = getDeclaredFont();
    FontMetrics metrics = chart.getFontMetrics(font);
    return metrics.getHeight() + labelTopMargin;
  }    

  @Override
  void drawLabels(Graphics g, double tickmarkInterval, double scale) {
    Font font = getDeclaredFont();
    g.setFont(font);
    g.setColor(getTextColor());
    FontMetrics metrics = chart.getFontMetrics(font);
    int labelY = y + metrics.getHeight() + labelTopMargin;

    double range = computedMaximum - computedMinimum;

      // hack! rather than try to be clever figuring out what the largest
      // number is, we look at all the numbers we may have to
      // print, and find the largest.
      // this is a very slow way to do it, but it works
    int maxLabelWidth = 0;

    for (double position = 0.0;
	 position <= range;
	 position += tickmarkInterval) {
      int x = left + (int)Math.round(position * scale);
      Trace.send(20, traceKey, i18nTrace, "schadrawTickmarks2",
		 new Double(position), new Integer(x));
      if (x > right)
	return;

      String label = formatLabel(position);
      int labelWidth = metrics.stringWidth(label);

      if (labelWidth > maxLabelWidth)
	maxLabelWidth = labelWidth;
    }

    int tickmarkSeparation = (int)Math.ceil(tickmarkInterval*scale);

    int tickmarksToSkip =
      (int)Math.max(1, MathUtils.ceil(maxLabelWidth + DEFAULT_LABEL_SEPARATOR,
				      tickmarkSeparation));

    double labelInterval = tickmarkInterval * tickmarksToSkip;

    for (double position = 0.0;
	 position <= range;
	 position += labelInterval) {
      int x = left + (int)Math.round(position * scale);
      Trace.send(20, traceKey, i18nTrace, "schadrawTickmarks2",
		 new Double(position), new Integer(x));
      if (x > right)
	return;

      // fix this: really will iterate over an array of label locations
      // and values
      String label = formatLabel(position + computedMinimum);
      int labelWidth = metrics.stringWidth(label);
      g.drawString(label, x - labelWidth/2, labelY);
    }
  }

  @Override
  void drawTickmarksOrGrid(Graphics g, double tickmarkInterval, double scale,
			   boolean doGrid) {
    Trace.send(20, traceKey, i18nTrace, "schadrawTickmarks",
	       new Double(tickmarkInterval), new Double(scale),
	       new Integer(left), new Integer(right));

    int y1 = doGrid ? chart.verticalAxis.top : y;
    int y2 = doGrid ? chart.verticalAxis.bottom : y1 - tickLength;

    double range = computedMaximum - computedMinimum;

    for (double position = 0.0;
	 position <= range;
	 position += tickmarkInterval) {
      int x = left + (int)Math.round(position * scale);
      Trace.send(20, traceKey, i18nTrace, "schadrawTickmarks2",
		 new Double(position), new Integer(x));
      if (x > right)
	return;

      g.drawLine(x, y1, x, y2);
    }
  }

  @Override
  void drawAxis(Graphics g) {
    g.setColor(getLineColor());
    g.drawLine(left, y, right, y);
  }    
}
