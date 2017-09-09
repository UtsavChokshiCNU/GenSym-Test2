package com.gensym.nols.chart.line;

import java.awt.*;
import java.awt.event.*;
import java.text.*;
import javax.swing.JComponent;

public class ConsoleLineChart extends JComponent implements ComponentListener{
	public int maxMarkerForegroundSize;
	public int minMarkerForegroundSize;
	public int maxMarkerBackgroundSize;
	public int minMarkerBackgroundSize;
	private int backgroundSize;

	public boolean autoscaleMarker;
	private long[] times;
	private double[] yData;
	private double ymin;
	private double ymax;
	private int nData;
	private int mouseIndex;
	private Range yrange;
	private Font labelFormat;	     // font for labels
	private NumberFormat numberFormat;   // controls integer formatting
	private int sigDigits;		     // *AUTO*  controls double formatting (since NumberFormats can't handle scientific notation!)
	
	
	private int majorTickLengthTR;
	private int majorTickLengthBL;
	private int minorTickLengthTR;
	private int minorTickLengthBL;
	private int labelOffset;          // spacing between tickmark and label
	private int minimumLabelSpacing;  // minimum space between adjacent labels, horizontal or vertical, used in autoFormatting axis
	private int maximumNumberLabels;	 // preference for how many labels when there's plenty of space, used only when autoFormatting
	
	// static variables
	private static int HORIZONTAL = 0;
	private static int VERTICAL = 1;
	private static int INT_TYPE = 0;
	private static int DOUBLE_TYPE = 1;
 	private static double inverseLn10 = 1.0/Math.log(10.0); //0.43429..

	private static final boolean DEBUG = false;



	public ConsoleLineChart(String name, long[] t, double[] y) {
		super();
		nData = y.length;
		if (t.length != nData){
			throw new IllegalArgumentException("arrays were unequal length");
		}
		yData = y;
		times = t;
		yrange = getRange();

		mouseIndex = -1;  // represents point which the mouse is over
		// default limits on marker size
		maxMarkerForegroundSize = 6;
		minMarkerForegroundSize = 0;
		maxMarkerBackgroundSize = 10;
		minMarkerBackgroundSize = 2;
		autoscaleMarker = true;
		resizeMarker();

		majorTickLengthTR = 0;
		majorTickLengthBL = 4;
		minorTickLengthTR = 0;
		minorTickLengthBL = 2;
		backgroundSize = 4;
		labelOffset = 3;
		minimumLabelSpacing = 8;
		maximumNumberLabels = 5;

		labelFormat = new Font("SansSerif", Font.PLAIN, 10);
		numberFormat = NumberFormat.getInstance();
		sigDigits = 3;
	}	


	public void setData(long[] t, double[] y){
		nData = y.length;
		if (t.length != nData){
			throw new IllegalArgumentException("arrays were unequal length");
		}
		yData = y;
		times = t;
		yrange = getRange();
		repaint(0L);
	}

	public Range getRange() {
		ymin = Double.MAX_VALUE;
		ymax = Double.NEGATIVE_INFINITY;
		for (int j=0; j < nData; ++j) {
			if (!(Double.isNaN(yData[j]))) {
				if (yData[j] < ymin){
					ymin = yData[j];
				}
				if (yData[j] > ymax){
					ymax = yData[j];
				}
			}
		}
	// just in case all points are NaN or plot is zero length, return some sensible default
		if (Double.compare(ymin, Double.MAX_VALUE) == 0 || Double.compare(ymax, -Double.MAX_VALUE) == 0) {   //Gchen 5/12/98
			ymin = 0.0;
			ymax = 1.0;
		}
	// System.out.println("get range, dimension="+dimension+" ymin="+ymin+" ymax="+ymax);
		return new Range(new Double(ymin), new Double(ymax));
	}

 	@Override
	public boolean isOpaque(){
		return false;
	}

