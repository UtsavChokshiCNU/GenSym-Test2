package com.gensym.nols.data.function;

import java.util.*;
import com.gensym.math.MathException;

public class MovingAverage extends Function {
	private double maximumTimeWindow;
	
	public MovingAverage() {
		super();
		maximumTimeWindow = 0.0;
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "MovingAverage";
	}

	@Override
	public String getDescription() {
		return "C = MovingAverage(A, B).  Returns the average value of A over the previous B seconds.";
	}

	/** returns the minimum number of input arguments, given current properties */
	@Override
	public int getMinimumInputs() {
		return 2;
	}

	/** returns the maximum number of input arguments, given current properties. */
	@Override
	public int getMaximumInputs() {
		return 2;
	}

	/** returns the number of outputs, given the number of input args */
	@Override
	public int getNumberOfOutputs(int numberOfInputs) {
		return 1;
	}

	@Override
	public void evaluate(long t[], Vector inputs, Vector outputs) throws MathException {
		double[] invals = (double[]) inputs.elementAt(0);
		double[] intervals = (double[]) inputs.elementAt(1);
		double[] outvals = (double[]) outputs.elementAt(0);
		int nsamples, rows = invals.length;
		double d;
		if(invals.length == 0){
			return;
		}
		outvals[0] = invals[0];
		for(int r=rows-1;r>0;r--) {  // r>0 makes sure we don't change first row of M
			d = invals[r];
			nsamples = 1;
			double interval = 1000*intervals[r];  // convert seconds to milliseconds
			// store the interval as time window (info for on-line deployment)
			if(interval > maximumTimeWindow){
				maximumTimeWindow = interval;
			}
			// go back as far in time as specified by size
			while(true) {
				int s = r-nsamples;
				if(s<0 || t[r]-t[s]>interval){
					break;
				}
				d+=invals[s];
				nsamples++;
			}
			outvals[r] = d/nsamples;
			//if(!Double.isNaN(outvals[r])) System.out.println("r = "+r+" t = "+t[r]+" samples = "+nsamples+", result = "+outvals[r]);
		}
	}

	@Override
	public long getRequiredHistoryLength() {
		return (long) maximumTimeWindow;
	}

}


