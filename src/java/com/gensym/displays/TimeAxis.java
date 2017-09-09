/*
 *  Copyright (C) 1986-2017 Gensym Corporation.All Rights Reserved.
 *
 *      TimeAxis.java
 *               Axis information
 *
 * Description:
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
import java.text.SimpleDateFormat;
import java.text.DateFormat;
import java.io.Serializable;

import com.gensym.util.*;
import com.gensym.message.*;

/** Corresponds to the time axis of a G2 trend chart.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */
public class TimeAxis extends ChartAxis implements Serializable {

  public static boolean traceOn;
  /** prevents update loops from running too fast */
  private static Resource i18n =
  Trace.getBundle("com.gensym.displays.Messages");
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.TraceMessages");
  private static MessageKey traceKey = 
  Trace.registerMessageKey("com.gensym.displays", TimeAxis.class);
  private Color baselineColor;
  private boolean baselineVisible;
  private int gridLinesPerLabel;
  private String timeFormat;
  private Symbol labelAlignment;
  private long labelFrequency;
  // this one is a computed slot
  private int labelFrequencyFactor = 1;
  private boolean relativeLabelsVisible;
  private boolean absoluteLabelsVisible;
  private Structure jumpScrollInterval;
  private boolean jumpScroll;
  private long displayUpdateInterval;
  private long endTime = 0;
  private Structure totalTimeSpan;
  private Structure dataWindowTimeSpan;

  private long visibleTimeSpan;

  private long startTime; //  = new Date().getTime();
  private DateFormat dateFormat;
  private DateFormat relativeDateFormat;
  private boolean valid = false;
  // Becomes invalid if the data range, label frequency, or grid ratio changes.
  // It is possible to optimize so that if the label frequency is only
  // changing because the width of the window has changed, then the
  // grid lines don't need to be recalculated.
  private boolean labelFrequencyValid = false;
  private long latestLabelTime;
  private long lastGridTime;
  long realLabelFrequency;
  private boolean serverTimeMode = false;

  private boolean initialized = false;
  private TrendChart trendChart;

  public TimeAxis() {
    super(new Integer(0));
  }

  public TimeAxis(DataAndLabelWindow dataAndLabelWindow) {
    super(dataAndLabelWindow.dataWindow, ChartAxis.HORIZONTAL);
    dataAndLabelWindow.setTimeAxis(this);
  }

  @Override
  public synchronized void configure(Chart chart) {
    super.configure(chart);
    trendChart = (TrendChart)chart;
  }

  @Override
  public double getDataOrigin() {
    return (double)(endTime - visibleTimeSpan);
  }
		    

  private synchronized void initialize() {
    setDataOrigin(endTime - visibleTimeSpan);
    setVisibleDataRange(endTime - visibleTimeSpan, endTime);
    valid = true;
    initialized = true;
  }

  @Override
  public synchronized double rescale() {
    double returnVal = super.rescale();
    return returnVal;
  }

  long getRealLabelFrequency() {
    if (!labelFrequencyValid) {
      computeLabelFrequency();
      labelFrequencyValid = true;
    }

    return realLabelFrequency;
  }

  double realTickmarkFrequency;

  private synchronized double computeTickMarkFrequency() {
    int dataWindowWidth = dataWindow.getSize().width;
    double scale = getScale();
    realTickmarkFrequency =
      ((automaticLabelFrequency || scale * labelFrequency == 0 )?
       calculateTickmarkInterval(visibleTimeSpan, dataWindowWidth,
				 (int)MathUtils.floor(dataWindowWidth,
						       automaticLabelCount)) :
       labelFrequency);

    Trace.send(20, traceKey, i18nTrace, "tacomputeTickMarkFrequency",
	       new Double(realTickmarkFrequency),
	       new Long(labelFrequency));
    return realTickmarkFrequency;
  }

  synchronized double getTickMarkFrequency() {
    if (!labelFrequencyValid)
      computeTickMarkFrequency();
    
    return realTickmarkFrequency;
  }

  void ensureLabelFrequencyValid() {
    if (!labelFrequencyValid)
      computeLabelFrequency();
  }    

