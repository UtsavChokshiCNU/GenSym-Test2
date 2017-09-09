package com.gensym.nols.data.function;

import java.util.*;
import com.gensym.math.MathException;

public class Sqrt extends Function {
	
	public Sqrt() {
		super();
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "Sqrt";
	}

	@Override
	public String getDescription() {
		return "B = Sqrt(A).  Returns the square root of its argument";
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
			if(invals[i]<0.0){
				throw new MathException("Square root of negative number "+invals[i]+" in row "+i);
			}
			outvals[i] = Math.sqrt(invals[i]);
		}
	}

}

