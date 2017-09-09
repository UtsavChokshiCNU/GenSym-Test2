package com.gensym.icons;

import java.awt.*;
import com.gensym.util.*;
import com.gensym.ntw.util.*;
import com.gensym.draw.TextCell;
import com.gensym.draw.TextStyle;

/**
 *
 *    <b>SYNOPSIS</b><p>
 *
 */

public class Layer {
  private static final Symbol LINES_ = Symbol.intern ("LINES");
  private static final Symbol FILLED_CIRCLE_ = Symbol.intern ("FILLED-CIRCLE");
  private static final Symbol CIRCLE_ = Symbol.intern ("CIRCLE");
  private static final Symbol FILLED_RECTANGLE_ = Symbol.intern ("FILLED-RECTANGLE");
  private static final Symbol FILLED_POLYGON_ = Symbol.intern ("FILLED-POLYGON");
  private static final Symbol OUTLINE_ = Symbol.intern ("OUTLINE");
  private static final Symbol IMAGE_ = Symbol.intern ("IMAGE");
  private static final Symbol TEXT_ = Symbol.intern ("TEXT");
  private static final Symbol TYPE_ = Symbol.intern ("TYPE");

  private static final Symbol LINE_DRAWING_ELEMENTS_ = Symbol.intern ("LINE-DRAWING-ELEMENTS");
  private static final Symbol REGION_OR_COLOR_ = Symbol.intern ("REGION-OR-COLOR");
  static final Symbol POINT_ = Symbol.intern ("POINT");

  private Symbol region = null;
  // made package private for the use of "icons as plot markers"
  // in trend-charts.
  Color defaultColor;
  private Structure defaultRegions;
  private Structure regionOverrides;
  private Structure defaultVariables;
  private Structure variableOverrides;
  private DrawingElement[] linedrawingelements;
  private int elementCount;
  private boolean isdynamic = false;

  protected Layer(Structure data, Structure variables, Structure regions) {
    this.defaultVariables = variables;
    this.defaultRegions = regions;
    Symbol g2ColorOrRegion = (Symbol) data.getAttributeValue (REGION_OR_COLOR_, null);
    defaultColor = (Color) G2ColorMap.get(g2ColorOrRegion);
    if (defaultColor == null) {
      region = g2ColorOrRegion;
      defaultColor = lookupColorForRegion(region, defaultRegions);
    }
    Sequence elements
      = (Sequence) data.getAttributeValue(LINE_DRAWING_ELEMENTS_, null);
    this.linedrawingelements = castObjectArray(elements, "DrawingElement");
    init();
  }

  private DrawingElement[] castObjectArray(Sequence sequence, String classname) {
    Structure struct;
    DrawingElement newobject;
    int count = sequence.size();
    Symbol type;
    DrawingElement[] newobjects =  new DrawingElement[count];

    for (int i=0; i<count; i++) {
      struct = (Structure) sequence.elementAt (i);
      type = (Symbol) struct.getAttributeValue(TYPE_, null);

      if (type.equals (LINES_))
	newobject = new LinesElement (struct);
      else if (type.equals (FILLED_POLYGON_)) {
	newobject = new PolygonElement (struct);
	newobject.setFilled (true);
      } else if (type.equals (FILLED_RECTANGLE_)) {
	newobject = new RectangleElement (struct);
	newobject.setFilled (true);
      } else if (type.equals (OUTLINE_))
	newobject = new OutlineElement (struct);
      else if (type.equals (CIRCLE_))
	newobject = new CircleElement (struct);
      else if (type.equals (FILLED_CIRCLE_)) {
	newobject = new CircleElement (struct);
	newobject.setFilled (true);
      } else if (type.equals (TEXT_))
	newobject = new TextElement (struct);
      else if (type.equals (POINT_))
	newobject = new PointElement (struct);
      else if (type.equals (IMAGE_))
	newobject = new ImageElement (struct);
      else
	newobject = new DrawingElement (struct); //ERROR???
      
      newobjects[i] = newobject;
    }
    return newobjects;
  }
  
  private void init() {
    elementCount = linedrawingelements.length;
    this.isdynamic = ComputeifLayerisDynamic();
  }