	@Override
	public void paintComponent(Graphics g) {
		// Get the size for axises.

		Dimension xdim = getMinimumSizeForAxis(HORIZONTAL);
		Dimension ydim = getMinimumSizeForAxis(VERTICAL);
		Dimension totalSize = getSize();

		boolean prevIsaNum = true;
		boolean thisIsaNum = true;
		int startIndex = 0;
  		int endIndex = nData - 1;


		int xtotalLength = totalSize.width - ydim.width -10;
		int ytotalLength = totalSize.height - xdim.height - 10;

		g.setColor(Color.darkGray);
		g.fillRect(ydim.width+5,5,xtotalLength,ytotalLength);


		g.setColor(Color.green);

		double span = (ymax - ymin);
		if(Double.compare(span, 0.0)== 0) 
			span = 2.0;
		double y2Pixels = ytotalLength/span;
		double x2Pixels = ((double)xtotalLength)/nData;

		int prevx = ydim.width+5;
		int prevy = 0;
		int thisx = ydim.width+5;
		int thisy = 0;

		if (!(Double.isNaN(yData[startIndex]))) {
			prevy = (int) Math.rint(y2Pixels*(ymax - yData[startIndex]))+5;
			// MK 1/31/99: draw symbol if i==0 (special case -- otherwise first point in not selectable)
			if(startIndex==0) {
				thisy = (int) Math.rint(y2Pixels*(ymax - yData[0]))+5;
				drawMarker(g, thisx, thisy);
			}
		} else prevIsaNum = false;

		boolean thisyready=  true;


		// now the core drawing loop
		for (int i = startIndex + 1; i <= endIndex; ++i) {
			thisx = (int) Math.rint(x2Pixels*i)+ydim.width+5;
			thisyready = false;
			if (!(Double.isNaN(yData[i]))) {
				thisy = (int) Math.rint(y2Pixels*(ymax - yData[i]))+5; 
				thisyready = true;  // referenced below
				drawMarker(g, thisx, thisy);
				thisIsaNum = true;
			} else {
				thisIsaNum = false;			
			}
			if (prevIsaNum && thisIsaNum){
				g.drawLine(prevx, prevy, thisx, thisy);
			}

			//System.out.println("line from ("+prevx+","+prevy+") to ("+thisx+","+thisy+")");
			prevx = thisx;
			if (thisIsaNum){
				prevy = thisy;
			}
			prevIsaNum = thisIsaNum;
		}

		//Draw Axis. x axis first. then y axis

		g.setColor(Color.black);
		g.setFont(labelFormat);
		FontMetrics fontMetrics = getFontMetrics(labelFormat);
		int charHeight = fontMetrics.getAscent();  // getMaxAscent??
		String label;
		int labelWidth, tickLocation, lastTickLocation, labelBaseline, labelEdgePosition, baseline, pixelStart, pixelEnd;

		baseline = 	ytotalLength+5;
		g.drawLine(ydim.width+5, baseline, xtotalLength+ydim.width+5, baseline);

		int tick = 1; 
		if(nData<=5){
			tick = 1;
		}else if(nData <= 10){
			tick = 2;
		}else if(nData <= 25){
			tick = 5;
		}else if(nData <= 50){
			tick = 10;
		}else if(nData <= 100){
			tick = 20;
		}else{
			int a = nData/25 ;
			tick = a*5;
		}
		int nTicks = nData/tick;
		int tickLength = majorTickLengthTR + majorTickLengthBL;
		int tickLabelOffset = 3;
		labelBaseline = tickLength + tickLabelOffset + charHeight - 1;	 // to bottom of character
		if(tick<=2){
			for(int i=0;i<nTicks;i++){
				int tickCount = tick*(i+1);
				label = numberFormat.format(tickCount);
				tickLocation = (int) Math.round(x2Pixels*tickCount) + ydim.width+5;
				g.drawLine(tickLocation, baseline, tickLocation, baseline+tickLength);


				labelWidth = fontMetrics.stringWidth(label);
				labelEdgePosition = tickLocation - labelWidth/2;
				if (labelEdgePosition >= 0){
					g.drawString(label,labelEdgePosition, baseline+labelBaseline);
				}
			}
		}else{
			int minTick = tick/5;
			for(int i=1;i<5;i++){
				int mintickCount = minTick*i;
				tickLocation = (int) Math.round(x2Pixels*mintickCount) + ydim.width+5;
				g.drawLine(tickLocation, baseline - minorTickLengthTR, tickLocation, baseline + minorTickLengthBL);
			}
			for(int i=0;i<nTicks;i++){
				int tickCount = tick*(i+1);
				label = numberFormat.format(tickCount);
				tickLocation = (int) Math.round(x2Pixels*tickCount) + ydim.width+5;
				g.drawLine(tickLocation, baseline, tickLocation, baseline+tickLength);
				labelWidth = fontMetrics.stringWidth(label);
				labelEdgePosition = tickLocation - labelWidth/2;
				if (labelEdgePosition >= 0){
					g.drawString(label,labelEdgePosition, baseline+labelBaseline);
				}
				for(int j=1;j<5;j++){
					int mintickCount = minTick*j+tickCount;
					if(mintickCount<=nData){
						tickLocation = (int) Math.round(x2Pixels*mintickCount) + ydim.width+5;
						g.drawLine(tickLocation, baseline - minorTickLengthTR, tickLocation, baseline + minorTickLengthBL);
					}
				}
			}
		}

		int minLabelSpacing = 8;
		Dimension labelSize = getLabelSize(DOUBLE_TYPE);
		double approxNTicks = ((double) (ytotalLength + minLabelSpacing))/((double) (labelSize.height + minLabelSpacing));
		if (approxNTicks > (double) maximumNumberLabels){
			nTicks = maximumNumberLabels;
		}else if (approxNTicks < 1.0) {
			nTicks = 1;
		}else {
			nTicks = (int) Math.floor(approxNTicks);
		}
		// Now determine the majorTickInterval, which is in units

		double approxTick = (ymax-ymin)/(double)nTicks;
		double floorPower10 = Math.pow(10.0, Math.floor(inverseLn10*Math.log(approxTick)));
		double ytick = floorPower10*Math.round(approxTick/floorPower10);
		double majorTickInterval = ytick;

		baseline = 	ydim.width+5;

		g.drawLine(baseline, 5, baseline, 5+ytotalLength);

		double startVal, endVal;
		startVal = ymin;
		endVal= ymax;
		ytick = majorTickInterval* Math.ceil(startVal/majorTickInterval);
		lastTickLocation = Integer.MAX_VALUE; 
		int minorTicks = 4;
		while(ytick < endVal) {		 
			label = StringFormatter.DoubleToString(ytick, sigDigits);
			labelWidth = fontMetrics.stringWidth(label);
			int labelHeight = fontMetrics.getAscent();
			tickLocation = (int) Math.round(y2Pixels*(ymax - ytick)) + 5;
			g.drawLine(baseline - tickLength, tickLocation, baseline, tickLocation);
			labelEdgePosition = tickLocation + labelHeight/2;
			labelBaseline = baseline - tickLength - tickLabelOffset; // right edge position
			g.drawString(label, labelBaseline - labelWidth, labelEdgePosition);
			

			if (lastTickLocation == Integer.MAX_VALUE){
				lastTickLocation = tickLocation + (int) Math.rint(y2Pixels*majorTickInterval);
			}
			double interval = ((double) (lastTickLocation - tickLocation))/(minorTicks + 1);
			for (int i=1; i<=minorTicks; ++i) {
				int minortickLocation = tickLocation + (int) Math.round(i*interval);
//System.out.println("tickLocation="+tickLocation+"interva="+interval+"minortickLocation="+minortickLocation);
				if (minortickLocation >= 5 && minortickLocation <= 5+ytotalLength) {
					g.drawLine(baseline - minorTickLengthBL, minortickLocation, baseline + minorTickLengthTR, minortickLocation);
				}
			}
			ytick += majorTickInterval;
			lastTickLocation = tickLocation;
		}
	}

	
	public void resizeMarker(){
		int foregroundSize = (int) Math.rint((double) getSize().width/(double) nData);
		if (foregroundSize < minMarkerForegroundSize){
			foregroundSize = minMarkerForegroundSize;
		}
		
		if (foregroundSize > maxMarkerForegroundSize){
			foregroundSize = maxMarkerForegroundSize;
		}
		
		if (foregroundSize <= 1) {
			backgroundSize = 3;
		}else if (foregroundSize == 2) {
			backgroundSize = 4;
		}else if (foregroundSize == 3){
			backgroundSize = 6;
		}else{
			backgroundSize = foregroundSize + 4;
		}
		
		if (backgroundSize < minMarkerBackgroundSize){
			backgroundSize = minMarkerBackgroundSize;
		}
		
		if (backgroundSize > maxMarkerBackgroundSize) {
			backgroundSize = maxMarkerBackgroundSize;
		}
	}

	 

