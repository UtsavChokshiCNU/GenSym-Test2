package com.gensym.beaneditor;

import java.awt.*;
import java.awt.event.*;
import java.lang.Math;
import java.beans.Introspector;
import java.beans.Customizer;
import com.gensym.draw.*;
import java.util.*;
import com.gensym.dlg.InputDialog;
import com.gensym.dlg.WarningDialog;
import com.gensym.message.Trace;
import com.gensym.message.Resource;
import com.gensym.message.MessageKey;
import com.gensym.message.Message;
import com.gensym.message.MessageEvent;
import com.gensym.util.Helper;

class BeanEditTool extends EventHandler
implements MouseListener, MouseMotionListener, KeyListener
,ActionListener
{
  private int start_x;
  private int start_y;
  private Rectangle[] bounds;
  private int current_x;
  private int current_y;
  private Color color;
  private boolean mouseDown = false;
  private BeanCanvas canvas;
  private EditorFrame frame;
  private Component element;
  private Component popupElement;
  private Component selectedElement = null;
  private Cursor originalCursor;
  private ViewScrollState horizontal_state; 
  private ViewScrollState vertical_state;
  //private PopupMenu popup;
  //private int newEventMenuIndex;
  private long gestureStart;
  private int gesture;
  private int portSize = 10;
  private Vector selection = new Vector();
  boolean dirtyBit = false;

  private static final int UNDETERMINED_GESTURE = 0;
  private static final int RUBBERBAND_GESTURE = 1;
  private static final int DRAG_OUTPUT_PORT_GESTURE = 2;
  private static final int DRAG_INPUT_PORT_GESTURE = 3;
  private static final int DRAG_LOOSE_END_GESTURE = 4;
  private static final int DRAG_WRAPPER_GESTURE = 5;
  private static final int RESIZE_GESTURE = 6;
  private static final int CONTAINER_SIZING_GESTURE = 7;
  private static final int CONTAINER_POSITIONING_GESTURE = 8;
  private static final int DRAG_LINK_GESTURE = 9;

  private static final boolean mouseButtonTrace = false;

  private static java.lang.reflect.Method doHookupMethod;
  private static final Class componentClass = java.awt.Component.class;
  private final HookupDispatch hooker = new HookupDispatch ();


  private static final int DELAY = 750;
  private static final Color tipColor = new Color(255, 255, 225);//what about Solaris
  private boolean toolTipsEnabled = true;
  private Thread timer;
  private int toolTipX;
  private int toolTipY;
  private long toolTipStart;
  private Component toolTipComponent;
  private ToolTip toolTip;
  private javax.swing.ToolTipManager swingTipMgr = javax.swing.ToolTipManager.sharedInstance();

  static {
    try {
      doHookupMethod = HookupDispatch.class.getDeclaredMethod
	("doHookup", new Class[] {componentClass, componentClass, MouseEvent.class, Boolean.TYPE, Boolean.TYPE});
    } catch (Exception e) {
      Trace.setExceptionTraceOn (true);
      Trace.exception (e, null);
      doHookupMethod = null;
    }
  }
  
  /*
   * Standard Tracing Requirements
   */
  static private MessageKey traceKey =
  Trace.registerMessageKey("com.gensym.beaneditor",
			   BeanEditTool.class);

  static private Resource i18nTrace =
  Trace.getBundle("com.gensym.beaneditor.translations",
		  Locale.getDefault());

  /*
   * Standard Messaging Requirements
   */

  static private Resource i18n =
  Resource.getBundle("com.gensym.resources.Messages",
		     Locale.getDefault());

  static private int GUI_LEVEL = 2;

  private static final int DEF_TRACE_LEVEL = 5;
  private static final int DEF_WARN_LEVEL  = 2;
  //private boolean allowCustomHookups;

  public BeanEditTool (PersistentCanvas parent, Frame newFrame)
  {   
    canvas = (BeanCanvas) parent;
    frame = (EditorFrame)newFrame;
    //allowCustomHookups = frame.application.allowCustomHookups;
    //System.out.println("in constructor ach = "+frame.application.allowCustomHookups);
    color = parent.current_color;
    listenerTypes = MOUSELISTENER | MOUSEMOTIONLISTENER;
    horizontal_state = canvas.getScrollState(true);
    vertical_state = canvas.getScrollState(false);

    toolTip = new ToolTip((Frame)com.gensym.core.UiApplication.getCurrentFrame());
    //toolTip.addMouseListener(this);
    timer = new Thread(new Timer(DELAY, this));
  }

  synchronized void clearSelection()
  {
    int i, size = selection.size();
    for (i=0; i<size ; i++)
      {
	Wrapper wrapper = (Wrapper) selection.elementAt(i);
	wrapper.selected = false;
	repaintElement(wrapper);
      }
    selection.removeAllElements();
    frame.updateEditMenu();
  }

  synchronized boolean selectionExists()
  {
    return selection.size() > 0;
  }

  synchronized int selectionCount()
  {
    return selection.size();
  }

  synchronized void extendSelection(Wrapper wrapper, boolean updateMenu)
  {
    if (!selection.contains(wrapper))
      {
	wrapper.selected = true;
	selection.addElement(wrapper);
	//wrapper.repaint();
	canvas.invalidateElement(wrapper);
      }
    if (updateMenu)
      frame.updateEditMenu();
  }

  synchronized void selectAll()
  {
    Component[] components = canvas.getComponents();
    int i,len = components.length;
    for (i=0; i<len ;i++)
      if (components[i] instanceof Wrapper)
	extendSelection((Wrapper)components[i],false);
    frame.updateEditMenu();
  }

  synchronized void selectInRectangle(boolean extend, Rectangle r)
  {
    if (!extend)
      clearSelection();
    r.x = r.x + canvas.getViewBounds().x;
    r.y = r.y + canvas.getViewBounds().y;
    Component[] components = canvas.findElements(r);
    int i,len = components.length;
    for (i=0; i<len ;i++)
      if (components[i] instanceof Wrapper)
	extendSelection((Wrapper)components[i],false);
    frame.updateEditMenu();
  }

  synchronized void deleteSelection()
  {
    dirtyBit = true;
    int i,j , size = selection.size();
    for (i=0; i<size ; i++)
      {
	Wrapper wrapper = (Wrapper) selection.elementAt(i);
	Port[] ports = wrapper.getPorts();
	for (j=0; j<ports.length; j++)
	  deletePort(ports[j]);
	if (wrapper.bean instanceof Component)
	  canvas.remove((Component)wrapper.bean);
	canvas.removeElement(wrapper);
      }
    selection.removeAllElements();
    frame.updateEditMenu();
  }

  void editLastSelection()
  {
    dirtyBit = true;
    if (selection.size() > 0)
      {
	Wrapper wrapper = (Wrapper) selection.lastElement();
	Point location = wrapper.getLocation();
	Dimension size = wrapper.getSize();
	Point offset = canvas.getScrollOffset();
	new ExpertBeanSheet(wrapper.getBean(), 
		      frame, 
		      location.x + (size.width / 2) + offset.x,
		      location.y + (size.height / 2) + offset.y);
      }
  }

  void runCustomizerOnLastSelection () {
    dirtyBit = true;
    if (selection.size() > 0) {
      Wrapper wrapper = (Wrapper) selection.lastElement();
      Point location = wrapper.getLocation();
      Dimension size = wrapper.getSize();
      Point offset = canvas.getScrollOffset();
      Object bean = wrapper.getBean();
      try {
	Class customizerClass = Introspector.getBeanInfo (bean.getClass()).getBeanDescriptor().getCustomizerClass ();
	Component editor = (Component) customizerClass.newInstance ();
	final Dialog dlg = new Dialog (frame);
	dlg.setLayout (new BorderLayout ());
	dlg.add (editor, BorderLayout.CENTER);
	((Customizer)editor).setObject (bean);
	String name = bean.getClass().getName();
	int index = name.lastIndexOf(".");
	if (index >= 0) 
	  name = name.substring(index+1, name.length());
	dlg.setTitle("Edit "+  name);
	dlg.pack ();
	dlg.setLocation (location.x + (size.width / 2) + offset.x,
			 location.y + (size.height / 2) + offset.y);
	dlg.setVisible (true);
	dlg.addWindowListener (new WindowAdapter () {
	  @Override
      public void windowClosing (WindowEvent wEvt) {
	    dlg.dispose ();
	  }
	});
      } catch (Exception e) {
	Trace.exception (e);
      }
    }
  }

  void deletePort(Port port)
  {
    if (port.getIsInput())
      {
	EventConnection connection = port.getConnection();
	Port input = connection.input;
	input.removeLink();
      }
    else
      port.removeLink();
    frame.updateViewMenuForDelete(port);
  }

  private void repaintSelectionGhost()
  {
    int i, size = selection.size();
    Point offset = canvas.getScrollOffset();
    int shift_x =  (current_x - start_x) + offset.x;
    int shift_y =  (current_y - start_y) + offset.y;
    for (i=0; i<size ; i++)
      {
	Wrapper wrapper = (Wrapper) selection.elementAt(i);
	Rectangle[] exactBounds = canvas.elementExactBounds(wrapper);
	int j, length = exactBounds.length;

	for (j=0 ; j<length ; j++)
	  canvas.repaintIt (shift_x + exactBounds[j].x - 1,
				shift_y + exactBounds[j].y - 1,
				exactBounds[j].width + 2, 
				exactBounds[j].height + 2);
      }
  }

  private void paintSelectionGhost(Graphics g)
  {
    int i, size = selection.size();
    Point offset = canvas.getScrollOffset();
    int shift_x =  (current_x - start_x) + offset.x;
    int shift_y =  (current_y - start_y) + offset.y;
    g.setColor(Color.black);
    for (i=0; i<size ; i++)
      {
	Wrapper wrapper = (Wrapper) selection.elementAt(i);
	Rectangle[] exactBounds = canvas.elementExactBounds(wrapper);
	int j, length = exactBounds.length;
	
	for (j=0 ; j<length ; j++)
	  g.drawRect(exactBounds[j].x + shift_x,
		     exactBounds[j].y + shift_y,
		     exactBounds[j].width,
		     exactBounds[j].height);
      }
  }

  Component[] getSelection(){
    Component[] selectedItems = new Component[selection.size()];
    selection.copyInto(selectedItems);
    return selectedItems;
  }

  @Override
  public synchronized void Draw (Graphics g)
  {
    switch (gesture)
      {
      case RUBBERBAND_GESTURE:
      case CONTAINER_SIZING_GESTURE:  
	if (mouseDown)
	  {
	    g.setColor(Color.black);
	    g.drawRect(Math.min(current_x,start_x),
		       Math.min(current_y,start_y),
		       Math.abs(current_x - start_x), 
		       Math.abs(current_y - start_y));
	  }
	break;
	  
      case DRAG_WRAPPER_GESTURE:
	paintSelectionGhost(g);
	break;

      case DRAG_INPUT_PORT_GESTURE:
      case DRAG_OUTPUT_PORT_GESTURE:
      case DRAG_LOOSE_END_GESTURE:
	if (mouseDown)
	  {
	    g.setColor(Color.black);
	    int length = bounds.length;
	    if (element instanceof LooseEnd)
	      g.drawOval(bounds[0].x, bounds[0].y,
			 bounds[0].width, bounds[0].height);
	    else
	      for (int i = 0 ; i<length ; i++)
		g.drawRect(bounds[i].x, bounds[i].y,
			   bounds[i].width - 1, bounds[i].height - 1);
	  }
	break;

      case RESIZE_GESTURE:
	Wrapper wrapper = (Wrapper)element;
	Rectangle outlineRectangle = getResizeDrawingBounds(wrapper);
	g.setColor(Color.black);
	g.drawRect(outlineRectangle.x, outlineRectangle.y,
		   outlineRectangle.width, outlineRectangle.height);
      
	break;

      case DRAG_LINK_GESTURE:
	if (mouseDown)
	  {
	    g.setColor(Color.black);
	    int length = bounds.length;
	    if (element instanceof KnowledgeLinkLooseEnd)
	      g.drawPolygon(new int[]{bounds[0].x, bounds[0].x+bounds[0].width, bounds[0].x}, 
	                    new int[]{bounds[0].y, bounds[0].y+bounds[0].height/2, 
				      bounds[0].y+bounds[0].height}, 
			    3);
	  }
	break;
      }

  }

  private Rectangle getResizeDrawingBounds(Wrapper wrapper)
  {
    Point offset = canvas.getScrollOffset();
    int corner = wrapper.getSelectedWrapperCorner();
    int resize_start_x = ((Point)(wrapper.getResizeCorner())).x + offset.x;
    int resize_start_y = ((Point)(wrapper.getResizeCorner())).y + offset.y;
    int resize_end_x   = current_x;
    int resize_end_y   = current_y;

    switch(corner)
      {
      case Wrapper.TOP:
	
	resize_end_x   = wrapper.getLocation().x +
	  wrapper.getSize().width + offset.x;
	break;
	
      case Wrapper.RIGHT:
	
	resize_end_y   = wrapper.getLocation().y +
	  wrapper.getSize().height + offset.y;
	break;
	
      case Wrapper.BOTTOM:
	
	resize_end_x   = wrapper.getLocation().x +
	  wrapper.getSize().width + offset.x;
	break;
	
      case Wrapper.LEFT:
	
	resize_end_y   = wrapper.getLocation().y +
	  wrapper.getSize().height + offset.y;
	break;
      }

    return new Rectangle(Math.min(resize_end_x, resize_start_x),
			 Math.min(resize_end_y, resize_start_y),
			 Math.abs(resize_end_x - resize_start_x), 
			 Math.abs(resize_end_y - resize_start_y));
  }

  @Override
  public void registerListeners(PersistentCanvas canvas)
  {
    frame.canvasBoundsReport("begin rL");
    canvas.addMouseListener(this);
    canvas.addMouseMotionListener(this);
    canvas.addKeyListener (this);
  }

  @Override
  public void deregisterListeners(PersistentCanvas canvas)
  {
    canvas.removeMouseListener(this);
    canvas.removeMouseMotionListener(this);
    // canvas.setCursor(originalCursor);
  }

  @Override
  public void mouseClicked(MouseEvent e)
  {  
    if (mouseButtonTrace)
      System.out.println("mouseClicked "+e);
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "mouseClicked");
    Point p = e.getPoint();
    int x = p.x;
    int y = p.y;

    switch (gesture)
      {
      case DRAG_WRAPPER_GESTURE:
        gesture = UNDETERMINED_GESTURE;
        break;
      case RUBBERBAND_GESTURE:
      case RESIZE_GESTURE:
        break;
      default:
        element = canvas.findElement(x,y);
        element = getWrapperForBeanIfAny(element);
        if ((element instanceof Wrapper) &&
	    (e.getClickCount() == 2) && !e.isMetaDown())
	  new ExpertBeanSheet(((Wrapper)element).getBean(),frame, start_x, start_y);
        break;
      }
  }
  
  @Override
  public void mousePressed(MouseEvent e)
  {
    hideToolTip();
    dirtyBit = true;
    if (mouseButtonTrace)
      System.out.println("mousePressed "+e);
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "mousePressed");
    switch (gesture)
      {     
      case DRAG_WRAPPER_GESTURE:
      case DRAG_LOOSE_END_GESTURE:
      case DRAG_OUTPUT_PORT_GESTURE:
      case DRAG_INPUT_PORT_GESTURE:
      case RUBBERBAND_GESTURE:
      case RESIZE_GESTURE:
      case CONTAINER_POSITIONING_GESTURE:
      case CONTAINER_SIZING_GESTURE:
      case DRAG_LINK_GESTURE:
	break;
      default:
	Point p = e.getPoint();
	int x = p.x;
	int y = p.y;

	// initialize gesture variables
	gesture = UNDETERMINED_GESTURE; 
	gestureStart = e.getWhen();
	start_x = x;
	start_y = y;

	Point offset = canvas.getScrollOffset();
	element = canvas.findElement(x,y);
	element = getWrapperForBeanIfAny(element);
	if (e.isPopupTrigger ()) {
	  postContextMenu (element, x, y);
	  e.consume ();
	}
	
	if (element instanceof SizingWidget)
	  {
	    SizingWidget widget = (SizingWidget)element;
	    mouseDown = true;
	    current_x = x;
	    current_y = y;
	    if (widget.direction == Directions.TOP_LEFT ||
		widget.direction == Directions.TOP ||
		widget.direction == Directions.LEFT)
	      ; // someday gesture = CONTAINER_POSITIONING_GESTURE;
	    else 
	      {
		gesture = CONTAINER_SIZING_GESTURE;
		start_x = 0;
		start_y = 0;
	      }
	  }
	else if (element != null)
	  {
	    mouseDown = true;
	    if (!e.isShiftDown() &&
		!selection.contains(element))
	      clearSelection();
	      
	    current_x = x;
	    current_y = y;
	    Rectangle[] element_bounds = canvas.elementExactBounds(element);
	    /* copy to be independent of bounds stored in element */
	    int length = element_bounds.length;
	    bounds = new Rectangle[length];
	    for (int i = 0 ; i<length ; i++)
	      {
		bounds[i] = new Rectangle(element_bounds[i].x,
					  element_bounds[i].y,
					  element_bounds[i].width, 
					  element_bounds[i].height);
		bounds[i].translate(offset.x,offset.y);
	      }

	    if (element instanceof Wrapper)
	      {
		extendSelection((Wrapper)element,true);
		((Wrapper)element).setSelectedWrapperCorner (x - offset.x - 
							     element_bounds[0].x,
							     y - offset.y - 
							     element_bounds[0].y);
	      }
          }
	else
          {
	    if (canvas.isNewBeanSelected())
	      clearSelection();
	    gesture = RUBBERBAND_GESTURE;
	    mouseDown = true;
          }
      }
  }
  
  private Component getWrapperForBeanIfAny(Component component)
  {
    if (component != null && 
	!(component instanceof Wrapper ||
	  component instanceof Port ||
	  component instanceof EventConnection ||
	  component instanceof LooseEnd ||
	  component instanceof SizingWidget ||
	  component instanceof KnowledgeLink ||
	  component instanceof KnowledgeLinkLooseEnd))
      {
	Wrapper wrapper = canvas.getWrapper(component);
	if (wrapper != null)
	  return wrapper;
	else
	  {
	    //System.out.println("ERROR!!! - no wrapper for component");
	    return null;
	  }
      }
    else
      return component;
  }

  private void postContextMenu (Component element, int x, int y) {
    //select before posting context-sensitive menu-cmh
    if (element instanceof Wrapper){
      clearSelection();
      extendSelection((Wrapper)element, true);
    }
    popupElement = element;
    //removeNewEventMenu();
    //if (element instanceof Wrapper &&
    //((Wrapper)element).bean != null)
    //addNewEventMenu(((Wrapper)element).bean.getClass());
    PopupMenu popup = frame.getPopupMenu(element, x, y);
    popup.show(canvas, x, y);
  }
    
  @Override
  public void mouseReleased(MouseEvent e)
  {
    if (mouseButtonTrace)
      System.out.println("mouseReleased "+e);
    Point p = e.getPoint();
    int x = p.x;
    int y = p.y;

    Point offset = canvas.getScrollOffset();
    switch (gesture)
      {
      case UNDETERMINED_GESTURE:
	Component element_at_release = canvas.findElement(x,y);
	element_at_release = getWrapperForBeanIfAny(element_at_release);
	if (element != null){
	  if ((element == element_at_release) && e.isPopupTrigger()) {
	    e.consume ();
	    postContextMenu (element, x, y);
	  }
	  break;
	}

      case 31415926: // DRAG_WRAPPER_GESTURE:

	if (mouseDown)
	  {
	    Point shift = canvas.getScrollOffset();
	    Rectangle[] old_bounds = canvas.elementExactBounds(element);
	    mouseDown = false;
	    gesture = UNDETERMINED_GESTURE;
	    int i, length = old_bounds.length;

	    for (i=0 ; i<length ; i++)
	      canvas.repaintIt (shift.x + old_bounds[i].x - 1,
				    shift.y + old_bounds[i].y - 1,
				    old_bounds[i].width + 1, 
				    old_bounds[i].height + 1);
	    
	    canvas.shiftElement(element, x - start_x, y - start_y);
	    
	    Rectangle new_bounds[] = canvas.elementExactBounds(element);
	    length = new_bounds.length;
	    for (i=0 ; i<length ; i++)
	      canvas.repaintIt (shift.x + new_bounds[i].x - 1,
				    shift.y + new_bounds[i].y - 1,
				    new_bounds[i].width + 1,       
				    new_bounds[i].height + 1);  
	  }      
	break;

      case DRAG_WRAPPER_GESTURE:
	mouseDown = false;
	gesture = UNDETERMINED_GESTURE;
	repaintSelectionGhost();
	int i, size = selection.size();
	for (i=0; i<size ; i++)
	  canvas.shiftElement((Component)selection.elementAt(i),
			      x - start_x, y - start_y);
	break;
	
      case DRAG_INPUT_PORT_GESTURE:
      case DRAG_OUTPUT_PORT_GESTURE:

	if (mouseDown)
	  {
	    int newX = bounds[0].x, newY = bounds[0].y;
	    Point location = element.getLocation(); 
	    Port port = (Port) element;

	    // repaintElement(element);
	    canvas.repaintIt (newX - 1, newY - 1,
				  bounds[0].width + 2, bounds[0].height + 2);
	    canvas.shiftElement(element,
				newX - location.x - offset.x, 
				newY - location.y - offset.y);

	    port.getWrapper().setPortPosition(port, newX - offset.x, newY - offset.y);
	    mouseDown = false;
	    gesture = UNDETERMINED_GESTURE;
	  }
	break;

      case DRAG_LOOSE_END_GESTURE:
	frame.getStatusBar().resetStatus ();
	if (mouseDown)
	  {
	    int newX = bounds[0].x, newY = bounds[0].y;
	    canvas.repaintIt (newX - 1, newY - 1,
				  bounds[0].width + 2, bounds[0].height + 2);
	    Component targetElement = canvas.findElement(x,y);
	    targetElement = getWrapperForBeanIfAny(targetElement);

	    if (targetElement != null && targetElement instanceof Wrapper)
	      {
		boolean customHookupRequested = e.isMetaDown () || e.isAltDown ();
		boolean restrictToExactMatch = e.isControlDown ();
		//System.out.println("hReq="+hookupRequested+" allowCH "+Preferences.currentPreferences.isCustomHookupsAllowed());
		//System.out.println ("Restrict = " + restrictToExactMatch);
		Helper hookupThread
		  = new Helper (hooker, doHookupMethod,
				new Object [] {targetElement, element, e,
						 new Boolean (customHookupRequested &&
							      Preferences.currentPreferences.isCustomHookupsAllowed()),
						 new Boolean (restrictToExactMatch)});
		hookupThread.start ();
	      }
	    mouseDown = false;
	    gesture = UNDETERMINED_GESTURE;
	  }
	break;
      
      case RESIZE_GESTURE:

	Wrapper w       = (Wrapper)element;
	int     corner  = w.getSelectedWrapperCorner();
	int     width   = w.getSize().width;
	int     height  = w.getSize().height;
	int     wx      = ((Point)w.getLocation()).x;
	int     wy      = ((Point)w.getLocation()).y;

	Rectangle r = getResizeDrawingBounds(w);

	switch (corner)
          {                  
	  case Wrapper.TOP_LEFT:
	    w.setLocation (wx + (x - start_x), wy + (y - start_y));
	    w.setSize (width - (x - start_x), height - (y - start_y));
	    break;
	  case Wrapper.TOP:
	    w.setLocation (wx, wy + (y - start_y));
	    w.setSize (width, height - (y - start_y));
	    break;
	  case Wrapper.TOP_RIGHT:
	    w.setLocation (wx, wy + (y - start_y));
	    w.setSize (width + (x - start_x), height - (y - start_y));
	    break;
	  case Wrapper.RIGHT:
	    w.setSize (width + (x - start_x), height);
	    break;
	  case Wrapper.BOTTOM_RIGHT:
	    w.setSize (width + (x - start_x), height + (y - start_y));
	    break;
	  case Wrapper.BOTTOM:
	    w.setLocation (wx, wy);
	    w.setSize (width, height + (y - start_y));
	    break;
	  case Wrapper.BOTTOM_LEFT:
	    w.setLocation (wx + (x - start_x), wy);
	    w.setSize (width - (x - start_x), height + (y - start_y));
	    break;
	  case Wrapper.LEFT:
	    w.setLocation (wx + (x - start_x), wy);
	    w.setSize (width - (x - start_x), height);
	    break;
          }
	w.ensureBeanBounds();
	w.updateForScroll(offset.x, offset.y);
	w.reestablishPortPositions();

	canvas.repaintIt (wx + offset.x, wy + offset.y, width, height);
	canvas.repaintIt (r.x - 1, r.y - 1, r.width + 2, r.height + 2);
	
	mouseDown = false;
	gesture = UNDETERMINED_GESTURE;

	break;

      case RUBBERBAND_GESTURE:

	gesture = UNDETERMINED_GESTURE; 
	mouseDown = false;
	repaintBetweenPoints(start_x,start_y,x,y);
	if (Math.abs(x - start_x) <= 3 && Math.abs(y - start_y) <= 3)
	  {
	    if (canvas.isNewBeanSelected())
	      createNewBean(new Point(Math.min(x, start_x)-offset.x, Math.min(y, start_y)-offset.y), null);
	    else
	      clearSelection();
	  }
	else
	  {
	    if (canvas.isNewBeanSelected())
	      createNewBean(new Point(Math.min(x, start_x) - offset.x, Math.min(y, start_y) - offset.y), new Dimension(Math.abs(x - start_x), 
														       Math.abs(y - start_y)));
	    else
	      selectInRectangle(e.isShiftDown(),
				new Rectangle(Math.min(x, start_x),
					      Math.min(y, start_y),
					      Math.abs(x - start_x), 
					      Math.abs(y - start_y)));
	  }
	break;
      case CONTAINER_SIZING_GESTURE:
	if (mouseDown)
	  {
	    SizingWidget widget = (SizingWidget) element;
	    // fix dragging in one dimension if not the BOTTOM_RIGHT
	    if (widget.direction == Directions.TOP_RIGHT ||
		widget.direction == Directions.RIGHT)
	      y = canvas.getContainerSize().height;
	    else if (widget.direction == Directions.BOTTOM_LEFT ||
		     widget.direction == Directions.BOTTOM)
	      x = canvas.getContainerSize().width;
	    Dimension oldSize = canvas.getContainerSize();
	    x = x - offset.x;
	    y = y - offset.y;
	    canvas.setContainerSize(x, y);
	    repaintBetweenPoints(start_x, start_y,
				 Math.max(oldSize.width, x),
				 Math.max(oldSize.height,y));
	    mouseDown = false;
	  }
	break;
      case DRAG_LINK_GESTURE:
	if (mouseDown)
	  {
	    KnowledgeLinkLooseEnd end = (KnowledgeLinkLooseEnd)element;
	    KnowledgeLink link = end.getLink();
	    Wrapper subject = link.subject;
	    Component elementAtRelease = canvas.findElement(x,y);
	    elementAtRelease = getWrapperForBeanIfAny(elementAtRelease);
	    int newX = bounds[0].x, newY = bounds[0].y;
	    canvas.repaintIt (newX - 1, newY - 1,
			      bounds[0].width + 2, bounds[0].height + 2);
	    if (elementAtRelease != null &&
		elementAtRelease instanceof Wrapper &&
		elementAtRelease != subject && 
		!subject.knows((Wrapper)elementAtRelease))
	      {
		Wrapper object = (Wrapper)elementAtRelease;
		String linkName = editFriendLink(link);
		if (linkName != null)
		{
		  link.removeLink();
	   
		  Point center1 = subject.centerPoint(), center2 = object.centerPoint();
		  Point[] points = { center1, center2 };
		  int[] widths = { 1 };
		  String[] stripeNames = { "only" };
		  Color[] colors = { Color.black };
		  String[] colorNames = { "only" };
		  
		  KnowledgeLink newLink 
		    = new KnowledgeLink(linkName, subject, object,
					points,widths,stripeNames,
					colorNames,colors);
		  //add links to end so they don't get in the way of drag & drop
		  canvas.addElement(newLink, -1);
		}
	      }
	    mouseDown = false;
	    gesture = UNDETERMINED_GESTURE;
	  }
	break;
      }

    // no element is chosen (this is done regardless of what else happens)
    element = null;
    gesture = UNDETERMINED_GESTURE; 
  }

  String editFriendLink(KnowledgeLink link){
    InputDialog dlg = new InputDialog(frame, "Edit Access Link", true, 
				      new String[]{"Name:"}, 
				      new String[]{(link.name == null ? "" : link.name)},
				      null);
    dlg.setVisible(true);
    if (!dlg.wasCancelled()){
      String[] results = dlg.getResults();
      String linkName = results[0];
      if (linkName.equals(link.name)) return linkName;
      String errorString = link.subject.getKnownBeanNameProblemIfAny(linkName);
      if (errorString != null){
	new WarningDialog(frame, "Error", true, errorString, null).setVisible(true);
	return editFriendLink(link);
      }
      else{
	link.name = linkName;
	return linkName;
      }
    }
    else return link.name;
  }

  private void createNewBean(Point p, Dimension d){
    Class  newBeanClass = null;
    Object bean = null;

    try
      {
	bean = ComponentEditor.getBean (canvas.getNewBeanClass());
	newBeanClass = (Class)bean.getClass();
	canvas.registerBeanClass(newBeanClass);
      }  
    catch (Exception ex)
      {
	Trace.exception(ex);
      }
    
    if (newBeanClass == null)
      {
	// If this bean can't be instantiated thru the normal process,
	// try to instantiate it directly.  This is currently used for 
	// generic AcitveX objects
	
	try
	  {      
	    newBeanClass = Class.forName(canvas.getNewBeanClass());
	    bean = newBeanClass.newInstance();
	    canvas.registerBeanClass(newBeanClass);
	  }  
	catch (Exception ex)
	  {
	    Message.send (new MessageEvent(GUI_LEVEL, "com.gensym.beaneditor",
					   BeanEditTool.class, i18n,
					   "cantCreateBean", new Object[] {}));
	    Trace.exception(ex);
	  }
	finally{
	    frame.application.setBeanSelection(null, null);
	}
      }
    if (newBeanClass != null)
      {
	if (d == null)
	  {  
	    if (bean instanceof Component)
	      {
		try
		  {
		    d = ((Component)bean).getPreferredSize();
		  }
		catch(Exception ex)
		  {
		    //label gives an exception, catch it and ignore
		  }
	      }
	    if (d == null)
	      d = new Dimension(50, 50);
	  }
	Wrapper wrapper = new Wrapper(Color.gray, newBeanClass,
				      p.x, p.y, d.width, d.height);   
	
	canvas.addElement(wrapper);
	//canvas.setNewBeanClass(null);
	try
	  {
	    wrapper.bean = bean;	
	    if (wrapper.bean instanceof Component)
	      {
		Component component = (Component)wrapper.bean;
		if (component.getBackground() == null)
		  {
		    Preferences prefs = Preferences.currentPreferences;
		    component.setBackground(prefs.getContainerBackgroundColor());
		  }
		canvas.addElement(component);

		Dimension unconstrainedSize = wrapper.getSize();
		wrapper.setSize(unconstrainedSize.width,
				unconstrainedSize.height);
		wrapper.ensureBeanBounds();
		Point offset = canvas.getScrollOffset();
		wrapper.updateForScroll(offset.x, offset.y);
		ComponentBeanAdapter adapter 
		  = new ComponentBeanAdapter(component,this);
		wrapper.setComponentBeanAdapter(adapter);
		component.validate();
	      }
	    else // invisible bean case
	      {
	      }
	    //select new bean-cmh
	    clearSelection();
	    extendSelection(wrapper, true);
	  }
	catch (Exception exception)
	  {
	    Message.send (new MessageEvent(GUI_LEVEL, "com.gensym.beaneditor",
					   BeanEditTool.class, i18n,
					   "cantCreateBean", new Object[] {}));
	    exception.printStackTrace();
	  }	 
      }
    frame.dropOccurred();
  }

  private void repaintBetweenPoints(int x1, int y1, int x2, int y2)
  {
    canvas.repaintIt (Math.min(x1,x2) - 1,
			  Math.min(y1,y2) - 1,
			  Math.abs(x1 - x2) + 2,
			  Math.abs(y1 - y2) + 2);
  }

  public class HookupDispatch {
    public void doHookup (Component targetElement, Component element, MouseEvent e, boolean customHookup, boolean restrictToExactMatch) {
      Wrapper wrapper = (Wrapper) targetElement;
      LooseEnd looseEnd = (LooseEnd) element;		     
      EventConnection connection = looseEnd.getConnection();
      int x = e.getX (), y = e.getY ();
      
      int syntax;
      if (customHookup &&  
	 Preferences.currentPreferences.getSyntax().getType() == HookupFactory.JAVA)
	  //frame.application.syntax.equals("java"))
 	syntax = HookupFactory.JAVA;
      else if (customHookup)
 	syntax = HookupFactory.G2SCRIPT;
      else if (restrictToExactMatch)
	syntax = HookupFactory.AUTOMATIC_EXACT;
      else
 	syntax = HookupFactory.AUTOMATIC;
      HookupDialog hookupDialog = new HookupDialog
	(wrapper,
	 connection.input,
	 frame,
	 syntax);
      // Get the hookup from the dialog (if it exists)
      Object hookup = hookupDialog.getHookup();
      
      // If the hookup was successfull then create the new port, etc.
      if (hookup != null) {
	Port port = new Port(wrapper, null, Color.lightGray, true,
			     x,y, portSize, portSize);
	port.setMethodName(hookupDialog.getMethodName());
	canvas.removeElement(looseEnd);
	port.setConnection(connection);
	connection.output = port;
	canvas.addElement(port);
	wrapper.setPortPosition(port, e.getX (), e.getY ());
      }
    }
  }

  private void repaintElement(Component element)
  {
    Point shift = canvas.getScrollOffset();
    
    int i;
    Rectangle[] old_bounds = canvas.elementExactBounds(element);
    int length = old_bounds.length;
    for (i=0 ; i<length ; i++)
      canvas.repaintIt (shift.x + old_bounds[i].x - 1,
			    shift.y + old_bounds[i].y - 1,
			    old_bounds[i].width + 1, 
			    old_bounds[i].height + 1);
  }
	    
 

  @Override
  public void mouseEntered(MouseEvent e)
  {
    // canvas.pushCursor(Cursor.getPredefinedCursor(Cursor.MOVE_CURSOR));
  }
   
  @Override
  public void mouseExited(MouseEvent e)
  {
    // canvas.popCursor();
  }

  @Override
  public void mouseDragged(MouseEvent e)
  {
    if (mouseButtonTrace)
      System.out.println("mouseDragged "+e);
    Trace.send (DEF_TRACE_LEVEL, traceKey, i18nTrace, "mouseDragged");
    Point p = e.getPoint();
    int x = p.x;
    int y = p.y;
    int x_distance = x - start_x;
    int y_distance = y - start_y;

    switch (gesture)
      {
      case UNDETERMINED_GESTURE:

	if (((x_distance * x_distance) + (y_distance * y_distance)
	     > 16) && (element != null))
	  {
	    if (element instanceof Wrapper)
	      {
		int selectedWrapperCorner = ((Wrapper)element).getSelectedWrapperCorner();

		if (selectedWrapperCorner == Wrapper.NOT_SELECTED)
		  {
		      gesture = DRAG_WRAPPER_GESTURE;
		  }
		else
                  gesture = RESIZE_GESTURE;

		mouseDragged(e); // recursive call, but gesture is set
	      }
	    else if (element instanceof Port)
	      {
		Port port = (Port) element;

		if (port.getIsInput())
		  gesture = DRAG_INPUT_PORT_GESTURE;
		else
		  gesture = DRAG_OUTPUT_PORT_GESTURE;
             
		mouseDragged(e); // recursive call, but gesture is set
	      }
	    else if (element instanceof LooseEnd)
	      {
		gesture =  DRAG_LOOSE_END_GESTURE;
		mouseDragged(e); // likewise
	      }
	    else if (element instanceof KnowledgeLinkLooseEnd){
	      gesture = DRAG_LINK_GESTURE;
	      mouseDragged(e); //again
	    }
	  }
	break;

      case DRAG_LOOSE_END_GESTURE:
	updateHookupStatus (e);
      case DRAG_INPUT_PORT_GESTURE:
      case DRAG_OUTPUT_PORT_GESTURE:
      case DRAG_LINK_GESTURE:
	if (mouseDown)
	  {
	    int i,length;
	    length = bounds.length;    
	    
	    for (i=0 ; i<length ; i++)
	      {
		canvas.repaintIt (bounds[i].x - 1,
				  bounds[i].y - 1,
				  bounds[i].width + 2, 
				  bounds[i].height + 2);
		bounds[i].translate(x - current_x, y - current_y);
	      }
	    
            current_x = x;
	    current_y = y;
	    
	    for (i=0 ; i<length ; i++)
	      canvas.repaintIt (bounds[i].x - 1,
				bounds[i].y - 1,
				bounds[i].width + 2, 
				bounds[i].height + 2);
	  }
	break;

      case DRAG_WRAPPER_GESTURE:
	repaintSelectionGhost();
	current_x = x;
	current_y = y;
	repaintSelectionGhost();
	break;

      case RESIZE_GESTURE:

	Wrapper wrapper = (Wrapper)element;     

	int old_x        = current_x;
	int old_y        = current_y;
	Point offset = canvas.getScrollOffset();
	int resize_x     = wrapper.getResizeCorner().x+offset.x;
	int resize_y     = wrapper.getResizeCorner().y+offset.y;
	int resize_end_x = x; 
	int resize_end_y = y;      
	int corner       = wrapper.getSelectedWrapperCorner();

	switch(corner)
	  {
	  case Wrapper.TOP:

	    resize_end_x   = wrapper.getLocation().x +
	      wrapper.getSize().width + offset.x;
	    break;

	  case Wrapper.RIGHT:

	    resize_end_y   = wrapper.getLocation().y +
	      wrapper.getSize().height + offset.y;
	    break;

	  case Wrapper.BOTTOM:

	    resize_end_x   = wrapper.getLocation().x +
	      wrapper.getSize().width + offset.x;
	    break;

	  case Wrapper.LEFT:

	    resize_end_y   = wrapper.getLocation().y +
	      wrapper.getSize().height + offset.y;
	    break;                   
	  }

	current_x = resize_end_x;
	current_y = resize_end_y;
	repaintBetweenPoints(old_x, old_y, resize_x, resize_y);
	repaintBetweenPoints(current_x, current_y, resize_x, resize_y);
	break;

      case RUBBERBAND_GESTURE:

	if (mouseDown)
	  {
	    repaintBetweenPoints(start_x,start_y, current_x,current_y);
	    current_x = x;
	    current_y = y;
	    repaintBetweenPoints(start_x,start_y,x,y);
	  }
	break;

      case CONTAINER_POSITIONING_GESTURE:
	break;

      case CONTAINER_SIZING_GESTURE:
	if (mouseDown)
	  {
	    SizingWidget widget = (SizingWidget) element;
	    // fix dragging in one dimension if not the BOTTOM_RIGHT
	    if (widget.direction == Directions.TOP_RIGHT ||
		widget.direction == Directions.RIGHT)
	      y = canvas.getContainerSize().height;
	    else if (widget.direction == Directions.BOTTOM_LEFT ||
		     widget.direction == Directions.BOTTOM)
	      x = canvas.getContainerSize().width;
	      
	    repaintBetweenPoints(start_x,start_y,current_x,current_y);
	    current_x = x;
	    current_y = y;
	    repaintBetweenPoints(start_x,start_y,x,y);
	  }
	break;
      }    
  }

  private void repaintEmptyRectangle(int x, int y, int w, int h, int slop)
  {
    // Top Line
    canvas.repaintIt (x,          y - slop,     x+w,          y + 2 * slop);
    // Bottom Line
    canvas.repaintIt (x,          (y+h) - slop, x+w,          (y+h)+2*slop);
    
    // Left Line
    canvas.repaintIt (x - slop,   y,            x + 2 * slop, y+h);
    // Right Line
    canvas.repaintIt (x+w - slop, y,            (x+w)+2*slop, y+h);
  }
   
  @Override
  public void mouseMoved(MouseEvent e){
    int x = e.getX();
    int y = e.getY();
    Component c = canvas.findElement(x, y);
    if (c instanceof ToolTip){
      hideToolTip();
      return;
    }

    if (toolTipComponent == null){
      if (c instanceof Port || c instanceof EventConnection || isConnectedKnowledgeLink(c)){
	toolTipComponent = c;
	toolTipX = x;
	toolTipY = y;
	timer = new Thread(new Timer(DELAY, this));
	timer.start();
      }
    }
    else{
      if (c == null){
	hideToolTip();
      }
      else{
	if (c.equals(toolTipComponent)){
	  //do nothing
	}
	else{
	  hideToolTip();
	  if (c instanceof Port || c instanceof EventConnection || isConnectedKnowledgeLink(c)){
	    toolTipComponent = c;
	    toolTipX = x;
	    toolTipY = y;
	    timer = new Thread(new Timer(DELAY, this));
	    timer.start();
	  }
	}
      }
    }
  }

  @Override
  public void keyTyped(KeyEvent e) {}

  @Override
  public void keyPressed(KeyEvent e) {
    if (gesture == DRAG_LOOSE_END_GESTURE)
      updateHookupStatus (e);
  }

  @Override
  public void keyReleased(KeyEvent e) {
    if (gesture == DRAG_LOOSE_END_GESTURE)
      updateHookupStatus (e);
  }

  private void updateHookupStatus (InputEvent e) {
    boolean hookupWillBeCustom = (e.isMetaDown () || e.isAltDown ()) && Preferences.currentPreferences.isCustomHookupsAllowed();
    boolean restrictToExactMatch = e.isControlDown ();
    String label;
    if (hookupWillBeCustom) {
      label = (Preferences.currentPreferences.getSyntax().getType() == HookupFactory.JAVA ?
	       "Java" : "G2Script");
      label = "Creating Custom " + label + " hookup";
    } else if (restrictToExactMatch)
      label = "Creating Exact hookup";
    else
      label = "Creating Default hookup";
    frame.getStatusBar().setStatus (label);
  }

  private boolean isConnectedKnowledgeLink(Component c){
    if (c instanceof KnowledgeLink)
      return (((KnowledgeLink)c).object instanceof Wrapper);
    return false;
  }

  private void hideToolTip(){
    toolTipComponent = null;
    timer.stop();
    toolTip.setVisible(false);
  }

  private String getTipText(Port port){
    if (port.getIsInput()) 
      return port.getMethodName();
    else 
      return port.getEventInfo().name;
  }

  private String getTipText(EventConnection cxn){
    String outputText;
    if (cxn.output instanceof Port)
      outputText = getTipText(((Port)cxn.output));
    else
      outputText = "???";

    /*    if (cxn.input.getSide() == Directions.LEFT)  //is l-to-r readable?
      return outputText+" <- "+getTipText(cxn.input);
    else*/
    return getTipText(cxn.input)+" \u2794 "+outputText;
  }

  private String getTipText(KnowledgeLink link){
    return link.name;
  }

  private void showToolTip(Component c){
    //hack : need to first hide any tool tips hanging around on Swing components
    swingTipMgr.setEnabled(false);
    swingTipMgr.setEnabled(true);

    if (!toolTipsEnabled) return;
    String tip;
    if (c instanceof Port)
      tip = getTipText(((Port)c));
    else if (c instanceof EventConnection)
      tip = getTipText(((EventConnection)c));
    else
      tip = getTipText((KnowledgeLink)c);
    toolTip.setTipText(tip);
    toolTip.setSize(toolTip.getPreferredSize());
    Point p = new java.awt.Point(toolTipX, toolTipY);
    p.y = p.y + 20;
    javax.swing.SwingUtilities.convertPointToScreen(p, canvas);
    toolTip.setLocation(p);
    toolTip.setVisible(true);
  }

  @Override
  public void actionPerformed(ActionEvent e){
    if ((toolTipComponent != null) && (toolTipComponent.isVisible())){
      showToolTip(toolTipComponent);
    }
  }

  public void addElements (Vector objects)
  {
    int length = objects.size();

    for (int i=0; i<length; i++)
      {
	Component obj = (Component)objects.elementAt(i);

	if (obj instanceof Wrapper) 
          {
	    Wrapper wrapper = (Wrapper)obj;
	    canvas.addElement(wrapper);
	    
	    try
              {
		if (wrapper.bean instanceof Component)
		  {
		    Component component = (Component)wrapper.bean;
		    canvas.addElement(component);
		    ComponentBeanAdapter adapter
		      = new ComponentBeanAdapter(component, this);
		    wrapper.setComponentBeanAdapter(adapter);
                  }
		else // invisible bean case
		  {
		  }
	      }
	    catch (Exception exception)
	      {
		Trace.exception(exception,null);
		System.out.println("Failed to add element to canvas");
		exception.printStackTrace();
	      }
	  }
	else if (obj instanceof Port && ! (((Port)obj).getIsInput()))
	  {
	    Port outputPort = (Port)obj;
	    outputPort.reestablishEventInfo(canvas);
	    canvas.addElement(outputPort);
	    frame.updateViewMenuForAdd(outputPort);
	  }
	else
	  canvas.addElement(obj);
      }
    System.gc();
  }


  class ToolTip extends Window{

    String tip;

    ToolTip(Frame frame){
      super(frame);
    }

    void setTipText(String tip){
      this.tip = tip;
    }
    
    @Override
    public void paint(Graphics g){
      FontMetrics metrics = g.getFontMetrics();
      Dimension size = getSize();
      g.setColor(Color.black);
      g.drawRect(0, 0, size.width - 1, size.height - 1);
      g.setColor(tipColor);
      g.fillRect(1, 1, size.width - 2, size.height - 2);
      g.setColor(getForeground());
      g.drawString(tip, 3, 2 + metrics.getAscent());
    }

    @Override
    public Dimension getPreferredSize(){
      Font font = getFont();
      FontMetrics metrics = getFontMetrics(font);
      return new Dimension(6 + metrics.stringWidth(tip), 4 + metrics.getAscent() + metrics.getDescent());
    }

    @Override
    public Dimension getMinimumSize(){
      return getPreferredSize();
    }

  }

}

