package com.gensym.nols.data.function;

import java.util.*;
import com.gensym.math.MathException;


public class CutHighValue extends Function {
	
	public CutHighValue() {
		super();
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "CutHighValue";
	}

	@Override
	public String getDescription() {
		return "C = CutHighValue(A, B).  If A > B, then C = NaN, otherwise C = A.";
	}

	/** returns the minimum number of input arguments */
	@Override
	public int getMinimumInputs() {
		return 2;
	}

	/** returns the maximum number of input arguments. */
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
		double[] thresholds = (double[]) inputs.elementAt(1);
		double[] outvals = (double[]) outputs.elementAt(0);
		int nvals = invals.length;
		for(int i=0;i<nvals;i++) {
			if(invals[i] > thresholds[i]){
				outvals[i] = Double.NaN;
			}
			else outvals[i] = invals[i];
		}
	}

}

