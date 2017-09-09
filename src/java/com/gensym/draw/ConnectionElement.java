package com.gensym.draw;

import java.awt.*;
import com.gensym.util.MathUtils;
import com.gensym.message.Resource;
import com.gensym.util.UnexpectedException;
import com.gensym.ntw.util.G2ColorMap;

/**
 *
 * Connection Element
 *
 */
public class ConnectionElement extends BasicDrawElement
{

  private static Resource i18n =
  Resource.getBundle("com.gensym.draw.Messages");

  static final long serialVersionUID = -2355440499730146526L;
  public static final int ORTHOGONAL = 0;
  public static final int DIAGONAL = 1;
  private boolean paintMode = true;
  private Rectangle[] bounds;
  private Rectangle outerBounds;
  private Object[] logicalColors;
  private Color[] jColors;
  private int[] stripeWidths;
  private Object[] stripePattern;
  private Color[] colorPattern;
  private int width;
  private Point[] vertices;
  protected Segment[] segments;
  private boolean connectionElementDebugP = false;
  protected int style = ORTHOGONAL;
  protected boolean directed = false;

  public ConnectionElement (Point[] vertices,
			    int[]widths, Object[] stripePattern,
			    Object[] logicalColors, Color[] jColors,
			    int style)
  {
    this.style = style;
    setStripeWidths(widths);
    this.stripePattern = stripePattern;// cant call setStripePattern until colormap is set
    setLogicalColorMap(logicalColors,jColors);
    setVertices(vertices);
  }

  // We could be smarter about the exact bounds of Connections:
  // If there are no arrows, then don't take them into account
  // when calculating the exact bounds, just take into account
  // the total stripe widths. If we did that, changing whether
  // or not a connection is directed would require computeBounds
  // to be called.
  public void setDirected(boolean directed)
  {
    this.directed=directed;
    //computeBounds();
  }

  public boolean getDirected()
  {
    return directed;
  }
  
  public void setStyle(int style)
  {
    this.style = style;
  }

  public int getStyle()
  {
    return style;
  }
  
  public void setVertices(Point[] newVertices) 
  {
    int top_half = width >> 1;
    vertices = newVertices;
    switch(style) {
    case ORTHOGONAL:
      segments = makeOrthogonalSegments(newVertices,top_half, width - top_half);
      break;
    case DIAGONAL:
      segments = makeDiagonalSegments(newVertices,top_half, width - top_half);
      break;
    default:
      throw new UnexpectedException(null,
				    i18n.format("unexpectedConnectionStyle",
						new Integer(style)));
    }
    computeBounds();
  }

  public ConnectionElement copy() {
    int length = vertices.length;
    Point[] newVertices = new Point[length];
    for (int i=0; i<length; i++) {
      newVertices[i] = new Point(vertices[i].x, vertices[i].y);
    }
    //shouldn't we copy these arrays???
    return new ConnectionElement(newVertices,
				 stripeWidths, stripePattern,
				 logicalColors, jColors, style);
  }

  public Point[] getVertices()
  {
    /*
    Point[] points = new Point[segments.length + 1];
    int leftTopHalfWidth = width >> 1;
    int rightBottomHalfWidth = width - leftTopHalfWidth;
    for (int i = 0 ; i<segments.length ; i++)
      {
	Segment segment = segments[i];
	switch (segment.heading)
	  {
	  case Segment.LEFT:
	    break;
	  case Segment.TOP:
	    break;
	  case Segment.RIGHT:
	    break;
	  case Segment.BOTTOM:
	    break;

	  }
      }
    return points;
    */
    return vertices;
  }

