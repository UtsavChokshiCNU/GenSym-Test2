package com.gensym.nols.data.function;

import java.security.SecureRandom;
import java.util.*;
import com.gensym.math.MathException;

public class RandUniform extends Function {
	
	public RandUniform() {
		super();
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "RandUniform";
	}

	@Override
	public String getDescription() {
		return "C = RandUniform(A,B).  Returns random numbers uniformly distributed between lower limit A and upper limit B.";
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
		double[] lb = (double[]) inputs.elementAt(0);
		double[] ub = (double[]) inputs.elementAt(1);
		double[] outvals = (double[]) outputs.elementAt(0);
		int nvals = lb.length;
		SecureRandom Ran = new SecureRandom();
		Ran.setSeed((long)(new SecureRandom().nextDouble() *1.0e6));
		for(int i=0;i<nvals;i++) {
			outvals[i] = (ub[i] - lb[i])*Ran.nextDouble() + lb[i];   // Does nextDouble give a double in the (0,1) range??
		}
	}

}

