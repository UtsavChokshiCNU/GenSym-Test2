package com.gensym.nols.data;
import java.lang.*;

public interface OptimizationListener {
	public void completeNewSample(int row);
	public void completeCalculation();
}