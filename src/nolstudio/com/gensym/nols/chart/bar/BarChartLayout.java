package com.gensym.nols.chart.bar;

import com.gensym.nols.chart.line.*;
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
public class BarChartLayout implements LayoutManager {

	// layout parameters
	public int scrollbarHeight;  //scroll bar dimension
	public int scrollbarOffset;	// space between bottom of x-axis and scrollbar
	
    /** primary constructor. **/
    public BarChartLayout() {
		//System.out.println("BarChartLayout:BarrChartLayout - constructor...");
		scrollbarHeight = 16;
		scrollbarOffset = 4;
	}

    @Override
    public void addLayoutComponent(String name, Component comp) {}

    @Override
    public void removeLayoutComponent(Component comp) {}

    @Override
    public Dimension preferredLayoutSize(Container parent) {
		Insets insets = parent.getInsets();  // top, left, bottom, right insets around chart contained
		return new Dimension(insets.left + insets.right + 200, 
			     insets.top + insets.bottom + 200);
    }

    @Override
    public Dimension minimumLayoutSize(Container parent) {
		//System.out.println("BarChartLayout:minumumLayoutSize - getting minimum size for scatter chart.");
		Insets insets = parent.getInsets();
		return new Dimension(insets.left + insets.right + 200, 
			     insets.top + insets.bottom + 200);
    }

    @Override
    public void layoutContainer(Container parent) {
		
		BarChart chart = (BarChart) parent;
		if (parent.getComponentCount() == 0) 
			return;
		
		Insets insets = parent.getInsets();
		ChartScrollpane pane = chart.pane;
		ValueAxis yAxis = chart.yAxis;
		ValueAxis xAxis = chart.xAxis;
		BarPlot plot = chart.plot;
		ChartScrollbar hscroll = chart.hscroll;
		
//		System.out.println("BarrChartLayout:layoutContainer - doing layout on "+plots.size()+" plot(s)");
		
		Rectangle bounds = parent.getBounds();
		int width = bounds.width - (insets.left + insets.right);
		int height = bounds.height - (insets.top + insets.bottom);
		int left = insets.left;
		int top = insets.top;
		int right = left + width;
		int bottom = top + height;

		// Y axis stuff
		Dimension axisSize = yAxis.getMinimumSize();
		int yAxisWidth = axisSize.width;
		int topInset = yAxis.getInsets().top;
		int bottomInset = yAxis.getInsets().bottom;
		
		// X axis stuff
		axisSize = xAxis.getMinimumSize();
		int xAxisHeight = axisSize.height;

		// set chart dimensions
		int chartPaneWidth = width - yAxisWidth;
		int chartPaneHeight = height - xAxisHeight - scrollbarOffset - scrollbarHeight;

		// set the bounds for the chart pane
		pane.setBounds(0, 0, chartPaneWidth + yAxisWidth, chartPaneHeight);
		
		// set the Y axis to the chart pane - (left, top, width, height)
		yAxis.setBounds(0, 0, yAxisWidth, chartPaneHeight);
		xAxis.setBounds(yAxisWidth, chartPaneHeight, chartPaneWidth , xAxisHeight);

		// set the horizontal and vertical scroll bars
		hscroll.setBounds(yAxisWidth, chartPaneHeight + xAxisHeight + scrollbarOffset, chartPaneWidth, scrollbarHeight);

		if(!chart.zoomed) 
			hscroll.setBounds(0, 0, 0, 0);

		plot.setBounds(yAxisWidth, 0, chartPaneWidth, chartPaneHeight); // set the chart bounds

		chart.invalidateAll();
		chart.repaint(0L); 
	}

}