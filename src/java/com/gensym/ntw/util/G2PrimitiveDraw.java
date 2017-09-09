package com.gensym.ntw.util;

import java.awt.*;
import com.gensym.util.*;
//import com.gensym.irm.*;
import com.gensym.icons.PointOrArcPoint;

/**
 * <b>SYNOPSIS:</b><p>
 */

public class G2PrimitiveDraw {
  
  private static final Symbol SMALL_ = Symbol.intern ("SMALL");
  private static final Symbol LARGE_ = Symbol.intern ("LARGE");

  public static final int scale_constant = 1000;
  
  public static int G2FontSize(Symbol g2_font) {
    if (g2_font.equals(SMALL_))
      return 14;
    else if (g2_font.equals(LARGE_))
      return 18;
    else
      return 24;
  }

  private static int Scale(int value,int scale) {
    return (int) (value*scale)/scale_constant;
  }
    
  private static float[] Midpoint(Point point1, Point point2) {
    float[] midpoint = new float[2];
    midpoint[0] = ((float)(point1.x + point2.x) / 2);
    midpoint[1] = ((float)(point1.y + point2.y) / 2);
    return midpoint;
  }

  private static float Slope(Point point1, Point point2) {
    float dy = (float)(point1.y - point2.y);
    float dx = (float)(point1.x - point2.x);
    return dy/dx;
  }

  public static float[] IntersectLines(float[] p1, float m1,
				       float[] p2, float m2) {
    float dm = m1 - m2;
    if (Float.compare(dm, 0.0f) != 0) { //if not parallel
      float x1 = p1[0];
      float y1 = p1[1];
      float x2 = p2[0];
      float y2 = p2[1];
      if (Float.compare(x1, x2) == 0 && Float.compare(y1, y2) == 0) 
    	  return p1;
      float[] intersection = new float[2];
      float b1 = y1 - m1*x1;
      float b2 = y2 - m2*x2;
      float x = (b2 - b1)/dm;
      float y = m1*x + b1;
      intersection[0] = x;
      intersection[1] = y;
      return intersection;
    } else
      return null;
  }
  
  private static float[] CalculateCenterofCircle(Point p1, Point p2, Point p3) {
    float[] mp1 = Midpoint(p1, p2); 
    float[] mp2 = Midpoint(p2, p3);
    float m1 =  Slope(p1,p2); 
    float m2 =  Slope(p2, p3);
    float[] center = null;
    if (Float.compare(m1, 0.0f) == 0 && Float.compare(m2, 0.0f) == 0)//its really a line then
      center = new float[] {mp1[0], mp2[0]};
    else if (Float.compare(m1, 0.0f) == 0) {//know the value of x;plugging into equation for other line
      center = new float[]{mp1[0], - mp1[0]/m2 + mp2[1] + mp2[0]/m2};
    } else if (Float.compare(m2, 0.0f) == 0)//know the value of x;plugging into equation for other line
      center = new float[]{mp2[0], - mp2[0]/m1 + mp1[1] + mp1[0]/m1};
    else 
      center = IntersectLines(mp1, -1/m1, mp2, -1/m2);
    return center;
  }

  public static void Point(Point point,int xs, int ys, 
			   Graphics g) {
    g.drawLine(Scale(point.x, xs), Scale(point.y, ys),
	       Scale(point.x, xs), Scale(point.y, ys));
  }

  private static void drawArc(Point p1, Point p2, Point p3,
			      int xs, int ys,
			      Graphics g) {
    float[] fcenter = CalculateCenterofCircle(p1, p2, p3);
    if (fcenter != null) {
      if ((int)fcenter[0] == p1.x && (int)fcenter[1] == p1.y) {
    	  Point(p1, xs, ys, g); 
    	  return;
      }
      int x0 = (int) fcenter[0]; 
      int y0 = (int) fcenter[1];
      int radius_x = p2.x - x0;
      int radius_y = p2.y - y0;
      if (radius_x < 0){
    	  radius_x = -radius_x;
      }
      if (radius_y < 0){
    	  radius_y = -radius_y;
      }
      float fradius = (float) Math.sqrt(((double)(radius_x*radius_x)) + radius_y*radius_y);
      int radius = (int) fradius;
      int left = x0 - radius; 
      int top = y0 - radius;
      int sleft = Scale(left,xs); 
      int stop = Scale(top, ys);
      int x_radius = Scale(radius,xs); 
      int y_radius = Scale(radius, ys);
      int startAngle = (int) (180*Math.atan2(-(((double)p1.y) - y0), ((double)p1.x) - x0)/Math.PI);
      if (startAngle < 0)
	startAngle+=360;
      int middleAngle = (int) (180*Math.atan2(-(((double)p2.y) - y0), ((double)p2.x) - x0)/Math.PI);
      if (middleAngle < 0)
	middleAngle+=360;
      int endAngle = (int) (180*Math.atan2(-(((double)p3.y) - y0), ((double)p3.x) - x0)/Math.PI);
      if (endAngle < 0)
	endAngle+=360;
      if (endAngle < startAngle)
	endAngle+=360;
      int arcAngle = endAngle - startAngle;
      if (middleAngle < startAngle || middleAngle > endAngle) {
	arcAngle = (arcAngle - 360);
      }
      //System.out.println("LT == " + left +","+top+ "radius="+radius);
      //System.out.println("p1 = " + p1 + "p3 = " + p3 + " center = " + x0 + "," + y0);
      //System.out.println("SA = " + startAngle + " aA = " + arcAngle + "EA = " + endAngle);      
      g.drawArc(sleft, stop, (2*x_radius)-1, (2*y_radius)-1, startAngle, arcAngle);
    }
  }
			      
