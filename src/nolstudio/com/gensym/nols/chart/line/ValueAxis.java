package com.gensym.nols.chart.line;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.text.*;

public class ValueAxis extends ChartComponent implements ComponentListener, PlotListener {
	// basic information
	private int orientation; 
	private int dimension;  // 1 = x dimension, 2 = y dimension, 3 = z dimension
	private boolean autoScale;  // determine range and ticks automatically
	private int axisType;  // int, double, or long
	private Insets insets;  
	private boolean autoInsets;
	
	// formatting information
	// Those marked by *AUTO* will be automatically determined if autoscale = true
	public Color itsColor;			 // axis color
	public DateFormat dateFormat;	 // *AUTO*  controls date format if using LONGs
	public int dateFormatVerbosity;  // either DateFormat.SHORT, .MEDIUM, or .LONG
	public NumberFormat numberFormat;   // controls integer formatting
	public int sigDigits;		     // *AUTO*  controls double formatting (since NumberFormats can't handle scientific notation!)
	public Font labelFormat;	     // font for labels
	public Number majorTickInterval; // *AUTO*  major tick interval 
	public Number majorTickOrigin;   // *AUTO*  a major tick would go through this point, if axis were infinitely long (not implemented yet) 
	public int minorTicks;           // number of minor ticks between each major tick (not yet implemented)
	public int labelPosition;        // either TOP_OR_RIGHT or BOTTOM_OR_LEFT
	public int majorTickLengthTR;
	public int majorTickLengthBL;
	public int minorTickLengthTR;
	public int minorTickLengthBL;
	public int labelOffset;          // spacing between tickmark and label
	public int minimumLabelSpacing;  // minimum space between adjacent labels, horizontal or vertical, used in autoFormatting axis
	public int maximumNumberLabels;	 // preference for how many labels when there's plenty of space, used only when autoFormatting
	
	// static variables
	public static final int HORIZONTAL = 0;
	public static final int VERTICAL = 1;
	public static final int INT_TYPE = 0;
	public static final int DOUBLE_TYPE = 1;
	public static final int LONG_TYPE = 2;
	public static final int TOP_OR_RIGHT = 0;
	public static final int BOTTOM_OR_LEFT = 1;

	// scale information -- used by plots
	public Number min;
	public Number max;
	public double units2Pixels;
	public double pixels2Units;

	// internal data
	private Vector itsPlots;
	private Vector maxima;
	private Vector minima;
	transient Vector itsListeners;
	private int nPlots;
	private int hold;
	private int nTicks;  // number of ticks to use when autoscaling
	private double rangePadding;  // extra fraction of data range to add to top and bottom of double axis

	// private static data
	private static double inverseLn10 = 1.0/Math.log(10.0); //0.43429..
	private static double second = 1000.;
	private static double minute = 60000.;
	private static double hour = 3600000.;
	private static double day = 86400000.;

	private static final boolean DEBUG = false;


	public ValueAxis (int axisType, int dimension, int orientation) {
		super();
		this.dimension = dimension;
		this.orientation = orientation;
		this.axisType = axisType;
		itsPlots = new Vector(0,10);
		maxima = new Vector(0,10);
		minima = new Vector(0,10);
		itsListeners = new Vector(0, 10);
		insets = new Insets(0,0,0,0);
		autoScale = true;
		autoInsets = true;
//		setVisible(true);
		addComponentListener(this);
		min = null;
		max = null;
		nPlots = 0;
		hold = 0;
		nTicks = 5;
		// default format information
		itsColor = Color.white;
		dateFormatVerbosity = DateFormat.SHORT;
		dateFormat = DateFormat.getDateTimeInstance(dateFormatVerbosity, dateFormatVerbosity);
		numberFormat = NumberFormat.getInstance();
		sigDigits = 3;
		labelFormat = new Font("SansSerif", Font.PLAIN, 10);
		majorTickInterval = null; 
		minorTicks = 3;           
		labelPosition = ValueAxis.BOTTOM_OR_LEFT;        
		majorTickLengthTR = 0;
		majorTickLengthBL = 4;
		minorTickLengthTR = 0;
		minorTickLengthBL = 2;
		labelOffset = 3;
		minimumLabelSpacing = 8;
		maximumNumberLabels = 5;
		setDragBehavior(Chart.DRAG_CREATES_SELECTION_BOX);
		rangePadding = 0.05;  // by default, add 5% to range for double axis
	}

