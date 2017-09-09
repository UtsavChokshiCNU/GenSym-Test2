package com.gensym.editor.icon.g2;

import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import java.util.Enumeration;
import java.awt.Color;
import java.awt.Font;
import com.gensym.editor.icon.shapes.*;
import com.gensym.editor.icon.core.Layer;
import com.gensym.editor.icon.core.IconFormat;
import com.gensym.editor.icon.core.IconEditorCanvas;
import com.gensym.ntw.util.G2ColorMap;
import com.gensym.ntw.util.G2FontMap;
import java.awt.Point;
import java.awt.Rectangle;
import com.gensym.icons.PowerPoint;
import com.gensym.editor.icon.core.ElementInconsistancyError;
import java.util.Vector;
import java.util.Enumeration;
import com.gensym.editor.icon.core.Parameter;
import com.gensym.editor.icon.core.BadExpressionException;
import com.gensym.util.NoSuchAttributeException;
import com.gensym.message.Trace;
import com.gensym.dlg.InputDialog;
import com.gensym.classes.ClassDefinition;
import java.awt.Image;
import java.net.URL;
import com.gensym.classes.ImageDefinition;
import com.gensym.ntw.TwAccess;
import com.gensym.classes.ImplAccess;
import com.gensym.jgi.G2AccessException;
import java.awt.Toolkit;
import java.awt.image.ImageObserver;
import java.net.MalformedURLException;

public class G2IconFormat implements IconFormat
{
  private static final Symbol BLACK_ = Symbol.intern ("BLACK"),
    IMAGE_DEFINITION_ = Symbol.intern("IMAGE-DEFINITION");
  public static int g2FormatVersion = 512;
  public static int t2FormatVersion = 102;
  private ClassDefinition classDef;

  public G2IconFormat(ClassDefinition classDef) {
    this.classDef = classDef;
  }

  public G2IconFormat() {
    this(null);
  }
  
  private Structure getDescription(IconLine iconLine)
  {
    Structure description = new Structure();
    description.setAttributeValue(Util.TYPE_, Util.LINES_);
    description.setAttributeValue
      (Util.POINTS_,
       Util.createPointsSequence(iconLine.getExpressions()));
    return description;
  }

  private Structure getDescription(IconLines iconLines)
  {
    Structure description = new Structure();
    description.setAttributeValue(Util.TYPE_, Util.LINES_);
    description.setAttributeValue
      (Util.POINTS_,
       Util.createPointsSequence(iconLines.getExpressions()));
    return description;
  }
  
  private Structure getDescription(IconPolygon iconPolygon)
  {
    Structure description = new Structure();
    boolean filled = iconPolygon.isFilled();
    description.setAttributeValue(Util.TYPE_, filled?Util.FILLED_POLYGON_:Util.OUTLINE_);
    description.setAttributeValue
      (Util.POINTS_,
       Util.createPointsSequence(iconPolygon.getExpressions()));
    return description;
  }

  private Structure getDescription(IconText iconText) {
    Structure description = new Structure();
    description.setAttributeValue(Util.TYPE_, Util.TEXT_);

    Object x = iconText.getExpression(IconText.X);
    Object y = iconText.getExpression(IconText.Y);
    if (y instanceof Integer)
      y = new Integer(((Integer)y).intValue() +
		      (int)iconText.getBounds().getHeight());
    description.setAttributeValue(Util.LABEL_, iconText.getExpression(IconText.TEXT));
    description.setAttributeValue(Util.POINT_,
				  Util.createPointStructure(x, y));
    Symbol fontSize;
    Font iconFont = iconText.getFont();
    int fontPoint = iconFont.getSize();
    if (fontPoint >= 24)
      fontSize = Util.EXTRA_LARGE_;
    else if (fontPoint >= 18)
      fontSize = Util.LARGE_;
    else fontSize = Util.SMALL_;
    description.setAttributeValue(Util.FONT_SIZE_, fontSize);
    return description;
  }
  
  private Structure getDescription(IconOval iconOval)
       //G2 ONLY SUPPORTS CIRCLES
  {
    Rectangle bounds = iconOval.getExactBounds()[0];
    boolean filled = iconOval.isFilled();
    Structure description = new Structure();
    description.setAttributeValue(Util.TYPE_, filled?Util.FILLED_CIRCLE_:Util.CIRCLE_);
    Sequence pointsSequence = null;

    if (iconOval instanceof G2IconOval) 
      pointsSequence = ((G2IconOval)iconOval).getPointsSequence();
    if (pointsSequence == null)
      pointsSequence = getPointsSequence(iconOval);
    
    description.setAttributeValue(Util.POINTS_, pointsSequence);
    return description;
  }