	@Override
	public void componentResized(ComponentEvent event) {}
	@Override
	public void componentHidden(ComponentEvent event) {}
   	@Override
	public void componentMoved(ComponentEvent event) {}
	@Override
	public void componentShown(ComponentEvent event) {}


	private Dimension getLabelSize(int type) {
		// returns an approximate maximum label size based on generating labels for max & min values
		// requires dateFormat, sigDigits, or numberFormat as prerequisite
		// there is no wrapping of dates onto multiple lines, for now
		FontMetrics fontMetrics = getFontMetrics(labelFormat);
		int charHeight = fontMetrics.getAscent();
		int labelWidth1, labelWidth2;
		if (type == INT_TYPE) {
			labelWidth1 = fontMetrics.stringWidth(numberFormat.format(0));
			labelWidth2 = fontMetrics.stringWidth(numberFormat.format(nData));
		} else {
			labelWidth1 = fontMetrics.stringWidth(StringFormatter.DoubleToString(ymin, sigDigits));
			labelWidth2 = fontMetrics.stringWidth(StringFormatter.DoubleToString(ymax, sigDigits));
		}
		int labelWidth = Math.max(labelWidth1, labelWidth2);
		return new Dimension(labelWidth, charHeight);
	}


	public Dimension getMinimumSizeForAxis(int orientation) {
		// determine the minimum size of the axis based on size and labels
		// this is a request to the layout manager
		// the insets are adjusted here ONLY, because it is assumed the layout is in progress, 
		// which is the only safe time to change the insets
		int width, height;
		//System.out.println("label size = "+labelSize.toString());
		if (orientation == HORIZONTAL) {
			Dimension labelSize = getLabelSize(INT_TYPE);
			int labelWidth = labelSize.width;
			int labelHeight = labelSize.height;
			width = 10;
			height = labelHeight + majorTickLengthBL + majorTickLengthTR + labelOffset;
		} else {
			Dimension labelSize = getLabelSize(DOUBLE_TYPE);
			int labelWidth = labelSize.width;
			int labelHeight = labelSize.height;
			width = labelWidth + majorTickLengthBL + majorTickLengthTR + labelOffset;
			height = 10;
		}
		//System.out.println("axis min size = ("+width+", "+height+")");
		return new Dimension(width, height);
	}



