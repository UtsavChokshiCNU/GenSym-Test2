package com.gensym.nols.chart.scatter;
import com.gensym.nols.chart.line.*;
//package com.gensym.chart.scatter;

import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.lang.Object.*;
import java.lang.Math.*;

/**
 * ScatterChartLayout
 *
 * @version     1.0 May 26 1998
 * @author      Brian O. Bush
**/
public class ScatterChartLayout implements LayoutManager {

	// layout parameters
	public int scrollbarHeight;  //scroll bar dimension
	public int scrollbarOffset;	// space between bottom of x-axis and scrollbar
	public int border; // empty border around entire chart

	public int plotWidth;
	public int plotHeight;
	private static final boolean DEBUG = false;
	private static boolean firstTime = true;
	
	
    /** primary constructor. **/
    public ScatterChartLayout() {
		//System.out.println("ScatterChartLayout:ScatterChartLayout - constructor...");
		scrollbarHeight = 16;
		scrollbarOffset = 4;
		border = 10; 
	}

    @Override
    public void addLayoutComponent(String name, Component comp) {}

    @Override
    public void removeLayoutComponent(Component comp) {}

    @Override
    public Dimension preferredLayoutSize(Container parent) {
		Insets insets = parent.getInsets();  // top, left, bottom, right insets around chart contained
		return new Dimension(insets.left + insets.right + 300, 
			     insets.top + insets.bottom + 300);
    }

    @Override
    public Dimension minimumLayoutSize(Container parent) {
		Insets insets = parent.getInsets();
		return new Dimension(insets.left + insets.right + 300, 
			     insets.top + insets.bottom + 300);
    }

    @Override
    public void layoutContainer(Container parent) {
		
		ScatterChart chart = (ScatterChart) parent;
		if (parent.getComponentCount() == 0) {
			return;
		}
		
		Insets insets = parent.getInsets();
		ChartScrollpane pane = chart.pane;
		ChartScrollpane xPane = chart.xPane;
		ChartScrollpane yPane = chart.yPane;
		ValueAxis xAxis = chart.xAxis;
		ValueAxis yAxis = chart.yAxis;
		ScatterPlot plot = chart.plot;
		ChartScrollbar hscroll = chart.hscroll;
		ChartScrollbar vscroll = chart.vscroll;
//		System.out.println("ScatterChartLayout:layoutContainer - doing layout on "+plots.size()+" plot(s)");
		Rectangle bounds = parent.getBounds();
		int width = bounds.width - (insets.left + insets.right);
		int height = bounds.height - (insets.top + insets.bottom);
		int left = insets.left;
		int top = insets.top;
		int right = left + width;
		int bottom = top + height;
		/*	System.out.println("rect bounds");
			System.out.println("\twidth: " + width + "\theight: " + height);
			System.out.println("\tleft: " + left + "\tright: " + right);
			System.out.println("\ttop: " + top + "\tbottom: " + bottom); */
		// Y axis stuff
		Dimension axisSize = yAxis.getMinimumSize();
		int yAxisWidth = axisSize.width;
		int topInset = yAxis.getInsets().top;
		int bottomInset = yAxis.getInsets().bottom;
		
		// X axis stuff
		axisSize = xAxis.getMinimumSize();
		int xAxisHeight = axisSize.height;

		// set chart dimensions
		int chartPaneLeft = left + yAxisWidth; 
		int chartPaneTop = top; 
		int chartPaneWidth = width - yAxisWidth - scrollbarOffset - scrollbarHeight;
		int chartPaneHeight = height - xAxisHeight - scrollbarOffset - scrollbarHeight;

		// set the bounds for the chart pane
		pane.setBounds(chartPaneLeft, chartPaneTop, chartPaneWidth, chartPaneHeight);
		pane.proportionalResize();  

		// set the bounds for the x pane that contains the x axis
		xPane.setBounds(chartPaneLeft, chartPaneHeight, chartPaneWidth, xAxisHeight);
		xPane.proportionalResize(); 

		// set the bounds for the y pane that contains the y axis
		yPane.setBounds(left, chartPaneTop, yAxisWidth, chartPaneHeight);
		yPane.proportionalResize(); 

		// set the horizontal and vertical scroll bars
		hscroll.setBounds(chartPaneLeft, chartPaneHeight + xAxisHeight + scrollbarOffset, chartPaneWidth, scrollbarHeight);
		vscroll.setBounds(chartPaneWidth + yAxisWidth + scrollbarOffset, chartPaneTop, scrollbarHeight, chartPaneHeight);

		// get full size, X and Y of pane 
		int fullPaneWidth = pane.getFullWidth();
		int viewX = pane.getViewX();
		int fullPaneHeight = pane.getFullHeight();
		int viewY = pane.getViewY();

		if(chartPaneWidth == fullPaneWidth) 
			hscroll.setBounds(0, 0, 0, 0);
	
		if(chartPaneHeight == fullPaneHeight) 
			vscroll.setBounds(0, 0, 0, 0);

		if(firstTime)
		{
			hscroll.setBounds(0, 0, 0, 0);
			vscroll.setBounds(0, 0, 0, 0);
			firstTime = false;
		}
	
		// set the X axis to chart dimensions - (left, top, width, height)
		xAxis.setBounds(-viewX, 0, fullPaneWidth, xAxisHeight);
		// set the Y axis to the chart pane - (left, top, width, height)
		yAxis.setBounds(0, -viewY, yAxisWidth, fullPaneHeight);		
		plot.setBounds(-viewX, -viewY, fullPaneWidth, fullPaneHeight); // set the chart bounds

	}

}