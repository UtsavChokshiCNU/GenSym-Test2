package com.gensym.nols.chart.line;

import java.awt.*;
import java.util.*;
import javax.swing.*;

public class ChartScrollpane extends JPanel implements ScrollbarListener, Chartable {
/**
  (0,0)
   __________________________________
   |(vx,vy)	_________				|
   |		|VIEW	|				|
   |		|_______|				|
   |			(vx + vw, vy + vh)	|
   |								|
   |		FULL ITEM				|
   ---------------------------------| (fullWidth, fullHeight)
  */
	public ChartScrollbar itsHorizontalScrollbar;
	public ChartScrollbar itsVerticalScrollbar;
	public Chart itsChart;
	transient Vector itsListeners;
	private int viewX;
	private int viewY;
	private int fullWidth;
	private int fullHeight;
	private int viewWidth;
	private int viewHeight;
	private int lastPaintedX;
	private int lastPaintedY;

	public ChartScrollpane (Chart chart, Point viewLocation, Dimension viewDimension, Dimension fullDimension) {
		setLayout(null);
		viewWidth = viewDimension.width;
		viewHeight = viewDimension.width;
		setViewLocation(viewLocation);
		setDimension(fullDimension);
		lastPaintedX = 0;
		lastPaintedY = 0;
		setVisible(true);
		itsHorizontalScrollbar = null;
		itsVerticalScrollbar = null;
		itsChart = chart;
		itsListeners = new Vector(0, 10);
	}

	@Override
	public boolean isOpaque(){
		return false;
	}

	public void addScrollbar(ChartScrollbar bar) {
		if (bar.getOrientation() == Scrollbar.HORIZONTAL) 
			itsHorizontalScrollbar = bar;
		else{
			itsVerticalScrollbar = bar;
		}
		bar.addScrollbarListener(this);
		addScrollpaneListener(bar);
	}

	public void removeScrollbar(ChartScrollbar bar) {
		if (bar.getOrientation() == Scrollbar.HORIZONTAL) {
			itsHorizontalScrollbar = null;
		}else {
			itsVerticalScrollbar = null;
		}
		bar.removeScrollbarListener(this);
		removeScrollpaneListener(bar);	
	}

	public void addScrollpaneListener(ScrollpaneListener l) {
		itsListeners.addElement(l);
	}

	public void removeScrollpaneListener(ScrollpaneListener l) {
		itsListeners.removeElement(l);
	}

// override various add methods to register components with host chart
	@Override
	public Component add(Component c) {
		if (itsChart != null) {
			itsChart.register(c);
		}
		return super.add(c);
	}

	@Override
	public Component add(Component c, int index) {
		if (itsChart != null) {
			itsChart.register(c);
		}
		return super.add(c, index);
	}

	@Override
	public void add(Component c, Object constraints) {
		if (itsChart != null) {
			itsChart.register(c);
		}
		super.add(c, constraints);
	}

	@Override
	public void add(Component c, Object constraints, int index) {
		if (itsChart != null) {
			itsChart.register(c);
		}
		super.add(c, constraints, index);	
	}

	public Dimension getFullDimension() {
		return new Dimension(fullWidth, fullHeight);
	}

	public int getFullWidth() {
		return fullWidth;
	}

	public int getFullHeight() {
		return fullHeight;
	}

	public Point getViewLocation() {
		return new Point(viewX, viewY);
	}

	public int getViewX() {
		return viewX;
	}

	public int getViewY() {
		return viewY;
	}

	public Dimension getViewDimension() {
		return new Dimension(viewWidth, viewHeight);
	}

	public int getViewWidth() {
		return viewWidth;
	}

	public int getViewHeight() {
		return viewHeight;
	}

