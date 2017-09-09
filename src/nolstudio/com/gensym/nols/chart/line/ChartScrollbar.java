package com.gensym.nols.chart.line;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import javax.swing.*;

public class ChartScrollbar extends JScrollBar implements ScrollpaneListener, AdjustmentListener { //, ChangeListener
	private int visibleRange;  // in pixels
	private int fullRange;  // in pixels
	private int currentValue;  // in pixels
	private static int SCROLLMAX = 65535;
	//	private static int SCROLLMAX =    2147483647;
	public Vector itsListeners;
	private int unit;
	private int block;
	private int visibleRangeScrollUnits;  // visibleRange in scrollbar units

	public ChartScrollbar(int orientation) {
		super(orientation);
		setMaximum(SCROLLMAX);
		setMinimum(0);
		itsListeners = new Vector(0, 10);
		addAdjustmentListener(this);  // listens for its own adjustment events
	}

	public void addScrollbarListener(ScrollbarListener l) {
		itsListeners.addElement(l);
	}

	public void removeScrollbarListener(ScrollbarListener l) {
		itsListeners.removeElement(l);
	}

	@Override
	public void adjustmentValueChanged(AdjustmentEvent event) {
		int position = event.getValue();  // in scrollbar units
		int val = (int) Math.rint((double)position*(double)fullRange/(double)SCROLLMAX); 
		//if(getOrientation() == Scrollbar.VERTICAL) System.out.println("Scrollbar got new adjustment event, val = "+val+", position = "+position);
		setThumbPosition(val);		
    }

	// Request to set thumb to new value, input in pixels.  Returns position of thumb, 
	// which might be different because of constraints
	public int setThumbPosition(final int val) {
		int value = val;
		if (value < 0){
			value = 0;
		}
		if (value > fullRange - visibleRange) {
			value = fullRange - visibleRange;
		}
		if(value==currentValue) {
			return value;  // already OK
		}
		currentValue = value;
		// convert to scrollbar units
		int position = (int) Math.rint(((double)SCROLLMAX*(double)value)/(double)fullRange);
		//if(getOrientation() == Scrollbar.VERTICAL) System.out.println("Setting thumb to value = "+val+" and position = "+position );
		setValues(position, visibleRangeScrollUnits, 0, SCROLLMAX);
		// broadcast event to listeners
		ScrollbarEvent event = new ScrollbarEvent(this);
		for(int j=0; j < itsListeners.size(); ++j) {
			((ScrollbarListener) itsListeners.elementAt(j)).scrollbarAdjusted(event);
		}
		return currentValue;
	}

	private void setParameters(int visible, int full) {	
		//if(getOrientation() == Scrollbar.HORIZONTAL) System.out.println("Setting scrollbar parameters: visibleRange="+visible+", fullRange="+full);
		visibleRange = visible;
		fullRange = full;
		block = Math.max(9, (int) Math.rint(0.9*visible));   // minimum block of 9 pixels
		unit = Math.max(1, (int) Math.rint(0.09*visible));	// minimum unit of 1 pixel
		setBlockIncrement((int) Math.rint((double)SCROLLMAX*(double)block/(double)full));
		setUnitIncrement((int) Math.rint((double)SCROLLMAX*(double)unit/(double)full));
		// cache the visible range in scroll units (used in setThumb)
		visibleRangeScrollUnits = (int) Math.rint((double)SCROLLMAX*(double)visibleRange/(double)fullRange);
	}

	public int getCurrentValue() {
		return currentValue;
	}

	public int getFullRange() {
		return fullRange;
	}

	public int getBlock(){
		return block;
	}

	public int getUnit(){
		return unit;
	}

	public int getVisibleRange() {
		return visibleRange;
	}

	// Listeners
	@Override
	public void scrollpaneResized(ScrollpaneEvent e) {
		ChartScrollpane pane = e.getScrollpane();
		int val=0, vRange=0, fRange=0;
		if (getOrientation() == Scrollbar.HORIZONTAL) {
			val = pane.getViewX();
			vRange = pane.getViewWidth();
			fRange = pane.getFullWidth();
			//System.out.println("Scrollbar got scrollpaneResized event, val = "+val+", visible = "+vRange+", full = "+fRange);
		} else { // VERTICAL
			val = pane.getViewY();
			vRange = pane.getViewHeight();
			fRange = pane.getFullHeight();
		}
		if(visibleRange!=vRange || fullRange!=fRange) {
			setParameters(vRange, fRange);
		}
		if(val != currentValue) {
			setThumbPosition(val);
		}
	}


	@Override
	public void scrollpaneScrolled(ScrollpaneEvent e) {
		// this is necessary because the scrollpane can be programmatically scrolled.
		// in such a case, the scroll bar must respond to the new position of the pane
		// this is opposite the normal directionality
		// looping is avoided by setting the thumb position only when the value is different than 
		//if(getOrientation() == Scrollbar.VERTICAL) System.out.println("scrollbar got scrollpane scrolled message");
		ChartScrollpane pane = e.getScrollpane();
		Point view = pane.getViewLocation();
		if (getOrientation() == Scrollbar.HORIZONTAL) {
			if (currentValue != view.x) {
				setThumbPosition(view.x);
			}
		} else {
			if (currentValue != view.y) {
				setThumbPosition(view.y);
			}
		}
	}

/*ONLY FOR DIAGNOSTICS 
	public void paint(Graphics g) {
System.out.println("Painting scrollbar, width = "+this.getBounds().width);
System.out.println("scrollbar params: value = "+currentValue+", visible = "+visibleRange+", range = "+fullRange);
		super.paint(g);
	} */
}
