package com.gensym.nols.data;
/*
 *		Gensym NolSimulation Class.
 *		This class is extended from Object.class
 *		Modified 9/12/98 by Gchen
 */

import java.io.Serializable;

public class NolSimulation extends DataSource implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	protected NolModel2 model;
	protected boolean isCalculated;

/** Create a new NolSimulation containing no characters.*/
	public NolSimulation() {
		super();
	}


/** Create a NolSimulation information object with NolSimulation and given index.*/
	public NolSimulation(Project project, NolModel2 model) {
		super(project);
		this.model = model;
	}

/** Return the model of this NolSimulation.*/
	public NolModel2 getModel(){
		return model;
	}

 /** Return the output dataseries.*/
	public DataSeries getOutputData(){
		return null;
	}

	public boolean isCalculated(){
		return isCalculated;
	}

	public void setCalculated(boolean isCalculated){
		this.isCalculated = isCalculated;
	}

	@Override
	public Object clone() throws CloneNotSupportedException {
		NolSimulation cloned = (NolSimulation) super.clone();
		cloned.model = model == null ? null : (NolModel2) model.clone();
		return cloned;
	}
	
	/** Overide the object equals method.*/
	@Override
	public boolean equals(Object obj){
		if(obj == null || !getClass().equals(obj.getClass()))
			return false;
		NolSimulation sim = (NolSimulation)obj;
		return sim.name.equals(this.name);
	}	

	/** Overide the object hashcode method.*/
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		return prime * result + ((this.name == null) ? 0 : this.name.hashCode());
	}

	/** Returns a String object representing this NolSimulation value.  */
	@Override
	public String toString(){
		return this.name;
	}
/** Calculate the NolSimulation*/
	public void calulationSimulation(){}

/** Initialize the transient part of this simulation. */
	@Override
	public void initTransient(Project p){
		super.initTransient(p);
	}

}