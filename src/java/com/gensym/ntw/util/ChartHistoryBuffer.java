/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ChartHistoryBuffer.java
 *
 *     
 */

package com.gensym.ntw.util;

import java.awt.Point;
import com.gensym.core.DebugUtil;
import com.gensym.message.*;
import com.gensym.util.HistoryRingBuffer;

/** A chart-specific utility class for plot histories.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */
public class ChartHistoryBuffer extends HistoryRingBuffer {
  private static Resource i18n =
  Trace.getBundle("com.gensym.displays.Messages");
  private static Resource i18nTrace =
  Trace.getBundle("com.gensym.displays.traceMessages");
  private static final MessageKey traceKey = 
  Trace.registerMessageKey("com.gensym.displays", ChartHistoryBuffer.class);

  private static boolean traceOn = false;

  private int g2StartIndex;

  public ChartHistoryBuffer() {
    super();
  }

  public ChartHistoryBuffer(long timespan, long granularity) {
    super(timespan, granularity);
  }

  /** Takes all the points in the ChartHistoryBuffer, and fills in the
   * the transformed values into the provided device buffers. It is
   * the responsibility of the caller to make sure the buffers are
   * large enough.
   * @returns a Point, the x value of which is the count, the y value
   * is the G2 history index of the first point transformed. Returns
   * <code>null</code> if no points are transformed.
   */
  public synchronized Point transform(long startTime, long endTime,
				      int indexDelta,
				      int[] xDeviceBuf, double xScale,
				      long xTranslate, int xOrigin,
				      int[] yDeviceBuf, double yScale,
				      double yTranslate, int yOrigin,
				      int markerFrequency,
				      double[] markerValues)
  {
    if (elementCount() == 0)
      return null;

    boolean collectMarkerValues = (markerValues != null);

    int bufferStart = getBufferIndex(startTime);
    bufferStart = previousBufferIndex(bufferStart);

    int markerBufLength = collectMarkerValues ? markerValues.length : 0;
    int markerIndex = 0;

    int bufferEnd = getBufferIndex(endTime);
    bufferEnd = nextBufferIndex(bufferEnd);

    int count = 0;
    int index = 0;
    int len = length;
    
    for (int i = bufferStart; ;i++) {
      if (i == len) {
	i = i % len;
      }
      xDeviceBuf[index] =
	  (int)Math.floor((timeBuf[i] - xTranslate) * xScale) +
	xOrigin;
      yDeviceBuf[index] =
	(int)Math.floor((yTranslate - valueBuf[i]) * yScale) +
	yOrigin;

      if (collectMarkerValues &&
	  // Only collect the values that will actually be displayed,
	  // as determined by markerFrequency. Note, that in order
	  // to display the same markers as G2 would display, modulo
	  // arithmetic needs to be in relation to G2's view of
	  // history index values.
	  ((absoluteIndex(i) + g2StartIndex) % markerFrequency) == 0 &&
	  // next test should be unnecessary, but I don't
	  // want to deal with this causing an abort
	  // at this stage in the release cycle.
	   markerIndex < markerBufLength) {
	markerValues[markerIndex] = valueBuf[i];
	markerIndex++;
      }

      if (traceOn)
	Trace.send(30, traceKey, i18nTrace, "historyLinearTransform",
		   new Long(timeBuf[i]), new Integer(xDeviceBuf[index]),
		   new Double(valueBuf[i]), new Integer(yDeviceBuf[index]));
      count++;
      if (i == bufferEnd)
	break;
      index += indexDelta;
    }

    if (traceOn)
      Trace.send(30, traceKey, i18nTrace, "historyLinearTransform2",
		 pprint(), DebugUtil.printArray(xDeviceBuf, 0, index + 1),
		 DebugUtil.printArray(yDeviceBuf, 0, index + 1));
    return new Point (index + 1, absoluteIndex(bufferStart) + g2StartIndex);
  }

  public void setG2StartIndex(Number startIndex) {
    if (startIndex != null)
      g2StartIndex = startIndex.intValue();
  }

  public int getG2StartIndex() {
    return g2StartIndex;
  }
}
