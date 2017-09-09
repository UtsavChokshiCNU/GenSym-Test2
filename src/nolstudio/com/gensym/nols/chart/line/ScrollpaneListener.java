package com.gensym.nols.chart.line;

import java.awt.AWTEvent;
import java.awt.Event;
import java.lang.*;

public interface ScrollpaneListener {
	public void scrollpaneResized(ScrollpaneEvent e);
	public void scrollpaneScrolled(ScrollpaneEvent e);
}