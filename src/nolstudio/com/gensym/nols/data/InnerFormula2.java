package com.gensym.nols.data;

import java.io.Serializable;
import java.util.Vector;

import com.gensym.nols.data.function.FunctionInterface;

/** InnerFormula2 class. The transform operation indexes 
can be add, modify, and delete from a vector. */
public class InnerFormula2 extends Formula2 implements Cloneable, Serializable {
	static final long serialVersionUID = 1L;

/** Create a null data transform object. */	
	public InnerFormula2() {
		super();
	}

	/** Clone creator */
	public InnerFormula2(InnerFormula2 formula) {
		super((Formula2) formula);
	}

/** Create a data transform object with given class name, method name, 
	inputs and outputs */	
	public InnerFormula2(FunctionInterface func, Vector ins, Vector outs) {
		super(func,ins,outs);
	}

/** Create a data transform object with given method name and inputs */
	public InnerFormula2(FunctionInterface func, Vector ins) {
		super(func,ins);
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}
	
	/** toString method*/
	@Override
	public String toString(){
	
		String s = getName()+"(";
		for(int i=0;i<inputs.size();i++){
			s=s+inputs.elementAt(i).toString();
			if(i<inputs.size()-1){
				s = s+", ";
			}
		}
		s = s +")";
		return s;
	}
	
}