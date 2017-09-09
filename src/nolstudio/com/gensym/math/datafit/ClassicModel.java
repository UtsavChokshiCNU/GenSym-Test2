package com.gensym.math.datafit;

import java.io.*;
import java.lang.*;
import java.util.*;
import com.gensym.math.MathException;
import com.gensym.math.matrix.Matrix;

public interface ClassicModel {
	
	/** Gets the name of the function, in a form that can be displayed to the user */
	public String getName();

	/** A description of the function and its arguments */
	public String getDescription();

	/** Returns the names of the inputs, if known, such as in the case of a trained model.
	May return null if the inputs are not known */
	public Vector getInputVarNames();

	/** Returns the names of the outputs, if known, such as in the case of a trained model.
	May return null if the outputs are not known */
	public Vector getOutputVarNames();

	public void evaluate(Matrix X, Matrix Y) throws MathException;

	public double getRMSE();

}

