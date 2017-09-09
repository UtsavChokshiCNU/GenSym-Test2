package com.gensym.nols.chart.line;

import java.awt.*;
import java.util.*;

public class MultiLineChart extends Chart {
	public int layoutStyle;
	private boolean timeMode;
	// its components
	public Vector itsPlots;
	public Vector itsYAxes;  // used only if not sharing y axis
	public ValueAxis xAxis;  // always shared between all plots
	public ValueAxis yAxis;  // used only if sharing y axis
	public ChartScrollpane pane;
	public SelectableBackground plotBackground;
	public ChartScrollbar hscroll;
	public boolean sharedYAxis; 
	private double zoomRatio;

	// formatting options
	public boolean colorKeyedAxes;

	// style choices
	public static final int OVERLAY_LAYOUT_STYLE = 0;
	public static final int STACKED_LAYOUT_STYLE = 1;
	public static final int SHARED_Y_LAYOUT_STYLE = 2;
	public static final int TIME_MODE = 0;
	public static final int ROW_MODE = 1;
	
	public MultiLineChart(int layoutStyle, int mode, Color back) {
/*		this(layoutStyle, mode);
		backColor = back;
	}
	public MultiLineChart(int layoutStyle, int mode) {
*/		super();
		backColor = back;
		this.layoutStyle = layoutStyle;
		if(layoutStyle == MultiLineChart.SHARED_Y_LAYOUT_STYLE){
			sharedYAxis = true;
		}else{
			sharedYAxis = false;
		}
		
		if (mode == MultiLineChart.TIME_MODE){
			timeMode = true;
		}else {
			timeMode = false;
		}
		itsPlots = new Vector(0, 10);
		itsYAxes = new Vector(0, 10);
//		setVisible(true);
		setLayout(new MultiLineChartLayout());
		colorKeyedAxes = true;
		zoomRatio = 2.0;

	// create components of this chart

		// SCROLLPANE TO CONTAIN PLOTS
		pane = new ChartScrollpane(this, new Point(0,0), new Dimension(200, 200), new Dimension(200,200));  // these are dummy arguments for now
		add(pane);

		// SCROLL BAR FOR X-DIMENSION
		hscroll = new ChartScrollbar(Scrollbar.HORIZONTAL);
		pane.addScrollbar(hscroll);  // not to be confused with adding to the container
		add(hscroll);

		// X AXIS
		if(timeMode){
			xAxis = new ValueAxis(ValueAxis.LONG_TYPE, 1, ValueAxis.HORIZONTAL);
		} else{
			xAxis = new ValueAxis(ValueAxis.INT_TYPE, 1, ValueAxis.HORIZONTAL);
		}
		xAxis.setAutoInsets(false);  // don't use insets on x axis since it screws up zooming
		pane.add(xAxis);  // x-axis scrolls with components
		xAxis.setToolTipText("x axis");

		// CREATE SHARED Y AXIS
		yAxis = new ValueAxis(ValueAxis.DOUBLE_TYPE, 2, ValueAxis.VERTICAL);
		add(yAxis);
		yAxis.setToolTipText("y axis");

		// BACKGROUND FOR PLOT AREA
		plotBackground = new SelectableBackground();
		pane.add(plotBackground);
	}

	public void setAxisColor(Color c) {
		xAxis.setColor(c);
		yAxis.setColor(c);
	}
	
 
	public void addDataSeries(String name, long[] t, double[] y, MarkerFormat[] markerFormats, byte[] markers, LineFormat connectorFormat) {
		//System.out.println("MultiLineChart -- adding data series");
		//System.out.println(" times "+t.length+" ys "+y.length+" select "+select.length);
		holdOn();
		ComboPlot cp;
		ValueAxis yaxis = new ValueAxis(ValueAxis.DOUBLE_TYPE, 2, ValueAxis.VERTICAL);
		itsYAxes.addElement(yaxis); 
		if (sharedYAxis) {
			cp = new ComboPlot(name, t, y, markerFormats, markers, connectorFormat, xAxis, yAxis);
		}else {
			add(yaxis);  // make sure its on top of background
			cp = new ComboPlot(name, t, y, markerFormats, markers, connectorFormat, xAxis, yaxis);
		}
		itsPlots.addElement(cp);
		cp.setBackgroundComponent(plotBackground);
		pane.add(cp, 0);
		doLayout();
		cp.setMarkerFormats(markerFormats);  // MOVED by MK 2/15/99. added by Brian O. Bush, Feb 12, 1999 to correct markers failing to update
		holdOff();
	}

	public void removeDataSeries(int i) {
		holdOn();
		ComboPlot cp = (ComboPlot) itsPlots.elementAt(i);
		itsPlots.removeElement(cp);
		ValueAxis yaxis = (ValueAxis) itsYAxes.elementAt(i);
		itsYAxes.removeElement(yaxis);
		remove(yaxis);
		xAxis.removePlot(cp);
		pane.remove(cp);
		doLayout();
		holdOff();
	}

