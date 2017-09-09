package com.gensym.nols.chart.line;

public class PlotEvent {
	public static final int NEW_MINIMUM = 0;
	public static final int NEW_MAXIMUM = 1;
	private Plot source;
	private int type;
	private Number value;

	public PlotEvent(Plot plot, int eventType) {
		source = plot;
		type = eventType;
	}

	public PlotEvent(Plot plot, int eventType, Number v) {
		source = plot;
		type = eventType;
		value = v;
	}

	public Plot getPlot() {
		return source;
	}

	public int getType() {
		return type;
	}

	public Number getValue() {
		return value;
	}

	public void setValue(Number v) {
		value = v;
	}
}