package com.gensym.draw;

import java.awt.*;
import java.util.Vector;
import java.lang.Math;
import com.gensym.ntw.util.WindowUtil;
import com.gensym.util.Sequence;
import com.gensym.message.Resource;
import com.gensym.message.Message;
import com.gensym.message.Trace;
import com.gensym.message.MessageKey;

/**
* <P>
* The PersistentCanvas implements a scrollable, 2D drawing field supporting
* persistent, rather than immediate graphics.  DrawElements are added and
* remove from a PersistentCanvas.  The user does not handle paint method or
* invalidation directly.  Automatic mapping of mouse events to DrawElements
* is supported.  
* </P>
*
* <P>
* All event handling is delegated to the current eventHandler of the persistent
* canvas.  This allows easy implementation of palette-based drawing programs 
* like MacDraw or Paintbrush.  This also encourages a Model-View-Controller
* programming style because the view (the DrawElements) does not implement the
* controller (the eventHandler).
* </P>  
* 
* <P>
* The Persistent Canvas has two sets of bounds, logical and view.  The logical
* bounds delimit the size of the drawing area being used.  The view bounds 
* delimit what is currently visible to the user.  The logical bounds always
* encompass the view bounds.  If the size (AWT component bounds) of the 
* PersistentCanvas is greater than its logical bounds, area outside the logical
* bounds is said to be "OutOfBounds", from the PersistentCanvas's point of
* view
* </P>
*
* @author Joe Devlin
* @see com.gensym.draw.DrawElement
* @see com.gensym.draw.EventHandler
*/
public class PersistentCanvas extends Container implements Scrollable

{

  static final long serialVersionUID = -303563266454775782L;
  private static final MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.draw", PersistentCanvas.class);
  private static final Resource i18nTrace =
  Trace.getBundle("com.gensym.draw.TraceMessages");

  private boolean use_double_buffer = false;
  private transient Image doublebuffer;
  private transient Graphics dbg;
  private ColorTable colorTable = ColorTable.createDefaultColorTable();
  public Color current_color = new Color (128, 128, 128);
  private Color background_color = Color.white;
  private Color out_of_bounds_color = new Color(200, 200, 200);
  private transient Container nativeContainer = null;
  private transient Cursor outerCursor = null;

  private EventHandler eventHandler;

  // private Vector elements = new Vector();

  private int element_count = 0;
  private boolean debug = false;

  protected ViewScrollState vertical_state;
  protected ViewScrollState horizontal_state; 

  public void setDoubleBuffered (boolean dbState)
  {
    if (debug) {
      System.out.println("Setting db to " + dbState);
    }

    if (use_double_buffer == dbState)
      return;

    use_double_buffer = dbState;
  }

  @Override
  public boolean isDoubleBuffered () {
    return use_double_buffer;
  }
  
  public void setBackgroundColor(Color color)
  {
    background_color = color;
  }

  public Color getBackgroundColor()
  {
    return background_color;
  }

  public void setOutOfBoundsColor(Color color)
  {
    out_of_bounds_color = color;
  }

  public Color getOutOfBoundsColor()
  {
    return out_of_bounds_color;
  }

  public ColorTable getColorTable()
  {
    return colorTable;
  }

  public void setColorTable(ColorTable colorTable)
  {
    this.colorTable = colorTable;
    repaintCanvas();
  }

  @Override
  public void addNotify()
  {
    super.addNotify();
    Container parent = this;

    while (! ((parent instanceof Panel) ||
	      (parent instanceof ScrollPane) ||
	      (parent instanceof Window)))
      parent = parent.getParent();

    if (debug) {
      System.out.println("nativeContainer="+parent);
    }
   nativeContainer = parent;
  }


  public void pushCursor(Cursor cursor)
  {
    outerCursor = nativeContainer.getCursor();
    nativeContainer.setCursor(cursor);
  }

