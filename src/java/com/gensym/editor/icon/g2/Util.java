package com.gensym.editor.icon.g2;

import java.awt.*;
import com.gensym.util.*;

public class Util
{
  public static final Symbol X_ = Symbol.intern ("X");
  public static final Symbol Y_ = Symbol.intern ("Y");
  public static final Symbol TYPE_ = Symbol.intern ("TYPE");
  public static final Symbol LABEL_ = Symbol.intern ("LABEL");
  public static final Symbol SMALL_ = Symbol.intern ("SMALL");
  public static final Symbol LARGE_ = Symbol.intern ("LARGE");
  public static final Symbol EXTRA_LARGE_ = Symbol.intern ("EXTRA-LARGE");
  public static final Symbol FONT_SIZE_ = Symbol.intern ("FONT-SIZE");
  public static final Symbol IMAGE_NAME_ = Symbol.intern ("IMAGE-NAME");
  public static final Symbol POINTS_ = Symbol.intern ("POINTS");

  public static final Symbol WIDTH_ = Symbol.intern ("WIDTH");
  public static final Symbol HEIGHT_ = Symbol.intern ("HEIGHT");
  public static final Symbol REGIONS_ = Symbol.intern ("REGIONS");
  public static final Symbol VARIABLES_ = Symbol.intern ("VARIABLES");
  public static final Symbol ICON_BACKGROUND_LAYER_ = Symbol.intern ("ICON-BACKGROUND-LAYER");
  public static final Symbol REGION_OR_COLOR_ = Symbol.intern ("REGION-OR-COLOR");
  public static final Symbol LINE_DRAWING_ELEMENTS_ = Symbol.intern ("LINE-DRAWING-ELEMENTS");
  public static final Symbol LAYERS_ = Symbol.intern ("LAYERS");
  
  public static final int CIRCLE = 0;
  public static final int LINES = 1;
  public static final int OUTLINE = 2;
  public static final int FILLED_RECTANGLE = 4;
  public static final int POINT = 5;
  public static final int FILLED_POLYGON = 6;
  public static final int MONOCHROME_IMAGE = 7;
  public static final int TEXT = 8;
  public static final int FILLED_CIRCLE = 9;
  
  public static final Symbol CIRCLE_ = Symbol.intern("CIRCLE");
  public static final Symbol FILLED_CIRCLE_ = Symbol.intern ("FILLED-CIRCLE");
  public static final Symbol LINES_ = Symbol.intern("LINES");
  public static final Symbol OUTLINE_ = Symbol.intern ("OUTLINE");
  public static final Symbol FILLED_RECTANGLE_ = Symbol.intern ("FILLED-RECTANGLE");
  public static final Symbol POINT_ = Symbol.intern ("POINT");
  public static final Symbol FILLED_POLYGON_ = Symbol.intern ("FILLED-POLYGON");
  public static final Symbol IMAGE_ = Symbol.intern ("IMAGE");
  public static final Symbol TEXT_ = Symbol.intern ("TEXT");

  public static Symbol mapTypeToDescriptionType(int type)
  {
    Symbol descriptionType = null;
    switch(type) {
    case CIRCLE: descriptionType = CIRCLE_; break;
    case FILLED_CIRCLE: descriptionType = FILLED_CIRCLE_; break;
    case LINES: descriptionType = LINES_; break;
    case OUTLINE: descriptionType = OUTLINE_; break;
    case FILLED_RECTANGLE: descriptionType = FILLED_RECTANGLE_; break;
    case POINT: descriptionType = POINT_; break;
    case FILLED_POLYGON: descriptionType = FILLED_POLYGON_; break;
    case MONOCHROME_IMAGE: descriptionType = IMAGE_; break;
    case TEXT: descriptionType = TEXT_; break;
    }
    return descriptionType;
  }

  public static Sequence createPointsSequence(Object[][] points)
  {
    int count = points.length;
    Sequence sequence = new Sequence(count);
    for (int i=0;i<count;i++) {
      sequence.addElement(createPointStructure(points[i]));
    }
    return sequence;
  }

  public static Sequence createPointsSequence(Object[] points)
  {
    int count = points.length;
    Sequence sequence = new Sequence(count/2);
    for (int i=0;i<count;i+=2) {
      sequence.addElement(createPointStructure(points[i], points[i+1]));
    }
    return sequence;
  }
  
  public static Sequence createPointsSequence(int[] xPoints, int[] yPoints)
  {
    int count = xPoints.length;
    Sequence sequence = new Sequence(count);
    for (int i=0;i<count;i++) {
      sequence.addElement(createPointStructure(new Integer(xPoints[i]),
					       new Integer(yPoints[i])));
    }
    return sequence;
  }

  public static Structure createPointStructure(Object x, Object y)
  {
    if (x instanceof PointExpression)
      x = x.toString();
    if (y instanceof PointExpression)
      y = y.toString();            
    Structure pointStruct = new Structure();
    pointStruct.setAttributeValue(X_, x);
    pointStruct.setAttributeValue(Y_, y);
    return pointStruct;
  }
  
  public static Structure createPointStructure(Object[] point)
  {
    return createPointStructure(point[0], point[1]);
  }

  public static Symbol mapFontToG2Font(Font font)
  {
    //PBK FINISH THIS
    return LARGE_;
  }

  public static Symbol mapImageToImageName(Image image)
  {
    return Symbol.intern("IMAGES-NOT-SUPPORTED-YET");
  }

  public static Object[] threePointsOnCircle(Object centerX,
					     Object centerY,
					     Object radius)
  {
    Object x0 = centerX+" - "+radius;
    Object y1 = centerY+" + "+radius;    
    Object x2 = centerX+" + "+radius;
    if (radius instanceof Number) {
      if (centerX instanceof Number) {
	x0 = new Integer(((Number)centerX).intValue() - ((Number)radius).intValue());
	x2 = new Integer(((Number)centerX).intValue() + ((Number)radius).intValue());
      }
      if (centerY instanceof Number)
	y1 = new Integer(((Number)centerY).intValue() + ((Number)radius).intValue());
    }
    
    Object[] threePoints = {x0, centerY, centerX,y1, x2,centerY};
    return threePoints;
  }

  public static Point[] pointsRectangle(Point location, int width, int height)
  {
    Point[] rect = {location, new Point(location.x+width,
					location.y+height)};
    return rect;
  }
}
