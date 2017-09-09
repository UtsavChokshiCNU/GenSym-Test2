package com.gensym.nols.data;

import java.util.Vector;

import com.gensym.math.MathException;
import com.gensym.math.matrix.Matrix;

public interface INolOptimizeModel extends INolModel2, Cloneable {

	public Object clone() throws CloneNotSupportedException;
	Vector getExogenous();

	Vector getManipulate();

	IPreprocessor getPreprocessor();

	Vector getState();

	Vector getStateInput();

	Object getStateModel();

	String parametersToString();

	Vector getStateDelays();

	Vector getOutputVarNames();

	long[] prepareTrainingSetFromDataSeries(Vector retraindataSeries, Matrix x,
			Matrix y) throws MathException;

	long[] prepareTrainingSet2FromDataSeries(Vector retraindataSeries, Matrix i,
			Matrix d) throws MathException;

	Vector<long[]> getStateInputDelays();

}