  public void popCursor()
  {
    nativeContainer.setCursor(outerCursor);
    outerCursor = null;
  }

  @Override
  public void addScrollbar(ViewScrollbar scrollbar, boolean isHorizontal)
  {
    if (isHorizontal)
      horizontal_state.addObserver(scrollbar);
    else
      vertical_state.addObserver(scrollbar);
  }

  @Override
  public void removeScrollbar(ViewScrollbar scrollbar, boolean isHorizontal) {
    if (isHorizontal)
    {
      horizontal_state.deleteObserver(scrollbar);
      horizontal_state=null ;
    }
    else
    {
      vertical_state.deleteObserver(scrollbar);
      vertical_state=null ;
    }
  }
    
  @Override
  public void addScrollObserver (java.util.Observer o, boolean isHorizontal) {
    if (isHorizontal)
      horizontal_state.addObserver (o);
    else
      vertical_state.addObserver (o);
  }

  public void removeScrollObserver (java.util.Observer o, boolean isHorizontal) {
    if (isHorizontal)
      horizontal_state.deleteObserver (o);
    else
      vertical_state.deleteObserver (o);
  }

  @Override
  public ViewScrollState getScrollState(boolean isHorizontal)
  {
    if (isHorizontal)
      return horizontal_state;
    else
      return vertical_state;
  }

  
  @Override
  public void setScroll()
  {
    Rectangle bounds = getBounds();
    vertical_state.setScrollState(0,bounds.height,0,bounds.height);
    horizontal_state.setScrollState(0,bounds.width,0,bounds.width);
  }

  @Override
  public void setScroll(int logicalLeft, int logicalTop,
                        int logicalRight, int logicalBottom)
  {
    Rectangle bounds = getBounds();
    vertical_state.setScrollState(logicalTop,logicalBottom,
                                  logicalTop,
				  Math.min(logicalBottom,logicalTop+bounds.height));
    horizontal_state.setScrollState(logicalLeft,logicalRight,
                                    logicalLeft,
				    Math.min(logicalRight,logicalLeft+bounds.width));
    if (debug) {
      System.out.println("vert args = ("+logicalTop+", "+logicalBottom+", "+
			 logicalTop+", "+
			 Math.min(logicalBottom,logicalTop+bounds.height)+")");
      System.out.println("horiz args = ("+logicalLeft+", "+logicalRight+", "+
			 logicalLeft+", "+
			 Math.min(logicalRight,logicalLeft+bounds.width)+")");
    }
   ViewScrollState state = horizontal_state;
   if (debug) {
     System.out.println("setScroll SCROLL UPDATE vmin="+state.view_min+
			" vmax="+state.view_max+
			" lmin="+state.logical_min+
			" lmax="+state.logical_max);
   }
  }

  @Override
  public void setScroll(int logicalLeft, int logicalTop,
                        int logicalRight, int logicalBottom,
                        int viewLeft, int viewTop,
                        int viewRight, int viewBottom)
  {
    Rectangle bounds = getBounds();
    vertical_state.setScrollState(logicalTop, logicalBottom,
                                   viewTop,viewBottom);
    horizontal_state.setScrollState(logicalLeft,logicalRight,
                                     viewLeft,viewRight);
  }

  public Rectangle getViewBounds () {
    return new Rectangle (horizontal_state.view_min,
			  vertical_state.view_min,
			  horizontal_state.view_max - horizontal_state.view_min,
			  vertical_state.view_max - vertical_state.view_min);
  }

  public Rectangle getLogicalBounds()
  {
    int left = horizontal_state.logical_min;
    int top = vertical_state.logical_min;

    return new Rectangle(left,top,
                         horizontal_state.logical_max-left,
                         vertical_state.logical_max-top);
  }

  public Point getScrollOffset()
  {
    return new Point (-horizontal_state.view_min, -vertical_state.view_min);
  }

