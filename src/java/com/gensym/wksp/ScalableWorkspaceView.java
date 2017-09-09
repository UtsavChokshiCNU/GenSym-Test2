/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 ScalableWorkspaceView.java
 *
 */
package com.gensym.wksp;

import java.awt.Component;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Point;
import java.awt.Dimension;
import java.awt.PopupMenu;
import java.awt.Rectangle;
import java.awt.event.MouseEvent;
import java.awt.geom.AffineTransform;
import java.awt.geom.NoninvertibleTransformException;
import java.awt.print.Printable;
import java.awt.print.Pageable;
import java.awt.print.PrinterException;
import java.awt.print.PageFormat;
import java.util.Vector;
import java.util.Enumeration;
import javax.swing.JViewport;
import com.gensym.classes.KbWorkspace;
import com.gensym.draw.ViewScrollState;
import com.gensym.jgi.G2AccessException;
import com.gensym.message.Trace;
import com.gensym.util.Sequence;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import java.awt.RenderingHints;

/**
 * A ScalableWorkspaceView supports arbitrary scaling of the view in the x- and y-axis directions.
 * This class is only supported with JDK1.2.
 * @since Telewindows2 Toolkit 1.1 rev. 0
 */

public class ScalableWorkspaceView extends WorkspaceView implements Printable, Pageable{

  private AffineTransform tx;
  private boolean scaledToFit = false;
  private Vector listeners = new Vector();

  public ScalableWorkspaceView(KbWorkspace wksp){
    super(wksp);
  }

  public ScalableWorkspaceView(){
    super();
  }

  @Override
  protected ViewScrollState createScrollState(boolean isHorizontal){
    return new ScalableScrollState(isHorizontal, this);
  }

  @Override
  protected void processMouseEvent (MouseEvent e){
    inverseTransformMouseEvent(e);
    super.processMouseEvent (e);
  }

  @Override
  protected void processMouseMotionEvent (MouseEvent e){
    inverseTransformMouseEvent(e);
    super.processMouseMotionEvent (e);
  }

  private final void inverseTransformMouseEvent(MouseEvent e){
   if (tx != null){
      Point location = e.getPoint();
      int originalX = location.x;
      int originalY = location.y;
      try{
	tx.inverseTransform(location, location);
	e.translatePoint(location.x - originalX,
			 location.y - originalY);
      }
      catch(NoninvertibleTransformException ex){
	Trace.exception(ex);
      }
    }
  }