  private boolean ComputeifLayerisDynamic() {
    DrawingElement element;
    for (int i = 0; i<elementCount;i++) {
      element = linedrawingelements[i];
      if (element.isDynamic())
	return true;
    }
    return false;
  }
  
  private Color lookupColorForRegion(Symbol region_name,
				     Structure regions) {

    if (regions != null) 
      return (Color) regions.getAttributeValue(region_name, null);
    else
      return null;
  }

  private void DrawGraphicElements(Graphics g,
				   int x_scale, int y_scale,
				   int rotationindegrees,
				   Point pivotpoint,
				   boolean reflected,
				   Structure variables,
				   Structure variableOverrides) {
    DrawingElement element;
    for (int i = 0; i < elementCount; i++) {
      element = linedrawingelements[i];
      element.Draw(g, x_scale, y_scale,
		   rotationindegrees, pivotpoint,
		   reflected,
		   variables, variableOverrides);
    }
  }

  /**
   * Updates the integer array current_extrema with the Layer's
   * maximum extents.
   */
  protected void updateRightBottomExtrema(int[] current_extrema,
					  Structure variables,
					  Structure variableOverrides) {
    DrawingElement elt;
    for (int i = 0; i<elementCount; i++) {
      elt = linedrawingelements[i];
      elt.init(variables, variableOverrides);
      elt.updateRightBottomExtrema(current_extrema);
    }
  }

  /**
   *@return true iff the Layer contains variables in any of its elements.
   */
  protected boolean isDynamic() {
    return isdynamic;
  }

  /**
   *@return true if the color is dictated by a region
   */
  public boolean hasDynamicColor() {
    return (region!=null);
  }

  /**
   *Draws layer's elements to the Graphics g using the given x_scale, y_scale
   * rotation, pivotpoint, reflection and variable overrides.
   *@see com.gensym.irm.IconRendering#setRenderingOverrides
   *@see DrawingElement#Draw
   */
  public void Draw(Graphics g,
		   int x_scale, int y_scale,
		   int rotationindegrees,
		   Point pivotpoint,
		   boolean reflected,
		   Structure regionOverrides,
		   Structure variableOverrides) {
    Color currentColor = null;
    if (regionOverrides != null && region != null)
      currentColor = lookupColorForRegion(region, regionOverrides);
    if (currentColor == null)
      currentColor = defaultColor;
    if (!G2ColorMap.TRANSPARENT.equals(currentColor)) {
      g.setColor(currentColor);
      DrawGraphicElements(g, x_scale, y_scale,
			  rotationindegrees, pivotpoint,
			  reflected,
			  defaultVariables, variableOverrides);
    }
  }
}





/**
 *
 *    <b>SYNOPSIS</b><p>
 *     - private class for storing g2 line drawing elements
 *
 *
 */

class DrawingElement {

  private static final Symbol POINTS_ = Symbol.intern ("POINTS");

  protected Point[] points;
  protected Point[] points_to_draw;
  protected int pointCount;
  protected boolean isdynamic = false;
  protected boolean filled = false;

  protected DrawingElement() {
    init();
  }

  protected DrawingElement(Point[] points) {
    this.points = points;
    pointCount = points.length;
    init();
  }
  
  protected DrawingElement(Structure data) {
    Object pointdata = data.getAttributeValue(POINTS_, null);
    if (pointdata instanceof Sequence)
      this.points = castObjectArray((Sequence) pointdata, "PowerPoint");
    else {
      if (pointdata == null)
	pointdata = data.getAttributeValue(Layer.POINT_, null);
      if (pointdata != null) {
	this.points = new PowerPoint[1];
	points[0] = new PowerPoint((Structure)pointdata);
      } else {
	this.points = new PowerPoint[0];
      }
    }
    pointCount = points.length;
    init();
  }

  private void init() {
    isdynamic = checkforDynamicElements();
  }
  
  private PowerPoint[] castObjectArray(Sequence sequence, String classname) {
    PowerPoint object;
    if (sequence != null) {
      int count = sequence.size();
      PowerPoint[] objects = new PowerPoint[count];
      Structure struct;
      for (int i=0; i<count; i++) {
	struct = (Structure) sequence.elementAt (i);
	object = new PowerPoint(struct);
	objects[i] = object;
      }
      return objects;
    }
    else 
      return null;
  }
				  
