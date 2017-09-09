package com.gensym.nols.data.function;

import java.util.Vector;

import com.gensym.math.MathException;

public interface FunctionInterface extends Cloneable {
	
	/** Gets the name of the function, in a form that can be displayed to the user */
	public String getName();

	/** A description of the function and its arguments */
	public String getDescription();

	/** returns the minimum number of input arguments, given current properties */
	public int getMinimumInputs();

	/** returns the maximum number of input arguments. */
	public int getMaximumInputs();

	/** returns the number of outputs */
	public int getNumberOfOutputs(int numberOfInputs);

	/** Evaluates the function.  Inputs and outpus are vectors whose 
	elements are double arrays. Arrays are equal length, matching time stamps t.
	For time-independent functions, the time vector will be passed in as null.
	Outputs are pre-sized according to the getNumberOfOutputs method. */

	public void evaluate(long t[], Vector inputs, Vector outputs) throws MathException;

	/** Returns the names of the inputs, if known, such as in the case of a trained model.
	May return null if the inputs are not known */
	public Vector getInputVarNames();

	/** Returns the names of the outputs, if known, such as in the case of a trained model.
	May return null if the outputs are not known */
	public Vector getOutputVarNames();

	/** Returns the required time delay for this function */
	public long getRequiredHistoryLength();

	public Object clone() throws CloneNotSupportedException;
}