  private void computeBounds() {
    int length = segments.length;
    int minLeft = Integer.MAX_VALUE;
    int minTop = Integer.MAX_VALUE;
    int maxRight = Integer.MIN_VALUE;
    int maxBottom = Integer.MIN_VALUE;

    bounds = new Rectangle[length];

    for (int i = 0 ; i < length ; i++)
    {
      Segment s = segments[i];
      minLeft = Math.min(minLeft,Math.min(s.left, s.right));
      /*minTop = Math.min(minTop,Math.min(s.bottom,s.top));
      maxRight = Math.max(maxRight,Math.max(s.left,s.right));
      maxBottom = Math.max(maxBottom,Math.max(s.top,s.bottom));
      bounds[i] = new Rectangle(s.left,s.top,s.right - s.left,
				s.bottom - s.top);*/
      int left = Math.min(s.left, s.right);
      int right = Math.max(s.left,s.right);
      int top = Math.min(s.bottom,s.top);
      int bottom = Math.max(s.top,s.bottom);
      minLeft = Math.min(minLeft,left);
      minTop = Math.min(minTop,top);
      maxRight = Math.max(maxRight,right);
      maxBottom = Math.max(maxBottom,bottom);
      if (style == ORTHOGONAL) {
	if (s.isHorizontal)
	  bounds[i] = new Rectangle(left,top-arrowSize,
				    Math.max(1,right-left),
				    Math.max(1,bottom+2*arrowSize-top));
	else
	  bounds[i] = new Rectangle(left-arrowSize,top,
				    Math.max(1,right+2*arrowSize-left),
				    Math.max(1,bottom+-top));
      } else {
	// if directed always had the correct value, the following
	// could be used (setDirected would have to call computeBounds)
	// arrowAdjust = directed ? diagonalArrowSize : 0;
	int arrowAdjust = diagonalArrowSize;
	bounds[i] = new Rectangle(left-arrowAdjust,top-arrowAdjust,
				  Math.max(1,right+2*arrowAdjust-left),
				  Math.max(1,bottom+2*arrowAdjust-top));
      }
    }

    if (style == ORTHOGONAL) {
      minLeft-=arrowSize; minTop-=arrowSize;
      outerBounds = new Rectangle(minLeft,minTop,
				  //maxRight - minLeft, maxBottom - minTop);
				  Math.max(1,maxRight - minLeft + 2*arrowSize),
				  Math.max(1,maxBottom - minTop + 2*arrowSize));
    } else {
      minLeft-=arrowSize; minTop-=arrowSize;
      outerBounds = new Rectangle(minLeft - 1,minTop - 1,
				  //maxRight - minLeft, maxBottom - minTop);
				  Math.max(1,maxRight + 2*arrowSize - minLeft)+2,
				  Math.max(1,maxBottom + 2*arrowSize - minTop)+2);
    }
    setLocation(minLeft,minTop);
    setSize(outerBounds.width,outerBounds.height);
  }

  public void setStripeWidths(int[] widths)
  {
    stripeWidths = widths;
    int total = 0;

    for (int i = 0 ; i < widths.length ; i++)
        total += widths[i];
    width = total;
  }

  public int getConnectionWidth() {
    return width;
  }
  
  private void resetColorPattern() {
    int stripeCount = stripePattern.length;
    colorPattern = new Color[stripeCount];
    for (int i=0 ; i< stripeCount ; i++) 
      colorPattern[i] = getColor(stripePattern[i]);
  }
  
  public void setStripePattern(Object[] stripePattern) {
    this.stripePattern = stripePattern;
    resetColorPattern();
  }
    
  public void setLogicalColorMap(Object[] logicalColors, Color[] jColors)
  {
    this.logicalColors = logicalColors;
    this.jColors = jColors;
    resetColorPattern();
  }

  public Color getColor(Object logicalColor) {
    int count = logicalColors.length;
    for (int i=0 ; i< count ; i++)
      if (logicalColors[i].equals(logicalColor))
	return jColors[i];
    return G2ColorMap.get(logicalColor);
  }
  
  @Override
  public void changeColor(Object logicalColor, Color color)
  {
    int index = -1, i;
    for (i=0 ; i< logicalColors.length ; i++){
      if (logicalColors[i].equals(logicalColor))
        {
          jColors[i] = color;
	  resetColorPattern();
        }
    }
    canvas.invalidateElement(this);
  }

  @Override
  public void changeColor(Object logicalColor, Object colorKey)
  {
    Color color =  canvas.getColorTable().lookup(colorKey);
    if (color != null)
      changeColor(logicalColor, color);
  }

  @Override
  public Object[] getLogicalColors()
  {
    return logicalColors;
  }

  private Segment[] makeDiagonalSegments (Point[] vertices,
					  int top_left_width,
					  int bottom_right_width)
  {
    int len = vertices.length;

    Segment[] segments = new Segment[(len - 1)];
    boolean isHorizontal = false;
    int heading = Segment.NO_HEADING;

    for (int i = 0; i<(len - 1) ; i++)
    {
      Point v1 = vertices[i];
      Point v2 = vertices[i+1];
      segments[i] = new Segment(isHorizontal,
				v1.x, v1.y, v2.x, v2.y,
				heading);
    }
    return segments;
  }
  
