package com.gensym.nols.data.function;

import java.util.*;
import com.gensym.math.MathException;


public class ReplaceHighValue extends Function {
	
	public ReplaceHighValue() {
		super();
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "ReplaceHighValue";
	}

	@Override
	public String getDescription() {
		return "D = ReplaceHighValue(A,B,C). If A > B, then D = C, otherwise D = A.";
	}

	/** returns the minimum number of input arguments, given current properties */
	@Override
	public int getMinimumInputs() {
		return 3;
	}

	/** returns the maximum number of input arguments, given current properties. */
	@Override
	public int getMaximumInputs() {
		return 3;
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
		double[] replacements = (double[]) inputs.elementAt(2);
		double[] outvals = (double[]) outputs.elementAt(0);
		int nvals = invals.length;
		for(int i=0;i<nvals;i++) {
			if(invals[i] > thresholds[i]){
				outvals[i] = replacements[i];
			}
			else outvals[i] = invals[i];
		}
	}

}