	public void setRangePadding(double pad) {
		rangePadding = pad;
	}

	public double getRangePadding() {
		return rangePadding;
	}

	public void setColor(Color color) {
		itsColor = color;
	}

	public Color getColor() {
		return itsColor;
	}

	public int getOrientation() {
		return orientation;
	}

	public int getDimension() {
		return dimension;
	}

	public int getAxisType() {
		return axisType;
	}

	public void setAxisType(int axisType) {
		if (this.axisType == axisType) {
			return;
		}
		this.axisType = axisType;
		min = null;
		max = null;
		// force update of minima/maxima
		if (autoScale) {
			setAutoScale(false);  // clears maxima/minima
			setAutoScale(true);   // sets up new max/min and rescales
		}
	}

	public void addPlot(Plot p) {
		itsPlots.addElement(p);
		++nPlots;
		p.addPlotListener(this);
		if (autoScale) {
			Range r = p.getRange(dimension);
			// should verify that correct type was returned
			minima.addElement(r.lowerBound);
			maxima.addElement(r.upperBound);
			calcRange();
		}
	}

	public void removePlot(Plot p) {
		int j = itsPlots.indexOf(p);
		itsPlots.removeElementAt(j);
		--nPlots;
		p.removePlotListener(this);
		if (autoScale) {
			minima.removeElementAt(j);
			maxima.removeElementAt(j);
			calcRange();
		}
	}

	@Override
	public void setBounds(Rectangle r) {
		if(r.equals(getBounds())) {
			return;
		}
		super.setBounds(r);
		calcScaleFactors();
	}

	@Override
	public void setBounds(int x, int y, int width, int height) {
		Rectangle r = getBounds();
		if(x==r.x && y==r.y && width==r.width && height==r.height) {
			return;
		}
		super.setBounds(x,y,width,height);
		calcScaleFactors();
	}

	public void setRange(Range r) {
		// ignore if autoscaling
		if (autoScale) 
			return;
		if(r.lowerBound.equals(min) && r.upperBound.equals(max)) 
			return;
		min = r.lowerBound;
		max = r.upperBound;
//		System.out.println(" setRange min="+min+" max="+max);
		calcScaleFactors();
	}

	public Number pixelToCoordinate(final int pixel) {
		// find the coordinate at given pixel position, relative to the origin of the component
		// convert to number of pixels from axis origin
		int pixelIndex = pixel;
		if (orientation == ValueAxis.HORIZONTAL) {
			pixelIndex = pixelIndex - insets.left;  
		} else {
			pixelIndex = getSize().height - pixelIndex - insets.bottom;
		}
		
		if (axisType == ValueAxis.LONG_TYPE) {
			return  min.longValue() + Math.round(pixelIndex*pixels2Units);
		} else if (axisType == ValueAxis.INT_TYPE) {
			// find coordinate at or below the given pixel (i.e. use floor)
			return min.intValue() + (int) Math.floor(pixelIndex*pixels2Units);
		} else {
			return min.doubleValue() + pixelIndex*pixels2Units;
		}
	}

	public boolean getAutoScale() {
		return autoScale;
	}

	public void setAutoScale(boolean autoScale) {
		if (this.autoScale == autoScale){
			return;
		}
		this.autoScale = autoScale;
		if (autoScale) {
			// build maxima and minima vectors
			Plot p;
			for (int i=0; i<itsPlots.size(); ++i) {
				p = (Plot) itsPlots.elementAt(i);
				Range r = p.getRange(dimension);
				minima.addElement(r.lowerBound);
				maxima.addElement(r.upperBound);
			}
			calcRange();
		} else {
			// freeze axis at current max/min, so no re-calculation of scale factors
			minima.removeAllElements();
			maxima.removeAllElements();
		}
	}

	public void setAutoInsets(boolean autoInsets) {
		// controls whether to adjust length of axis to allow labels at ends of axis to 
		// completely show. This should generally be true, except when axis is inside a scroll pane.
		if (!autoInsets) {
			insets.left = 0;
			insets.right = 0;
			insets.top = 0;
			insets.bottom = 0;
		}
		this.autoInsets = autoInsets;
	}

	@Override
	public Insets getInsets() {
		return (Insets) insets.clone();
	}

	public void addAxisListener(AxisListener l) {
		itsListeners.addElement(l);
	}