  @Override
  public void growLogical(int size, boolean isHorizontal, 
                          boolean setMinimum)
  {
    ViewScrollState state = null;
    Rectangle bounds = getBounds();
    int newViewMax, boundsMax;

    if (isHorizontal)
      { 
	state = horizontal_state;
        boundsMax = state.view_min + bounds.width;
      }
    else
      {
	state = vertical_state;
        boundsMax = state.view_min + bounds.height;
      }
    int logicalMax = state.logical_max;
    if (!setMinimum)
      logicalMax += size;
    newViewMax = Math.min(logicalMax,boundsMax);
    state.grow(size,setMinimum,newViewMax);
    repaintCanvas();
  }

  @Override
  public void scrollView(int distance, boolean is_horizontal)
  {
    ViewScrollState state 
        = is_horizontal ? horizontal_state : vertical_state;

    state.shift(distance);
    repaintCanvas();
  }

  @Override
  public void scrollViewAbsolute(int new_view_min, boolean is_horizontal)
  {
    ViewScrollState state 
        = is_horizontal ? horizontal_state : vertical_state;

    state.shift(new_view_min - state.view_min);
    repaintCanvas();
  }

  /** This method is a backdoor way to change the bounds and the scroll state simultaneaously without
   * the bounds change messing with the scroll state. There is also only one repaint with this call. The first four
   *  arguments are the bounds. The remaining arguments are for the full-featured setScroll. */
  public void setBounds(int x, int y, int width, int height,
			int logicalLeft, int logicalTop,
                        int logicalRight, int logicalBottom,
                        int viewLeft, int viewTop,
                        int viewRight, int viewBottom) {
    super.setBounds(x, y, width, height);
    setScroll(logicalLeft, logicalTop,
	      logicalRight, logicalBottom,
	      viewLeft, viewTop,
	      viewRight, viewBottom);
  }


  @Override
  public void setBounds(int x, int y, int width, int height)
  {
    Rectangle bounds = getBounds();
    
    super.setBounds(x,y,width,height);

    if (debug)
      {

	System.out.println("resize canvas old="+bounds+
			   " neww="+width+" newh="+height);
	System.out.println("HSCROLL "+horizontal_state);
      }
    
    adjustBoundsForSizing(horizontal_state,bounds.width,width);
    adjustBoundsForSizing(vertical_state,bounds.height,height);
 
    repaintCanvas();
  }

  protected void adjustBoundsForSizing(ViewScrollState scrollState,
				     int oldWidth, int newWidth) // AWT Component Width
  {
    int logicalWidth = scrollState.logical_max - scrollState.logical_min;
    int diff = newWidth - oldWidth;

    if (newWidth >= logicalWidth)  // show everything
      scrollState.setView(scrollState.logical_min,
			  scrollState.logical_max);
    else if (diff > 0) // growing partial
      {
	if (scrollState.view_max + diff > scrollState.logical_max) // max the right, grow the left 
	  scrollState.setView(scrollState.logical_max - newWidth,
			      scrollState.logical_max);
	else                                     // just grow the right
	  scrollState.setView(scrollState.view_min,
			      scrollState.view_max + diff);
      }
    else                        
      {
        if (oldWidth > logicalWidth) // we were maxed
	  scrollState.setView(scrollState.view_min,
			      scrollState.view_min + newWidth);
	else                     // shrinking partial
	  scrollState.setView(scrollState.view_min,
			      scrollState.view_max + diff);
      }
  }


  @Override
  public Dimension getPreferredSize ()
  {
    Rectangle r = getLogicalBounds();
    if (r == null)
      return super.getPreferredSize();
    else
      return new Dimension(r.width, r.height);
  }


  @Override
  public Dimension getMinimumSize ()
  {
    return new Dimension(100, 100);
  }

