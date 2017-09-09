package com.gensym.math.opt;

import com.gensym.math.MathException;
import com.gensym.math.matrix.Matrix;

public interface INolObjective extends Function {

	void clearMatrices();

	void createSimplex(Matrix x0, Matrix simplexP);

	void evaluateModel(Matrix simplexP, Matrix x, Matrix y)
		throws MathException;

	boolean[] getVariableMasks();

}
