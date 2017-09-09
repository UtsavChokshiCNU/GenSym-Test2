package com.gensym.nols.chart.line;

import java.awt.*;
import java.awt.event.*;
import java.util.*;

public class ComboPlot extends Plot implements AxisListener, ComponentListener {
	public ValueAxis yAxis;
	public ValueAxis xAxis;
	public int maxMarkerForegroundSize;
	public int minMarkerForegroundSize;
	public int maxMarkerBackgroundSize;
	public int minMarkerBackgroundSize;
	public boolean autoscaleMarker;
	private long[] times;
	private double[] yData;
	private byte[] markers;  // array index into markerFormats
	private MarkerFormat[] markerFormats;  // the markers used in this plot
	public LineFormat connectorFormat;
	public int selectionSlop;
	private int nData;
	private int mouseIndex;
	private boolean[] drawMarkers;

	private static final boolean DEBUG = false;

	ComboPlot(String name, long[] t, double[] y, MarkerFormat[] markerFormats, byte[] markers, LineFormat connectorFormat,
			ValueAxis xAxis, ValueAxis yAxis) {
		super();
		nData = y.length;
		if (t.length != nData){
			throw new IllegalArgumentException("arrays were unequal length");
		}
		yData = y;
		times = t;
		setName(name);
		this.markers = markers;
		this.markerFormats = markerFormats;
		drawMarkers = new boolean[markerFormats.length];
		determineMarkerDrawability();
		this.connectorFormat = connectorFormat;	
		selectionSlop = 10;
		setDragBehavior(Chart.DRAG_CREATES_SELECTION_BOX);
		this.xAxis = xAxis;
		this.yAxis = yAxis;
		setVisible(true);
		xAxis.addPlot(this);
		xAxis.addAxisListener(this);
		yAxis.addPlot(this);
		yAxis.addAxisListener(this);
		addComponentListener(this);
		mouseIndex = -1;  // represents point which the mouse is over
		// default limits on marker size
		maxMarkerForegroundSize = 6;
		minMarkerForegroundSize = 0;
		maxMarkerBackgroundSize = 10;
		minMarkerBackgroundSize = 2;
		autoscaleMarker = true;
		resizeMarker();
	}	

	public void setMarkers(int[] rowNumbers, byte marker) {
		int nrows = rowNumbers.length;
		//System.out.println("selecting "+nrows+" points, select = "+ select);
		if (nrows == 0) {
			return;
		}
		int firstRow = rowNumbers[0];
		int lastRow = firstRow;
		int row;
		for (int i=0; i< rowNumbers.length; i++) {
			row = rowNumbers[i];
			markers[row] = marker;
			if (row < firstRow) {
				firstRow = row;
			} else if (row > lastRow) {
				lastRow = row;
			}
		}
		invalidateRowRange(firstRow-1, lastRow + 1);
	}

	public void setMarkerArray(byte[] markers) {
		this.markers = markers;
		invalidateRowRange(0, nData-1);
	}
	
	public byte[] getMarkerArray() {
		return markers;
	}
	
	public MarkerFormat[] getMarkerFormats() {
		return markerFormats;
	}

	public void setMarkerFormats(MarkerFormat[] formats) {
		markerFormats = formats;
		drawMarkers = new boolean[formats.length];
		determineMarkerDrawability();
		resizeMarker();
	}