  private Sequence getPointsSequence(IconOval iconOval) {
    Object x = iconOval.getExpression(IconOval.X);
    if (x instanceof PointExpression)
      x = x.toString();        
    Object y = iconOval.getExpression(IconOval.Y);
    if (y instanceof PointExpression)
      y = y.toString();            
    Object radX = iconOval.getExpression(IconOval.RADIUS_X);
    if (radX instanceof PointExpression)
      radX = radX.toString();            
    Object[] points = Util.threePointsOnCircle(x, y, radX);
    return Util.createPointsSequence(points);
  }
  
  private Structure getDescription(IconPoint iconPoint)
  {
    Structure description = new Structure();
    description.setAttributeValue(Util.TYPE_, Util.POINT_);
    Object x = iconPoint.getExpression(IconPoint.X);
    if (x instanceof PointExpression)
      x = x.toString();
    Object y = iconPoint.getExpression(IconPoint.Y);
    if (y instanceof PointExpression)
      y = y.toString();    
    description.setAttributeValue(Util.POINTS_,
				  Util.createPointStructure
				  (new Object[]{x, y}));
    return description;
  }

  private Structure getDescription(IconImage iconImage)
  {
    Structure description = new Structure();
    description.setAttributeValue(Util.TYPE_, Util.IMAGE_);
    Object imageLocation = iconImage.getImageLocation();
    Symbol imageName = null;
    if (imageLocation instanceof Symbol) 
      imageName = (Symbol)imageLocation;
    else {
      InputDialog dlg = new InputDialog(null,
					"Image Definition name for "
					+ imageLocation,
					true,
					new String[] {"Name"},
					new String[] {""},
					null);
      dlg.setVisible(true);
      imageName = Symbol.intern(dlg.getResults()[0].toUpperCase());
    }
    //Need to make this dialog a file chooser like when you open/save
    //an icon.  Should make it so one is able to select a file from which
    //to get the image or an image definition from g2.
    description.setAttributeValue(Util.IMAGE_NAME_, imageName);
    Object x = iconImage.getExpression(IconPoint.X);
    if (x instanceof PointExpression)
      x = x.toString();    
    Object y = iconImage.getExpression(IconPoint.Y);
    if (y instanceof PointExpression)
      y = y.toString();    
    description.setAttributeValue(Util.POINT_,
				  Util.createPointStructure
				  (new Object[]{x, y}));
    return description;
  }
  
  private Structure getDescription(IconRectangle iconRectangle)
  {
    Structure description = new Structure();
    boolean filled = iconRectangle.isFilled();
    description.setAttributeValue(Util.TYPE_, filled?
				  Util.FILLED_RECTANGLE_:Util.OUTLINE_);
    Object[][] points;
    Rectangle bounds = iconRectangle.getExactBounds()[0];
    Object x = iconRectangle.getExpression(IconRectangle.X);
    Object y = iconRectangle.getExpression(IconRectangle.Y);
    Object width = iconRectangle.getExpression(IconRectangle.WIDTH);
    Object height = iconRectangle.getExpression(IconRectangle.HEIGHT);
    Object x2 = x.toString() + " + " + width.toString();
    if (x instanceof Number & width instanceof Number)
      x2 = new Integer(((Number)x).intValue() + ((Number)width).intValue());
    Object y2 = y.toString() + " + " + height.toString();
    if (y instanceof Number & height instanceof Number)
      y2 = new Integer(((Number)y).intValue() + ((Number)height).intValue());
    if (filled) {
      points =
	new Object[][] {
	new Object[] {x,y}, new Object[] {x2, y2}};
    } else {
      points = new Object[][]{
      new Object[] {x,y},
      new Object[] {x,y2},
      new Object[] {x2,y2},
      new Object[] {x2,y}};
    }
    description.setAttributeValue(Util.POINTS_, Util.createPointsSequence(points));
    return description;
  }


