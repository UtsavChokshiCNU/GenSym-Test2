package com.gensym.nols.data.function;

import java.util.*;
import com.gensym.math.MathException;


public class ReplaceLowValue extends Function {
	
	public ReplaceLowValue() {
		super();
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "ReplaceLowValue";
	}

	@Override
	public String getDescription() {
		return "D = ReplaceLowValue(A,B,C). If A < B, then D = C, otherwise D = A.";
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
			if(invals[i] < thresholds[i]){
				outvals[i] = replacements[i];
			}
			else outvals[i] = invals[i];
		}
	}

}


/*
	public void setPropertyValue(String name, Object value) throws FormulaException {
		if(name.equals("threshold")) {
			if(value instanceof Double) threshold = (Double) value;
			else throw new FormulaException("Illegal property value for threshold");
		} else if(name.equals("replacement")) {
			if(value instanceof Double) replacement = (Double) value;
			else throw new FormulaException("Illegal property value for replacement value");
		}
		throw new FormulaException("CUT LOW does not have a property named "+name);
	}
*/