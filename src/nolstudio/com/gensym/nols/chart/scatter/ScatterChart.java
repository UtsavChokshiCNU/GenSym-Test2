package com.gensym.nols.chart.scatter;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.lang.Object.*;
import java.lang.Math.*;
import javax.swing.*;

import com.gensym.nols.chart.line.*;


/**
 * ScatterChart
 *
 * @version     1.0 May 26 1998
 * @author      Brian O. Bush
**/
public class ScatterChart extends Chart implements ChartListener{
	
	// its components
	public ScatterPlot plot;

	private ScatterChartLayout theLayout;

	public ValueAxis xAxis;  
	public ValueAxis yAxis;  
	
	public ChartScrollpane pane;
	public ChartScrollpane xPane;
	public ChartScrollpane yPane;
	public ChartScrollbar hscroll;
	public ChartScrollbar vscroll;

	public SelectableBackground plotBackground;

	private double zoomRatio;
	public static final byte DEFAULT_FORMAT = 0;
	public static final byte HIGHLIGHT_FORMAT = 1;

	private static final boolean DEBUG = false;

    /** primary constructor. **/
	public ScatterChart(Color back) {
		super(back);
		holdOn();
		//System.out.println("ScatterChart:ScatterChart - constructor...");
		zoomRatio = 2.0;
		theLayout = new ScatterChartLayout();
		setLayout(theLayout);

		// SCROLLPANE TO CONTAIN PLOTS
		pane = new ChartScrollpane(this, new Point(0,0), new Dimension(300, 300), new Dimension(300,300)); 
		// pane is added at the end of this constructor

		// CREATE X AXIS within a ScrollPane
		xPane = new ChartScrollpane(this, new Point(0,0), new Dimension(100, 100), new Dimension(100,100));  
		xAxis = new ValueAxis(ValueAxis.DOUBLE_TYPE, 1, ValueAxis.HORIZONTAL);
		xAxis.setAutoInsets(false);  // don't use insets on x axis since it screws up zooming
		xAxis.setColor(Color.black);
		xAxis.setOpaque(true);
		xAxis.setToolTipText("X Axis");
		xAxis.setDragBehavior(Chart.DRAG_CREATES_SELECTION_BOX);
		xPane.add(xAxis);  
		add(xPane);

		// CREATE Y AXIS within a ScrollPane
		yPane = new ChartScrollpane(this, new Point(0,0), new Dimension(100, 100), new Dimension(100,100));  
		yAxis = new ValueAxis(ValueAxis.DOUBLE_TYPE, 2, ValueAxis.VERTICAL);
		yAxis.setAutoInsets(false);  // don't use insets on y axis since it screws up zooming
		yAxis.setColor(Color.black);
		yAxis.setOpaque(false);
		yAxis.setDragBehavior(Chart.DRAG_CREATES_SELECTION_BOX);
		yAxis.setToolTipText("Y Axis");
		yPane.add(yAxis);
		add(yPane);
		
		// SCROLL BAR FOR X-DIMENSION
		hscroll = new ChartScrollbar(Scrollbar.HORIZONTAL);
		pane.addScrollbar(hscroll);  // not to be confused with adding to the container
		xPane.addScrollbar(hscroll);  // associate horizontal scroll bar with x axis
		add(hscroll);

		// SCROLL BAR FOR Y-DIMENSION
		vscroll = new ChartScrollbar(Scrollbar.VERTICAL);
		pane.addScrollbar(vscroll);  
		yPane.addScrollbar(vscroll);  // associate vertical scroll bar with y axis
		add(vscroll);

		add(pane);
		addChartListener(this);
		holdOff();
	}

	@Override
	public void chartPointSelected(ChartEvent e) {
	}

	@Override
	public void chartAreaSelected(ChartEvent e) {
	}