  // shouldn't call this if labels are not shown, or if
  // nullLabelFrequency is true.
  synchronized long computeLabelFrequency() {
    double scale = getScale();
    double firstLabelFrequency =
      getTickMarkFrequency();
    double deviceLabelFrequency = firstLabelFrequency * scale;
    if (deviceLabelFrequency == 0) {
      if (traceOn) {
	System.out.println("computeLabelFrequency got deviceLabelFrequncy of 0 "
                           + getScale());
	System.out.println("size: " + dataWindow.getSize() + "; endTime: " +
			   endTime + "; span:" + visibleTimeSpan);
      }
      throw new UnexpectedException(null, i18n.getString("errorComputingLabelFrequency"));
    }
    double firstWidthAttempt = deviceLabelFrequency;
    // NOTE: this takes into account the necessary separation
    // fix this: need to compute the label width
    int labelDeviceInterval = computeLabelDeviceInterval();
    int factor = 1;
    Trace.send(20, traceKey, i18nTrace, "tacomputeLabelFrequency",
	       new Double(firstLabelFrequency),
	       new Long(labelFrequency),
	       new Integer(labelDeviceInterval));
    for (; labelDeviceInterval > firstWidthAttempt * factor; factor++)
      ;
    Trace.send(20, traceKey, i18nTrace, "tacomputeLabelFrequencyFactor",
	       new Integer(factor));

    labelFrequencyFactor = factor;

    return realLabelFrequency = (long)(firstLabelFrequency * factor);
  }

  private int computeLabelDeviceInterval() {
    String sampleString = dateFormat.format(new Date(endTime));
    return trendChart.getFontMetrics(trendChart.getFont()).stringWidth(sampleString) + TimeLabels.DEFAULT_LABEL_SEPARATION;
  }

  private static final int AUTOMATIC_LABEL_COUNT = 6;
  private int automaticLabelCount = AUTOMATIC_LABEL_COUNT;

  /** Adjusts the end time.
   * @param newTime a new time value that may or may not already fit
   * in the data window. */
  public synchronized void adjustEndTime(double newTime) {
    Trace.send(5, traceKey, i18nTrace, "taadjustEndTime", new Double(endTime),
	       new Double(newTime), new Integer(endTimeMode));
    setEndTime((long)newTime);
  }

  @Override
  public int transform(double value) { // doesn't throw OutOfBoundsException
    int returnVal = 0;
    try {
      returnVal = super.transform(value);
    } catch (OutOfBoundsException oobe) {
      oobe.printStackTrace();
    }
    return returnVal;
  }

  public synchronized void setBaselineColor(Color baselineColor) {
    this.baselineColor = baselineColor;
  }

  public Color getBaselineColor() {
    return baselineColor;
  }

  public synchronized void setBaselineVisible(boolean baselineVisible) {
    this.baselineVisible = baselineVisible;
  }

  public boolean getBaselineVisible() {
    return baselineVisible;
  }

  public synchronized void setGridLinesPerLabel(int gridLinesPerLabel) {
    this.gridLinesPerLabel = gridLinesPerLabel;
    labelFrequencyValid = false;
  }

  public int getGridLinesPerLabel() {
    return gridLinesPerLabel;
  }

  static private Resource formatTranslator =
  Resource.getBundle("com.gensym.displays.TimeFormats");

  static private Resource relativeFormatTranslator =
  Resource.getBundle("com.gensym.displays.RelativeTimeFormats");

  /** Adaptor method for G2 */
  public synchronized void setTimeFormat(String timeFormat) {
    this.timeFormat = timeFormat;
    setDateFormat(TimeUtils.g2DateFormatToJava(formatTranslator, timeFormat));
    relativeDateFormat =
      TimeUtils.g2DateFormatToJava(relativeFormatTranslator, timeFormat);
  }

  /** Adaptor method for G2 */
  public String getTimeFormat() {
    return timeFormat;
  }

  public synchronized void setDateFormat(DateFormat dateFormat) {
    this.dateFormat = dateFormat;
    labelFrequencyValid = false;
  }

  public DateFormat getDateFormat() {
    return dateFormat;
  }

  public DateFormat getRelativeDateFormat() {
    return relativeDateFormat;
  }

  static final int LEFT = 0, CENTER = 1, RIGHT = 2;
  public static final Symbol LEFT_ = Symbol.intern ("LEFT");
  public static final Symbol CENTER_ = Symbol.intern ("CENTER");
  public static final Symbol RIGHT_ = Symbol.intern ("RIGHT");

  int labelAlignmentIndicator = RIGHT;
  public synchronized void setLabelAlignment(Symbol labelAlignment) {
    this.labelAlignment = labelAlignment;
    labelAlignmentIndicator = mapAlignmentSymbol(labelAlignment);
  }

  public Symbol getLabelAlignment() {
    return labelAlignment;
  }

  int getAlignmentIndicator() {
    return labelAlignmentIndicator;
  }

  private static int mapAlignmentSymbol(Symbol labelAlignment) {
    if (LEFT_.equals(labelAlignment))
      return LEFT;
    if (CENTER_.equals(labelAlignment))
      return CENTER;
    return RIGHT;
  }

