package com.gensym.nols.data.function;

import java.util.*;
import com.gensym.math.MathException;
import com.gensym.math.matrix.TimeFunctions;

public class Delay extends Function {
	private double maximumTimeWindow;
	
	public Delay() {
		super();
		maximumTimeWindow = 0.0;
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "Delay";
	}

	@Override
	public String getDescription() {
		return "C = Delay(A, B).  Returns the value of variable A, B seconds before the current time.";
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
		double[] delays = (double[]) inputs.elementAt(1);
		double[] outvals = (double[]) outputs.elementAt(0);
		int n = invals.length;
		// set up time vector
		long delayedTimes[] = new long[t.length];
		for(int i=0;i<n;i++) {
			long delay = (long) (1000.0*delays[i]);
			delayedTimes[i] = t[i] - delay;
			if(delay > maximumTimeWindow){
				maximumTimeWindow = delay;
			}
		}
		double[] delayedVals = TimeFunctions.interpolateArray(invals,t,delayedTimes);
		System.arraycopy(delayedVals, 0, outvals, 0, n);
	}

	@Override
	public long getRequiredHistoryLength() {
		return (long) maximumTimeWindow;
	}

}


