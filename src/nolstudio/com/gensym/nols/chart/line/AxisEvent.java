package com.gensym.nols.chart.line;

public class AxisEvent {
	public static final int RESCALED = 0;
	
	private ValueAxis source;
	private int type;

	AxisEvent(ValueAxis axis, int eventType) {
		source = axis;
		type = eventType;
	}

	public ValueAxis getAxis() {
		return source;
	}

	public int getType() {
		return type;
	}
}