  private boolean nullLabelFrequency = false;
  private boolean automaticLabelFrequency = true;
  private static final Symbol synchronized_ = Symbol.intern("SYNCHRONIZED");
  private static final Symbol interval_ = Symbol.intern("INTERVAL");
  private static final Symbol numberOfSeconds_ =
  Symbol.intern("NUMBER-OF-SECONDS");
  private static final Symbol labelFrequencyMode_ =
  Symbol.intern("LABEL-FREQUENCY-MODE");
  /** Adaptor method for G2 */
  public synchronized void setLabelFrequency(Structure labelFrequencyStruct)
  throws NoSuchAttributeException{
    labelFrequencyValid = false;
    Symbol mode = null;
    try {
      mode =
	(Symbol)labelFrequencyStruct.getAttributeValue(labelFrequencyMode_);
    } catch (NoSuchAttributeException nsae) {
      nullLabelFrequency = true;
      return;
    }
    
    if (interval_.equals(mode)) {
      automaticLabelFrequency = false;
      labelFrequency = labelFrequencyStruct.getLong(numberOfSeconds_) * 1000;
    } else {
      automaticLabelFrequency = true;
    }
  }
  
  public synchronized void setLabelFrequency(long labelFrequency) {
    this.labelFrequency = labelFrequency;
  }

  public long getLabelFrequency() {
    return labelFrequency;
  }

  public void setAutomaticLabelFrequency(boolean automaticLabelFrequency) {
    this.automaticLabelFrequency = automaticLabelFrequency;
  }

  public boolean getAutomaticLabelFrequency() {
    return automaticLabelFrequency;
  }

  @Override
  public void setLabelColor(Color color) {
    labelColor = color;
    if (trendChart != null)
      trendChart.repaint();
  }

  @Override
  public Color getLabelColor() {
    return labelColor;
  }
  
  public void setRelativeLabelsVisible(boolean relativeLabelsVisible) {
    this.relativeLabelsVisible = relativeLabelsVisible;
    if (trendChart != null) {
      trendChart.acknowledgeLayoutChange();
    }
  }

  public boolean getRelativeLabelsVisible() {
    return relativeLabelsVisible;
  }

  public void setAbsoluteLabelsVisible(boolean absoluteLabelsVisible) {
    this.absoluteLabelsVisible = absoluteLabelsVisible;
    if (trendChart != null) {
      trendChart.acknowledgeLayoutChange();
    }
  }

  public boolean getAbsoluteLabelsVisible() {
    return absoluteLabelsVisible;
  }

  /** Adaptor method for G2 */
  public synchronized void setJumpScrollInterval(Structure jumpScrollInterval)
  throws NoSuchAttributeException{
    this.jumpScrollInterval = jumpScrollInterval;
  }

  public Structure getJumpScrollInterval() {
    return jumpScrollInterval;
  }

  /** Adaptor method for G2 */
  public synchronized void setJumpScroll(boolean jumpScroll)
  throws NoSuchAttributeException{
    this.jumpScroll = jumpScroll;
  }

  public boolean getJumpScroll() {
    return jumpScroll;
  }

  /** In seconds */
  public void setDisplayUpdateInterval(Number displayUpdateInterval) {
    this.displayUpdateInterval =
      (long)((Number)displayUpdateInterval).doubleValue() * 1000;
  }

  /** In seconds */
  public long getDisplayUpdateInterval() {
    return displayUpdateInterval/1000;
  }

  private int endTimeMode;

  public synchronized void setEndTimeMode(int endTimeMode) {
    this.endTimeMode = endTimeMode;
  }

  public int getEndTimeMode() {
    return endTimeMode;
  }

  private void configureScroll() {
  }
  
  private long serverStartTime;

  public synchronized void setServerStartTime(long serverStartTime) {
    this.serverStartTime = serverStartTime;
  }

  public long getServerStartTime() {
    return serverStartTime;
  }

  private static final Symbol END_TIME_MODE_ = Symbol.intern("END-TIME-MODE");
  private static final Symbol LAST_SAMPLE_ = Symbol.intern("LAST-SAMPLE");
  private static final Symbol CURRENT_TIME_ = Symbol.intern("CURRENT-TIME");
  private static final Symbol INTERVAL_ = Symbol.intern ("INTERVAL");

  public static final int LAST_SAMPLE = 0;
  public static final int CURRENT_TIME = 1;
  public static final int INTERVAL = 2;

