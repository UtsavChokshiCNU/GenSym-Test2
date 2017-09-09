/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 RingBufferOfDouble.java
 *
 *     
 */

package com.gensym.ntw.util;

import java.util.Enumeration;

/** Maintains ring buffer state when points are added. To be able to
 * use the buffer contents, add various methods that use the internally
 * stored data. To allow subclasses to make efficient use of the stored
 * buffer, the internal data is all <code>protected</code> on the understanding
 * that users of this data (i.e., subclasses) will not modify it.
 * @author Robert Penny
 * @version 1.0 21-nov-97
 */
public class RingBufferOfDouble implements java.io.Serializable {

  protected static int defaultCapacity = 86400; // a day, in seconds
  /** the index of the "oldest" value still in the buffer */
  protected int start = 0;
  /** The index of the last element appended */
  protected int end = 0;
  /** This is the index within the buffer at which the next
   * data point will be appended. */
  protected int nextPos = 0;
  /** The number that is added to a "relative" index to get the
   * "absolute" index. */
  protected int offset = 0;
  private boolean wrapped = false;
  private int length;

  protected double[] buf;

  public RingBufferOfDouble() {
    this(defaultCapacity);
  }

  public RingBufferOfDouble(int initialCapacity) {
    if (initialCapacity <= 0)
      initialCapacity = defaultCapacity;

    buf = new double[initialCapacity];
    length = initialCapacity;
  }

  /** Add a new value to the end of the RingBuffer, possibly dropping
   * a value (i.e., overwriting the "oldest" value). */
  public synchronized void addElement(double value) {
    buf[nextPos] = value;

    adjustCounters();
  }

  /** Maintains the internal state of all the variables that enable
   * the ring buffer to work */
  protected final void adjustCounters() {
    end = nextPos;
    int len = this.length;
    if (wrapped) {
      nextPos = (nextPos + 1) % len;
      start = nextPos;
      if (nextPos == 0)
	offset += len;
    } else if (++nextPos == len) { // first time it wraps
      System.out.println("Wrapped: " + nextPos);
      wrapped = true;
      nextPos = 0;
    }
  }

  /** @param index the "absolute" index */
  public synchronized double elementAt(int index) {
    int realIndex = index - offset;
    int len = this.length;
    if (realIndex >= len) {
      realIndex = realIndex - len;
    }
    return buf[realIndex];
  }

  /** Returns a string of "index=value;" pairs for this buffer. */
  public String pprint() {
    StringBuffer strBuf = new StringBuffer("RingBufferOfDouble: ");
    synchronized (this) {
      int len = this.length;
      int localOffset = offset;
      for (int i = start; ;i = (i + 1)) {
	if (i == len) {
	  i = i % len;
	  localOffset = localOffset + len;
	}
	strBuf.append(i + localOffset).append("=").append(buf[i]).append(";");
	if (i == end)
	  break;
      }
    }
    return strBuf.toString();
  }

  /** Starts with the "oldest" value still in the buffer, and progresses
   * to the last value added to the buffer. Does not take a snapshot
   * of data in the buffer.
   * CAUTION: This Enumeration is somewhat open to race conditions: If
   * the competing thread adds elements to the RingBufferOfDouble
   * faster than the Enumeration goes through the buffer, then it is possible
   * for the ring buffer to go around the end of the ring buffer, then
   * "overtake" the Enumeration, with unpredictable results. Also, if the
   * buffer is made smaller during the iteration, the results are
   * unpredictable.
   * <p>
   * If a competing thread adds elements at about the same speed as the
   * enumeration, then it is possible that the Enumeration will never end
   * (i.e., hasMoreElements() can return true forever).
   *<p>
   * If in any doubt, enclose any enumeration inside a block synchronized
   * on the source buffer.
   */
  public Enumeration elements() {
    return
      new Enumeration()
      {
	int pos = start;
	@Override
	public boolean hasMoreElements() {
	  return (pos != start + length);
	}
	@Override
	public Object nextElement() {
	  double val = buf[pos++ % length];
	  return new Double(val);
	}
      };
  }
}
