package com.gensym.uiutil;

import java.awt.Component;
import java.awt.Point;
import java.lang.reflect.Method;
import com.gensym.core.util.QuickSorter;

/**
 *  This class contains several convenience methods for adjusting the layout
 *  of components in a container with no layout manager.
 */
public class LayoutTools{

  public static final int ALIGN_LEFTS = 0;
  public static final int ALIGN_CENTERS = 1;
  public static final int ALIGN_RIGHTS = 2;
  public static final int ALIGN_TOPS = 3;
  public static final int ALIGN_MIDDLES = 4;
  public static final int ALIGN_BOTTOMS = 5;

  public static final int MAKE_SAME_SIZE_WIDTH = 10;
  public static final int MAKE_SAME_SIZE_HEIGHT = 11;
  public static final int MAKE_SAME_SIZE_BOTH = 12;

  public static final int DISTRIBUTE_HORIZONTALLY = 20;
  public static final int DISTRIBUTE_VERTICALLY = 21;

  private static Class thisClass = com.gensym.uiutil.LayoutTools.class;
  private static Class[] args = new Class[]{java.awt.Component.class, java.awt.Component.class};
  private static Method compareXMethod;
  private static Method compareYMethod;

  static{
    try{
      compareXMethod = thisClass.getMethod("compareX", args);
      compareYMethod = thisClass.getMethod("compareY", args);
    }
    catch(NoSuchMethodException ex){
      com.gensym.message.Trace.exception(ex);
    }
  }

  /**
   *  Aligns the components in <code>componentsToAlign</code> according to the
   *  specified <code>alignmentCode</code>.  <code>alignmentCode</code> may be
   *  either ALIGN_LEFTS, ALIGN_CENTERS, ALIGN_RIGHTS, ALIGN_TOPS, ALIGN_MIDDLES,
   *  or ALIGN_BOTTOMS.  The first component in the array is used as the reference
   *  component.
   */
  public static void align(Component[] componentsToAlign, int alignmentCode){
    int len = componentsToAlign.length;
    if (len < 2) return;
    int x, y, width, height;
    switch (alignmentCode){
    case ALIGN_LEFTS:
      x = componentsToAlign[0].getLocation().x;
      for (int i=1; i<len; i++){
	Point newLocation = new Point(x, componentsToAlign[i].getLocation().y);
	componentsToAlign[i].setLocation(newLocation);
      }
      break;

    case ALIGN_CENTERS:
      x = componentsToAlign[0].getLocation().x;
      width = componentsToAlign[0].getSize().width;
      int centerX = x + width/2;
      for (int i=1; i<len; i++){
	Point newLocation = new Point(centerX - (componentsToAlign[i].getSize().width/2), componentsToAlign[i].getLocation().y);
	componentsToAlign[i].setLocation(newLocation);
      }
      break;

    case ALIGN_RIGHTS:
      x = componentsToAlign[0].getLocation().x;
      width = componentsToAlign[0].getSize().width;
      int rightX = x + width;
      for (int i=1; i<len; i++){
	Point newLocation = new Point(rightX - componentsToAlign[i].getSize().width, componentsToAlign[i].getLocation().y);
	componentsToAlign[i].setLocation(newLocation);
      }
      break;

    case ALIGN_TOPS:
      y = componentsToAlign[0].getLocation().y;
      for (int i=1; i<len; i++){
	Point newLocation = new Point(componentsToAlign[i].getLocation().x, y);
	componentsToAlign[i].setLocation(newLocation);
      }
      break;
      
    case ALIGN_MIDDLES:
      y = componentsToAlign[0].getLocation().y;
      height = componentsToAlign[0].getSize().height;
      int centerY = y + height/2;
      for (int i=1; i<len; i++){
	Point newLocation = new Point(componentsToAlign[i].getLocation().x, centerY - (componentsToAlign[i].getSize().height/2));
	componentsToAlign[i].setLocation(newLocation);
      }
      break;
  
    case ALIGN_BOTTOMS:
      y = componentsToAlign[0].getLocation().y;
      height = componentsToAlign[0].getSize().height;
      int bottomY = y + height;
      for (int i=1; i<len; i++){
	Point newLocation = new Point(componentsToAlign[i].getLocation().x, bottomY - componentsToAlign[i].getSize().height);
	componentsToAlign[i].setLocation(newLocation);
      }
      break;
    }
  }

