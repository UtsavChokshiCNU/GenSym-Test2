package com.gensym.nols.chart.line;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class Chart extends JComponent implements ComponentListener, MouseListener, MouseMotionListener {
	public boolean drawingSelectionBox;
	public boolean releaseSelectionBox;
	private Image cachedImage;
	private Graphics cachedGraphics;
	private Vector invalidations;
	private Vector itsComponents;
	private int holdCount;
	protected Rectangle selectionBox;
	protected boolean showSelectionBox;
	protected Rectangle selectionBoxConstraints;
	protected int selectionBoxStyle;
	protected int selectionBoxBehavior;
	transient Vector itsListeners;
	private int width;  
	private int height;

	// selection box styles and behavior 
	public static final int OUTLINE_STYLE = 0;
	public static final int FILL_STYLE = 1;
	public static final int BOX_BEHAVIOR = 0;
	public static final int HORIZONTAL_BEHAVIOR = 1;
	public static final int VERTICAL_BEHAVIOR = 2;
	
	// drag properties
	public static final int DRAG_DOES_NOTHING = 0;
	public static final int DRAG_CREATES_SELECTION_BOX = 1;
	protected Color backColor;
	
	public Chart(Color backColor) {
		this();
		this.backColor = backColor;
	}

	public Chart() {
		backColor = getBackground();
		invalidations = new Vector(0, 20);
		itsComponents = new Vector(0, 20);
		itsListeners = new Vector(0, 10);
		selectionBox = new Rectangle();
		selectionBoxConstraints = null;  // set in resize
		showSelectionBox = false;
		drawingSelectionBox = false;
		releaseSelectionBox = false;
		addComponentListener(this);
		setVisible(true);
		enableEvents(AWTEvent.MOUSE_EVENT_MASK | AWTEvent.MOUSE_MOTION_EVENT_MASK);
		width =200;
		height = 100;
		holdCount = 0;
	}

	/** Increments the hold count, temporarily stops chart from drawing. 
	Use this method when doing a number of consecutive chart operations 
	to minimize redraw work. */
	public void holdOn() {
		holdCount++;
	}
	
	/** Reduces the hold count by one.  Causes an immediate repaint of invalidated
	regions when hold count reaches 0 */
	public void holdOff(){
		holdCount--;
		if(holdCount<0) {
			holdCount=0;
		}
		if (holdCount==0) {
			repaint(0L);
		}
	}

	@Override
	public boolean isOpaque(){
		return true;
	}

	public void addChartListener(ChartListener l) {
		itsListeners.addElement(l);
	}

	public void removeChartListener(ChartListener l) {
		itsListeners.removeElement(l);
	}

	// override various add methods to add backpointer to this chart
	@Override
	public Component add(Component c) {
		register(c);
		return super.add(c);
	}

	@Override
	public Component add(Component c, int index) {
		register(c);
		return super.add(c, index);
	}

	@Override
	public void add(Component c, Object constraints) {
		register(c);
		super.add(c, constraints);
	}

	@Override
	public void add(Component c, Object constraints, int index) {
		register(c);
		super.add(c, constraints, index);	
	}

	@Override
	public void remove(Component c) {
		itsComponents.removeElement(c);
		c.removeMouseMotionListener(this);
		c.removeMouseListener(this);
		super.remove(c);
	}

	public void register(Component c) {
		if (itsComponents.contains(c)){
			return;
		}
		itsComponents.addElement(c);
		// chart listens for mouse events on its components
		c.addMouseMotionListener(this);
		c.addMouseListener(this);
		if (c instanceof ChartComponent){
			((ChartComponent) c).itsChart = this;
		}else if (c instanceof Container) {
			Container container = (Container) c;
			for (int i=0;i<container.getComponentCount();++i) {
				register(container.getComponent(i));
			}
		}
	}

	public void liftToTop(Component c) {
		Container parent = c.getParent();
		parent.remove(c);
		parent.add(c,0);
	}

	public Rectangle getVisiblePortion(Component c) {
		// given component c contained in this chart, find the portion of the component
		// that is currently visible, in chart coordinates
		Rectangle bounds;
		if (c.getParent() instanceof ChartScrollpane) {
			ChartScrollpane pane = (ChartScrollpane) c.getParent();
			Rectangle vbounds = c.getBounds();  // relative to viewport
			Rectangle view = new Rectangle(0, 0, pane.getViewWidth(), pane.getViewHeight());  // also relative to view port
			Rectangle intersection = vbounds.intersection(view);
			intersection.x = intersection.x - vbounds.x;   // translate back to component coordinates
			intersection.y = intersection.y - vbounds.y;
			bounds = toChartCoordinates(c, intersection);
		} 
		else bounds = c.getBounds();  // in chart coords
		Rectangle chartBounds = new Rectangle(0,0,width, height);
		return bounds.intersection(chartBounds);
	}

	private void startSelectionBox(int x0, int y0, int style, int behavior) {
		selectionBox.x = x0;
		selectionBox.y = y0;
		selectionBoxStyle = style;
		selectionBoxBehavior = behavior;
		selectionBox.width = 0;
		selectionBox.height = 0;
		drawingSelectionBox = true;  // tell the world
		showSelectionBox = false;  // don't show it until we are sure the drag is for real
		releaseSelectionBox = false;
		repaint();  // to clear old selection box, if any
	}

	private Point extendSelectionBox(final int x, final int y) {
		int xAxis = x;
		int yAxis= y;
		// extend the box from (x0, y0) to (x, y)
		if (selectionBoxConstraints != null) {
			if (xAxis < selectionBoxConstraints.x) 
				xAxis = selectionBoxConstraints.x;
			
			if (yAxis < selectionBoxConstraints.y) 
				yAxis = selectionBoxConstraints.y;

			if (xAxis > selectionBoxConstraints.x + selectionBoxConstraints.width) 
				xAxis = selectionBoxConstraints.x + selectionBoxConstraints.width;
			
			if (yAxis > selectionBoxConstraints.y + selectionBoxConstraints.height) 
				yAxis = selectionBoxConstraints.y + selectionBoxConstraints.height;
		}
		selectionBox.width = xAxis - selectionBox.x;  // might be negative, allow it so x,y always represents starting point of box
		selectionBox.height = yAxis - selectionBox.y;
		if (selectionBoxConstraints != null) {
			if (selectionBoxBehavior == Chart.HORIZONTAL_BEHAVIOR) {
				// extend from lower to upper bound on x
				selectionBox.x = selectionBoxConstraints.x;
				selectionBox.width = selectionBoxConstraints.width;
			} else if (selectionBoxBehavior == Chart.VERTICAL_BEHAVIOR) {
				// extend from lower to upper bound on y
				selectionBox.y = selectionBoxConstraints.y;
				selectionBox.height = selectionBoxConstraints.height;			
			}
		}
		showSelectionBox = true;
		repaint();
		return new Point(xAxis, yAxis);  // the actual point, considering constraints
	}

	private void translateSelectionBoxOrigin(int dx, int dy) {
		// origin is allowed to move beyond constraints (i.e. the case of scrolling)
		// x and y are in chart coordinates
		selectionBox.x = selectionBox.x + dx;
		selectionBox.y = selectionBox.y + dy;
		selectionBox.width = selectionBox.width - dx;
		selectionBox.height = selectionBox.height - dy;
		//System.out.println("selection box = "+selectionBox.toString());
	}

	public Rectangle getSelectionBoxExtent() {
		// make sure width and height are positive
		int sbx, sby, sbw, sbh;
		if (selectionBox.width < 0) {
			sbx = selectionBox.x + selectionBox.width;
			sbw = - selectionBox.width;
		} else {
			sbx = selectionBox.x;
			sbw = selectionBox.width;
		}
		if (selectionBox.height < 0) {
			sby = selectionBox.y + selectionBox.height;
			sbh = - selectionBox.height;
		} else {
			sby = selectionBox.y;
			sbh = selectionBox.height;
		}
		Rectangle r = new Rectangle(sbx, sby, sbw, sbh);
		return r;
	}

	public void getContainedComponents(Rectangle r, Vector components) {
		// appends components totally contained in r to the supplied vector
		Component c;
		Rectangle bounds, intersection;
		for (int i=0; i<itsComponents.size(); i++) {
			c = (Component) itsComponents.elementAt(i);
			bounds = c.getBounds();
			bounds.x = 0; 
			bounds.y = 0;  // translate to component coordinates
			intersection = toComponentCoordinates(c, r).intersection(bounds);
			if (intersection.width == bounds.width && intersection.height == bounds.height) {
				components.addElement(c);
			}
		}
	}

	public void getIntersectingComponents(Rectangle r, Vector components, Vector intersections) {
		// returns list of components intersecting the given rectangle r (given in chart coordinates)
		// also returns the intersection of r with the components, in component coordinates
		Component c;
		Rectangle bounds, intersection;
		for (int i=0; i<itsComponents.size(); i++) {
			c = (Component) itsComponents.elementAt(i);
			bounds = c.getBounds();
			bounds.x = 0; 
			bounds.y = 0;  // translate to component coordinates
			intersection = toComponentCoordinates(c, r).intersection(bounds);
			if (intersection.width > 0 && intersection.height > 0) {
				components.addElement(c);
				intersections.addElement(intersection);
			}
		}
	}

	public void hideSelectionBox() {
		showSelectionBox = false;
		repaint();
	}

	public void setSelectionBoxConstraints(Rectangle r) {
		selectionBoxConstraints = new Rectangle(r);
//		System.out.println("selection constrained to "+r.toString());
	}

	public void releaseSelectionBoxConstraints() {
		selectionBoxConstraints = new Rectangle(0,0,0,0);
	}

	public int getSelectionBoxStyle() {
		return selectionBoxStyle;
	}

	public int getSelectionBoxBehavior() {
		return selectionBoxBehavior;
	}

	public Point toChartCoordinates(Component c, Point p) {
		Component parent = c;
		int chartX = p.x;
		int chartY = p.y;
		Point offset;
		while (parent != null && !(parent instanceof Chart)) {
			offset = parent.getLocation();
			chartX = chartX + offset.x;
			chartY = chartY + offset.y;
			parent = parent.getParent();
		}
		return new Point(chartX, chartY);
	}
	
	public Point toComponentCoordinates(Component c, Point p) {
		Component parent = c;
		int compX = p.x;
		int compY = p.y;
		Point offset;
		while (parent != null && !(parent instanceof Chart)) {
			offset = parent.getLocation();
			compX = compX - offset.x;
			compY = compY - offset.y;
			parent = parent.getParent();
		}
		return new Point(compX, compY);
	}

	public Rectangle toChartCoordinates(Component c, Rectangle r) {
		Point p = toChartCoordinates(c, new Point(r.x, r.y));
		return new Rectangle (p.x, p.y, r.width, r.height);
	}

	public Rectangle toComponentCoordinates(Component c, Rectangle r) {
		Point p = toComponentCoordinates(c, new Point(r.x, r.y));
		return new Rectangle (p.x, p.y, r.width, r.height);
	}

	public void addInvalidation(int x, int y, int width, int height) {
		//System.out.println("received invalidation, "+width+" by "+height);
		addInvalidation(new Rectangle(x, y, width, height));
	}

	public void invalidateAll() {
		//System.out.println("Invalidating entire chart");
		invalidations.removeAllElements();
		addInvalidation(new Rectangle(0,0,getSize().width,getSize().height));
	}
		
	public void addInvalidation(Rectangle r) {
		// if this rectangle intersects another, replace with the union
		for (int i=0; i<invalidations.size(); ++i) {
			if(r.intersects((Rectangle) invalidations.elementAt(i))) {
				invalidations.setElementAt(r.union((Rectangle) invalidations.elementAt(i)), i);
				return;
			}
		}
		invalidations.addElement(r);
		//System.out.println("Now have total of "+invalidations.size()+" invalidations");
	}

	@Override
	public void paint(Graphics g) {
		//System.out.println("In chart paint, hold count = "+holdCount);
		if(holdCount>0) {
			return;
		}

		if(g instanceof java.awt.PrintGraphics){
			Component c;
			ChartScrollpane pane;
			Component[] cs = getComponents();
			int ncomponents = cs.length;
			for (int j=0; j < ncomponents; ++j) {
				c = (Component) cs[j];
				if (c instanceof ChartScrollpane) {
					pane = (ChartScrollpane) c;
					pane.updateGraphics(this, g);
				}
			}
			Rectangle invalidation = new Rectangle(0,0,getSize().width, getSize().height);
			if(invalidation.width > 0 && invalidation.height > 0) {
				g.setClip(invalidation.x, invalidation.y, invalidation.width, invalidation.height);				
				g.setColor(backColor);
				g.fillRect(invalidation.x, invalidation.y, invalidation.width, invalidation.height);
				super.paint(g);  //this will go through the containment hierarchy to ask each component to paint into the clip rectangle
			}

			// update other components
			for (int j=0; j < ncomponents; ++j) {
				c = (Component) cs[j];
				if (!(c instanceof ChartScrollpane)) {
					invalidation = c.getBounds();
					g.setClip(invalidation.x, invalidation.y, invalidation.width, invalidation.height);
					g.setColor(backColor);
					g.fillRect(invalidation.x, invalidation.y, invalidation.width, invalidation.height);
					super.paint(g);
				}
			}
			return;
		}
		
		
		
		// create off-screen graphics if needed
		if (cachedImage == null) {
			cachedImage = createImage(width, height);
			cachedGraphics = cachedImage.getGraphics();
			invalidations.removeAllElements();
			//System.out.println("New cached image, invalidating all");
			addInvalidation(new Rectangle(0,0,getSize().width, getSize().height));  // make sure entire chart is invalidated
		}
		// now shift the graphic on all scroll panes
		Component c;
		ChartScrollpane pane;
		Component[] cs = getComponents();
//		int ncomponents = getComponentCount(); //gchen changed 9.22.1999
		int ncomponents = cs.length;
		for (int j=0; j < ncomponents; ++j) {
//			c = (Component) getComponent (j);//gchen changed 9.22.1999
			c = (Component) cs[j];
			if (c instanceof ChartScrollpane) {
				//System.out.println("updating scroll pane "+j);
				pane = (ChartScrollpane) c;
				pane.updateGraphics(this, cachedGraphics);
			}
		}
		// now update invalidated regions
		Rectangle invalidation;
		for(int j=0; j < invalidations.size(); ++j) {
			invalidation = (Rectangle) invalidations.elementAt(j);
			//System.out.println("painting invalidation at "+invalidation.x+", "+invalidation.y+" size = "+invalidation.width+" by "+invalidation.height);
			if(invalidation.width > 0 && invalidation.height > 0) {
				cachedGraphics.setClip(invalidation.x, invalidation.y, invalidation.width, invalidation.height);				
				// clear background
				cachedGraphics.setColor(backColor);
				//cachedGraphics.setColor(new Color((int)Math.floor((float)256*Math.random()),(int)Math.floor((float)256*Math.random()),(int)Math.floor((float)256*Math.random())));
				cachedGraphics.fillRect(invalidation.x, invalidation.y, invalidation.width, invalidation.height);
				super.paint(cachedGraphics);  //this will go through the containment hierarchy to ask each component to paint into the clip rectangle
			}
		}

		// update other components
		for (int j=0; j < ncomponents; ++j) {
//			c = (Component) getComponent (j);//gchen changed 9.22.1999
			c = (Component) cs[j];
			if (!(c instanceof ChartScrollpane)) {
				//System.out.println("Updating "+c.getClass().getName()+" bounds = "+c.getBounds());
				invalidation = c.getBounds();
				cachedGraphics.setClip(invalidation.x, invalidation.y, invalidation.width, invalidation.height);
				cachedGraphics.setColor(backColor);
				cachedGraphics.fillRect(invalidation.x, invalidation.y, invalidation.width, invalidation.height);
				super.paint(cachedGraphics);
			}
		}

	// cached graphic is now up-to-date, so any remaining invalidations can be cleared
		invalidations.removeAllElements();
		g.drawImage(cachedImage, 0, 0, this);

		// now add selection box directly to screen
		if (showSelectionBox) {
			Rectangle sb = getSelectionBoxExtent().intersection(selectionBoxConstraints);   //never draw outside screen area
			g.setColor(Color.black);
			g.setXORMode(Color.white);
			if(!releaseSelectionBox) {
				if (selectionBoxStyle == 0){
					g.drawRect(sb.x, sb.y, sb.width, sb.height);
				} else{
					g.fillRect(sb.x, sb.y, sb.width, sb.height);
				}
			}
			g.setPaintMode();
		}
	}


	// LISTENERS

	@Override
	public void componentResized(ComponentEvent event) {
		// source is the chart itself (not components of chart)
		Rectangle bounds = getBounds();
		if(bounds.width<=0 || bounds.height<=0) {
			return;  // this can happen during layout, ignore
		}
		if(bounds.width==width && bounds.height==height){
			return;
		}
		// before setting new width and height, scale the selection box constraints
		if (selectionBoxConstraints != null) {
			double xscale = ((double)bounds.width)/width;
			double yscale = ((double)bounds.height)/height;
			selectionBoxConstraints.x = (int) Math.rint(selectionBoxConstraints.x*xscale);
			selectionBoxConstraints.y = (int) Math.rint(selectionBoxConstraints.y*yscale);
			selectionBoxConstraints.width = (int) Math.rint(selectionBoxConstraints.width*xscale);
			selectionBoxConstraints.height = (int) Math.rint(selectionBoxConstraints.height*yscale);
		}
		//System.out.println("Chart was resized, now " + bounds.width + " by " + bounds.height +" was "+width+" by "+height);
		// set new width & height
		width = bounds.width;
		height = bounds.height;
		cachedImage=null;
		if (cachedGraphics != null) {
			cachedGraphics.dispose();
			cachedGraphics = null;
    	}
		repaint();
	}

	@Override
	public void componentHidden(ComponentEvent event) {}
   	@Override
	public void componentMoved(ComponentEvent event) {}
	@Override
	public void componentShown(ComponentEvent event) {}

   	@Override
	public void mouseEntered(MouseEvent event) {}
    @Override
    public void mouseExited(MouseEvent event) {}
	@Override
	public void mouseMoved(MouseEvent event) {}

   	@Override
	public void mousePressed(MouseEvent event) {
		if (drawingSelectionBox){
			return;  // seems to get a spurious mouse press when tracking over scroll thumb
		}
//		System.out.println("mousepress source="+event.getSource());
		if (!(event.getSource() instanceof Chartable)){
			return;
		}
		Chartable source = (Chartable) event.getSource();
		// popup menu
		if (event.isMetaDown() || event.isPopupTrigger()) {
			ChartEvent chartEvent= new ChartEvent(this, event);
			for (int i=0; i<itsListeners.size(); ++i) {
				((ChartListener) itsListeners.elementAt(i)).chartPopupTriggered(chartEvent);
			}
		// start selection box
		} else if (source.getDragBehavior() == Chart.DRAG_CREATES_SELECTION_BOX) {  // create selection box
			Point chartPoint = toChartCoordinates((Component) source, event.getPoint());
			setSelectionBoxConstraints(source.getSelectionBoxConstraints());
			startSelectionBox(chartPoint.x, chartPoint.y, source.getSelectionBoxStyle(), source.getSelectionBoxBehavior());
		}
	}

   	@Override
	public void mouseReleased(MouseEvent event) {
//		System.out.println("mouseReleased source="+event.getSource());
		if (drawingSelectionBox) { 
			drawingSelectionBox = false;
			releaseSelectionBox  = true;
			if (showSelectionBox) {  // finish selection box only if it was visible
				Component source = (Component) event.getSource();
				Point mousePoint = event.getPoint();
				Point chartPoint = toChartCoordinates(source, mousePoint);
				extendSelectionBox(chartPoint.x, chartPoint.y);
				ChartEvent chartEvent = new ChartEvent(this, event);
				chartEvent.setSelectionRectangle(getSelectionBoxExtent());
				for (int i=0; i<itsListeners.size(); ++i) {
					((ChartListener) itsListeners.elementAt(i)).chartAreaSelected(chartEvent);
				}
			}
		}
	}

	@Override
	public void mouseClicked(MouseEvent event) {
		ChartEvent chartEvent = new ChartEvent(this, event);
		for (int i=0; i<itsListeners.size(); ++i) {
			((ChartListener) itsListeners.elementAt(i)).chartPointSelected(chartEvent);
		}
	}

	@Override
	public void mouseDragged(MouseEvent event) {
//		System.out.println("mouseDragged source="+event.getSource());
//	System.out.println("event = mouse dragged");
		Component csource = (Component) event.getSource();
		if (!(csource instanceof Chartable)) {
			return;
		}
		Chartable source = (Chartable) csource;
		Chart chart = this;
		Point mousePoint = event.getPoint();
		Point chartPoint = toChartCoordinates(csource, mousePoint);
		int chartX = chartPoint.x;
		int chartY = chartPoint.y;
		if (drawingSelectionBox) {
			Point sbCorner = extendSelectionBox(chartX, chartY);
			//Change by gchen to stop the scroll problem
/*			if (sbCorner.x != chartX) {
				// hit a constraint, maybe scroll
				Container parent = csource.getParent();
				if (parent instanceof ChartScrollpane) {
					ChartScrollpane pane = (ChartScrollpane) parent;
					if (pane.itsHorizontalScrollbar != null) {
						ChartScrollbar scrollbar = pane.itsHorizontalScrollbar;
						int oldValue = scrollbar.getValue();
						int newValue;
						if (chartX > sbCorner.x){
							newValue = scrollbar.getCurrentValue() + scrollbar.getUnit();
							scrollbar.setThumbPosition(newValue);
						}else{
							newValue = scrollbar.getCurrentValue() - scrollbar.getUnit();
							scrollbar.setThumbPosition(newValue);
						}
						translateSelectionBoxOrigin(oldValue - newValue, 0);
					}
				}
			}
			if (sbCorner.y != chartY) {
				// hit a constraint, maybe scroll
				Container parent = csource.getParent();
				if (parent instanceof ChartScrollpane) {
					ChartScrollpane pane = (ChartScrollpane) parent;
					if (pane.itsVerticalScrollbar != null) {
						ChartScrollbar scrollbar = pane.itsVerticalScrollbar;
						int oldValue = scrollbar.getValue();
						int newValue;
						if (chartY > sbCorner.y){
							newValue = scrollbar.getCurrentValue() + scrollbar.getUnit();
							scrollbar.setThumbPosition(newValue);
						}else{
							newValue = scrollbar.getCurrentValue() - scrollbar.getUnit();
							scrollbar.setThumbPosition(newValue);
						}
						translateSelectionBoxOrigin(0, oldValue - newValue);
					}
				}
			}*/
		}
	}
	@Override
	public void setBackground(Color c){
		super.setBackground(c);
		backColor = c;
	}
}	  