	public int setViewX(final int x) {
		// enforce constraint that view must be completely constrained within pane
		//System.out.println("In setViewX, x = "+x+" fullWidth = "+fullWidth+", viewWidth = "+viewWidth);
		int xAxis = x;
		if (xAxis < 0){
			xAxis = 0;
		}
		if (xAxis > fullWidth - viewWidth) {
			xAxis = fullWidth - viewWidth;
		}
		int shift = viewX - xAxis;
		if (shift == 0) {
			return xAxis;
		}
		//System.out.println("In setViewX, SHIFTING! New x = "+x+" shift = "+shift);
		viewX = xAxis;
		Component c;
		int ncomponents = getComponentCount();
		for (int j=0; j < ncomponents; ++j) {
			c = (Component) getComponent(j);
			Point location = c.getLocation();
			c.setLocation(location.x + shift, location.y);
		}
		return xAxis;
	}

	public int setViewY(final int y) {
		// enforce constraints that view must be completely constrained within pane
		//System.out.println("In setViewY, y = "+y+" fullHeight = "+fullHeight+", viewHeight = "+viewHeight);
		int yAxis = y;
		if (yAxis < 0) {
			yAxis = 0;
		}
		if (yAxis > fullHeight - viewHeight) {
			yAxis = fullHeight - viewHeight;
		}
		int shift = viewY - yAxis;
		if (shift == 0) {
			return yAxis;
		}
		//System.out.println("In setViewY, SHIFTING! New y = "+y+" shift = "+shift);
		viewY = yAxis;
		Component c;
		int ncomponents = getComponentCount();
		for (int j=0; j < ncomponents; ++j) {
			c = (Component) getComponent(j);
			Point location = c.getLocation();
			c.setLocation(location.x, location.y + shift);
		}
		return yAxis;
	}

	public Point setViewLocation(Point p) {
		int x = setViewX(p.x);
		int y = setViewY(p.y);
		return new Point(x, y);
	}

	public int setFullWidth(final int w) {
		int width = w;
		if(width == fullWidth) {
			return width;
		}
		if (width < viewWidth) {
			width = viewWidth;  // never smaller than the view
		}
		fullWidth = width;
		setViewX(viewX);  // enforce constraints on view position
		return width;
	}

	public int setFullHeight(final int h) {
		int height = h;
		if(height == fullHeight) {
			return height;
		}
		if (height < viewHeight) {
			height = viewHeight;  // never smaller than the view
		}
		fullHeight = height;
		//System.out.println("Resetting full height to "+fullHeight);
		setViewY(viewY);  // enforce constraints
		return height;
	}

	public Dimension setDimension(Dimension d) {
		int w = setFullWidth(d.width);
		int h = setFullHeight(d.height);
		return new Dimension(w, h);
	}