	public int[][] findSelectedRows(Rectangle rb){
		Rectangle plotBounds = plot.getBounds();
		Dimension axisSize = yAxis.getMinimumSize();
		int width = rb.width;
		int height = rb.height;
		double xMin = plot.pixelToX(rb.x-axisSize.width-plotBounds.x);
		double xMax = plot.pixelToX(rb.x+rb.width-axisSize.width-plotBounds.x);
		double yMin = plot.pixelToY(rb.y+rb.height-plotBounds.y);
		double yMax = plot.pixelToY(rb.y-plotBounds.y);
	/*	System.out.println("----------------------------------------------------------");
		System.out.println("plotBounds.x="+plotBounds.x+" plotBounds.y="+plotBounds.y);
		System.out.println("plotBounds.width="+plotBounds.width+" plotBounds.height="+plotBounds.height);
		System.out.println("rb.x="+rb.x+" rb.y="+rb.y);
		System.out.println("rb.width="+rb.width+" rb.height="+rb.height);
		System.out.println("x="+x+" y="+y);
		System.out.println(""+xMin + " < x < "+xMax);
		System.out.println(""+yMin + " < y < "+yMax);
		System.out.println("----------------------------------------------------------"); */
		Vector data = plot.getData();
		Vector trees = plot.getTrees();
		int nData = data.size();			// get the number of data sets
		int[][] rowArrays = new int[nData][];
		for(int d = 0; d < nData; d++) {	// loop through all data sets in vector
			TwoDTree tree = (TwoDTree)trees.elementAt(d);		// get tree
			tree.searchTwoDTree(xMin, xMax, yMin, yMax);		// search tree
			int count = tree.getNumFoundItems();				// get number of found items
			int[] rows = new int[count];			
			//System.out.println("labelArea:points found... " + count);
			for(int i = 0; i < count; i++) {
				rows[i] = tree.foundItems[i];
			}
			tree.resetNumFoundItems();  // remove the items found from tree
			rowArrays[d] = rows;
		}
		return rowArrays;
	}
	
	@Override
	public void chartPopupTriggered(ChartEvent e) {
	}

	@Override
	public boolean isOpaque(){
		return false;
	}

	public void setFortyFiveDegreeLine(boolean lineOn, boolean foreground, Color color) {
		plot.setFortyFiveDegreeLineState(lineOn, foreground); // default is white line
		plot.setFortyFiveDegreeLineColor(color); // sets color of line
	}

	public void setFortyFiveDegreeLine(boolean lineOn) {
		plot.setFortyFiveDegreeLineState(lineOn, true); // turns line on in the foreground, default white
		invalidateAll();  // invalidate the entire region
		repaint();
		validate();	
	}

	public void setFortyFiveDegreeLineColor(Color color) {
		plot.setFortyFiveDegreeLineColor(color); // sets color of line
		invalidateAll();  // invalidate the entire region
		repaint();
		validate();	
	}

	public void setConnectorsState(boolean state) {
		plot.setConnectorsState(state);
		invalidateAll();  // invalidate the entire region
		repaint();
		validate();	
	}

	public void setAxisColor(Color c) {
		xAxis.setColor(c);
		yAxis.setColor(c);
	}

	// add data series with marker format and marker array
	public void addDataSeries(String name, double[] x, double[] y, MarkerFormat[] theMarkerFormats, byte[] theMarkers) {
		holdOn();
		//System.out.println("ScatterChart:addDataSeries - begin adding data series '" + name + "'");
		LineFormat connectorFormat = new LineFormat(Color.green, 1);
		if(plot == null){
			plot = new ScatterPlot(name, x, y, theMarkerFormats, theMarkers, connectorFormat, xAxis, yAxis);
			pane.add(plot, 0);
		}else{
			plot.addDataSeries(name, x, y, theMarkerFormats, theMarkers, connectorFormat);
		}
//		plot.resizeMarker(); // added by Brian O. Bush, Feb 12, 1999
		invalidateAll();
		repaint();
		validate();	
		holdOff();
	}

