/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 TimeLabels.java
 *
 *  Description:
 *               The "scrolling" labels that show the time values.
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
import java.text.DateFormat;
import com.gensym.draw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.G2FontMap;

/** The labels and tickmarks for the time axis. The labels are "slaved" to
 * the DataWindow and the timeAxis.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */
public class TimeLabels extends Object implements DynamicShape {

  private static Resource i18n =
  Resource.getBundle("com.gensym.displays.Messages");
  private static Resource i18nTrace =
  Resource.getBundle("com.gensym.displays.TraceMessages");
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.displays", TimeLabels.class);
  public static boolean traceOn = false;

  private static int DEFAULT_TICKMARK_LENGTH = 4;
  private static final int DEFAULT_TOP_MARGIN = 0;
  private static final int DEFAULT_BOTTOM_MARGIN = 4;

  private TimeAxis timeAxis;
  private DataWindow dataWindow;
  static int DEFAULT_LABEL_SEPARATION = 10;
  
  // fix this: the following are only needed to implement DynamicShape
  private boolean needsFormatting = true;
  private boolean valid = false;
  private boolean invalidElement = false;

  private boolean growVerticallyFirst;
  private Dimension maxSize;
  private Dimension size;
  private Point location;

  private int topMargin = DEFAULT_TOP_MARGIN;
  private int bottomMargin = DEFAULT_BOTTOM_MARGIN;
  private int labelSeparation = DEFAULT_LABEL_SEPARATION;
  private int tickmarkLength = DEFAULT_TICKMARK_LENGTH;
  TrendChart chart;

  public TimeLabels(TimeAxis timeAxis, DataWindow dataWindow) {
    this.dataWindow = dataWindow;
    chart = dataWindow.getTrendChart();
    this.timeAxis = timeAxis;
    // setBackground(dataWindow.getBackgroundColor());
    // setForeground(dataWindow.getForegroundColor());
  }

  private int computeHeightFromFont() {
    FontMetrics metrics = chart.getFontMetrics(chart.getFont());
    return metrics.getHeight();
  }

  private int computeMinimumHeight() {
    return computeHeightFromFont() + topMargin + bottomMargin;
  }

  static final Dimension SINGULARITY = new Dimension(0, 0);

  public Dimension getPreferredSize() {
    if (isVisible()) {
      Rectangle bounds = dataWindow.getBounds();
      return new Dimension(bounds.width,
			   computeMinimumHeight());
    } else {
      return SINGULARITY;
    }
  }

  public Dimension getMinimumSize() {
    return getPreferredSize();
  }

  private boolean isVisible;
  
  void setVisible(boolean yes) {
    isVisible = yes;
  }

  boolean isVisible() {
    return isVisible;
  }

  private Rectangle boundsRect;

  void setBounds(int x, int y, int width, int height) {
    boundsRect = new Rectangle(x, y, width, height);
  }

  Rectangle getBounds() {
    return boundsRect;
  }

  void setSize(int width, int height) {
    boundsRect.width = width;
    boundsRect.height = height;
  }

  Dimension getSize() {
    return new Dimension(boundsRect.width, boundsRect.height);
  }

  /** based on the principle that it is better to start at the right hand
   * end in doing calculations.
   * <p>
   * NOTES: The labels are drawn here, but the gridlines are drawn by the
   * timeAxis.
   */
  private void paintLabelsAndTickmarks(Graphics g) {
    long labelFrequency = timeAxis.realLabelFrequency;
    if (labelFrequency <= 0)
      return;

    Font font = chart.getFont();
    g.setFont(font);
    FontMetrics metrics = g.getFontMetrics(font);
    DateFormat dateFormat = timeAxis.getDateFormat();
    int labelHeight = metrics.getHeight();

    Trace.send(20, traceKey, i18nTrace, "tldrawLabels", getBounds(),
	       g.getClipBounds());
    int top = getBounds().y;
    int tickmarkBottom = top + tickmarkLength;

    int bottom = top + labelHeight + topMargin;
    int alignment = timeAxis.getAlignmentIndicator();
    Color gridColor = timeAxis.getGridLineColor(),
      labelColor = timeAxis.getLabelColor();
    // fix this: optimization: should only do labels within
    // the clipping rectangle
    int windowLeft = dataWindow.getLocation().x;
    double timeScale = timeAxis.getScale();
    long windowStartTime = (long)timeAxis.getDataOrigin();
    long windowEndTime = timeAxis.getEndTime();
    long firstLabelTime = windowStartTime - (windowStartTime % labelFrequency);
    // Hack! Can't see how to do this without special-casing the
    // larger-than-a-day case without messing up smaller intervals
    if (labelFrequency % TimeUtils.DAY == 0)
      firstLabelTime = TimeUtils.adjustForTimeZone(firstLabelTime);
    // make sure we draw one off to the right of the window
    // for smoother looking scrolling
    long endMarker = windowEndTime + labelFrequency;

    for (long time = firstLabelTime; time < endMarker; time += labelFrequency) {
      int x =
	(int)Math.floor((time - windowStartTime) * timeScale) + windowLeft;
      String timeString = dateFormat.format(new Date(time));
      int pos;
      if (alignment == TimeAxis.LEFT) {
	pos = x;
      } else {
	int labelWidth = metrics.stringWidth(timeString);
	if (alignment == TimeAxis.RIGHT) {
	  pos = x - labelWidth;
	} else {
	  pos = x - labelWidth/2;
	}
      }
      // fix this: is it faster to loop twice to reduce the number of
      // color changes?
      //System.out.println("time labels top: " + top + "; bottom: " + bottom +
      //		   "; pos: " + pos);
      g.setColor(gridColor);  
      g.drawLine(x, top, x, tickmarkBottom);
      g.setColor(labelColor);
      g.drawString(timeString, pos, bottom);
    }
  }

  public void draw(Graphics g) {
    if(!isVisible())
      return;
    Trace.send(20, traceKey, i18nTrace, "tlpaint", g, g.getClipBounds(),
	       getBounds());
    
    if (!dataWindow.getTrendChart().getActive())
      return;

    paintLabelsAndTickmarks(g);
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
    if(newSize.height > newMaxSize.height) {
      throw new IllegalArgumentException
	(i18n.format("SizeExceedsMaxSize", newSize, newMaxSize));
    }

    int minimumHeight = computeMinimumHeight();
    if (minimumHeight > newMaxSize.height) {
      throw new UnableToFormatException(i18n.getString("tlheightTooSmall"));
    }
    Dimension currentSize = getSize();
    int width = currentSize.width;
    int height = currentSize.height;
    setSize(newSize.width, minimumHeight);
    return new Dimension(width, minimumHeight);
  }
}