  public static final Symbol GREY_ = Symbol.intern ("GREY"),
    LIGHT_GREY_ = Symbol.intern ("LIGHT-GREY"),
    GRAY_ = Symbol.intern ("GRAY"),
    LIGHT_GRAY_ = Symbol.intern ("LIGHT-GRAY"),
    EXTRA_LIGHT_GREY_ = Symbol.intern ("EXTRA-LIGHT-GREY"),
    EXTRA_LIGHT_GRAY_ = Symbol.intern ("EXTRA-LIGHT-GRAY"),
    DIM_GREY_ = Symbol.intern ("DIM-GREY"),
    DIM_GRAY_ = Symbol.intern ("DIM-GRAY");


  @Override
  public Object getDescriptionOfColor(Color color) {
    Symbol clr = null;
    for (int fudge = 0;clr == null;fudge++) {
      clr = getDescriptionOfColor(color, fudge);
    }
    return clr;
  }

  private final static int getDiff(Color c1, Color c2) {
    int val = (int)Math.pow(c1.getRed()-c2.getRed(), 2);
    val+=(int)Math.pow(c1.getGreen()-c2.getGreen(), 2);
    val+=(int)Math.pow(c1.getBlue()-c2.getBlue(), 2);
    return val;
  }
  
  public final static Symbol getDescriptionOfColor(Color color, int fudge)
  {
    Enumeration e = G2ColorMap.getColors();
    while(e.hasMoreElements()) {
      Symbol colorName = (Symbol)e.nextElement();
      Color clr = G2ColorMap.get(colorName);
      if (getDiff(clr,color) <= fudge) {
	if (colorName.equals(GREY_))
	  colorName = GRAY_;
	else if (colorName.equals(LIGHT_GREY_))
	  colorName = LIGHT_GRAY_;
	else if (colorName.equals(EXTRA_LIGHT_GREY_))
	  colorName = EXTRA_LIGHT_GRAY_;
	else if (colorName.equals(DIM_GREY_))
	  colorName = DIM_GRAY_;	
	return colorName;
      }
    }
    return null;
  }

  private Sequence getDescriptionOfElements(Layer layer)
  {
    Sequence description = new Sequence();
    Enumeration e = layer.getElements();
    while (e.hasMoreElements()) {
      Object elt = e.nextElement();
      if (elt instanceof IconRectangle)
	description.addElement(getDescription((IconRectangle)elt));
      else if (elt instanceof IconPoint)
	description.addElement(getDescription((IconPoint)elt));
      else if (elt instanceof IconOval)
	description.addElement(getDescription((IconOval)elt));
      else if (elt instanceof IconPolygon)
	description.addElement(getDescription((IconPolygon)elt));
      else if (elt instanceof IconLines)
	description.addElement(getDescription((IconLines)elt));
      else if (elt instanceof IconLine)
	description.addElement(getDescription((IconLine)elt));
      else if (elt instanceof IconImage)
	description.addElement(getDescription((IconImage)elt));
      else if (elt instanceof IconText)
	description.addElement(getDescription((IconText)elt));
      else {
	System.out.println("CAN'T CONVERT " + elt);
      }
    }
    return description;
  }
  
  private Structure getDescriptionOfLayer(Layer layer)
  {
    Structure description = new Structure();
    String regionName = layer.getRegionName();
    description.setAttributeValue(Util.REGION_OR_COLOR_,
				  regionName!=null?Symbol.intern(regionName.toUpperCase())
				  :getDescriptionOfColor(layer.getColor()));
    description.setAttributeValue(Util.LINE_DRAWING_ELEMENTS_,
				  getDescriptionOfElements(layer));
    return description;
  }

  private Sequence getDescriptionOfLayers(IconEditorCanvas canvas)
  {
    Sequence descriptions = new Sequence();
    Layer[] layers = canvas.getLayers();
    for (int i=0;i<layers.length;i++) {
      descriptions.addElement(getDescriptionOfLayer((Layer)layers[i]));
    }
    return descriptions;
  }