	public void removeAllDataSeries() {
		holdOn();
		for(int looper = itsPlots.size()-1; looper >= 0; looper--) {
			ComboPlot cp = (ComboPlot) itsPlots.elementAt(looper);
			itsPlots.removeElement(cp);
			ValueAxis yaxis = (ValueAxis) itsYAxes.elementAt(looper);
			itsYAxes.removeElement(yaxis);
			remove(yaxis);
			xAxis.removePlot(cp);
			pane.remove(cp);
		}
		doLayout();
		holdOff();
	}

	public void setMarkerArray(int plotNumber, byte[] markers) {
		ComboPlot cp = (ComboPlot) itsPlots.elementAt(plotNumber);
		cp.setMarkerArray(markers);
	}

	public byte[] getMarkerArray(int plotNumber) {
		// returns pointer to marker array
		ComboPlot cp = (ComboPlot) itsPlots.elementAt(plotNumber);
		return cp.getMarkerArray();
	}

	public MarkerFormat[] getMarkerFormats(int plotNumber) {
		ComboPlot cp = (ComboPlot) itsPlots.elementAt(plotNumber);
		return cp.getMarkerFormats();
	}

	public LineFormat getLineFormat(int plotNumber) {
		ComboPlot cp = (ComboPlot) itsPlots.elementAt(plotNumber);
		return cp.connectorFormat;
	}	 //Gchen add 2/23/99

	public int getPlotCount() {
		return itsPlots.size();
	}

	public void setStyle(int newStyle) {
		// return if there are no plots, added by Brian O. Bush, March 12, 1999
		if (itsPlots.isEmpty()) 
			return; 
		if (newStyle == layoutStyle) 
			return;
		holdOn();
		if (newStyle == MultiLineChart.SHARED_Y_LAYOUT_STYLE) {
			sharedYAxis = true;
		} else {
			sharedYAxis = false;
		}
		if (newStyle == MultiLineChart.SHARED_Y_LAYOUT_STYLE) {
			// was not shared before, so hide multiple y-axes, change to single y axis
			ComboPlot cp;
			int i;
			for (i=0; i<itsPlots.size(); ++i) {
				cp = (ComboPlot) itsPlots.elementAt(i);
				cp.changeAxis(yAxis);
				remove((Component) itsYAxes.elementAt(i));
			}
			add(yAxis, 0);
		} else if (layoutStyle == MultiLineChart.SHARED_Y_LAYOUT_STYLE) {
			// was shared before, now add multiple y-axes
			ComboPlot cp;
			int i;
			remove(yAxis);
			ValueAxis yaxis;
			for (i=0; i<itsPlots.size(); ++i) {
				cp = (ComboPlot) itsPlots.elementAt(i);
				yaxis = (ValueAxis) itsYAxes.elementAt(i);
				cp.changeAxis(yaxis);
				add(yaxis, 0);
			}
		}
		layoutStyle = newStyle;
		doLayout();
		holdOff();
	}
	
	public int getStyle() {
		return layoutStyle;
	}

	public void setMode(int mode) {
		if (mode == MultiLineChart.TIME_MODE) {
			if (timeMode) {
				return;
			}
			timeMode = true;
			xAxis.setAxisType(ValueAxis.LONG_TYPE);
		} else {
			if (!timeMode) {
				return;
			}
			timeMode = false;
			xAxis.setAxisType(ValueAxis.INT_TYPE);
		}	
		addInvalidation(pane.getBounds());  // no conversion, already in chart coords
		repaint();  // added by Brian O. Bush, Feb 16, 1999 to allow x-axis to repaint when mode changed
	}

	public int getMode() {
		if (timeMode) {
			return MultiLineChart.TIME_MODE;
		}else {
			return MultiLineChart.ROW_MODE;
		}
	}

	public void zoomIn() {
		// zooms in, using current zoomRatio on x-dimension, keeping center of screen fixed, if possible
		zoom(zoomRatio);
	}

	public void zoomOut() {
		zoom(1.0/zoomRatio);
	}

	public synchronized void zoom(double ratio) {
		holdOn();
		int focusX = pane.getViewWidth()/2;
		int focusY = pane.getViewHeight()/2;
		// ratio is magnification for x, and 1.0 is the magnification for y, focus in center
		pane.zoom(ratio, 1.0, new Point(focusX, focusY));
		for(int i=0;i<itsPlots.size();i++) {
			ComboPlot cp = (ComboPlot) itsPlots.elementAt(i);
			cp.resizeMarker();
		}
		invalidateAll();
		holdOff();

	}

	public void setMarkerFormats(int plotNumber, MarkerFormat[] markerFormats) {
		ComboPlot cp = (ComboPlot) itsPlots.elementAt(plotNumber);
		cp.setMarkerFormats(markerFormats);
	}

}