	public void removeAxisListener(AxisListener l) {
		itsListeners.removeElement(l);
	}

	private void calcRange() {
		if (hold > 0 || !autoScale){
			return;
		}
		Number newMin, newMax;
		boolean newRange = false;
		if(axisType == ValueAxis.LONG_TYPE) {
			long currentMin = Long.MAX_VALUE;
			long currentMax = Long.MIN_VALUE;
			long thisMin, thisMax;
			for (int i=0; i<nPlots; ++i) {
				thisMin = ((Number) minima.elementAt(i)).longValue();
				thisMax = ((Number) maxima.elementAt(i)).longValue();
				if (thisMin < currentMin){
					currentMin = thisMin;
				}
				if (thisMax > currentMax){
					currentMax = thisMax;
				}
			}
			newMin = currentMin;
			newMax = currentMax;
		} else if (axisType == ValueAxis.INT_TYPE) {
			int currentMin = Integer.MAX_VALUE;
			int currentMax = Integer.MIN_VALUE;
			int thisMin, thisMax;
			for (int i=0; i<nPlots; ++i) {
				thisMin = ((Number) minima.elementAt(i)).intValue();
				thisMax = ((Number) maxima.elementAt(i)).intValue();
				if (thisMin < currentMin){
					currentMin = thisMin;
				}
				if (thisMax > currentMax) {
					currentMax = thisMax;
				}
			}
			newMin = currentMin;
			newMax = currentMax;
		} else {  // double 
			double currentMin = Double.MAX_VALUE;
			double currentMax = Double.NEGATIVE_INFINITY;
			double thisMin, thisMax;
			for (int i = 0; i < nPlots; ++i) {
				thisMin = ((Number) minima.elementAt(i)).doubleValue();
				thisMax = ((Number) maxima.elementAt(i)).doubleValue();
				if (thisMin < currentMin){
					currentMin = thisMin;
				}
				if (thisMax > currentMax){
					currentMax = thisMax;
				}
			}
			// System.out.println("min = "+currentMin+" max = "+currentMax);
			// add a little top and bottom padding, added Oct. 16, 1998 by bbush and mkramer
			if(Double.compare(currentMin, Double.MAX_VALUE) != 0 && Double.compare(currentMax, Double.NEGATIVE_INFINITY) != 0) {
				double pad = rangePadding * Math.abs(currentMax - currentMin);
				currentMax += pad;
				currentMin -= pad;
			}
			//System.out.println("with padding, min = "+currentMin+" max = "+currentMax);
			newMin = currentMin;
			newMax = currentMax;			
			//System.out.println("new min = "+newMin.toString()+", max = "+newMax.toString());
		}
		// now compare range with current range
		// don't adjust range for small changes  (not implemented!)
		if (min == null || !min.equals(newMin)) {
			min = newMin;
			newRange = true;
		}
		if (max == null || !max.equals(newMax)) {
			max = newMax;
			newRange = true;
		}
		if (newRange){
			calcScaleFactors();
		}
		//System.out.println("ValueAxis-calcRange: min=" + min + " max=" + max);
	}

	private void calcScaleFactors() {
		double oldScaleFactor = units2Pixels;
		calcScaleFactorsOnly();
		// broadcast rescale event to listeners
		if (Double.compare(units2Pixels, oldScaleFactor) != 0) {
			AxisEvent event = new AxisEvent(this, AxisEvent.RESCALED);
			for (int i=0; i<itsListeners.size(); ++i) {
				((AxisListener) itsListeners.elementAt(i)).axisRescaled(event);
			}
		}
	}


	private void calcScaleFactorsOnly() {
		//System.out.println("calc scale, axis type = "+axisType);
		if (hold > 0 || min == null || max == null) {
			return;
		}
		Dimension totalSize = getSize();
		int totalLength;
		double span;
		if (orientation == ValueAxis.HORIZONTAL) {
			totalLength = totalSize.width - insets.left - insets.right;
		}else {
			totalLength = totalSize.height - insets.top - insets.bottom;
		}
		if (totalLength == 0) {
			totalLength = 200;  // a harmless bootstrapping assumption
		}
//	System.out.println("calcScaleFactors total length = "+totalLength);
		if(axisType == ValueAxis.INT_TYPE){
			span = (double) (max.intValue() - min.intValue());
		}else if (axisType == ValueAxis.LONG_TYPE){
			span = (double) (max.longValue() - min.longValue());
		}else {
			span = max.doubleValue() - min.doubleValue();
		}
		units2Pixels =  totalLength/span;
		pixels2Units = 1.0/units2Pixels;
		//if (orientation == ValueAxis.HORIZONTAL) System.out.println("calcScaleFactors pixels2Units = "+pixels2Units);
		if (autoScale){
			autoFormat();
		}
	}

