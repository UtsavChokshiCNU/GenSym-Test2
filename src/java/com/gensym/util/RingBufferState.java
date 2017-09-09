/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 RingBufferState.java
 *
 *     
 */

package com.gensym.util;

import java.io.Serializable;

/** Maintains ring buffer state when points are added. To be able to
 * use the buffer contents, add various methods that use the internally
 * stored data. To allow subclasses to make efficient use of the stored
 * buffer, the internal data is all <code>protected</code> on the understanding
 * that users of this data (i.e., subclasses) will not modify it.
 * @author Robert Penny
 * @version 1.0 21-nov-97
 */
public abstract class RingBufferState implements Serializable {

  protected static int defaultCapacity = 300; // 5 minutes, in seconds
  /** the index of the "oldest" value still in the buffer */
  protected volatile int start = 0;
  /** The index of the last element appended */
  protected volatile int end = 0;
  /** This is the index within the buffer at which the next
   * data point will be appended. */
  protected volatile int nextPos = 0;
  /** The number that is added to a "relative" index to get the
   * "absolute" index. */
  protected volatile int offset = 0;
  protected volatile boolean wrapped = false;
  // the actual length of the underlying array(s)
  protected volatile int length;
  // the largest potential length of the underlying arrays(s)
  protected int capacity;

  /** Maintains the internal state of all the variables that enable
   * the ring buffer to work */
  protected final synchronized  void adjustCounters() {
    end = nextPos;
    int len = this.length;
    if (wrapped) {
      nextPos = (nextPos + 1) % len;
      start = nextPos;
      if (nextPos == 0)
	offset += len;
    } else if (++nextPos == len) { // first time it wraps
      wrapped = true;
      nextPos = 0;
    }
  }

  /** @param absolueIndex the index corresponding to the "nth" item added
   * using addElement(), even if absoluteIndex is greater than the length
   * of the buffer.
   * @return the index within the internal buffer that corresponds to the
   * absoluteIndex, if that index hasn't "dropped off". */
  protected final synchronized  int bufferIndex(int absoluteIndex) {
    int realIndex = absoluteIndex - offset;
    int len = this.length;
    if (realIndex >= len) {
      realIndex = realIndex - len;
    }
    if (realIndex >= len || realIndex < 0)
      throw new ArrayIndexOutOfBoundsException(absoluteIndex);
    return realIndex;
  }

  protected final synchronized  int absoluteIndex(int bufferIndex) {
    return (bufferIndex < start ?
	    bufferIndex + offset + length :
	    bufferIndex + offset);
  }

  /** For efficiency, this only sets the counters so that the
   * the buffer will appear to have no data. It does not actually
   * alter the values of any of the positions in the buffer. Since
   * data *must* be added in a way that sets the counters correctly,
   * old data will be overriden before any user of the buffer tries
   * to read from a particular position */
  public synchronized void clear() {
    start = end = nextPos = offset = 0;
    wrapped = false;
  }

  /** Returns the number of data points stored in the buffer.
   */
  public int elementCount() {
    if (wrapped)
      return length;
    else
      return nextPos - start;
  }

  /** @returns how many data points can be stored in this RingBuffer,
   * before it resizes its internal buffer(s).
   */
  public int getLength() {
    return length;
  }

  public void setCapacity(int capacity) {
    this.capacity = capacity;
  }

  /** @returns <code>true</code> if the next value added to the
   * RingBuffer would overwrite an old value in the buffer.
   * @undocumented
   */
  protected final boolean overwritingValue() {
    // in current implementation, with no empty space
    // in a wrapped ring buffer, the second part is
    // redundant.
    return (wrapped && nextPos == start);
  }

  /** concrete subclasses that have actual buffers are responsible
   * for transferring data from the original buffers to the new
   * buffers required for a size change, but can call this
   * method to set the state data correctly.
   * This method requires that the data from the old buffer
   * be copied into the new buffers such that the oldest point
   * in the new buffer goes into the 0th position. The method
   * <code>copyArrayForResize</code> does this.
   * <p><b>
   * The concrete subclass should copy the data into the new
   * buffers *before* calling this method.
   * </b>
   * @see #copyArrayForResize
   */
  protected synchronized void resize(int newSize) {
    if (newSize == length)
      return;
    
    if (wrapped) {
      if (newSize > length) {
	nextPos = length;
	end = nextPos - 1;
	wrapped = false;
      } else {
	nextPos = 0;
	end = newSize - 1;
	offset += (length - newSize);
      }
    } else {
      if (nextPos > newSize) {
	offset += (nextPos - newSize);
	nextPos = 0;
	end = newSize - 1;
	wrapped = true;
      }
    }

    offset += start;
    length = newSize;
    start = 0;
  }

  /** Assumes that the index is already within the range of
   * valid indices for this buffer.
   */
  protected final synchronized  int previousBufferIndex(int index) {
    if (index == start)
      return start;

    if (index == 0 && wrapped)
      return length - 1;
    else
      // note that !wrapped implies start == 0
      return index - 1;
  }

  /** Assumes that the index is already within the range of
   * valid indices for this buffer.
   */
  protected final synchronized  int nextBufferIndex(int index) {
    int localEnd = end;
    if (index == localEnd)
      return localEnd;

    if (wrapped) {
      if (index == length - 1) {
	return 0;
      } else {
	return index + 1;
      }
    } else {
      // note, can't have
      // (!wrapped && (index == length - 1) && !(index == localEnd) &&
      return index + 1;
    }
  }

  /** To be called on the internal buffers before calling resize().
   */
  protected void copyArrayForResize(Object oldArray, Object newArray,
				    int newSize) {
    if (newSize == length)
      return;
    if (newSize > length) {
      // first move the first part of the data into the beginning 
      System.arraycopy(oldArray, start, newArray, 0, length - start);
      if (start != 0) {
	// now put the rest at the end
	System.arraycopy(oldArray, 0, newArray, length - start, end + 1);
      }
    } else if (end > newSize - 1) {
      // only one portion will need to be copied
      System.arraycopy(oldArray, end + 1 - newSize, newArray, 0, newSize);
    } else if (!wrapped) {
      // it will all fit even though shrinking
      System.arraycopy(oldArray, 0, newArray, 0, end + 1);
    } else {
      int tailLength = end + 1;
      int remainder = newSize - tailLength;
      // copy tail portion into the end of the new array first
      System.arraycopy(oldArray, 0, newArray, remainder, tailLength);
      // copy as much of the rest as will fit
      System.arraycopy(oldArray, length - remainder, newArray,
		       0, remainder);
    }
  }

  @Override
  public String toString() {
    return super.toString() + ";" + "start=" + start + ";end=" + end +
      ";wrapped=" + wrapped + ";offset=" + offset + ";nextPos" + nextPos;
  }
}
