package com.gensym.nols.data;

import java.util.Vector;

import com.gensym.math.datafit.Model;

public interface INolModel2 extends Model {

	String getComment();

	Vector getInputDelays();

	Vector getInputs();

	Object getModel();

	String getName();

	Vector getOutputDelays();

	Vector getOutputs();

	boolean isTrained();

	void setIsTrained(boolean b);

	boolean isRecursiveModel();
	
	int getDelayTimeUnit();

}
