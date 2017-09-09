package com.gensym.beaneditor;

import java.awt.*;
import com.gensym.draw.*;
import java.util.Vector;
import com.gensym.util.Structure;

public class Wrapper extends BasicDrawElement implements java.io.Serializable
{

  /*
   * Allow serialization
   */
  static final long serialVersionUID = 6042789294360642527L;
  
  public static final int NOT_SELECTED = -1;
  public static final int TOP_LEFT     = 0;
  public static final int TOP          = 1;
  public static final int TOP_RIGHT    = 2;
  public static final int RIGHT        = 3;
  public static final int BOTTOM_RIGHT = 4;
  public static final int BOTTOM       = 5;
  public static final int BOTTOM_LEFT  = 6;
  public static final int LEFT         = 7;

  private Color color;
  private Rectangle[] bounds;
  private Vector ports = new Vector();  
  private int margin = -6; // between wrapper and ports  (-border to make port flush)
  private Class clazz;
  public  Object bean;
  private Structure info; // extra info storage

  // Drawing Parameters
  private static final int border = 6;
  private static final int sz = 5; // resize handle size

  // Non-component painting properties
  private transient java.awt.Image img = null;
  private transient boolean size32x32 = false;

  // Editing State
  transient boolean selected = false;
  private transient int selectedWrapperCorner = NOT_SELECTED;
  private transient ComponentBeanAdapter componentBeanAdapter = null;
  
  // KnowledgeLinks
  Vector knowledgeLinks = new Vector();

  public Wrapper (Color color, Class clazz, int x, int y, int w, int h)
  {
    this.clazz = clazz;
    bounds = new Rectangle[1];
    bounds[0] = new Rectangle(x - border, y - border,
                              w + border * 2, h + border * 2);
    setLocation(x - border, y - border);
    setSize(w + border * 2, h + border * 2);
    this.color = color;
  }

  @Override
  public void setSize(int width, int height)
  {

    if (bean instanceof Component)
      {
	Component c = (Component) bean;
	int beanWidth = width - 2 * border;
	int beanHeight = height - 2 * border;
	Dimension max = c.getMaximumSize();
	Dimension min = c.getMinimumSize();
	int newComponentWidth = Math.min(max.width,Math.max(min.width,beanWidth));
	int newComponentHeight = Math.min(max.height,Math.max(min.height,beanHeight));
	width = newComponentWidth + 2 * border;
	height = newComponentHeight + 2 * border;
      }
    else{
      if (width < 10) width = 10;
      if (height < 10) height = 10;
    }
    Rectangle b_rect = bounds[0];
    bounds[0] = new Rectangle(b_rect.x, b_rect.y,
			      width, height);
    // System.out.println("wrapper set size called with b="+bean);
    super.setSize(width, height);
  }

  @Override
  public void setLocation(int x, int y)
  {
    //Rectangle logicalBounds = ((EditorFrame)com.gensym.core.UiApplication.getCurrentFrame()).getCanvas().getLogicalBounds();
    Container parent = getParent();
    if (parent != null && parent instanceof BeanCanvas){
      Rectangle logicalBounds = ((BeanCanvas)parent).getLogicalBounds();
      Rectangle b_rect = bounds[0];
      if (x < logicalBounds.x) 
	x = logicalBounds.x;
      else {
	int maxWidth = logicalBounds.x + logicalBounds.width - b_rect.width;
	if (x > maxWidth)
	  x = maxWidth;
      }
      if (y < logicalBounds.y) 
	y = logicalBounds.y;
      else {
	int maxHeight = logicalBounds.y + logicalBounds.height - b_rect.height;
	if (y > maxHeight)
	  y = maxHeight;
      }
      bounds[0] = new Rectangle(x, y,
				b_rect.width, b_rect.height);
    }
    // System.out.println("wrapper set location called with b="+bean);
    super.setLocation(x, y);
  }

