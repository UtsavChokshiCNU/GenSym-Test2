package com.gensym.nols.chart.line;

import java.awt.*;
import java.util.*;

public class MultiLineChartLayout implements LayoutManager {
	// layout parameters
	public int scrollbarHeight;  //scroll bar dimension
	public int scrollbarOffset;	// space between bottom of x-axis and scrollbar
	public int border; // empty border around entire chart
	public int plotSpacing;  // extra space between stacked plots
	public int axisSpacing;	// space between axes, when laid out left to right, also below x axis

    public MultiLineChartLayout() {
		scrollbarHeight = 16;
		scrollbarOffset = 4;
		border = 10;  // used to be 20, bbush, 10-13-98 
		plotSpacing = 10;
		axisSpacing = 4;	 
	}

    @Override
    public void addLayoutComponent(String name, Component comp) {}

    @Override
    public void removeLayoutComponent(Component comp) {}

    @Override
    public Dimension preferredLayoutSize(Container parent) {
		Insets insets = parent.getInsets();  // top, left, bottom, right insets around chart contained
		return new Dimension(insets.left + insets.right + 300, 
			     insets.top + insets.bottom + 200);
    }

    @Override
    public Dimension minimumLayoutSize(Container parent) {
//System.out.println("getting minimum size for multi-line chart");
		Insets insets = parent.getInsets();
		return new Dimension(insets.left + insets.right + 300, 
			     insets.top + insets.bottom + 200);
    }