  private Segment[] makeOrthogonalSegments (Point[] vertices,
					    int top_left_width,
					    int bottom_right_width)
  {
    int len = vertices.length;
    Segment[] segments = new Segment[(len - 1)];

    for (int i = 0; i<(len - 1) ; i++)
    {
      Point v1 = vertices[i];
      Point v2 = vertices[i+1];
      boolean isHorizontal = (v1.y == v2.y);

      segments[i]
          = new Segment(isHorizontal,
                 0, 0, 0, 0,
                 (isHorizontal ?
                 (v1.x > v2.x ? Segment.LEFT : Segment.RIGHT) :
                    (v1.y > v2.y ? Segment.TOP : Segment.BOTTOM)));
    }
    for (int i = 0; i < (len - 1) ; i++)
    {
      int left,top,right,bottom;
      Segment segment = segments[i];
      Point v1 = vertices[i];
      Point v2 = vertices[i+1];
      int prev_heading 
          = (i == 0) ? Segment.NO_HEADING : segments[i-1].heading;
      int next_heading
          = (i == (len - 2)) ? Segment.NO_HEADING : segments[i+1].heading;

      

      if (segment.isHorizontal)
      {
        left = (segment.heading == Segment.RIGHT) ? v1.x : v2.x;
        right = (segment.heading == Segment.RIGHT) ? v2.x : v1.x;
        top = v1.y - top_left_width;
        bottom = v1.y + bottom_right_width;
      }
      else
      {
        left = v1.x - top_left_width;
        right = v1.x + bottom_right_width;
        top = (segment.heading == Segment.TOP) ? v2.y : v1.y;
        bottom = (segment.heading == Segment.TOP) ? v1.y : v2.y;
      }
      if (((segment.heading == Segment.RIGHT) &&
           ((prev_heading == Segment.TOP) || 
            (prev_heading == Segment.BOTTOM))) ||
          ((segment.heading == Segment.LEFT) &&
           ((next_heading == Segment.TOP) ||
            (next_heading == Segment.BOTTOM))))
        left -= top_left_width;
      if (((segment.heading == Segment.RIGHT) &&
           ((next_heading == Segment.TOP) || 
            (next_heading == Segment.BOTTOM))) ||
          ((segment.heading == Segment.LEFT) &&
           ((prev_heading == Segment.TOP) ||
            (prev_heading == Segment.BOTTOM))))
        right += bottom_right_width;
      if (((segment.heading == Segment.TOP) &&
           ((next_heading == Segment.RIGHT) || 
            (next_heading == Segment.LEFT))) ||
          ((segment.heading == Segment.BOTTOM) &&
           ((prev_heading == Segment.RIGHT) ||
            (prev_heading == Segment.LEFT))))
        top -= top_left_width;
      if (((segment.heading == Segment.TOP) &&
           ((prev_heading == Segment.RIGHT) || 
            (prev_heading == Segment.LEFT))) ||
          ((segment.heading == Segment.BOTTOM) &&
           ((next_heading == Segment.RIGHT) ||
            (next_heading == Segment.LEFT))))
        bottom += bottom_right_width;

      segment.left = left;
      segment.top = top;
      segment.right = right;
      segment.bottom = bottom;
      if (connectionElementDebugP)
	System.out.println("seg ltrb = ("+left+", "+top+", "+right
			   +", "+bottom+") heading="+segment.heading+
			   "horizp="+segment.isHorizontal);
    }
    return segments;
  }

  public void setPaintMode(boolean paintMode) {
    this.paintMode = paintMode;
  }

  private Color getXORColor(Color color)
  {
    int red = color.getRed(), green = color.getGreen(), blue = color.getBlue();
    Color bg = canvas.getBackgroundColor();
    Color newColor = new Color(255-red,255-green,255-blue);
    if (newColor.equals(bg))
      newColor = new Color((red + bg.getRed())/2,
			   (green + bg.getGreen())/2,
			   (blue + bg.getBlue())/2);
    return newColor;
  }
  private synchronized void paintDiagonalConnection(Graphics g,
						    int shift_x,
						    int shift_y)
  {
    int length = segments.length;
    Color color = colorPattern[0];
    g.setColor(color);
    for (int i = 0; i<length ; i++)
    {
      Segment segment = segments[i];
      if (!paintMode) 
	g.setXORMode(getXORColor(color));
      g.drawLine(segment.left+shift_x, segment.top+shift_y,
		 segment.right+shift_x, segment.bottom+shift_y);
      if (getDirected())
	drawArrowsForDiagonalSegment(g, segment, shift_x, shift_y);
    }
  }

