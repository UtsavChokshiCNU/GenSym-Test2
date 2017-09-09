package com.gensym.nols.data.function;

import java.util.*;
import com.gensym.math.MathException;

public class Sum extends Function {
	
	public Sum() {
		super();
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "Sum";
	}

	@Override
	public String getDescription() {
		return "C = Sum(A,B,...).  Returns the sum of two or more input arguments";
	}

	/** returns the minimum number of input arguments */
	@Override
	public int getMinimumInputs() {
		return 2;
	}

	/** returns the maximum number of input arguments. */
	@Override
	public int getMaximumInputs() {
		return 99999;
	}

	/** returns the number of outputs, given the number of input args */
	@Override
	public int getNumberOfOutputs(int numberOfInputs) {
		return 1;
	}

	@Override
	public void evaluate(long t[], Vector inputs, Vector outputs) throws MathException {
		// initialize outputs
		double[] outvals = (double[]) outputs.elementAt(0);
		int n = outvals.length;
		for(int i=0;i<n;i++){
			outvals[i] = 0.0;
		}
		for(int j=0;j<inputs.size();j++) {
			double[] invals = (double[]) inputs.elementAt(j);
			for (int i=0;i<n;i++) {
				outvals[i] += invals[i];
			}
		}
	}

}