  Port[] getPorts()
  {
    Port[] portArray = new Port[ports.size()];
    ports.copyInto(portArray);
    return portArray;
  }

  void ensureBeanBounds()
  {
    if (bean instanceof Component)
      {
	Component c = (Component) bean;
	Dimension size = getSize();
	Point location = getLocation();
	c.setLocation(location.x + border, location.y + border);
	c.setSize(size.width - 2 * border, size.height - 2 * border);
	c.validate();
      }
  }

  void updateForScroll(){
    Point offset = canvas.getScrollOffset();
    updateForScroll(offset.x, offset.y);
  }

  void updateForScroll(int shiftX, int shiftY)
  {
    if (bean instanceof Component)
      {
	Component c = (Component)bean;
	if (!(c.getPeer() instanceof java.awt.peer.LightweightPeer)){
	  Point point = c.getLocation();
	  c.setLocation(point.x + shiftX,
			point.y + shiftY);
	}
      }
  }

  Point getResizeCorner()
  {
    int resize_start_x = 0;
    int resize_start_y = 0;
    switch(selectedWrapperCorner)
      {
      case TOP_LEFT:
	resize_start_x = getLocation().x + getSize().width;
	resize_start_y = getLocation().y + getSize().height;
	break;
      case TOP:
	resize_start_x = getLocation().x;
	resize_start_y = getLocation().y + getSize().height;
	break;
      case TOP_RIGHT:
	resize_start_x = getLocation().x;
	resize_start_y = getLocation().y + getSize().height;
	break;
      case RIGHT:
	resize_start_x = getLocation().x;
	resize_start_y = getLocation().y;
	break;
      case BOTTOM_RIGHT:
	resize_start_x = getLocation().x;
	resize_start_y = getLocation().y;
	break;
      case BOTTOM:
	resize_start_x = getLocation().x;
	resize_start_y = getLocation().y;
	break;
      case BOTTOM_LEFT:
	resize_start_x = getLocation().x + getSize().width;
	resize_start_y = getLocation().y;
	break;
      case LEFT:
	resize_start_x = getLocation().x + getSize().width;
	resize_start_y = getLocation().y;
	break;                  
      }
    return new Point (resize_start_x, resize_start_y);
  }

  void setSelectedWrapperCorner(int x, int y)
  {
    Rectangle b_rect = bounds[0];

    if (x < sz)
      {
	if (y < sz)
	  {
	    selectedWrapperCorner = TOP_LEFT;
	  }
	else if (y > (b_rect.height - sz))
	  {
	    selectedWrapperCorner = BOTTOM_LEFT;
	  }
	else if (y > b_rect.height/2 - sz/2 &&
		 y < b_rect.height/2 + sz/2)
	  {
	    selectedWrapperCorner = LEFT;
	  }
	else
	  selectedWrapperCorner = NOT_SELECTED;

      }
    else if (x > (b_rect.width - sz))
      {
	if (y < sz)
	  {
	    selectedWrapperCorner = TOP_RIGHT;
	  }
	else if (y > (b_rect.height - sz))
	  {
	    selectedWrapperCorner = BOTTOM_RIGHT;
	  }
	else if (y > b_rect.height/2 - sz/2 &&
		 y < b_rect.height/2 + sz/2)
	  {
	    selectedWrapperCorner = RIGHT;
	  }
	else
	  selectedWrapperCorner = NOT_SELECTED;

      }
    else if (y < sz)
      {
	if (x < sz)
	  {
	    selectedWrapperCorner = TOP_LEFT;
	  }
	else if (x > (b_rect.width - sz))
	  {
	    selectedWrapperCorner = TOP_RIGHT;
	  }
	else if (x > b_rect.width/2 - sz/2 &&
		 x < b_rect.width/2 + sz/2)
	  {
	    selectedWrapperCorner = TOP;
	  }
	else
	  selectedWrapperCorner = NOT_SELECTED;
      }
    else if (y > (b_rect.height - sz))
      {
	if (x < sz)
	  {
	    selectedWrapperCorner = BOTTOM_LEFT;
	  }
	else if (x > (b_rect.width - sz))
	  {
	    selectedWrapperCorner = BOTTOM_RIGHT;
	  }
	else if (x > b_rect.width/2 - sz/2 &&
		 x < b_rect.width/2 + sz/2)
	  {
	    selectedWrapperCorner = BOTTOM;
	  }
	else
	  selectedWrapperCorner = NOT_SELECTED;
      }
    else
      selectedWrapperCorner = NOT_SELECTED;
  }

