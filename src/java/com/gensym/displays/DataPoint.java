/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 DataPoint.java
 *
 *  Description:
 *               A repository of connector information that can draw itself.
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

/** This class is intended to mimick the non-ui apsects of
 * <code>java.awt.Point</code>, but with <code>double</code>'s instead of
 * <code>int</code>'s.
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 * @deprecated This class is no longer used.
 */

public class DataPoint {
  public double x;
  public double y;

  public DataPoint(double x, double y) {
    this.x = x;
    this.y = y;
  }

  public DataPoint(DataPoint p) {
    this(p.x, p.y);
  }

  /** NOTE: this uses == on the members. For a more practical
   * <code>equals</code>, use one of the <code>fuzzyEquals</code>
   * methods.
   */
  @Override
  public boolean equals(Object obj) {
    if(!(obj instanceof DataPoint))
      return false;

    DataPoint p = (DataPoint)obj;

    return (x == p.x && y == p.y);
  }

  /** @return Returns <code>true</code> iff the distance between the current
   * point and <code>p</code> is less than <code>epsilon</code>.
   */
  public boolean fuzzyEquals(DataPoint p, double epsilon) {
    double dx = p.x - x;
    double dy = p.y - y;

    return( Math.sqrt(dx*dx + dy*dy) < epsilon);
  }

  @Override
  public String toString() {
    return "[DataPoint: x: " + x + "; y: " + y;
  }
}
