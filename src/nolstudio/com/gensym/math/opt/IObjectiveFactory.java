package com.gensym.math.opt;

import com.gensym.math.MathException;
import com.gensym.math.matrix.Matrix;
import com.gensym.nols.data.INolOptimizeModel;

public interface IObjectiveFactory {

	INolObjective createObjective(INolOptimizeModel optModel,
			boolean[] varMask, Matrix xBounds, Matrix xCosts, Matrix yBounds,
			Matrix yCosts) throws MathException;

}
