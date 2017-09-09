/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ChartSet.java
 *
 *  Description:
 *               The mathematical set.
 *
 *	 Author:
 *		Robert Penny		Aug/97
 *
 *     
 *   Modifications:
 *
 */

package com.gensym.displays;

import java.util.*;

import com.gensym.util.Set;

/** Implements a special way of choosing which element to return if
 * the set has fewer elements than the caller expects.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 */
public class ChartSet extends Set {
  public ChartSet() {
    super();
  }

  public ChartSet(int capacity) {
    super(capacity);
  }

  public ChartSet(int capacity, int increment) {
    super(capacity, increment);
  }

  /** Performs a shallow clone on the data in the vector */
  public ChartSet(Vector vector) {
    super(vector);
  }

  /** If the index would otherwise be out of bounds, defaults first to 1,
   * the to 0. Will still throw an exception if the set is empty. */
  @Override
  public Object elementAt(int index) {
    int size = size();
    if (index >= size) {
      if (size > 1)
	index = 1;
      else
	index = 0;
    }
    return super.elementAt(index);
  }
}