  @Override
  public synchronized void paint (Graphics finalg)
  {
    Trace.send(10, traceKey, i18nTrace, "pcpaint", this, finalg);
    Graphics g;
    boolean drawOffScreen = use_double_buffer;
    if (finalg instanceof PrintGraphics)
      drawOffScreen = false;
    if (drawOffScreen) {
      if (doublebuffer == null) {
	Dimension size = getSize();
	doublebuffer = WindowUtil.createImage (size.width, size.height);
	dbg = (Graphics) doublebuffer.getGraphics();
// 	Graphics2D g2 = (Graphics2D) dbg;
// 	g2.setRenderingHint (RenderingHints.KEY_ANTIALIASING,
// 			     RenderingHints.VALUE_ANTIALIAS_OFF);
// 	g2.setRenderingHint (RenderingHints.KEY_RENDERING,
// 			     RenderingHints.VALUE_RENDER_SPEED);
// 	g2.setRenderingHint (RenderingHints.KEY_DITHERING,
// 			     RenderingHints.VALUE_DITHER_DISABLE);
// 	g2.setRenderingHint (RenderingHints.KEY_TEXT_ANTIALIASING,
// 			     RenderingHints.VALUE_TEXT_ANTIALIAS_OFF);
// 	g2.setRenderingHint (RenderingHints.KEY_COLOR_RENDERING,
// 			     RenderingHints.VALUE_COLOR_RENDER_SPEED);
      }
      g = dbg;
      // new graphics should only paint the region the incoming
      // graphics was going to paint
      g.setClip(finalg.getClip());
    } else
      g = finalg;
    int i;
    int shift_x = /*horizontal_state.logical_min */ 0 -
                  horizontal_state.view_min;
    int shift_y = /* vertical_state.logical_min */ 0 -
                  vertical_state.view_min;

    paintBackground(g);
    // Draw the Elements
    try {
      g.translate(shift_x, shift_y);
      super.paint(g);
    } finally {
      g.translate(- shift_x, - shift_y);
    }

    // Draw tool State (this is deprecated)
    if (eventHandler != null)
        eventHandler.Draw(g);

    // Finish double-buffer drawing
    if (drawOffScreen) {
      finalg.drawImage(doublebuffer, 0, 0, null);
    }
  } 

  protected void paintBackground(Graphics g)
  {
    paintOutOfBounds(g);
    paintLogicalCanvasBackground(g);
  }

  protected void paintLogicalCanvasBackground(Graphics g){
    int view_height = vertical_state.view_max - vertical_state.view_min;
    int view_width = horizontal_state.view_max - horizontal_state.view_min;
    g.setColor(background_color);
    g.fillRect(0,0,view_width, view_height);
  }

  protected void paintOutOfBounds(Graphics g){
    g.setColor(out_of_bounds_color);
    Rectangle bounds = getBounds();
    g.fillRect(0,0,bounds.width,bounds.height);
  }

  private volatile Thread gcaThread;

  @Override
  public boolean contains (int x, int y) {
    if (Thread.currentThread () == gcaThread) {
      Rectangle canvasBounds = getLogicalBounds();
      return canvasBounds.contains (x, y);
    } else
      return super.contains (x, y);
  }

  @Override
  public Component getComponentAt(int x, int y) {
    gcaThread = Thread.currentThread ();
    Component targetComponent = super.getComponentAt (x, y);
    gcaThread = null;
    return targetComponent;
  }

  public Component old_getComponentAt(int x, int y)
  {    
    Rectangle canvasBounds = getLogicalBounds();
    if (!canvasBounds.contains(x, y)) {
      return null;
    }
    int ncomponents = getComponentCount();
    Component[] elements = getComponents();
    for (int i = 0 ; i < ncomponents ; i++) {
      Component comp = elements[i];
      if (comp != null) 
	{
          Point location = comp.getLocation();
	  if (comp.contains(x - location.x, y - location.y)) 
	    {
	      gcaThread = Thread.currentThread ();
	      System.out.println ("Container -> " + locate (x, y) + ", Canvas -> " + comp);
	      if (comp != locate (x, y))
		throw new Error ("Wrong Component!0");
	      gcaThread = null;
	      return comp;
	    }
	}
    }
    gcaThread = Thread.currentThread ();
    System.out.println ("Container -> " + locate (x, y) + ", Canvas -> " + this);
    if (locate (x, y) != this)
      throw new Error ("Wrong Component!1");
    gcaThread = null;
    return this;
  }

