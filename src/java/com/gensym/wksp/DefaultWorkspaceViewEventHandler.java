package com.gensym.wksp;

import java.util.Locale;
import java.awt.*;
import java.awt.event.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.draw.*;
import com.gensym.dispatcher.*;
import com.gensym.classes.Item;
import com.gensym.classes.ActionButton;
import com.gensym.classes.CheckBox;
import com.gensym.classes.RadioButton;
import com.gensym.classes.ReadoutTable;
import com.gensym.classes.FreeText;
import com.gensym.classes.BorderlessFreeText;
import com.gensym.classes.KbWorkspaceImpl;
import com.gensym.classes.ImplAccess;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.ntw.TwConnectionListener;
import com.gensym.ntw.TwConnectionEvent;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2CommunicationErrorEvent;
import com.gensym.classes.TableItem;

public class DefaultWorkspaceViewEventHandler extends TableDrivenEventHandler
implements WorkspaceRepresentationTypes, TwConnectionListener,WorkspaceViewListener,
java.io.Serializable {

  static final long serialVersionUID = -7566827872321210156L;
  private static final Symbol ADMINISTRATOR_ = Symbol.intern ("ADMINISTRATOR");
  private static final Symbol ATTRIBUTE_ = Symbol.intern ("ATTRIBUTE");
  private transient boolean canvasHasFocus = false;
  private transient LineElement[] band = new LineElement[4];
  private transient int currentX, currentY;
  private transient int connectionLastX, connectionLastY,
    connectionCurrentX, connectionCurrentY;
  private transient WorkspaceConnection currentConnection;
  private transient boolean isLasso, isDrag, isButtonPress, isResizing, isConnectionDrag;
  private transient boolean okToDrag = false;
  private transient boolean isSliderDrag = false;
  private transient boolean allowHorizontalChange, allowVerticalChange;
  private transient MarkerElement resizingHandle;
  private transient long prevWhen;
  protected static int DBLCLICK_INTERVAL = 250;
  private transient int scratchArrayLength = 50;
  private transient WorkspaceElement[] scratchWkspArray = new WorkspaceElement[scratchArrayLength];
  private static final boolean debugEvts = false;
  private transient Object origItm, prevItm;
  static final Symbol JOINING_LOOSE_ENDS_ = Symbol.intern ("JOINING-LOOSE-ENDS");
  static final Symbol MAKING_NEW_JUNCTION_BLOCK_ = Symbol.intern ("MAKING-NEW-JUNCTION-BLOCK");
  static final Symbol DRAGGING_LOOSE_END_INTO_ITEM_ = Symbol.intern ("DRAGGING-LOOSE-END-INTO-ITEM");
  static final Symbol MOVING_LOOSE_END_ = Symbol.intern ("MOVING-LOOSE-END");
  private static final Symbol RUNNING_ = Symbol.intern ("RUNNING");
  private static final Symbol TABLE_HEADER_ = Symbol.intern("TABLE-HEADER");
  private transient FocusListener focalComponent = null; 
  private transient Reference g2IsRunning = new VariableReference("g2IsRunning", Boolean.TYPE);
  private transient TwAccess context;
  private static Condition movedEnoughToStartDrag
  = new NotCondition(new AndCondition
		     (new SimpleCondition(SimpleCondition.EQUAL,
					  new VariableReference("startX", Integer.TYPE),
					  new VariableReference("currentX",Integer.TYPE)),
		      new SimpleCondition(SimpleCondition.EQUAL,
					  new VariableReference("startY", Integer.TYPE),
					  new VariableReference("currentY",Integer.TYPE))));

  private void setG2IsRunning(boolean state) {
    try {
      dispatch.setVariable("g2IsRunning", new Boolean(state));
    } catch (NoSuchVariableException nsve) {
      Trace.exception(nsve);
    }
  }
    
  private void setMode(int mode) {
    switch(mode) {
    case LASSO: isLasso = true; break;
    case DRAG: isDrag = true; break;
    case CONNECTION_DRAG: isConnectionDrag = true; break;
    case BUTTON_PRESS: isButtonPress = true; break;
    case RESIZING: isResizing = true; break;
    case SLIDER_DRAG: isSliderDrag = true; break;
    default: isLasso = isDrag = isConnectionDrag = isButtonPress = isResizing = isSliderDrag = false;
    }
    try {
      dispatch.setVariable("uiMode", new Integer(mode));
    } catch (NoSuchVariableException nsve) {
      Trace.exception(nsve);
    }
  }

  @Override
  protected DispatchTable createDispatchTable()
  {
    return new WorkspaceDispatchTable(this);
  }

  public static void printEvent(String message) {
    System.out.println("EVENT: " + message);
  }

  @Override
  public void doConnectionDragMousePressed(MouseEvent e,
					   Component d,
					   PersistentCanvas canvas)
  throws IllegalAccessException
  {
    WorkspaceView view = (WorkspaceView)canvas;
    int newX = e.getX(), newY = e.getY();
    int dX = newX - connectionLastX, dY = newY - connectionLastY;
    int distance=(int)Math.sqrt(dX*dX+dY*dY);
    connectionLastX = connectionCurrentX; connectionLastY = connectionCurrentY;
    connectionCurrentX = newX; connectionCurrentY = newY;
    ConnectionDraggingGhost ghost = view.getConnectionGhost();
    ConnectionElement connectionElement = ghost.getConnectionElement();
    boolean clickedOnDraggedConnection
      = ((d == connectionElement) || (d == currentConnection));
    if (clickedOnDraggedConnection) {
      Sequence exemptElements = new Sequence();
      exemptElements.addElement(connectionElement);
      exemptElements.addElement(currentConnection);
      d = canvas.findElement(((Integer)startX.getValue(dispatch)).intValue(),
			     ((Integer)startY.getValue(dispatch)).intValue(),
			     exemptElements);
    }
    if (d == null || d == canvas) {
      Point[] vertices = connectionElement.getVertices();      
      int length = vertices.length;
      Point endPoint = vertices[length-1];
      Point prevPoint = vertices[length-2];
      boolean clickedOnBend = pointsAreClose(endPoint, prevPoint);
      if (distance > 0 && !clickedOnBend) 
	putKinkInConnectionGhost(ghost,(WorkspaceView)canvas);
      else {
	if (handleLooseEndPress(connectionElement,
				null,
				e,
				clickedOnBend,
				view)) {
	  setMode(-1);
	  currentConnection = null;
	  view.setConnectionGhost(null);
	}
      }
    } else if ((d instanceof WorkspaceElement)) {
      if (handleLooseEndPress(connectionElement,
			      (WorkspaceElement)d,
				e,
			      false,
			      view)) {
	setMode(-1);
	currentConnection = null;
	view.setConnectionGhost(null);
      }
      else 
	putKinkInConnectionGhost(ghost,view);
    }
  }

  @Override
  public void doConnectionMousePressed(MouseEvent e)
       throws IllegalAccessException
  {
    Reference targetRef = new TargetReference();
    WorkspaceElement w = (WorkspaceElement)targetRef.getValue(dispatch);
    PersistentCanvas canvas = (PersistentCanvas)(new ContainerReference()).getValue(dispatch);
    WorkspaceView view = (WorkspaceView)canvas;
    Reference viewBoundsRef =
      new NestedPropertyReference(Rectangle.class,
				  "getViewBounds",
				  new ContainerReference());
    Rectangle viewBounds = (Rectangle)viewBoundsRef.getValue(dispatch);
    Reference xRef
      = new NestedPropertyReference(Integer.TYPE,
				    "getX",
				    new EventReference());
    Reference yRef
      = new NestedPropertyReference(Integer.TYPE,
				    "getY",
				    new EventReference());
    int x=((Integer)xRef.getValue(dispatch)).intValue();
    int y=((Integer)yRef.getValue(dispatch)).intValue();
    x+=viewBounds.x;y+=viewBounds.y;
    if (((WorkspaceConnection)w).insideLooseEnd(x, y)) {
      currentConnection = (WorkspaceConnection)w;
      setMode(CONNECTION_DRAG);
      doConnectionDragPress(e);
    } else
      doLassoPress(e);
  }

  @Override
  public void doWorkspaceElementMousePressed(MouseEvent e)
       throws G2AccessException, IllegalAccessException
  {
    Reference targetRef = new TargetReference();
    WorkspaceElement w = (WorkspaceElement)targetRef.getValue(dispatch);
    PersistentCanvas canvas = (PersistentCanvas)(new ContainerReference()).getValue(dispatch);

    if ((w instanceof WorkspaceButton) && ((Boolean)g2IsRunning.getValue(dispatch)).booleanValue())
      doButtonPress (e);
    else if ((w instanceof ConnectionElement)) 
      doConnectionMousePressed(e);
    else {
      WorkspaceView view = (WorkspaceView)canvas;
      if (w.isSelected ()) {
	if (e.isShiftDown ()) {
	  view.removeElementFromSelection (w);
	  return;
	}
	doDragPress (e);
      } else {
	if (!e.isShiftDown () ||
	    view.haveSelectedConnections()) //ConnectionElements should
	  //not be selectable along with any other elements.
	  view.selectElements(new WorkspaceElement[]{w});
	else
	  view.addElementToSelection (w);
	doDragPress (e);
      }      
    }
  }
  
  @Override
  public void postContextMenu (MouseEvent e)
       throws IllegalAccessException
  {
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    Reference targetRef = new TargetReference();
    Component d = (Component)targetRef.getValue(dispatch);
      /*canvas.findElement (((Integer)currentX.getValue(dispatch)).intValue(),
				      ((Integer)Y.getValue(dispatch)).intValue(),
				      true);*/
    WorkspaceView wksp = (WorkspaceView)canvas;
    Item item;
    if (d == null || !(d instanceof WorkspaceElement)) {
      if (d instanceof WorkspaceView) {
	wksp.clearSelection ();	// Clear the selection so we can put up a menu for the kb-workspace
	item = wksp.getWorkspace();
	if (item == null) return;
	//printComponent((Component)canvas);
      } else
	return;
    } else {
      WorkspaceElement wElt = (WorkspaceElement)d;
      item = wElt.getItem();
      if (debugEvts)
	System.out.println ("Element is already selected = " + wElt.isSelected ());
      if (!wElt.isSelected ()) {
	wksp.clearSelection();
	wksp.addElementToSelection(wElt);
      }
    }
    //System.out.println ("Posting Context Menu For : " + d + " in response to " + e);
    //PopupMenuUtility.postContextMenu (wksp, item, e);
    postMenuFromThread(wksp,item, e);
  }

  private static MenuPosterThread theMenuPosterThread;
  
  // maybe should add some synchronization here, but it is unlikely
  // to make a difference.
  private void postMenuFromThread(WorkspaceView wksp, Item item, MouseEvent e) {
    if (theMenuPosterThread == null || !theMenuPosterThread.isAlive()) {
    theMenuPosterThread = new MenuPosterThread();
    theMenuPosterThread.start();
    }      
    theMenuPosterThread.post(wksp,item, e);
  }
  
  @Override
  public void noteSliderPress (MouseEvent e, SliderInput sliderInput)
       throws IllegalAccessException
  {
    currentX = ((Integer)startX.getValue(dispatch)).intValue();
    currentY = ((Integer)startY.getValue(dispatch)).intValue();
    isSliderDrag = true;
  }
  
  @Override
  public void doResizePress (MouseEvent e, MarkerElement marker)
       throws IllegalAccessException
  {
    Rectangle bnds = null;
    setMode(RESIZING);
    WorkspaceView wksp    = (WorkspaceView) ((PersistentCanvas)e.getSource());
    int numSelected       = wksp.getSelection().length;
    resizingHandle        = marker;
    allowHorizontalChange = marker.isHorizontallyExtensible ();
    allowVerticalChange   = marker.isVerticallyExtensible ();
    WorkspaceElement elt  = wksp.getWorkspaceElementFromMarker (marker);
    bnds = ((DrawElement)elt).getExactBounds()[0];
    currentX = ((Integer)startX.getValue(dispatch)).intValue();
    currentY = ((Integer)startY.getValue(dispatch)).intValue();
    setStartLocation(bnds.x, bnds.y);
    Rectangle vBounds = wksp.getViewBounds ();
    if (!allowHorizontalChange)
      currentX = bnds.x + bnds.width - vBounds.x;
    else if (!allowVerticalChange)
      currentY = bnds.y + bnds.height - vBounds.y;
    wksp.addGhosts ();
    if (debugEvts)
      System.out.println ("Mouse Event " + e);
    if (debugEvts) {
      Rectangle vb = wksp.getViewBounds ();
      System.out.println ("ViewBounds = " + vb);
      System.out.println ("Pt = " + (currentX + vb.x) + ", " + (currentY + vb.y));
      System.out.println ("Element Bounds = " + bnds);
    }
    if (debugEvts) {
      System.out.println ("currentX = " + bnds.x + " + " + bnds.width + " - " + vBounds.x);
      System.out.println ("Mouse down on resize corner at (" + currentX + ", " + currentY + ")");
    }
  }

  @Override
  public void doSliderDrag (MouseEvent e) {
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    int prevX = currentX; currentX = e.getX();
    try {
      if (!((Boolean)g2IsRunning.getValue(dispatch)).booleanValue())
	return;
    } catch(IllegalAccessException iae) {
      Trace.exception(iae);
    }
    SliderInput sliderInput = ((WorkspaceDispatchTable)dispatch).getSliderInput();
    WorkspaceSliderImpl slider = sliderInput.getSlider();
    Rectangle vBounds = canvas.getViewBounds();
    Rectangle bounds = slider.getBounds();
    bounds.translate(-vBounds.x,-vBounds.y);
    Point sliderInputLocation = sliderInput.getLocation();
    int halfWidth = sliderInput.getSize().width/2;
    int deltaX = currentX - (sliderInputLocation.x + halfWidth - vBounds.x);
    slider.doInputShift(deltaX);
  }
    
  @Override
  public void doResizeDrag (MouseEvent e) {
    int prevX = currentX, prevY = currentY;
    currentX = e.getX (); currentY = e.getY ();
    PersistentCanvas canvas       = (PersistentCanvas) e.getSource ();
    WorkspaceView wksp            = (WorkspaceView)canvas;
    currentX = (allowHorizontalChange ? currentX : prevX);
    currentY = (allowVerticalChange   ? currentY : prevY);
    Rectangle vBounds = wksp.getViewBounds ();
    wksp.resizeGhosts (resizingHandle, currentX + vBounds.x, currentY + vBounds.y);
    if (debugEvts)
      System.out.println ("Mouse drag on resize corner at (" + (currentX+vBounds.x)
			  + ", " + (currentY+vBounds.y) + ") when view bounds = " + vBounds);
  }

  @Override
  public void doSliderRelease (MouseEvent e) {
    setMode(-1);
    try {
      ((WorkspaceDispatchTable)dispatch).getSliderInput().getSlider().setSliderValueUsingCurrentLocation();
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    ((WorkspaceDispatchTable)dispatch).getSliderInput().getSlider().setDragging(false);
    try {
      dispatch.setVariable("sliderInput",null);
    } catch (NoSuchVariableException nsve) {
      Trace.exception(nsve);
    }
  }

  @Override
  public void doResizeRelease (MouseEvent e) {
    setMode(-1);
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    WorkspaceView view = (WorkspaceView)canvas;
    Rectangle vb = canvas.getViewBounds ();
    view.removeGhosts ();
    if (debugEvts) {
      System.out.println ("\n Resized corner from (" +
			  startX + ", " + startY + ") to (" +
			  currentX + ", " + currentY + ")");
      System.out.println ("Element is (" +
			  startX + ", " + startY +
			  ") -> (" + (currentX + vb.x) +
			  ", " + (currentY + vb.y) + ")");
    }
    try {
      view.resizeSelection(resizingHandle, currentX + vb.x, currentY + vb.y);
    } catch (FatalWorkspaceException fwe) {
      Trace.exception(fwe);
    }
  }

  private void doButtonPress (MouseEvent e)
  throws IllegalAccessException
  {
    setMode(BUTTON_PRESS);
    Component d = ((PersistentCanvas)e.getSource ()).findElement
      (((Integer)startX.getValue(dispatch)).intValue(),
       ((Integer)startY.getValue(dispatch)).intValue(),
       true);
    WorkspaceButton btn = (WorkspaceButton)d;
    prevItm = origItm = btn;
    btn.setArmed(true);
  }

  @Override
  public void doButtonDrag (MouseEvent e) {
    int currentX = e.getX (), currentY = e.getY ();
    Component d = ((PersistentCanvas)e.getSource ()).findElement (currentX, currentY, true);
    if (!(d instanceof WorkspaceButton)) {
      if (prevItm == origItm) {
	((WorkspaceButton)origItm).setArmed(false);
	prevItm = d;
      }
      return;
    }
    WorkspaceButton btn = (WorkspaceButton)d;
    if (prevItm == btn)
      return;
    prevItm = btn;
    // Inside a new button, original or otherwise
    if ((origItm != btn))
      ((WorkspaceButton)origItm).setArmed(false);
    else
      btn.setArmed(true);
  }

  @Override
  public void doButtonRelease (MouseEvent e) {
    int currentX = e.getX (), currentY = e.getY ();
    PersistentCanvas canvas = (PersistentCanvas)e.getSource();
    Component d = canvas.findElement (currentX, currentY, true);
    if (!(d instanceof WorkspaceButton))
      return;
    WorkspaceButton btn = (WorkspaceButton)d;
    if (origItm != btn)
      return;
    btn.setArmed(false);
    
    if (debugEvts) 
      System.out.println ("\nPressing Button in G2!\n");
    try {
      Item item = btn.getItem();
      if (d instanceof WorkspaceActionButtonImpl) 
	((ActionButton)item).invoke();
      else if (d instanceof WorkspaceRadioButtonImpl) {
	Symbol newStatus = WorkspaceRadioButton.ON_;
	if (((WorkspaceRadioButtonImpl)d).getStatus().booleanValue())
	  newStatus = WorkspaceRadioButton.OFF_;
	((RadioButton)item).setButtonStatus(newStatus);
      } else if (d instanceof WorkspaceCheckBoxImpl) {
	Symbol newStatus = WorkspaceCheckBox.ON_;
	if (((WorkspaceCheckBoxImpl)d).getStatus().booleanValue())
	  newStatus = WorkspaceCheckBox.OFF_;
	((CheckBox)item).setButtonStatus(newStatus);
      } else if (d instanceof WorkspaceTypeInBoxImpl) {
	((Editable)d).setEditing(true);
	//focalComponent = (FocusListener)d;
      } 
    } catch (G2AccessException g2ae) {
      // fix this: should at least send a message to the user
      // Also don't know if isButtonPress should still be set to false
      // - rpenny
      g2ae.printStackTrace();
    }
    setMode(-1);
  }
  
  @Override
  public void doDragPress (MouseEvent e)
       throws IllegalAccessException
  {
    setMode(-1);
    okToDrag = true;
    currentX = ((Integer)startX.getValue(dispatch)).intValue();
    currentY = ((Integer)startY.getValue(dispatch)).intValue();
  }

  public void startDrag(WorkspaceView view) {
    setMode(DRAG);
    view.addGhosts ();
  }
  
  @Override
  public void doDragDrag (MouseEvent e) {
    if (!okToDrag)
      return;
    int newX = e.getX ();
    int newY = e.getY ();
    if ((newX == currentX) && (newY == currentY))
      return;
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    WorkspaceView view = (WorkspaceView)canvas;
    if (!isDrag) {
      try {
	if (movedEnoughToStartDrag.isSatisfied(dispatch)) 
	  startDrag(view);
      } catch (IllegalAccessException iae) {
	Trace.exception(iae);
      }
    }
    if (!isDrag) return;
    if ((newX == currentX) && (newY == currentY))
      return;
    view.moveGhosts (newX - currentX, newY - currentY);
    currentX = newX; currentY = newY;    
  }

  /*private Integer outX, outY = null;
  private void doConstrainedDrag(MouseEvent e) {
    
    int newX = e.getX ();
    int newY = e.getY ();
    if ((newX == currentX) && (newY == currentY))
      return;
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    WorkspaceView view = (WorkspaceView)canvas;
    if (!isDrag) {
      try {
	if (movedEnoughToStartDrag.isSatisfied(dispatch)) 
	  startDrag(view);
      } catch (IllegalAccessException iae) {
	Trace.exception(iae);
      }
    }
    if (!isDrag) return;
    Rectangle lbounds = view.getLogicalBounds();
    Rectangle gbounds = view.getGhostBounds();
    Rectangle vbounds = view.getViewBounds();
    Rectangle bounds = gbounds.intersection(lbounds);
    int currentlX = newX+vbounds.x;
    int currentlY = newY+vbounds.y;
    int r = bounds.x + bounds.width;
    int b = bounds.y + bounds.height;
    int gr = gbounds.x + gbounds.width;
    int gb = gbounds.y + gbounds.height;    
    
    int deltaX, deltaY;
    int rdeltaX = newX - currentX, rdeltaY = newY - currentY; 
    
    deltaX = rdeltaX;
    boolean outOnRight = gr > r;
    boolean outOnLeft = gbounds.x < bounds.x;
    if (outOnRight) {
      if (outX == null) {	
	outX = new Integer(newX);
      }
      else if (newX <= outX.intValue()) {
	outX = null;
      }
      if (outX == null)
	deltaX = Math.min(0, rdeltaX);
      else 
	deltaX = 0;
    } else if (outOnLeft) {
      if (outX == null)
	outX = new Integer(newX);
      else if (newX >= outX.intValue())
	outX = null;
      if (outX == null)
	deltaX = Math.max(0, rdeltaX);
      else 
	deltaX = 0;
    }

    deltaY = rdeltaY;
    boolean outOnBottom = gb > b;
    boolean outOnTop = gbounds.y < bounds.y;
    
    if (outOnBottom) {
      if (outY == null) 
	outY = new Integer(newY);
      else if (newY <= outY.intValue())
	outY = null;
      if (outY == null)
	deltaY = Math.min(0, rdeltaY);
      else 
	deltaY = 0;
    } else if (outOnTop) {
      if (outY == null)
	outY = new Integer(newY);
      else if (newY >= outY.intValue())
	outY = null;
      if (outY == null)
	deltaY = Math.max(0, rdeltaY);
      else 
	deltaY = 0;
    }
    int inewX = Math.min(lbounds.x+lbounds.width,Math.max(lbounds.x,currentlX));
    int inewY = Math.min(lbounds.y+lbounds.height,Math.max(lbounds.y,currentlY));
    int adjustX = 0;
    int adjustY = 0;
    view.moveGhosts (deltaX + adjustX, deltaY + adjustY);
    
    gbounds = view.getGhostBounds();
    bounds = gbounds.intersection(lbounds);
    deltaX = 0; deltaY = 0;
    if (gbounds.x < bounds.x)
      deltaX = bounds.x - gbounds.x;
    else if ((gbounds.x+gbounds.width)>(bounds.x+bounds.width))
      deltaX = (bounds.x+bounds.width)-(gbounds.x+gbounds.width);
    if (gbounds.y < bounds.y)
      deltaY = bounds.y - gbounds.y;
    else if ((gbounds.y+gbounds.height)>(bounds.y+bounds.height))
      deltaY = (bounds.y+bounds.height)-(gbounds.y+gbounds.height);
    if (deltaY != 0 || deltaX !=0) {
      if (outX == null)
	outX = new Integer(newX);
      if (outY == null)
	outY= new Integer(newY);
      outX = new Integer(outX.intValue() - deltaX);
      outY = new Integer(outY.intValue() - deltaY);
      view.moveGhosts(deltaX, deltaY);
    }
    currentX = newX; currentY = newY;
  }*/

  @Override
  public void doDragRelease (MouseEvent e, boolean enlargeWorkspaceIfNeccessary)
       throws IllegalAccessException
  {

    int endX = e.getX ();
    int endY = e.getY ();
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    WorkspaceView view = (WorkspaceView)canvas;
    int stX = ((Integer)startX.getValue(dispatch)).intValue();
    int stY = ((Integer)startY.getValue(dispatch)).intValue();
    view.moveSelection(endX-stX, endY-stY, enlargeWorkspaceIfNeccessary);
    endDragState(e);

  }

  @Override
  public void endDragState(MouseEvent e) {
    PersistentCanvas canvas = (PersistentCanvas)e.getSource();
    if (isDrag) {
      WorkspaceView view = (WorkspaceView)canvas;
      view.removeGhosts ();
      setMode(-1);
    }
    okToDrag = false;
  }

  private boolean pointsAreClose(Point p1, Point p2) {
    int proxInt = 10;
    return Math.abs(p1.x - p2.x) < proxInt && Math.abs(p1.y - p2.y) < proxInt;
  }

  private Point[] removeEndPoint(Point[] points) {
    int length = points.length;
    Point[] newPoints = new Point[length-1];
    for (int i=0;i<length-1;i++) {
      newPoints[i] = points[i];
    }
    return newPoints;
  }
  
  public boolean handleLooseEndPress(ConnectionElement ce,
				     WorkspaceElement we,
				     MouseEvent e,
				     boolean clickedOnBend,
				     WorkspaceView view) {
    boolean makeConnection = false;
    Symbol makeConnectionMode = null;
    Point[] vertices = ce.getVertices();      
    if (we == null) {
      int length = vertices.length;
      if (clickedOnBend) 
	vertices = removeEndPoint(vertices);
      length = vertices.length;
      Point endPoint = vertices[length-1];
      Point prevPoint = vertices[length-2];
      if (pointsAreClose(endPoint, prevPoint)) 
	ce.setVertices(vertices);
      else {
	makeConnection = true;
	makeConnectionMode = MOVING_LOOSE_END_;
      }
    } else if (we instanceof WorkspaceConnection) {
      int x=e.getX(), y=e.getY();
      PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
      Rectangle viewBounds = canvas.getViewBounds();
      x+=viewBounds.x;y+=viewBounds.y;
      makeConnectionMode
	= (((WorkspaceConnection)we).insideLooseEnd(x, y)?
	   JOINING_LOOSE_ENDS_:MAKING_NEW_JUNCTION_BLOCK_);
      makeConnection = true;
    } else if (we instanceof WorkspaceIcon) {
      Item item = we.getItem();
      Symbol representationType = ICON_WITHOUT_CONNECTIONS;
      try {
	representationType = item.getRepresentationType();
      } catch (G2AccessException g2ae) {Trace.exception(g2ae);}
      if (representationType.equals(ICON_WITH_CONNECTIONS)) {
	makeConnectionMode=DRAGGING_LOOSE_END_INTO_ITEM_;
	makeConnection = true;
      } else {
	if (debugEvts)
	  System.out.println("CAN NOT CONNECT TO ICON " + we);
      }
    }
    else {
      if (debugEvts)
	System.out.println("CAN NOT CONNECT TO " + we);
    }
    if (makeConnection) {
      WorkspaceConnection wc = currentConnection;
      Sequence connectionPositionSequence
	= WorkspaceUtil.convertPointArrayToVerticesSequence(vertices);
      try {
	view.makeConnection(wc, we,
			    makeConnectionMode,
			    connectionPositionSequence);
      } catch (G2AccessException g2ae) {
	makeConnection = false;
	Trace.exception (g2ae);
      }
    }
    return makeConnection;
  }
  
  private void putKinkInConnectionGhost(ConnectionDraggingGhost ghost,
					WorkspaceView canvas) {    
    ghost.setKinked(true);
    canvas.invalidateElement(ghost.getConnectionElement());
  }
  
  @Override
  public void doConnectionDragPress(MouseEvent e) {
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    WorkspaceView view = (WorkspaceView)canvas;
    connectionLastX = connectionCurrentX; connectionLastY = connectionCurrentY;
    connectionCurrentX = e.getX(); connectionCurrentY = e.getY();
    view.setConnectionGhost((ConnectionDraggingGhost)currentConnection.getDraggingGhost());
  }

  @Override
  public void doConnectionDragDrag (MouseEvent e) {
    int newX = e.getX ();
    int newY = e.getY ();
    if ((newX == connectionCurrentX) && (newY == connectionCurrentY))
      return;
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    WorkspaceView view = (WorkspaceView)canvas;
    view.moveConnectionGhost(newX - connectionCurrentX, newY - connectionCurrentY);
    connectionLastX = connectionCurrentX; connectionLastY = connectionCurrentY;
    connectionCurrentX = newX; connectionCurrentY = newY;    
  }

  @Override
  public void doConnectionDragRelease (MouseEvent e) {
    //int endX = e.getX ();
    //int endY = e.getY ();
    //PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    //WorkspaceView view = (WorkspaceView)canvas;
    //view.moveSelection (endX - startX, endY - startY);
    //view.removeGhosts ();
    //isConnectionDrag = false;//only if not double click
  }
  
  @Override
  public void doLassoPress (MouseEvent e) {
    setMode(LASSO);
    if (e.isShiftDown ())
      return;
    PersistentCanvas canvas = (PersistentCanvas)e.getSource ();
    WorkspaceView view = (WorkspaceView)canvas;
    if (view.pendingPaletteDrop)
      lassoColor = Color.green;
    view.clearSelection ();
  }

  private Color lassoColor = Color.red;
  @Override
  public void doLassoDrag (MouseEvent e)
       throws IllegalAccessException
  {
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    if (band[0] != null) {
      canvas.removeElement (band[0]);
      canvas.removeElement (band[1]);
      canvas.removeElement (band[2]);
      canvas.removeElement (band[3]);
    }
    
    currentX = e.getX ();
    currentY = e.getY ();
    Rectangle viewBounds = canvas.getViewBounds ();
    int deltaX = viewBounds.x;
    int deltaY = viewBounds.y;
    int stX = ((Integer)startX.getValue(dispatch)).intValue();
    int stY = ((Integer)startY.getValue(dispatch)).intValue();
    if (false)
      System.out.println ("rb from (" + (stX+deltaX)
			  + ", " + (stY+deltaY)
			  + ") to (" + (currentX+deltaX)
			  + ", " + (currentY+deltaY) + ")");
    
    canvas.addElement (band[0] = new LineElement (lassoColor,
						  stX + deltaX, stY + deltaY,
						  currentX + deltaX, stY + deltaY));
    canvas.addElement (band[1] = new LineElement (lassoColor,
						  currentX + deltaX, stY + deltaY,
						  currentX + deltaX, currentY + deltaY));
    canvas.addElement (band[2] = new LineElement (lassoColor,
						  currentX + deltaX, currentY + deltaY,
						  stX + deltaX, currentY + deltaY));
    canvas.addElement (band[3] = new LineElement (lassoColor,
						  stX + deltaX, currentY + deltaY,
						  stX + deltaX, stY + deltaY));
    canvas.invalidateElement (band[0]);
    canvas.invalidateElement (band[1]);
    canvas.invalidateElement (band[2]);
    canvas.invalidateElement (band[3]);
  }

  @Override
  public void doLassoRelease (MouseEvent e)
       throws IllegalAccessException
  {
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    int endX = e.getX ();
    int endY = e.getY ();
    Rectangle viewBounds = canvas.getViewBounds ();
    int dX = viewBounds.x; // (pbk notes that canvas needs consistent coordinate
    int dY = viewBounds.y; //  system in its API)
    int stX = ((Integer)startX.getValue(dispatch)).intValue();
    int stY = ((Integer)startY.getValue(dispatch)).intValue();
    int temp;
    if (band[0] != null) {
      canvas.removeElement (band[0]);
      canvas.removeElement (band[1]);
      canvas.removeElement (band[2]);
      canvas.removeElement (band[3]);
      band[0] = null;
      band[1] = null;
      band[2] = null;
      band[3] = null;
    }
    WorkspaceView view = (WorkspaceView)canvas;
    if (view.pendingPaletteDrop) {
      int xDiff = Math.abs(endX - stX);
      int yDiff = Math.abs(endY - stY);      
      if (xDiff == 0 && yDiff == 0) {
	//DO NOTHING SINCE THIS SHOULD ALSO PRODUCE A MOUSE CLICKED EVENT
	//SO THE DROP WILL HAPPEN DOWN THERE
      } else if (Math.sqrt(xDiff*xDiff+yDiff*yDiff) < 7) {
	view.dropItem(e, null);
      } else
	view.dropItem(e, new Point(stX, stY));
    } else {
      if (endX < stX) {
	temp = endX; endX = stX; stX = temp; setStartLocation(temp, stY);}
      if (endY < stY) {
	temp = endY; endY = stY; stY = temp; setStartLocation(stX,temp);}                
      Component[] selectedElements = canvas.findElements (new Rectangle (stX + dX, stY + dY,
									 endX - stX, endY - stY));
      WorkspaceElement[] wkspElements = filterElements (selectedElements);
      //fireEvent (SELECT, DrawElements);
      if (wkspElements.length != 0)      
	view.addElementsToSelection (wkspElements);
    }
    setMode(-1);
    lassoColor = Color.red;
  }

  private synchronized WorkspaceElement[] filterElements (Component[] elts) {
    int numWkspElts=0;
    if (scratchArrayLength < elts.length) {
      scratchArrayLength = elts.length;
      scratchWkspArray = new WorkspaceElement [scratchArrayLength];
    }
    for (int i=0; i<elts.length; i++) {
      Component elt = elts[i];
      if ((elt instanceof WorkspaceElement) &&
	  !(elt instanceof WorkspaceConnection)&&
	  !(elt instanceof WorkspaceAttributeDisplayImpl) &&
	  !((elt instanceof WorkspaceTextBoxImpl) &&
	    (((WorkspaceElement)elt)).getItem () instanceof com.gensym.classes.NameBox))
	scratchWkspArray[numWkspElts++] = (WorkspaceElement)elt;
    }
    WorkspaceElement[] wkspElts = new WorkspaceElement[numWkspElts];
    System.arraycopy (scratchWkspArray, 0, wkspElts, 0, numWkspElts);
    return wkspElts;
  }

  public void editAttributeInTable(WorkspaceTableImpl table,
				   int rowIndex) {
    Item item = table.getItem();
    if (!(item instanceof TableItem)) {
      return;
    }
    TableItem tableItem = (TableItem)item;
    try {
      Item representedItem = (Item) tableItem.getRepresentedItem();
      //BUG IN G2: getTableLayout will throw a class cast exception 
      // because the attr. is declared in g2 to return a Structure.
      Sequence tableLayout = (Sequence)
	tableItem.getPropertyValue
	(com.gensym.util.symbol.SystemAttributeSymbols.TABLE_LAYOUT_);
      Structure rowLayout = (Structure) tableLayout.elementAt(rowIndex);
      Symbol attributeName = (Symbol)
	rowLayout.getAttributeValue(ATTRIBUTE_, null);
      if (attributeName != TABLE_HEADER_) 
	new com.gensym.editor.text.Session (representedItem,attributeName, null);
    } catch(com.gensym.util.NoSuchAttributeException nsae) {
      Trace.exception(nsae);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
  }

  private static final Symbol TABLE_ = Symbol.intern ("TABLE");
  private static final com.gensym.wksp.configurations.Choice tableMenuChoice
  = new com.gensym.wksp.configurations.Choice(TABLE_,
					      com.gensym.wksp.configurations.OperationTypes.ITEM_MENU_);
  private static final Symbol EDIT_ = Symbol.intern ("EDIT");
  private static final com.gensym.wksp.configurations.Choice editMenuChoice
  = new com.gensym.wksp.configurations.Choice(EDIT_,
					      com.gensym.wksp.configurations.OperationTypes.TABLE_MENU_);
  private static final Symbol CLICK_TO_EDIT_ = Symbol.intern ("CLICK-TO-EDIT");
  private static final com.gensym.wksp.configurations.Choice clickToEditMenuChoice
  = new com.gensym.wksp.configurations.Choice(CLICK_TO_EDIT_,
					      com.gensym.wksp.configurations.OperationTypes.NON_MENU_);    
  @Override
  public void doMouseClicked(MouseEvent e) {
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    int stX = 0, stY = 0;
    try {
      stX = ((Integer)startX.getValue(dispatch)).intValue();
      stY = ((Integer)startY.getValue(dispatch)).intValue();
    } catch (IllegalAccessException iae) {
      Trace.exception(iae);
    }
    if (canvas instanceof WorkspaceView && ((WorkspaceView)canvas).pendingPaletteDrop) {
      ((WorkspaceView)canvas).dropItem(e, null);
      return;
    }
    Component thing = canvas.findElement (stX, stY, true);
    if (thing instanceof MouseListener)
      ((MouseListener)thing).mouseClicked(e);
    if (debugEvts)
      System.out.println ("Received Mouse Click! " + e + " on " + thing);
    if (thing == null)
      return;

    if (e.getWhen() - prevWhen > DBLCLICK_INTERVAL)  {
      if (! (thing instanceof WorkspaceElement))
        return;
      prevWhen = e.getWhen();
    } else {
      WorkspaceView view = (WorkspaceView) canvas;
      if (!view.getAllowDoubleClickToEdit ()) 
	return;     
      if (thing instanceof WorkspaceConnection) {
	setMode(-1);
	currentConnection = null;
	view.removeGhosts();
	view.clearSelection();
      }
      if (!(thing instanceof WorkspaceElement)) return;

      Item item = ((WorkspaceElement)thing).getItem();
	  
	
	// For item instance of FreeText & BorderlessFreeText do not go into this logic
	// we do not want to make allowEdit == true to edit on the fly, we want to pop up the dialog box
	// to do it and that will happen if we pass this logic block and continue the flow of execution further
	// to call editItem 
	if ((thing instanceof WorkspaceTextBoxImpl && !(item instanceof FreeText) && !(item instanceof BorderlessFreeText)) ||
		(thing instanceof WorkspaceTableImpl &&
		!(item instanceof ReadoutTable))) {
	 
	boolean allowEdit = false;
	try {
	  allowEdit
	    = com.gensym.wksp.configurations.ConfigurationSupport.choiceIsAvailable
	    (item, editMenuChoice);
	  allowEdit = allowEdit &&
	    com.gensym.wksp.configurations.ConfigurationSupport.choiceIsAvailable
	    (item, clickToEditMenuChoice);	  
	} catch (G2AccessException g2ae) {
	  Trace.exception(g2ae);
	  allowEdit = false;
	}
	if (allowEdit) {
	  int mouseX = e.getX();
	  int mouseY = e.getY();	  
	  if (thing instanceof Editable) {
	    ((Editable)thing).setEditing(true);
	    int index = ((Editable)thing).getIndex(new Point(mouseX, mouseY));
	    if (index >=0) 
	      ((Editable)thing).setIndex(index);
	  } else {
	    WorkspaceTableImpl table = (WorkspaceTableImpl)thing;
	    int rowIndex = table.getRowIndex(mouseY);
	    if (rowIndex != -1) 
	      editAttributeInTable(table, rowIndex);
	  }
	}
	return;
      }       
      boolean available = false;
      try {
	available 
	  = com.gensym.wksp.configurations.ConfigurationSupport.choiceIsAvailable
	  (item, tableMenuChoice);
      } catch (G2AccessException g2ae) {
	Trace.exception(g2ae);
	available = false;
      }
      if (!available) return;

      boolean running = false;
      try {
	running = ((Boolean)g2IsRunning.getValue(dispatch)).booleanValue();
      } catch (IllegalAccessException iae) {
	Trace.exception(iae);
      }
      if (thing instanceof WorkspaceButton && running)
	return;
      prevWhen = e.getWhen();
      try {
	TwAccess context = (TwAccess) ((com.gensym.classes.ImplAccess)item).getContext ();
	context.getDialogManager().editItem (canvas,
					     item,
					     context.getUserMode(),
					     Locale.getDefault ());
      } catch (Exception exc) {
	Trace.exception (exc);
      }
    }
  }

  public void dispose()
  {
    if (context != null)
      context.removeTwConnectionListener(this);
  }
  
  void setTwConnectionListener(WorkspaceView view)
  throws G2AccessException {
    TwAccess newContext = null;
    ImplAccess workspace = (ImplAccess)view.getWorkspace();
    if (workspace != null) 
      newContext = (TwAccess)workspace.getContext();
    if (context != null && (newContext != null) && (newContext.equals(context))) 
      return;
    else if (context != null) 
      context.removeTwConnectionListener(this);
    
    context = newContext;
    if (context != null) {
      //the body of this if is not thread safe; see rpenny
      context.addTwConnectionListener(this);
      Symbol state = context.getG2State();
      //if we recieve an event between the previous statement
      // and the next one, then we will be in an out of date state.
      if (RUNNING_.equals(state)) {
	setG2IsRunning(true);
      } else {
	setG2IsRunning(false);
      }
    } else {
      setG2IsRunning(false);
      return;
    }
  }
    
  synchronized void listenTwConnection(WorkspaceView view) {
    try {
      setTwConnectionListener(view);
    } catch (G2AccessException g2ae) {
      throw new UnexpectedException(g2ae);
    }
  }

  @Override
  public void loggedIn (TwConnectionEvent evt)
  {
  }

  @Override
  public void loggedOut (TwConnectionEvent evt)
  {
  }

  @Override
  public void userModeChanged (TwConnectionEvent evt)
  {
  }

  @Override
  public synchronized void g2IsPaused(G2ConnectionEvent event){
    setG2IsRunning(false);
  };
  @Override
  public synchronized void g2IsResumed(G2ConnectionEvent event){
    setG2IsRunning(true);
  };
  @Override
  public synchronized void g2IsReset(G2ConnectionEvent event){
    setG2IsRunning(false);
  };
  @Override
  public synchronized void g2IsStarted(G2ConnectionEvent event){
    setG2IsRunning(true);
  };
  @Override
  public synchronized void g2ConnectionClosed(G2ConnectionEvent event){
  }; 
  @Override
  public synchronized void g2ConnectionInitialized(G2ConnectionEvent event){
  };
  @Override
  public synchronized void g2MessageReceived(G2ConnectionEvent event){
  };
  @Override
  public synchronized void communicationError(G2CommunicationErrorEvent error_event){
  };
  @Override
  public synchronized void readBlockage(G2ConnectionEvent event){
  };
  @Override
  public synchronized void writeBlockage(G2ConnectionEvent event){
  };

  @Override
  public String toString() {
    return "aDefaultWorkspaceViewEventHandler";
  }

  @Override
  public void registerListeners (PersistentCanvas c) {
    super.registerListeners(c);
    listenTwConnection((WorkspaceView)c);
  }
  
}


class MenuPosterThread extends Thread {

  Item item;
  WorkspaceView wksp;
  MouseEvent e;
  
  MenuPosterThread () {
    super("Menu-Poster-Thread");
  }

  
  public synchronized void post(WorkspaceView wksp, Item item, MouseEvent e) {
    this.wksp = wksp;
    this.item = item;
    this.e = e;
    notify();
  }
  
  @Override
  public synchronized void run() {
    while (true) {
      try {
	if (wksp != null)
	  wksp.getSelectionCommandGenerator().postContextMenu (wksp, item, e);
      } catch (Exception e) {
	Trace.exception (e, "Error while posting context menu :");
      }
      try {
	wait();
      } catch (InterruptedException ie) {
	Trace.exception(ie);
      }
    }
  }
}
