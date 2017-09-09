package com.gensym.nols.chart.line;

import java.awt.AWTEvent;
import java.awt.Event;
import java.lang.*;

public interface ChartListener {
	public void chartPointSelected(ChartEvent e);
	public void chartAreaSelected(ChartEvent e);
	public void chartPopupTriggered(ChartEvent e);
}