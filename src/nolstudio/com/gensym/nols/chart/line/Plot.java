package com.gensym.nols.chart.line;

import java.awt.*;
import java.util.*;

public abstract class Plot extends ChartComponent {
	transient Vector itsListeners;
	ChartBackground itsBackground;  // used to establish selection box limits

	public Plot() {
		super();
		itsListeners = new Vector(0, 10);
		itsBackground = null;
	}

	public Range getRange(int dimension) {
		// should be abstract??
		Range r = new Range(0, 1);
		return r;
	}

	public void addPlotListener(PlotListener l) {
		itsListeners.addElement(l);
	}

	public void removePlotListener(PlotListener l) {
		itsListeners.removeElement(l);
	}

	public void setBackgroundComponent(ChartBackground b) {
		itsBackground = b;
	}

	@Override
	public Rectangle getSelectionBoxConstraints() {
		if (itsBackground != null) {
			return itsChart.getVisiblePortion(itsBackground);
		}else {
			return super.getSelectionBoxConstraints();
		}
	}

	public void fireEvent(PlotEvent e){
		int nl = itsListeners.size();
		for(int	i=0;i<nl;i++){
			PlotListener l = (PlotListener)itsListeners.elementAt(i);
			l.plotRangeChanged(e);
		}
	}
}
