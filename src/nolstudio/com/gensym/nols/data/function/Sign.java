package com.gensym.nols.data.function;

import java.util.*;
import com.gensym.math.MathException;

public class Sign extends Function {
	
	public Sign() {
		super();
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "Sign";
	}

	@Override
	public String getDescription() {
		return "B = Sign(A).  Returns -1,0, or +1 depending on whether A<0, A=0, or A>0, respectively.";
	}

	/** returns the minimum number of input arguments */
	@Override
	public int getMinimumInputs() {
		return 1;
	}

	/** returns the maximum number of input arguments */
	@Override
	public int getMaximumInputs() {
		return 1;
	}

	/** returns the number of outputs, given the number of input args */
	@Override
	public int getNumberOfOutputs(int numberOfInputs) {
		return 1;
	}

	@Override
	public void evaluate(long t[], Vector inputs, Vector outputs) throws MathException {
		double[] invals = (double[]) inputs.elementAt(0);
		double[] outvals = (double[]) outputs.elementAt(0);
		int nvals = invals.length;
		for(int i=0;i<nvals;i++) {
			if(Double.isNaN(invals[i])) 
				outvals[i] = Double.NaN;
			else if(invals[i]>0.0) 
				outvals[i] = 1.0;
			else if(Double.compare(invals[i], 0.0) == 0) 
				outvals[i] = 0.0;
			else 
				outvals[i] = -1.0;
		}
	}

}

