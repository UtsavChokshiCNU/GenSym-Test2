package com.gensym.nols.chart.line;

import java.awt.AWTEvent;
import java.awt.Event;
import java.lang.*;

public class ScrollpaneEvent {
	private ChartScrollpane source;

	ScrollpaneEvent(ChartScrollpane pane) {
		source = pane;
	}

	public ChartScrollpane getScrollpane() {
		return source;
	}
}