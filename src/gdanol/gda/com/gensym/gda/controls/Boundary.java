package com.gensym.gda.controls;


/**
Boundary defines methods for setting and getting min and max values.
*/
public interface Boundary {
	
	public void setMaxValue(double value);
	
	public double getMaxValue();
	
	public void setMinValue(double value);
	
	public double getMinValue();
	
}