	public void changeAxis(ValueAxis newAxis) {
		// used for plotting this chart against a new axis
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
	public Range getRange(int dimension) {
		if (dimension == 1) {
			// this procedure responds from a request from axis for range data
			// therefore, check the axis to see if it wants times or indexes
			if (xAxis.getAxisType()== ValueAxis.LONG_TYPE) {
				return new Range(times[0], times[nData-1]);
			} else {
				return new Range(0, nData-1);
			}
		} else {
			double ymin = Double.MAX_VALUE;
			double ymax = Double.NEGATIVE_INFINITY;
			for (int j=0; j < nData; ++j) {
				if (!(Double.isNaN(yData[j]))) {
					if (yData[j] < ymin) {
						ymin = yData[j];
					}
					if (yData[j] > ymax) {
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
			return new Range(ymin, ymax);
		}
	}

 	@Override
	public boolean isOpaque(){
		return false;
	}

	@Override
	public void paintComponent(Graphics g) {
		// do local assignments of scale factors
		boolean timeMode;
		long tmin;
		int xmin;
		if (xAxis.getAxisType()== ValueAxis.LONG_TYPE) {
			timeMode = true;
			tmin = xAxis.min.longValue();
			xmin = 0;  // compiler insists on initializing both xmin and tmin
		} else {
			timeMode = false;
			xmin = xAxis.min.intValue();
			tmin = 0l;
		}
		double x2Pixels = xAxis.units2Pixels;
		double y2Pixels = yAxis.units2Pixels;
		double pixels2X = xAxis.pixels2Units;
		double pixels2Y = yAxis.pixels2Units;
		double ymax = yAxis.max.doubleValue();
		// System.out.println("Painting, scale factors are: x2p ="+x2Pixels+", y2p = "+y2Pixels);
		Rectangle clip = g.getClipBounds();
		int pxStart = clip.x;
		int pxEnd = clip.x + clip.width;
		// allow 10 pixels extra for size of marker
		pxStart = pxStart - 10;
		pxEnd = pxEnd + 10;
		int startIndex = Math.max(0, pixelToRow(pxStart) - 1);
		int endIndex = Math.min(nData - 1, pixelToRow(pxEnd) + 1);
		//System.out.println("ComboPlot: painting from row "+startIndex+" to "+endIndex);
		int thisx, prevx;
		int miny = 0; 
		int maxy = 0;  // necessary only to satisfy compiler
		double yupper = 0.0; 
		double ylower = 0.0;
		int thisy = 0; 
		int prevy = 0;  // ditto
		boolean compressing = false;  // whether a pixel is overloaded
		boolean prevIsaNum = true;
		boolean thisIsaNum = true;
		boolean thisyready, onSamePixel;
		Color connectorColor = connectorFormat.lineColor;
		Color color = connectorColor;
		Color connectorColorObject = connectorColor;	//ColorMap.colors[connectorColor];
		g.setColor(connectorColorObject);
		// initialize the first point
		long nextTime = 0L;  // critical time indicating move to next pixel
		int nextRow = 0;    // critical row indicating move to next pixel
		if (timeMode) {
			prevx = (int) Math.rint(x2Pixels*(times[startIndex] - tmin));
			nextTime = Math.round((prevx+1)*pixels2X) + tmin;
		} else {
			prevx = (int) Math.rint(x2Pixels*(startIndex - xmin));
			nextRow = (int) Math.rint((prevx+1)*pixels2X) + xmin;
		}
		if (!(Double.isNaN(yData[startIndex]))) {
			prevy = (int) Math.rint(y2Pixels*(ymax - yData[startIndex]));
			// MK 1/31/99: draw symbol if i==0 (special case -- otherwise first point in not selectable)
			if(startIndex==0 && drawMarkers[markers[0]]) {
				thisy = (int) Math.rint(y2Pixels*(ymax - yData[0]));
				color = markerFormats[markers[0]].drawMarker(g, 0, thisy, color);
			}
		} else prevIsaNum = false;

		// now the core drawing loop
		for (int i = startIndex + 1; i <= endIndex; ++i) {
			// based on profiling this method, it is more efficient to calculate the 
			// break between pixels in units, rather than calculating a new pixel
			// position on every iteration.  The following minimizes the calculation
			// of thisx, only doing it when we've moved to a new pixel, as indicated by the 
			// inequalities (times[i] > nextTime) or (i >= nextRow)
			if (timeMode) {
				// System.out.print("time at " + i + "=" + times[i]);
				if (times[i] >= nextTime) {
					thisx = (int) Math.rint(x2Pixels*(times[i] - tmin));
					nextTime = Math.round((thisx+1)*pixels2X) + tmin; 
					//  System.out.println(" with this time=" + thisx + " and nextTime=" + nextTime);
					onSamePixel = false;
				} else {
					// System.out.println(" current time at " + i + " (" + times[i] + ")" + " is not >= than nextTime=" + nextTime); 
					thisx = prevx;
					onSamePixel = true;
				}
			} else {
				if (i >= nextRow) {
					thisx = (int) Math.rint(x2Pixels*(i - xmin));
					nextRow = (int) Math.rint((thisx+1)*pixels2X) + xmin;
					onSamePixel = false;
				} else {
					thisx = prevx;
					onSamePixel = true;
				}
			}
			thisyready = false;
			if (!(Double.isNaN(yData[i]))) {
				if (drawMarkers[markers[i]]) {
					thisy = (int) Math.rint(y2Pixels*(ymax - yData[i])); 
					thisyready = true;  // referenced below
					color = markerFormats[markers[i]].drawMarker(g, thisx, thisy, color);
				}
				thisIsaNum = true;
			} else {
				thisIsaNum = false;			
			}
			if (onSamePixel) { // still on same pixel, draw nothing
				if (!compressing && prevIsaNum) {
					//System.out.println("begin compressing, prevIsaNum = "+prevIsaNum);
					// initialize yupper and ylower
					yupper = yData[i - 1]; 
					ylower = yupper;
					compressing = true;
				}
				if (compressing && thisIsaNum) { 
					// compressing, update yupper and ylower
					// avoid conversion to pixels now; do that only when ready to draw
					if (yData[i] > yupper) {
						yupper = yData[i];
					} else if (yData[i] < ylower) {
						ylower = yData[i];
					}
				}
				// fix by bbush 8-16-98 to remedy NaNs showing up in chart as Maximum y value.
				if (!thisyready) {
					thisy = (int) Math.rint(y2Pixels * (ymax - yData[i]));
				}
			}
			else {  // moved to next pixel, draw it
				if (!color.equals(connectorColor)) {
					g.setColor(connectorColorObject);
					color = connectorColor;
				}
				if (!thisyready) {
					thisy = (int) Math.rint(y2Pixels * (ymax - yData[i]));
				}
				if (compressing) {// draw vertical line if previous pixel was overloaded
					//System.out.println("drawing vertical, miny = "+miny+" maxy = "+maxy);
					maxy = (int) Math.rint(y2Pixels * (ymax - ylower));
					miny = (int) Math.rint(y2Pixels * (ymax - yupper));
					g.drawLine(prevx, miny, prevx, maxy);  //vertical line
					// draw connecting line only if moving >1 x-pixel or moving outside of maxy - miny range
					boolean coordinateCheck = thisy > maxy || thisy < miny || thisx - prevx > 1;
					if (prevIsaNum && thisIsaNum &&   //gchen 8/15/98
							coordinateCheck) 
						g.drawLine(prevx, prevy, thisx, thisy);
					compressing = false;
				} else if (prevIsaNum && thisIsaNum) 
					g.drawLine(prevx, prevy, thisx, thisy);
			}

			//System.out.println("line from ("+prevx+","+prevy+") to ("+thisx+","+thisy+")");
			prevx = thisx;
			if (thisIsaNum){
				prevy = thisy;
			}
			prevIsaNum = thisIsaNum;
		}
	}
	
	public int pixelToRow(int px) {
		// finds row corresponding to px, returning the row AT or BEFORE the given pixel value.
		// -1 is used as an indicator of out-of-range
		if (xAxis.getAxisType()== ValueAxis.LONG_TYPE) {
			// use bisection -- should be efficient even for large data sets
			long xmin = xAxis.min.longValue();
			long xmax = xAxis.max.longValue();
			long x = Math.round(xAxis.pixels2Units*px) + xmin;
			if (x < xmin) {
				return -1;
			}else if (x > xmax) {
				return nData - 1;
			}
			int lowerBound = 0;
			int upperBound = nData - 1;
			int midPt;
			while (upperBound - lowerBound - 1 > 0) {
				midPt = (upperBound + lowerBound)/2;  // improve by right shifting bits ?
				if (x >= times[midPt]) {
					lowerBound = midPt;
				}
				else upperBound = midPt;
			}
			return lowerBound;
		} else {
			int row = (int) Math.floor(xAxis.pixels2Units*px);
			if (row < 0){
				return -1;
			}else if (row >= nData) {
				return nData - 1;
			}else {
				return row;
			}
		}
	}

	public double pixelToY(int py) {
		return yAxis.max.doubleValue() - yAxis.pixels2Units*py;	
	}

	@Override
	public boolean contains(int px, int py) {  
		int i = findPoint(px, py);
		if (i != -1) {
			if (i != mouseIndex) {  // reset tool tip
				int digits = yAxis.sigDigits + 1;
				if (xAxis.getAxisType()== ValueAxis.LONG_TYPE) {
					setToolTipText(getName()+" ("+xAxis.dateFormat.format(new Date(times[i]))+","+StringFormatter.DoubleToString(yData[i],digits)+")"); 
				// TO DO:  get rid of StringFormatter class
				} else {
					setToolTipText(getName()+" ("+i+","+StringFormatter.DoubleToString(yData[i],digits)+")"); 
				}
				mouseIndex = i;
			}
			return true;
		} else {
			mouseIndex = -1;
			return false;
		}
	}

	public int findPoint(int px, int py) { 
		double pixels2Y = yAxis.pixels2Units;
		double y2Pixels = yAxis.units2Pixels;
		double pixels2X = xAxis.pixels2Units;
		double x2Pixels = xAxis.units2Pixels;
		double y = yAxis.max.doubleValue() - pixels2Y*py;  // y coord of py
		double ytol = pixels2Y*selectionSlop;
		double x, xtol;
		int iStart;
		if (xAxis.getAxisType()== ValueAxis.LONG_TYPE) {
			x = pixels2X*px + xAxis.min.longValue();  // time coord of px
			xtol = pixels2X*selectionSlop;
			iStart = pixelToRow(px - selectionSlop);
		} else {
			x = pixels2X*px + xAxis.min.intValue();
			xtol = pixels2X*selectionSlop;
			iStart = (int) Math.ceil(x - xtol);
		}
		if (iStart < 0) {
			iStart = 0; 
		}
		int besti = -1;
		double thisDist;
		double bestDist = Double.MAX_VALUE;
		if (xAxis.getAxisType()== ValueAxis.LONG_TYPE) {
			int i = iStart;
			double endTime = x + xtol;
			while (i < nData && times[i] < endTime) {
				if (!(Double.isNaN(yData[i]))) {
					if (Math.abs(x - times[i]) < xtol && Math.abs(y - yData[i]) < ytol) {
						thisDist = Math.abs(x2Pixels*(x - times[i])) + Math.abs(y2Pixels*(y - yData[i]));
						if(thisDist < bestDist) {
							bestDist = thisDist;
							besti = i;
						}
					}
				}
				++i;
			}
		} else {
			int iEnd = (int) Math.floor(x + xtol);
			if (iEnd >= nData){
				iEnd = nData - 1;
			}
			for(int i = iStart; i<=iEnd; ++i) {
				if (!(Double.isNaN(yData[i]))) {
					if (Math.abs(x - i) < xtol && Math.abs(y - yData[i]) < ytol) {
						thisDist = Math.abs(x2Pixels*(x - i)) + Math.abs(y2Pixels*(y - yData[i]));
						if(thisDist < bestDist) {
							bestDist = thisDist;
							besti = i;
						}
					}
				}
			}
		}
		return besti;
	}

	private void invalidateRowRange(final int firstRow, final int lastRow) {
		//System.out.println("invalidating from "+firstRow+" to "+lastRow);
		int px1;
		int px2;
		int firstRowIndex = firstRow;
		int lastRowIndex = lastRow;
		if (firstRowIndex < 0) {
			firstRowIndex = 0;
		}
		if (lastRowIndex >= nData) {
			lastRowIndex = nData - 1;
		}
		double x2Pixels = xAxis.units2Pixels;
		if (xAxis.getAxisType()== ValueAxis.LONG_TYPE) {
			long tmin = xAxis.min.longValue();
			px1 = (int) Math.rint(x2Pixels*(times[firstRowIndex] - tmin));
			px2 = (int) Math.rint(x2Pixels*(times[lastRowIndex] - tmin));
		} else {
			int xmin = xAxis.min.intValue();
			px1 = (int) Math.rint(x2Pixels*(firstRowIndex - xmin));
			px2 = (int) Math.rint(x2Pixels*(lastRowIndex - xmin));
		}
		Rectangle r = addPadding(new Rectangle(px1, 0, px2 - px1, getSize().height));
		if(itsChart == null) {
			return;
		}
		itsChart.addInvalidation(itsChart.toChartCoordinates(this, r));
		itsChart.repaint();
	}

	private Rectangle addPadding(Rectangle r) {
		// compensate for width of data point plot symbols
		int padding = 10;  // max size of marker, TBD -- do not hard code!
		r.x = r.x - padding;
		r.y = r.y - padding;
		r.width = r.width + 2*padding;
		r.height = r.height + 2*padding;
		return r;
	} 
	

	// Listeners

	@Override
	public void componentResized(ComponentEvent event) {
		resizeMarker();
	}

	public void resizeMarker(){
		// this is based on "what looks good" to my eye ;-)
		if (!autoscaleMarker) {
			return;
		}
		int foregroundSize = (int) Math.rint((double) getSize().width/(double) nData);
		if (foregroundSize < minMarkerForegroundSize){
			foregroundSize = minMarkerForegroundSize;
		}
		if (foregroundSize > maxMarkerForegroundSize) {
			foregroundSize = maxMarkerForegroundSize;
		}
		int backgroundSize;
		if (foregroundSize <= 1) {
			backgroundSize = 3;
		} else if (foregroundSize == 2) {
			backgroundSize = 4;
		} else if (foregroundSize == 3) {
			backgroundSize = 6;
		} else {
			backgroundSize = foregroundSize + 4;
		}
		
		if (backgroundSize < minMarkerBackgroundSize) {
			backgroundSize = minMarkerBackgroundSize;
		}
		
		if (backgroundSize > maxMarkerBackgroundSize) {
			backgroundSize = maxMarkerBackgroundSize;
		}
		
		MarkerFormat mf;
		for (int i=0; i< markerFormats.length; i++) {
			mf = markerFormats[i];
			mf.setForegroundSize(foregroundSize);
			mf.setBackgroundSize(backgroundSize);
		}
		determineMarkerDrawability();
	}

	private void determineMarkerDrawability() {
		// privately keep info on whether this marker really needs to be drawn
		// to avoid unnecessary calls to MarkerFormat.drawMarker from paint
		MarkerFormat mf;
		for (int i=0; i< markerFormats.length; i++) {
			mf = markerFormats[i];
			if ((mf.getForegroundSize() == 0 || mf.getForegroundColor() == null) 
				&& (mf.getBackgroundSize() == 0 || mf.getBackgroundColor() == null)) drawMarkers[i] = false;
			else drawMarkers[i] = true;
		}
	}


	@Override
	public void componentHidden(ComponentEvent event) {}
   	@Override
	public void componentMoved(ComponentEvent event) {}
	@Override
	public void componentShown(ComponentEvent event) {}

	@Override
	public void axisRescaled(AxisEvent e) {
		//System.out.println("Plot get axis rescale event");
		invalidateRowRange(0, nData - 1);
	}
}
