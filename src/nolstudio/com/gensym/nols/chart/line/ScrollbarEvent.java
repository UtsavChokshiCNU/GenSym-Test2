package com.gensym.nols.chart.line;

import java.awt.AWTEvent;
import java.awt.Event;
import java.lang.*;

public class ScrollbarEvent {
	private ChartScrollbar source;

	ScrollbarEvent(ChartScrollbar bar) {
		source = bar;
	}

	public ChartScrollbar getScrollbar() {
		return source;
	}
}