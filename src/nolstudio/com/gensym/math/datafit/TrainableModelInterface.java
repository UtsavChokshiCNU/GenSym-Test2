package com.gensym.math.datafit;

import com.gensym.math.matrix.Matrix;
import com.gensym.math.MathException;

public interface TrainableModelInterface extends Model {
	public void learn(Matrix X, Matrix Y) throws MathException;
}