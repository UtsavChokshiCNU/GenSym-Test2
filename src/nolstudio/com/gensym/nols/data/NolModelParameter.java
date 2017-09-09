package com.gensym.nols.data;
/*
 *		Gensym Model Class.
 *		This class is extended from Object.class
 *		Modified 3/25/98 by Gchen
 */

import java.util.*;

import java.io.*;

public class NolModelParameter implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	public Vector inputs;
	public Vector outputs;
	public Vector inputDelays;
	public Vector outputDelays;
	public boolean isTrained;
	public String comment;
	public int delayTimeUnit; // 1: Hour; 2: Minute; 3: Second.
	public boolean hasTimeStamps;
	public String name;
	public String preprocessorName;
	public int typeFlag;


/** Create a null data Model object. */	
	public NolModelParameter() {
		super();
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		NolModelParameter cloned = (NolModelParameter) super.clone();
		cloned.inputs = inputs == null ? null : (Vector) inputs.clone();
		cloned.outputs = outputs == null ? null : (Vector) outputs.clone();
		cloned.inputDelays = inputDelays == null ? null : (Vector) inputDelays.clone();
		cloned.outputDelays = outputDelays == null ? null : (Vector) outputDelays.clone();
		
		return cloned;
	}
}