  public Component getComponentAt(int x, int y, Sequence exemptComponents)
  {    
    Rectangle canvasBounds = getLogicalBounds();
    if (!canvasBounds.contains(x, y)) {
      return null;
    }
    int ncomponents = getComponentCount();
    Component[] elements = getComponents();
    for (int i = 0 ; i < ncomponents ; i++) {
      Component comp = elements[i];
      if (comp != null && !exemptComponents.contains(comp))
	{
          Point location = comp.getLocation();
	  if (comp.contains(x - location.x, y - location.y)) 
	    {
	      return comp;
	    }
	}
    }
    return this;
  }

  public Component findElement (int mouse_x, int mouse_y, boolean allowCanvas)
  {
    Component element = getComponentAt(mouse_x + horizontal_state.view_min ,
				       mouse_y +  vertical_state.view_min);
    if (element == this && !allowCanvas)
      return null;
    else
      return element;
  }
  
  public Component findElement (int mouse_x, int mouse_y)
  {
    return findElement(mouse_x, mouse_y, false);
  }

  public Component findElement (int mouse_x, int mouse_y, Sequence exemptComponents)
  {
    Component element = getComponentAt(mouse_x + horizontal_state.view_min ,
				       mouse_y +  vertical_state.view_min,
				       exemptComponents);
    if (element == this)
      return null;
    else
      return element;
  }
  
  public Component[] findElements (Rectangle windowRect) 
  {
    Component[] elements = getComponents();
    int i, len = elements.length;
    int left = windowRect.x, top = windowRect.y,
        width = windowRect.width, height = windowRect.height;
    Vector containedElements = new Vector ();
     
    for (i = len-1 ; i >= 0  ; i--)
      {
	Component element = elements[i];
	if (element instanceof DrawElement)
	  {
	    DrawElement drawElement = (DrawElement)element;
	    // the following line is wrong.
	    Rectangle eltBounds = drawElement.getExactBounds()[0];
	    if (containedIn (eltBounds, windowRect))
	      containedElements.addElement(element);
	  }
	else
	  if (element.getBounds().intersects(windowRect))
	    containedElements.addElement(element);
      }
    int numElements = containedElements.size ();
    Component[] insideElements = new Component[numElements];
    containedElements.copyInto (insideElements);
    return insideElements;
  }

  public void dumpElements()
  {
    Component[] elements =  getComponents();
    int i, len = elements.length;
  
    for (i = len-1 ; i >= 0  ; i--)
      {
	Component element = elements[i];
        System.out.println("element="+element);
        System.out.println("  loc="+element.getLocation());
	System.out.println("  size="+element.getSize());
      }
  }

  

  public static boolean containedIn (Rectangle inner, Rectangle outer) {
    return ((inner.x >= outer.x)
	    && (inner.x + inner.width <= outer.x + outer.width)
	    && (inner.y >= outer.y)
	    && (inner.y + inner.height <= outer.y + outer.height));
  }


  public void addElement(Component element)
  {
    addElement(element, 0);
  }

  public void addElement(Component element,
			 int position) {
    add(element,position);
    if (element instanceof DrawElement)
      ((DrawElement)element).setCanvas(this);
    // The following call prevents the adding of a PersistenCanvas anywhere
    // in the child hierarchy of a PersistentCanvas before the parent
    // canvas has a native window in its parent hierarchy. Test TrendCharts
    // if it is ever uncommented.
    //element.addNotify ();
    invalidateElement(element);
  }
  