  /** adaptor method for G2 */
  public synchronized void setEndTime(Structure endTime)
  throws NoSuchAttributeException {
    Trace.send(20, traceKey, i18nTrace, "tasetEndTime", endTime);
    Symbol endTimeType = (endTime == null ? LAST_SAMPLE_ :
			  (Symbol)endTime.getAttributeValue(END_TIME_MODE_,
							    LAST_SAMPLE_));
    // for initialization and configuration, last-sample and current-time
    // can be treated the same. They differ once the chart is running.
    //    if (!initialized) {
    //  if (!INTERVAL_.equals(endTimeMode)) {
    //	setEndTime((new Date()).getTime());
    //  }
    //}
    endTimeMode = mapEndTimeMode(endTimeType);
  }

  private static int mapEndTimeMode(Symbol mode) {
    if (LAST_SAMPLE_.equals(mode))
      return LAST_SAMPLE;
    else if (CURRENT_TIME_.equals(mode))
      return CURRENT_TIME;
    else
      return INTERVAL;
  }

  public void setEndTimeMode(Symbol endTimeMode) {
    Trace.send(20, traceKey, i18nTrace, "tasetEndTimeMode", endTimeMode,
	       new Integer(this.endTimeMode));
    int mode = mapEndTimeMode(endTimeMode);
    this.endTimeMode = mode;
  }

  synchronized boolean isEndTimeCurrent() {
    return endTimeMode == CURRENT_TIME;
  }

  /** This should only be called after the axis is fully initialized */
  public synchronized void setEndTime(long newEndTime) {
    long shift = newEndTime - endTime;
    double startTime =
      (double)endTime - (double)getVisibleTimeSpan();
    setVisibleDataRange(startTime, endTime);
    setDataOrigin(startTime);
    endTime = newEndTime;
      setVisibleDataRange(startTime, endTime);
  }

  @Override
  public double getScale() {
    return (double)dataWindow.getSize().width/(double)visibleTimeSpan;
  }

  public long getEndTime() {
    return endTime;
  }

  public synchronized void setTotalTimeSpan(Structure totalTimeSpan) {
    this.totalTimeSpan = totalTimeSpan;
  }

  public Structure getTotalTimeSpan() {
    return totalTimeSpan;
  }

  long getTotalTimeSpanLength() {
    try {
      long spanLength = -1;
      if (totalTimeSpan != null) {
	Symbol timeSpanMode =
	  (Symbol)totalTimeSpan.getAttributeValue(TOTAL_TIME_SPAN_MODE_);
	if (INTERVAL_.equals(timeSpanMode)) {
	  spanLength =
	    (long)(((Number)totalTimeSpan.
		    getAttributeValue(NUMBER_OF_SECONDS_)).doubleValue() *
		   1000.0);
	}
      }
      if (dataWindowTimeSpan != null) {
	Symbol dataWindowSpanMode =
	  (Symbol)dataWindowTimeSpan.getAttributeValue(DATA_WINDOW_TIME_SPAN_MODE_);
	if (INTERVAL_.equals(dataWindowSpanMode)) {
	  long dwLength =
	    (long)(((Number)dataWindowTimeSpan.
		    getAttributeValue(NUMBER_OF_SECONDS_)).doubleValue() *
		   1000.0);
	  spanLength = Math.max(dwLength, spanLength);
	}
      }
      if (spanLength == -1)
	spanLength = DAY;

      return spanLength;
    } catch (NoSuchAttributeException nsae) {
      throw new CorruptionException(nsae);
    }
  }

  /** Adaptor method for G2 */
  public synchronized void setDataWindowTimeSpan(Structure dataWindowTimeSpan)
  throws NoSuchAttributeException {
    this.dataWindowTimeSpan = dataWindowTimeSpan;
    labelFrequencyValid = false;
     Symbol mode =
       (Symbol)dataWindowTimeSpan.getAttributeValue(DATA_WINDOW_TIME_SPAN_MODE_);
     if (INTERVAL_.equals(mode)) {
       Integer numberOfSeconds =
 	(Integer)dataWindowTimeSpan.getAttributeValue(numberOfSeconds_);
       setVisibleTimeSpan(numberOfSeconds.intValue() * 1000);
     }
  }

  public Structure getDataWindowTimeSpan() {
    return dataWindowTimeSpan;
  }

  public void adjustTimeBounds(long end, long span) {
    setVisibleTimeSpan(span);
    adjustEndTime(end);
  }

  public synchronized void setVisibleTimeSpan(long visibleTimeSpan) {
    Trace.send(10, traceKey, i18nTrace, "dwnewTimespan",
 	       new Long(visibleTimeSpan));
    if (this.visibleTimeSpan != visibleTimeSpan) {
      labelFrequencyValid = false;
    }
    this.visibleTimeSpan = visibleTimeSpan;
  }
  
