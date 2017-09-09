/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ItemLayoutTools.java
 *
 */
package com.gensym.ntw.util.uitools;

import java.lang.reflect.Method;

import com.gensym.classes.Item;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.util.Sorter;
import com.gensym.util.SorterSupport;

/**
 *  This class contains several convenience methods for adjusting the layout
 *  of com.gensym.classes.Items on a WorkspaceView.
 */
public class ItemLayoutTools {

  public static final int ALIGN_LEFTS   = 0;
  public static final int ALIGN_CENTERS = 1;
  public static final int ALIGN_RIGHTS  = 2;
  public static final int ALIGN_TOPS    = 3;
  public static final int ALIGN_MIDDLES = 4;
  public static final int ALIGN_BOTTOMS = 5;

  public static final int DISTRIBUTE_HORIZONTALLY = 20;
  public static final int DISTRIBUTE_VERTICALLY   = 21;

  private static Class thisClass = com.gensym.ntw.util.uitools.ItemLayoutTools.class;
  private static Class[] args = new Class[]{com.gensym.classes.Item.class, com.gensym.classes.Item.class};
  private static Method compareXMethod;
  private static Method compareYMethod;

  static {
    try {
      compareXMethod = thisClass.getMethod("compareX", args);
      compareYMethod = thisClass.getMethod("compareY", args);
    }
    catch(NoSuchMethodException nsme) {
      Trace.exception(nsme);
    }
  }

  /**
   *  Aligns the com.gensym.classes.Items in <code>itemsToAlign</code> according to the
   *  specified <code>alignmentCode</code>.  <code>alignmentCode</code> may be
   *  either ALIGN_LEFTS, ALIGN_CENTERS, ALIGN_RIGHTS, ALIGN_TOPS, ALIGN_MIDDLES,
   *  or ALIGN_BOTTOMS.  The first item in the array is used as the reference
   *  component.
   */
  public static void align(Item[] itemsToAlign, int alignmentCode) throws G2AccessException {
    int len = itemsToAlign.length;
    if (len < 2) return;
    int x, y, width, height;
    switch (alignmentCode){
    case ALIGN_LEFTS:
      x = itemsToAlign[0].getItemXPosition();
      width = itemsToAlign[0].getItemWidth();
      int leftX = x - width/2;
      for (int i=1; i<len; i++){
	x = leftX + itemsToAlign[i].getItemWidth()/2;
	y = itemsToAlign[i].getItemYPosition();
	itemsToAlign[i].move(x, y, true); 
      }
      break;

    case ALIGN_CENTERS:
      x = itemsToAlign[0].getItemXPosition();
      for (int i=1; i<len; i++){
	y = itemsToAlign[i].getItemYPosition();
	itemsToAlign[i].move(x, y, true);
      }
      break;

    case ALIGN_RIGHTS:
      x = itemsToAlign[0].getItemXPosition();
      width = itemsToAlign[0].getItemWidth();
      int rightX = x + width/2;
      for (int i=1; i<len; i++){
	x = rightX - itemsToAlign[i].getItemWidth()/2;
	y = itemsToAlign[i].getItemYPosition();
	itemsToAlign[i].move(x, y, true);
      }
      break;

    case ALIGN_TOPS:
      y = itemsToAlign[0].getItemYPosition();
      height = itemsToAlign[0].getItemHeight();
      int topY = y + height/2;
      for (int i=1; i<len; i++){
	x = itemsToAlign[i].getItemXPosition();
	y = topY - itemsToAlign[i].getItemHeight()/2;
	itemsToAlign[i].move(x, y, true);
      }
      break;
      
    case ALIGN_MIDDLES:
      y = itemsToAlign[0].getItemYPosition();
      for (int i=1; i<len; i++){
	x = itemsToAlign[i].getItemXPosition();
	itemsToAlign[i].move(x, y, true);
      }
      break;
  
    case ALIGN_BOTTOMS:
      y = itemsToAlign[0].getItemYPosition();
      height = itemsToAlign[0].getItemHeight();
      int bottomY = y - height/2;
      for (int i=1; i<len; i++){
	x = itemsToAlign[i].getItemXPosition();
	y = bottomY + itemsToAlign[i].getItemHeight()/2;
	itemsToAlign[i].move(x, y, true);
      }
      break;
    }
  }

 
  /**
   *  Comparison method used for sorting com.gensym.classes.Items by x-coordinate.
   *  @see com.gensym.util.Sorter
   */
  public static int compareX(Item c1, Item c2) throws G2AccessException {
    if (c1.getItemXPosition() == c2.getItemXPosition()) return SorterSupport.EQUAL;
    else if (c1.getItemXPosition() < c2.getItemXPosition()) return SorterSupport.LESS_THAN;
    else return SorterSupport.GREATER_THAN;
  }

