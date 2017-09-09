package com.gensym.nols.data.function;

import java.util.*;
import com.gensym.math.MathException;

public class Mean extends Function {
	
	public Mean() {
		super();
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "Mean";
	}

	@Override
	public String getDescription() {
		return "C = Mean(A,B,...).  Returns the mean of two or more input arguments";
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
		int no = outvals.length;
		int ni = inputs.size();
		for(int i=0;i<no;i++){
			outvals[i] = 0.0;
		}
		for(int j=0;j<ni;j++) {
			double[] invals = (double[]) inputs.elementAt(j);
			for (int i=0;i<no;i++) {
				outvals[i] += invals[i];
			}
		}
		for(int i=0;i<no;i++) {
			outvals[i] = outvals[i]/ni;
		}
	}

}