  int getSelectedWrapperCorner()
  {
    return selectedWrapperCorner;
  }

  synchronized void addPort(Port port)
  {
    if (ports.indexOf(port) == -1)
      ports.addElement(port);
  }

  synchronized void removePorts()
  {
    int i, size = ports.size();
    Vector copyOfPorts = (Vector) ports.clone();

    for (i=0; i<size; i++)
      removePort((Port)copyOfPorts.elementAt(i));
  }

  synchronized void removePort(Port port)
  {
    ports.removeElement(port);
  }

  String getShortName ()
  {
    String name = bean.getClass().getName();
    int    Index = 0;
    int    length = name.length();
   
    for (int i=0; i<length; i++)
      {
	if (name.charAt(i) == '.')
	  Index = i;
      }
     
    return name.substring (++Index);
  }

  @Override
  public synchronized void update (Graphics g)
  {
    paint(g);
  }

  @Override
  public synchronized void paint (Graphics g)
  {
    FontMetrics wMet = g.getFontMetrics();
    String displayName = getShortName();

    Rectangle b_rect = bounds[0];
    //g.setColor(Color.lightGray);
    //g.fillRect (0, 0, b_rect.width, b_rect.height);
    if (!(bean instanceof Component)) {
      g.setColor(color);
      g.fillRect(border, border,
		 b_rect.width - border * 2 - 1, b_rect.height - border * 2 - 1);
	g.setColor(Color.black);
	g.drawRect(border, border, b_rect.width - border * 2 - 1,
		   b_rect.height - border * 2 - 1);
	g.setColor(Color.black);

	if (bean != null) {
	  if (img == null)
	    getImage();
	  if (img == null)
	    g.drawString(displayName, b_rect.width / 2 - wMet.stringWidth(displayName)/2,
			 (b_rect.height / 2) + wMet.getAscent()/2 );
	  else{
	    Dimension size = getSize();
	    if (size32x32)
	      g.drawImage(img, (size.width-32)/2, (size.height-32)/2, null);
	    else
	      g.drawImage(img, (size.width-16)/2, (size.height-16)/2, null);
	  }
	}
    }

    if (selected)
      {
	Color lineColor = Preferences.currentPreferences.getSizingWidgetLineColor();
	if (lineColor == null) g.setColor(Color.black);
	else g.setColor(lineColor);
	g.drawRect(0, 0, sz, sz);
	g.drawRect(b_rect.width/2 - sz/2, 0, sz, sz);
	g.drawRect(b_rect.width - sz - 1, 0, sz, sz);
	g.drawRect(b_rect.width - sz - 1, b_rect.height/2 - sz/2, sz, sz);
	g.drawRect(0, b_rect.height - sz - 1, sz, sz);
	g.drawRect(0, b_rect.height/2 - sz/2, sz, sz);
	g.drawRect(b_rect.width - sz - 1, b_rect.height - sz - 1, sz, sz);
	g.drawRect(b_rect.width/2 - sz/2, b_rect.height - sz - 1, sz, sz);

	Color handleColor = Preferences.currentPreferences.getSizingWidgetHandleColor();
	if (handleColor == null) g.setColor(Color.white);
	else g.setColor(handleColor);
	g.fillRect(0+1, 0+1, sz-1, sz-1);
	g.fillRect(b_rect.width/2 - sz/2+1, 0+1, sz-1, sz-1);
	g.fillRect(b_rect.width - sz, 0+1, sz-1, sz-1);
	g.fillRect(b_rect.width - sz, b_rect.height/2 - sz/2+1, sz-1, sz-1);
	g.fillRect(0+1, b_rect.height - sz, sz-1, sz-1);
	g.fillRect(0+1, b_rect.height/2 - sz/2+1, sz-1, sz-1);
	g.fillRect(b_rect.width - sz, b_rect.height - sz, sz-1, sz-1);
	g.fillRect(b_rect.width/2 - sz/2+1, b_rect.height - sz, sz-1, sz-1);
      }
  }