	public void zoom(final double magx, final double magy, final Point focus) {
		//System.out.println("Entering ChartScrollpane.zoom");
		double magxLocal = magx;
		double magyLocal = magy;
		if(Double.compare(magxLocal, 1.0) == 0 && Double.compare(magyLocal, 1.0) == 0) 
			return;
		//  zooming proportionally enlarges components
		int oldViewX = getViewX();
		int oldViewY = getViewY();
		int oldWidth = getFullWidth();
		int oldHeight = getFullHeight();
		int newWidth = oldWidth;
		int newHeight = oldHeight;
		int newViewX = oldViewX;
		int newViewY = oldViewY;
		// record old component positions, relative to full dimension
		int ncomponents = getComponentCount();
		int[] oldPosX = new int[ncomponents];
		int[] oldPosY = new int[ncomponents];
		Point location;
		Component c;
		for (int j=0; j < ncomponents; ++j) {
			c = getComponent(j);
			location = c.getLocation();  //relative to viewport (pane)
			oldPosX[j] = location.x + oldViewX; // relative to full dimension
			oldPosY[j] = location.y + oldViewY;
		}
		// resize pane
		if(Double.compare(magxLocal, 1.0) != 0) {
			newWidth = (int) Math.rint(magxLocal*oldWidth);
			newWidth = setFullWidth(newWidth);
			magxLocal = ((double)newWidth)/((double)oldWidth);
			// now scroll so that the focal position appears fixed in the viewport
			newViewX = (int) Math.rint(magxLocal*(oldViewX + focus.x) - focus.x);
			newViewX = setViewX(newViewX);
			//System.out.println("Zooming pane, x-dimension, new width = "+getFullWidth()+", new viewx = "+getViewX());
		}
		if(Double.compare(magyLocal, 1.0) != 0) {
			newHeight = (int) Math.rint(magyLocal*oldHeight);
			newHeight = setFullHeight(newHeight);
			magyLocal = ((double)newHeight)/((double)oldHeight);
			newViewY = (int) Math.rint(magyLocal*(oldViewY + focus.y) - focus.y);
			newViewY = setViewY(newViewY);
			//System.out.println("\tnew height = "+newHeight+", new viewy = "+newViewY);
		}
		// rescale components proportionally to match
		int x,y,width,height;
		Dimension size, minSize;
		for (int j=0; j < ncomponents; ++j) {
			c = getComponent(j);
			size = c.getSize();
			width = (int) Math.rint(magxLocal*size.width);
			height = (int) Math.rint(magyLocal*size.height);
			x = (int) Math.rint(magxLocal*oldPosX[j]);  // relative to full dimension
			y = (int) Math.rint(magyLocal*oldPosY[j]);
			//System.out.println("Zoom: "+c.getClass().getName()+" width= "+width+" height="+height); 
			c.setBounds(x - newViewX,y - newViewY, width, height);  // translate to pane
			//	System.out.println("Zoom: "+c.getClass().getName()+" bounds are now "+c.getBounds().toString());
		}
		// broadcast to listeners
		//System.out.println("\tview height = "+viewHeight+", full height = "+fullHeight+", viewy = "+viewY);
		ScrollpaneEvent event = new ScrollpaneEvent(this);
		for(int j=0; j < itsListeners.size(); ++j) {
			//System.out.println("Zoom is sending a scrollpaneResized event to "+itsListeners.elementAt(j).getClass().getName());
			((ScrollpaneListener) itsListeners.elementAt(j)).scrollpaneResized(event);
		}
		itsChart.addInvalidation(itsChart.getBounds());  // no conversion, already in chart coords
		itsChart.validate();  // needed to force layout to happen 
		//System.out.println("Repaint called from scrollpane.zoom");
		itsChart.repaint();
	}


	public void proportionalResize() {
	// adjust viewX and viewY so the same content is visible after resize
		Rectangle bounds = getBounds();
		if(bounds.height==viewHeight && bounds.width==viewWidth) {
			return;  // nothing to do
		}
		double rescaleX = (double) bounds.width/(double) viewWidth;
		fullWidth = (int) Math.rint(rescaleX*fullWidth);
		viewX = (int) Math.rint(rescaleX*viewX);
		viewWidth = bounds.width;
		double rescaleY = (double) bounds.height/(double) viewHeight;
		fullHeight = (int) Math.rint(rescaleY*fullHeight);	
		viewY = (int) Math.rint(rescaleY*viewY);
		viewHeight = bounds.height;

		// rescale components proportionally to match
    	Component c;
		int x,y,width,height;
		int ncomponents = getComponentCount();
		for (int j=0; j < ncomponents; ++j) {
			c = getComponent(j);
			bounds = c.getBounds();
			x = (int) Math.rint(rescaleX*bounds.x);
			y = (int) Math.rint(rescaleY*bounds.y);
			width = (int) Math.rint(rescaleX*bounds.width);
			height = (int) Math.rint(rescaleY*bounds.height);
			c.setBounds(x,y,width,height);
		}
		// inform listeners of resize
		ScrollpaneEvent event = new ScrollpaneEvent(this);
		for(int j=0; j < itsListeners.size(); ++j) {
			//System.out.println("Proportional resize is sending resized event to a "+itsListeners.elementAt(j).getClass().getName());
			((ScrollpaneListener) itsListeners.elementAt(j)).scrollpaneResized(event);
		}
    }

