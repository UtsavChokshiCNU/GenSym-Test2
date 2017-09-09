package com.gensym.nols.data;
/*
 *		Gensym Objective Class.
 *		This class is extended from Object.class
 *		Modified 9/12/98 by Gchen
 */

import java.io.Serializable;
import java.util.Vector;

public class Objective implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	private String name;
	private String content="objval[0]  = 0.0;\n";
	private Vector innerVariables;

/** Create a new Objective containing no characters.*/
	public Objective() {
		super();
		innerVariables = new Vector();
	}

/** Create a new optimization containing no characters.*/
	public Objective(String n) {
		this();
		name = n;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		Objective cloned = (Objective) super.clone();
		cloned.innerVariables = innerVariables == null ? null : (Vector) innerVariables.clone();
		return cloned;
	}

/** Get the name of this optimization. */	
	public String getName(){
		return name;
	}

/** Get the content of this optimization. */	
	public String getContent(){
		return content;
	}

/** Set the content of this optimization. */	
	public void setContent(String str){
		content = str;
	}

	public void addInnerVariable(Variable var){
		if(!innerVariables.contains(var)){
			innerVariables.addElement(var);
		}
	}

	public void removerInnerVariable(Variable var){
		innerVariables.removeElement(var);
	}

	public String getInternalVarString(){
		StringBuffer sb = new StringBuffer();
		for(int i=0;i<innerVariables.size();i++){
			Variable var = (Variable)innerVariables.elementAt(i);
			sb.append("double * "+var.getName()+";\n");
		}
		return sb.toString();
	}
}