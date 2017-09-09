package com.gensym.nols.data;
/*
 *  Replaced by NolModel2 in V2.  Class is here for loading V1 projects only.
 */

import java.io.Serializable;
import java.util.Vector;

import com.gensym.math.datafit.EnsembleModel;
import com.gensym.math.datafit.Model;

public class NolModel extends Formula implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected int modelStructureFlag;
	protected Vector inputDelays;
	protected Vector outputDelays;
	protected Model model;
	protected boolean isTrained;
	private String comment;
	private int delayTimeUnit; // 1: Hour; 2: Minute; 3: Second.
	protected boolean hasTimeStamps;
	protected transient Preprocessor preprocessor;  // reference to preprocessor
	protected int preprocessorHashCode;  // reference to data series object

/** Create a null data Model object. */	
	public NolModel() {
		super();
	}

	public NolModel2 upgrade_1_2() {
		NolModel2 newModel = new NolModel2();
		newModel.preprocessor = null;  // preprocessor is transient, will never know at upgrade time
		newModel.preprocessorHashCode = preprocessorHashCode;
		newModel.name = name;
		newModel.model = null;
		if(properties!=null) {
			if(!properties.isEmpty()) 
				newModel.model = (EnsembleModel) properties.elementAt(0);
		}
		newModel.inputs = inputs;
		newModel.outputs = outputs;
		newModel.inputDelays = inputDelays;
		newModel.outputDelays = outputDelays;
		newModel.isTrained = isTrained;
		newModel.setComment(comment);
		newModel.setDelayTimeUnit(delayTimeUnit);
		newModel.hasTimeStamps = hasTimeStamps;
		return newModel;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		NolModel cloned = (NolModel) super.clone();
		cloned.inputDelays = inputDelays == null ? null : (Vector) inputDelays.clone();
		cloned.outputDelays = outputDelays == null ? null : (Vector) outputDelays.clone();
		cloned.preprocessor = preprocessor == null ? null : (Preprocessor) preprocessor.clone();
		
		return cloned;
	}
	
}