  boolean checkforDynamicElements() {
    Point point;
    for (int i = 0; i<pointCount; i++) {
      point = points[i];
      if ((point instanceof PowerPoint)&&
	  ((PowerPoint) point).isdynamic)
	return true;
    }
    return false;
  }

  void setFilled(boolean filled) {
    this.filled = filled;
  }

  private void EvaluatePoints(Point[] points,
			      Structure variables,
			      Structure overrides) {
    Point point;
    for (int i = 0; i < pointCount; i++) {
      point = points[i];
      if (point instanceof PowerPoint) 
	((PowerPoint) point).eval(variables, overrides);
    }
  }

  private void Orient(Point point, int degrees, Point pivot) {
    
    int x = point.x;  
    int y = point.y;
    int x1 = pivot.x; 
    int y1 = pivot.y;
    int w1 = x1 - x; 
    int h1 = y1 - y;
    /*    x = point.x; y = point.y;
	  newx = x*Math.cos(radians) - y*Math.sin(radians);
	  newy = x*Math.sin(radians) + y*Math.cos(radians);
	  point.x = (int) newx;
	  point.y = (int) newy;  */
    switch (degrees) {
    case 0:
      break;
    case 90:
      point.x = x1 - h1;
      point.y = y1 + w1;
      break;
    case 180:
      point.x = x1 + w1;
      point.y = y1 + h1;
      break;
    case 270:
      point.x = x1 + h1;
      point.y = y1 - w1;
      break;
    default:
    }
  }

  /**
   * reflect left/right across y-axis
   * up/down reflect:= rotate180 && left/right reflect
   */
  private void Reflect(Point point, Point x_intercept) {
    int x = point.x; 
    int x1 = x_intercept.x; 
    int w = x1 - x; 
    point.x = x1 + w;
  }

  void OrientPoints(Point[] points,int degrees, Point pivot) {
    if (degrees == 0)
      return;
    else {
      int count = points.length;
      for (int i = 0; i<count; i++) 
	Orient(points[i],degrees, pivot);
    }
  }
    
  void ReflectPoints(Point[] points, Point x_intercept) {
    int count = points.length;
    for (int i = 0; i<count; i++)
      Reflect(points[i], x_intercept);
  }
  
  protected boolean isDynamic() {
    return isdynamic;
  }

  protected void init(Structure variables,
		      Structure variableOverrides) {
    if (isdynamic)
      EvaluatePoints(points, variables, variableOverrides);
  }
  
  protected void updateRightBottomExtrema(int[] current_extrema) {
    // unless it's an image or text
    int count = points.length;
    Point point;
    for (int i = 0; i<count; i++) {
      point = points[i];
      current_extrema[0] = Math.max(point.x, current_extrema[0]);
      current_extrema[1] = Math.max(point.y, current_extrema[1]);
    }
  }
  
  /**
   * Draws the GraphicElement to the Graphics g with horizontal scaling x_scale,
   * vertical scaling y_scale, and orientation being determined by rotationindegrees
   * pivotpoint and reflected.
   * Substitudes overrides for any corresponding variables.
   *@see G2PrimitiveDraw
   */
  protected void Draw(Graphics g, int x_scale, int y_scale,
		      int rotationindegrees, Point pivotpoint,
		      boolean reflected,
		      Structure variables, Structure overrides) {
    if (isdynamic && (overrides != null || variables != null))
      EvaluatePoints(points, variables, overrides);
    if (reflected || rotationindegrees !=0) {
      points_to_draw = new PointOrArcPoint[pointCount];
      Point newPoint;
      for (int i=0;i<pointCount;i++) {
	boolean isArc = false;
	if (points[i] instanceof PowerPoint)
	  isArc = ((PowerPoint)points[i]).arcPoint;
	newPoint = new PointOrArcPoint(points[i].x, points[i].y, isArc);
	points_to_draw[i] = newPoint;
      }
    } else
      points_to_draw = points;
    if (rotationindegrees != 0)
      OrientPoints(points_to_draw, rotationindegrees, pivotpoint);
    if (reflected)
      ReflectPoints(points_to_draw, pivotpoint);
  }
}