  public long getVisibleTimeSpan() {
    return visibleTimeSpan;
  }

  // All calculations are done in milliseconds, to match
  // Java's internal representation.
  private static final int[]
    minuteSubdivisions = new int[] {1000, 5000, 10000, 30000, 60000};
  private static final int[]
    hourSubdivisions = new int[] {15000, 30000, 60000, 120000, 180000,
				    300000, 600000, 900000,
				    1200000, 1800000, 3600000};
  private static final int[]
    daySubdivisions = new int[] {300000, 600000, 900000, 1800000, 3600000,
				   7200000, 10800000,
				   14400000, 21600000, 28800000, 43200000};
  private static final int MINUTE = 60000, HOUR = 3600000, DAY = 86400000;

  /** helper method */
  private static long calculateTickmarkInterval(long computedDWTimespan,
						int dataWindowWidth,
						int labelWidth) {
    int maxLabels = (int)MathUtils.floor(dataWindowWidth, labelWidth);
    int[] units = minuteSubdivisions;
    int factor = 1;
    int unit = -1;
    long timespan = 0;

    if (computedDWTimespan <= MINUTE) {
      ; //factor = 1; units = minuteSubdivisions;
    } else if (computedDWTimespan <= HOUR) {
      factor = MINUTE; units = hourSubdivisions;
    } else if (computedDWTimespan <= DAY) {
      factor = HOUR; units = daySubdivisions;
    } else {
      timespan = DAY*(long)MathUtils.floor(computedDWTimespan, DAY);
      for (unit = DAY; MathUtils.ceil(timespan, unit) > maxLabels;
	   unit += DAY) {
	;
      }
      return unit;
    }

    if (units != null) {
      timespan = factor * (long)MathUtils.floor(computedDWTimespan, factor);
      for (int i = 0; i < units.length ; i++){
	unit = units[i];
	if (MathUtils.ceil(timespan, unit) <= maxLabels)
	  break;
      }
    }

    if (unit != -1)
      return unit;

    if (labelWidth >= dataWindowWidth)
      return (computedDWTimespan *
	      (long)MathUtils.ceil(labelWidth, dataWindowWidth));
    else
      return computedDWTimespan;
  }
    
  /** If this is true, the trend chart depends on time updates
   * from the server to determine what the "current" time is, rather
   * that looking at the local time on the client */
  void setServerTimeMode(boolean yes) {
    serverTimeMode = yes;
  }

  boolean getServerTimeMode() {
    return serverTimeMode;
  }

  public void invalidate() {
    valid = false;
  }

  // not synchronizing, because if one of the things changes
  // in midstream, we will get another draw request, and hence
  // a chance to draw correctly.
  /**
   * NOTES: The gridlines are drawn here, but the labels are drawn by the
   * timeLabels.
   */
  void draw (Graphics g) {
    if (realLabelFrequency <= 0)
      return;
    
    long windowStartTime = (long)getDataOrigin();
    double timeScale = getScale();

    Rectangle bounds = dataWindow.getBounds();
    int windowLeft = bounds.x;
    int windowRight = windowLeft + bounds.width;
    int windowTop = bounds.y;
    int windowBottom = windowTop + bounds.height;
    int factor = labelFrequencyFactor * gridLinesPerLabel;
    double deviceInterval =
      ((double)realLabelFrequency)/(double)factor * timeScale;
    long windowEndTime = endTime;
    long labelFrequency = realLabelFrequency;
    long firstLabelTime = windowStartTime - (windowStartTime % labelFrequency);
    // Hack! Can't see how to do this without special-casing the
    // larger-than-a-day case without messing up smaller intervals
    if (labelFrequency % DAY == 0)
      firstLabelTime = TimeUtils.adjustForTimeZone(firstLabelTime);
    long endMarker = windowEndTime;

    Trace.send(20, traceKey, i18nTrace, "tapaintGridLines",
	       bounds, dataWindow.getBounds(),
	       g, g.getClipBounds());
    // can find the first grid line much quicker :-)
    g.setColor(getGridLineColor());

//     System.out.println("deviceInterval=" + deviceInterval +
// 		       ";labelFrequencyFactor=" + factor);

    for (long time = firstLabelTime; time <= endMarker; time += labelFrequency) {
      int x =
	(int)Math.floor((time - windowStartTime) * timeScale) + windowLeft;
      g.drawLine(x, windowTop, x, windowBottom);
      for (int j = 1; j < factor; j++) {
	int newX = x + (int)Math.round(deviceInterval * j);
 	g.drawLine(newX, windowTop, newX, windowBottom);
      }
    }
  }
}