    @Override
    public void layoutContainer(Container parent) {
		//System.out.println("Doing layout");
		MultiLineChart chart = (MultiLineChart) parent;
		Insets insets = parent.getInsets();
		if (parent.getComponentCount() == 0) {
			return;
		}
		ValueAxis xAxis = chart.xAxis;
		ValueAxis yAxis = chart.yAxis; // used only if sharing y axis
		ChartScrollpane pane = chart.pane;
		Vector plots = chart.itsPlots;
		Vector yAxes = chart.itsYAxes;  // used only if not sharing y axis
		SelectableBackground plotBackground = chart.plotBackground;
		ChartScrollbar hscroll = chart.hscroll;
		boolean stacked;
		if(chart.layoutStyle == MultiLineChart.STACKED_LAYOUT_STYLE) {
			stacked = true;
		}
		else stacked = false;
		Rectangle bounds = parent.getBounds();
		int width = bounds.width - (insets.left + insets.right);
		int height = bounds.height - (insets.top + insets.bottom);
		int left = insets.left;
		int top = insets.top;
		int right = left + width;
		int bottom = top + height;
		int yAxisAreaWidth;
		int[] yAxisWidths;
		ValueAxis yaxis;
		Dimension axisSize;
		ComboPlot plot;
		int topInset = 0;
		int bottomInset = 0;
		int nPlots = chart.getPlotCount();
		if (chart.sharedYAxis) {
			yAxisWidths = new int[1];
			axisSize = yAxis.getMinimumSize();
			yAxisWidths[0] = axisSize.width;
			yAxisAreaWidth = yAxisWidths[0];
			topInset = yAxis.getInsets().top;
			bottomInset = yAxis.getInsets().bottom;
		} else { // multiple y axes
			yAxisWidths = new int[nPlots];
			yAxisAreaWidth = 0;
			for (int i=0; i<nPlots; ++i) {
				yaxis = (ValueAxis) yAxes.elementAt(i);
				if (i == 0) {
					topInset = yaxis.getInsets().top;
				}
				if (i == nPlots - 1) {
					bottomInset = yaxis.getInsets().bottom;
				}
				plot = (ComboPlot) plots.elementAt(i);
				axisSize = yaxis.getMinimumSize();
				yAxisWidths[i] = axisSize.width;
				if (stacked) {
					yAxisAreaWidth = Math.max(yAxisAreaWidth, axisSize.width);
					if (chart.colorKeyedAxes) {
						yaxis.itsColor = xAxis.itsColor;
					}
				} else { // not shared, not stacked -- use color of axis to match plots
					yAxisAreaWidth += axisSize.width;
					if (i != 0) {
						yAxisAreaWidth += axisSpacing; // extra space between axes
					}
					//if (chart.colorKeyedAxes) yaxis.itsColor = ColorMap.colors[plot.connectorFormat.lineColor];
					if (chart.colorKeyedAxes) {
						yaxis.itsColor = plot.connectorFormat.lineColor;
					}
				}
			}
		}
		axisSize = xAxis.getMinimumSize();
		int xAxisHeight = axisSize.height;
		//System.out.println("total height = "+height+", axis = "+xAxisHeight+", top inset = "+topInset+", bottom inset = "+bottomInset);
		int plotAreaHeight = height - 2*border - scrollbarHeight - scrollbarOffset - xAxisHeight - topInset;
		int yAxisSpace = plotAreaHeight + topInset + bottomInset;
		//System.out.println("plotAreaHeight = "+plotAreaHeight);
		int plotAreaWidth = width - 2*border - yAxisAreaWidth;  // minus legend space (later)
		int singlePlotHeight;
		if (stacked) {
			singlePlotHeight = (int) Math.rint((plotAreaHeight - (nPlots - 1)*plotSpacing)/(double) nPlots);
		}else {
			singlePlotHeight = plotAreaHeight;
		}
//		chartBackground.setBounds(left, top, width, height); 	
		pane.setBounds(left + border + yAxisAreaWidth, top + border + topInset, plotAreaWidth, plotAreaHeight + xAxisHeight);
		pane.proportionalResize();  // TO DO: move to layout manager of scrollpane??
		// now situate plots and x axis inside pane
		int fullPaneWidth = pane.getFullWidth();
		if(plotAreaWidth ==  fullPaneWidth){
			hscroll.setBounds(0, 0, 0, 0);  // no scroll bar appears
		}else {
			hscroll.setBounds(left + border + yAxisAreaWidth, bottom - border - scrollbarHeight, plotAreaWidth, scrollbarHeight);
		}
		int viewX = pane.getViewX();
		// remember, x Axis is relative to the scroll pane, not the chart
		xAxis.setBounds(-viewX, plotAreaHeight, fullPaneWidth, xAxisHeight);
		// y axis is more complex
		if (chart.sharedYAxis) {
			yAxis.setBounds(left + border, top + border, yAxisWidths[0], yAxisSpace);
		} else {
			if (stacked) {
				// layout from top to bottom
				int y = top + border;
				for (int i=0; i<nPlots; ++i) {
					yaxis = (ValueAxis) yAxes.elementAt(i);
					insets = yaxis.getInsets();
					yaxis.setBounds(left + border, y, yAxisAreaWidth, singlePlotHeight + insets.top + insets.bottom);
					y = y + singlePlotHeight + plotSpacing;
				}
			} else {
				int x = left + border;
				// layout from left to right
				for (int i=0; i<nPlots; ++i) {
					yaxis = (ValueAxis) yAxes.elementAt(i);
					yaxis.setBounds(x, top + border, yAxisWidths[i], yAxisSpace); 
					x += yAxisWidths[i];
					x += axisSpacing;
				}
			}
		}
		plotBackground.setBounds(-viewX, 0, fullPaneWidth, plotAreaHeight);
		if (stacked) {
			int y = 0;  // relative to pane, not chart
			for (int j=0; j < nPlots; ++j) {
				plot = (ComboPlot) plots.elementAt(j);
				plot.setBounds(-viewX, y, fullPaneWidth, singlePlotHeight);
				y = y + singlePlotHeight + plotSpacing;
			}
		} else {
			for (int j=0; j < nPlots; ++j) {
				plot = (ComboPlot) plots.elementAt(j);
				plot.setBounds(-viewX, 0, fullPaneWidth, plotAreaHeight);
			}
		}
		chart.invalidateAll();
		chart.repaint(0l);
	}

}