	public void updateGraphics(Chart chart, Graphics g) {
		//System.out.println("In ChartScrollpane, updateGraphics, viewX = "+viewX+" lastPaintedX = "+lastPaintedX+" viewY = "+viewY+" lastPaintedY = "+lastPaintedY);
		if (viewX != lastPaintedX) {
			int shift = viewX - lastPaintedX;
			Rectangle r = getBounds();
			if (Math.abs(shift) < r.width) {
				g.setClip(r);
				//System.out.println("shifting scroll pane graphic by "+shift+", r = "+r);
				if (shift > 0)  {  // shift graphic to the left, invalidate right edge
					g.copyArea(r.x + shift, r.y, r.width - shift, r.height, - shift, 0);
					chart.addInvalidation(r.x + r.width - shift, r.y, shift, r.height);
				}
				else { // shift < 0, shift graphic to right, invalidate left edge
					// 1/20/99  There is a bug in Microsoft's 3.1 VM in copyArea that 
					// corrupts the graphic on the following line (Sun's is OK)
					g.copyArea(r.x, r.y, r.width + shift, r.height, - shift, 0);
					chart.addInvalidation(r.x, r.y, - shift, r.height);
				}
			}
			else chart.addInvalidation(r);  // no part of image is usable
			lastPaintedX = viewX;
		}
		// ditto for Y
		if (viewY != lastPaintedY) {
			int shift = viewY - lastPaintedY;
			Rectangle r = getBounds();
			if (Math.abs(shift) < r.height) {
				g.setClip(r);
				if (shift > 0)  {  // shift graphic up, invalidate bottom edge (?)
					g.copyArea(r.x, r.y + shift, r.width, r.height - shift, 0, - shift);
					chart.addInvalidation(r.x, r.y + r.height - shift, r.width, shift);
				}
				else { // shift < 0, shift graphic down, invalidate upper edge
					g.copyArea(r.x, r.y, r.width, r.height + shift, 0, - shift);
					chart.addInvalidation(r.x, r.y, r.width, - shift);
				}
			}
			else chart.addInvalidation(r);  // no part of image is usable
			lastPaintedY = viewY;
		}
	}

	// Listeners
	@Override
	public void scrollbarAdjusted(ScrollbarEvent e) {
		ChartScrollbar bar = e.getScrollbar();
		if(bar.equals(itsHorizontalScrollbar)) {
			// MK 2/9/99: in the middle of a zoom, there is a mismatch between the scrollbar
			// and the scrollpane.  Don't allow the scrollbar to move the pane, or the focal
			// point may be off center for scatter charts.  This is a complex bug, due to the
			// interaction of two scroll panes with one scroll bar. When the first scrollpane
			// zooms, it sends a message to the scrollbar to sync up, and then the scrollbar sends a
			// message to both scroll panes to sync with it.  This is no problem for the first 
			// scroll pane, which is already in sync, but the second hasn't yet been zoomed. 
			// It cannot set the viewport to the desired position (enforcing constraints in 
			// setViewX or setViewY, and so it moves the view to a legal position, changing 
			// its focal point.  Next, the second pane is zoomed, and it maintains the new 
			// erroneous focal point that it acquired during the zooming of the first pane.  
			// This in turn forces the thumb to the wrong position, affecting both panes.
			// To prevent this, we simply check if the pane and the bar are the same size, 
			// before responding by scrolling the pane.  Hence, the following statement:
			//System.out.println("Chartpane got horizontal scroll event, val = "+bar.getCurrentValue()+", pane width = "+fullWidth+" bar width = "+bar.getFullRange()); 
			if(bar.getFullRange()!= fullWidth) {
				return; 
			}
			setViewX(bar.getCurrentValue()); 
		}
		else if (bar.equals(itsVerticalScrollbar)) {
			if(bar.getFullRange()!= fullHeight) {
				return; // see above explanation.
			}
			setViewY(bar.getCurrentValue());
		}
		itsChart.repaint();
	}

	//Chartable interface   
	@Override
	public int getDragBehavior(){
		return Chart.DRAG_CREATES_SELECTION_BOX;
	}

	@Override
	public Rectangle getSelectionBoxConstraints(){
		return itsChart.getVisiblePortion(this);
	}
	
	@Override
	public int getSelectionBoxStyle(){
		return Chart.OUTLINE_STYLE;
	}

	@Override
	public int getSelectionBoxBehavior(){
		return Chart.BOX_BEHAVIOR;
	}
}