  private void getImage(){
    if (!(bean instanceof Component)){
      try{
	java.beans.BeanInfo beanInfo = java.beans.Introspector.getBeanInfo(bean.getClass());
	img = beanInfo.getIcon(java.beans.BeanInfo.ICON_COLOR_32x32);
	if (img == null)
	  img = beanInfo.getIcon(java.beans.BeanInfo.ICON_COLOR_16x16);
	else
	  size32x32 = true;
      }
      catch(java.beans.IntrospectionException ex){
	img = null;
      } 
    }
  }

  @Override
  public void changeColor(Object logicalColor, Color color)
  {
    this.color = color;
    canvas.invalidateElement(this);
  }

  @Override
  public void changeColor(Object logicalColor, Object colorKey)
  {
    Color color =  canvas.getColorTable().lookup(colorKey);
    if (color != null)
      changeColor(logicalColor, color);
  }

  /* coordinates are local to component */
  @Override
  public boolean contains(int x, int y)
  {
    Rectangle theBounds = bounds[0];
    int translatedX = x + theBounds.x,
      translatedY = y + theBounds.y;
    if (bean == null || !(bean instanceof Component)) {
      return theBounds.contains(translatedX, translatedY);
    } else {
      Rectangle beanBounds = ((Component)bean).getBounds();
      int
	offsetX = theBounds.x - beanBounds.x,
	offsetY = theBounds.y - beanBounds.y;
      if (beanBounds.contains(translatedX ,translatedY)) {
	// if the point is within the bounds of the bean,
	// see if the bean itself thinks that contains()
	// is true
	return ((Component)bean).contains(x - offsetX, y - offsetY);
      } else {
	// then the "contains" status of the point is up to the
	// wrapper. This is the region between the bean and the
	// selection handles
	return theBounds.contains(translatedX, translatedY);
      }
    }
  }

  @Override
  public void shift (int shiftX, int shiftY)
  {
    Rectangle rect = bounds[0];
    int oldX = rect.x;
    int oldY = rect.y;
    rect.translate(shiftX,shiftY);
    setLocation(rect.x, rect.y);
    Point location = getLocation();
    int actualShiftX = location.x - oldX;
    int actualShiftY = location.y - oldY;
    int i, size = ports.size();
    for (i = 0 ; i<size ; i++)
      {
	Port port = (Port) ports.elementAt(i);
	canvas.shiftElement(port,actualShiftX,actualShiftY);
      }
    size = knowledgeLinks.size();
    for (i = 0 ; i<size ; i++)
      {
	KnowledgeLink link = (KnowledgeLink)knowledgeLinks.elementAt(i);
	if (link.object instanceof KnowledgeLinkLooseEnd)
	  canvas.shiftElement((KnowledgeLinkLooseEnd)link.object, actualShiftX, actualShiftY);
	link.updateVertices();
      }
    if (bean != null && bean instanceof Component)
      canvas.shiftElement(((Component)bean), actualShiftX, actualShiftY);    
  }
    
  @Override
  public Rectangle[] getExactBounds ()
  {
    Rectangle boundsRect = new Rectangle( bounds[0]);
    return new Rectangle[] { boundsRect };
  }

  Class getBeanClass()
  {
    return (Class)(bean.getClass());
  }

