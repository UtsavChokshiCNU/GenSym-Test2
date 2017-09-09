package com.gensym.math.opt;

import com.gensym.math.matrix.Matrix;
import com.gensym.math.MathException;

public interface BoundedFunction extends Function {
	/** Returns the bounds on the independent variables in two
	row vectors.  If there are no bounds on a particular variable,
	use Double.POSITIVE_INFINITY or Double.NEG_INFINITY */
	public void getBounds(Matrix LB, Matrix UB) throws MathException;
}