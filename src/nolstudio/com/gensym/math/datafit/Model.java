package com.gensym.math.datafit;

import com.gensym.math.matrix.Matrix;
import com.gensym.math.MathException;

public interface Model {
	public int getNin();
	public int getNout();
	public ArchitectureParameters getArchitectureParameters();
	public void evaluate(Matrix X, Matrix Y) throws MathException;
}