	@Override
	public Dimension getMinimumSize() {
		// determine the minimum size of the axis based on size and labels
		// this is a request to the layout manager
		// the insets are adjusted here ONLY, because it is assumed the layout is in progress, 
		// which is the only safe time to change the insets
		int width, height;
		Dimension labelSize = getLabelSize();
		int labelWidth = labelSize.width;
		int labelHeight = labelSize.height;
		//System.out.println("label size = "+labelSize.toString());
		if (orientation == ValueAxis.HORIZONTAL) {
			width = (labelWidth + minimumLabelSpacing)*nTicks;
			height = labelHeight + majorTickLengthBL + majorTickLengthTR + labelOffset;
			if (autoInsets) {
				insets.top = 0;
				insets.bottom = 0;
				insets.left = labelWidth/2;
				insets.right = insets.left;
			}
		} else {
			width = labelWidth + majorTickLengthBL + majorTickLengthTR + labelOffset;
			height = (labelHeight + minimumLabelSpacing)*nTicks;
			if (autoInsets) {
				insets.right = 0;
				insets.left = 0;
				insets.top = labelHeight/2;
				insets.bottom = insets.top;
			}
		}
		//System.out.println("axis min size = ("+width+", "+height+")");
		return new Dimension(width, height);
	}


	private void autoFormat() {
		// determines the major tick interval, sigDigits, dateFormat
		// because this might be called before the axis has been sized and initialized,
		// there is an attempt to force at least some approximate formats to be calculated,
		// even if they are not completely correct, so layout can happen.  However,
		// if max and min aren't set yet, return
		if (min == null || max == null){
			return;
		}
		double span;
		if(axisType == ValueAxis.INT_TYPE){
			span = (double) (max.intValue() - min.intValue());
		}else if (axisType == ValueAxis.LONG_TYPE){
			span = (double) (max.longValue() - min.longValue());
		}else {
			span = max.doubleValue() - min.doubleValue();
		}
		Dimension totalSize = getSize();
		int totalLength, visibleLength;
		if (orientation == ValueAxis.HORIZONTAL){
			totalLength = totalSize.width - insets.left - insets.right;
		}else {
			totalLength = totalLength = totalSize.height - insets.top - insets.bottom;	
		}
		
		if (totalLength == 0){
			totalLength = 200;  // assumption for bootstrapping
		}
		
		Rectangle visibleSize;
		if (itsChart != null) {
			visibleSize = itsChart.getVisiblePortion(this);
		}else{
			visibleSize = new Rectangle(0,0,200,200);  // bootstrapping assumption
		}
		
		if (orientation == ValueAxis.HORIZONTAL){
			visibleLength = visibleSize.width;
		}else{
			visibleLength = visibleSize.height;
		}
		if (visibleLength == 0) {
			visibleLength = totalLength;  // another bootstrapping assumption
		}
		//System.out.println("visible length = "+visibleLength+", totalLength ="+totalLength);
		// determine the dateFormat and sigDigits based on the range of values displayed
		if (axisType == ValueAxis.DOUBLE_TYPE) {	
			// determine number of digits to show, e.g. if the axis labels are 10.0001, 10.0002, etc. then six digits are required
			// the formula is based on looking at the number of digits in the ratio of start or end value to the range of values actually displayed
			// e.g., if the axis values are order 10, and the range is 0.01, the ratio has 4 digits
			// in this case, 5 significant digits are required, since the labels will be 10.002, 10.004, etc. (hence the +1).  
			// never less than 3 digits!
			double range = pixels2Units*visibleLength;
			double scale = Math.max(Math.abs(min.doubleValue()),Math.abs(max.doubleValue()));
			sigDigits = Math.max(3, (int) Math.ceil(ValueAxis.inverseLn10*Math.log(scale/range)) + 1);
			//System.out.println("range = "+range+", scale = "+scale+", digits = "+sigDigits);
		} else if (axisType == ValueAxis.LONG_TYPE) {
			// set date/time formatting
			// similar to above, if the range in is days, we drop the hours
			long range = (long) Math.round(pixels2Units*visibleLength);
			if (range > ValueAxis.hour){
				dateFormat = DateFormat.getDateTimeInstance(dateFormatVerbosity, dateFormatVerbosity);
			} else {
				dateFormat = DateFormat.getTimeInstance(dateFormatVerbosity);
			}
		}
		Dimension labelSize = getLabelSize();
		// determine number of ticks based on size of axis/labels
		// we'd like to keep about 5 labels, unless they're too tightly packed
		// the formula is nticks*labelsize + (nticks - 1)*spacebetween <= available space
		double approxNTicks;
		if (orientation == ValueAxis.HORIZONTAL){
			approxNTicks = ((double) (totalSize.width + minimumLabelSpacing))/((double) (labelSize.width + minimumLabelSpacing));
		} else {
			approxNTicks = ((double) (totalSize.height + minimumLabelSpacing))/((double) (labelSize.height + minimumLabelSpacing));
		}
		
		if (approxNTicks > (double) maximumNumberLabels) {
			nTicks = maximumNumberLabels;
		} else if (approxNTicks < 1.0){
			nTicks = 1;
		} else {
			nTicks = (int) Math.floor(approxNTicks);
		}
		// Now determine the majorTickInterval, which is in units
		if(axisType == ValueAxis.DOUBLE_TYPE) {
			double approxTick = span*visibleLength/((double) totalLength*nTicks);
			double floorPower10 = Math.pow(10.0, Math.floor(ValueAxis.inverseLn10*Math.log(approxTick)));
			double tick = floorPower10*Math.round(approxTick/floorPower10);
			majorTickInterval = tick;
		} else if (axisType == ValueAxis.INT_TYPE) {
			double approxTick = span*(double) visibleLength/((double) totalLength*nTicks);
			double floorPower10 = Math.pow(10.0, Math.floor(ValueAxis.inverseLn10*Math.log(approxTick)));
			int tick = (int) Math.rint(floorPower10*Math.round(approxTick/floorPower10));
			if (tick < 1){
				tick = 1;
			}
			majorTickInterval = tick;
		} else { // long
			double timeSpan = span*(double) visibleLength/(double) totalLength;
			double approxTick = timeSpan/nTicks;
			// put in terms of days, hours, minutes or seconds
			double timeBasis;
			if (approxTick > ValueAxis.day) {
				timeBasis = ValueAxis.day;
			} else if (approxTick > ValueAxis.hour) {
				timeBasis = ValueAxis.hour;
			} else if (approxTick > ValueAxis.minute) {
				timeBasis = ValueAxis.minute;
			} else {
				timeBasis = ValueAxis.second;
			}
			
			long tick = (long) Math.round(timeBasis*Math.round(approxTick/timeBasis));
			if (tick < 1){
				tick = 1;
			}
			majorTickInterval = tick;
		}
	}
	