  private Sequence getDescriptionOfRegions(IconEditorCanvas canvas)
  {
    Sequence regions = new Sequence();
    Layer[] layers = canvas.getLayers();
    Vector regionsFound = new Vector();    
    for (int i=0;i<layers.length;i++) {
      Layer layer = layers[i];
      String regionName = layer.getRegionName();
      if (regionName != null && !regionsFound.contains(regionName)) {
	Symbol regionNameSymbol = Symbol.intern(regionName.toUpperCase());
	if (G2ColorMap.get(regionNameSymbol) == null) {
	  regionsFound.addElement(regionName);
	  Structure regionsStructure = new Structure();
	  Color color = layer.getColor();
	  Object colorName = getDescriptionOfColor(color);
	  regionsStructure.setAttributeValue(REGION_NAME_,
					     regionNameSymbol);
	  regionsStructure.setAttributeValue(COLOR_NAME_, colorName);
	  regions.addElement(regionsStructure);
	}
      }
    }
    return regions;
  }  

  private static final Symbol VARIABLE_NAME_ = Symbol.intern ("VARIABLE-NAME");
  private static final Symbol INITIAL_VALUE_ = Symbol.intern ("INITIAL-VALUE");  
  private static final Symbol REGION_NAME_   = Symbol.intern ("REGION-NAME");
  private static final Symbol COLOR_NAME_    = Symbol.intern ("COLOR-NAME");
  private static final Object COLOR_CAST     = new Object ();  
  @Override
  public void importFormattedIcon(Object formattedIcon,
				  IconEditorCanvas canvas) {
    Structure description = (Structure) formattedIcon;
    Integer width = (Integer)description.getAttributeValue(Util.WIDTH_, null);
    Integer height = (Integer)description.getAttributeValue(Util.HEIGHT_, null);
    canvas.setIconWidth(width.intValue());
    canvas.setIconHeight(height.intValue());
    Sequence iconVariables =
      (Sequence)description.getAttributeValue(Util.VARIABLES_, new Sequence());
    int offset = 0;
    Parameter[] params = new Parameter[iconVariables.size()+offset];
    //REMOVING THE FOLLOWING TEMPORARILY
    //params[0]=new Parameter("WIDTH",Integer.class, width);
    //params[1]=new Parameter("HEIGHT",Integer.class, height);
    Enumeration iv = iconVariables.elements();
    int i=offset;
    while (iv.hasMoreElements()) {
      Structure ivs = (Structure)iv.nextElement();
      Object value = ivs.getAttributeValue(INITIAL_VALUE_,"");
      params[i++]=new Parameter(ivs.getAttributeValue(VARIABLE_NAME_,"").toString(),
				value.getClass(),
				value);
    }
				
    canvas.setEvaluator(new G2ExpressionEvaluator(params));
    Sequence regionsSeq =
      (Sequence)description.getAttributeValue(Util.REGIONS_, null);
    Structure regions = flattenSpecList(regionsSeq, REGION_NAME_, COLOR_NAME_, null);
    Sequence variables =
      (Sequence)description.getAttributeValue(Util.VARIABLES_, null);
    Object backgroundLayer =
      description.getAttributeValue(Util.ICON_BACKGROUND_LAYER_, null);
    Sequence layers = (Sequence)description.getAttributeValue(Util.LAYERS_, null);
    Enumeration e = layers.elements();
    while(e.hasMoreElements()) {
      Structure layerDescription = (Structure)e.nextElement();
      Layer layer = createLayer(layerDescription,
				flattenSpecList(variables,
						VARIABLE_NAME_,
						INITIAL_VALUE_, null),
				canvas);
      Symbol regionOrColor = Symbol.intern(layer.getRegionName().toUpperCase());
      Color color = G2ColorMap.get(regionOrColor);
      if (color == null) {
	regionOrColor = (Symbol)regions.getAttributeValue
	  (regionOrColor, BLACK_);
	color = G2ColorMap.get(regionOrColor);
      } else 
	layer.setRegionName(null);
      layer.setColor(color);
      canvas.addLayer(layer,canvas.getLayers().length);

      ///tmp HACK 
      IconElement[] ies = layer.getElementsSnapshot();
      for (int j=0;j<ies.length;j++) {
	IconElement ie = ies[j];
	ie.evaluateExpressions();
      }
    }
  }

  private Sequence createSpecList(Parameter[] parameters, Symbol namekey, Symbol valuekey)
  {
    Sequence specList = new Sequence();
    for (int i=0;i<parameters.length;i++) {
      Parameter param = parameters[i];
      Symbol name = Symbol.intern(param.getName().toUpperCase());
      if (!(Util.WIDTH_.equals(name) &&
	    Util.HEIGHT_.equals(name))) {
	Structure spec = new Structure();
	spec.setAttributeValue(namekey, name);
	spec.setAttributeValue(valuekey, param.getDefaultValue());
	specList.addElement(spec);
      }
    }
    return specList;
  }
  