  /**
   *  Comparison method used for soring com.gensym.classes.Items by y-coordinate.
   *  @see com.gensym.util.Sorter
   */
  public static int compareY(Item c1, Item c2) throws G2AccessException {
    if (c1.getItemYPosition() == c2.getItemYPosition()) return SorterSupport.EQUAL;
    else if (c1.getItemYPosition() < c2.getItemYPosition()) return SorterSupport.LESS_THAN;
    else return SorterSupport.GREATER_THAN;
  }

  /**
   *  Distributes the com.gensym.classes.Items in <code>itemsToDistribute</code> according to 
   *  the specified <code>distributionCode</code>.  <code>distributionCode</code> may
   *  be either DISTRIBUTE_HORIZONTALLY or DISTRIBUTE_VERTICALLY. For horizontal
   *  distribution, the items are evenly spaced between the minimum and
   *  maximum x-coordinates.  For vertical distribution, the items are evenly 
   *  spaced between the minimum and maximum y-coordinates.
   */
  public static void distribute(Item[] itemsToDistribute, int distributionCode) throws G2AccessException {
    int len = itemsToDistribute.length;
    //if (len < 3) return;

    switch (distributionCode){
    case DISTRIBUTE_HORIZONTALLY:
      Sorter.sort(itemsToDistribute, Sorter.ASCENDING, compareXMethod);
      int totalWidth = 0;
      for (int i=0; i < len - 1; i++)
	totalWidth = totalWidth + itemsToDistribute[i].getItemWidth();
      int firstX = itemsToDistribute[0].getItemXPosition() - itemsToDistribute[0].getItemWidth()/2;
      int hSpacing = (itemsToDistribute[len - 1].getItemXPosition() - 
		      itemsToDistribute[len -1].getItemWidth()/2 - firstX - totalWidth) / (len - 1);
      int previousX = firstX + itemsToDistribute[0].getItemWidth();
      for (int i=1; i<len; i++) {
	itemsToDistribute[i].move(previousX + hSpacing + itemsToDistribute[i].getItemWidth()/2, 
				  itemsToDistribute[i].getItemYPosition(), true);
	previousX = previousX + hSpacing + itemsToDistribute[i].getItemWidth();
      }
      break;

    case DISTRIBUTE_VERTICALLY:
      Sorter.sort(itemsToDistribute, Sorter.DESCENDING, compareYMethod);
      int totalHeight = 0;
      for (int i=0; i < len - 1; i++)
	totalHeight = totalHeight + itemsToDistribute[i].getItemHeight();
      int firstY = itemsToDistribute[0].getItemYPosition() + itemsToDistribute[0].getItemHeight()/2;
      int vSpacing = (firstY - (itemsToDistribute[len - 1].getItemYPosition() + 
		      itemsToDistribute[len - 1].getItemHeight()/2) - totalHeight) / (len - 1);
      int previousY = firstY - itemsToDistribute[0].getItemHeight();
      for (int i=1; i<len; i++) {
	itemsToDistribute[i].move(itemsToDistribute[i].getItemXPosition(), 
				  previousY - vSpacing - itemsToDistribute[i].getItemHeight()/2, true);
	previousY = previousY - vSpacing - itemsToDistribute[i].getItemHeight();
      }
      break;
    }
  }
}
