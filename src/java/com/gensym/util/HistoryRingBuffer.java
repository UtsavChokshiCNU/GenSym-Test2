/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 HistoryRingBuffer.java
 *
 *     
 */

package com.gensym.util;

import com.gensym.message.Resource;
import com.gensym.message.Trace;
import com.gensym.message.MessageKey;

/** Maintains ring buffer state when points are added. To be able to
 * use the buffer contents, add various methods that use the internally
 * stored data. To allow subclasses to make efficient use of the stored
 * buffer, the internal data is all <code>protected</code> on the understanding
 * that users of this data (i.e., subclasses) will not modify it.
 * <p>
 * NOTE: will only allow data more recent than it's own most recent data to
 * be stored (i.e., does not overwrite existing data or allow points to
 * be interpolated between existing points).
 * @author Robert Penny
 * @version 1.0 21-nov-97
 */
public class HistoryRingBuffer extends RingBufferState {
  private static Resource i18n =
  Trace.getBundle("com.gensym.ntw.util.Messages");
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.ntw.util.TraceMessages");
  private static final MessageKey traceKey = 
  Trace.registerMessageKey("com.gensym.ntw.util", HistoryRingBuffer.class);

  public static final boolean traceOn = false;

  /** 3 minutes.
   */
  private static final int DEFAULT_EXPANSION_INTERVAL = 180000;
  /** 1 second.
   */
  private static final int DEFAULT_GRANULARITY = 1000;
  /** Expand by 10 extra points to avoid extra expansions
   * when close to filling up the history.
   */
  private static final int DEFAULT_SIZE_SLACK = 10;

  private static final double DEFAULT_EXPANSION_FACTOR = 1.3;

  protected double[] valueBuf;
  protected volatile long[] timeBuf;

  volatile long granularity = 1; // default 1 millisecond
  volatile long timeSpan = -1;
  double expansionFactor = DEFAULT_EXPANSION_FACTOR;

  // Try not to expand too often, yet also try not to get
  // too big too soon: the client may be relatively shortlived.
  long averageExpansionInterval = DEFAULT_EXPANSION_INTERVAL;
  int sizeSlack = DEFAULT_SIZE_SLACK;

  public HistoryRingBuffer() {
    this(DEFAULT_EXPANSION_INTERVAL, DEFAULT_GRANULARITY);
  }

  public HistoryRingBuffer(long timeSpan, long granularity) {
    this.timeSpan = timeSpan;
    this.granularity = granularity;

    int initialCapacity =
      numberOfPointsForInterval(Math.min(timeSpan, averageExpansionInterval));

    valueBuf = new double[initialCapacity];
    timeBuf = new long[initialCapacity];
    length = initialCapacity;
  }

  public void setTimeSpan(long timeSpan) {
    this.timeSpan = timeSpan;
  }

  public void setGranularity(long granularity) {
    this.granularity = granularity;
  }

  /** Called when G2 adjusts its internal clock when going from
   * "as fast as possible" mode to "real time" mode.
   */
  public synchronized void adjustTimestamps(long timeDelta) {
    int len = length;
    int bufferEnd = end;
    for (int i = start; ;i++) {
      if (i == len)
	i = i % len;

      timeBuf[i] += timeDelta;

      if (i == bufferEnd)
	break;
    }
  }

  /** Add a new value to the end of the RingBuffer, possibly dropping
   * a value (i.e., overwriting the "oldest" value). */
  public synchronized void addElement(long timestamp, double value) {

    // fix this: should only get duplicates in first update
    // after trend-chart subscription: should move this filter
    // out and put responsibility onto the TrendChartImpl.
    if (timestamp > timeBuf[end]) {
      // could optimize to just test "wrapped" right here
      expandIfNecessary(timestamp);
      
      valueBuf[nextPos] = value;
      timeBuf[nextPos] = timestamp;
      adjustCounters();
    }
  }