  private static final double DESIRED_DISTANCE_BETWEEN_ARROWS_ON_LINK = 300.0;

  private void drawArrowsForDiagonalSegment(Graphics g, Segment segment,
					    int shift_x, int shift_y) {
    int xStart = segment.left;
    int yStart = segment.top;
    int xEnd = segment.right;
    int yEnd = segment.bottom;
    double xDelta = (double)(xEnd - xStart);
    double yDelta = (double)(yEnd - yStart);
    double length = Math.sqrt(xDelta*xDelta + yDelta*yDelta);
    if ((int)Math.round(length) == 0)
      return;

    int numberOfArrows =
      (int)Math.max(1, MathUtils.floor(length, DESIRED_DISTANCE_BETWEEN_ARROWS_ON_LINK));
    double spacing = Math.round(length/((double)(numberOfArrows + 1)));

    double cos = xDelta/length;
    double sin = yDelta/length;

    for (int i = 1; i <= numberOfArrows; i++){
      double distanceAlongLink = spacing*(double)i;
      double vertexX = xStart + cos*distanceAlongLink;
      double vertexY = yStart + sin*distanceAlongLink;
      // The naming conventions for the arrow parts are based on drawing
      // a right-facing arrow  on a horizontal line. The coordinates
      // are in Euclidean space, the reflection in the Y-axis is performed
      // along with the rotation around the vertex.
      int arrowTopX = computeArrowX(cos, sin, vertexX,true) + shift_x;
      int arrowTopY = computeArrowY(cos, sin, vertexY, true) + shift_y;
      int arrowBottomX = computeArrowX(cos, sin, vertexX, false) + shift_x;
      int arrowBottomY = computeArrowY(cos, sin, vertexY, false) + shift_y;
      int arrowPointX = (int)Math.round(vertexX) + shift_x;
      int arrowPointY = (int)Math.round(vertexY) + shift_y;

      g.drawLine(arrowTopX, arrowTopY, arrowPointX, arrowPointY);
      g.drawLine(arrowBottomX, arrowBottomY, arrowPointX, arrowPointY);
    }
  }

  // The arrow is initially assumed to be a right facing arrow
  // along the x axis with
  // the vertex at the origin of Euclidean space. To get the arrow
  // facing in the correct direction in "awt space" on a given line
  // we first reflect along the x-axis, then rotate to the
  // angle of the line.
  // The initial co-ordinates for the arrow head ends are:
  // TOP: (-10, 10); BOTTOM: (-10, -10)
  //
  // The transformation matrix is:
  // cos  sin
  // sin -cos

  private int diagonalArrowSize = 10;

  private int computeArrowX(double cos, double sin,
			       double translate,
			       boolean isTop) {
    // cos*x + sin*y
    double arrowDouble = (double)diagonalArrowSize;
    double newX =
      isTop ? -cos*arrowDouble + sin*arrowDouble : // (-10, 10)
      (-cos*arrowDouble - sin*arrowDouble);        // (-10, -10)
    return (int)Math.round(newX + translate);
  }

  private int computeArrowY(double cos, double sin,
			       double translate,
			       boolean isTop) {
    // sin*x - cos*y
    double arrowDouble = (double)diagonalArrowSize;
    double newY = 
      isTop ? -sin*arrowDouble - cos*arrowDouble : // (-10, 10)
      -sin*arrowDouble + cos*arrowDouble ;         // (-10, 10)
    return (int)Math.round(newY + translate);
  }

  int arrowSize = 16;
  private void drawArrow(Graphics g,
			 int heading,
			 int x,
			 int y)
  {
    g.setColor(colorPattern[0]);
    switch (heading) {
    case Segment.TOP:
      y-=arrowSize/2;
      g.drawLine(x-arrowSize, y+arrowSize, x,y);
      g.drawLine(x+arrowSize, y+arrowSize, x,y);
      break;
    case Segment.BOTTOM:
      y+=arrowSize/2;
      g.drawLine(x-arrowSize, y-arrowSize, x,y);
      g.drawLine(x+arrowSize, y-arrowSize, x,y);
      break;
    case Segment.RIGHT:
      x+=arrowSize/2;
      g.drawLine(x,y, x-arrowSize, y+arrowSize);
      g.drawLine(x,y, x-arrowSize, y-arrowSize);
      break;      
    case Segment.LEFT:
      x-=arrowSize/2;
      g.drawLine(x,y, x+arrowSize, y+arrowSize);
      g.drawLine(x,y, x+arrowSize, y-arrowSize);
      break;      
    }
  }