	private Dimension getLabelSize() {
		// returns an approximate maximum label size based on generating labels for max & min values
		// requires dateFormat, sigDigits, or numberFormat as prerequisite
		// there is no wrapping of dates onto multiple lines, for now
		if(min == null || max == null) {
			return new Dimension(0,0);
		}
		FontMetrics fontMetrics = getFontMetrics(labelFormat);
		int charHeight = fontMetrics.getAscent();
		int labelWidth1, labelWidth2;
		if (axisType == ValueAxis.LONG_TYPE) {
			labelWidth1 = fontMetrics.stringWidth(dateFormat.format(new Date(min.longValue())));
			labelWidth2 = fontMetrics.stringWidth(dateFormat.format(new Date(max.longValue())));
		} else if (axisType == ValueAxis.INT_TYPE) {
			labelWidth1 = fontMetrics.stringWidth(numberFormat.format(min.intValue()));
			labelWidth2 = fontMetrics.stringWidth(numberFormat.format(max.intValue()));
		} else {
			labelWidth1 = fontMetrics.stringWidth(StringFormatter.DoubleToString(min.doubleValue(), sigDigits));
			labelWidth2 = fontMetrics.stringWidth(StringFormatter.DoubleToString(max.doubleValue(), sigDigits));
		}
		int labelWidth = Math.max(labelWidth1, labelWidth2);
		return new Dimension(labelWidth, charHeight);
	}