	private void drawMarker(Graphics g, int x, int y) {
		g.fillRect(x-backgroundSize/2, y-backgroundSize/2, backgroundSize, backgroundSize);
	}
	

	/*
	private void drawMajorTick(Graphics g, int tickLocation, int tickLength, Dimension size, String label, int labelBaseline, FontMetrics fontMetrics) {
		// make sure tick is inside the proper bounds
		if (orientation == HORIZONTAL) {
			if (tickLocation < insets.left || tickLocation > size.width - insets.right) return;
		} else {
			if (tickLocation < insets.top || tickLocation > size.height - insets.bottom) return;
		}
		int labelEdgePosition;
		int labelWidth = fontMetrics.stringWidth(label);
		int labelHeight = fontMetrics.getAscent(); 
		if (orientation == HORIZONTAL) {
			if (labelPosition == ValueAxis.BOTTOM_OR_LEFT) g.drawLine(tickLocation, 0, tickLocation, tickLength);
			else g.drawLine(tickLocation, size.height - tickLength, tickLocation, size.height);
			labelEdgePosition = tickLocation - labelWidth/2;
			if (labelEdgePosition >= 0 && labelEdgePosition + labelWidth <= size.width) g.drawString(label,labelEdgePosition, labelBaseline);
		} else {
			if (labelPosition == ValueAxis.BOTTOM_OR_LEFT) g.drawLine(size.width - tickLength, tickLocation, size.width, tickLocation);
			else g.drawLine(0, tickLocation, tickLength, tickLocation);
			labelEdgePosition = tickLocation + labelHeight/2;
			if (labelEdgePosition - labelHeight >= 0 && labelEdgePosition <= size.height) {
				if (labelPosition == ValueAxis.BOTTOM_OR_LEFT) g.drawString(label, labelBaseline - labelWidth, labelEdgePosition);
				else g.drawString(label, labelBaseline, labelEdgePosition);
			}
		}
	}

	private void drawMinorTicks(Graphics g, int baseline, int tickLocation1, int tickLocation2, Dimension size) {
		// give location of one major tick, fill in all minor tickmarks
		if (minorTicks == 0 || minorTickLengthTR == 0 && minorTickLengthBL == 0) return;   // nothing to draw
//System.out.println("at 1, drawing ticks from "+tickLocation1+" to "+tickLocation2);
		if (tickLocation1 > tickLocation2) {
			int temp = tickLocation1;
			tickLocation1 = tickLocation2;
			tickLocation2 = temp;
		}
		int tickLocation, lowerBound, upperBound;
		if (orientation == ValueAxis.HORIZONTAL) {
			lowerBound = insets.left;
			upperBound = size.width - insets.right;
		} else {
			lowerBound = insets.top;
			upperBound = size.height - insets.bottom;
		}
		if (tickLocation1 == Integer.MIN_VALUE) // draw remaining ticks to the left or top
			tickLocation1 = tickLocation2 - (int) Math.rint(units2Pixels*majorTickInterval.doubleValue());
		else if (tickLocation2 == Integer.MAX_VALUE) // draw remaining ticks to the right or bottom
			tickLocation2 = tickLocation1 + (int) Math.rint(units2Pixels*majorTickInterval.doubleValue());
		if (tickLocation1 == tickLocation2) return;
		double interval = ((double) (tickLocation2 - tickLocation1))/(minorTicks + 1);
		for (int i=1; i<=minorTicks; ++i) {
			tickLocation = tickLocation1 + (int) Math.round(i*interval);
			if (tickLocation >= lowerBound && tickLocation <= upperBound) {
				if (orientation == ValueAxis.HORIZONTAL) g.drawLine(tickLocation, baseline - minorTickLengthTR, tickLocation, baseline + minorTickLengthBL);
				else g.drawLine(baseline - minorTickLengthBL, tickLocation, baseline + minorTickLengthTR, tickLocation);
			}
		}
	}
	*/

}
