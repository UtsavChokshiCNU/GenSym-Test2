/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DataAndLabelWindow.java
 *
 */

package com.gensym.displays;

import java.awt.*;
import java.util.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.BufferedContainer;

/** Contains the data window and the labels for the TimeAxis
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */

public class DataAndLabelWindow extends BufferedContainer
implements DynamicShape {

  public static boolean traceOn = false;
  private static Resource i18n =
  Trace.getBundle("com.gensym.displays.Messages");
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.TraceMessages");
  private static MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.displays", DataAndLabelWindow.class);

  DataWindow dataWindow;
  private TimeLabels timeLabels;
  private TimeAxis timeAxis;
  private boolean borderVisible = false;
  private Color borderColor = Color.black;

  public DataAndLabelWindow(Dimension initialSize,
			    Dimension minSize,
			    boolean borderVisible,
			    Color backgroundColor,
			    Color borderColor) {
    dataWindow = new DataWindow(initialSize, minSize);
    dataWindow.setParent(this);
    this.borderVisible = borderVisible;
    setBackground(backgroundColor);
    this.borderColor = borderColor;
  }

  void setTimeAxis(TimeAxis timeAxis) {
    this.timeAxis = timeAxis;
    timeLabels = new TimeLabels(timeAxis, dataWindow);
  }

  void setTrendChart(TrendChart trendChart) {
    dataWindow.chart = trendChart;
    timeLabels.chart = trendChart;
  }

  public DataAndLabelWindow(DataWindow dataWindow, TimeLabels timeLabels) {
    this.dataWindow = dataWindow;
    dataWindow.setParent(this);
    setBorderVisible(dataWindow.borderVisible);
    setDataWindowBackgroundColor(dataWindow.getBackgroundColor());
    setBorderColor(dataWindow.getBorderColor());
    this.timeLabels = timeLabels;
    // uncomment if "children" go back to being awt components.
    // the order is important to determine the order of drawing:
    // the dataWindow draws one pixel over the timeLabels
    //add(timeLabels);
    //add(dataWindow);

    //setBufferedPaint(false);
  }

  //
  // local methods
  //

  void setTimeLabelsVisible(boolean yes) {
    timeLabels.setVisible(yes);
  }

  //
  // DynamicShape
  //

  @Override
  public Dimension formatShape() throws UnableToFormatException {
    Dimension size = getSize();
    return formatShape(size, size, true);
  }
    
  @Override
  public Dimension formatShape(Dimension initialSize,
			       Dimension maxSize,
			       boolean growVerticallyFirst)
  throws UnableToFormatException {
    Trace.send(20, traceKey, i18nTrace, "dalwFormatShape", initialSize,
	       maxSize);
    Dimension dataSize = dataWindow.getMinimumSize(),
      labelSize = timeLabels.getMinimumSize();
    int dataHeight = initialSize.height,
      labelHeight = labelSize.height;
    int candidateWidth = initialSize.width;
    
    if (dataHeight > maxSize.height)
      throw new UnableToFormatException(i18n.format("dwMaxTooSmall", maxSize,
						    dataSize));
    if (dataHeight + labelHeight > maxSize.height) {
      labelHeight = 0;
    } else {
      dataHeight -= labelHeight;
    }

    dataWindow.setBounds(0, 0, candidateWidth, dataHeight);
    timeLabels.setBounds(0, dataHeight, candidateWidth, labelHeight);
    //repaint();
    return new Dimension(candidateWidth, dataHeight + labelHeight);
  }

  //
  // BufferedContainer
  //

  @Override
  protected void localPaint(Graphics g) {
    Rectangle dataWindowBounds = dataWindow.getBounds();
    Dimension size = getSize();
    g.setColor(getBackground());
    g.fillRect(0, 0, size.width, size.height);

    timeAxis.ensureLabelFrequencyValid();
    timeLabels.draw(g);
    dataWindow.draw(g);
    containerPaint(g);
    Trace.send(20, traceKey, i18nTrace, "dalwLocalPaint", getBounds(),
	       dataWindow.getBounds(), timeLabels.getBounds(),
	       g.getClipBounds());

    if (borderVisible) {
      g.setColor(borderColor);
      g.drawRect(0, 0, size.width - 1, size.height - 1);
    }
  }

  //
  // awt overrides
  //

  @Override
  public Dimension getMinimumSize() {
    return dataWindow.getMinimumSize();
  }

  @Override
  public void setBounds(int x, int y, int width, int height) {
    super.setBounds(x, y, width, height);
    Dimension dataSize = dataWindow.getMinimumSize(),
      labelSize = timeLabels.getMinimumSize();
    int dataHeight = dataSize.height,
      labelHeight = labelSize.height;
    int candidateWidth = width;
    
    if (dataHeight + labelHeight > height)
      labelHeight = 0;

    dataHeight = height - labelHeight;
    if (labelHeight == 0) // can't rely on space in the label area to draw
      dataHeight -= 1;

    dataWindow.setBounds(0, 0, candidateWidth, dataHeight);
    timeLabels.setBounds(0, dataHeight, candidateWidth, labelHeight);
    if(traceOn)
      Trace.send(20, traceKey, i18nTrace, "dalwsetBounds", getBounds(),
		 dataWindow.getBounds(), timeLabels.getBounds());
    //repaint();
  }

  @Override
  public void setBackground(Color color) {
    super.setBackground(color);
    repaint();
  }

  //
  // G2 Adaptor properties
  //

  public void setDataWindowBackgroundColor(Color color) {
    setBackground(color);
    repaint();
  }

  public void setBorderColor(Color color) {
    borderColor = color;
    repaint();
  }

  public Color getBorderColor() {
    return borderColor;
  }

  public void setBorderVisible(boolean yes) {
    borderVisible = yes;
    repaint();
  }

  public boolean getBorderVisible() {
    return borderVisible;
  }
}
  
