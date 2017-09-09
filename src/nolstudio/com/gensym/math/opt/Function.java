package com.gensym.math.opt;

import com.gensym.math.matrix.Matrix;
import com.gensym.math.MathException;

public interface Function {
	/** Evaluates a (potentially) multiple-input multiple-output function at 
	one or more points in the independent variable space given by the rows 
	of X to produce the predictions of dependent variables Y */
	public void evaluate(Matrix X, Matrix Y) throws MathException;
}