  static final int minimumDistanceBetweenArrows = 50;
  static final int desiredDistanceBetweenArrows = 100;
  static final int desiredDistanceBetweenArrowsOnLink = 300;
       
  @Override
  public synchronized void paint (Graphics g,
		    int shift_x, int shift_y)
  {
    if (style == DIAGONAL) {
      paintDiagonalConnection(g, shift_x, shift_y);
      return;
    }
    int stripe_count = colorPattern.length;
    int length = segments.length;

    int distanceFromLastSegment=0;
    for (int i = 0; i<length ; i++)
    {
      Segment segment = segments[i];
      int prev_heading 
          = (i == 0) ? Segment.NO_HEADING : segments[i-1].heading;
      int next_heading
          = (i == (length - 1)) ? Segment.NO_HEADING : segments[i+1].heading;

      int iterate_start, iterate_end , iterate_increment;
      if (directed) {
	int segmentWidth =
	    segment.isHorizontal?
	    Math.abs(segment.right-segment.left):
	    Math.abs(segment.top-segment.bottom);		     
	distanceFromLastSegment+=segmentWidth;
	if (!(((i==length-1) &&
	       (distanceFromLastSegment > minimumDistanceBetweenArrows)) ||
	      (distanceFromLastSegment > desiredDistanceBetweenArrows))) {
	  distanceFromLastSegment+=segmentWidth;
	} else {
	  int numArrowsForSegment =
	    Math.max(1, segmentWidth/desiredDistanceBetweenArrowsOnLink);
	  int spacingBetweenArrowsOnSegment =
	    segmentWidth/(1+numArrowsForSegment);
	  distanceFromLastSegment = spacingBetweenArrowsOnSegment;
	  for (int arrowNumber=1;
	       arrowNumber<=numArrowsForSegment;
	       arrowNumber++) {
	    int positionAlongSegment =
	      arrowNumber*spacingBetweenArrowsOnSegment;
	    int arrowX, arrowY;
	    if (segment.isHorizontal) {
	      arrowX = shift_x + segment.left + positionAlongSegment;
	      arrowY = shift_y + (segment.top + segment.bottom)/2;
	    } else {
	      arrowX = shift_x + (segment.left + segment.right)/2;
	      arrowY = shift_y + segment.top + positionAlongSegment;
	    }
	    drawArrow(g, segment.heading, arrowX,arrowY);
	  }
	}
      }
      
      if (segment.heading == Segment.TOP || 
          segment.heading == Segment.RIGHT)
      {
          iterate_start = 0;
          iterate_end = stripe_count;
          iterate_increment = 1;
      }
      else
      {
          iterate_start = stripe_count - 1;
          iterate_end = -1;
          iterate_increment = -1;
      }

      int offset = 0;
      int new_offset = 0;
      for (int j = iterate_start ; j != iterate_end ; 
           j += iterate_increment)
      {
         int stripe_left, stripe_top , stripe_right, stripe_bottom;
         int stripe_width = stripeWidths[j];
         
         offset = new_offset;
         new_offset += stripe_width;
         if (segment.isHorizontal)
         {
           if (segment.heading == Segment.RIGHT)
           {
             switch (prev_heading)
             {
             case Segment.TOP:
                 stripe_left = segment.left + offset;
                 break;
               case Segment.BOTTOM:
                 stripe_left = segment.left + (width - new_offset);
                 break;
             default:
                 stripe_left = segment.left;
             }
             switch (next_heading)
             {
             case Segment.TOP:
                 stripe_right = segment.right - (width - new_offset);
                 break;
               case Segment.BOTTOM:
                 stripe_right = segment.right - offset;
                 break;
             default:
                 stripe_right = segment.right; 
             }
             stripe_top = segment.top + offset;
             stripe_bottom = segment.top + new_offset;
           }
           else
           {
             switch (next_heading)
             {
             case Segment.TOP:
                 stripe_left = segment.left + (width - new_offset);
                 break;
               case Segment.BOTTOM:
                 stripe_left = segment.left + offset;
                 break;
             default:
                 stripe_left = segment.left;
             }
             switch (prev_heading)
             {
             case Segment.TOP:
                 stripe_right = segment.right - offset;
                 break;
               case Segment.BOTTOM:
                 stripe_right = segment.right - (width - new_offset);
                 break;
             default:
                 stripe_right = segment.right; 
             }
             stripe_top = segment.top + offset;
             stripe_bottom = segment.top + new_offset;
           }
         }
         else
         {
           if (segment.heading == Segment.TOP)
           {
             switch (next_heading)
             {
             case Segment.LEFT:
                 stripe_top = segment.top + (width - new_offset);
                 break;
               case Segment.RIGHT:
                 stripe_top = segment.top + offset;
                 break;
             default:
                 stripe_top = segment.top;
             }
             switch (prev_heading)
             {
             case Segment.LEFT:
                 stripe_bottom = segment.bottom - offset;
                 break;
               case Segment.RIGHT:
                 stripe_bottom = segment.bottom - (width - new_offset);
                 break;
             default:
                 stripe_bottom = segment.bottom; 
             }
             stripe_left = segment.left + offset;
             stripe_right = segment.left + new_offset;
           }
           else
           {
             switch (prev_heading)
             {
             case Segment.RIGHT:
                 stripe_top = segment.top + (width - new_offset);
                 break;
               case Segment.LEFT:
                 stripe_top = segment.top + offset;
                 break;
             default:
                 stripe_top = segment.top;
             }
             switch (next_heading)
             {
             case Segment.LEFT:
                 stripe_bottom = segment.bottom - (width - new_offset);    
                 break;
               case Segment.RIGHT:
                 stripe_bottom = segment.bottom - offset;
                 break;
             default:
                 stripe_bottom = segment.bottom;
             }
             stripe_left = segment.left + offset;
             stripe_right = segment.left + new_offset;
           } /* inner else */
         } /* outer else */

         /* weds - draw a rectangle for the segments stripe */
         /* System.out.println("i="+i+" j="+j+" color="+colorPattern[j]);
         System.out.println("stripe-seg-ltrb="+stripe_left+" "+
                            stripe_top+" "+stripe_right+" "+
                            stripe_bottom); */
	 Color color = colorPattern[j];
	 //color should never be null. This is a bug. Fix after beta. pbk.
	 if (color != null && color != G2ColorMap.TRANSPARENT) {
	   g.setColor(color);
	   if (!paintMode) 
	     g.setXORMode(getXORColor(color));
	   g.fillRect(stripe_left+shift_x, stripe_top +shift_y,
		      stripe_right - stripe_left, 
		      stripe_bottom - stripe_top);
	 }
      } /* for j -- stripe loop */
    } /* for i -- segment loop */
  }

