/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      SimpleChartVerticalAxis.java
 *
 * Description:
 *               One set of information to draw and how to draw it
 *
 *
 */
package com.gensym.displays;

import com.gensym.ntw.util.G2FontMap;
import com.gensym.util.*;
import com.gensym.message.*;
import java.util.*;
import java.awt.*;


/** Corresponds to a vertical axis of a Chart in G2.
 * @author Robert Penny
 * @version 1.0 December 1997
 * @undocumented
 */
class SimpleChartVerticalAxis extends SimpleChartAxis {

  static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.displays.chart",
			   SimpleChartVerticalAxis.class);
  static Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.TraceMessages");

  static final Integer index = new Integer(2);

  int top, bottom, x;

  SimpleChartVerticalAxis(SimpleChart chart,
			  SimpleChartAxisDefaults axisDefaults) {
    super(chart, axisDefaults);
  }

  //
  // G2 Slots
  //

  // final for performance only
  private final int getLabelHeight() {
    Font font = getDeclaredFont();
    FontMetrics metrics = chart.getFontMetrics(font);
    return metrics.getHeight();
  }

  int getTopAdjust() {
    Font font = getDeclaredFont();
    FontMetrics metrics = chart.getFontMetrics(font);
    return metrics.getAscent()/2;
  }

  int getBottomAdjust() {
    Font font = getDeclaredFont();
    FontMetrics metrics = chart.getFontMetrics(font);
    return metrics.getAscent()/2 + metrics.getDescent();
  }

  @Override
  int getVisibleLength() {
    return bottom - top;
  }

  @Override
  int getOffset() {
    double scale = getScale();
    return top + (int)(scale * computedMaximum);
  }

  //
  // drawing support
  //
  int labelRightMargin = 2;

  /**
   * This really a stub at the moment. It will be completed when
   * the new "precision" annotation is implemented.
   */
  int getMaxLabelWidth() {
    Font font = getDeclaredFont();
    FontMetrics metrics = chart.getFontMetrics(font);

    return (int) Math.max(metrics.stringWidth(formatLabel(computedMinimum)),
			  metrics.stringWidth(formatLabel(computedMaximum)));
  }
    

  @Override
  void drawLabels(Graphics g, double tickmarkInterval, double scale) {
    Font font = getDeclaredFont();
    g.setFont(font);
    g.setColor(getTextColor());
    FontMetrics metrics = chart.getFontMetrics(font);
    int labelHeight = metrics.getHeight();
    int labelAscent = metrics.getAscent();
    
    double range = computedMaximum - computedMinimum;
    
    int tickmarkSeparation = (int)Math.ceil(tickmarkInterval*scale);
    
    int tickmarksToSkip =
      (int)Math.max(1, MathUtils.ceil(labelHeight, tickmarkSeparation));
    
    double labelInterval = tickmarkInterval * tickmarksToSkip;

    for (double position = computedMinimum;
	 position <= computedMaximum;
	 position += labelInterval) {
      
      int y = bottom - (int)Math.round((position - computedMinimum) * scale);
      Trace.send(20, traceKey, i18nTrace, "scvadrawTickmarks2",
		 new Double(position), new Integer(y));
      if (y < top)
	return;

      String label = formatLabel(position);
      int labelWidth = metrics.stringWidth(label);
      int xPos = x - (labelWidth + labelRightMargin);
      // for some reason, the following yPos makes the labels look
      // vertically centered at all three point sizes that chart
      // deal with.
      int yPos = y + labelAscent/2;
      Trace.send(5, traceKey, i18nTrace, "scvadrawLabelsMin",
		 new Integer(labelWidth), new Integer(xPos), new Integer(yPos));
      g.drawString(label, xPos, yPos);
    }

  }

  @Override
  void drawTickmarksOrGrid(Graphics g, double tickmarkInterval, double scale,
			   boolean doGrid) {
    Trace.send(20, traceKey, i18nTrace, "scvadrawTickmarks",
	       new Double(tickmarkInterval), new Double(scale),
	       new Integer(top), new Integer(bottom));
    if (tickmarkInterval < 0) // not specified
      tickmarkInterval = computedMaximum - computedMinimum;
    int x1 = doGrid ? chart.horizontalAxis.left : x;
    int x2 = doGrid ? chart.horizontalAxis.right : x1 + tickLength;

    for (double position = 0.0;
	 position <= computedMaximum - computedMinimum;
	 position += tickmarkInterval) {
      int y = top + (int)Math.round(position * scale);
      Trace.send(20, traceKey, i18nTrace, "scvadrawTickmarks2",
		 new Double(position), new Integer(y));
      if (y > bottom)
	return;

      g.drawLine(x1, y, x2, y);
    }
  }

  @Override
  void drawAxis(Graphics g) {
    g.setColor(getLineColor());
    g.drawLine(x, top, x, bottom);
  }
}
