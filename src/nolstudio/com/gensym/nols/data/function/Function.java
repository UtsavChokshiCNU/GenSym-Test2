package com.gensym.nols.data.function;

import java.io.Serializable;
import java.util.Vector;

import com.gensym.math.MathException;

/** A convenience class trivially implementing FunctionInterface methods */

public class Function implements Serializable, FunctionInterface {

	/** We added a clone() method when the serial version UID
	    was this, so we now declare this as to preserve backward
	    compatibility.
	 */
	private static final long serialVersionUID = 3070357386483768315L;

	public Function() {
		super();
	}

	/** Gets the name of the function, in a form that can be displayed to the user */
	@Override
	public String getName() {
		return "";
	}

	@Override
	public String getDescription() {
		return ("No information on "+getName());
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

	/** Evaluates the function.  Inputs and outpus are vectors whose 
	elements are double arrays. Arrays are equal length, matching time stamps t.
	For time-independent functions, the time vector will be passed in as null.
	Outputs are pre-sized according to the getNumberOfOutputs method. */

	@Override
	public void evaluate(long t[], Vector inputs, Vector outputs) throws MathException {
	}

	@Override
	public Vector getInputVarNames() {
		return null;
	}

	@Override
	public Vector getOutputVarNames() {
		return null;
	}

	@Override
	public long getRequiredHistoryLength() {
		return 0L;
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}
}