  public int getElementPosition(Component element)
  {
    Component[] elements = getComponents();
    int i, len = elements.length;

    for (i = 0; i<len ; i++)
      if (element == elements[i])
        return i;
    return -1;
  }

  public void moveElementUp(Component element)
  {
    int count = getComponentCount();

    if (count > 1)
    {
      int index = getElementPosition(element);
      Component other_element = getComponent(index - 1);

      remove(index - 1);
      remove(index - 1);
      add(other_element,index - 1);
      add(element, index - 1);
      // elements.setElementAt(other_element,index);
      // elements.setElementAt(element,index - 1);
    }
    invalidateElement(element);
  }

  public void moveElementDown (Component element)
  {
    int count = getComponentCount();

    if (count > 1)
    {
      int index = getElementPosition(element);
      Component other_element = getComponent(index + 1);

      remove(index);
      remove(index);
      add(element,index);
      add(other_element,index);
      // elements.setElementAt(other_element,index);
      // elements.setElementAt(element,index + 1);
    }
    invalidateElement(element);
  }

  public void moveElementToTop(Component element)
  {
    int count = getComponentCount();

    if (count > 1)
    {
      int index = getElementPosition(element);
      remove(index);
      add(element,0);
    }
    invalidateElement(element);
  }

  public void moveElementToBottom(Component element)
  {
    int count = getComponentCount();

    if (count > 1)
    {
      int index = getElementPosition(element);
      remove(index);
      add(element,-1);
    }
    invalidateElement(element);
  }

  public void removeElement(Component element)
  {
    Rectangle bounds[] = null;
    if (element instanceof DrawElement)
      bounds = ((DrawElement)element).getExactBounds();
    else
      {
	bounds = new Rectangle[1];
	bounds[0] = element.getBounds();
      }
    remove(element);
    invalidate(bounds);
  }

  private boolean invalidating;
  private volatile transient Thread invalidatingThread;

  public void invalidate(Rectangle[] invalidationBounds) {
    if (debug)
      System.out.println ("invalidate (" + com.gensym.core.DebugUtil.printArray (invalidationBounds) + ")");
    int shift_x = /*horizontal_state.logical_min */ 0 -
      horizontal_state.view_min;
    int shift_y = /* vertical_state.logical_min */ 0 -
      vertical_state.view_min;
    int length = invalidationBounds.length;
    invalidating = true;
    invalidatingThread = Thread.currentThread ();
    for (int i = 0; i<length ; i++)
      {
	Rectangle rect = invalidationBounds[i];
	repaint(rect.x+shift_x,
		rect.y+shift_y,
		rect.width,
		rect.height);
	if (debug)
	  System.out.println (" --> repaint (" + rect + ") >> (" + shift_x + ", " + shift_y + ")");
      }
    if (invalidatingThread == Thread.currentThread ())
      invalidating = false;
  }

  private boolean backtrace = false;

  @Override
  public void repaint (long tm, int x, int y, int width, int height) {
    if (debug)
      System.out.println ("    ==> (" + x + ", " + y + ") " + width + "x" + height + ")");
    if (debug && backtrace)
      System.out.println (com.gensym.core.DebugUtil.getStackTrace ());
    if (invalidating)
      super.repaint (tm, x,  y, width, height);
  }

  protected void repaintCanvas () {
    invalidating = true;
    invalidatingThread = Thread.currentThread ();
    repaint ();
    if (invalidatingThread == Thread.currentThread ())
      invalidating = false;
  }

  protected void repaintCanvas (int x, int y, int width, int height) {
    invalidating = true;
    invalidatingThread = Thread.currentThread ();
    repaint (x, y, width, height);
    if (invalidatingThread == Thread.currentThread ())
      invalidating = false;
  }


  protected void repaintCanvas (long tm, int x, int y, int width, int height) {
    invalidating = true;
    invalidatingThread = Thread.currentThread ();
    repaint (tm, x, y, width, height);
    if (invalidatingThread == Thread.currentThread ())
      invalidating = false;
  }