	@Override
	public void paintComponent(Graphics g) {
		//System.out.println("painting axis type "+axisType+", min="+min+" max="+max);
		calcScaleFactorsOnly();  // WHO PUT THIS HERE?  WHY IS IT NECESSARY?  - MK
		if(majorTickInterval == null) {
			return;  // safety measure 
		}
		Rectangle clip = g.getClipBounds();
		//System.out.println("painting value axis, clip.x = "+clip.x+", clip.width = "+clip.width);
		Dimension size = getSize();
		g.setColor(itsColor);
		g.setFont(labelFormat);
		FontMetrics fontMetrics = getFontMetrics(labelFormat);
		int charHeight = fontMetrics.getAscent();  // getMaxAscent??
		String label;
		int labelWidth, tickLocation, lastTickLocation, labelBaseline, labelEdgePosition, baseline, pixelStart, pixelEnd;
		int padding; // amount by which we increase clip to capture entire label
		boolean horizontal, belowleft;
		if (orientation == ValueAxis.HORIZONTAL){
			horizontal = true; 
		}else {
			horizontal = false;
		}
		
		if (labelPosition == ValueAxis.BOTTOM_OR_LEFT){
			belowleft = true;
		}else {
			belowleft = false;
		}
		
		int tickLength = majorTickLengthTR + majorTickLengthBL;
		if (horizontal) {
			Rectangle visibleSize = itsChart.getVisiblePortion(this);
			padding = visibleSize.width/nTicks;  // approx. the tick-to-tick length
			pixelStart = Math.max(0, clip.x - padding);
			pixelEnd = Math.min(size.width, clip.x + clip.width + padding);
			if (belowleft) {  // label below
				baseline = majorTickLengthTR;
				labelBaseline = tickLength + labelOffset + charHeight - 1;	 // to bottom of character
				// added -1 to above calculation to avoid clipping the "," in the numbers by bbush, Oct 30, 1998
			} else {  // label above
				baseline = size.height - majorTickLengthBL;
				labelBaseline = size.height - tickLength - labelOffset;
			}
			g.drawLine(insets.left, baseline, size.width - insets.right, baseline);
			//System.out.println("pixel start = "+pixelStart+", pixel end = "+pixelEnd);
		} else {
			padding = charHeight;
			pixelStart = Math.max(size.height, clip.y + clip.height + padding);
			pixelEnd = Math.min(0, clip.y - padding);
			if (belowleft) { // label left of axis, right sides aligned
				baseline = size.width - majorTickLengthTR - 1;   // -1 to compensate for width of line
				labelBaseline = size.width - tickLength - labelOffset; // right edge position
			} else {  // label to right of axis, left sides aligned
				baseline = majorTickLengthBL;
				labelBaseline = tickLength + labelOffset;  // left edge position
			}
			g.drawLine(baseline, insets.top, baseline, size.height - insets.bottom);
		}
		if (horizontal) {
			lastTickLocation = Integer.MIN_VALUE;
		}else {
			lastTickLocation = Integer.MAX_VALUE;  // since paint from bottom up (higher pixels to lower)
		}
		// now iterate through major ticks (different for different data types)
		if (axisType == ValueAxis.LONG_TYPE) {
			long tickInt = majorTickInterval.longValue();
			long tmin = min.longValue();
			long tmax = max.longValue();
			long startTime, endTime;
			if (horizontal) {
				startTime = Math.round(pixels2Units*pixelStart) + tmin;
				endTime = Math.round(pixels2Units*pixelEnd) + tmin;
			} else {
				startTime = tmax - Math.round(pixels2Units*pixelStart);
				endTime = tmax - Math.round(pixels2Units*pixelEnd);
			}
			long tick = tickInt * (long) Math.ceil((double) startTime/tickInt);
			while(tick < endTime) {
				label = dateFormat.format(new Date(tick));
				if (horizontal) {
					tickLocation = (int) Math.round(units2Pixels*(tick - tmin)) + insets.left;
				}else {
					tickLocation = (int) Math.round(units2Pixels*(tmax - tick)) + insets.top;
				}
				drawMajorTick(g, tickLocation, tickLength, size, label, labelBaseline, fontMetrics);
				drawMinorTicks(g, baseline, lastTickLocation, tickLocation, size);
				tick += tickInt;
				lastTickLocation = tickLocation;
			}
		} else if (axisType == ValueAxis.INT_TYPE) {
			int tickInt = majorTickInterval.intValue();
			int rmin = min.intValue();
			int rmax = max.intValue();
			int startRow, endRow;
//System.out.println("pixelStart = "+pixelStart+", pixels2Units = "+pixels2Units);
			if (horizontal) {
				startRow = (int) Math.round(pixels2Units*pixelStart) + rmin;
				endRow= (int) Math.round(pixels2Units*pixelEnd) + rmin;
			} else {
   				startRow = rmax - (int) Math.round(pixels2Units*pixelStart);
				endRow = rmax - (int) Math.round(pixels2Units*pixelEnd);
			}
			int tick = tickInt* (int) Math.ceil((double) startRow/tickInt);
			while(tick < endRow) {
				label = numberFormat.format(tick);
				if (horizontal) {
					tickLocation = (int) Math.round(units2Pixels*(tick - rmin)) + insets.left;
				}else {
					tickLocation = (int) Math.round(units2Pixels*(rmax - tick)) + insets.top;
				}
//System.out.println("tick = "+tick+", tickLocation = "+tickLocation);
				drawMajorTick(g, tickLocation, tickLength, size, label, labelBaseline, fontMetrics);
				drawMinorTicks(g, baseline, lastTickLocation, tickLocation, size);
				tick += tickInt;
				lastTickLocation = tickLocation;
			}
		} else {
			double tickInt = majorTickInterval.doubleValue();
			double dmin = min.doubleValue();
			double dmax = max.doubleValue();
			double startVal, endVal;
			if (horizontal) {
				startVal = pixels2Units*pixelStart + dmin;
				endVal= pixels2Units*pixelEnd + dmin;
			} else {
		   		startVal = dmax - pixels2Units*pixelStart;
				endVal= dmax - pixels2Units*pixelEnd;
			}
			double tick = tickInt* Math.ceil(startVal/tickInt);
			while(tick < endVal) {		 
				label = StringFormatter.DoubleToString(tick, sigDigits);
				if (horizontal) {
					tickLocation = (int) Math.round(units2Pixels*(tick - dmin)) + insets.left;
				} else {
					tickLocation = (int) Math.round(units2Pixels*(dmax - tick)) + insets.top;
				}
				drawMajorTick(g, tickLocation, tickLength, size, label, labelBaseline, fontMetrics);				
				drawMinorTicks(g, baseline, lastTickLocation, tickLocation, size);
				tick += tickInt;
				lastTickLocation = tickLocation;
			}
		}
		if (horizontal) {
			drawMinorTicks(g, baseline, lastTickLocation, Integer.MAX_VALUE, size);
		} else {
			drawMinorTicks(g, baseline, lastTickLocation, Integer.MIN_VALUE, size); // plot remaining minor ticks
		}
	}

