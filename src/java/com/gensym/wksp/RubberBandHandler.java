package com.gensym.wksp;

import java.util.Locale;
import java.awt.*;
import java.awt.event.*;
import com.gensym.classes.Item;
import com.gensym.classes.ActionButton;
import com.gensym.classes.CheckBox;
import com.gensym.classes.RadioButton;
import com.gensym.classes.KbWorkspaceImpl;
import com.gensym.draw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.jgi.G2AccessException;
import com.gensym.ntw.TwAccess;
import com.gensym.jgi.G2ConnectionListener;
import com.gensym.jgi.G2ConnectionEvent;
import com.gensym.jgi.G2CommunicationErrorEvent;

public class RubberBandHandler extends EventHandler
implements WorkspaceRepresentationTypes, G2ConnectionListener,
java.io.Serializable {

  private transient boolean canvasHasFocus = false;
  private transient SliderInput sliderInput;
  private transient LineElement[] band = new LineElement[4];
  private transient int startX, startY, currentX, currentY;
  private transient int connectionLastX, connectionLastY,
    connectionCurrentX, connectionCurrentY;
  private transient WorkspaceConnection currentConnection;
  private transient boolean isLasso, isDrag, isButtonPress, isResizing, isConnectionDrag;
  private transient boolean isSliderDrag = false;
  private transient boolean allowHorizontalChange, allowVerticalChange;
  private transient MarkerElement resizingHandle;
  private transient long prevWhen;
  protected static int DBLCLICK_INTERVAL = 250;
  private transient int scratchArrayLength = 50;
  private transient WorkspaceElement[] scratchWkspArray = new WorkspaceElement[scratchArrayLength];
  private static final boolean debugEvts = false;
  private transient Object origItm, prevItm;
  public static final Symbol JOINING_LOOSE_ENDS_ = Symbol.intern ("JOINING-LOOSE-ENDS");
  public static final Symbol MAKING_NEW_JUNCTION_BLOCK_ = Symbol.intern ("MAKING-NEW-JUNCTION-BLOCK");
  public static final Symbol DRAGGING_LOOSE_END_INTO_ITEM_ = Symbol.intern ("DRAGGING-LOOSE-END-INTO-ITEM");
  public static final Symbol MOVING_LOOSE_END_ = Symbol.intern ("MOVING-LOOSE-END");

  private static final Symbol RUNNING_ = Symbol.intern ("RUNNING");
  private transient volatile boolean g2StateIsKnown = false;
  private transient boolean g2IsRunning = false;
  private transient FocusListener focalComponent = null;

  public RubberBandHandler () {
    listenerTypes = MOUSELISTENER | MOUSEMOTIONLISTENER | KEYLISTENER | FOCUSLISTENER;
  }

  @Override
  public void mouseMoved(MouseEvent e) {
    if (isConnectionDrag)
      doConnectionDragDrag(e);
  }

  @Override
  public void mouseEntered (MouseEvent e) {}
  @Override
  public void mouseExited (MouseEvent e) {}

  @Override
  public void mousePressed (MouseEvent e) {
   try {
    startX = e.getX ();
    startY = e.getY ();
    if (debugEvts)
      System.out.println ("isMetaDown? = " + e.isMetaDown ());
    if (e.isMetaDown ()) {
      postContextMenu (e);
      return;
    }
    if (debugEvts)
      System.out.println ("MouseDown : clickCount = " + e.getClickCount ());
    if (debugEvts)
      System.out.println ("MouseDown at (" + startX + ", " + startY + ")");
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    WorkspaceView view = (WorkspaceView)canvas;
    Component d = canvas.findElement (startX, startY);
    if (debugEvts)
      System.out.println ("MouseDown on " + d);
    if (isConnectionDrag) {
      int newX = e.getX(), newY = e.getY();
      int dX = newX - connectionLastX, dY = newY - connectionLastY;
      int distance=(int)Math.sqrt(dX*dX+dY*dY);
      connectionLastX = connectionCurrentX; connectionLastY = connectionCurrentY;
      connectionCurrentX = newX; connectionCurrentY = newY;
      java.util.Vector ghosts = view.getGhosts();
      ConnectionDraggingGhost ghost = (ConnectionDraggingGhost)ghosts.elementAt(0);
      ConnectionElement connectionElement = ghost.getConnectionElement();
      boolean clickedOnDraggedConnection
	= ((d == connectionElement) || (d == currentConnection));
      if (clickedOnDraggedConnection) {
	Sequence exemptElements = new Sequence();
	exemptElements.addElement(connectionElement);
	exemptElements.addElement(currentConnection);
	d = canvas.findElement(startX, startY, exemptElements);
      }
      if (d == null || d == canvas) {
	Point[] vertices = connectionElement.getVertices();      
	int length = vertices.length;
	Point endPoint = vertices[length-1];
	Point prevPoint = vertices[length-2];
	boolean clickedOnBend = pointsAreClose(endPoint, prevPoint);
	if (distance > 0 && !clickedOnBend) {
	  putKinkInConnectionGhost(ghost,(WorkspaceView)canvas);	  
	} else {
	  if (handleLooseEndPress(connectionElement,
				  null,
				  e,
				  clickedOnBend,
				  view)) {
	    isConnectionDrag = false;
	    currentConnection = null;
	    view.removeGhosts();
	    view.clearSelection();
	  }
	}
      } else if ((d instanceof WorkspaceElement)) {	
	if (handleLooseEndPress(connectionElement,
				(WorkspaceElement)d,
				e,
				false,
				view)) {
	  isConnectionDrag = false;
	  currentConnection = null;
	  view.removeGhosts();
	  view.clearSelection();
	}
	else
	  putKinkInConnectionGhost(ghost,(WorkspaceView)canvas);	  
      }
    }    
    else if (d == null || d == canvas ) 
      doLassoPress (e);
    else if (d instanceof WorkspaceElement) {
      WorkspaceElement w = (WorkspaceElement)d;
      if (debugEvts)
	System.out.println ("MouseDown on Wksp Representation Type = " +
			    w.getItem().getRepresentationType());      
      if ((w instanceof WorkspaceButton) && g2IsRunning((WorkspaceView)canvas))
	doButtonPress (e);
      else if ((w instanceof ConnectionElement)) {
	  int x=e.getX(), y=e.getY();
	  Rectangle viewBounds = canvas.getViewBounds();
	  x+=viewBounds.x;y+=viewBounds.y;
	  if (w.isSelected ()) {
	    if (e.isShiftDown ()) {
	      view.removeElementFromSelection (w);
	      return;
	    }
	  } else if (((WorkspaceConnection)w).insideLooseEnd(x, y))
	    {
	      view.clearSelection ();
	      view.addElementToSelection (w);//maybe remove this
	      currentConnection = (WorkspaceConnection)w;
	      isConnectionDrag = true;
	      doConnectionDragPress(e);
	    }
	  /*else {
	    if (!e.isShiftDown ())
	    view.clearSelection ();
	    view.addElementToSelection (w);
	  }*/
      }
      else {
	if (w.isSelected ()) {
	  if (e.isShiftDown ()) {
	    view.removeElementFromSelection (w);
	    return;
	  }
	  doDragPress (e);
	} else {
	  if (!e.isShiftDown ())
	    view.clearSelection ();
	  view.addElementToSelection (w);
	  doDragPress (e);
	}
      }
    }
    else if (d instanceof com.gensym.wksp.MarkerElement) {
      // Logic for markers
      if (debugEvts)
	System.out.println ("\n\n Mouse Down on Marker. Start RESIZING...\n\n");
      doResizePress (e, (MarkerElement)d);
    } else if (d instanceof SliderInput) {
      doSliderPress (e, (SliderInput)d);
    } 
   } catch (G2AccessException g2ae) { System.out.println(g2ae);}

  }


  @Override
  public void mouseDragged (MouseEvent e) {
    if (isLasso)
      doLassoDrag (e);
    else if (isDrag)
      doDragDrag (e);
    else if (isConnectionDrag)
      doConnectionDragDrag(e);
    else if (isButtonPress)
      doButtonDrag (e);
    else if (isResizing)
      doResizeDrag (e);
    else if (isSliderDrag)
      doSliderDrag (e);
  }

  @Override
  public void mouseReleased (MouseEvent e) {
    if (isLasso)
      doLassoRelease (e);
    else if (isDrag)
      doDragRelease (e);
    else if (isConnectionDrag)
      doConnectionDragRelease(e);
    else if (isButtonPress)
      doButtonRelease (e);
    else if (isResizing)
      doResizeRelease (e);
    else if (isSliderDrag)
      doSliderRelease (e);
  }

  @Override
  public void keyPressed(KeyEvent e)
  {
    int inc = 10;
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    switch (e.getKeyCode()) {
    case KeyEvent.VK_DOWN:
      canvas.scrollView(inc, false); break;
    case KeyEvent.VK_UP:
      canvas.scrollView(-inc, false); break;
    case KeyEvent.VK_LEFT:
      canvas.scrollView(-inc, true); break;
    case KeyEvent.VK_RIGHT:
      canvas.scrollView(inc, true); break;
    }
  }

  @Override
  public void keyReleased(KeyEvent e)
  {
  }
    
  void postContextMenu (MouseEvent e) {
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    Component d = canvas.findElement (startX, startY);
    WorkspaceView wksp = (WorkspaceView)canvas;
    Item item;
    if (d == null || !(d instanceof WorkspaceElement)) {
      if (d == null) {
	return;//item = wksp.getWorkspace();
      } else
	return;
    } else {
      WorkspaceElement wElt = (WorkspaceElement)d;
      item = wElt.getItem();
      if (debugEvts)
	System.out.println ("Element is already selected = " + wElt.isSelected ());
      if (!wElt.isSelected ()) {
	wksp.clearSelection ();
	wksp.addElementToSelection (wElt);
      }
    }
    wksp.getSelectionCommandGenerator().postContextMenu (wksp, item, e);
  }

  private void doSliderPress (MouseEvent e, SliderInput sliderInput) {
    currentX = startX; currentY = startY;
    isSliderDrag = true;
    this.sliderInput = sliderInput;
    sliderInput.getSlider().setDragging(true);
  }
  
  private void doResizePress (MouseEvent e, MarkerElement marker) {
    Rectangle bnds = null;
    isResizing = true;
    WorkspaceView wksp    = (WorkspaceView) ((PersistentCanvas)e.getSource());
    int numSelected       = wksp.getSelection().length;
    resizingHandle        = marker;
    if (numSelected != 1)
      return;
    allowHorizontalChange = marker.isHorizontallyExtensible ();
    allowVerticalChange   = marker.isVerticallyExtensible ();
    WorkspaceElement elt  = wksp.getWorkspaceElementFromMarker (marker);
    bnds = ((DrawElement)elt).getExactBounds()[0];
    currentX = startX; currentY = startY;
    startX = bnds.x; startY = bnds.y;
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

  private void doSliderDrag (MouseEvent e) {
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    int prevX = currentX; currentX = e.getX();
    WorkspaceSliderImpl slider = sliderInput.getSlider();
    Rectangle vBounds = canvas.getViewBounds();
    Rectangle bounds = slider.getBounds();
    bounds.translate(-vBounds.x,-vBounds.y);
    if (currentX >= bounds.x && currentX <= bounds.x+bounds.width)
      slider.doInputShift(currentX - prevX);
  }
    
  private void doResizeDrag (MouseEvent e) {
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

  private void doSliderRelease (MouseEvent e) {
    isSliderDrag = false;
    try {
      sliderInput.getSlider().setSliderValueUsingCurrentLocation();
    } catch (G2AccessException g2ae) {
      System.out.println(g2ae);
    }
    sliderInput.getSlider().setDragging(false);
    sliderInput = null;
  }

  private void doResizeRelease (MouseEvent e) {
    isResizing = false;
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    WorkspaceView view = (WorkspaceView)canvas;
    Rectangle vb = canvas.getViewBounds ();
    view.removeGhosts ();
    if (debugEvts) {
      System.out.println ("\n Resized corner from (" + startX + ", " + startY + ") to (" + currentX + ", " + currentY + ")");
      System.out.println ("Element is (" + startX + ", " + startY + ") -> (" + (currentX + vb.x) + ", " + (currentY + vb.y) + ")");
    }
    Rectangle newBounds = 
      view.getResizingBounds (resizingHandle, currentX + vb.x, currentY + vb.y);
    view.resizeSelection (newBounds.x, newBounds.y,
			  newBounds.x + newBounds.width, newBounds.y + newBounds.height);
  }

  private void doButtonPress (MouseEvent e) {
    isButtonPress = true;
    Component d = ((PersistentCanvas)e.getSource ()).findElement (startX, startY);
    WorkspaceButtonImpl actnBtn = (WorkspaceButtonImpl)d;
    prevItm = origItm = actnBtn;
    actnBtn.setArmed(true);
  }

  private void doButtonDrag (MouseEvent e) {
    int currentX = e.getX (), currentY = e.getY ();
    Component d = ((PersistentCanvas)e.getSource ()).findElement (currentX, currentY);
    if (!(d instanceof WorkspaceButtonImpl)) {
      if (prevItm == origItm) {
	((WorkspaceButtonImpl)origItm).setArmed(false);
	prevItm = d;
      }
      return;
    }
    WorkspaceButtonImpl actnBtn = (WorkspaceButtonImpl)d;
    if (prevItm == actnBtn)
      return;
    prevItm = actnBtn;
    // Inside a new action button, original or otherwise
    if ((origItm != actnBtn))
      ((WorkspaceButtonImpl)origItm).setArmed(false);
    else
      actnBtn.setArmed(true);
  }

  private void doButtonRelease (MouseEvent e) {
    int currentX = e.getX (), currentY = e.getY ();
    PersistentCanvas canvas = (PersistentCanvas)e.getSource();
    Component d = canvas.findElement (currentX, currentY);
    if (!(d instanceof WorkspaceButtonImpl))
      return;
    WorkspaceButtonImpl btn = (WorkspaceButtonImpl)d;
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
	((WorkspaceTypeInBoxImpl)d).setEditing(true);
	//focalComponent = (FocusListener)d;
      }
    } catch (G2AccessException g2ae) {
      // fix this: should at least send a message to the user
      // Also don't know if isButtonPress should still be set to false
      // - rpenny
      g2ae.printStackTrace();
    }
    isButtonPress = false;
  }
  
  @Override
  public void focusGained(FocusEvent e)
  {
    if (focalComponent != null)
      focalComponent.focusGained(e);
  }
  
  @Override
  public void focusLost(FocusEvent e)
  {
    if (focalComponent != null)
      focalComponent.focusLost(e);
  }
  
  private void doDragPress (MouseEvent e) {
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    WorkspaceView view = (WorkspaceView)canvas;
    isDrag = true;
    currentX = startX;
    currentY = startY;
    view.addGhosts ();
  }
  
  private void doDragDrag (MouseEvent e) {
    int newX = e.getX ();
    int newY = e.getY ();
    if ((newX == currentX) && (newY == currentY))
      return;
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    WorkspaceView view = (WorkspaceView)canvas;
    view.moveGhosts (newX - currentX, newY - currentY);
    currentX = newX; currentY = newY;    
  }

  private void doDragRelease (MouseEvent e) {
    int endX = e.getX ();
    int endY = e.getY ();
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    WorkspaceView view = (WorkspaceView)canvas;
    view.moveSelection(endX-startX, endY-startY);
    view.removeGhosts ();
    Rectangle viewBounds = canvas.getViewBounds();
    isDrag = false;
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
  
  private boolean handleLooseEndPress(ConnectionElement ce,
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
      } catch (G2AccessException g2ae) {System.out.println(g2ae);}
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
  
  private void doConnectionDragPress(MouseEvent e) {
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();    
    WorkspaceView view = (WorkspaceView)canvas;
    connectionLastX = connectionCurrentX; connectionLastY = connectionCurrentY;
    connectionCurrentX = e.getX(); connectionCurrentY = e.getY();
    view.addGhosts ();
  }

  private void doConnectionDragDrag (MouseEvent e) {
    int newX = e.getX ();
    int newY = e.getY ();
    if ((newX == connectionCurrentX) && (newY == connectionCurrentY))
      return;
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    WorkspaceView view = (WorkspaceView)canvas;
    view.moveGhosts (newX - connectionCurrentX, newY - connectionCurrentY);
    connectionLastX = connectionCurrentX; connectionLastY = connectionCurrentY;
    connectionCurrentX = newX; connectionCurrentY = newY;    
  }

  private void doConnectionDragRelease (MouseEvent e) {
    //int endX = e.getX ();
    //int endY = e.getY ();
    //PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    //    WorkspaceView view = (WorkspaceView)canvas;
    //view.moveSelection (endX - startX, endY - startY);
    //view.removeGhosts ();
    //isConnectionDrag = false;//only if not double click
  }
  
  private void doLassoPress (MouseEvent e) {
    isLasso = true;
    if (e.isShiftDown ())
      return;
    PersistentCanvas canvas = (PersistentCanvas)e.getSource ();
    WorkspaceView view = (WorkspaceView)canvas;
    view.clearSelection ();
  }

  public void doLassoDrag (MouseEvent e) {
    
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
    if (false)
      System.out.println ("rb from (" + (startX+deltaX)
			  + ", " + (startY+deltaY)
			  + ") to (" + (currentX+deltaX)
			  + ", " + (currentY+deltaY) + ")");

    canvas.addElement (band[0] = new LineElement (Color.red,
						  startX + deltaX, startY + deltaY,
						  currentX + deltaX, startY + deltaY));
    canvas.addElement (band[1] = new LineElement (Color.red,
						  currentX + deltaX, startY + deltaY,
						  currentX + deltaX, currentY + deltaY));
    canvas.addElement (band[2] = new LineElement (Color.red,
						  currentX + deltaX, currentY + deltaY,
						  startX + deltaX, currentY + deltaY));
    canvas.addElement (band[3] = new LineElement (Color.red,
						  startX + deltaX, currentY + deltaY,
						  startX + deltaX, startY + deltaY));
    canvas.invalidateElement (band[0]);
    canvas.invalidateElement (band[1]);
    canvas.invalidateElement (band[2]);
    canvas.invalidateElement (band[3]);
  }

  public void doLassoRelease (MouseEvent e) {
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    int endX = e.getX ();
    int endY = e.getY ();
    Rectangle viewBounds = canvas.getViewBounds ();
    int dX = viewBounds.x; // (pbk notes that canvas needs consistent coordinate
    int dY = viewBounds.y; //  system in its API)
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
    if (endX < startX) {
      temp = endX; endX = startX; startX = temp;}
    if (endY < startY) {
      temp = endY; endY = startY; startY = temp;}
    Component[] selectedElements = canvas.findElements (new Rectangle (startX + dX, startY + dY,
									 endX - startX, endY - startY));
    WorkspaceElement[] wkspElements = filterElements (selectedElements);
    //fireEvent (SELECT, DrawElements);
    WorkspaceView view = (WorkspaceView)canvas;
    view.addElementsToSelection (wkspElements);
    isLasso = false;
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

  @Override
  public void mouseClicked (MouseEvent e) {
    startX = e.getX ();
    startY = e.getY ();
    PersistentCanvas canvas = (PersistentCanvas) e.getSource ();
    Component thing = canvas.findElement (startX, startY);
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
      if (thing instanceof WorkspaceConnection) {
	isConnectionDrag = false;
	currentConnection = null;
	view.removeGhosts();
	view.clearSelection();
      }
      if (! ((thing instanceof WorkspaceIcon) && 
            (canvas instanceof WorkspaceView)))
        return;
      if (thing instanceof WorkspaceButton
	  && g2IsRunning((WorkspaceView)canvas))
	return;
      prevWhen = e.getWhen();
      try {
	Item item = ((WorkspaceElement)thing).getItem();
	TwAccess context = (TwAccess) ((com.gensym.classes.ImplAccess)item).getContext ();
	context.getDialogManager().editItem (item,
					     ADMINISTRATOR_,
					     Locale.getDefault ());
      } catch (Exception exc) {
	// System.out.println ("Double-click:  edited object is " + thing);
	/*WkspCommandEvent editEvent = new WkspCommandEvent (view,
	  WkspCommandEvent.EDIT_PROPERTIES,
	  view.getSelection ());
	  view.commandPerformed(editEvent);*/
	Trace.exception (exc);
      }

    }
  }

  private static final Symbol ADMINISTRATOR_ = Symbol.intern ("ADMINISTRATOR");
  //public void fireEvent (CommandEvent evt) {}

  void setG2StateListener(WorkspaceView view)
  throws G2AccessException {
    if (g2StateIsKnown)
      return;

    KbWorkspaceImpl workspace = (KbWorkspaceImpl)view.getWorkspace();
    TwAccess context = (TwAccess)workspace.getContext();

    context.addG2ConnectionListener(this);

    synchronized (this) {
      if (g2StateIsKnown)
	return;

      Symbol state = context.getG2State();
      if (RUNNING_.equals(state)) {
	g2IsRunning = true;
      } else {
	g2IsRunning = false;
      }
      g2StateIsKnown = true;
    }
  }
    
  synchronized boolean g2IsRunning(WorkspaceView view) {
    if (!g2StateIsKnown) {
      try {
	setG2StateListener(view);
      } catch (G2AccessException g2ae) {
	throw new UnexpectedException(g2ae);
      }
    }

    return g2IsRunning;
  }
    
  @Override
  public synchronized void g2IsPaused(G2ConnectionEvent event){
    g2StateIsKnown = true;
    g2IsRunning = false;
  };
  @Override
  public synchronized void g2IsResumed(G2ConnectionEvent event){
    g2StateIsKnown = true;
    g2IsRunning = true;
  };
  @Override
  public synchronized void g2IsReset(G2ConnectionEvent event){
    g2StateIsKnown = true;
    g2IsRunning = false;
  };
  @Override
  public synchronized void g2IsStarted(G2ConnectionEvent event){
    g2StateIsKnown = true;
    g2IsRunning = true;
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
}