  /**
   *  Resizes the components in <code>componentsToSize</code> according to the
   *  specified <code>sizingCode</code>.  <code>sizingCode</code> may be
   *  either MAKE_SAME_SIZE_WIDTH, MAKE_SAME_SIZE_HEIGHT, or
   *  MAKE_SAME_SIZE_BOTH.  The first component in the array is used as the reference
   *  component.
   */
  public static void size(Component[] componentsToSize, int sizingCode){
    int len = componentsToSize.length;
    if (len < 2) return;
    
    int width, height;
    switch (sizingCode){
    case MAKE_SAME_SIZE_WIDTH:
      width = componentsToSize[0].getSize().width;
      for (int i=1; i<len; i++)
	componentsToSize[i].setSize(width, componentsToSize[i].getSize().height);
      break;

    case MAKE_SAME_SIZE_HEIGHT:
      height = componentsToSize[0].getSize().height;
      for (int i=1; i<len; i++)
	componentsToSize[i].setSize(componentsToSize[i].getSize().width, height);
      break;

    case MAKE_SAME_SIZE_BOTH:
      width = componentsToSize[0].getSize().width;
      height = componentsToSize[0].getSize().height;
      for (int i=1; i<len; i++)
	componentsToSize[i].setSize(width, height);
      break;
    }
  }

  /**
   *  Comparison method used for sorting components by x-coordinate.
  public static int compareX(Component c1, Component c2){
    if (c1.getLocation().x == c2.getLocation().x) return SorterSupport.EQUAL;
    else if (c1.getLocation().x < c2.getLocation().x) return SorterSupport.LESS_THAN;
    else return SorterSupport.GREATER_THAN;
  }

  /**
   *  Comparison method used for soring components by y-coordinate.
  public static int compareY(Component c1, Component c2){
    if (c1.getLocation().y == c2.getLocation().y) return SorterSupport.EQUAL;
    else if (c1.getLocation().y < c2.getLocation().y) return SorterSupport.LESS_THAN;
    else return SorterSupport.GREATER_THAN;
  }
   */

  static class LocationSorter extends QuickSorter {
    public static final int X = 0, Y = 1;
    private int coordinate;
    LocationSorter (int coordinate) {
      this.coordinate = coordinate;
    }
    @Override
    public boolean lessThan(Object a, Object b) {
      int coord1 = (coordinate == X ?
		    ((Component)a).getLocation().x : ((Component)a).getLocation().y);
      int coord2 = (coordinate == X ?
		    ((Component)b).getLocation().x : ((Component)b).getLocation().y);
      return coord1 < coord2;
    }
  }

  /**
   *  Distributes the components in <code>componentsToDistribute</code> according to 
   *  the specified <code>distributionCode</code>.  <code>distributionCode</code> may
   *  be either DISTRIBUTE_HORIZONTALLY or DISTRIBUTE_VERTICALLY. For horizontal
   *  distribution, the components are evenly spaced between the minimum and
   *  maximum x-coordinates.  For vertical distribution, the components are evenly 
   *  spaced between the minimum and maximum y-coordinates.
   */
  public static void distribute(Component[] componentsToDistribute, int distributionCode){
    int len = componentsToDistribute.length;
    if (len < 3) return;
    
    switch (distributionCode){
    case DISTRIBUTE_HORIZONTALLY:
      //Sorter.sort(componentsToDistribute, Sorter.ASCENDING, compareXMethod);
      new LocationSorter (LocationSorter.X).quickSortInPlace (componentsToDistribute);
      int totalWidth = 0;
      for (int i=0; i < len - 1; i++)
	totalWidth = totalWidth + componentsToDistribute[i].getSize().width;
      int firstX = componentsToDistribute[0].getLocation().x;
      int hSpacing = (componentsToDistribute[len - 1].getLocation().x - 
		      firstX - totalWidth) / (len - 1);
      int previousX = firstX + componentsToDistribute[0].getSize().width;
      for (int i=1; i<len; i++){
	componentsToDistribute[i].setLocation(previousX + hSpacing, componentsToDistribute[i].getLocation().y);
	previousX = previousX + hSpacing + componentsToDistribute[i].getSize().width;
      }
      break;

    case DISTRIBUTE_VERTICALLY:
      //Sorter.sort(componentsToDistribute, Sorter.ASCENDING, compareYMethod);
      new LocationSorter (LocationSorter.Y).quickSortInPlace (componentsToDistribute);
      int totalHeight = 0;
      for (int i=0; i < len - 1; i++)
	totalHeight = totalHeight + componentsToDistribute[i].getSize().height;
      int firstY = componentsToDistribute[0].getLocation().y;
      int vSpacing = (componentsToDistribute[len - 1].getLocation().y - 
		      firstY - totalHeight) / (len - 1);
      int previousY = firstY + componentsToDistribute[0].getSize().height;
      for (int i=1; i<len; i++){
	componentsToDistribute[i].setLocation(componentsToDistribute[i].getLocation().x, previousY + vSpacing);
	previousY = previousY + vSpacing + componentsToDistribute[i].getSize().height;
      }
      break;
    }
  }

}