	private void drawMajorTick(Graphics g, int tickLocation, int tickLength, Dimension size, String label, int labelBaseline, FontMetrics fontMetrics) {
		// make sure tick is inside the proper bounds
		if (orientation == ValueAxis.HORIZONTAL) {
			if (tickLocation < insets.left || tickLocation > size.width - insets.right){
				return;
			}
		} else {
			if (tickLocation < insets.top || tickLocation > size.height - insets.bottom){
				return;
			}
		}
		int labelEdgePosition;
		int labelWidth = fontMetrics.stringWidth(label);
		int labelHeight = fontMetrics.getAscent(); 
		if (orientation == ValueAxis.HORIZONTAL) {
			if (labelPosition == ValueAxis.BOTTOM_OR_LEFT){
				g.drawLine(tickLocation, 0, tickLocation, tickLength);
			} else {
				g.drawLine(tickLocation, size.height - tickLength, tickLocation, size.height);
			}
			labelEdgePosition = tickLocation - labelWidth/2;
			if (labelEdgePosition >= 0 && labelEdgePosition + labelWidth <= size.width){
				g.drawString(label,labelEdgePosition, labelBaseline);
			}
		} else {
			if (labelPosition == ValueAxis.BOTTOM_OR_LEFT) {
				g.drawLine(size.width - tickLength, tickLocation, size.width, tickLocation);
			} else {
				g.drawLine(0, tickLocation, tickLength, tickLocation);
			}
			labelEdgePosition = tickLocation + labelHeight/2;
			if (labelEdgePosition - labelHeight >= 0 && labelEdgePosition <= size.height) {
				if (labelPosition == ValueAxis.BOTTOM_OR_LEFT){
					g.drawString(label, labelBaseline - labelWidth, labelEdgePosition);
				}else {
					g.drawString(label, labelBaseline, labelEdgePosition);
				}
			}
		}
	}

