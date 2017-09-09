package com.gensym.nols.chart.bar;

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
public class BarChart extends Chart implements ChartListener{
	
	// its components
	public BarPlot plot;
	private BarChartLayout theLayout;
	public ValueAxis xAxis;  
	public ValueAxis yAxis;  
	public ChartScrollpane pane;
	public ChartScrollbar hscroll;

	private int nBins;
	private double [] binValues;
	private double xLow, xHigh;

	private double zoomRatio;
	private int zoomFlag;	// 0: no zoom; 1: zoomin 2: zoomout 3: zoomxin 4: zoomyin; 5:zoomxout; 6:zoomyout
	public boolean zoomed;

	/////////////////// BarChart (name, binValues[], low, high) //////////////////
	public BarChart(String name, double [] binValues, double xLow, double xHigh) {
		super();
		
		this.nBins = binValues.length;
		this.xLow = xLow;
		this.xHigh = xHigh;
		this.binValues = binValues;
		
		zoomRatio = 2.0;
		zoomFlag = 0;
		zoomed = false;

		theLayout = new BarChartLayout();
		setLayout(theLayout);

		// SCROLLPANE TO CONTAIN BARCHART
		pane = new ChartScrollpane(this, new Point(0,0), new Dimension(300, 300), new Dimension(300,300)); 
		// pane is added at the end of this constructor

		// CREATE X AXIS
		xAxis = new ValueAxis(ValueAxis.DOUBLE_TYPE, 1, ValueAxis.HORIZONTAL);
		xAxis.setAutoInsets(false);  // don't use insets on y axis since it screws up zooming
		xAxis.setColor(Color.black);
		xAxis.setOpaque(false);
		xAxis.setDragBehavior(Chart.DRAG_DOES_NOTHING);
		xAxis.setToolTipText("Bin Axis");
		add(xAxis);

		// CREATE Y AXIS
		yAxis = new ValueAxis(ValueAxis.DOUBLE_TYPE, 2, ValueAxis.VERTICAL);
		yAxis.setAutoInsets(false);  // don't use insets on y axis since it screws up zooming
		yAxis.setColor(Color.black);
		yAxis.setOpaque(false);
		yAxis.setDragBehavior(Chart.DRAG_DOES_NOTHING);
		yAxis.setToolTipText("Y Axis");
		add(yAxis);

		// SCROLL BAR FOR X-DIMENSION
		hscroll = new ChartScrollbar(Scrollbar.HORIZONTAL);
		pane.addScrollbar(hscroll);  // not to be confused with adding to the container
		add(hscroll);

		plot = new BarPlot(name, binValues, xLow, xHigh, xAxis, yAxis);
		pane.add(plot);
		add(pane);
	}

	@Override
	public boolean isOpaque(){
		return false;
	}

	public void print() {
		plot.print();
	}

	// set (or replace) a data series of a given name
	public void setDataSeries(String name, double [] binValues, double xLow, double xHigh) {
		plot.setDataSeries(name, binValues, xLow, xHigh);
		invalidateAll();  // invalidate the entire region
		repaint(0L);
	}

	@Override
	public void chartPointSelected(ChartEvent e) {}
	@Override
	public void chartAreaSelected(ChartEvent e) {}	
	@Override
	public void chartPopupTriggered(ChartEvent e) {}

	public synchronized void zoom(double ratio) {
		int focusX = pane.getViewWidth()/2;
		int focusY = pane.getViewHeight()/2;
		pane.zoom(ratio, ratio, new Point(focusX, focusY));  // contains immediate repaint
		zoomFlag = 0;
		zoomed = true;
		repaint(0L);
	}
}
