package com.gensym.nols.chart.bar;

import com.gensym.nols.chart.line.*;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.lang.*;
import java.text.*;


/**
 * ScatterPlot
 *
 * @version     1.0 May 21 1998
 * @author      Brian O. Bush
**/
public class BarPlot extends Plot implements AxisListener, ComponentListener {

	public static final int VERTICAL = 1;
	public static final int HORIZONTAL = 2;
	public static final int INVERTED = 3;

	private static final boolean DEBUG = false;

	public ValueAxis yAxis;
	public ValueAxis xAxis;

	private double yMax, yMin;
	private double xLow, xHigh;

	private int mouseIndex;
	private Dimension displaySize;

	private int nBins;
	private double [] binValues;
	private Color backgroundColor;
	private Color barColor;
	private int shadowOffset;
	private boolean autoBarSpacing;
	private boolean applyBarShadow;
	private boolean drawStrings;
	public int selectionSlop;

	/**
	** BarPlot Constructor
	**
	**/
	public BarPlot(String name, double [] binValues, double xLow, double xHigh, ValueAxis xAxis, ValueAxis yAxis) {
		super();

		this.xAxis = xAxis;
		xAxis.setRangePadding(0.0);
		this.yAxis = yAxis;
		yAxis.setRangePadding(0.0);
		this.xLow = xLow;
		this.xHigh = xHigh;
		this.nBins = binValues.length;
		this.binValues = binValues;
		
		findMinMax();

		// set defaults
		barColor = new Color( 127 , 255 , 212);
		shadowOffset = 2;
		selectionSlop = 6;
		setDragBehavior(Chart.DRAG_DOES_NOTHING);
		autoBarSpacing = false;
		applyBarShadow = false;
		drawStrings = true;
		displaySize = new Dimension(300,300);

		// set the background color
		backgroundColor	= Color.darkGray;
//		backgroundColor	= Color.white;

		setVisible(true);

		yAxis.addPlot(this);
		yAxis.addAxisListener(this);
		xAxis.addPlot(this);
		xAxis.addAxisListener(this);
		addComponentListener(this);
	}


	//------------------------------------------------------------------------------
	// 
	// setDataSeries 
	//
	public void setDataSeries(String name, double [] binValues, double xLow, double xHigh) {

		this.nBins = binValues.length;
		this.binValues = binValues;
		this.xLow = xLow;
		this.xHigh = xHigh;
		findMinMax();
		// this needs to be changed eventually... fire event.
		PlotEvent e = new PlotEvent(this,0,new Double(xLow));
		xAxis.plotRangeChanged(e);
		e = new PlotEvent(this,1,new Double(xHigh));
		xAxis.plotRangeChanged(e);
		e = new PlotEvent(this,0,new Double(yMin));
		yAxis.plotRangeChanged(e);
		e = new PlotEvent(this,1,new Double(yMax));
		yAxis.plotRangeChanged(e);
		repaint();
	}

	//------------------------------------------------------------------------------
	//
	// find the Min and the Max of both the binValues and binLabels
	//
	public void findMinMax() {
		yMin = 0.0;  // peg at zero for histograms
		yMax = -Double.MAX_VALUE;
		// find the maximum over all bins
		for(int i=0; i< binValues.length; i++) {  
			if (!(Double.isNaN(binValues[i]))) {
				if(binValues[i] > yMax){
					yMax = binValues[i];
				}
			}
		}
		if(yMax<=yMin){
			yMax = yMin + 1.0;  // MK added 2/8/99  just in case no data in given x range
		}
	}

	//------------------------------------------------------------------------------
	//
	// set the Background color
	//

	public void setBackgroud(Color color) {
		backgroundColor = color;
	}

	//------------------------------------------------------------------------------
	//
	// set the Bar color
	//
	public void setBarColor(Color color) {
		barColor = color;
	}


	//------------------------------------------------------------------------------
	//
	// set the bar spacing
	//

	public void setBarSpacing(boolean state) {
		autoBarSpacing = state;
	}
	
	//------------------------------------------------------------------------------
	//
	// set the strings to draw
	//

	public void setDrawStrings(boolean state) {
		drawStrings = state;
	}

	//------------------------------------------------------------------------------
	//
	// apply shadow to bars
	//

	public void setBarShadowing(boolean state) {
		applyBarShadow = state;
	}


	/** 
	** getRange - get the range of the data 
	**/
	
	@Override
	public Range getRange(int dimension) {
			// dimension: 1 = x dimension, 2 = y dimension
			if(dimension == 1) {
				return new Range(new Double(xLow), new Double(xHigh));
			}
			else { // dimension == 2
				return new Range(new Double(yMin), new Double(yMax));
			}
	}

	/**
	** isOpaque
	**/	
	@Override
	public boolean isOpaque() {
		return true;
	}