  @Override
  public void paint(Graphics g)
  {
    paint(g, (- outerBounds.x) , (- outerBounds.y));
  }
  
  @Override
  public void shift (int shift_x, int shift_y)
  {
    int length = segments.length;

    for (int i = 0; i<length ; i++)
    {
      Segment segment = segments[i];
      segment.left += shift_x;
      segment.top += shift_y;
      segment.right += shift_x;
      segment.bottom += shift_y;
      bounds[i].x += shift_x;
      bounds[i].y += shift_y;
    }
    setLocation(outerBounds.x + shift_x, outerBounds.y + shift_y);
    //outerBounds.translate(shift_x,shift_y);
  }

  @Override
  public void setLocation(int x, int y) {
    outerBounds.x = x;
    outerBounds.y = y;
    super.setLocation(x, y);
  }
  
  @Override
  public void setSize(int width, int height) {
    outerBounds.width = width;
    outerBounds.height = height;
    super.setSize(width,height);
  }
  
  /* coordinates are logical */
  @Override
  public boolean contains(int x, int y)
  {
    x += outerBounds.x; y += outerBounds.y;
    for (int i = 0 ; i<segments.length ; i++) {
      
      if (segments[i].contains(x,y))
	return true;
    }
    return false;
  }

  @Override
  public boolean inside(int x, int y)
  {
    return contains(x, y);
  }


  @Override
  public Rectangle[] getExactBounds ()
  {
     return bounds;
  }


}



