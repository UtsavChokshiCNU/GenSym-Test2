package com.gensym.nols.data;
import java.io.Serializable;
import java.util.Vector;

public class LabelPattern implements Cloneable, Serializable{
	static final long serialVersionUID = 1L;
	public Vector labelsPresent;  // contains integers corresponding to 
	public Vector labelsAbsent;
	public Vector existLabels;

	public LabelPattern() {
		// creates a label pattern with no restrictions
		super();
		labelsPresent = new Vector(); 
		labelsAbsent = new Vector(); 
		existLabels = new Vector(); 
	}

	public LabelPattern(Vector labelsPresent, Vector labelsAbsent,Vector existLabels) {
		super();
		this.labelsPresent = labelsPresent;
		this.labelsAbsent = labelsAbsent;
		this.existLabels = existLabels;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		LabelPattern cloned = (LabelPattern) super.clone();
		cloned.labelsPresent = labelsPresent == null ? null : (Vector) labelsPresent.clone();
		cloned.labelsAbsent  = labelsAbsent == null  ? null : (Vector) labelsAbsent.clone();
		cloned.existLabels   = existLabels  == null  ? null : (Vector) existLabels.clone();
		
		return cloned;
	}
	
	public Vector getLabelsPresent(){
		return labelsPresent;
	}

	public Vector getLabelsAbsent(){
		return labelsAbsent;
	}

 	public void setLabelsPresent(Vector labs){
		labelsPresent = labs;
	}

	public void setLabelsAbsent(Vector labs){
		labelsAbsent = labs;
	}

	public Vector getExistLabels(){
		return existLabels;
	}

 	public void setExistLabels(Vector labs){
		existLabels = labs;
	}

	public boolean matchesPattern(boolean[][] labelMatrix, int rowNumber) {
		// determines whether the labels given in labelsPresent are true,
		// and the labels given in labelsAbsent are false
		for (int j=0; j<labelsPresent.size(); j++) {
			NolLabel lab = (NolLabel)labelsPresent.elementAt(j);
			int labelIndex = existLabels.indexOf(lab);
			if(!labelMatrix[labelIndex][rowNumber]){
				return false;
			}
		}
		for (int j=0; j<labelsAbsent.size(); j++) {
			NolLabel lab = (NolLabel)labelsAbsent.elementAt(j);
			int labelIndex = existLabels.indexOf(lab);
			if(labelMatrix[labelIndex][rowNumber]){
				return false;
			}
		}
		return true;
	}

	@Override
	public boolean equals(Object obj){
		if(obj == null || !getClass().equals(obj.getClass())) {
			return false;
		}
		
		LabelPattern p1 = (LabelPattern)obj;
		for (int j=0; j<labelsPresent.size(); j++) {
			NolLabel lab = (NolLabel)labelsPresent.elementAt(j);
			if(!p1.labelsPresent.contains(lab)){
				return false;
			}
		}
		for (int j=0; j<labelsAbsent.size(); j++) {
			NolLabel lab = (NolLabel)labelsAbsent.elementAt(j);
			if(!p1.labelsAbsent.contains(lab)){
				return false;
			}
		}
		return true;
	}
	
	/** Overide the object hashcode method.*/
	@Override
	public int hashCode() {
		final int prime = 31;
    	int result = 1;
    	result = prime * result + ((labelsPresent == null) ? 0 : labelsPresent.hashCode());
    	result = prime * result + ((labelsAbsent == null) ? 0 : labelsAbsent.hashCode());
    	return result;
	}


	public boolean hasLabel(NolLabel lab){
		if(labelsPresent.contains(lab))
			return true;
		if(labelsAbsent.contains(lab))
			return true;
		return false;
	}
}