  private Structure flattenSpecList (Sequence speclist, Symbol namekey, Symbol valuekey,
				     Object classCastName) {
    if (speclist == null)
      return null;
    else {
      int specListSize = speclist.size ();
      Structure newStruct = new Structure (/*specListSize*/);
      Structure currentspec;
      Symbol name; Object value;
      for (int i=0; i<specListSize; i++) {
	currentspec = (Structure) speclist.elementAt (i);
	name = (Symbol) currentspec.getAttributeValue (namekey, null);
	value = currentspec.getAttributeValue (valuekey, null);
	if (classCastName != null && classCastName.equals (COLOR_CAST))
	  value = (Color) G2ColorMap.get ((Symbol)value);
	if (name != null)
	  newStruct.setAttributeValue (name, value);
      }
      return newStruct;
    }
  }
      

  private Layer createLayer(Structure struct, Structure variables,
			    IconEditorCanvas canvas) {
    Layer layer = new Layer();
    Symbol regionOrColor = (Symbol)struct.getAttributeValue(Util.REGION_OR_COLOR_, null);
    layer.setRegionName(regionOrColor.getPrintValue());
    Sequence elements =
      (Sequence)struct.getAttributeValue(Util.LINE_DRAWING_ELEMENTS_, null);
    Enumeration e = elements.elements();
    while (e.hasMoreElements()) {
      Structure element = (Structure)e.nextElement();
      try {
	IconElement iconElement = createIconElement(element,variables, canvas);
	if (iconElement != null) {
	  try {
	    layer.addElement(iconElement);
	  } catch (ElementInconsistancyError eie) {
	    System.out.println(eie);
	  }
	}
      } catch (BadExpressionException bee) {
	Trace.exception(bee);
      } catch (NoSuchAttributeException nsae) {
	Trace.exception(nsae);
      }
    }
    return layer;
  }

  private PowerPoint[] castObjectArray(Sequence sequence, String classname, Structure variables) {
    PowerPoint object;
    if (sequence != null) {
      int count = sequence.size();
      PowerPoint[] objects = new PowerPoint[count];
      Structure struct;
      for (int i=0; i<count; i++) {
	struct = (Structure) sequence.elementAt (i);
	object = new PowerPoint(struct);
	object.eval(variables, null);
	objects[i] = object;
      }
      return objects;
    }
    else 
      return null;
  }