  /** Note that currently the capacity of this history ring buffer
   * is determined solely by the timeSpan: there is no concept
   * of the maximum number of points to be stored, just the
   * maximum age.
   */
  void expandIfNecessary(long newTimestamp) {
    // fix this: I find the following readable, but is it the most
    // efficient codewise? Could use a single boolean expression.
    //long amountOfTimeToExpand = averageExpansionInterval;
    if (!overwritingValue()) { // could optimize to just test "wrapped"
      return;
    } else if (timeSpan == -1) {
      // never overwrite a value: expand
      expand();
    } else {
      long remainingTimeInSpan =
	(earliestTimestamp() + timeSpan) - newTimestamp;
      if (remainingTimeInSpan < 0)
	// can afford to overwrite the earliest point
	return;
      expand();
    }
  }

  /** NOTE: this is only really an approximation, as there could end
   * up being more or less points than this during the specified
   * time-interval.
   */
  private final int numberOfPointsForInterval(long timeInterval) {
    return (int)((double)timeInterval/(double)granularity) + sizeSlack;
  }    

  void expand() {
    // Add extra points at the end to avoid floating point errors
    // ever resulting in not actually expanding at low numbers
    resizeBuffers((int)Math.ceil(length * expansionFactor) + sizeSlack);
  }

  public long earliestTimestamp() {
    return timeBuf[start];
  }

  public long latestTimestamp() {
    return timeBuf[end];
  }

  @Override
  public int getLength() {
    return length;
  }

  public int getEndIndex() {
    if (wrapped)
      return end + offset + length;
    else
      return end;
  }

  public int getStartIndex() {
    return start + offset;
  }

  /** @returns the closest index into the underlying array.
   */
  protected synchronized int getBufferIndex(long timestamp) {
    return getIndexByBinarySearch(timestamp);
  }

  public synchronized int elementCount(long startTime, long endTime) {
    return (getIndex(endTime) - getIndex(startTime) + 1);
  }

  /** @returns the closest index into the overall history.
   */
  protected synchronized int getIndex(long timestamp) {
    return absoluteIndex(getIndexByBinarySearch(timestamp));
  }

  private final int getMedianIndex(int intervalStart, int intervalEnd) {
    if (elementCount() == 0)
      return 0;
    int intervalLength =
      (intervalEnd >= intervalStart ?
       intervalEnd - intervalStart :
       intervalEnd - intervalStart + length);
    return (intervalStart + intervalLength/2) % length;
  }

  private int getIndexByBinarySearch(long timestamp) {
    int latest = end;
    int earliest = start;

    for (int median = getMedianIndex(earliest, latest);;
	 median = getMedianIndex(earliest, latest)) {
//       System.out.println("Median: " + median + "; earliest: " + earliest +
// 			 "; latest: " + latest);
      if (median == earliest || median == latest) {
	if (earliest == latest) {
	  return median;
	} else {
	  if (Math.abs(timeBuf[earliest] - timestamp) <=
	      Math.abs(timeBuf[latest] - timestamp))
	    return earliest;
	  else
	    return latest;
	}
      } else {
	if (timestamp < timeBuf[median])
	  latest = median;
	else
	  earliest = median;
      }
    }
  }

  /** Returns a string of "index=value;" pairs for this buffer. */
  public String pprint() {
    StringBuffer strBuf;
    synchronized (this) {
      int len = this.length;
      if (len == 0)
	return "<EMPTY>";

      strBuf = new StringBuffer();
      int localOffset = offset;
      for (int i = start; ;i = (i + 1)) {
	if (i == len) {
	  i = i % len;
	  localOffset = localOffset + len;
	}
	strBuf.append(i + localOffset).append("(").append(i).append(")").
	  append("=").append(timeBuf[i]).
	  append(",").append(valueBuf[i]).append(";");
	if (i == end)
	  break;
      }
    }
    return strBuf.toString();
  }

  protected void resizeBuffers(int newSize) {
    if (traceOn) {
      Trace.send(10, traceKey, i18nTrace, "hrb_resizeBuffers",
		 new Integer(newSize), new Integer(length));
    }

    if (newSize == length)
      return;

    long[] newTimeBuf = new long[newSize];
    double[] newValueBuf = new double[newSize];
    copyArrayForResize(timeBuf, newTimeBuf, newSize);
    copyArrayForResize(valueBuf, newValueBuf, newSize);
    resize(newSize);
    timeBuf = newTimeBuf;
    valueBuf = newValueBuf;
  }
}