	// add data series with marker format and marker array
	public void addDataSeries(String name, double[] x, double[] y, MarkerFormat[] theMarkerFormats, byte[] theMarkers, LineFormat connectorFormat) {
		holdOn();
		// System.out.println("ScatterChart:addDataSeries - begin adding data series '" + name + "'");
		if(plot == null){
			plot = new ScatterPlot(name, x, y, theMarkerFormats, theMarkers, connectorFormat, xAxis, yAxis);
			pane.add(plot, 0);
		}else{
			plot.addDataSeries(name, x, y, theMarkerFormats, theMarkers, connectorFormat);
		}
//		plot.resizeMarker(); // added by Brian O. Bush, Feb 12, 1999
		invalidateAll();
		repaint();
		validate();	
		holdOff();
	}

	// set (or replace) a data series of a given name
	public void setDataSeries(String name, double[] x, double[] y, byte[] theMarkers) {
		holdOn();
		if(plot == null){
			return;
		}
		plot.setDataSeries(name, x, y, theMarkers);
//		plot.resizeMarker(); // added by Brian O. Bush, Feb 12, 1999
		invalidateAll();  // invalidate the entire region
		repaint();
		validate();	
		holdOff();
	}

	public void removeDataSeries(String name) {
		holdOn();
		if(plot == null){
			return;
		}
		plot.removeDataSeries(name);
		invalidateAll();  // invalidate the entire region
		repaint();
		validate();	
		holdOff();
	}

// returns pointer to marker array
  	public byte[] getMarkerArray(String name) {
		return plot.getMarkerArray(name);
	}

	// sets the marker array
  	public void setMarkerArray(String name, byte[] markers) {		//gchen
  		plot.setMarkerArray(name,markers);
	}

	// get the marker format
	public MarkerFormat[] getMarkerFormat(String name) {
		return plot.getMarkerFormat(name);
	}

	// set the marker format
	public void setMarkerFormat(String name, MarkerFormat[] markerFormat) {
  		plot.setMarkerFormat(name, markerFormat);
		invalidateAll();
		repaint();
	}

	public void zoomIn() {
		zoom(zoomRatio);
	}

	public void zoomInX() {
		zoomX(zoomRatio);
	}

	public void zoomInY() {
		zoomY(zoomRatio);
	}

	public void zoomOut() {
		zoom(1.0/zoomRatio);
	}

	public void zoomOutX() {
		zoomX(1.0/zoomRatio);
	}
	
	public void zoomOutY() {
		zoomY(1.0/zoomRatio);
	}

	public synchronized void zoom(double ratio) {
		holdOn();
		int focusX = pane.getViewWidth()/2;
		int focusY = pane.getViewHeight()/2;
		Point p = new Point(focusX, focusY);
		xPane.zoom(ratio,1.0,p);
		yPane.zoom(1.0,ratio,p);
		pane.zoom(ratio,ratio,p);  // contains immediate repaint
		plot.resizeMarker();
		invalidateAll();
		holdOff();
	}

	public synchronized void zoomX(double ratio) {
		holdOn();
		int focusX = pane.getViewWidth()/2;
		Point p = new Point(focusX, pane.getViewHeight());
		//System.out.println("***ZOOMING CHART****");
		pane.zoom(ratio, 1.0, p);
		//System.out.println("***ZOOMING X AXIS ****");
		xPane.zoom(ratio, 1.0, p);
		plot.resizeMarker();
		invalidateAll();
		//System.out.println("***DONE ZOOMING, CALLING REPAINT***");
		holdOff();
	}

	public synchronized void zoomY(double ratio) {
		holdOn();
		int focusY = pane.getViewHeight()/2;
		Point p = new Point(pane.getViewWidth(), focusY);
		//System.out.println("In ScatterChart.zoomY, zooming main pane");
		pane.zoom(1.0, ratio, p);
		//System.out.println("In ScatterChart.zoomY, zooming y axis pane");
		yPane.zoom(1.0, ratio, p);
		plot.resizeMarker();
		invalidateAll();
		holdOff();
	}

}
