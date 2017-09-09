package com.gensym.nols.data.function;

import java.io.*;
import java.lang.*;
import java.util.*;
import com.gensym.math.MathException;

public class Subtract extends Function {
	
	public Subtract() {
		super();
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "Subtract";
	}

	@Override
	public String getDescription() {
		return "C = Subtract(A,B).  Returns C = A - B";
	}

	/** returns the minimum number of input arguments */
	@Override
	public int getMinimumInputs() {
		return 2;
	}

	/** returns the maximum number of input arguments */
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
		double[] in1 = (double[]) inputs.elementAt(0);
		double[] in2 = (double[]) inputs.elementAt(1);
		double[] outvals = (double[]) outputs.elementAt(0);
		int nvals = in1.length;
		for(int i=0;i<nvals;i++) {
			outvals[i] = in1[i] - in2[i];
		}
	}

}

