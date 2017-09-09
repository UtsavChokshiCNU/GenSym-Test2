/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ValueLabels.java
 *
 *		Robert Penny		Jan/98
 *
 */

package com.gensym.displays;

import java.awt.*;
import java.util.*;
import java.text.NumberFormat;
import com.gensym.draw.*;
import com.gensym.util.*;
import com.gensym.message.*;

/** The labels and tickmarks for the value axis. The labels are "slaved" to
 * the DataWindow and the valueAxis.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */
public class ValueLabels extends Component implements DynamicShape {

  private static Resource i18n =
  Resource.getBundle("com.gensym.displays.Messages");
  private static Resource i18nTrace =
  Resource.getBundle("com.gensym.displays.TraceMessages");
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.displays", ValueLabels.class);

  private static final int DEFAULT_LABEL_SEPARATION = 6;
  static final int LABEL_RIGHT_MARGIN = 2;
  static final int LABEL_LEFT_MARGIN = 2;

  private FontMetrics metrics;
  private Dimension maxSize;

  ValueAxis valueAxis;
  DataWindow dataWindow;

  ValueLabels(ValueAxis valueAxis, DataWindow dataWindow) {
    this.valueAxis = valueAxis;
    this.dataWindow = dataWindow;
  }

  int computeMinimumWidth() {
    int width = valueAxis.getMaxLabelWidth();
    if (valueAxis.getBaselineVisible())
      width += 1;
    return width;
  }

  int getStringWidth(String sample) {
    Trace.send(10, traceKey, i18nTrace, "vlgetStringWidth", this, sample);
    return getFontMetrics(getFont()).stringWidth(sample);
  }

  @Override
  public Dimension getPreferredSize() {
    Dimension size = dataWindow.getSize();
    return new Dimension(computeMinimumWidth(), size.height);
  }

  @Override
  public Dimension getMinimumSize() {
    return getPreferredSize();
  }

  @Override
  public Dimension formatShape() throws UnableToFormatException {
    Dimension size = getSize();
    return formatShape(size, maxSize, true);
  }

  @Override
  public Dimension formatShape(Dimension newSize,
			       Dimension newMaxSize,
			       boolean growVerticallyFirst)
  throws UnableToFormatException {
    if(newSize.width > newMaxSize.width) {
      throw new IllegalArgumentException
	(i18n.format("SizeExceedsMaxSize", newSize, newMaxSize));
    }

    int minimumWidth = computeMinimumWidth();
    if (minimumWidth > newMaxSize.width) {
      throw new UnableToFormatException(i18n.getString("tlwidthTooSmall"));
    }
    maxSize = newMaxSize;
    Dimension currentSize = getSize();
    int width = currentSize.width;
    int height = currentSize.height;
    setSize(minimumWidth, height);
    return new Dimension(minimumWidth, height);
  }

  // fix this: temp hack for development
  int labelMargin = 2;

  int getLabelHeight() {
    return getFontMetrics(getFont()).getHeight() + labelMargin;
  }

  int getLabelAscent() {
    return getFontMetrics(getFont()).getAscent();
  }

  // fix this: temp hack for development
  private static final int labelOffsetTweak = 2;

  private void paintBaseline(Graphics g, boolean onRight, int labelOffset) {
    TrendChart chart = valueAxis.chart;
    DataAndLabelWindow dalw = chart.dataAndLabelWindow;
    Point location = dalw.getLocation();
    DataWindow dataWindow = chart.dataWindow;
    Dimension dwSize = dataWindow.getSize();
    int y1 = labelOffset/2;
    int y2 = y1 + dwSize.height;
    Dimension size = getSize();
    int x =
      (onRight ? LABEL_LEFT_MARGIN : size.width - LABEL_RIGHT_MARGIN);

    g.setColor(valueAxis.getBaselineColor());
    g.drawLine(x, y1, x, y2);
  }

  @Override
  public void paint(Graphics g) {
    if (!(valueAxis.getValueAxisVisible() && valueAxis.getLabelsVisible()))
      return;
    g.setFont(getFont());
    double[] tickmarkValues = valueAxis.getTickmarkValues();
    int tickmarkCount = valueAxis.getTickmarkCount();

    int labelOffset = getLabelAscent();

    double valueOffset, valueScale;
    NumberFormat numberFormatter;

    int maxLabelWidth;
    boolean percent;
    double min, max, range;
    synchronized(valueAxis) {
      valueOffset = valueAxis.getDataOrigin();
      valueScale = valueAxis.getScale();
      numberFormatter = valueAxis.getNumberFormatter();
      
      maxLabelWidth = valueAxis.getMaxLabelWidth();
      percent = valueAxis.getShowLabelsAsPercent();
      
      min = valueAxis.getVisibleDataMinimum();
      max = valueAxis.getVisibleDataMaximum();
      range = max - min;
    }

    boolean onRight = valueAxis.positionedOnRight();
    boolean baselineVisible = valueAxis.getBaselineVisible();
    int baselineAdjustement = 0;

    if (baselineVisible) {
      paintBaseline(g, onRight, labelOffset);
      baselineAdjustement = (onRight ? 1 : -1);
    }

    int labelRight =
      maxLabelWidth - LABEL_RIGHT_MARGIN + baselineAdjustement;
      
    g.setColor(valueAxis.getLabelColor());
    Trace.send(10, traceKey, i18nTrace, "vlpaint1", new Double(min),
	       new Double(max), new Boolean(percent),
	       new Integer(maxLabelWidth));

    for(int i = 0; i < tickmarkCount; i++) {
      int yPos =
	(int)Math.floor((valueOffset - tickmarkValues[i]) * valueScale) +
	labelOffset;
      double val = (percent ? (tickmarkValues[i] - min)/range :
		    tickmarkValues[i]);
      String label = numberFormatter.format(val);
      int width = getFontMetrics(getFont()).stringWidth(label);
      int xPos = labelRight - width;
      Trace.send(30, traceKey, i18nTrace, "vlpaint2",
		 new Integer(i), new Integer(yPos), new Integer(width));
      g.drawString(label, xPos, yPos);
    }

//     Rectangle bounds = getBounds();
//     g.drawRect(0, 0, bounds.width, bounds.height);
//     g.setColor(valueAxis.getLabelColor());
//     g.drawString(valueAxis.getChartElementUid().toString(), 13, 13);
  }
    
}