/**
 * CircleElement
 */

class CircleElement extends DrawingElement {

  protected CircleElement(Point[] points) {
    super(points);
  }

  protected CircleElement(Structure data) {
    super(data);
  }

  /**
   * Draws a circle to the Graphics g with horizontal scaling x_scale,
   * vertical scaling y_scale, and orientation being determined by rotationindegrees
   * pivotpoint and reflected.
   * Substitudes overrides for any corresponding variables.
   *@see G2PrimitiveDraw
   */
  @Override
  protected void Draw(Graphics g, int x_scale, int y_scale,
		      int rotationindegrees, Point pivotpoint,
		      boolean reflected,
		      Structure variables, Structure overrides) {
    super.Draw(g, x_scale, y_scale,
	       rotationindegrees, pivotpoint,
	       reflected,
	       variables, overrides);
    if (filled)
      G2PrimitiveDraw.Circle(points_to_draw,x_scale, y_scale, g, true);
    else 
      G2PrimitiveDraw.Circle(points_to_draw, x_scale, y_scale, g, false);
  }
}

/**
 * PointElement
 */

class PointElement extends DrawingElement {

  protected PointElement(Point[] points) {
    super(points);
  }

  protected PointElement(Structure data) {
    super(data);
  }

  /**
   * Draws a point to the Graphics g with horizontal scaling x_scale,
   * vertical scaling y_scale, and orientation being determined by rotationindegrees
   * pivotpoint and reflected.
   * Substitudes overrides for any corresponding variables.
   *@see G2PrimitiveDraw
   */
  @Override
  protected void Draw(Graphics g, int x_scale, int y_scale,
		      int rotationindegrees, Point pivotpoint,
		      boolean reflected,
		      Structure variables, Structure overrides) {
    super.Draw(g, x_scale, y_scale,
	       rotationindegrees, pivotpoint,
	       reflected,
	       variables, overrides);
    G2PrimitiveDraw.Point(points_to_draw[0],x_scale, y_scale, g);
  }
}

/**
 * LinesElement
 */

class LinesElement extends DrawingElement {

  protected LinesElement(Point[] points) {
    super(points);
  }

  protected LinesElement(Structure data) {
    super(data);
  }

  /**
   * Draws lines to the Graphics g with horizontal scaling x_scale,
   * vertical scaling y_scale, and orientation being determined by rotationindegrees
   * pivotpoint and reflected.
   * Substitudes overrides for any corresponding variables.
   *@see G2PrimitiveDraw
   */
  @Override
  protected void Draw(Graphics g, int x_scale, int y_scale,
		      int rotationindegrees, Point pivotpoint,
		      boolean reflected,
		      Structure variables, Structure overrides) {
    super.Draw(g, x_scale, y_scale,
	       rotationindegrees, pivotpoint,
	       reflected,
	       variables, overrides);
    G2PrimitiveDraw.Lines(points_to_draw,x_scale, y_scale, g);
  }
}

/**
 * RectangleElement
 */

class RectangleElement extends DrawingElement {

  protected RectangleElement(Point[] points) {
    super(points);
  }

  protected RectangleElement(Structure data) {
    super(data);
  }

  /**
   * Draws a rectangle to the Graphics g with horizontal scaling x_scale,
   * vertical scaling y_scale, and orientation being determined by rotationindegrees
   * pivotpoint and reflected.
   * Substitudes overrides for any corresponding variables.
   *@see G2PrimitiveDraw
   */
  @Override
  protected void Draw(Graphics g, int x_scale, int y_scale,
		      int rotationindegrees, Point pivotpoint,
		      boolean reflected,
		      Structure variables, Structure overrides) {
    super.Draw(g, x_scale, y_scale,
	       rotationindegrees, pivotpoint,
	       reflected,
	       variables, overrides);
    if (filled)
      G2PrimitiveDraw.Rectangle(points_to_draw,x_scale, y_scale, g, true);
    else
      G2PrimitiveDraw.Rectangle(points_to_draw,x_scale, y_scale, g, false);
  }
}

