package com.gensym.draw;

import java.awt.*;

/*
 *
 * Segment (of an othogonal connection)
 *
 */

public class Segment extends Object implements java.io.Serializable
{

  static final long serialVersionUID = 2390948605044211229L;

  public static final int NO_HEADING = 0;
  public static final int LEFT = 1;
  public static final int TOP = 2;
  public static final int RIGHT = 3;
  public static final int BOTTOM = 4;

  protected boolean isHorizontal = false;
  /**
   * NOTE: left, top, right, and bottom are all misnamed.
   * They should really be called startX, startY, endX, and endY
   * respectively (at least for diagonal connections).
   * If left, top, etc. are changed to actually
   * mean what their names imply, ConnectionElement.drawArrowsForDiagonalSegment
   * will break.
   * @undocumented
   */
  protected int left;
  protected int top;
  protected int right;
  protected int bottom;
  protected int heading = NO_HEADING;


  public int getHeading() {
    return heading;
  }

  // NOTE this "contains" method assumes that heading == NO_HEADING
  // and "segment is diagonal" are equivalent.
  // If diagonal segments were ever to have thickness, this must
  // be re-written. It could be written in a more general way.

  public boolean contains(int x, int y)
  {
    float[] p1 = {0,0}, p2 = {0,0}, p3 = {0,0};    
    int buffer = 4;
    int dy = bottom - top;
    int dx = right - left;
    float xDistance = 10000;
    float yDistance = 10000;
    // distance from point to orthogonally-oriented-rectangle
    if (heading != NO_HEADING) {

      if (Math.min(top, bottom)<=y &&
	  y<=(Math.max(top, bottom)))
	yDistance = 0;
      else
	yDistance = Math.min(Math.abs((y-top)),
			     Math.abs((y-bottom)));

      if (Math.min(left, right)<=x &&
	  x<=(Math.max(left, right)))
	xDistance = 0;
      else
	xDistance = Math.min(Math.abs((x-left)),
			     Math.abs((x-right)));      
    } else {
      // point to line distance
      if (dx == 0) {
	xDistance = Math.abs(x-left);
	if (Math.min(top, bottom)<=y &&
	    y<=(Math.max(top, bottom)))
	  yDistance = 0;
	else
	  yDistance = Math.min(Math.abs((y-top)),
			       Math.abs((y-bottom)));
      } else if (dy == 0) {
	yDistance = Math.abs(y-top);
	if (Math.min(left, right)<=x &&
	    x<=(Math.max(left, right)))
	  xDistance = 0;
	else
	  xDistance = Math.min(Math.abs((x-left)),
			       Math.abs((x-right)));      
      } else {   
	p1[0] = left; p1[1] = top;
	p2[0] = right; p2[1] = bottom;
	p3[0] = x; p3[1] = y;
	float m1 = (((float)dy)/dx);    
	float m2 = -1/m1;
	float[] intersection
	  = com.gensym.ntw.util.G2PrimitiveDraw.IntersectLines(p1, m1, p3, m2);
	if (Math.min(left,right)-buffer<=intersection[0] &&
	    intersection[0] <= Math.max(left,right)+buffer &&
	    Math.min(top, bottom)-buffer <=intersection[1] &&
	    intersection[1] <= buffer + Math.max(top,bottom)) {
	  xDistance = (x - intersection[0]);
	  yDistance = (y - intersection[1]);
	}
      }
    }
    int distance = (int)Math.sqrt(xDistance*xDistance + yDistance*yDistance);

    return distance <= buffer;
  }

  /**
   * NOTE: left, top, right, and bottom are all misnamed.
   * They should really be called startX, startY, endX, and endY
   * respectively. If left, top, etc. are changed to actually
   * mean what their names imply, ConnectionElement.drawArrowsForDiagonalSegment
   * will break.
   * @undocumented
   */
  public Segment(boolean isHorizontal,
		 int left, int top, int right, int bottom,
		 int heading)
  {
    this.isHorizontal = isHorizontal;
    this.left = left;
    this.top = top;
    this.right = right;
    this.bottom = bottom;
    this.heading = heading;
  }

  @Override
  public String toString()
  {
    return "("+left+","+top+","+right+","+bottom+
      ") horizontal?:"+isHorizontal+" heading:"+heading;
    
  }

}
