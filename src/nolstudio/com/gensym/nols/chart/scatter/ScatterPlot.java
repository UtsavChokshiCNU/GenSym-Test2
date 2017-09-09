package com.gensym.nols.chart.scatter;

import com.gensym.nols.chart.line.*;
import com.gensym.nols.util.*;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class ScatterPlot extends Plot implements AxisListener, ComponentListener {
	public ValueAxis yAxis;
	public ValueAxis xAxis;

	private Dimension displaySize;

	private Vector data;
	private Vector plots;

	private Vector trees;
	private Vector lineFormats;

	private Vector markersCache;		// array index into markerFormats
	private Vector markerFormatsCache;	// the markers used in this plot
	private Vector drawMarkersCache;

	public int maxMarkerForegroundSize;
	public int minMarkerForegroundSize;
	public int maxMarkerBackgroundSize;
	public int minMarkerBackgroundSize;
	public boolean autoscaleMarker;

	public int selectionSlop;
	private int[] mouseIndex;
	private boolean compressing;

	private int previousForegroundSize=0;
	public LineFormat connectorFormat;
	private boolean connectorState;

	private static final boolean DEBUG = false;

//
// The bounding rectangle defined by data
//
	private double xMin, yMin, xMax, yMax;
	private int zoomRatio;
	private Color backgroundColor;
	private boolean drawFortyFiveDegreeLine;
	private boolean drawLineInForeground;
	private Color fortyFiveDegreeLineColor;
	private int bucketSize = 128;

    /** primary constructor. **/
	public ScatterPlot(String name, double[] X, double[] Y, MarkerFormat[] markerFormats, byte[] markers, LineFormat connectorFormat, ValueAxis xAxis, ValueAxis yAxis) {
		super();
		if (X.length != Y.length) 
			throw new IllegalArgumentException("X and Y Arrays are of unequal length!");
		plots = new Vector();
		plots.addElement(name);
		markersCache = new Vector();
		markersCache.addElement(markers);
		markerFormatsCache = new Vector();
		markerFormatsCache.addElement(markerFormats);
		lineFormats = new Vector(); 
		lineFormats.addElement(connectorFormat);
		boolean[] drawMarkers = new boolean[markerFormats.length];
		drawMarkersCache = new Vector();
		drawMarkersCache.addElement(drawMarkers);
		determineMarkerDrawability();
		setDragBehavior(Chart.DRAG_CREATES_SELECTION_BOX);
		selectionSlop = 10;
		this.connectorFormat = connectorFormat;	
		this.xAxis = xAxis;
		this.yAxis = yAxis;
		connectorState = false;
		double[][] xy = new double[2][];
		data = new Vector();
		xy[0] = Y;
		xy[1] = X;
		data.addElement(xy);
		findMinMax(true);
		trees = new Vector();
		TwoDTree tree = new TwoDTree(X, Y, xy[0].length, bucketSize);
		trees.addElement(tree);
		displaySize = new Dimension(200,200);
		setVisible(true);
		yAxis.addPlot(this);
		yAxis.addAxisListener(this);
		xAxis.addPlot(this);
		xAxis.addAxisListener(this);
		addComponentListener(this);

		mouseIndex = new int[2];  // represents point which the mouse is over
		mouseIndex[0] = -1;
		mouseIndex[1] = -1;
		// set the background color
		backgroundColor	= Color.darkGray;
		// set the default bucket size for the K-2 search
		bucketSize = 128;
		// default limits on marker size
		maxMarkerForegroundSize = 8;
		minMarkerForegroundSize = 2;
		maxMarkerBackgroundSize = 12;
		minMarkerBackgroundSize = 4;
		autoscaleMarker = true;
		drawFortyFiveDegreeLine = true;
		drawLineInForeground = false;		
		fortyFiveDegreeLineColor = Color.red;
		zoomRatio = 2;
	}

	public void addDataSeries(String name, double[] X, double[] Y, MarkerFormat[] markerFormats, byte[] markers, LineFormat connectorFormat) {
		plots.addElement(name);
		markersCache.addElement(markers);
		markerFormatsCache.addElement(markerFormats);
		lineFormats.addElement(connectorFormat);
		boolean[] drawMarkers = new boolean[markerFormats.length];
		drawMarkersCache.addElement(drawMarkers);
		determineMarkerDrawability();
		double[][] xy = new double[2][];
		xy[0] = Y;
		xy[1] = X;
		data.addElement(xy);
		findMinMax(true); //gchen changed 9.10.99
		calculateNewMinMaxForAxis();
		TwoDTree tree = new TwoDTree(X, Y, xy[0].length, bucketSize);
		trees.addElement(tree);
	}

	public void setDataSeries(String name, double[] X, double[] Y, byte[] markers) {
		if (X.length != Y.length) 
			throw new IllegalArgumentException("setDataSeries: X and Y Arrays are of unequal length!");
		int index = plots.indexOf(name);
		if(index == -1)
			throw new IllegalArgumentException("setDataSeries: " + name + " not found in data series");

		markersCache.setElementAt(markers, index);
		double[][] xy = new double[2][];
		xy[0] = Y;
		xy[1] = X;
		data.setElementAt(xy, index);  // insert xy at position index
		findMinMax(true);
		calculateNewMinMaxForAxis();
		TwoDTree tree = new TwoDTree(X, Y, xy[0].length, bucketSize);
		trees.setElementAt(tree, index);
	}

	private void calculateNewMinMaxForAxis(){
		// calc new max/min
		PlotEvent e = new PlotEvent(this,0,new Double(xMin));
		xAxis.plotRangeChanged(e);
		e = new PlotEvent(this,1,new Double(xMax));
		xAxis.plotRangeChanged(e);
		e = new PlotEvent(this,0,new Double(yMin));
		yAxis.plotRangeChanged(e);
		e = new PlotEvent(this,1,new Double(yMax));
		yAxis.plotRangeChanged(e); 		
	}

	public void removeDataSeries(String name) {
		int index = plots.indexOf(name);
		if(index == -1)
			throw new IllegalArgumentException("removeDataSeries: " + name + " not found in data series");
		plots.removeElement(name);
		markersCache.removeElementAt(index);
		markerFormatsCache.removeElementAt(index);
		lineFormats.removeElementAt(index);
		drawMarkersCache.removeElementAt(index);
		data.removeElementAt(index);
		trees.removeElementAt(index);
	}

	private void findMinMax(boolean fromStart){
		int nD = data.size();
		if(fromStart){
			xMin = Double.MAX_VALUE;
			xMax = -Double.MAX_VALUE;
			yMin = Double.MAX_VALUE;
			yMax = -Double.MAX_VALUE;
		}

		for(int j=0;j<nD;j++){
			double[][] xy = (double[][])data.elementAt(j);
		// search for the min and max of X and Y
			int length = xy[1].length;
			for(int i=0; i< length; i++) {  
				if (!(Double.isNaN(xy[1][i]))) {
					if(xy[1][i] > xMax){
						xMax = xy[1][i];
					}
					if(xy[1][i] < xMin){
						xMin = xy[1][i];
					}
				}

				if (!(Double.isNaN(xy[0][i]))) {
					if(xy[0][i] > yMax){
						yMax = xy[0][i];
					}
					if(xy[0][i] < yMin){
						yMin = xy[0][i];
					}
				}
			}

		}
		if (Double.compare(yMin, Double.MAX_VALUE) == 0 || Double.compare(yMax, -Double.MAX_VALUE) == 0 ) { 
			yMin = 0.0;
			yMax = 1.0;
		}
		if (Double.compare(xMin, Double.MAX_VALUE) == 0 || Double.compare(xMax, -Double.MAX_VALUE) ==0 ) {  
			xMin = 0.0;
			xMax = 1.0;
		}
//		System.out.println("findMinMax: yMin = " + yMin + " yMax = " + yMax + " xMin = " + xMin + " xMax = " + xMax);
	}

	public byte[] getMarkerArray(String name) {

		int index = plots.indexOf(name);
		if(index == -1)
			throw new IllegalArgumentException("getMarkerArray: " + name + " marker not found");

		return (byte[])markersCache.elementAt(index);
	}


	public void setMarkerArray(String name, byte[] markers) {
		int index = plots.indexOf(name);
		if(index == -1)
			throw new IllegalArgumentException("getMarkerArray: " + name + " marker not found");
		markersCache.setElementAt(markers,index);
	}


	public MarkerFormat[] getMarkerFormat(String name) {
		int index = plots.indexOf(name);
		if(index == -1)
			throw new IllegalArgumentException("getMarkerFormat: " + name + " marker format not found");

		return (MarkerFormat[])markerFormatsCache.elementAt(index);
	}


	public void setMarkerFormat(String name, MarkerFormat[] markerFormats) {
		int index = plots.indexOf(name);
		if(index == -1)
			throw new IllegalArgumentException("setMarkerFormats: " + name + " marker format not found");

		markerFormatsCache.setElementAt(markerFormats, index);
		boolean[] drawMarkers = new boolean[markerFormats.length];
		drawMarkersCache.setElementAt(drawMarkers, index);						// added by bbush 7-31-98
		resizeMarker();
	}

	public Vector getData() {
		return data;
	}

	public Vector getTrees() {
		return trees;
	}

	@Override
	public Range getRange(int dimension) {
		// dimension: 1 = x dimension, 2 = y dimension
		if (dimension == 1) {
			return new Range(new Double(xMin), new Double(xMax));	
		}else {
			return new Range(new Double(yMin), new Double(yMax));
		}
	}


	public void changeAxis(ValueAxis newAxis) {
		if (newAxis.getOrientation() == ValueAxis.VERTICAL) {
			yAxis.removePlot(this);
			yAxis.removeAxisListener(this);
			this.yAxis = newAxis;
			yAxis.addPlot(this);
			yAxis.addAxisListener(this);
		} else {
			xAxis.removePlot(this);
			xAxis.removeAxisListener(this);
			this.xAxis = newAxis;
			xAxis.addPlot(this);
			xAxis.addAxisListener(this);
		}
	}

	@Override
	public boolean isOpaque(){
		return true;
	}

	public void setBackgroud(Color color) {
		backgroundColor = color;
	}

	public void setConnectorsState(boolean state) {
		connectorState = state;
	}

	public void setFortyFiveDegreeLineState(boolean lineOn, boolean foreground) {
		drawFortyFiveDegreeLine = lineOn;
		drawLineInForeground = foreground;
		fortyFiveDegreeLineColor = Color.red;
	}

	public void setFortyFiveDegreeLineColor(Color color) {
		fortyFiveDegreeLineColor = color;
	}

	@Override
	public void paint(Graphics g){
		if (g instanceof PrintGraphics) {
//		System.out.println("printing");
			backgroundColor = Color.white;
		}
		super.paint(g);
		backgroundColor	= Color.darkGray;
	}

	@Override
	public void paintComponent(Graphics g) {
//System.out.println("ScatterPlot:paintComponent - begin paint...");
		// get the region of the plot that can be seen...
		Rectangle bounds = getBounds();
		Rectangle clipBounds = g.getClipBounds();
		//System.out.println("bounds = "+bounds+", clip = "+clipBounds);
		Dimension paneSize = getParent().getSize(); // get size of pane to use
		int pxStart = Math.abs(clipBounds.x);  
		int pxEnd = pxStart + clipBounds.width;
		int pyEnd = Math.abs(clipBounds.y);
		int pyStart = pyEnd + clipBounds.height;
		//System.out.println("Painting: pxStart = " + pxStart + " pxEnd = " + pxEnd);
		//System.out.println("Painting: pyStart = " + pyStart + " pyEnd = " + pyEnd);
		// (MK 2/2/99: include 10 extra pixels to assure we draw the plot 
		//  symbols of points that are just outside the clip
		//System.out.println("x axis pixel2Units = " + xAxis.pixels2Units);
		double xStart = pixelToX(pxStart - 10);
		double xEnd = pixelToX(pxEnd + 10);
		double yStart = pixelToY(pyStart + 10);
		double yEnd = pixelToY(pyEnd - 10);

		// for drawing the forty five degree line
		int startingPointX = 0;
		int startingPointY = 0;
		int endingPointX = 0;
		int endingPointY = 0;
	//System.out.println("Painting: xStart = " + xStart + " xEnd = " + xEnd);
	//System.out.println("Painting: yStart = " + yStart + " yEnd = " + yEnd);
		g.setColor(backgroundColor); // fill with background color
		g.fillRect(pxStart,pyEnd,paneSize.width,paneSize.height);
		boolean linePresent = true;
		double startingPoint = 0;
		// finding the starting point in common with both axis
		if(xMin > yMin) { // if xMin is larger
			if((xMin <= yMax) && (xMin >= yMin)) {
				//System.out.println("x min inside Y");
			    startingPoint = xMin;
			}
			else linePresent = false;
		}
		else { // if yMin is larger
			if((yMin <= xMax) && (yMin >= xMin)) {
//				System.out.println("y min inside X");
				startingPoint = yMin;
			}
			else linePresent = false;
		}

		double endingPoint = 0;
		// finding the ending point in common with both axis
		if(xMax < yMax) { // if xMax is smaller
			if((xMax <= yMax) && (xMax >= yMin)) {
				endingPoint = xMax;
			}else {
				linePresent = false;
			}
		}
		else { // if yMax is smaller
			if((yMax <= xMax) && (yMax >= xMin)) {
				endingPoint = yMax;
			}else {
				linePresent = false;
			}
		}
		// Get range of x and y axes
		double xPlotMin = xAxis.min.doubleValue();
		double xPlotMax = xAxis.max.doubleValue();
		double yPlotMin = yAxis.min.doubleValue();
		double yPlotMax = yAxis.max.doubleValue();
		double xPlotRange = xPlotMax - xPlotMin;
		double yPlotRange = yPlotMax - yPlotMin;
		// for drawing the forty five degree line
		if(drawFortyFiveDegreeLine) {
			startingPointX = (int) ((bounds.width * (startingPoint-xPlotMin))/xPlotRange);
			startingPointY = (int) ((bounds.height * (yPlotMax-startingPoint))/yPlotRange);
			endingPointX = (int) ((bounds.width * (endingPoint-xPlotMin))/xPlotRange);
			endingPointY = (int) ((bounds.height * (yPlotMax-endingPoint))/yPlotRange);
		}

		if((drawFortyFiveDegreeLine) && (!drawLineInForeground) && (linePresent)) {
			g.setColor(fortyFiveDegreeLineColor);
			g.drawLine(startingPointX, startingPointY, endingPointX, endingPointY);
		}

		int nData = data.size(); // get the number of data sets
//System.out.println("nData = " + nData);
		for(int d = 0; d < nData; d++) { // loop through all data sets
			TwoDTree tree = (TwoDTree)trees.elementAt(d);
			tree.searchTwoDTree(xStart, xEnd, yStart, yEnd);
			MarkerFormat[] markerFormats = (MarkerFormat[])markerFormatsCache.elementAt(d);
			boolean[] drawMarkers  = (boolean[])drawMarkersCache.elementAt(d); 
			byte[] markers = (byte[]) markersCache.elementAt(d);
			int count = tree.getNumFoundItems();		
			int		xi = 0, yi = 0;
			double	x = 0, y = 0;
			double[][] xy = (double[][])data.elementAt(d);
//System.out.println("xy i= " + xy.length);
//System.out.println("xy j= " + xy[0].length);
//System.out.println("drawMarkers length= " + drawMarkers.length);
//System.out.println("markers length= " + markers.length);
//System.out.println("markerFormats length= " + markerFormats.length);
//System.out.println("count= " + count);
			// this is the core drawing loop...
			if(!connectorState) { // if no connectors needed...
				for(int i = 0; i < count; i++) {
					int ii = tree.foundItems[i];
					x = xy[1][ii];
					y = xy[0][ii];
					xi = (int) ((bounds.width * (x-xPlotMin))/xPlotRange);
					yi = (int) ((bounds.height * (yPlotMax-y))/yPlotRange);
//System.out.println("markers[ii]= " + markers[ii]);
					markerFormats[markers[ii]].drawMarker(g, xi, yi, ColorMap.colors[1]);
				}
			}
			else { // connectors are needed...
				int prevxi = 0, prevyi = 0;
				double prevx = 0, prevy = 0;
				int nextxi = 0, nextyi = 0;
				double nextx = 0, nexty = 0;
				for(int i = 0; i < count; i++) {
					int ii = tree.foundItems[i];
					x = xy[1][ii];
					y = xy[0][ii];
					xi = (int) ((bounds.width * (x-xPlotMin))/xPlotRange);
					yi = (int) ((bounds.height * (yPlotMax-y))/yPlotRange);
					if (drawMarkers[markers[ii]]) {
						markerFormats[markers[ii]].drawMarker(g, xi, yi, ColorMap.colors[1]);
					}
					if(tree.foundItems[i]-1  >= 0) { // connect line from current point to previous
						prevx = xy[1][ii-1];
						prevy = xy[0][ii-1];
						prevxi = (int) ((bounds.width * (prevx-xPlotMin))/xPlotRange);
						prevyi = (int) ((bounds.height * (yPlotMax-prevy))/yPlotRange);
						g.drawLine(prevxi, prevyi, xi, yi);
					}
					if(tree.foundItems[i]+1 < xy[0].length) { // connect line from current point to next
						nextx = xy[1][ii+1];
						nexty = xy[0][ii+1];
						nextxi = (int) ((bounds.width * (nextx-xPlotMin))/xPlotRange);
						nextyi = (int) ((bounds.height * (yPlotMax-nexty))/yPlotRange);
						g.drawLine(nextxi, nextyi, xi, yi);
					}
				}
			}
			tree.resetNumFoundItems();
		}
		if((drawFortyFiveDegreeLine) && (drawLineInForeground)) {
			g.setColor(fortyFiveDegreeLineColor);
			g.drawLine(startingPointX, startingPointY, endingPointX, endingPointY);
		}
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

	public final double pixelToX(int px) {  
		return xAxis.min.doubleValue() + xAxis.pixels2Units*px;
	}

	public final double pixelToY(int py) {
		return yAxis.max.doubleValue() - yAxis.pixels2Units*py;
	} 

	@Override
	public boolean contains(int px, int py) {  
		String name = null;
		int[] i = findPoint(px, py);
		if (i != null) { // if the point has changed... update tooltiptext
			if (i[0] != mouseIndex[0] || i[1] != mouseIndex[1]) {  // reset tool tip
				int yDigits = yAxis.sigDigits + 1;
				int xDigits = xAxis.sigDigits + 1;
				double[][] xy = (double[][]) data.elementAt(i[0]);
				String pname = (String) plots.elementAt(i[0]);
				setToolTipText(pname+": "+ i[1] + " (" + StringFormatter.DoubleToString(xy[1][i[1]],xDigits) + "," + StringFormatter.DoubleToString(xy[0][i[1]],yDigits) + ")");
				mouseIndex = i;
			}
			return true;
		}
		else { // else return that nothing has changed...
			mouseIndex = new int[2];  // represents point which the mouse is over
			mouseIndex[0] = -1;
			mouseIndex[1] = -1;
			return false;
		}
	}

	public int[] findPoint(int px, int py) { 
		//System.out.println("findPoint:px=" + px + " py="+py);
		double y = pixelToY(py+selectionSlop/2);  
		double ytol = pixelToY(py-selectionSlop/2);
		double x = pixelToX(px-selectionSlop/2);  // x coord of px
		double xtol = pixelToX(px+selectionSlop/2);
		//System.out.println("findPoint:converted x=" + x + " y=" + y);
		int count = 0;
		int nData = data.size();
		double bestDistX = Double.MAX_VALUE;
		double bestDistY = Double.MAX_VALUE;
		double distX = Double.MAX_VALUE;
		double distY = Double.MAX_VALUE;
		boolean foundPoint = false;
		int dataIndex = 0;
		int bestPointIndex = 0;
		for(int d = 0; d < nData; d++){
			int bestIndex = 0;
			if(d>=trees.size()) {
				break;
			}
			TwoDTree tree = (TwoDTree)trees.elementAt(d);
			tree.searchTwoDTree(x, xtol, y, ytol);
			count = tree.getNumFoundItems();
			if(count > 0) { 
				//System.out.println("\tfindPoint: points found=" + count);
				double[][] xy = (double[][])data.elementAt(d);
				// go through all of the points in the region to find the closest...
				for(int i = 0; i < count; i++) {
//					System.out.println("d="+d+" index=" + tree.foundItems[i] + " x=" + xy[1][tree.foundItems[i]] + " y="+ xy[0][tree.foundItems[i]]);
					distX = (Math.abs(xy[1][tree.foundItems[i]] - xy[1][tree.foundItems[bestIndex]]));
					distY = (Math.abs(xy[0][tree.foundItems[i]] - xy[0][tree.foundItems[bestIndex]]));

					if((distX < bestDistX) && (distY < bestDistY)) {
						foundPoint = true;
						bestIndex = tree.foundItems[i];
						bestDistX = distX;
						bestDistY = distY;
						bestPointIndex = bestIndex;
						dataIndex = d;
					}
				}
			}
			tree.resetNumFoundItems();
		}
		if(foundPoint){
			int[] index = new int[2];
			index[0] = dataIndex;
			index[1] = bestPointIndex;
			//System.out.println("\t*findPoint: best index=" + bestIndex);
			return index;
		}else { // did not find a point...
			return null;
		}
	}

	// Listeners
	@Override
	public void componentResized(ComponentEvent event) {
//System.out.println("Component resized, now resizing marker");
		resizeMarker();
	}

	@Override
	public void componentHidden(ComponentEvent event) {}
   	@Override
	public void componentMoved(ComponentEvent event) {}
	@Override
	public void componentShown(ComponentEvent event) {}

	@Override
	public void axisRescaled(AxisEvent e) {
	}

	public void resizeMarker(){
		// this is based on "what looks good" to my eye ;-)
		if (!autoscaleMarker) {
			return;
		}
		Rectangle bounds = getBounds();
		Dimension paneSize = getParent().getSize(); // get size of pane to use
		int pxStart = Math.abs(bounds.x);
		int pxEnd = pxStart + paneSize.width;
		int pyEnd = Math.abs(bounds.y);
		int pyStart = pyEnd + paneSize.height;

		double xStart = pixelToX(pxStart);
		double xEnd = pixelToX(pxEnd);
		double yStart = pixelToY(pyStart);
		double yEnd = pixelToY(pyEnd);

		int numberVisible = 0;
		int nData = data.size(); // get the number of data sets
		for(int d = 0; d < nData; d++) { // loop through all data sets
			TwoDTree tree = (TwoDTree)trees.elementAt(d);
			tree.searchTwoDTree(xStart, xEnd, yStart, yEnd);
			numberVisible += tree.getNumFoundItems();
			tree.resetNumFoundItems();
		}
		int foregroundSize;
		//System.out.println("Plot has " + totalDataSetSize + " points.");
		if(numberVisible < 50){
			foregroundSize = 6;
		}else if(numberVisible < 250) {
			foregroundSize = 5;
		}else if(numberVisible < 1000) {
			foregroundSize = 4;
		}else {
			foregroundSize = 3;
		}

		if (foregroundSize < minMarkerForegroundSize) {
			foregroundSize = minMarkerForegroundSize;
		}
		if (foregroundSize > maxMarkerForegroundSize) {
			foregroundSize = maxMarkerForegroundSize;
		}
//System.out.println("Resizing marker, "+numberVisible+" points, size = "+foregroundSize);
		int backgroundSize;
		if (foregroundSize <= 3) {
			backgroundSize = 5;
		}else if (foregroundSize == 4) {
			backgroundSize = 6;
		}else if (foregroundSize == 5) {
			backgroundSize = 8;
		}else {
			backgroundSize = foregroundSize + 4;
		}

		if (backgroundSize < minMarkerBackgroundSize) {
			backgroundSize = minMarkerBackgroundSize;
		}
		if (backgroundSize > maxMarkerBackgroundSize) {
			backgroundSize = maxMarkerBackgroundSize;
		}

		MarkerFormat mf;
		for(int d = 0; d < nData; d++) { // loop through all data sets
			MarkerFormat[] markerFormats = (MarkerFormat[])markerFormatsCache.elementAt(d);
			for (int i=0; i< markerFormats.length; i++) {
				mf = markerFormats[i];
				mf.setForegroundSize(foregroundSize);
				mf.setBackgroundSize(backgroundSize);
			}
		}		
		determineMarkerDrawability();
	}

	private void determineMarkerDrawability() {
		// privately keep info on whether this marker really needs to be drawn
		// to avoid unnecessary calls to MarkerFormat.drawMarker from paint
		MarkerFormat[] mfs;
		MarkerFormat mf;
		int n = markerFormatsCache.size();
		boolean[] drawMarkers;
		for(int d = 0; d < n; d++){
			mfs = (MarkerFormat[]) markerFormatsCache.elementAt(d);
			drawMarkers = (boolean[]) drawMarkersCache.elementAt(d);
			for (int i = 0; i < mfs.length; i++) {
				mf = mfs[i];
				if ((mf.getForegroundSize() == 0 || mf.getForegroundColor() == null) 
					&& (mf.getBackgroundSize() == 0 || mf.getBackgroundColor() == null)) drawMarkers[i] = false;
				else drawMarkers[i] = true;
			}
		}
	}




}
