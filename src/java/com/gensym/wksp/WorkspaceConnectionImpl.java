package com.gensym.wksp;

import java.awt.*;
import com.gensym.irm.*;
import com.gensym.ntw.*;
import com.gensym.util.*;
import com.gensym.message.*;
import com.gensym.ntw.util.CrossSectionPattern;
import java.util.*;
import com.gensym.draw.*;
import com.gensym.classes.Connection;
import com.gensym.jgi.G2AccessException;
import com.gensym.classes.Item;
import com.gensym.classes.Entity;


/**
 *
 * WorkspaceConnection <p>
 * A WorkspaceElement that appears as a connection
 */
public class WorkspaceConnectionImpl extends ConnectionElement
implements WorkspaceConnection
{
  private Integer stubLength;
  private WorkspaceElementHelper helper;
  private Structure logicalColorMap;
  static int fuzzFactor = 3;

  /**
   * @param item The g2 item which this element is to represent.
   * @param parent The view into which this element is being added. 
   * @return an initialized WorkspaceElement.
   * @see initialize
   */
  public WorkspaceConnectionImpl(Connection connection, WorkspaceView parent)
       throws G2AccessException
  {      
    this(new CrossSectionPattern(connection.getCrossSectionPatternForClass()),
	 (PersistentCanvas) parent,
	 connection,
	 WorkspaceUtil.convertVerticesSequenceToPointArray
	 (connection.getConnectionPositionSequence()));
    this.helper = new WorkspaceElementHelper(this,
					     this,
					     this,
					     (Item)connection,
					     parent);
  }

  private WorkspaceConnectionImpl(CrossSectionPattern csp,
				  PersistentCanvas canvas,
				  Connection connection,
				  Point[] vertices)
       throws G2AccessException
  {
    super(vertices,
	  csp.getWidths(), csp.getRegions(),
	  csp.getLogicalColors(), csp.getColors(null,canvas.getColorTable()),
	  convertStyle(connection.getConnectionStyleSnapshot()));
    boolean directed = false;
    try {
      directed = connection.getConnectionIsDirected();
    } catch (NullPointerException npe) {
      //g2's prior to 51r1 don't support this attribute
      Trace.exception(npe);
    }
    setDirected(directed);
    Structure colorOverrides = ((Entity)connection).getItemColorPattern();
    logicalColorMap = csp.getColorMap();
    setCanvas(canvas);
    updateColorPattern(colorOverrides);
  }

  private static int convertStyle(Symbol style)
  {
    if (ORTHOGONAL_.equals(style))
      return ConnectionElement.ORTHOGONAL;
    else if (DIAGONAL_.equals(style))
      return ConnectionElement.DIAGONAL;
    else
      return -1;
  }
  
  private void updateColorPattern(Structure colorPatternChange) {
    if (colorPatternChange != null) {
      Enumeration newColorNames = colorPatternChange.getAttributeNames();
      Symbol nextColor;
      Object nextColorValue;
      while (newColorNames.hasMoreElements()) {
	nextColor = (Symbol) newColorNames.nextElement();
	nextColorValue = colorPatternChange.getAttributeValue(nextColor, null);
	logicalColorMap.setAttributeValue(nextColor,nextColorValue);
      }
      int length = logicalColorMap.getAttributeCount();
      Object[] logicalColors = new Object[length];
      Color[] colors = new Color[length];
      Enumeration names=logicalColorMap.getAttributeNames();
      int i = 0;
      while (names.hasMoreElements()) {
	Symbol name = (Symbol)names.nextElement();
	logicalColors[i] = name;
	Symbol logicalColorValue =(Symbol)logicalColorMap.getAttributeValue(name, null);
	colors[i] = (Color) canvas.getColorTable().lookup(logicalColorValue);
	i++;
      }
      setLogicalColorMap(logicalColors, colors);
    }
    canvas.invalidateElement(this);
  }

  /*WORKSPACE ELEMENT API*/
  
  @Override
  public void handleWorkspaceItemColorsChanged(WorkspaceEvent event) {
    Structure updateInfo = event.getInfo();
    Structure colorPatternChange
	= (Structure) updateInfo.getAttributeValue(COLOR_PATTERN_CHANGES_, null);
    updateColorPattern(colorPatternChange);
  }
  
  @Override
  public void handleWorkspaceItemMoved(WorkspaceEvent event) {
    Structure extraInfo = event.getInfo();
    Sequence newVerticesSequence
      = (Sequence) extraInfo.getAttributeValue
      (TW_WORKSPACE_ITEM_POSITION_, null);
    Point[] newVertices
      = WorkspaceUtil.convertVerticesSequenceToPointArray(newVerticesSequence);
    Rectangle[] currentBounds = getExactBounds();
    int length = currentBounds.length;
    Rectangle[] oldBounds = new Rectangle[length];
    for (int i = 0; i < length; i++) 
      oldBounds[i] = new Rectangle(currentBounds[i]);
    setVertices(newVertices);
    ((PersistentCanvas)getParent()).invalidate(oldBounds);
    ((PersistentCanvas)getParent()).invalidateElement(this);
  }

  /**
   * Resizes the DrawElement to the given Rectangle.
   */
  @Override
  public void handleWorkspaceItemResized(WorkspaceEvent event) {
    helper.resize(event);
  }

  @Override
  public void receivedInitialValues (ItemEvent e) {
    helper.receivedInitialValues(e);
  }

  @Override
  public void itemModified (ItemEvent e) {
    helper.itemModified(e);
  }
  
  /**
   * Invoked when the connection's style has changed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of <code>ITEM_CHANGE</code>.<p>
   * The event's info will contain a structure whose attribute named by
   * <code>WorkspaceElement.ATTRIBUTE_NAME_</code> will be <code>CONNECTION_STYLE_</code> and whose
   * attribute named by <code>WorkspaceElement.NEW_VALUE_</code> will be either
   * <code>ORTHOGONAL_</code>, <code>DIAGONAL_</code>, or <code>null</code>.
   */
  @Override
  public void handleConnectionStyleChanged(WorkspaceEvent event)
  {
    Structure info = event.getInfo();
    setStyle(convertStyle((Symbol) info.getAttributeValue(NEW_VALUE_, null)));
  }

  /**
   * Invoked when the connection become directed or is no longer directed.
   * @param <code>event</code> a <code>WorkspaceEvent</code> with ID of <code>ITEM_CHANGE</code>.<p>
   * The event's info will contain a structure whose attribute named by
   * <code>WorkspaceElement.ATTRIBUTE_NAME_</code> will be <code>CONNECTION_IS_DIRECTED_</code> and whose
   * attribute named by <code>WorkspaceElement.NEW_VALUE_</code> will be a
   * a boolean indicating whether or not the connection is directed or not.
   */
  @Override
  public void handleConnectionIsDirectedChanged(WorkspaceEvent event)
  {
    Structure info = event.getInfo();
    boolean directed
      = ((Boolean) info.getAttributeValue(NEW_VALUE_, null)).booleanValue();
    setDirected(directed);
  }
  
  @Override
  public void itemDeleted (ItemEvent e) {
    helper.itemDeleted(e);
  }

  @Override
  public Item getItem() {
    return helper.getItem();
  }

  @Override
  public void select () {
    helper.select();
  }

  @Override
  public void unselect () {
    helper.unselect();
  }

  @Override
  public boolean isSelected () {
    return helper.isSelected();
  }
  
  @Override
  public DraggingGhost getDraggingGhost (int left, int top, int width, int height) {
    return getDraggingGhost();
  }

  private Point[] flipVertices(Point[] vertices) {
    int length = vertices.length;
    Point[] flipped = new Point[length];
    for (int i=0; i<length;i++) {
      flipped[i] = vertices[length-(i+1)];
    }
    return flipped;
  }
  
  @Override
  public DraggingGhost getDraggingGhost () {
    ConnectionDraggingGhost ghost = new ConnectionDraggingGhost ();
    ghost.elements = new Component[1];
    ConnectionElement ghostConnection = (ConnectionElement)copy();
    Object inputEnd = getInputEndObject();
    boolean inputIsLooseEnd = (inputEnd instanceof Boolean);
    if (inputIsLooseEnd) 
      ghostConnection.setVertices(flipVertices(ghostConnection.getVertices()));
    ghost.elements[0] = ghostConnection;

    Point[] vertices = ghostConnection.getVertices();
    Point firstPoint = vertices[0];
    Point secondPoint = vertices[1];
    ghost.firstSegmentIsHorizontal = (firstPoint.y==secondPoint.y);
    ghostConnection.setPaintMode(false);
    ghost.boundsArray = ghostConnection.getExactBounds();
    return ghost;
  }
  
  @Override
  public DraggingGhost getDraggingGhost (int markerLocn, int currentX, int currentY) {
    return getDraggingGhost();
  }

  @Override
  public PopupMenu getContextMenu () {
    return helper.getContextMenu();
  }

  
  /*Workspace Connection API*/
  
  /**
   *@return true iff the Connection for this WorkspaceConnection
   * is a loose end.
   */
  @Override
  public boolean isLooseEnd() {
    boolean isLooseEnd = false;
    Item item = getItem();
    try {
      Sequence ends = ((Connection)item).getConnectionInputAndOutput();
      Object input = ends.elementAt(0);
      Object output = ends.elementAt(1);
      if ((input instanceof Boolean) || (output instanceof Boolean))
	isLooseEnd = true;
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
    }
    return isLooseEnd;
  }
  
  private Object getInputEndObject()
  {
    Item item = getItem();
    try {
      Sequence ends = ((Connection)item).getConnectionInputAndOutput();
      return ends.elementAt(0);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      return null;
    }
  }
  
  private Object getOutputEndObject()
  {
    Item item = getItem();
    try {
      Sequence ends = ((Connection)item).getConnectionInputAndOutput();
      return ends.elementAt(1);
    } catch (G2AccessException g2ae) {
      Trace.exception(g2ae);
      return null;
    }
  }

  private int getOppositeHeading(int heading)
  {
    switch (heading)
      {
      case Segment.LEFT:
	return Segment.RIGHT;
      case Segment.TOP:
	return Segment.BOTTOM;
      case Segment.RIGHT:
	return Segment.LEFT;
      case Segment.BOTTOM:
	return Segment.TOP;
      default:
	return -1;
      }
  }
  
  /**
   *@return true iff the the Point (x,y) is within a loose end
   * of this connection. (Calls isLooseEnd).
   */
  @Override
  public boolean insideLooseEnd(int x, int y) {
    Rectangle[] bounds = getExactBounds();
    Object inputEnd = getInputEndObject();
    Object outputEnd = getOutputEndObject(); 
    boolean inputIsLooseEnd = (inputEnd instanceof Boolean);
    boolean outputIsLooseEnd = (outputEnd instanceof Boolean);
    if (inputIsLooseEnd || outputIsLooseEnd ) {
      int endSegmentIndex = bounds.length-1;
      if (inputIsLooseEnd) {
	endSegmentIndex = 0;
      }
      Rectangle endSegmentBounds = bounds[endSegmentIndex];
      int left = endSegmentBounds.x, top = endSegmentBounds.y;
      int width = endSegmentBounds.width, height = endSegmentBounds.height;
      int heading = segments[endSegmentIndex].getHeading();
      if (inputIsLooseEnd)
	heading = getOppositeHeading(heading);
      Rectangle looseEndBounds = new Rectangle(left, top, width, height);
      int bufferSize = 7;
      switch (heading)
	{
	case Segment.LEFT:
	  looseEndBounds.width = bufferSize;
	  break;
	case Segment.TOP:
	  looseEndBounds.height = bufferSize;
	  break;
	case Segment.RIGHT:
	  int xDiff = width - bufferSize;
	  looseEndBounds.x += xDiff; looseEndBounds.width-=xDiff;
	  break;
	case Segment.BOTTOM:
	  int yDiff = height - bufferSize;
	  looseEndBounds.y += yDiff; looseEndBounds.height-=yDiff;
	  break;
	}
      looseEndBounds.x -= fuzzFactor;
      looseEndBounds.y -= fuzzFactor;
      looseEndBounds.width +=2*fuzzFactor;
      looseEndBounds.height +=2*fuzzFactor;
	
      return (looseEndBounds.contains(x,y));
    } else
      return false;
  }

  @Override
  public boolean isCut () {
    return helper.isCut ();
  }

  @Override
  public void setCut (boolean newCutState) {
    helper.setCut (newCutState);
    repaint ();
  }

  // Connections cannot be cut so paint is just super.paint

  @Override
  public void dispose() throws G2AccessException{
  }
}
  