  Object getBean()
  {
    return bean;
  }

  void setBean(Object bean)
  {
    this.bean = bean;
  }

  void setDebuggingEnabled(boolean b)
  {
    int i, size = ports.size();
    for (i=0; i<size ; i++)
      ((Port)ports.elementAt(i)).setDebuggingEnabled(b);
  }

  void setComponentBeanAdapter(ComponentBeanAdapter adapter)
  {
    componentBeanAdapter = adapter;
  }

  ComponentBeanAdapter getComponentBeanAdapter()
  {
    return componentBeanAdapter;
  }

  void reestablishPortPositions()
  {
    int i, size = ports.size();
    for (i=0; i<size ; i++)
      {
	Port port = (Port)ports.elementAt(i);
	Rectangle bounds = port.getBounds();
	setPortPosition(port,bounds.x, bounds.y);
			// bounds.x + (bounds.width / 2),
			// bounds.y + (bounds.height / 2));
      }
  }

  void setPortPosition(Port port, int x, int y)
  {
    Dimension size = port.getSize();
    int width = size.width;
    int height = size.height;

    Rectangle theBounds = bounds[0];
    int wrapperLeft = theBounds.x;
    int wrapperHCenter = theBounds.x + (theBounds.width / 2);
    int wrapperRight = theBounds.x + theBounds.width;
    int wrapperTop = theBounds.y;
    int wrapperVCenter = theBounds.y + (theBounds.height / 2);
    int wrapperBottom = theBounds.y + theBounds.height;

    int portLeft = x;
    int portHCenter = x + (width / 2);
    int portRight = x + width;
    int portTop = y;
    int portVCenter = y + (height / 2);
    int portBottom = y + height;
    
    int targetX = portLeft, targetY = portTop, directionX;
    int direction = findClosestSide(wrapperLeft, wrapperTop,
				    wrapperRight, wrapperBottom,
				    portHCenter, portVCenter);
    if (direction == Directions.LEFT) // (portRight < wrapperLeft)
      {
	direction = Directions.LEFT;
	targetX = wrapperLeft - (width + margin);
	if (portTop < wrapperTop)
	  targetY = wrapperTop;
	else if (portBottom > wrapperBottom)
	  targetY = wrapperBottom - height;
      }
    else if (direction == Directions.RIGHT) // (portLeft >= wrapperRight) 
      {
	direction = Directions.RIGHT;
	targetX = wrapperRight + margin;
	if (portTop < wrapperTop)
	  targetY = wrapperTop;
	else if (portBottom > wrapperBottom)
	  targetY = wrapperBottom - height;

      }
    else if (direction == Directions.TOP) // (portVCenter < wrapperVCenter) 
      {
	direction = Directions.TOP;
	targetY = wrapperTop - (height + margin);
	if (portLeft < wrapperLeft)
	  targetX = wrapperLeft;
	else if (portRight > wrapperRight)
	  targetX = wrapperRight - width;
      }
    else                                   // BOTTOM
      {
	direction = Directions.BOTTOM;
	targetY = wrapperBottom + margin;
	if (portLeft < wrapperLeft)
	  targetX = wrapperLeft;
	else if (portRight > wrapperRight)
	  targetX = wrapperRight - width;
      }
  

    int shiftX = targetX - portLeft;
    int shiftY = targetY - portTop;
    port.setSide(direction);
    canvas.shiftElement(port,shiftX, shiftY);
  }

  protected int findClosestSide(int left, int top, int right, int bottom,
				int px, int py)
  {
    if (pointAboveLine(px,py,left,top,right,bottom))
      {
	if (pointAboveLine(px,py,left,bottom,right,top))
	  return Directions.BOTTOM;
	else
	  return Directions.LEFT;
      }
    else if (pointAboveLine(px,py,left,bottom,right,top))
      return Directions.RIGHT;
    else
      return Directions.TOP;   
  }

