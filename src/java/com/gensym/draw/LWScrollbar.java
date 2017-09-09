package com.gensym.draw;

import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.Vector;
import com.gensym.uiutil.UIHeartBeat;
import com.gensym.uiutil.UIHeartBeatRecipient;

public class LWScrollbar extends Component
   implements Adjustable, MouseListener, MouseMotionListener, Serializable, UIHeartBeatRecipient
{

  /*
   * Allow deserialization
   */
  static final long serialVersionUID = 3826353377709244048L;

  public static final int     HORIZONTAL = 0;
  public static final int     VERTICAL   = 1;
  private static final int START_INTERVAL = 500, DUB_INTERVAL = 150;

  int value;
  int maximum;
  int minimum;
  int visibleAmount;
  int orientation;
  int unitIncrement = 1;
  int blockIncrement = 10;
  Rectangle decrementRect;
  Rectangle incrementRect;
  Rectangle elevatorRect;
  Rectangle thumbRect;
  Rectangle ghostRect;

  transient private Point startPoint;
  transient private int gesture = 0;
  transient private boolean mouseIsDown = false;

  private static final int NO_GESTURE = 0; 
  private static final int INCREMENT = 1;
  private static final int DECREMENT = 2;
  private static final int BLOCK_INCREMENT = 3;
  private static final int BLOCK_DECREMENT = 4;
  private static final int THUMB_DRAG = 5;

  private int[] arrowX = { 0 , 0 , 0 };
  private int[] arrowY = { 0 , 0 , 0 };
  private Polygon triangle = new Polygon(arrowX, arrowY, 3);

  Vector listeners = new Vector();

  private transient boolean receivingHeartbeat = false;

  public LWScrollbar (int orientation, int value, int visible,
	       int minimum, int maximum)
  {
    switch (orientation) 
      {
      case HORIZONTAL:
      case VERTICAL:
	this.orientation = orientation;
	break;
      default:
	throw new IllegalArgumentException("illegal scrollbar orientation");
      }
    addMouseListener(this);
    addMouseMotionListener(this);
    setUpRegions();
    setValues(value, visible, minimum, maximum);
  }

  @Override
  public void setBounds(int x, int y, int width, int height)
  {
    super.setBounds(x,y,width,height);
    setUpRegions();
    if (elevatorRect != null)
      calculateThumbRect();
    repaint();
  }

  @Override
  public void setBounds(Rectangle r)
  {
    setBounds(r.x,r.y,r.width,r.height);
  }

  @Override
  public Dimension getPreferredSize()
  {
    if (orientation == HORIZONTAL)
      return new Dimension(100,20);
    else
      return new Dimension(20,100);
  }

  @Override
  public int getOrientation() {
    return orientation;
  }

  public synchronized void setOrientation(int orientation) {
    if (orientation == this.orientation) {
      return;
    }
    switch (orientation) {
    case HORIZONTAL:
    case VERTICAL:
      this.orientation = orientation;
      break;
    default:
      throw new IllegalArgumentException("illegal scrollbar orientation");
    }
    setUpRegions();
    setValues(value, visibleAmount, minimum, maximum);
    repaint();
  }

  @Override
  public int getValue() {
    return value;
  }


  @Override
  public synchronized void setValue(int newValue) 
  {
    setValues(newValue, visibleAmount, minimum, maximum);
  }
  
  @Override
  public int getMinimum() {
    return minimum;
  }

  @Override
  public synchronized void setMinimum(int newMinimum) 
  {
    setValues(value, visibleAmount, newMinimum, maximum);
  }

  @Override
  public int getMaximum() {
    return maximum;
  }

  @Override
  public synchronized void setMaximum(int newMaximum) {
    setValues(value, visibleAmount, minimum, newMaximum);
  }
  
  @Override
  public int getVisibleAmount() {
    return getVisible();
  }
  
  public int getVisible() {
    return visibleAmount;
  }
  
  @Override
  public synchronized void setVisibleAmount(int newAmount) {
    setValues(value, newAmount, minimum, maximum);
  }
  
  @Override
  public synchronized void setUnitIncrement(int v) {
    unitIncrement = v;
  }

  @Override
  public int getUnitIncrement() {
    return unitIncrement; 
  }

  @Override
  public synchronized void setBlockIncrement(int v) {
    blockIncrement = v;
  }

  @Override
  public int getBlockIncrement() {
    return blockIncrement;
  }


  public synchronized void setValues(int value, int visible, 
				     int minimum, int maximum) 
  {
    if (maximum <= minimum) {
      maximum = minimum + 1;
    }
    if (visible > maximum - minimum) {
      visible = maximum - minimum;
    }
    if (visible < 1) {
      visible = 1;
    }
    if (value < minimum) {
      value = minimum;
    }
    if (value > maximum - visible) {
      value = maximum - visible;
    }
    
    if (this.value != value ||
	this.visibleAmount != visible ||
	this.minimum != minimum ||
	this.maximum != maximum)
      {
	this.value = value;
	this.visibleAmount = visible;
	this.minimum = minimum;
	this.maximum = maximum;
	
	if (elevatorRect != null)
	  {
	    calculateThumbRect();
	    // I hope this merely enqueue an invalid region
	    // rather than painting recursively
	    repaintElevator();
	  }
      }
  }

  private void repaintElevator()
  {
    repaint(elevatorRect.x,elevatorRect.y,
	    elevatorRect.width,elevatorRect.height);
  }

  private void calculateThumbRect()
  {
    if (value <= minimum && value+visibleAmount >= maximum)
      thumbRect = null;
    else if (orientation == HORIZONTAL)
      {
	thumbRect
	  = new Rectangle(elevatorRect.x + scale(value,0,elevatorRect.width),
			  0,
			  scale(minimum+visibleAmount,0,elevatorRect.width),
			  elevatorRect.height);
      }
    else
      {
	thumbRect
	  = new Rectangle(0,
			  elevatorRect.y + scale(value,0,elevatorRect.height),
			  elevatorRect.width,
			  scale(minimum+visibleAmount,0,elevatorRect.height));
      }
  }

  private int scale(int x, int rangeMin, int rangeMax)
  {
    double portion 
      = ((double) (x - minimum)) / ((double) (maximum - minimum));

    double rangePortion 
      = portion * ((double) (rangeMax - rangeMin));
    
    return rangeMin + (int)rangePortion;
  }

  private int inverseScale(int x, int rangeMin, int rangeMax)
  {
    double portion 
      = ((double) (x - rangeMin)) / ((double) (rangeMax - rangeMin));
    double domainPortion
      = portion * ((double) (maximum - minimum));
    return minimum + (int)domainPortion;
  }
  
  @Override
  public synchronized void addAdjustmentListener(AdjustmentListener l) 
  {
    listeners.addElement(l);
  }
  
  
  @Override
  public synchronized void removeAdjustmentListener(AdjustmentListener l) 
  {
    listeners.removeElement(l);
  }
  
  private void fireAdjustmentEvent(int type, int value)
  {
    AdjustmentEvent e 
      = new AdjustmentEvent(this,
			    AdjustmentEvent.ADJUSTMENT_VALUE_CHANGED,
			    type,
			    value);
    Vector listenersCopy = null;
    synchronized (listeners)
      {
	listenersCopy = (Vector) listeners.clone();
      }
    int i , size = listenersCopy.size();
    for (i=0; i<size; i++)
      {
	AdjustmentListener listener 
	  = (AdjustmentListener)listenersCopy.elementAt(i);
	listener.adjustmentValueChanged(e);
      }
  }
  
  @Override
  protected void processEvent(AWTEvent e) 
  {
    if (e instanceof AdjustmentEvent) 
      {
	processAdjustmentEvent((AdjustmentEvent)e);
	return;
      }
    super.processEvent(e);
  }
  
  protected void processAdjustmentEvent(AdjustmentEvent e) 
  {
    if (listeners != null) 
      {
	fireAdjustmentEvent(e.getAdjustmentType(),e.getValue());
      }
  }
  
  @Override
  protected String paramString() {
    return super.paramString() +
      ",val=" + value +
      ",vis=" + visibleAmount +
      ",min=" + minimum +
      ",max=" + maximum +
      ((orientation == VERTICAL) ? ",vert" : ",horz");
  }
  
  private void setUpRegions()
  {
    Dimension size = getSize();
    int width = size.width;
    int height = size.height;

    if (orientation == HORIZONTAL)
      {
	if (width > (2 * height))
	  {
	    decrementRect = new Rectangle(0,0,height,height);
	    incrementRect = new Rectangle(width-height,0,height,height);
	    elevatorRect = new Rectangle(height,0,width - (2 * height),height);
	  }
	else
	  {
	    int halfWidth = width >> 1;
	    decrementRect = new Rectangle(0,0,halfWidth,height);
	    incrementRect = new Rectangle(halfWidth,0,width - halfWidth,height);
	    elevatorRect = null;
	  }
      }
    else
      {
	if (height > (2 * width))
	  {
	    decrementRect = new Rectangle(0,0,width,width);
	    incrementRect = new Rectangle(0,height-width,width,width);
	    elevatorRect = new Rectangle(0,width,width,height - (2 * width));
	  }
	else
	  {
	    int halfHeight = height >> 1;
	    decrementRect = new Rectangle(0,0,width,halfHeight);
	    incrementRect = new Rectangle(0,halfHeight,width,height - halfHeight);
	    elevatorRect = null;
	  }
      }
    thumbRect = null;
  }

  @Override
  public void setSize(int x, int y)
  {
    super.setSize(x,y);
  }

  private static final Color trackColor = new Color (224, 224, 224);
  
  @Override
  public void paint(Graphics g)
  {
    Dimension size = getSize();
    g.setColor(trackColor);
    g.fillRect(0,0,size.width,size.height);
    g.setColor(Color.gray);
    if (orientation == HORIZONTAL)
      {
	g.drawLine(decrementRect.width,0,
		   incrementRect.x,0);
	g.drawLine(decrementRect.width,size.height - 1,
		   incrementRect.x,size.height - 1);
      }
    else
      {
	g.drawLine(0,decrementRect.height,
		   0,incrementRect.y);
	g.drawLine(size.width - 1,decrementRect.height,
		   size.width - 1,incrementRect.y);
      }
    g.setColor(Color.lightGray);
    g.fill3DRect(decrementRect.x + 1,
		 decrementRect.y + 1,
		 decrementRect.width - 2,
		 decrementRect.height - 2,
		 true);
    g.setColor(Color.lightGray);
    g.fill3DRect(incrementRect.x + 1,
		 incrementRect.y + 1,
		 incrementRect.width - 2,
		 incrementRect.height - 2,
		 true);
    paintArrow(g,decrementRect,(orientation == HORIZONTAL),
	       false,Color.black);
    paintArrow(g,incrementRect,(orientation == HORIZONTAL),
	       true,Color.black);
    g.setColor(Color.lightGray);
    if (ghostRect != null)
      {
	//g.setColor(Color.blue);
	g.fill3DRect(ghostRect.x + 1,
		     ghostRect.y + 1,
		     ghostRect.width - 2,
		     ghostRect.height - 2,
		     true);
      }
    else if (thumbRect != null)
      {
	//g.setColor(Color.green);
	g.fill3DRect(thumbRect.x + 1,
		     thumbRect.y + 1,
		     thumbRect.width - 2,
		     thumbRect.height - 2,
		     true);
      }
  }

  private void paintArrow(Graphics g,Rectangle rect, boolean isHorizontal,
			  boolean isIncrement, Color color)
  {
    int midX = rect.x + (rect.width >> 1);
    int midY = rect.y + (rect.height >> 1);

    g.setColor(color);
    if (isHorizontal)
      {
	if (isIncrement)
	  {
	    arrowX[0] = midX + 2;
	    arrowY[0] = midY;
	    arrowX[1] = midX - 2;
	    arrowY[1] = midY - 4;
	    arrowX[2] = midX - 2;
	    arrowY[2] = midY + 4;
	    g.fillPolygon(new Polygon(arrowX, arrowY,3));
	  }
	else
	  {
	    arrowX[0] = midX - 2;
	    arrowY[0] = midY;
	    arrowX[1] = midX + 2;
	    arrowY[1] = midY - 4;
	    arrowX[2] = midX + 2;
	    arrowY[2] = midY + 4;
	    g.fillPolygon(new Polygon(arrowX, arrowY,3));
	  }
      }
    else
      {
	if (isIncrement)
	  {
	    arrowX[0] = midX;
	    arrowY[0] = midY + 2;
	    arrowX[1] = midX - 4;
	    arrowY[1] = midY - 2;
	    arrowX[2] = midX + 4;
	    arrowY[2] = midY - 2;
	    g.fillPolygon(new Polygon(arrowX, arrowY,3));
	  }
	else
	  {
	    //hack these numbers so that the up and down arrow look the same size
	    arrowX[0] = midX;
	    arrowY[0] = midY - 3;
	    arrowX[1] = midX - 5;
	    arrowY[1] = midY + 2;
	    arrowX[2] = midX + 5;
	    arrowY[2] = midY + 2;
	    g.fillPolygon(new Polygon(arrowX, arrowY,3));
	  }
      }
  }

  @Override
  public void mouseClicked(MouseEvent e)
  {}
  
  @Override
  public void mousePressed(MouseEvent e)
  {
    Point point = e.getPoint();
    /*System.out.println("mouse pressed "+point+" thumb "+thumbRect +
		       " IncremmentRect = " + incrementRect +
		       " DecrementRect =  " + decrementRect);
		       */
    if (incrementRect.contains(point)) {
      gesture = INCREMENT;
      UIHeartBeat.registerForUIHeartBeat (this, START_INTERVAL, DUB_INTERVAL);
    } else if (decrementRect.contains(point)) {
      gesture = DECREMENT;
      UIHeartBeat.registerForUIHeartBeat (this, START_INTERVAL, DUB_INTERVAL);
    } else if (thumbRect == null)
      gesture = NO_GESTURE;
    else if (thumbRect.contains(point))
      {
	gesture = THUMB_DRAG;
	ghostRect = new Rectangle(thumbRect);
	repaintElevator();
      }
    else if (((orientation == HORIZONTAL) && 
	      (point.x < thumbRect.x))        ||
	     ((orientation == VERTICAL) &&
	      (point.y < thumbRect.y))) {
      gesture = BLOCK_DECREMENT;
      UIHeartBeat.registerForUIHeartBeat (this, START_INTERVAL, DUB_INTERVAL);
    } else {
      gesture = BLOCK_INCREMENT;
      UIHeartBeat.registerForUIHeartBeat (this, START_INTERVAL, DUB_INTERVAL);
    }
	    
    // System.out.println("mousePressed gesture = "+gesture);
    mouseIsDown = true;
    if (gesture != NO_GESTURE)
      {
	startPoint = point;
      }

  }

  @Override
  public void dub () {
    switch (gesture)
      {
      case INCREMENT:
	fireAdjustmentEvent(AdjustmentEvent.UNIT_INCREMENT,unitIncrement);
	break;
      case DECREMENT:
	fireAdjustmentEvent(AdjustmentEvent.UNIT_DECREMENT,unitIncrement);
	break;
      case BLOCK_INCREMENT:
	fireAdjustmentEvent(AdjustmentEvent.BLOCK_INCREMENT,blockIncrement);
	break;
      case BLOCK_DECREMENT:
	fireAdjustmentEvent(AdjustmentEvent.BLOCK_DECREMENT,blockIncrement);
	break;
      }
  }
  
  @Override
  public void mouseReleased(MouseEvent e)
  {
    Point point = e.getPoint();
    // System.out.println("mouse released "+point);
    switch (gesture)
      {
      case THUMB_DRAG:
	if (elevatorRect != null &&
	    thumbRect != null)
	  {
	    int min = 0, max = 1, pointInElevator = 0;
	    if (orientation == HORIZONTAL)
	      {
		min = elevatorRect.x;
		max = elevatorRect.x + elevatorRect.width;
		pointInElevator = ghostRect.x;
	      }
	    else
	      {
		min = elevatorRect.y;
		max = elevatorRect.y + elevatorRect.height;
		pointInElevator = ghostRect.y;
	      }
	    fireAdjustmentEvent(AdjustmentEvent.TRACK,
				inverseScale(pointInElevator,min,max));
	    repaintElevator();
	  }
	ghostRect = null;
	break;
      case INCREMENT:
	if (incrementRect.contains(point))
	  fireAdjustmentEvent(AdjustmentEvent.UNIT_INCREMENT,unitIncrement);
	UIHeartBeat.unregisterForUIHeartBeat (this);
	break;
      case DECREMENT:
	if (decrementRect.contains(point))
	  fireAdjustmentEvent(AdjustmentEvent.UNIT_DECREMENT,unitIncrement);
	UIHeartBeat.unregisterForUIHeartBeat (this);
	break;
      case BLOCK_DECREMENT:
      case BLOCK_INCREMENT:
	UIHeartBeat.unregisterForUIHeartBeat (this);
	if (elevatorRect != null &&
	    elevatorRect.contains(point) &&
	    thumbRect != null &&
	    !thumbRect.contains(point))
	  {
	    if (gesture == BLOCK_DECREMENT &&
		(((orientation == HORIZONTAL) && 
		  (point.x < thumbRect.x))    ||
		 ((orientation == VERTICAL) &&
		  (point.y < thumbRect.y))))
	      fireAdjustmentEvent(AdjustmentEvent.BLOCK_DECREMENT,blockIncrement);
	    if (gesture == BLOCK_INCREMENT &&
		((orientation == HORIZONTAL) ?
		 (point.x > thumbRect.x + thumbRect.width) :
		 (point.y > thumbRect.y + thumbRect.height)))
	      fireAdjustmentEvent(AdjustmentEvent.BLOCK_INCREMENT,blockIncrement);
	  }
	break;
      }
    mouseIsDown = false;
    gesture = NO_GESTURE;
  }
  
  @Override
  public void mouseEntered(MouseEvent e)
  {}

  @Override
  public void mouseExited(MouseEvent e)
  {}

  @Override
  public void mouseDragged(MouseEvent e)
  {
    Point point = e.getPoint();
    switch (gesture)
      {
      case THUMB_DRAG:
	if (orientation == HORIZONTAL)
	  {
	    int dragOffset = pinTrackRange(point);
	    int newX = thumbRect.x + (dragOffset -  startPoint.x);
	    if (newX != ghostRect.x)
	      {
		ghostRect.x = newX;
		repaintElevator();
	      }
	  }
	else 
	  {
	    int dragOffset = pinTrackRange(point);
	    int newY = thumbRect.y + (dragOffset -  startPoint.y);
	    if (newY != ghostRect.y)
	      {
		ghostRect.y = newY;
		repaintElevator();
	      }
	  }
	break;
      case INCREMENT:
	break;
      case DECREMENT:
	break;
      }
  }

  private int pinTrackRange(Point point)
  {
    if (orientation == HORIZONTAL)
      {
	int lowBound = elevatorRect.x + (startPoint.x - thumbRect.x);
	int highBound = ((elevatorRect.x + elevatorRect.width) -
			 ((thumbRect.x + thumbRect.width) - 
			  startPoint.x));
	return Math.min(Math.max(point.x,lowBound),
				  highBound);
      }
    else 
      {
	int lowBound = elevatorRect.y + (startPoint.y - thumbRect.y);
	int highBound = ((elevatorRect.y + elevatorRect.height) -
			 ((thumbRect.y + thumbRect.height) - 
			  startPoint.y));
	return Math.min(Math.max(point.y,lowBound),
			highBound);
      }
  }
      
  
  @Override
  public void mouseMoved(MouseEvent e)
  {}
  
}