  @Override
  public void paint(Graphics g) {
    if (g instanceof Graphics2D) {
      Graphics2D twoDg = (Graphics2D)g;
      twoDg.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
			     RenderingHints.VALUE_ANTIALIAS_ON);
      if (getScaleX() >= 1 || getScaleY() >= 1)
	twoDg.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING,
			       RenderingHints.VALUE_TEXT_ANTIALIAS_OFF);
      if (tx != null)
	twoDg.transform(tx);
    }
    super.paint(g);
  }

  private Point paintPoint; //this point gets created in setTransform

  @Override
  protected void paintOutOfBounds(Graphics g){
    g.setColor(getOutOfBoundsColor());
    Rectangle bounds = getBounds();
    if (tx != null){
      paintPoint.x = bounds.width;
      paintPoint.y = bounds.height;
      try{
	tx.inverseTransform(paintPoint, paintPoint);
      }
      catch(NoninvertibleTransformException ex){
	Trace.exception(ex);
      }
      g.fillRect(0, 0, paintPoint.x, paintPoint.y);
    }
    else
      g.fillRect(0, 0, bounds.width, bounds.height);
  }

  @Override
  public void repaint(){
    super.repaint(0, 0, 0, getWidth(), getHeight());
  }

  @Override
  public void repaint(long tm) {
    super.repaint(tm, 0, 0, getWidth(), getHeight());
  }

  @Override
  public void repaint (long tm, int x, int y, int width, int height) {
    if (tx != null){
      Point p1 = new Point(x, y);
      Point p2 = new Point(width, height);
      tx.transform(p1, p1);
      tx.transform(p2, p2);
      super.repaint (tm, p1.x-1, p1.y-1, p2.x+2, p2.y+2);
    }
    else
      super.repaint(tm, x, y, width, height);
  }

  /**
   * @undocumented
   * @internal
   */
  //this will be called with transformed coords
  @Override
  public void scrollViewAbsolute(int newViewMin, boolean isHorizontal){
    ScalableScrollState state
      = isHorizontal ? (ScalableScrollState)horizontal_state : (ScalableScrollState)vertical_state;
    state.shift(newViewMin - state.getTransformedScrollState().getViewMin());
    repaintCanvas();
  }

  @Override
  public void scrollToLocation(int x, int y, boolean center){
    Component parent = getParent();
    //This bug fix was related to using the shink-wrap as the image was
    //repainted incorrectly before.Had to do with the viewport size.
    //Get the size of the parent component
    Dimension comp=  parent.getSize();
    if (parent instanceof JViewport){
      JViewport viewport = (JViewport)parent;
      //Get the size of the viewport
      Dimension viewSize =viewport.getViewSize();
      if (!comp.equals(viewSize)){
         Rectangle lbnds = getLogicalBounds();
         int hlmin = horizontal_state.getLogicalMin();
         int vlmin = vertical_state.getLogicalMin();
         Point p = new Point(x - hlmin, y - vlmin);

         if (tx != null)
           tx.transform(p, p);

         Rectangle bnds = viewport.getViewRect();
         int width = bnds.width;
         int height = bnds.height;
         p.x= Math.max(0, p.x-width/2);
         p.y= Math.max(0, p.y-height/2);
         viewport.setViewPosition(p);
         //Make sure to repaint the viewport after scrolling is done
         viewport.repaint();
      }
    } else {
      scrollToLocation(x, true);
      scrollToLocation(y, false);
    }
  }

  private void scrollToLocation(int newViewMin, boolean isHorizontal){
    ScalableScrollState state
      = isHorizontal ? (ScalableScrollState)horizontal_state : (ScalableScrollState)vertical_state;
    int logicalMin = state.getLogicalMin();
    Point p = isHorizontal ? new Point(newViewMin - logicalMin, 0) : new Point(0, newViewMin - logicalMin);
    if (tx != null)
      tx.transform(p, p);
    state.shift((isHorizontal ? p.x + logicalMin : p.y +logicalMin) - state.getTransformedScrollState().getViewMin());
    repaintCanvas();
  }

  @Override
  protected void adjustBoundsForSizing(ViewScrollState state, int oldWidth, int newWidth){
    ScalableScrollState scalableState = (ScalableScrollState)state;
    //adjust the txScrollState
    super.adjustBoundsForSizing(scalableState.getTransformedScrollState(), oldWidth, newWidth);
    //then update the normal coords
    scalableState.updateViewBounds();
  }

  /**
   * Sets the scale used to render the view
   * @param sx the factor by which the width of the view is scaled
   * @param sy the factor by which the height of the view is scaled
   * @see #setScaleX
   * @see #setScaleY
   */
  public void setScale(double sx, double sy) throws NoninvertibleTransformException{
    setScaledToFit(false);
    if (tx == null || (tx != null && (sx != tx.getScaleX() || sy != tx.getScaleY()))){
      AffineTransform newTx = new AffineTransform();
      newTx.setToScale(sx, sy);
      setTransform(newTx);
    }
  }

  /**
   * Sets the x-axis scaling factor
   * @see #setScaleY
   * @see #setScale
   */
  public void setScaleX(double sx) throws NoninvertibleTransformException{
    setScale(sx, getScaleY());
  }

  /**
   * Sets the y-axis scaling factor
   * @see #setScaleX
   * @see #setScale
   */
  public void setScaleY(double sy) throws NoninvertibleTransformException{
    setScale(getScaleX(), sy);
  }

  /**
   * Returns the x-axis scaling factor
   */
  public double getScaleX(){
    if (tx == null)
      return 1.0;
    return tx.getScaleX();
  }

  /**
   * Returns the y-axis scaling factor
   */
  public double getScaleY(){
    if (tx == null)
      return 1.0;
    return tx.getScaleY();
  }

  /**
   * Turns scaled to fit on and off.  If true, the scaling factors are set to the maximum
   * while maintaining the view's aspect ratio.  Scaled to fit remains on until either it is
   * turned off or a scale is set with setScale()
   * @see #setScale
   */
  public void setScaledToFit(boolean scaledToFit){
    if (scaledToFit != this.scaledToFit){
      this.scaledToFit = scaledToFit;
      if (scaledToFit)
	scaleToFit();
    }
  }

  private void scaleToFit(){
    Dimension size = getSize();
    Rectangle logicalBounds = getLogicalBounds();
    double scale = Math.min((double)size.width/logicalBounds.width,
			    (double)size.height/logicalBounds.height);
    //This bug fix was related to scaling of the window to fit the workspace
    //running into endless loops in rethink/escor.
    double lastScale = Math.min(getScaleX(), getScaleY());
    double delta = Math.abs(lastScale - scale);
    //System.out.println("new scaleToFit: " + scale + " lastScale: " + lastScale + " delta: " + delta);
    if (delta > 0.01) {
      try{
        AffineTransform tx = new AffineTransform();
        tx.setToScale(scale, scale);
        setTransform(tx);
      }
      catch(NoninvertibleTransformException ex){
        Trace.exception(ex);
      }
    }
  }

  /**
   * Returns true if the view is scaled to fit
   */
  public boolean isScaledToFit(){
    return scaledToFit;
  }

  @Override
  public void setSize(Dimension size){
    super.setSize(size);
    if (scaledToFit)
      scaleToFit();
  }

  @Override
  public void setSize(int width, int height){
    super.setSize(width, height);
    if (scaledToFit)
      scaleToFit();
  }

  @Override
  public void setBounds(Rectangle bounds){
    super.setBounds(bounds);
    if (scaledToFit)
      scaleToFit();
  }

  @Override
  public void setBounds(int x, int y, int width, int height){
    super.setBounds(x, y, width, height);
    if (scaledToFit)
      scaleToFit();
  }

  /**
   * @undocumented until scrolling works with rotation
   */
  protected void setTransform(AffineTransform tx) throws NoninvertibleTransformException{
    // Note that we are maintaining backwards compatibility with
    // the old ViewScrollBar API. This method could be cleaner in
    // expressing that (by delegating to two separate methods).
    // (parent instanceof JViewport) and (center != null) are both
    // indications that we are in a JScrollPane, and hence not
    // dealing with ViewScrollBar stuff.
    AffineTransform oldTx = this.tx;
    if (tx != null && tx.getDeterminant() != 0.0){
      this.tx = tx;
      if (paintPoint == null)
	paintPoint = new Point();
      if (popupPoint == null)
	popupPoint = new Point();

      Point center = null;
      Component parent = getParent();
      Dimension prefSize = getPreferredSize();
      if (parent instanceof JViewport){ // sets center to non-null
	JViewport viewport = (JViewport)parent;
	Dimension extent = viewport.getExtentSize();
	Point origin = viewport.getViewPosition();
	center = new Point(origin.x + Math.min(extent.width, prefSize.width)/2,
			   origin.y + Math.min(extent.height, prefSize.height)/2);

	if (oldTx != null)
	  oldTx.inverseTransform(center, center);
	if (!getSize().equals(prefSize))
	  setSize(prefSize);
      } else
	repaintCanvas();

      ((ScalableScrollState)vertical_state).transformChanged(oldTx);
      ((ScalableScrollState)horizontal_state).transformChanged(oldTx);
      if (center != null){ // only if parent instanceof JViewport
	if (tx != null)
	  tx.transform(center, center);
	JViewport viewport = (JViewport)parent;
	Dimension extent = viewport.getExtentSize();
	int x = 0;
	int y = 0;
	if (extent.width < prefSize.width)
	  x = center.x - extent.width/2;
	if (extent.height < prefSize.height)
	  y = center.y - extent.height/2;
	viewport.setViewPosition(new Point(x, y));
	viewport.getParent().validate();//bug?
      }
      updateSelectionMarkers();
      if (center != null)
	parent.repaint(); //repaintCanvas();
      else
	repaintCanvas();
      if (getSelection().length > 0 && parent instanceof JViewport)
	  adjustScrollForSelection((JViewport)parent);
    }
    else
      throw new NoninvertibleTransformException("Determinant is 0");
    notifyTransformChanged();
  }

  private void adjustScrollForSelection(JViewport viewport) {
    Dimension extent = viewport.getExtentSize();
    Rectangle selectionBounds = getSelectionBounds();
    try {
      Point newCenter = getCurrentSelectionCenter();
      translateWorkspaceToView(newCenter);
      tranlateViewToWindow(newCenter);
      tx.transform(newCenter, newCenter);
      //always trying to center selection.
      //Math.max keeps origin of viewport from being above or to the
      //left of workspace view.
      int x = Math.max(0, newCenter.x - extent.width/2);
      int y = Math.max(0, newCenter.y - extent.height/2);
      Dimension size = getSize();
      //Math.min keeps origin of viewport from being too far down or too
      //far to the right-- this would otherwise create weird empty space
      //at bottom or right of viewport.
      x = Math.min(x,size.width - extent.width);
      y = Math.min(y,size.height - extent.height);
      Point topLeft = new Point(x, y);
      viewport.setViewPosition(topLeft);
    } catch (G2AccessException gae) {
      Trace.exception(gae);
    }
  }

  private Rectangle getSelectionBounds() {
    Component[] markers = getSelectionMarkers();
    Rectangle bounds = new Rectangle();
    Point topPoint, bottomPoint;
    int left, right, top, bottom;

    for (int x = 0; x<markers.length; x++)
      bounds.add(markers[x].getBounds());

    topPoint = bounds.getLocation();
    bottomPoint = new Point(topPoint.x+bounds.width,
			    topPoint.y+bounds.height);
    tranlateViewToWindow(topPoint);
    tranlateViewToWindow(bottomPoint);
    tx.transform(topPoint, topPoint);
    tx.transform(bottomPoint, bottomPoint);
    left = topPoint.x;
    right = bottomPoint.x;
    top = topPoint.y;
    bottom = bottomPoint.y;
    return new Rectangle(left, top, right - left, bottom - top);
  }

  @Override
  public Dimension getPreferredSize(){
    Dimension size = super.getPreferredSize();
    if (tx == null){
      return size;
    }
    else if (getParent() instanceof JViewport) {
      //assumes tx is just a scale, handle generic tx?
      double sx = tx.getScaleX();
      double sy = tx.getScaleY();
      return new Dimension(Math.round((float)(size.width*sx)), Math.round((float)(size.height*sy)));
    } else
      return size;
  }

  /**
   * @undocumented until scrolling works with rotation
   */
  protected AffineTransform getTransform(){
    if (tx != null)
      return (AffineTransform)tx.clone();
    return null;
  }

  private Point popupPoint; //this point gets created in setTransform

  @Override
  public void showPopup(PopupMenu popup, int x, int y){
    if (tx != null){
      popupPoint.x = x;
      popupPoint.y = y;
      tx.transform(popupPoint, popupPoint);
      super.showPopup(popup, popupPoint.x, popupPoint.y);
    }
    else
      super.showPopup(popup, x, y);
  }

  @Override
  protected MarkerElement createMarkerElement(int locn, int x, int y){
    Dimension d = getInverseTransformedDimensionForMarker();
    return new ScalableMarkerElement(locn, x, y, d.width, d.height);
  }

  private Point markerPoint = new Point();
  private Dimension markerDimension = new Dimension();

  Dimension getInverseTransformedDimensionForMarker(){
    int markerHalfWidth = MarkerElement.getMarkerHalfWidth();
    markerPoint.x = markerHalfWidth*2;
    markerPoint.y = markerPoint.x;
    if (tx != null){
      try{
	tx.inverseTransform(markerPoint, markerPoint);
      }
      catch(NoninvertibleTransformException ex){
	Trace.exception(ex);
      }
    }
    markerDimension.width = Math.max(markerPoint.x, 3);//width or height < 3 is too small
    markerDimension.height = Math.max(markerPoint.y, 3);
    return markerDimension;
  }

  private void updateSelectionMarkers(){
    Dimension d = getInverseTransformedDimensionForMarker();
    Component[] markers = getSelectionMarkers();
    if (markers == null) return;
    for (int i=0; i<markers.length; i++){
      ScalableMarkerElement marker = (ScalableMarkerElement)markers[i];
      marker.setBounds(marker.originalX-d.width/2, marker.originalY-d.height/2, d.width, d.height);
    }
  }

  @Override
  public void showWorkspace(Structure showingParticulars){
    super.showWorkspace(showingParticulars);

    if (showingParticulars != null){
      double sx = getScaleXForShow(showingParticulars);
      double sy = getScaleYForShow(showingParticulars);
      try{
	setScale(sx, sy);
      }
      catch(NoninvertibleTransformException ex){
	Trace.exception(ex);
      }
    }
  }

  private double getScaleXForShow(Structure showingParticulars){
    double scaleX = translateSymbolicScale((Symbol)showingParticulars.getAttributeValue(SYMBOLIC_X_SCALE_, null), true);
    Number magX = (Number)showingParticulars.getAttributeValue(X_MAGNIFICATION_, null);
    return (magX == null ? scaleX : scaleX * magX.doubleValue());
  }

  private double getScaleYForShow(Structure showingParticulars){
    double scaleY = translateSymbolicScale((Symbol)showingParticulars.getAttributeValue(SYMBOLIC_Y_SCALE_, null), false);
    Number magY = (Number)showingParticulars.getAttributeValue(Y_MAGNIFICATION_, null);
    return (magY == null ? scaleY : scaleY * magY.doubleValue());
  }

  private double translateSymbolicScale(Symbol scale, boolean xscale){
    if (scale == null || scale.equals(CURRENT_))
      return (xscale ? getScaleX() : getScaleY());
    else if (scale.equals(FULL_))
      return 1;
    else if (scale.equals(THREE_QUARTER_))
      return 0.75;
    else if (scale.equals(HALF_))
      return 0.5;
    else if (scale.equals(ONE_QUARTER_))
      return 0.25;
    else
      return 1;
  }

  /**
   * @undocumented
   */
  public void addTransformationListener(TransformationListener listener){
    listeners.addElement(listener);
  }

  /**
   * @undocumented
   */
  public void removeTransformationListener(TransformationListener listener){
    listeners.removeElement(listener);
  }

  private void notifyTransformChanged(){
    TransformationEvent event = new TransformationEvent(this);
    Vector l;
    synchronized(this){
      l = (Vector)listeners.clone();
    }
    Enumeration dispatchList = l.elements();
    while (dispatchList.hasMoreElements())
      ((TransformationListener)dispatchList.nextElement()).transformationChanged(event);
  }

  @Override
  public int getNumberOfPages(){
    WorkspaceFormat pageFormat = getPageFormat();
    if (pageFormat.scaleToFit)
      return 1;
    double printableWidth = pageFormat.getImageableWidth();
    double printableHeight = pageFormat.getImageableHeight();
    return ((int)Math.ceil((pageFormat.scale * getWidth()) / printableWidth)) *
	    ((int)Math.ceil((pageFormat.scale * getHeight()) / printableHeight));
  }

  private WorkspaceFormat pageFormat;

  @Override
  public PageFormat getPageFormat(int pageIndex){
    return getPageFormat();
  }

  public WorkspaceFormat getPageFormat(){
    if (pageFormat == null)
      pageFormat = new WorkspaceFormat();
    return pageFormat;
  }

  public void setPageFormat(WorkspaceFormat pageFormat){
    this.pageFormat = pageFormat;
  }

  @Override
  public Printable getPrintable(int pageIndex){
    return this;
  }

  /*
    print order:
    ------
        /
      /
    /
   ------>
   */
  @Override
  public int print(Graphics g, PageFormat pageFormat, int pageIndex) throws PrinterException{
    int numberOfPages = getNumberOfPages();
    if(pageIndex >= numberOfPages)
      return NO_SUCH_PAGE;

    Graphics2D  g2 = (Graphics2D) g;

    g2.translate(pageFormat.getImageableX(), pageFormat.getImageableY());

    double pageHeight = pageFormat.getImageableHeight();
    double pageWidth = pageFormat.getImageableWidth();

    double scale = 1.0;
    if (pageFormat instanceof WorkspaceFormat){
      WorkspaceFormat workspaceFormat = (WorkspaceFormat)pageFormat;
      if (workspaceFormat.scaleToFit)
	scale = Math.min(pageWidth/getWidth(),
			 pageHeight/getHeight());
      else
	scale = workspaceFormat.scale;
    }

    int numberOfPagesInRow = (int)Math.ceil((scale * getWidth()) / pageWidth);
    int row = pageIndex / numberOfPagesInRow;
    int col = pageIndex % numberOfPagesInRow;

    g2.translate(-(pageWidth * col), -(pageHeight * row));
    g2.scale(scale, scale);
    paint(g2);

    return Printable.PAGE_EXISTS;
  }

}









