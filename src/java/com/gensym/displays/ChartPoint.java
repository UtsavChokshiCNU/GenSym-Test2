/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ChartPoint.java
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

/** ChartPoints keep both the abstract, data, representation and the
 * visual co-ordinates of that representation.
 * <p>
 * NOTE, the dataPoint and devicePoint are both <code>final</code> in full
 * realization that they can be transformed directly
 * @author Robert Penny
 * @version 1.0
 * @undocumented
 * @deprecated this class is no longer used.
 */

public class ChartPoint {
  private DataPoint dataPoint;
  private Point devicePoint;

  public ChartPoint(DataPoint dataPoint, Point devicePoint) {
    this.dataPoint = dataPoint;
    this.devicePoint = devicePoint;
  }

  @Override
  public String toString() {
    return "[ChartPoint: dataPoint: " + dataPoint + "; devicePoint: " +
      devicePoint;
  }

  public DataPoint getDataPoint() {
    return dataPoint;
  }

  public Point getDevicePoint() {
    return devicePoint;
  }
}