	/**
	** paintComponent
	**
	**/
	@Override
	public void paintComponent(Graphics g) {
		// get the region that can be seen...
		Rectangle bounds = getBounds();
		g.setColor(backgroundColor); // fill with background color: white
		int width = bounds.width; 
		int height = bounds.height; 
		int left = 0;
		int right = width;
		int top = 0;
		int bottom = height;
		g.fillRect(left,top,width,height); 
		double barWidth = (xHigh - xLow)/nBins;  // in units
		int extraSpace = 0;
		int spacing = 1;  // pixel gap between bars
		int initialOffset = 0;
		int pixelBarWidth = (int) Math.floor(((double) width/(double) nBins) - spacing);
		//System.out.println("width: " + width + " pixelBarWidth: " + pixelBarWidth );
		if(pixelBarWidth < 15) {
			drawStrings = false; 
		}
		else  drawStrings = true;
		if(pixelBarWidth == 0) { 
			pixelBarWidth = 1; // this of course is going to mess the layout up
			if(DEBUG){
				System.out.println("Plotting too much data");
			}
		}
		FontMetrics fm = getFontMetrics(getFont());
		int stringHeight = fm.getHeight();
		String s;
		double x = barWidth;
		int cy, cxEnd, cx = initialOffset;
		for (int i=0; i < nBins; i++) {
			cxEnd = (int) Math.rint(x*xAxis.units2Pixels + initialOffset) - spacing;
			cy = (int) Math.rint((bottom - (((binValues[i] - yMin) * height)/(yMax - yMin))));
			if(applyBarShadow) { // must correct spacing... if shadow is applied
				g.setColor(Color.gray);
				g.fillRect(cx + shadowOffset, cy - shadowOffset, cxEnd + shadowOffset,  bottom - cy + shadowOffset);
			}
			g.setColor(barColor);
			g.fillRect(cx, cy, cxEnd - cx, bottom - cy); 
			// draw the label -- eventually move to external loop to avoid values getting painted over
			// by following bar...
			if(drawStrings) {
				g.setColor(Color.black);
				if(binValues[i] > 0.0) {
					s = String.valueOf((int)binValues[i]);
				}
				else s = "";
				if((cy + 15) > height) { // bar is too short... place string on top of bar
					g.drawString(s, (cx + 1 + (pixelBarWidth - fm.stringWidth(s))/2), cy - 6);
					g.setColor(Color.white);
					g.drawString(s, (cx + (pixelBarWidth - fm.stringWidth(s))/2), cy - 5);
				}
				else { // put it in the bar
					g.setColor(Color.white);
					g.drawString(s, (cx + 1 + (pixelBarWidth - fm.stringWidth(s))/2), cy + 13);
					g.setColor(Color.black);
					g.drawString(s, (cx + (pixelBarWidth - fm.stringWidth(s))/2), cy + 12);
				}
			}
			cx = cxEnd + spacing;  // where next bar starts
			x += barWidth;
		}

	}


	/** print out the chart **/
	public void print() {
	//	Toolkit toolkit = this.getToolkit();
	//	PrintJob job = toolkit.getPrintJob(frame, "BarChart", printprefs);
		PrintJob pj = getToolkit().getPrintJob(null, "My Print Job", null);
		if (pj != null) {
			Graphics pg = pj.getGraphics();
			pg.drawRect (100,100,200,200);

			// the page is sent to the printer when the graphics object
			// is disposed.
			pg.dispose();
			pj.end();
		}
		// else the user canceled out of the print options dialog
	}

	/** pixel to X **/
	public double pixelToX(int px) {
		return (xAxis.pixels2Units*px);
	}

	/** pixel to Y **/
	public double pixelToY(int py) {
	//	System.out.println("Y: pixel: " + py + " is converted to :" + (yAxis.pixels2Units*(py + yAxis.min.doubleValue())) + " note min: "  + yAxis.min.doubleValue() );
		return(yAxis.pixels2Units*py);
	}


	@Override
	public boolean contains(int px, int py) {  
		int i = findPoint(px,py);
		if ((i != -1) || (i == mouseIndex)) { // if the point has changed... update tooltiptext
			double barWidth = (xHigh-xLow)/nBins;
			int digits = xAxis.sigDigits + 1;
			if (i != mouseIndex) {  // reset tool tip
				int val = (int) Math.rint(binValues[i]);
				if(val == 0){
					setToolTipText("no points, "+StringFormatter.DoubleToString(xLow+barWidth*i,digits)+ " to " + StringFormatter.DoubleToString(xLow+barWidth*(i+1),digits));
				}else if(val == 1) {
					setToolTipText(val+" point, "+StringFormatter.DoubleToString(xLow+barWidth*i,digits)+ " to " + StringFormatter.DoubleToString(xLow+barWidth*(i+1),digits));
				}else {
					setToolTipText(val+" points, "+StringFormatter.DoubleToString(xLow+barWidth*i,digits)+ " to " + StringFormatter.DoubleToString(xLow+barWidth*(i+1),digits));
				}
				mouseIndex = i;
			}
			return true;
		}
		else { // else return that nothing has changed...
			mouseIndex = -1;
			setToolTipText(null);
			return false;
		}
	}

	public int findPoint(int px, int py) { 
		//System.out.println("findPoint:px=" + px + " py="+py);
		double x = pixelToX(px);
		//System.out.println("xLow = "+xLow+" xHigh = "+xHigh+" nBins = "+nBins);
		double xIncrement = (xHigh - xLow)/nBins;
		double currentPosition = 0.0;
		int index = -1;
		for(int i = 0; i< nBins; i++) {
			currentPosition += xIncrement;
			if(x < currentPosition) { 
				index = i;
				break;
			}
		}
		return index;
	}


	@Override
	public void setPreferredSize(Dimension size) {
		super.setPreferredSize(size);
		this.displaySize = size;
	}

	@Override
	public void setMinimumSize(Dimension size) {
		super.setMinimumSize(size);
		this.displaySize = size;
	}

	@Override
	public Dimension getPreferredSize() {
		return displaySize;
	}
	@Override
	public Dimension getMinimumSize() {
		return displaySize;
	}
	
	@Override
	public void componentResized(ComponentEvent event) {}
	@Override
	public void componentHidden(ComponentEvent event) {}
   	@Override
	public void componentMoved(ComponentEvent event) {}
	@Override
	public void componentShown(ComponentEvent event) {}
	@Override
	public void axisRescaled(AxisEvent e) {}
}