  public static void Lines(Point[] points,int xs, int ys,
			   Graphics g) {
    // need to check if it is an arc, ie contains arc-points
    int linecount = (points.length - 1);
    Point p1, p2, p3;
    for (int i = 0; i<linecount; i++) {
      p1 = points[i]; 
      p2 = points[i + 1];
      if (p2 instanceof PointOrArcPoint && ((PointOrArcPoint)p2).arcPoint) {
	p3 = points[i + 2];
	drawArc(p1, p2, p3, xs, ys, g);
	i++;
      } else 
	g.drawLine(Scale(p1.x, xs), Scale(p1.y, ys),
		   Scale(p2.x, xs), Scale(p2.y, ys));
    }
  }

  public static void Circle(Point[] points,int xs, int ys, 
			    Graphics g, boolean filled) {
    if (points!=null && points.length == 3) {
      Point p0 = points[0];
      float[] fcenter = CalculateCenterofCircle(p0, points[1], points[2]);
      if (fcenter != null) {
	int x0 = (int) fcenter[0]; 
	int y0 = (int) fcenter[1];
	if (x0 == p0.x && y0 == p0.y) {
	  Point(p0, xs, ys, g); 
	  return;
	}
	int radius_x = points[1].x - x0;
	int radius_y = points[1].y - y0;
	if (radius_x < 0) {
		radius_x = -radius_x;
	}
	if (radius_y < 0) {
		radius_y = -radius_y;
	}
	float fradius = (float) Math.sqrt(((double)(radius_x*radius_x)) + radius_y*radius_y);
	int radius = (int) fradius;
	int left = x0 - radius; 
	int top = y0 - radius;
	int sleft = Scale(left,xs); 
	int stop = Scale(top, ys);
	int x_radius = Scale(radius,xs); 
	int y_radius = Scale(radius, ys);
	if (filled)
	  g.fillOval(sleft, stop, 2* x_radius, 2*y_radius);
	else
	  g.drawOval(sleft, stop, (2*x_radius)-1, (2*y_radius)-1);
      }
    }
  }
  
  public static void Rectangle(Point[] points,int xs, int ys,
			       Graphics g, boolean filled) {
     int x1,y1, x2,y2, temp;
     x1 = points[0].x; 
     x2 = points[1].x;
     if (x2 < x1) {
    	 temp = x1; 
    	 x1 = x2; 
    	 x2 = temp;
     }
     y1 = points[0].y; 
     y2 = points[1].y;
     if (y2 < y1) {
    	 temp = y1; 
    	 y1 = y2; 
    	 y2 = temp;
     }
     
     x1 = Scale(x1, xs); 
     x2 = Scale(x2, xs);
     y1 = Scale(y1, ys); 
     y2 = Scale(y2, ys);
     int width = 1 + x2 - x1; 
     int height = 1 + y2 - y1;
     if (filled)
       g.fillRect(x1, y1, width, height);     
     else
       g.drawRect(x1, y1, width, height);
  }

  public static void Polygon(Point[] points,int xs, int ys,
			     Graphics g, boolean filled) {
    int count = points.length;
    int[] x_array = new int[count];
    int[] y_array = new int[count];
    for (int i = 0; i<count; i ++) {
      x_array[i]=Scale(points[i].x, xs);
      y_array[i]=Scale(points[i].y, ys);
    }
    if (filled)
      g.fillPolygon(x_array,y_array,count);
    else
      g.drawPolygon(x_array,y_array,count);
  }

  public static void Outline(Point[] points,int xs, int ys, 
			     Graphics g, boolean filled) {
    if (filled)
      Polygon(points,xs, ys, g, true);
    else {
      int length = points.length;
      Point[] outlinePoints = new Point[length+1];
      System.arraycopy(points, 0, outlinePoints, 0, length);
      outlinePoints[length]=outlinePoints[0];
      Lines(outlinePoints, xs, ys, g);
    }
  }
  
  public static void Text(String label, Point p, Symbol g2_font,
			  int xs, int ys, 
			  Graphics g) {
    Font font = G2FontMap.get(g2_font);
    Text(label, p, font, xs, ys, g);
  }

  public static void Text(final String label, final Point p, final Font font,
			  final int xs, final int ys, 
			  final Graphics g) {
    int fontSize = font.getSize();
    fontSize=Math.max(1,Scale(fontSize, Math.min(xs, ys)));
    Font fontLocal = G2FontMap.get(fontSize);
    g.setFont(fontLocal);
    g.drawString(label,Scale(p.x,xs), Scale(p.y,ys));
  }
  
  public static void Image(final Image image, Point p,
			   Graphics g,
			   boolean polychrome) {
    g.drawImage(image, p.x, p.y, null);
  }
}
