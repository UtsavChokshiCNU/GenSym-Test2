package com.gensym.nols.data.function;

import java.util.*;
import com.gensym.math.MathException;


public class CutRepeatValue extends Function {
	
	public CutRepeatValue() {
		super();
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "CutRepeatValue";
	}

	@Override
	public String getDescription() {
		return "D = CutRepeatValue(A). If A(t)==A(t-1)(t is row index), then D = NaN, otherwise D = A.";
	}

	/** returns the minimum number of input arguments, given current properties */
	@Override
	public int getMinimumInputs() {
		return 1;
	}

	/** returns the maximum number of input arguments, given current properties. */
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
		if(nvals <1) 
			return;
		outvals[0] = invals[0];
		if(nvals <2) 
			return;
		for(int i=1;i<nvals;i++) {
			if(Double.compare(invals[i], invals[i-1]) == 0){
				outvals[i] = Double.NaN;
			}else{
				outvals[i] = invals[i];
			}
		}
	}

}