/**
 * PolygonElement
 */

class PolygonElement extends DrawingElement {

  protected PolygonElement(Point[] points) {
    super(points);
  }

  protected PolygonElement(Structure data) {
    super(data);
  }

  /**
   * Draws a polygon to the Graphics g with horizontal scaling x_scale,
   * vertical scaling y_scale, and orientation being determined by rotationindegrees
   * pivotpoint and reflected.
   * Substitudes overrides for any corresponding variables.
   *@see G2PrimitiveDraw
   */
  @Override
  protected void Draw(Graphics g, int x_scale, int y_scale,
		      int rotationindegrees, Point pivotpoint,
		      boolean reflected,
		      Structure variables, Structure overrides) {
    super.Draw(g, x_scale, y_scale,
	       rotationindegrees, pivotpoint,
	       reflected,
	       variables, overrides);
    if (filled)
      G2PrimitiveDraw.Polygon(points_to_draw, x_scale, y_scale, g, true);
    else
      G2PrimitiveDraw.Polygon(points_to_draw, x_scale, y_scale, g, false);
  }
}

/**
 * OutlineElement
 */

class OutlineElement extends DrawingElement {

  protected OutlineElement(Point[] points) {
    super(points);
  }

  protected OutlineElement(Structure data) {
    super(data);
  }

  /**
   * Draws an outline to the Graphics g with horizontal scaling x_scale,
   * vertical scaling y_scale, and orientation being determined by rotationindegrees
   * pivotpoint and reflected.
   * Substitudes overrides for any corresponding variables.
   *@see G2PrimitiveDraw
   */
  @Override
  protected void Draw(Graphics g, int x_scale, int y_scale,
		      int rotationindegrees, Point pivotpoint,
		      boolean reflected,
		      Structure variables, Structure overrides) {
    super.Draw(g, x_scale, y_scale,
	       rotationindegrees, pivotpoint,
	       reflected,
	       variables,overrides);
    if (filled)
      G2PrimitiveDraw.Outline(points_to_draw,x_scale, y_scale, g, true);
    else
      G2PrimitiveDraw.Outline(points_to_draw,x_scale, y_scale, g, false);
  }
}

/**
 * TextElement
 */

class TextElement extends DrawingElement {
  
  private static final Symbol POINT_ = Symbol.intern ("POINT");
  private static final Symbol LABEL_ = Symbol.intern ("LABEL");
  private static final Symbol FONT_SIZE_ = Symbol.intern ("FONT-SIZE");

  protected PowerLabel label;
  protected PowerSymbol g2_font;

  protected TextElement(Point[] points) {
    super(points);
  }

  static Point[] getPoints(Structure data) {
    Point[] points = null;
    Structure text_point_data
      = (Structure) data.getAttributeValue(POINT_, null);
    if (text_point_data != null) {
      points = new PowerPoint[1];
      (points)[0] = new PowerPoint(text_point_data);
    }
    return points;
  }
  
  protected TextElement(Structure data) {
    this(getPoints(data));
    this.label = new PowerLabel(data.getAttributeValue(LABEL_, "")); 
    this.g2_font = new PowerSymbol((Symbol) data.getAttributeValue
				   (FONT_SIZE_, null));
  }

  @Override
  boolean checkforDynamicElements() {
    if (super.checkforDynamicElements())
      return true;
    if ((label != null)&&label.isdynamic)
      return true;
    if ((g2_font != null)&&g2_font.isdynamic)
      return true;
    return false;
  }
     
