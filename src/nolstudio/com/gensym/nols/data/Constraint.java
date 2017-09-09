package com.gensym.nols.data;
/*
 *		Gensym Constraint Class.
 *		This class is extended from Object.class
 *		Modified 9/12/98 by Gchen
 */

import java.io.Serializable;
import java.util.Vector;

public class Constraint implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;
	private int number;
	private String name;
	private String sense;
	private String contents;
	private double rhv;
	private Vector innerVariables;
	private boolean defined;

	/** Create a new Constraint containing no characters.*/
	public Constraint() {
		number  = 0;
		contents = "0.0";
		sense = "E";
		innerVariables = new Vector();
		defined = false;
	}

/** Create a new Constraint with a name.*/
	public Constraint(int n, String name, String s, double rhv) {
		this();
		number = n;
		this.name = name;
		this.sense = s;
		this.rhv = rhv;
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		Constraint cloned = (Constraint) super.clone();
		cloned.innerVariables = innerVariables == null ? null : (Vector) innerVariables.clone();
		
		return cloned;
	}

/** Get the name of this data project. */	
	public String getName(){
		return name;
	}

/** Set the name of this data project. */	
	public void setName(String n){
		name = n;
	}

/** Set the sense of this data project. */	
	public void setSense(String n){
		sense = n;
	}

/** Get the sense of this data project. */	
	public String getSense(){
		return sense;
	}

	public int getNumber(){
		return number;
	}

/** Get the right Hand Value of this data project. */	
	public double getRightHandValue(){
		return rhv;
	}

/** Set the right Hand Value of this data project. */	
	public void setRightHandValue(double v){
		rhv = v;
	}

/** Get the define status. */	
	public boolean getDefined(){
		return defined;
	}

/** Set the define status. */	
	public void setDefined(boolean v){
		defined = v;
	}

	@Override
	public boolean equals(Object obj){
		if(obj == null || !getClass().equals(obj.getClass())) {
			return false;
		}
		Constraint objVar = (Constraint)obj;
		return objVar.name.equals(this.name);
	}
	
	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 1;
		return prime * result + ((this.name == null) ? 0 : this.name.hashCode());
	}

	@Override
	public String toString(){
		return name;
	}

	public String getContent(){
		return contents;
	}

	public String getContentString(){
		String str = "lhs["+number+"] = " +contents;
		return str;
	}

	public void setContent(String c){
		contents = c;
	}

	public void addInnerVariable(Variable var){
		innerVariables.addElement(var);
	}

	public void removerInnerVariable(Variable var){
		innerVariables.removeElement(var);
	}

	public String getInternalVarString(){
		StringBuffer sb = new StringBuffer();
		for(int i=0;i<innerVariables.size();i++){
			Variable var = (Variable)innerVariables.elementAt(i);
			sb.append("double "+var.toString()+";\n");
		}
		return sb.toString();
	}
}