	private void drawMinorTicks(final Graphics g, final int baseline, final int tickLocation1, 
			final int tickLocation2, final Dimension size) {
		// give location of one major tick, fill in all minor tickmarks
		int tickIndex1 = tickLocation1;
		int tickIndex2 = tickLocation2;
		if (minorTicks == 0 || minorTickLengthTR == 0 && minorTickLengthBL == 0) {
			return;   // nothing to draw
		}
//System.out.println("at 1, drawing ticks from "+tickLocation1+" to "+tickLocation2);
		if (tickIndex1 > tickIndex2) {
			int temp = tickIndex1;
			tickIndex1 = tickIndex2;
			tickIndex2 = temp;
		}
		int tickLocation, lowerBound, upperBound;
		if (orientation == ValueAxis.HORIZONTAL) {
			lowerBound = insets.left;
			upperBound = size.width - insets.right;
		} else {
			lowerBound = insets.top;
			upperBound = size.height - insets.bottom;
		}
		if (tickIndex1 == Integer.MIN_VALUE) // draw remaining ticks to the left or top
			tickIndex1 = tickIndex2 - (int) Math.rint(units2Pixels*majorTickInterval.doubleValue());
		else if (tickIndex2 == Integer.MAX_VALUE) // draw remaining ticks to the right or bottom
			tickIndex2 = tickIndex1 + (int) Math.rint(units2Pixels*majorTickInterval.doubleValue());
		if (tickIndex1 == tickIndex2) {
			return;
		}
		double interval = ((double) (tickIndex2 - tickIndex1))/(minorTicks + 1);
		for (int i=1; i<=minorTicks; ++i) {
			tickLocation = tickIndex1 + (int) Math.round(i*interval);
			if (tickLocation >= lowerBound && tickLocation <= upperBound) {
				if (orientation == ValueAxis.HORIZONTAL) {
					g.drawLine(tickLocation, baseline - minorTickLengthTR, tickLocation, baseline + minorTickLengthBL);
				}else {
					g.drawLine(baseline - minorTickLengthBL, tickLocation, baseline + minorTickLengthTR, tickLocation);
				}
			}
		}
	}

	@Override
	public Rectangle getSelectionBoxConstraints() {
		Rectangle r = itsChart.getVisiblePortion(this);
		Plot p;
		for (int i=0; i<itsPlots.size(); ++i) {
			p = (Plot) itsPlots.elementAt(i);
			r = r.union(itsChart.getVisiblePortion(p));
		}
		return r;
	}

	@Override
	public int getSelectionBoxStyle() {
		return Chart.FILL_STYLE;
	}

	@Override
	public int getSelectionBoxBehavior(){
		if (orientation == ValueAxis.HORIZONTAL) {
			return Chart.VERTICAL_BEHAVIOR;
		}else {
			return Chart.HORIZONTAL_BEHAVIOR;
		}
	}

	// Event Listeners

	@Override
	public void plotRangeChanged(PlotEvent e) {
		//if (orientation == ValueAxis.HORIZONTAL) System.out.println("xaxis got range changed event");
		if (!autoScale) {
			return;
		}
		Plot p = e.getPlot();
		int j = itsPlots.indexOf(p);
		if (e.getType() == PlotEvent.NEW_MINIMUM){
			minima.setElementAt(e.getValue(), j);
		} else if (e.getType() == PlotEvent.NEW_MAXIMUM) {
			maxima.setElementAt(e.getValue(), j);
		}
		//if (orientation == ValueAxis.HORIZONTAL) System.out.println("\t   new min="+min+" max="+max);
		calcRange();
	}

	@Override
	public void componentResized(ComponentEvent event) {
		//if (orientation == ValueAxis.HORIZONTAL) System.out.println("valueAxis componentResized");
		// this is to make sure axis rescales when it is resized
		calcScaleFactors();
	}
	@Override
	public void componentHidden(ComponentEvent event) {}
   	@Override
	public void componentMoved(ComponentEvent event) {}
	@Override
	public void componentShown(ComponentEvent event) {}

}