  /**
   * Draws the text to the Graphics g with horizontal scaling x_scale,
   * vertical scaling y_scale, and orientation being determined by rotationindegrees
   * pivotpoint and reflected.
   * Substitudes overrides for any corresponding variables.
   *@see G2PrimitiveDraw
   */
  @Override
  protected void Draw(Graphics g, int x_scale, int y_scale,
		      int rotationindegrees, Point pivotpoint,
		      boolean reflected,
		      Structure variables, Structure overrides) {
    super.Draw(g, x_scale, y_scale,
	       rotationindegrees, pivotpoint,
	       reflected,
	       variables, overrides);
    label.eval(variables, overrides);
    g2_font.eval(variables, overrides);
    int currentScale = Math.min(x_scale, y_scale);
    if (label.toString().equals ("")) // Nothing to paint. Why format textCell?
      return;
    if (!(label.toString().equals (cellLabel) &&
	  g2_font.currentValue().equals (cellFont) &&
	  minScale == currentScale &&
	  g.getColor ().equals (cellColor))) {
      Symbol cellFontLocal = g2_font.currentValue ();
      Font graphicsFont = G2FontMap.get (cellFontLocal);
      int fontSize = graphicsFont.getSize();
      fontSize= (int)Math.max(1,fontSize*currentScale/1000);
      graphicsFont = G2FontMap.get(fontSize);
      cellLabel = label.toString ();
      cellColor = g.getColor ();
      FontMetrics metrics= Toolkit.getDefaultToolkit().getFontMetrics(graphicsFont);
      fontDelta = metrics.getLeading() + metrics.getAscent ();
      if (textCell == null || !this.cellFont.equals(cellFontLocal) || minScale != currentScale) {
	this.cellFont = cellFontLocal;
	minScale = currentScale;
	textCell = new TextCell (10000, cellLabel,
				 new TextStyle (graphicsFont, 0, 0, 0),
				 Color.red,
				 cellColor,
				 0,
				 Color.blue);
	textCell.setHeight (10000);
      }
      textCell.setText (cellLabel);
      textCell.format (g);
      textCell.setTextColor (cellColor);
    }
    /* In JDK 1.3, every Graphics instance is actually a Graphics2D,
     * so we can safely cast it.  If we wanted to be really anal we
     * could do an instanceof check first.  -dkuznick, 8/8/2001
     */
    Graphics2D g2d = (Graphics2D) g;
    int xPointToDraw = points_to_draw[0].x*x_scale/1000;
    int yPointToDraw = points_to_draw[0].y*y_scale/1000;

    if (reflected == true) {
      g2d.translate(xPointToDraw, 0);
      g2d.scale(-1, 1);
      g2d.translate(-xPointToDraw, 0);
    }

    if ((rotationindegrees % 360) != 0) {
      /* The minus sign is a mystery, but seems to be required.
       * -dkuznick, 8/8/2001 */
      g2d.rotate(Math.toRadians(-rotationindegrees),
                 xPointToDraw,
                 yPointToDraw);
    }

    textCell.draw (g2d, xPointToDraw, yPointToDraw - fontDelta);
  }

  private String cellLabel;
  private Symbol cellFont;
  private int minScale;
  private Color cellColor;
  private int fontDelta;
  private TextCell textCell;
}

/**
 * ImageElement
 */

class ImageElement extends DrawingElement {

  private static final Symbol IMAGE_NAME_ = Symbol.intern ("IMAGE-NAME");
  
  protected PowerSymbol image_name;
  
  protected ImageElement(Point[] points) {
    super(points);
  }

  protected ImageElement(Structure data) {
    super(data);
    this.image_name = new PowerSymbol((Symbol) data.getAttributeValue
				      (IMAGE_NAME_, null));
  }

  @Override
  boolean checkforDynamicElements() {
    if (super.checkforDynamicElements())
      return true;
    if ((image_name != null)&&image_name.isdynamic)
      return true;
    return false;
  }
     
  /**
   * Draws the image to the Graphics g with horizontal scaling x_scale,
   * vertical scaling y_scale, and orientation being determined by rotationindegrees
   * pivotpoint and reflected.
   * Substitudes overrides for any corresponding variables.
   *@see G2PrimitiveDraw
   */
  @Override
  protected void Draw(Graphics g, int x_scale, int y_scale,
		      int rotationindegrees, Point pivotpoint,
		      boolean reflected,
		      Structure variables, Structure overrides) {
    super.Draw(g, x_scale, y_scale,
	       rotationindegrees, pivotpoint,
	       reflected,
	       variables, overrides);
    image_name.eval(variables, overrides);
    /*G2PrimitiveDraw.Image(pbkDealWithGetImageFromImageName(image_name.currentValue()),
      points_to_draw[0], g, false);*/
  }
}
