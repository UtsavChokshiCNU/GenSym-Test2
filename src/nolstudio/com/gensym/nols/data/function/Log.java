package com.gensym.nols.data.function;

import java.io.*;
import java.lang.*;
import java.util.*;
import com.gensym.math.MathException;

public class Log extends Function {
	
	public Log() {
		super();
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "Log";
	}

	@Override
	public String getDescription() {
		return "C = Log(A).  Returns the natural (base e) logarithm of A.";
	}

	/** returns the minimum number of input arguments */
	@Override
	public int getMinimumInputs() {
		return 1;
	}

	/** returns the maximum number of input arguments. */
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
			outvals[i] = Math.log(invals[i]);
		}
	}

}