  private boolean pointAboveLine(int px, int py, int x1, int y1,
				 int x2, int y2)
  {
    double m = ((double)(y2 - y1)) / ((double) (x2 - x1));
    double b = (double)y1 - (m * (double)x1);
    
    if (((m * (double)px) + b) <= (double)py)
      return true;
    else
      return false;
  }

  // Knowledge Link Stuff

  String getKnownBeanNameProblemIfAny(String name)
  {
    if (name.equals("source") ||
	name.equals("target") ||
	name.equals("event"))
      return "source, target, and event are reserved names.";
    int i, size = knowledgeLinks.size(), total = 0;

    for (i=0; i<size ; i++)
      {
	KnowledgeLink link = (KnowledgeLink)knowledgeLinks.elementAt(i);
	if (link.name != null && link.name.equals(name))
	  return "The name \""+name+"\" is already in use.";
      }
    char[] chars = name.toCharArray();
    size = chars.length;
    for (i=0; i<size; i++)
      if (!(i==0 ? 
	    Character.isLetter(chars[i]) :
	    Character.isLetterOrDigit(chars[i])))
	return "Bad identifier syntax.";
    return null;
  }

  int knownBeanCount()
  {
    int i, size = knowledgeLinks.size(), total = 0;

    for (i=0; i<size ; i++)
      {
	KnowledgeLink link = (KnowledgeLink)knowledgeLinks.elementAt(i);
	if (link.subject == this && link.object instanceof Wrapper)
	  total++;
      }
    return total;
  }

  Object[] knownBeans()
  {
    int i, size = knowledgeLinks.size();
    Object[] result = new Object[knownBeanCount()];
    for (i=0; i<size ; i++)
      {
	KnowledgeLink link = (KnowledgeLink)knowledgeLinks.elementAt(i);
	if (link.subject == this)
	  if (link.object instanceof Wrapper)
	  result[i] = ((Wrapper)link.object).getBean();
      }
    return result;
  }

  Class[] knownBeanClasses()
  {
    int i, size = knowledgeLinks.size();
    Class[] result = new Class[knownBeanCount()];
    for (i=0; i<size ; i++)
      {
	KnowledgeLink link = (KnowledgeLink)knowledgeLinks.elementAt(i);
	if (link.subject == this)
	  if (link.object instanceof Wrapper)
	    result[i] = ((Wrapper)link.object).getBean().getClass();
      }
    return result;
  }

  String[] knownBeanNames()
  {
    int i, size = knowledgeLinks.size();
    String[] result = new String[knownBeanCount()];
    for (i=0; i<size ; i++)
      {
	KnowledgeLink link = (KnowledgeLink)knowledgeLinks.elementAt(i);
	if (link.subject == this)
	  if (link.object instanceof Wrapper)
	    result[i] = link.name;
      }
    return result;
  }

  boolean knows(Wrapper wrapper)
  {
    int i, size = knowledgeLinks.size();
    for (i=0; i<size ; i++)
      {
	KnowledgeLink link = (KnowledgeLink)knowledgeLinks.elementAt(i);
	if (link.subject == this && link.object == wrapper)
	  return true;
      }
    return false;
  }

  boolean anyKnownBeansInUse()
  {
    int i,size = ports.size();
    for (i=0; i<size ; i++)
      {
	Port port = (Port)ports.elementAt(i);
	if (port.getConnection().output instanceof Port) // i.e. not a loose end
	  {
	    return true;
	  }
      }
    return false;
  }

  Point centerPoint()
  {
    Point location = getLocation();
    Dimension size = getSize();
    return new Point(location.x + (size.width / 2),
		     location.y + (size.height / 2));
  }

  private void readObject (java.io.ObjectInputStream stream) throws java.io.IOException, ClassNotFoundException {
    stream.defaultReadObject();
    if (knowledgeLinks == null)
      knowledgeLinks = new Vector ();
  }
}
