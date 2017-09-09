package com.gensym.nols.util;
import java.awt.*;
import java.awt.event.*;
import java.util.*;
import java.lang.Object.*;

public class NolSliderEvent {

	private int type;
	private NolSlider slider;
	private double lowLimit;
	private double softLow;
	private double softHigh;
	private double highLimit;
	private double setpoint;
	private double current;

	NolSliderEvent(NolSlider s, int t, double val) {
		super();
		slider = s;
		type = t;
		if(type == 0)
			lowLimit = val;
		else if(type == 1)
			softLow = val;
		else if(type == 2)
			setpoint = val;
		else if(type == 3)
			softHigh = val;
		else if(type == 4)
			highLimit = val;
		else if(type == 5)
			current = val;
	}

	NolSliderEvent(NolSlider s, double lb, double slb, double set,
		double sub, double ub, double val){
		super();
		slider = s;
		type = -1;
		lowLimit = lb;
		softLow = slb;
		setpoint = set;
		softHigh = sub;
		highLimit = ub;
		current = val;
	}

	public int getType() {
		return type;
	}

	public double getLowLimit() {
		return lowLimit;
	}
	public double getSoftLow() {
		return softLow;
	}
	public double getSetpoint() {
		return setpoint;
	}
	public double getSoftHigh() {
		return softHigh;
	}
	public double getHighLimit() {
		return highLimit;
	}
	public double getCurrent() {
		return current;
	}
}