  private static float[] CalculateCenterofCircle(Point p1, Point p2, Point p3) {
    float[] mp1 = Midpoint(p1, p2); float[] mp2 = Midpoint(p2, p3);
    float m1 =  Slope(p1,p2); float m2 =  Slope(p2, p3);
    float[] center = IntersectLines(mp1, -1/m1, mp2, -1/m2);
    return center;
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
    if (dm != 0) { //if not parallel
      float x1 = p1[0];
      float y1 = p1[1];
      float x2 = p2[0];
      float y2 = p2[1];
      if (x1 == x2 && y1 == y2) 
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
  
  private IconElement createIconElement(Structure struct,
					Structure variables,
					IconEditorCanvas canvas)
  throws BadExpressionException, NoSuchAttributeException
  {
    Symbol type = (Symbol) struct.getAttributeValue(Util.TYPE_, null);
    Object pointdata = struct.getAttributeValue(Util.POINTS_, null);
    if (pointdata == null) 
      pointdata = struct.getAttributeValue(Util.POINT_, null);
    if (pointdata instanceof Structure) {
      Sequence pointDataSeq = new Sequence();
      pointDataSeq.addElement(pointdata);
      pointdata = pointDataSeq;
    }
    PowerPoint[] points = castObjectArray((Sequence)pointdata, "PowerPoint", variables);
    int pointCount = points.length;
    IconElement newobject = null;
    if (type.equals (Util.LINES_)) {
      int[] xPoints = new int[pointCount];
      int[] yPoints = new int[pointCount];
      for (int i=0;i<pointCount;i++) {
	PowerPoint p = points[i];
	//p.eval(variables, null);
	xPoints[i]=p.x;
	yPoints[i]=p.y;
      }      
      newobject = new IconLines(pointCount, xPoints, yPoints);
      for (int i=0;i<pointCount;i++) {      
	Structure ps = (Structure)((Sequence)pointdata).elementAt(i);
	Object val = ps.getAttributeValue(Util.X_);
	if (!(val instanceof Number))
	  newobject.setExpression(2*i, new PointExpression(val));
	val = ps.getAttributeValue(Util.Y_);
	if (!(val instanceof Number))
	  newobject.setExpression(2*i+1, new PointExpression(val));	
      }
    } else if (type.equals (Util.FILLED_POLYGON_)) {
      int[] xPoints = new int[pointCount];
      int[] yPoints = new int[pointCount];
      for (int i=0;i<pointCount;i++) {
	PowerPoint p = points[i];
	//p.eval(variables, null);
	xPoints[i]=p.x;
	yPoints[i]=p.y;
      }
      newobject = new IconPolygon(points.length, xPoints, yPoints, true);
      for (int i=0;i<pointCount;i++) {      
	Structure ps = (Structure)((Sequence)pointdata).elementAt(i);
	Object val = ps.getAttributeValue(Util.X_);
	if (!(val instanceof Number))
	  newobject.setExpression(2*i, new PointExpression(val));
	val = ps.getAttributeValue(Util.Y_);
	if (!(val instanceof Number))
	  newobject.setExpression(2*i+1, new PointExpression(val));	
      }      
    } else if (type.equals(Util.OUTLINE_)) {
      int[] xPoints = new int[pointCount];
      int[] yPoints = new int[pointCount];
      for (int i=0;i<pointCount;i++) {
	PowerPoint p = points[i];
	//p.eval(variables, null);
	xPoints[i]=p.x;
	yPoints[i]=p.y;
      }
      newobject = new IconPolygon(points.length, xPoints, yPoints, false);
      for (int i=0;i<pointCount;i++) {      
	Structure ps = (Structure)((Sequence)pointdata).elementAt(i);
	Object val = ps.getAttributeValue(Util.X_);
	if (!(val instanceof Number))
	  newobject.setExpression(2*i, new PointExpression(val));
	val = ps.getAttributeValue(Util.Y_);
	if (!(val instanceof Number))
	  newobject.setExpression(2*i+1, new PointExpression(val));
      }            
    } else if (type.equals (Util.FILLED_RECTANGLE_)) {
     int x1,y1, x2,y2, temp;
     PowerPoint p1 = points[0];
     PowerPoint p2 = points[1];
     //p1.eval(variables,null);
     //p2.eval(variables,null);
     x1 = p1.x; x2 = p2.x;
     if (x2 < x1) {temp = x1; x1 = x2; x2 = temp;}
     y1 = p1.y; y2 = p2.y;
     if (y2 < y1) {temp = y1; y1 = y2; y2 = temp;}
     int width = 1 + x2 - x1; int height = 1 + y2 - y1;      
     newobject = new IconRectangle(x1,y1,width,height,true);
     
     Structure ps1 = (Structure)((Sequence)pointdata).elementAt(0);
     Structure ps2 = (Structure)((Sequence)pointdata).elementAt(1);

     Object val = ps1.getAttributeValue(Util.X_);

     if (!(val instanceof Number))
       newobject.setExpression(IconRectangle.X, new PointExpression(val));
     val = ps1.getAttributeValue(Util.Y_);
     if (!(val instanceof Number))
       newobject.setExpression(IconRectangle.Y, new PointExpression(val));     
     val = ps2.getAttributeValue(Util.X_);
     Object xVal=newobject.getExpression(IconRectangle.X);
     Object yVal=newobject.getExpression(IconRectangle.Y);
     if (!(val instanceof Integer && xVal instanceof Integer))
       newobject.setExpression(IconRectangle.WIDTH,
			       new PointExpression
			       (val+" - "+xVal));
     val = ps2.getAttributeValue(Util.Y_);
     if (!(val instanceof Integer && yVal instanceof Integer))     
       newobject.setExpression(IconRectangle.HEIGHT,
			       new PointExpression
			       (val+" - "+yVal));     
    } else if (type.equals (Util.FILLED_CIRCLE_) ||
	       type.equals (Util.CIRCLE_)) {
      boolean filled = type.equals (Util.FILLED_CIRCLE_);
      Point p0 = points[0], p1 = points[1], p2 = points[2];
      float[] fcenter = CalculateCenterofCircle(p0, p1, p2);
      if (fcenter != null) {
	int x0 = (int) fcenter[0]; int y0 = (int) fcenter[1];
	if (x0 == p0.x && y0 == p0.y) {
	  newobject = new IconPoint(x0,y0);
	} else {
	  int radius_x = points[1].x - x0;
	  int radius_y = points[1].y - y0;
	  if (radius_x < 0) radius_x = -radius_x;
	  if (radius_y < 0) radius_y = -radius_y;
	  float fradius = (float) Math.sqrt(radius_x*radius_x + radius_y*radius_y);
	  int radius = (int) fradius;
	  newobject = new G2IconOval(x0,y0,radius, radius, filled);
	  if (p0.x + radius == p1.x && p1.x ==  p2.x - radius &&
	      p0.y == p1.y - radius && p0.y == p2.y) {
	    Structure ps0 = (Structure)((Sequence)pointdata).elementAt(0);	    
	    Structure ps1 = (Structure)((Sequence)pointdata).elementAt(1);
	    Object p0x = ps0.getAttributeValue(Util.X_);
	    Object p0y = ps0.getAttributeValue(Util.Y_);
	    Object p1x = ps1.getAttributeValue(Util.X_);	    
	    if (!(p0y instanceof Number))
	      newobject.setExpression(IconOval.Y, new PointExpression(p0y));
	    if (!(p1x instanceof Number) || !(p0x instanceof Number)) {
	      if (!(p0x instanceof Number))       
		newobject.setExpression(IconOval.X, new PointExpression(p1x));
	      Object rad = p1x + " - "+ p0x;
	      newobject.setExpression(IconOval.RADIUS_X, new PointExpression(rad));
	      newobject.setExpression(IconOval.RADIUS_Y, new PointExpression(rad));
	    }
	  }
	  ((G2IconOval)newobject).setPointsSequence((Sequence)pointdata);
	}
      }
    } else if (type.equals (Util.TEXT_)) {
      String label;
      Font font = new Font("sansserif", Font.PLAIN, 14);
      PowerPoint p = points[0];
      Object labelVar = null, fontVar = null;
      boolean labelIsExpression = false;
      boolean fontIsExpression = false;
      labelVar = struct.getAttributeValue(Util.LABEL_);
      if (labelVar instanceof Symbol) {
	label = variables.getAttributeValue((Symbol)labelVar).toString();
	labelIsExpression = true;
      } else
	label = labelVar.toString();
      fontVar = struct.getAttributeValue(Util.FONT_SIZE_);
      if (fontVar instanceof Symbol) {
	if (Util.SMALL_.equals(fontVar) ||
	    Util.LARGE_.equals(fontVar) ||
	    Util.EXTRA_LARGE_.equals(fontVar));
	else {
	  fontVar = (Symbol)variables.getAttributeValue((Symbol)fontVar);
	  fontIsExpression = true;
	}
	font = (Font)G2FontMap.get((Symbol)fontVar);
      }
      newobject = new IconText (label, font, p.x, p.y);
      if (labelIsExpression)
	newobject.setExpression(IconText.TEXT, labelVar);
      if (fontIsExpression)
	newobject.setExpression(IconText.FONT, fontVar);
      Structure p1 = (Structure)((Sequence)pointdata).elementAt(0);
      Object val = p1.getAttributeValue(Util.X_);
      if (!(val instanceof Number))
	newobject.setExpression(IconText.X, new PointExpression(val));
      val = p1.getAttributeValue(Util.Y_);
      if (!(val instanceof Number))
	newobject.setExpression(IconText.Y, new PointExpression(val));
    } else if (type.equals (Util.POINT_)) {
      PowerPoint p = points[0];
      //p.eval(variables, null);
      newobject = new IconPoint(p.x,p.y);
      Structure p1 = (Structure)((Sequence)pointdata).elementAt(0);
      Object val = p1.getAttributeValue(Util.X_);
      if (!(val instanceof Number))
	newobject.setExpression(IconPoint.X, new PointExpression(val));
      val = p1.getAttributeValue(Util.Y_);
      if (!(val instanceof Number))
	newobject.setExpression(IconPoint.Y, new PointExpression(val));
    } else if (type.equals (Util.IMAGE_)) {
      PowerPoint p = points[0];
      Object imageVar = struct.getAttributeValue(Util.IMAGE_NAME_);
      Object imageLocation = null;
      boolean imageIsExpression = false;
      Image image = null;
      //Need to add option of opening image from file
      //Here we extract imageLocation from G2 ImageDefinition
      if (classDef != null) {
	ImageDefinition idef;
	try {
	  TwAccess context = (TwAccess) ((ImplAccess)classDef).getContext();
	  idef = (ImageDefinition)context.
	    getUniqueNamedItem(IMAGE_DEFINITION_, (Symbol)imageVar);
	} catch (G2AccessException gae) {
	  idef = (ImageDefinition)variables.getAttributeValue
	    ((Symbol)imageVar);
	  imageIsExpression = true;
	}
	try {
	  String filename = idef.getFileNameOfImage();
	  image = Toolkit.getDefaultToolkit().getImage(filename);
	  imageLocation = idef.getNames();
	} catch (G2AccessException gae) {
	  Trace.exception(gae);
	}
      }
      newobject = new IconImage(imageLocation, image, p.x, p.y, 
				image.getWidth((ImageObserver)canvas),
				image.getHeight((ImageObserver)canvas));
      if (imageIsExpression)
	newobject.setExpression(IconImage.IMAGE_LOCATION, imageVar);
      Structure p1 = (Structure)((Sequence)pointdata).elementAt(0);
      Object val = p1.getAttributeValue(Util.X_);
      if (!(val instanceof Number))
	newobject.setExpression(IconImage.X, new PointExpression(val));
      val = p1.getAttributeValue(Util.Y_);
      if (!(val instanceof Number))
	newobject.setExpression(IconImage.Y, new PointExpression(val));
    } 
    return newobject;
  }
  
  @Override
  public Object createFormattedIcon(IconEditorCanvas canvas)
  {
    Structure description = new Structure();
    description.setAttributeValue(Util.WIDTH_, canvas.getIconWidth());
    description.setAttributeValue(Util.HEIGHT_, canvas.getIconHeight());
    Sequence regions = getDescriptionOfRegions(canvas);
    if (regions != null && !regions.isEmpty())
      description.setAttributeValue(Util.REGIONS_, regions);
    Sequence variables = createSpecList(canvas.getEvaluator().getParameters(),
					VARIABLE_NAME_,
					INITIAL_VALUE_);
    if (variables != null && !variables.isEmpty())
      description.setAttributeValue(Util.VARIABLES_, variables);
    Object backgroundLayer = canvas.getIconBackgroundLayer();
    if (backgroundLayer != null)
      description.setAttributeValue(Util.ICON_BACKGROUND_LAYER_,
				    backgroundLayer);
    description.setAttributeValue(Util.LAYERS_,
				  getDescriptionOfLayers(canvas));
    return description;    
  }
  
  @Override
  public String getFormatName() {
    return "gid";
  }
  
  @Override
  public String getFormatDescription() {
   return "A G2 Icon Description"; 
  }
}

class G2IconOval extends IconOval {
  private Sequence pointsSequence;
  public G2IconOval(int x, int y, int xRadius, int yRadius, boolean filled)
  {
    super(x, y, xRadius, yRadius, filled);
  }
  public Sequence getPointsSequence(){
    return pointsSequence;
  }
  public void setPointsSequence(Sequence pointsSequence){
    this.pointsSequence = pointsSequence;
  }

  @Override
  public IconElement copy() {
    Rectangle bounds = getExactBounds()[0];
    G2IconOval copy = new G2IconOval(bounds.x+bounds.width/2,
				     bounds.y+bounds.height/2,
				     bounds.width/2, bounds.height/2,
				     filled);
    try {
      copy.setExpression(X, getExpression(X));
      copy.setExpression(Y, getExpression(Y));
      copy.setExpression(RADIUS_X, getExpression(RADIUS_X));
      copy.setExpression(RADIUS_Y, getExpression(RADIUS_Y));
      copy.setExpression(FILLED, getExpression(FILLED));
    } catch (BadExpressionException bee) {
      Trace.exception(bee);
    }
    copy.setPointsSequence(pointsSequence);    
    return copy;        
  }
  @Override
  public void shift (int shiftX, int shiftY) {
    pointsSequence = null;
    super.shift(shiftX, shiftY);
  }
  @Override
  public void setExpression(int argIndex, Object expression)
       throws BadExpressionException
  {
    if (expression != null)
      pointsSequence = null;
    super.setExpression(argIndex, expression);
  }
}
