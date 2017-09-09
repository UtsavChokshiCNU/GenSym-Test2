/* 
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved. 
 * 
 *   ComponentSorterSupport.java 
 * 
 * 
 */ 

package com.gensym.beaneditor;

import java.awt.Point;
import java.awt.Component;

import com.gensym.util.SorterSupport;

public class ComponentSorterSupport {

  private static int horizontalFudge;
  
  public static void setHorizontalFudge(int newFudge) {
    horizontalFudge = newFudge;
  }

  private static int verticalFudge;
  
  public static void setVerticalFudge(int newFudge) {
    verticalFudge = newFudge;
  }

  private static int compareInts(int int1, int int2, int fudge) {
    int diff = int2 - int1;
    if (-fudge <= diff && diff <= fudge)
      return SorterSupport.EQUAL;

    if (int1 < int2)
      return SorterSupport.LESS_THAN;

    return SorterSupport.GREATER_THAN;
  }
    

  /** If a c1 is lower on the screen than c2, c1 is GREATER than c2,
   * regardless of relative horizontal placement. When used as a sorter,
   * this results in components being ordered left to right then top
   * to bottom.
   */
  public static int compareVerticallyFirst(Component c1, Component c2) {
    Point loc1 = c1.getLocation();
    Point loc2 = c2.getLocation();

    int compared = compareInts(loc1.y, loc2.y, verticalFudge);

    if (compared == SorterSupport.EQUAL)
      return compareInts(loc1.x, loc2.x, horizontalFudge);
    return compared;
  }

  /** If a c1 is to the right of c2, c1 is GREATER than c2,
   * regardless of relative vertical placement. When used as a sorter,
   * this results in components being ordered top
   * to bottom then left to right.
   */
  public static int compareHorizontallyFirst(Component c1, Component c2) {
    Point loc1 = c1.getLocation();
    Point loc2 = c2.getLocation();

    int compared = compareInts(loc1.x, loc2.x, horizontalFudge);

    if (compared == SorterSupport.EQUAL)
      return compareInts(loc1.y, loc2.y, verticalFudge);
    return compared;
  }
}