  public Rectangle[] elementExactBounds(Component element)
  {
    Rectangle bounds[] = null;
    if (element instanceof DrawElement)
      bounds = ((DrawElement)element).getExactBounds();
    else
      {
	bounds = new Rectangle[1];
	bounds[0] = element.getBounds();
      }
    return bounds;
  }

  public void invalidateElement(Component element)
  {
    //System.out.println ("invalidateElement (" + element + ")");
    Rectangle bounds[] = null;
    if (element instanceof DrawElement)
      bounds = ((DrawElement)element).getExactBounds();
    else
      {
	bounds = new Rectangle[1];
	bounds[0] = element.getBounds();
      }
    invalidate(bounds);
  }

  public void shiftElement(Component element,
			   int deltaX,
			   int deltaY) 
  {
    Rectangle[] oldBounds = null;
    Point location = element.getLocation();

    if (element instanceof DrawElement)
      {
        DrawElement drawElement = (DrawElement)element;
	Rectangle[] currentBounds = drawElement.getExactBounds();
	int length = currentBounds.length;
	oldBounds = new Rectangle[length];
	for (int i = 0; i < length; i++) 
	  oldBounds[i] = new Rectangle(currentBounds[i]);
	drawElement.shift(deltaX, deltaY);
      }
    else {
      oldBounds = new Rectangle[1];
      oldBounds[0] = new Rectangle(element.getBounds());
      element.setLocation(location.x+deltaX,location.y+deltaY);
    }
    invalidate(oldBounds);
    invalidateElement(element);
  }


  @Override
  public void validate() {
    if (debug) {
      System.out.println("in pc validate");
    }
    super.validate();
  }
  
  public PersistentCanvas ()
  {
    enableEvents(AWTEvent.MOUSE_EVENT_MASK);
    horizontal_state = createScrollState(true);
    vertical_state  = createScrollState(false);
  }

  protected ViewScrollState createScrollState(boolean isHorizontal){
    return new ViewScrollState(isHorizontal);
  }

  @Override
  public void update(Graphics g)
  {
    paint(g);
  }

  public void setEventHandler(EventHandler eh)
  {
    if (eventHandler != null)
        eventHandler.deregisterListeners (this);
    eventHandler = eh;
    if (debug) {
      System.out.println("new event handler");
    }
    if (eventHandler != null)
      eventHandler.registerListeners (this);
  }

  public EventHandler getEventHandler()
  {
    return eventHandler;
  }


  /**
   * null out the offscreen buffer as part of invalidation
   */
  @Override
  public void invalidate() {
      super.invalidate();
      doublebuffer = null;
      dbg = null;
  }

  private boolean requestsFocusOnMouseDown = true;

  /**
   * Indicates if the PersistentCanvas grabs the
   * keyboard focus when any mouse button is pressed
   * down in this Component.
   */
  public boolean getRequestsFocusOnMouseDown () {
    return requestsFocusOnMouseDown;
  }

  /**
   * Sets the behaviour of the PersistentCanvas to
   * grab keyboard focus when the mouse is pressed
   * down in this Component.
   */
  public void setRequestsFocusOnMouseDown (boolean grabFocusOnMouseDown) {
    requestsFocusOnMouseDown = grabFocusOnMouseDown;
  }

  /**
   * Overrides processMouseEvent to grab keyboard
   * focus, if so configured.
   * @see #setRequestsFocusOnMouseDown
   */
  @Override
  protected void processMouseEvent (java.awt.event.MouseEvent e) {
    if (e.getID () == java.awt.event.MouseEvent.MOUSE_PRESSED && requestsFocusOnMouseDown)
      requestFocus ();
    super.processMouseEvent (e);
  }

  public void showPopup(PopupMenu popup, int x, int y){
    popup.show(this, x, y);
  }
}

